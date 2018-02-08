// саод сорт.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <ctime>
#include <time.h> 
#include <math.h>
#include <memory>
#if defined(ETYPE_UNSIGNED_INT)
#include "uicomp.h"
#elif defined(ETYPE_SIGNED_INT)
#include "sicomp.h"
#elif defined(ETYPE_UNSIGNED_LONG)
#include "ulcomp.h"
#endif 
#define PRELUDE
#define KEYSIZE (8)
#define COST 4


#define LeftChild( i )  ( 2 * ( i ) + 1 )

const unsigned long LargeCutoff = 200000;
const unsigned long SmallCutoff = 20;

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

int             GT(int & a, int & b)
{
	return a > b;
}

int             LT(int & a, int & b)
{
	return a < b;
}


int             LE(int & a, int & b)
{
	return a <= b;
}


int             EQ(int & a, int & b)
{
	return a == b;
}

void            SWAP(int & a, int & b)
{
	int         tmp = a;
	a = b;
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
	int             i;

	for (i = N / 2; i >= 0; i--)
		/* BuildHeap */
		PERCDOWN(A, i, N);
	for (i = N - 1; i > 0; i--) {
		SWAP(A[0], A[i]);
		/* DeleteMax */
		PERCDOWN(A, 0, i);
	}
}

void generation(int *A, int n)
{
	for (int i = 0; i < n; i++)
	{
		A[i] = 1 * rand() ;
	//	num1[i] = A[i];
	}

}

//void            INSERTTWO(int array[])
//{
//	if (GT(array[0], array[1]))
//		SWAP(array[0], array[1]);
//	return;
//}
//
//
//void            INSERTTHREE(int array[])
//{
//	if (LT(array[0], array[1])) {
//		if (LT(array[1], array[2]))
//			return;
//		else if (LT(array[0], array[2]))
//			SWAP(array[1], array[2]);
//		else {
//			int           Tmp = array[0];
//			array[0] = array[2];
//			array[2] = array[1];
//			array[1] = Tmp;
//		}
//	}
//	else {
//		if (LT(array[0], array[2]))
//			SWAP(array[0], array[1]);
//		else if (LT(array[1], array[2])) {
//			int         Tmp = array[0];
//			array[0] = array[1];
//			array[1] = array[2];
//			array[2] = Tmp;
//		}
//		else
//			SWAP(array[0], array[2]);
//	}
//	return;
//}
//
//
//void            INSERTFOUR(int array[])
//{
//	int          temp;
//	if (GT(array[0], array[1])) {
//		temp = array[0];
//		array[0] = array[1];
//		array[1] = temp;
//	}
//	if (GT(array[2], array[3])) {
//		temp = array[2];
//		array[2] = array[3];
//		array[3] = temp;
//	}
//	if (GT(array[1], array[2])) {
//		if (GT(array[0], array[3])) {
//			temp = array[0];
//			array[0] = array[2];
//			array[2] = temp;
//			temp = array[1];
//			array[1] = array[3];
//			array[3] = temp;
//		}
//		else {
//			temp = array[1];
//			array[1] = array[2];
//			array[2] = temp;
//			if (GT(array[0], array[1])) {
//				temp = array[0];
//				array[0] = array[1];
//				array[1] = temp;
//			}
//			if (GT(array[2], array[3])) {
//				temp = array[2];
//				array[2] = array[3];
//				array[3] = temp;
//			}
//		}
//	}
//}

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
	size_t          m;          
	if (l < r) {               
								
		m = ((l + r) >> 1);
		MSORT(A, B, l, m);
		MSORT(A, B, m + 1, r);
		MMERGE(A, B, l, m, r);  
	}
}

