#pragma once
#include <stdlib.h>
namespace lz
{
#define DEF_LZ_ENCRYPT_PRIME_N 421 // prime number for encrypt
#define DEF_LZ_ENCRYPT_MALLOC(n) malloc(n) // new memory
#define DEF_LZ_ENCRYPT_FREE(p) free(p) // delete memory
	void lzEncryptDisorder(void *pMem, int len, int mode_forward_backward); // disorder the datas in pMem
	void lzEncryptDisorderTable(int *pArrTable[2], int len, int prime);
}
