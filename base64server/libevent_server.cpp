#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <glog/logging.h>
#include <glog/raw_logging.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <zlib.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "pdu.h"

#include <memory>
#include <iomanip>


char *base64(const unsigned char *input, int length)
{
	BIO *bmem, *b64;
	BUF_MEM *bptr;

	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bmem);
	BIO_write(b64, input, length);
	BIO_flush(b64);
	BIO_get_mem_ptr(b64, &bptr);

	char *buff = (char *)malloc(bptr->length);
	memcpy(buff, bptr->data, bptr->length-1);
	buff[bptr->length-1] = 0;

	BIO_free_all(b64);

	return buff;

}

int Base64Encode(const unsigned char* buffer, size_t length, char** b64text) { //Encodes a binary safe base 64 string
	BIO *bio, *b64;
	BUF_MEM *bufferPtr;

	b64 = BIO_new(BIO_f_base64());
	bio = BIO_new(BIO_s_mem());
	bio = BIO_push(b64, bio);

	BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines - write everything in one line
	BIO_write(bio, buffer, length);
	BIO_flush(bio);
	BIO_get_mem_ptr(bio, &bufferPtr);
	BIO_set_close(bio, BIO_NOCLOSE);
	BIO_free_all(bio);

	*b64text=(*bufferPtr).data;

	return (0); //success
}

std::string bin2hex(uint8_t* bin, size_t length) 
{
	std::ostringstream os;
	os.fill('0');
	for ( size_t i = 0; i < length; i++) {
		os <<std::setw(2) <<std::hex << std::uppercase <<(int)bin[i];
	}

	return os.str();
}

void buff_read_cb(struct bufferevent *bev, void *ctx)
{
	struct	evbuffer	*input	=	bufferevent_get_input(bev);
	size_t recvlen = evbuffer_get_length(input);
	// not enough size of a header
	if (recvlen < (sizeof(pdu_header) + 1)) {
		//LOG(INFO) << "not enough size of a header"; 
		return;
	}

	uint8_t head_data[sizeof(pdu_header)+1];
	evbuffer_copyout(input, head_data, sizeof(pdu_header)+1);
	struct pdu_header* ptr_header = (struct pdu_header *) (head_data+1);
	// not enough size of a complete package
	if (ptr_header->length > recvlen) {
		//LOG(INFO) << "not enough size, header->length["<<ptr_header->length <<"] received["<<recvlen<<"]" ;
		return;
	} else {
		//LOG(INFO) << "receive size["<< recvlen << "]" ;
	}

	void* pdu_data = malloc(ptr_header->length);
	if (pdu_data == NULL) {
		LOG(ERROR)<< "malloc failed for pdu data";
		return;
	}

	std::shared_ptr<void> ap_pdu_data(pdu_data, free);
	evbuffer_remove(input, pdu_data, ptr_header->length);

	LOG(INFO) << "package content: " << bin2hex((uint8_t*)pdu_data, ptr_header->length);
	
	bool valid = valid_pdu_package(pdu_data, ptr_header->length);
	if (!valid) {
		LOG(WARNING) << "not a valid pdu package";
		return;
	}

	LOG(INFO) << "received complete package";

	bufferevent_disable(bev, EV_READ);
	char* resp_data;
	//Base64Encode((const unsigned char *)pdu_data, ptr_header->length, &resp_data);
	uint8_t *pdu_body = (uint8_t *)pdu_data + 1 +sizeof(pdu_header);
	size_t body_length = ptr_header->length - 2 - sizeof(ptr_header);
	resp_data = base64((const unsigned char *)pdu_body, body_length);
	LOG(INFO) << "base64 encode: " << resp_data;
	std::shared_ptr<void> ap_resp_data(resp_data, free);

	struct evbuffer* write_evbuf = evbuffer_new();
	evbuffer_add_pdu(write_evbuf, resp_data, strlen(resp_data)+1);
	bufferevent_write_buffer(bev,write_evbuf);
	evbuffer_free(write_evbuf);

	bufferevent_enable(bev, EV_WRITE);
}

void buff_write_cb(struct bufferevent *bev, void *ctx)
{
	bufferevent_disable(bev, EV_WRITE);
	bufferevent_enable(bev, EV_READ);
}

void buff_error_cb(struct bufferevent *bev, short events, void *ctx)
{
	//RAW_LOG(INFO, "bufferevent events[%d]", events);
	if (events & BEV_EVENT_ERROR) {
	    PLOG(ERROR) << "Error from bufferevent";
	}

	if (events & BEV_EVENT_EOF)	{
      LOG(ERROR) << "connection closed by peer";
	}

	if (events & BEV_EVENT_TIMEOUT)  {
		if (events & BEV_EVENT_WRITING) {
			LOG(ERROR) << "write bufferevent timeout";
		}
		if (events & BEV_EVENT_READING) {
			LOG(ERROR) << "read bufferevent timeout";
		}
	}


	bufferevent_free(bev);
}

void accept_conn_cb(struct evconnlistener *listener,
		evutil_socket_t fd, struct sockaddr *address, int socklen,
		void *ctx)
{
	struct event_base *base = evconnlistener_get_base(listener);
	struct bufferevent *bev = bufferevent_socket_new(base, fd,
			BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(bev, buff_read_cb, buff_write_cb, buff_error_cb, NULL);
	bufferevent_enable(bev, EV_READ);
	bufferevent_disable(bev, EV_WRITE);
	struct timeval tv;
	tv.tv_sec = 5;
	tv.tv_usec = 0;
	bufferevent_set_timeouts(bev, &tv, &tv);
}

void accept_error_cb(struct evconnlistener *listener, void *ctx)
{
    struct event_base *base = evconnlistener_get_base(listener);
	int err = EVUTIL_SOCKET_ERROR();
	LOG(ERROR) << "Got an error " << err << "(" << evutil_socket_error_to_string(err) << ") on the listener";

	event_base_loopexit(base, NULL);
}

int main(int argc, char *argv[])
{
	FLAGS_log_dir = "./log";
//	FLAGS_logtostderr = true;
	FLAGS_minloglevel = 1;
	google::InitGoogleLogging(argv[0]);

	int port = 8888;

	if (argc > 1) {
		port = atoi(argv[1]);
	}

	if (port <=0 || port > 65545) {
		puts("Invaild port");
		return -1;
	}

    struct event_base *base;
	base = event_base_new();
	if (!base) {
		LOG(ERROR) << "Couldn't open event base";
		return -1;
	}

	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(0);
	sin.sin_port = htons(port);

	struct evconnlistener *listener;
	listener = evconnlistener_new_bind(base, accept_conn_cb, NULL,
			LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE, -1,
			(struct sockaddr*)&sin, sizeof(sin));
	if (!listener) {
		LOG(ERROR) << "Could't create listener";
		return -1;
	}

	evconnlistener_set_error_cb(listener, accept_error_cb);

	event_base_dispatch(base);

	return 0;
}