//long            ARRAYISREVERSED(int A[], unsigned long Lo, unsigned long Hi)
//{
//	unsigned long   i;
//	for (i = Lo; i < Hi; i++) {
//		if (LE(A[i], A[i + 1]))
//			return 0;
//	}
//	return 1;
//}
//
//
//void            REVERSEARRAY(int * A, unsigned long Lo, unsigned long Hi)
//{
//	int         *r = A + Lo;
//	for (r = A + (Hi - Lo); A < r; A++, r--) {
//		int          Tmp = *A;
//		*A = *r;
//		*r = Tmp;
//	}
//}
//
//long            ARRAYISSORTED(int A[], unsigned long Lo, unsigned long Hi)
//{
//	unsigned long   i;
//	unsigned int    ascending;
//	if (Lo == Hi)
//		return 1;
//	if ((ascending = (LE(A[Lo], A[Lo + 1]))))
//		for (i = Lo + 1; i < Hi; i++) {
//		
//			if (GT(A[i], A[i + 1])) {
//			
//				if (EQ(A[i], A[Lo]))
//				
//					if (ARRAYISREVERSED(A, i, Hi)) {
//				
//						REVERSEARRAY(A, Lo, Hi);
//						return 1;
//					}
//					else {   
//						return 0;
//					}
//				else
//					return 0;
//			}
//		}
//
//	else if (ARRAYISREVERSED(A, Lo, Hi)) {
//	
//		REVERSEARRAY(A, Lo, Hi);
//		return 1;
//	}
//	else
//		return 0;
//	return 1;
//}
//
//void            SHELLSORT(int array[], size_t count)
//{
//	size_t          i,
//		inc,
//		j;
//	int           tmp;
//
//	switch (count) {
//	case 0:
//	case 1:
//		return;
//	case 2:
//		INSERTTWO(array);
//		return;
//	case 3:
//		INSERTTHREE(array);
//		return;
//	case 4:
//		INSERTFOUR(array);
//		return;
//#ifdef MY_CACHE_IS_ENORMOUS
//	case 5:
//		InsertFive(array);
//		return;
//#endif
//
//	default:
//
//		for (inc = count; inc > 0;) {
//			for (i = inc; i < count; i++) {
//				j = i;
//				tmp = array[i];
//				while (j >= inc && (LT(tmp, array[j - inc]))) {
//					array[j] = array[j - inc];
//					j -= inc;
//				}
//				array[j] = tmp;
//			}                   /* Calculate the next h-increment */
//			inc = (size_t)((inc > 1) && (inc < 5)) ? 1 : 5 * inc / 11;
//		}
//	}
//}
//
//
//void            MEDIAN(int A[], unsigned long n)
//{
//	unsigned long   m,
//		x,
//		i, 
//		j,
//		k;
//	int           t;
//	i = (rand() + 1) % n;     /* We randomly stir the pot up a bit... */
//	j = (rand() + 1) % n;     /* We randomly stir the pot up a bit... */
//	k = n / 2;                  /* The middle element of a partition is a
//								* good guess */
//								/* Pick the center of these three */
//	if (LE(A[i], A[j])) {
//		if (LE(A[j], A[k])) {
//			m = j;
//			x = k;
//		}
//		else if (LE(A[i], A[k])) {
//			m = k;
//			x = j;
//		}
//		else {
//			m = i;
//			x = j;
//		}
//	}
//	else {
//		if (LE(A[i], A[k])) {
//			m = i;
//			x = k;
//		}
//		else if (LE(A[j], A[k])) {
//			m = k;
//			x = i;
//		}
//		else {
//			m = j;
//			x = i;
//		}
//	}
//	/* Store out of the way... */
//	t = A[0];
//	A[0] = A[m];
//	A[m] = t;
//	t = A[n - 1];
//	A[n - 1] = A[x];
//	A[x] = t;
//}
//
//void            IQSORT5(int A[], unsigned long n)
//{
//	unsigned long   i,
//		j;
//	int          t;
//
//	if (n < SmallCutoff) {
//		SHELLSORT(A, n);
//		return;
//	}
//
//	if (ARRAYISSORTED(A, 0, n - 1))
//		return;
//	MEDIAN(A, n);
//
//	i = 0;
//	j = n;
//	for (;;) {
//		do
//			i++;
//		while (LT(A[i], A[0]) && i < n);
//		do
//			j--;
//		while (GT(A[j], A[0]) && j > 0);
//		if (j < i)
//			break;
//		t = A[i];
//		A[i] = A[j];
//		A[j] = t;
//	}
//
//	t = A[0];
//	A[0] = A[j];
//	A[j] = t;
//
//	if (j < n - j) {
//		IQSORT5(A, j);
//		IQSORT5(A + j + 1, n - j - 1);
//	}
//	else {
//		IQSORT5(A + j + 1, n - j - 1);
//		IQSORT5(A, j);
//	}
//}
//
//
//void            RADIXMSD(int a[], long l, long r, unsigned w)
//{
//	if (w > KEYSIZE || r <= l)
//		return;
//	if (r - l <= LargeCutoff * COST) {
//		IQSORT5(a + l, r - l + 1);
//		return;
//	}
//	else {
//		long   i, j, 
//			count[r + 1] = { 0 };
//		int       *b = malloc((r - l + 1) * sizeof(int));
//
//		/* Use standard comparison sort if allocation fails */
//		if (b == NULL) {
//			IQSORT5(a + l, r - l + 1);
//			return;
//		}
//		/* increment the starting place for the next bin */
//		for (i = l; i <= r; i++) {
//			count[CHUNK(a + i, w) + 1]++;
//		}
//
//		/* Add the previous bin counts to find true offset */
//		for (j = 1; j < R; j++)
//			count[j] += count[j - 1];
//
//		/* Distribute according to bin positions */
//		for (i = l; i <= r; i++) {
//			b[count[CHUNK(a + i, w)]++] = a[i];
//		}
//		/* Transfer back to the original array */
//		for (i = l; i <= r; i++)
//			a[i] = b[i - l];
//		free(b);
//
//		/* Process the next chunk of the key for the first bin */
//		RADIXMSD(a, l, bin(0) - 1, w + 1);
//		for (j = 0; j < R - 1; j++) {
//			/* Process the next chunk of the key for the rest of the  bins */
//			RADIXMSD(a, bin(j), bin(j + 1) - 1, w + 1);
//		}
//
//	}
//}
//
//void RADIXLSD(int a[], long l, long r, size_t keysize)
//{
//	int    i,j,	w;
//	int    *b;
//
//	if (r - l <= LargeCutoff * COST) {
//		IQSORT5(a + l, r - l + 1);
//		return;
//	}
//	
//	if (KEYSIZE > 8) {
//		RADIXMSD(a, l, r, 0);
//		return;
//	}
//	else {
//		unsigned long   cnts[R + 1][8] = { 0 };
//		b = malloc((r - l + 1) * sizeof(int));
//
//		
//		if (b == NULL) {
//			IQSORT5(a + l, r - l + 1);
//			return;
//		}
//	
//		for (i = l; i <= r; i++)
//			CHUNKS(a + i, cnts);
//		for (w = KEYSIZE - 1; w >= 0; w--)
//			
//			for (j = 1; j < R; j++)
//				cnts[j][w] += cnts[j - 1][w];
//
//
//		for (w = KEYSIZE - 1; w >= 0; w--) {
//			long            count[R + 1] =
//			{ 0 };
//
//			for (i = l; i <= r; i++) {
//				b[cnts[CHUNK(&a[i], w)][w]++] = a[i];
//			}
//			
//			for (i = l; i <= r; i++)
//				a[i] = b[i];
//		}
//		free(b);
//	}
//}

