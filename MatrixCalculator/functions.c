#include "functions.h"

float** arrayAlloc(int n, int m) {
	float** arr = (float**)malloc(n * sizeof(float*));
	for (int i = 0; i < n; i++) {
		arr[i] = (float*)malloc(m * sizeof(float));
	}

	return arr;
}
void arrayFree(float** arr, int n) {
	for (int i = 0; i < n; i++) {
		free(arr[i]);
	}
	free(arr);
}

float** arraySquareEnter(int* n) {
	int i, j;

	printf("¬ведите размерность : ");
	scanf_s("%d", n);
	float** arr = arrayAlloc(*n, *n);
	printf("¬ведите элементы матрицы :\n");
	for (i = 0; i < *n; i++) {
		for (j = 0; j < *n; j++) {
			scanf_s("%f", &arr[i][j]);
		}
	}

	return arr;
}
float** arrayOblongEnter(int* n, int* m) {
	int i, j;

	printf("¬ведите кол-во строк : ");
	scanf_s("%d", n);
	printf("¬ведите кол-во столбцов : ");
	scanf_s("%d", m);
	float** arr = arrayAlloc(*n, *m);
	printf("¬ведите элементы матрицы :\n");
	for (i = 0; i < *n; i++) {
		for (j = 0; j < *m; j++) {
			scanf_s("%f", &arr[i][j]);
		}
	}

	return arr;
}

void arrayPrint(float** arr, int n, int m) {
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < m; j++) {
			printf("%g ", arr[i][j]);
		}
		printf("\n");
	}
}

float determinant(float** arr, int n) {
	int i, j, k;
	float det;

	if (n == 2) {
		det = (arr[0][0] * arr[1][1]) - (arr[1][0] * arr[0][1]);
	}
	else {
		// перестановка строк, чтобы ведущий элемент был != 0
		if (arr[0][0] == 0) {

			float maxLeadEl = 0;
			int iMaxEl = 0;
			for (k = 1; k < n; k++) {
				if (fabs(arr[k][0]) > fabs(maxLeadEl)) {
					maxLeadEl = arr[k][0];
					iMaxEl = k;
				}
			}
			float tmp;
			for (k = 0; k < n; k++) {
				tmp = arr[0][k];
				arr[0][k] = arr[iMaxEl][k];
				arr[iMaxEl][k] = tmp;
			}

		}

		// нули ниже главной диагонали (ступенчатый вид)
		for (j = 0; j < n; j++) {
			for (i = j + 1; i < n; i++) {
				if (arr[i][j] != 0) {
					float toZero = (-1 * arr[i][j]) / arr[j][j];
					for (k = 0; k < n; k++) {
						arr[i][k] = arr[i][k] + arr[j][k] * toZero;
					}
				}
			}
		}

		det = 1;
		for (i = 0; i < n; i++) {
			det *= arr[i][i];
		}
	}

	return det;
}
float** algebraAdd(float** arr, int n) {
	int i, j, k, p, u, v;
	float** b = arrayAlloc(n, n);
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			b[i][j] = arr[i][j];
		}
	}

	float** m = arrayAlloc(n - 1, n - 1);
	int det; int unit = -1;
	for (k = 0; k < n; k++) {
		for (p = 0; p < n; p++) {

			u = 0; v = 0;
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					if (i != k && j != p) {

						if (v != (n - 1)) {
							m[u][v] = b[i][j];
							v++;
						}
						else if (u != (n - 1) - 1) {
							u++; v = 0;
							m[u][v] = b[i][j];
							v++;
						}

					}
				}
			}
			det = determinant(m, n - 1);
			unit *= -1;
			arr[k][p] = unit * det;

		}
	}

	arrayFree(b, n);
	arrayFree(m, n - 1);
	return arr;
}
float** transposition(float** arr, int* n, int* m) {
	int i, j;
	float** t = arrayAlloc(*m, *n);

	for (i = 0; i < *n; i++) {
		for (j = 0; j < *m; j++) {
			t[j][i] = arr[i][j];
		}
	}
	if (*n != *m) {
		int tmp;
		tmp = *n;
		*n = *m;
		*m = tmp;
	}

	arrayFree(arr, *n);
	return t;
}