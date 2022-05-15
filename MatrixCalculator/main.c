#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int main() {
	system("chcp 1251");
	system("cls");

	printf("��� �� ������ ������� � ��������?\n");
	printf("����� 1 - ������� (�������) � ������ ��������\n");
	printf("����� 2 - ���������������\n");
	printf("����� 3 - �������� �� �����\n");
	printf("����� 4 - �������� �� ������ �������\n");
	printf("����� 5 - �������� � ������� n (��� n - �����������)\n");
	printf("����� 6 - ��������� ������������\n");
	printf("����� 7 - ����� �������� �������\n");
	printf("������� ����� : ");
	int choice;
	scanf_s("%d", &choice);

	switch (choice) {
	case 1: {
		int i, j;
		int n, m;
		char oper;
		float** a, ** b;

		printf("������� A :\n");
		a = arraySquareEnter(&n);
		getchar();
		printf("�������� : ");
		scanf_s("%c", &oper);
		printf("������� B :\n");
		b = arraySquareEnter(&m);

		if (n != m) {
			printf("������� ������ ���� ����������� �������...");
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
			printf("������ �������� ����...");
			arrayFree(a, n);
			arrayFree(b, m);
			exit(1);
		}

		printf("��������� :\n");
		arrayPrint(a, n, n);

		arrayFree(a, n);
		arrayFree(b, m);
		break;
	}
	case 2: {
		int n, m;
		float** a;

		printf("\n���������������� �������\n");
		a = arrayOblongEnter(&n, &m);
		a = transposition(a, &n, &m);

		printf("��������� :\n");
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

		printf("\n��������� ������� �� �����\n");
		a = arrayOblongEnter(&n, &m);
		printf("������� ����� ��� ����� ( -1.2 , 4/7, ... ) : ");
		scanf_s("%f", &num);
		scanf_s("%c", &slash);
		if (slash == 47) {
			scanf_s("%f", &den);
		}
		else if (slash == '\n') den = 1;
		else {
			printf("������ �� ��� ���� ( ��� ����� ������ ����� '%g' � '/' )", num);
			arrayFree(a, n);
			exit(1);
		}

		for (i = 0; i < n; i++) {
			for (j = 0; j < m; j++) {
				a[i][j] = a[i][j] * num / den;
			}
		}

		printf("��������� :\n");
		arrayPrint(a, n, m);

		arrayFree(a, n);
		break;
	}
	case 4: {

		int n_a, m_a, n_b, m_b;
		int i, j;
		float** a, ** b, ** s;

		printf("\n������������ ������:\n");
		printf("������� A :\n");
		a = arrayOblongEnter(&n_a, &m_a);
		printf("������� B :\n");
		b = arrayOblongEnter(&n_b, &m_b);

		s = arrayAlloc(n_a, m_b);
		for (i = 0; i < n_a; i++) {
			for (j = 0; j < m_b; j++) {
				s[i][j] = 0;
			}
		}

		if (m_a != n_b) {
			printf("��� ������� �� ����� ���� ��������...");
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

		printf("��������� :\n");
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

		printf("\n���������� ������� � �������:\n");
		a = arraySquareEnter(&n);

		p = arrayAlloc(n, n);
		r = arrayAlloc(n, n);
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) {
				p[i][j] = a[i][j];
				r[i][j] = 0;
			}
		}

		printf("������� ������� : ");
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
				for (q = 0; q < power - 1; q++) { // �������

					for (i = 0; i < n; i++) { // �� �������
						for (j = 0; j < n; j++) { // �� �������� (n=m)

							for (u = 0; u < n; u++) { // ����������� ��-�
								r[i][j] += p[i][u] * a[u][j];
							}
						}
					} // ��������� ��������� ��������������� ������� r,������� ����� ������ �������� � ���������� ��� �������� �������
					for (i = 0; i < n; i++) {
						for (j = 0; j < n; j++) {
							p[i][j] = r[i][j];
							r[i][j] = 0;
						}
					}
				}
			}
			printf("��������� :\n");
			arrayPrint(p, n, n);

		}
		else {
			printf("������� ������ ������������ ����������� ������...");
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

		printf("\n���������� ������������ �������:\n");
		a = arraySquareEnter(&n);

		det = determinant(a, n);
		printf("������������ = %g", det);

		arrayFree(a, n);
		break;
	}
	case 7: {
		int n;
		int i, j;
		float det;
		float** a, ** d;

		printf("\n���������� �������� �������\n");
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
			printf("������� ������� :\n");
			arrayPrint(a, n, n);
			a = transposition(a, &n, &n);
			printf("�������� ������� ����� ����� :\n");
			printf("������� �������������� ���������� :\n");
			arrayPrint(a, n, n);
			printf("������� �� ������������ :\n");
			printf("%g", det);
		}
		else {
			printf("�������� ������� �� ����� ���� �������, ��� ��� ������������ ����� ����...");
			arrayFree(a, n);
			exit(1);
		}

		arrayFree(a, n);
		break;
	}
	default: printf("����� ������� �������...");
	}

	return 0;
}