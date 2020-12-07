#define _CRT_SECURE_NO_WARNINGS

#include "omp.h"
#include "iostream"
#include <stdio.h>
#include <ctime>



using namespace std;

int critical(int* a, int* b, int* c, int NMAX);
int atom(int* a, int* b, int* c, int NMAX);
int consistently(int* a, int* b, int* c, int NMAX);

const int NMAX = 10000000;


int main()

{
	setlocale(LC_ALL, "russian");

	int NMAX;

	printf("Введите: NMAX ");

	scanf("%d", &NMAX);


	double start1, end1;

	double start2, end2;

	double start3, end3;

	long total = 0;

	int* A = new int[NMAX];

	int* B = new int[NMAX];

	int* C = new int[NMAX];

	for (int i = 0; i < NMAX; i++) {

		A[i] = (i - 15) % 1000 + 150;

		B[i] = (i + 7) % 1500 - 26;

	}



	start1 = omp_get_wtime();

	total = atom(A, B, C, NMAX);

	end1 = omp_get_wtime();


	printf("Сумма элементов матрицы равна %ld\n", total);

	start2 = omp_get_wtime();

	total = critical(A, B, C, NMAX);

	end2 = omp_get_wtime();


	printf("Сумма элементов матрицы равна %ld\n", total);

	start3 = omp_get_wtime();

	total = consistently(A, B, C, NMAX);

	end3 = omp_get_wtime();

	printf("Сумма элементов матрицы равна %ld\n", total);

	printf("Время для atomic: %f\n", end1 - start1);

	printf("Время для critical: %f\n", end2 - start2);

	printf("Время для последовательного вычисления: %f\n", end3 - start3);

	delete[] A;
	delete[] B;
	delete[] C;

	return 0;

}

int atom(int* a, int* b, int* c, int NMAX) {

	int total = 0;
	int i;
#pragma omp parallel shared(a,b,c,total) 
	{
#pragma omp for private(i)
		for (i = 0; i < NMAX; i++)
		{
			if (a[i] > b[i])
				c[i] = a[i];
			else
				c[i] = b[i];
#pragma omp atomic
			total += c[i];
		}
	}

	return total;
}

int critical(int* a, int* b, int* c, int NMAX) {
	int total = 0;
	int i = 0;
#pragma omp parallel shared(c,b,a,total) 
	{
#pragma omp for private(i)
		for (i = 0; i < NMAX; i++)
		{
			if (a[i] > b[i])
				c[i] = a[i];
			else
				c[i] = b[i];
#pragma omp critical
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
