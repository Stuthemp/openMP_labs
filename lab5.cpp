#define _CRT_SECURE_NO_WARNINGS

#include "omp.h"
#include "iostream"
#include <stdio.h>
#include <ctime>



using namespace std;

int twoThreads(int* a, int* b, int* c, int NMAX);
int threeThreads(int* a, int* b, int* c, int NMAX);
int fourThreads(int* a, int* b, int* c, int NMAX);
int consistently(int* a, int* b, int* c, int NMAX);

int main()

{
	setlocale(LC_ALL, "russian");

	int NMAX;

	printf("Введите: NMAX ");

	scanf("%d", &NMAX);


	double start1, end1;

	double start2, end2;

	double start3, end3;

	double start4, end4;

	long total = 0;

	int* A = new int[NMAX];

	int* B = new int[NMAX];

	int* C = new int[NMAX];

	for (int i = 0; i < NMAX; i++) {

		A[i] = (i - 15) % 1000 + 150;

		B[i] = (i + 7) % 1500 - 26;

	}



	start1 = omp_get_wtime();

	total = twoThreads(A, B, C, NMAX);

	end1 = omp_get_wtime();


	printf("Сумма элементов матрицы равна %ld\n", total);

	start2 = omp_get_wtime();

	total = threeThreads(A, B, C, NMAX);

	end2 = omp_get_wtime();


	printf("Сумма элементов матрицы равна %ld\n", total);

	start3 = omp_get_wtime();

	total = fourThreads(A, B, C, NMAX);

	end3 = omp_get_wtime();

	printf("Сумма элементов матрицы равна %ld\n", total);

	start4 = omp_get_wtime();

	total = consistently(A, B, C, NMAX);

	end4 = omp_get_wtime();

	printf("Сумма элементов матрицы равна %ld\n", total);

	printf("Время для 2-х тредов: %f\n", end1 - start1);

	printf("Время для 3-х тредов: %f\n", end2 - start2);

	printf("Время для 4-х тредов: %f\n", end3 - start3);

	printf("Время для последовательного вычисления: %f\n", end4 - start4);

	delete[] A;
	delete[] B;
	delete[] C;

	return 0;
}

int twoThreads(int* a, int* b, int* c, int NMAX) {
	int total = 0;
	int i;

#pragma omp parallel private(i) reduction(+:total)
#pragma omp sections
	{
#pragma omp section
		for (i = 0; i < NMAX / 2; i++)
		{
			if (a[i] > b[i])
				c[i] = a[i];
			else
				c[i] = b[i];
			total += c[i];
		}
#pragma omp section
		for (i = NMAX / 2; i < NMAX; i++)
		{
			if (a[i] > b[i])
				c[i] = a[i];
			else
				c[i] = b[i];
			total += c[i];
		}
	}
	
	return total;
}

int threeThreads(int* a, int* b, int* c, int NMAX) {
	int total = 0;
	int i;

#pragma omp parallel private(i) reduction(+:total)
#pragma omp sections
	{
#pragma omp section
		for (i = 0; i < NMAX / 3; i++)
		{
			if (a[i] > b[i])
				c[i] = a[i];
			else
				c[i] = b[i];
			total += c[i];
		}
#pragma omp section
		for (i = NMAX / 3; i < 2 * NMAX / 3; i++)
		{
			if (a[i] > b[i])
				c[i] = a[i];
			else
				c[i] = b[i];
			total += c[i];
		}
#pragma omp section
		for (i = 2 * NMAX / 3; i < NMAX; i++)
		{
			if (a[i] > b[i])
				c[i] = a[i];
			else
				c[i] = b[i];
			total += c[i];
		}
	}
	return total;
}

int fourThreads(int* a, int* b, int* c, int NMAX) {
	int total = 0;
	int i;

#pragma omp parallel private(i) reduction(+:total)
#pragma omp sections
	{
#pragma omp section
		for (i = 0; i < NMAX / 4; i++)
		{
			if (a[i] > b[i])
				c[i] = a[i];
			else
				c[i] = b[i];
			total += c[i];
		}
#pragma omp section
		for (i = NMAX / 4; i < NMAX / 2; i++)
		{
			if (a[i] > b[i])
				c[i] = a[i];
			else
				c[i] = b[i];
			total += c[i];
		}
#pragma omp section
		for (i = NMAX / 2; i < 3 * NMAX / 4; i++)
		{
			if (a[i] > b[i])
				c[i] = a[i];
			else
				c[i] = b[i];
			total += c[i];
		}
#pragma omp section
		for (i = 3 * NMAX / 4; i < NMAX; i++)
		{
			if (a[i] > b[i])
				c[i] = a[i];
			else
				c[i] = b[i];
			total += c[i];
		}
	}
	return total;
}

int consistently(int* a, int* b, int* c, int NMAX) {
	int total = 0;
	int i;

	for (i = 0; i < NMAX; i++)

	{
		if (a[i] > b[i])
			c[i] = a[i];
		else
			c[i] = b[i];
		total += c[i];
	}
	return total;
}

