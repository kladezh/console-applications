#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
	system("chcp 1251");
	system("cls");

	printf("Что вы хотите сделать с матрицей?\n");
	printf("Цифра 1 - сложить (вычесть) с другой матрицей\n");
	printf("Цифра 2 - транспонировать\n");
	printf("Цифра 3 - умножить на число\n");
	printf("Цифра 4 - умножить на другую матрицу\n");
	printf("Цифра 5 - возвести в степень n (где n - натуральное)\n");
	printf("Цифра 6 - вычислить определитель\n");
	printf("Цифра 7 - найти обратную матрицу\n");
	printf("Введите цифру : ");
	int choice;
	scanf_s("%d", &choice);

	switch (choice) {
	case 1: {
		int i, j;
		int n, m;
		char oper;
		float** a, ** b;

		printf("Матрица A :\n");
		a = arraySquareEnter(&n);
		getchar();
		printf("Операция : ");
		scanf_s("%c", &oper);
		printf("Матрица B :\n");
		b = arraySquareEnter(&m);

		if (n != m) {
			printf("Матрицы должны быть одинакового размера...");
			arrayFree(a, n);
			arrayFree(b, m);
			exit(1);
		}

		if (oper == 43) {
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					a[i][j] += b[i][j];
				}
			}
		}
		else if (oper == 45) {
			for (i = 0; i < n; i++) {
				for (j = 0; j < n; j++) {
					a[i][j] -= b[i][j];
				}
			}
		}
		else {
			printf("Введен неверный знак...");
			arrayFree(a, n);
			arrayFree(b, m);
			exit(1);
		}

		printf("Результат :\n");
		arrayPrint(a, n, n);

		arrayFree(a, n);
		arrayFree(b, m);
		break;
	}
	case 2: {
		int n, m;
		float** a;

		printf("\nТранспонирование матрицы\n");
		a = arrayOblongEnter(&n, &m);
		a = transposition(a, &n, &m);

		printf("Результат :\n");
		arrayPrint(a, n, m);

		arrayFree(a, n);
		break;
	}
	case 3: {
		int i, j;
		int n, m;
		float num, den;
		char slash;
		float** a;

		printf("\nУмножение матрицы на число\n");
		a = arrayOblongEnter(&n, &m);
		printf("Введите число или дробь ( -1.2 , 4/7, ... ) : ");
		scanf_s("%f", &num);
		scanf_s("%c", &slash);
		if (slash == 47) {
			scanf_s("%f", &den);
		}
		else if (slash == '\n') den = 1;
		else {
			printf("Введен не тот знак ( или стоит пробел между '%g' и '/' )", num);
			arrayFree(a, n);
			exit(1);
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				a[i][j] = a[i][j] * num / den;
			}
		}

		printf("Результат :\n");
		arrayPrint(a, n, m);

		arrayFree(a, n);
		break;
	}
	case 4: {

		int n_a, m_a, n_b, m_b;
		int i, j;
		float** a, ** b, ** s;

		printf("\nПроизведение матриц:\n");
		printf("Матрица A :\n");
		a = arrayOblongEnter(&n_a, &m_a);
		printf("Матрица B :\n");
		b = arrayOblongEnter(&n_b, &m_b);

		s = arrayAlloc(n_a, m_b);
		for (i = 0; i < n_a; i++) {
			for (j = 0; j < m_b; j++) {
				s[i][j] = 0;
			}
		}

		if (m_a != n_b) {
			printf("Эти матрицы не могут быть умножены...");
			arrayFree(a, n_a);
			arrayFree(b, n_b);
			arrayFree(s, n_a);
			exit(1);
		}

		for (i = 0; i < n_a; i++) {
			for (j = 0; j < m_b; j++) {
				for (int k = 0; k < m_a; k++) {
					s[i][j] += a[i][k] * b[k][j];
				}
			}
		}

		printf("Результат :\n");
		arrayPrint(s, n_a, m_b);

		arrayFree(a, n_a);
		arrayFree(b, n_b);
		arrayFree(s, n_a);
		break;
	}
	case 5: {
		int n;
		int power;
		int i, j, q, u;
		float** a, ** p, ** r;

		printf("\nВозведение матрицы в степень:\n");
		a = arraySquareEnter(&n);

		p = arrayAlloc(n, n);
		r = arrayAlloc(n, n);
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				p[i][j] = a[i][j];
				r[i][j] = 0;
			}
		}

		printf("Введите степень : ");
		scanf_s("%d", &power);

		if (power > -1) {

			if (power == 0) {
				for (i = 0; i < n; i++) {
					for (j = 0; j < n; j++) {
						if (i == j) p[i][j] = 1;
						else p[i][j] = 0;
					}
				}
			}
			else {
				for (q = 0; q < power - 1; q++) { // степень

					for (i = 0; i < n; i++) { // по строкам
						for (j = 0; j < n; j++) { // по столбцам (n=m)

							for (u = 0; u < n; u++) { // вычисляется эл-т
								r[i][j] += p[i][u] * a[u][j];
							}
						}
					} // результат принимает вспомогательная матрица r,которая потом отдает значения и обнуляется для следущей степени
					for (i = 0; i < n; i++) {
						for (j = 0; j < n; j++) {
							p[i][j] = r[i][j];
							r[i][j] = 0;
						}
					}
				}
			}
			printf("Результат :\n");
			arrayPrint(p, n, n);

		}
		else {
			printf("Степень должна принадлежать натуральным числам...");
			arrayFree(a, n);
			arrayFree(p, n);
			arrayFree(r, n);
			exit(1);
		}

		arrayFree(a, n);
		arrayFree(p, n);
		arrayFree(r, n);
		break;
	}
	case 6: {
		int n;
		float det;
		float** a;

		printf("\nВычисление определителя матрицы:\n");
		a = arraySquareEnter(&n);

		det = determinant(a, n);
		printf("Определитель = %g", det);

		arrayFree(a, n);
		break;
	}
	case 7: {
		int n;
		int i, j;
		float det;
		float** a, ** d;

		printf("\nНахождение обратной матрицы\n");
		a = arraySquareEnter(&n);
		d = arrayAlloc(n, n);
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				d[i][j] = a[i][j];
			}
		}

		det = determinant(d, n);
		arrayFree(d, n);
		if (det != 0) {
			a = algebraAdd(a, n);
			printf("союзная матрица :\n");
			arrayPrint(a, n, n);
			a = transposition(a, &n, &n);
			printf("Обратная матрица будет равна :\n");
			printf("матрица алгебраических дополнений :\n");
			arrayPrint(a, n, n);
			printf("деленая на определитель :\n");
			printf("%g", det);
		}
		else {
			printf("Обратная матрица не может быть найдена, так как определитель равен нулю...");
			arrayFree(a, n);
			exit(1);
		}

		arrayFree(a, n);
		break;
	}
	default: printf("Цифра введена неверно...");
	}

	return 0;
}