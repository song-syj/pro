#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/event.h>
#include <glog/logging.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>
#include <zlib.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <time.h>
#include <arpa/inet.h>

#include <string>
#include <atomic>
#include <memory>
#include <iostream>
#include "pdu.h"
#include <sys/time.h>

int conn_num = 1000;

struct timeval startTime;
struct timeval endTime;

std::atomic_long connected(0);
std::atomic_long disconnected(0);
std::atomic_long sockerror(0);

static const char alphanum[] =
"0123456789"
"!@#$%^&*"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz";

int stringLength = sizeof(alphanum) - 1;

std::string gen_rand_str(size_t length)  // Random string generator function.
{

	srand(time(0));
	char* str = (char *)malloc(sizeof(char)* (length+1));
	for (size_t i = 0; i < length; i++) {
		str[i] = alphanum[rand() % stringLength];
	}
	str[length] = '\0';
	std::string rand_str(str);
	free(str);
	return rand_str;
}

void finishWork()
{
	LOG(WARNING)<< "client status: conneted["
		<< connected
		<< "] disconnected["
		<< disconnected
		<< "] sockerror["
		<< sockerror
		<< "]" << std::endl;
	gettimeofday(&endTime, NULL);

	int costTime = (endTime.tv_sec - startTime.tv_sec) * 1000 + (endTime.tv_usec - startTime.tv_usec) / 1000;

	LOG(WARNING) << "costTime["
		<< costTime << "]" << std::endl;

	exit(0);
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
	}

	void* pdu_data = malloc(ptr_header->length);
	if (pdu_data == NULL) {
		LOG(ERROR)<< "malloc failed for pdu data";
		return;
	}

	std::shared_ptr<void> ap_pdu_data(pdu_data, free);
	evbuffer_remove(input, pdu_data, ptr_header->length);
	
	bool valid = valid_pdu_package(pdu_data, (size_t)(ptr_header->length));
	if (!valid) {
		LOG(WARNING) << "not a valid pdu package";
		return;
	}

	char *msg = (char *)pdu_data + 1 + sizeof(struct pdu_header);
	//LOG(INFO) << "recieved msg: " <<  msg;
	//LOG(INFO) << "disconnected by host";
	disconnected++;
	bufferevent_free(bev);

	if ((disconnected + sockerror) == conn_num ) {
		finishWork();
	}
}

void buff_write_cb(struct bufferevent *bev, void *ctx)
{
	bufferevent_disable(bev, EV_WRITE);
	bufferevent_enable(bev, EV_READ);
}

void buff_error_cb(struct bufferevent *bev, short events, void *ctx)
{
	if (events & BEV_EVENT_CONNECTED) {
		//LOG(INFO) << "connect to server...";
		connected++;
//		std::string  rand_str = gen_rand_str(10000);
		std::string  rand_str = "1234567890";
		//LOG(INFO) << "genrandstr: " << rand_str;

		struct	evbuffer* evb = evbuffer_new();
		evbuffer_add_pdu(evb, (const void *)rand_str.c_str(), rand_str.size());
		bufferevent_write_buffer(bev, evb);
		evbuffer_free(evb);

		bufferevent_disable(bev, EV_READ);
		bufferevent_enable(bev, EV_WRITE);
		bufferevent_setcb(bev, buff_read_cb, buff_write_cb, buff_error_cb, NULL);
	} else if (events & (BEV_EVENT_EOF)) {
		//LOG(INFO) << "disconnected by peer";
		disconnected++;
		bufferevent_free(bev);
	} else if (events & BEV_EVENT_ERROR) {
		sockerror++;
		PLOG(ERROR) << "Error from bufferevent";
		bufferevent_free(bev);
	}

	if ((disconnected + sockerror) == conn_num ) {
		finishWork();
	}
}

void on_time_cb(evutil_socket_t fd, short what, void *arg)
{
	LOG(WARNING) << "client status: conneted["
		<< connected
		<< "] disconnected["
		<< disconnected
		<< "] sockerror["
		<< sockerror
		<< "]";
}


int main(int argc, char *argv[])
{
	if (argc < 3) {
		std::cout << "usage: ./a.out [thread_num] [ip]";
		return -1;
	}
	FLAGS_log_dir = "./log";
//	FLAGS_logtostderr=true;
	FLAGS_minloglevel = 1;
	google::InitGoogleLogging(argv[0]);

	struct event_base *base;
	struct bufferevent *bev;
	struct sockaddr_in sin;

	base = event_base_new();

	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	//sin.sin_addr.s_addr	= htonl(0x7f000001); /*127.0.0.1*/
	inet_pton(AF_INET, argv[2], &sin.sin_addr);
	sin.sin_port = htons(8888); /*Port 8888*/

	if (argc > 1) {
		conn_num = atoi(argv[1]);
		if (conn_num < -1) {
			conn_num = 1000;
		}
	}

	for (int i = 0; i < conn_num; i++) {

		bev	= bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);

		bufferevent_setcb(bev, NULL, NULL, buff_error_cb, NULL);

		if	(bufferevent_socket_connect(bev,
					(struct	sockaddr*)&sin,	sizeof(sin)) <	0)	{
			/*	Error	starting	connection	*/
			int err = EVUTIL_SOCKET_ERROR();
			LOG(ERROR) << "Got an error " << err << "(" << evutil_socket_error_to_string(err) << ") on connection";
			bufferevent_free(bev);
			return	-1;
		}
	}

	struct timeval one_sec = { 30, 0};
	struct event *evtm = NULL;
    evtm = event_new(base, -1, EV_PERSIST, on_time_cb, evtm);
	event_add(evtm, &one_sec);

	gettimeofday(&startTime, NULL);

	event_base_dispatch(base);
	return	0;
}
