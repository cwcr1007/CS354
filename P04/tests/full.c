#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "mem.h"

int main() {
	assert(Mem_Init(4096, FIRST_FIT) == 0);
	void *ptr[3];

	ptr[0] = Mem_Alloc(1768);
	assert(ptr[0] != NULL);
	ptr[0] = memset(ptr[0], 0xff, 1768);

	ptr[1] = Mem_Alloc(880);
	assert(ptr[1] != NULL);
	ptr[1] = memset(ptr[1], 0xff, 880);

	ptr[2] = Mem_Alloc(1416);
	assert(ptr[2] != NULL);
	ptr[2] = memset(ptr[2], 0xff, 1416);

	assert(Mem_Free(ptr[0]) == 0);
	assert(Mem_Free(ptr[2]) == 0);
	assert(Mem_Free(ptr[1]) == 0);

	ptr[0] = Mem_Alloc(4080);
	assert(ptr[0] != NULL);

	return 0;
}
