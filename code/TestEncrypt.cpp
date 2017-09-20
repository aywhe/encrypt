#include "encrypt\Encrypt.h"
#include <random>
#include <iostream>
#include <fstream>
using namespace std;
using namespace lz;
void PrintHelp()
{
	cout << "syntax: arrlen txtfile" << endl;
}
int main(int narg, char *argv[])
{
	if (narg < 3)
	{
		PrintHelp();
		return -1;
	}
	int len = atoi(argv[1]);
	if (len < 1) return -1;
	int *pArrOrg = new int[len];
	int *pArrEncrypt = new int[len];
	int *pArrDecrypt = new int[len];
	int lenMem = sizeof(int)*len;
	// random numbers
	for (int i = 0; i < len; i++)
	{
		pArrOrg[i] = rand();
	}
	// encryption
	memcpy_s(pArrEncrypt, lenMem, pArrOrg, lenMem);
	lzEncryptDisorder((void*)pArrEncrypt, lenMem, 0);
	memcpy_s(pArrDecrypt, lenMem, pArrEncrypt, lenMem);
	lzEncryptDisorder(pArrDecrypt, lenMem, 1);
	// write to file
	ofstream file;
	file.open(argv[2], ios::out|ios::trunc);
	for (int i = 0; i < len; i++)
	{
		file << right;
		file<< pArrOrg[i] << " " << pArrEncrypt[i] << " " << pArrDecrypt[i] << endl;
		//cout << pArrOrg[i] << " " << pArrEncrypt[i] << " " << pArrDecrypt[i] << endl;
	}
	file.close();
	// delete
	delete[] pArrDecrypt;
	delete[] pArrEncrypt;
	delete[] pArrOrg;
}