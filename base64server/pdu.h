
#ifndef PDU_COMMON_H
#define PDU_COMMON_H

#include <event2/buffer.h>

#define PDU_START 0x04
#define PDU_END 0x05

#pragma pack(1)
struct pdu_header {
	uint32_t length;
	uint32_t crc32;
};
#pragma pack()

bool valid_pdu_package(void* data, size_t length);
void evbuffer_add_pdu(struct evbuffer *evb, const void *data, size_t length);

#endif