//void radix(int *num1, int *br, int *cr, int n)
//{
//	int i, k, l;
//	k = 10;
//	l = n;
//	for (i = 0; i <= k; i++)
//		cr[i] = 0;
//	for (i = 0; i < l; i++)
//		cr[num1[i]] += 1;
//	for (i = 1; i < k + 1; i++)
//		cr[i] += cr[i - 1];
//	for (i = n - 1; i >= 0; i--)
//	{
//		br[cr[num1[i]] - 1] = num1[i];
//		cr[num1[i]] -= 1;
//	}
//}


int main()
{
	setlocale(LC_ALL, "Russian");
	//time_t start, end;
	int A[10], B[10];
	int n, *num, *num1, *br, *cr;
	int l, r;
	//cr = new int[10];
	srand(time(NULL));
	cout << "Введите количество элементов: ";
	cin >> n;
	l = 0; r = n - 1;
	num = new int[n]; 
	num1 = new int[n];
	br = new int[n];
	cr = new int[10];
	generation(A,n);

	/*radix(num1,br,cr,n);
	for (int i = 0; i < 10; i++)
		cout << "\nПоразрядная сортировка\n" << br[i] << " ";
	cout << "\n";*/

	MSORT(A, B, l, r);
	cout << "\nСортировка слиянием\n";
	for (int i = 0; i < 10; i++)
		cout <<A[i] << "\n";
//	double seconds = difftime(end, start);
	//printf("The time: %f seconds\n", seconds);

//	time(&start);
	generation(A, n);
	HEAPSORT(A,n);
	cout << "\nПирамидная сортировка\n";
	for (int i = 0; i < 10; i++)
		cout << A[i] << "\n";

	system("pause");
	return 0;
}

