#include "omp.h"
#include "iostream"
#include <stdio.h>
#include <ctime>



using namespace std;

const int NMAX = 1000000;


int main()

{
	setlocale(LC_ALL, "Russian");

	int i;


	srand(time(0));



	//Масиив динамичский, потому что иначе будет Stack Overflow


	int* A = new int[NMAX];
	for (int i = 0; i < NMAX; i++) {
		A[i] = 1 + rand() % 10;
	}

	int* B = new int[NMAX];
	for (int i = 0; i < NMAX; i++) {
		B[i] = 1 + rand() % 10;
	}

	int* C = new int[NMAX];
	int* C2 = new int[NMAX];




	double start2;
	double end2;
	int total = 0;

	start2 = omp_get_wtime();
	/*Начало параллельного фрагмента*/
#pragma omp for private(i, j) reduction(+:total)
#pragma omp sections
	{
#pragma omp section
		for (i = 0; i < NMAX / 2; i++)
		{
			if (A[i] > B[i])
				C[i] = A[i];
			else
				C[i] = B[i];
			total += C[i];
		}
#pragma omp section
		for (i = NMAX / 2; i < NMAX; i++)
		{
			if (A[i] > B[i])
				C[i] = A[i];
			else
				C[i] = B[i];
			total += C[i];
		}
	}
	/* Завершение параллельного фрагмента */

	end2 = omp_get_wtime();

	printf("Сумма элементов маccива равна %d\n", total);

	cout << "Время при делении на 2 потока " << end2 - start2 << endl;


	double start3;
	double end3;
	total = 0;

	start3 = omp_get_wtime();
	/*Начало параллельного фрагмента*/
#pragma omp for private(i, j) reduction(+:total)
#pragma omp sections
	{
#pragma omp section
		for (i = 0; i < NMAX / 3; i++)
		{
			if (A[i] > B[i])
				C[i] = A[i];
			else
				C[i] = B[i];
			total += C[i];
		}
#pragma omp section
		for (i = NMAX / 3; i < 2 * NMAX / 3; i++)
		{
			if (A[i] > B[i])
				C[i] = A[i];
			else
				C[i] = B[i];
			total += C[i];
		}
#pragma omp section
		for (i = 2 * NMAX / 3; i < NMAX; i++)
		{
			if (A[i] > B[i])
				C[i] = A[i];
			else
				C[i] = B[i];
			total += C[i];
		}
	}
	/* Завершение параллельного фрагмента */

	end3 = omp_get_wtime();

	printf("Сумма элементов маccива равна %d\n", total);

	cout << "Время при делении на 3 потока " << end3 - start3 << endl;


	double start4;
	double end4;
	total = 0;


	start4 = omp_get_wtime();
	/*Начало параллельного фрагмента*/
#pragma omp for private(i, j) reduction(+:total)
#pragma omp sections
	{
#pragma omp section
		for (i = 0; i < NMAX / 4; i++)
		{
			if (A[i] > B[i])
				C[i] = A[i];
			else
				C[i] = B[i];
			total += C[i];
		}
#pragma omp section
		for (i = NMAX / 4; i < NMAX / 2; i++)
		{
			if (A[i] > B[i])
				C[i] = A[i];
			else
				C[i] = B[i];
			total += C[i];
		}
#pragma omp section
		for (i = NMAX / 2; i < 3 * NMAX / 4; i++)
		{
			if (A[i] > B[i])
				C[i] = A[i];
			else
				C[i] = B[i];
			total += C[i];
		}
#pragma omp section
		for (i = 3 * NMAX / 4; i < NMAX; i++)
		{
			if (A[i] > B[i])
				C[i] = A[i];
			else
				C[i] = B[i];
			total += C[i];
		}
	}
	/* Завершение параллельного фрагмента */

	end4 = omp_get_wtime();

	printf("Сумма элементов маccива равна %d\n", total);

	cout << "Время при делении на 4 потока " << end4 - start4 << endl;


	double startPos;
	double endPos;
	int sum = 0;

	startPos = omp_get_wtime();

	for (i = 0; i < NMAX; i++)
	{
		if (A[i] > B[i])
			C2[i] = A[i];
		else
			C2[i] = B[i];
		sum += C2[i];
	}

	endPos = omp_get_wtime();


	printf("Сумма элементов маccива равна %d\n", sum);

	cout << "Время без параллельного использования вычислительных ресурсов " << endPos - startPos << endl;






}

