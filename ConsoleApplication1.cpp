#include "omp.h"
#include "iostream"
#include <stdio.h>



using namespace std;

const int NMAX = 50;

const int LIMIT = 1;

void main()

{
	setlocale(LC_ALL, "Russian");

	int i, j;

	float sum;

	//Переменные для расчета времени
	double start; 
	double end;

	//Масиив динамичский, потому что иначе будет Stack Overflow
	int** a = new int* [NMAX];

	for (i = 0; i < NMAX; i++)

		a[i] = new int[NMAX];

	start = omp_get_wtime();

	/*Начало параллельного фрагмента*/

#pragma omp parallel shared(a) if (NMAX>LIMIT)

	{

#pragma omp for private(i,j)

		for (i = 0; i < NMAX; i++)

			for (j = 0; j < NMAX; j++)

				a[i][j] = i + j;

#pragma omp for private(i,j,sum)

		for (i = 0; i < NMAX; i++)

		{

			sum = 0;

			for (j = 0; j < NMAX; j++)

				sum += a[i][j];

			//printf("Сумма элементов строки %d равна %f\n", i, sum);

		}

	}
	
/* Завершение параллельного фрагмента */

	end = omp_get_wtime();

	//cout << endl << sum << endl;

	for (i = 0; i < NMAX; i++)

		delete[]a[i];

	cout << "Время " << end - start << endl;

}
