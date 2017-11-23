// CacheEffect.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <time.h>
#include <string>
#include "CacheEffect.h"

using namespace std;

int** setArray(int n) {
	int **arr = new int *[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			arr[i][j] = rand(); // Случайное число
		}
	}

	return arr;
}

int** setClearArray(int n) {
	int **arr = new int *[n];
	for (int i = 0; i < n; i++)
	{
		arr[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			arr[i][j] = 0; 
		}
	}

	return arr;
}

void multiplyTwoArrays(int **A, int **B, int **C, int n) {

	double s;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			C[i][j] = 0;

			for(int k = 0; k < n; k ++)
			{
				C[i][j] += A[i][k] * B[k][j];
			}
			
		}
	}
}


void bijk(int **A, int **B, int **C, int n, int bsize) {
	int i, j, k, kk, jj;
	double sum;
	int en = bsize * (n / bsize);

	for (kk = 0; kk < en; kk += bsize)
	{
		for (jj = 0; jj < en; jj += bsize)
		{
			for (i = 0; i < n; i++)
			{
				for (j = jj; j < jj + bsize; j++)
				{
					sum = C[i][j];
					for (k = kk; k < kk + bsize; k++)
					{
						sum += A[i][k] * B[k][j];
					}
					
					C[i][j] = sum;
				}
			}
		}
	}
}

void clearMemory(int **A, int n) {
	for (size_t i = 0; i < n; ++i)
	{
		delete[] A[i];
	}

	delete A;
}

void startTraditionalMultiply(int n) {

	clock_t start1, stop1;

	start1 = clock();

	int **aArr1 = setArray(n);
	int **bArr1 = setArray(n);
	int **cArr1 = setClearArray(n);

	multiplyTwoArrays(aArr1, bArr1, cArr1, n);

	stop1 = clock();

	cout << "Time >> "<< (stop1 - start1) << endl;

	clearMemory(aArr1, n);
	clearMemory(bArr1, n);
	clearMemory(cArr1, n);
}

void startBlockMultiply(int blockSize, int n) {
	clock_t start2, stop2;

	start2 = clock();
	int **aArr2 = setArray(n);
	int **bArr2 = setArray(n);
	int **cArr2 = setClearArray(n);
	bijk(aArr2, bArr2, cArr2, n, blockSize);
	stop2 = clock();

	cout << "Block size >> " << blockSize << " " << (stop2 - start2) << " << Time" << endl;

	clearMemory(aArr2, n);
	clearMemory(bArr2, n);
	clearMemory(cArr2, n);
}



int main()
{
	srand(time(NULL));

	int firstLength = 500;
	int secondLength = 1000;
	int thirdLength = 2000;

	/// traditional

	cout << "Classic multiply. Size = " << firstLength << endl;
	startTraditionalMultiply(firstLength);
	cout << endl << endl;

	cout << "Classic multiply. Size = " << secondLength << endl;
	startTraditionalMultiply(secondLength);
	cout << endl << endl;

	cout << "Classic multiply. Size = " << thirdLength << endl;
	startTraditionalMultiply(thirdLength);
	cout << endl << endl;

	/// block 

	int blockSizes[6] = {5, 10, 25, 50, 75, 100};

	cout << "Block algorithm. Size = " << firstLength << endl;
	for each (int blockSize in blockSizes)
	{		
		startBlockMultiply(blockSize, firstLength);
	}

	cout << endl << endl;

	cout << "Block algorithm. Size = " << secondLength << endl;
	for each (int blockSize in blockSizes)
	{		
		startBlockMultiply(blockSize, secondLength);
	}

	cout << endl << endl;

	cout << "Block algorithm. Size = " << thirdLength << endl;
	for each (int blockSize in blockSizes)
	{		
		startBlockMultiply(blockSize, thirdLength);
	}

	cout << endl << endl;

	getchar();
	return 0;
}

