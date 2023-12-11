#include <stdio.h>
#include "libbuf.h"

int main() {
	float *buffer = 0;

	buf_push(buffer, 12.3f);
	printf("%f", *buffer);
	buf_free(buffer);

	return 0;
}