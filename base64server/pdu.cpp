#include <zlib.h>
#include <event2/buffer.h>
#include "pdu.h"


bool valid_pdu_package(void* data, size_t length)
{
	if (length < (sizeof(struct pdu_header)+2)) {
		return false;
	}

	uint8_t pdu_start = *((uint8_t *)data);
	uint8_t pdu_end = *((uint8_t *)data+length-1);
	if (pdu_start != PDU_START || pdu_end != PDU_END) {
		return false;
	}

	struct pdu_header* ptr_header = (struct pdu_header*)((uint8_t *)data + 1);
	if (ptr_header->length != length) {
		return false;
	}

	uint8_t *pdu_body = ((uint8_t *)data + 1 + sizeof(struct pdu_header));
	uLong crc = crc32(0L, Z_NULL, 0);
	crc = crc32(crc, (const Bytef *)pdu_body, ptr_header->length - sizeof(struct pdu_header) - 2);
	if (crc != ptr_header->crc32) {
		return false;
	}

	return true;

}

void evbuffer_add_pdu(struct evbuffer *evb, const void *data, size_t length)
{
    struct pdu_header pdu_hd;
	uint8_t pdu_symbol = PDU_START;
	evbuffer_add(evb, (const void *)&pdu_symbol, sizeof(uint8_t));
	pdu_hd.length = 2 + sizeof(struct pdu_header) + length;
	uLong crc = crc32(0L, Z_NULL, 0);
	crc = crc32(crc, (const Bytef *)data, length);
	pdu_hd.crc32 = crc;
	evbuffer_add(evb, (const void*)&pdu_hd, sizeof(pdu_hd));
	evbuffer_add(evb, (const void*)data, length);
	pdu_symbol = PDU_END;
	evbuffer_add(evb, (const void *)&pdu_symbol, sizeof(uint8_t));

}
