#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <time.h> 
#include <math.h>
#include <memory>
#define LeftChild( i )  ( 2 * ( i ) + 1 ) 
const unsigned long LargeCutoff = 200000;
const unsigned long SmallCutoff = 10;


using namespace std;

void selection(int *num, int n)
{
	int i, j, mx, nmx;

	for (i = 0; i < n - 1; i++)
	{
		mx = num[i];
		nmx = i;
		for (j = i + 1; j < n; j++)
		{
			if (num[j]<mx)
			{
				mx = num[j];
				nmx = j;
			}
		}
		num[nmx] = num[i];
		num[i] = mx;
	}
}

int             GT(int & A, int & b)
{
	return A> b;
}

int             LT(int & A, int & b)
{
	return A < b;
}

void            SWAP(int *A, int *b)
{
	int tmp = *A;
	*A = *b;
	*b = tmp;
}
void            swap(int &A, int &b)
{
	int tmp = A;
	A = b;
	b = tmp;
}

void            PERCDOWN(int A[], int i, int N)
{
	int             Child;
	int          Tmp;

	for (Tmp = A[i]; LeftChild(i) < N; i = Child) {
		Child = LeftChild(i);
		if (Child != N - 1 && GT(A[Child + 1], A[Child]))
			Child++;
		if (LT(Tmp, A[Child]))
			A[i] = A[Child];
		else
			break;
	}
	A[i] = Tmp;
}

void  HEAPSORT(int A[], int N)
{

	int i;
	for (i = N / 2; i >= 0; i--)
		/* BuildHeap */
	{
		PERCDOWN(A, i, N);
		for (i = N - 1; i > 0; i--) {
			swap(A[0], A[i]);
			/* DeleteMax */
			PERCDOWN(A, 0, i);
		}
	}
	
}

void            MMERGE(int A[], int B[], size_t l, size_t m, size_t r)
{
	size_t          i = l;
	size_t          j = m + 1;
	size_t          k = l;
	/* Put the smallest thing into array B */
	while ((i <= m) && (j <= r)) {
		if (LT(A[i], A[j]))
			B[k++] = A[i++];
		else
			B[k++] = A[j++];
	}
	/* Copy leftover (if any) */
	while (i <= m) {
		B[k++] = A[i++];
	}
	while (j <= r) {
		B[k++] = A[j++];
	}
	/* Transfer back to original array */
	for (k = l; k <= r; k++) {
		A[k] = B[k];
	}
}


void            MSORT(int A[], int B[], size_t l, size_t r)
{
	
	size_t  m;
	if (l < r) {

		m = ((l + r) >> 1);
		MSORT(A, B, l, m);
		MSORT(A, B, m + 1, r);
		MMERGE(A, B, l, m, r);
	}
	
}
void generation(int *A, int n)
{
	for (int i = 0; i < n; i++)
	{
		A[i] = 0 + rand()%11;
		//	num1[i] = A[i];
	}

}
int correct(int *A, int size)
{
	while (--size > 0)
		if (A[size - 1] > A[size])
			return 0;
	return 1;
}
void shuffle(int *A, int size)
{
	int i;
	for (i = 0; i < size; i++)
		SWAP(A + i, A + (rand() % size));
}
void bogoSort(int *A, int size)
{
	
	while (!correct(A, size))
	shuffle(A, size);
}
int main()
{
	setlocale(LC_ALL, "Russian");
//	time_t start, end;
	int A[10], B[10];
	int size = 10;
	int n, *num, *num1, *br, *cr;
	int l, r;
	//cr = new int[10];
	srand(time(NULL));
	cout << "Введите количество элементов: ";
	cin >> n;
	l = 0; r = n - 1;
	num = new int[n];

	generation(A, n);

	clock_t start = clock();
	bogoSort(A, n);
	cout << "\nСортировка bogosort \n";
	for (int i = 0; i < 10; i++)
		cout << A[i] << "\n";
	clock_t end = clock();
	double seconds = (double)(end - start) / CLOCKS_PER_SEC;
	printf("The time: %f seconds\n", seconds);

	generation(A, n);
	
	MSORT(A, B, l, r);
	cout << "\nСортировка слиянием\n";
	for (int i = 0; i < 10; i++)
		cout << A[i] << "\n";

	
	generation(A, n);
	
	HEAPSORT(A, n);
	cout << "\nПирамидная сортировка\n";
	for (int i = 0; i < 10; i++)
		cout << A[i] << "\n";

	system("pause");
	return 0;
}
