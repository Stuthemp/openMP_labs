﻿#include "omp.h"
#include "iostream"
#include <stdio.h>
#include <ctime>



using namespace std;

const int NMAX = 100000000;

const int MMAX = 10;

int main()

{
	setlocale(LC_ALL, "Russian");

	int i, j;


	srand(time(0));

	//Переменные для расчета времени
	double start;
	double end;

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



	start = omp_get_wtime();

	/*Начало параллельного фрагмента*/

	int total = 0;
#pragma omp parallel shared(C,B,A,total) 
	{
#pragma omp for private(i, j)
		for (i = 0; i < NMAX; i++)
		{
			if (A[i] > B[i])
				C[i] = A[i];
			else
				C[i] = B[i];
		#pragma omp atomic
			total += C[i];
		}
	}

	/* Завершение параллельного фрагмента */

	end = omp_get_wtime();


	printf("Сумма элементов маccива равна %d\n", total);

	cout << "Время при параллельном использовании atomic " << end - start << endl;

	start = omp_get_wtime();

	/*Начало параллельного фрагмента*/

	total = 0;
#pragma omp parallel shared(C,B,A,total) 
	{
#pragma omp for private(i, j)
		for (i = 0; i < NMAX; i++)
		{
			if (A[i] > B[i])
				C[i] = A[i];
			else
				C[i] = B[i];
		#pragma omp critical
			total += C[i];
		}
	}

	/* Завершение параллельного фрагмента */

	end = omp_get_wtime();



	printf("Сумма элементов маccива равна %d\n", total);

	cout << "Время при параллельном использовании critical " << end - start << endl;

	start = omp_get_wtime();

	/*Начало параллельного фрагмента*/

	total = 0;
#pragma omp parallel shared(C,B,A) 
	{
#pragma omp for private(i, j) reduction(+:total)
		for (i = 0; i < NMAX; i++)
		{
			if (A[i] > B[i])
				C[i] = A[i];
			else
				C[i] = B[i];
			total = total + C[i];
		}
	}

	/* Завершение параллельного фрагмента */

	end = omp_get_wtime();


	printf("Сумма элементов маccива равна %d\n", total);

	cout << "Время при параллельном использовании reduction " << end - start << endl;

	
	double start2;
	double end2;
	int sum = 0;

	start2 = omp_get_wtime();

	for (i = 0; i < NMAX; i++)
	{
		if (A[i] > B[i])
			C2[i] = A[i];
		else
			C2[i] = B[i];
		sum += C2[i];
	}

	end2 = omp_get_wtime();


	printf("Сумма элементов маccива равна %d\n", sum);

	cout << "Время без параллельного использования вычислительных ресурсов " << end2 - start2 << endl;
	

	//cout << endl << sum << endl;





}

