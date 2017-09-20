#include "encrypt\Encrypt.h"
#include "string.h"
/*
author: lz
function: disorder datas in pMem
input:
	pMem: datas
	len: data size
	mode: 0 forward and 1 backward
output:
	void
date: 20160409
*/
void lz::lzEncryptDisorder(void * pMem, int len, int mode_forward_backward)
{
	if (!pMem || len < DEF_LZ_ENCRYPT_PRIME_N)
	{
		return;
	}
	// disorder table
	int *pArrDisorderTable[2];
	for (int i = 0; i < 2; i++)
	{
		pArrDisorderTable[i] = (int *)DEF_LZ_ENCRYPT_MALLOC(sizeof(int)*len);
	}
	lzEncryptDisorderTable(pArrDisorderTable, len, DEF_LZ_ENCRYPT_PRIME_N);
	// temporary memory
	void *pMemTemp = DEF_LZ_ENCRYPT_MALLOC(len);
	if (!pMemTemp)
	{
		return;
	}
	memcpy_s(pMemTemp, len, pMem, len);
	// table map
	int iTableActIdx = 0 == mode_forward_backward ? 0 : 1;
	int *pArrDisorderActTable = pArrDisorderTable[iTableActIdx];
	char *pMemT = (char *)pMem;
	char *pMemTp = (char *)pMemTemp;
	for (int i = 0; i < len; i++)
	{
		pMemT[i] = pMemTp[pArrDisorderActTable[i]];
	}
	// free memory
	DEF_LZ_ENCRYPT_FREE(pMemTemp);
	for (int i = 0; i < 2; i++)
	{
		if (pArrDisorderTable[i])
		{
			DEF_LZ_ENCRYPT_FREE(pArrDisorderTable[i]);
		}
	}
}
/*
author: lz
function: construct disorder table
input:
	pArrTable: 2 elements points to disorder table as size "len",
		include forward and backward table
	len: length of table
output:
	void
date: 20160409
*/
void lz::lzEncryptDisorderTable(int * pArrTable[2], int len, int prime)
{
	if (len < 0 || prime > len || !pArrTable[0] || !pArrTable[1])
	{
		return;
	}
	for (int j = 0; j < 2; j++)
	{
		for (int i = 0; i < len; i++)
		{
			pArrTable[j][i] = i;
		}
	}
	// calculate the forward map
	int iGroup = len / prime; // how many groups of prime size
	int idx = 0,idx2;
	for (int i = 0; i < prime; i++)
	{
		for (int j = 0; j < iGroup; j++)
		{
			idx2 = j*prime + i;
			pArrTable[0][idx++] = pArrTable[1][idx2];
		}
	}
	// reverse map
	for (int i = 0; i < len; i++)
	{
		pArrTable[1][pArrTable[0][i]] = i;
	}
}
