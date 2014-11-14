#ifndef BASE64_H
#define BASE64_H

int base64encode(const void* data_buf, int dataLength, char* result, int resultSize);
int base64decode (char *in, int inLen, INT8U *out, int *outLen);

#endif
