#include<stdio.h>
#include<stdlib.h>
#include<string.h> // ��� strlen()

/* ����� �����: �� ���� �������� ������������ ptrBegin - ��� ��������� ���� libr*, ������� ����� � ��������� ������
� �� ����� � ���� ������, �� ������ ��������� �� ������ ����, ������� ��� ����� � ������������ ������ � �������� �� ���� ������� ������� ��� ������� �������.
����� � �������� ������������ libr* ptr = ptrBegin - ��� ��������������� ���������, ������� ����� �� ����� �, ���� ����, ������ �������� �� ����������*/

// ���������� ��������� � ������ ���� libr
typedef struct libr {
	struct libr* next; // ��������� �� ��������� ������� (���������� �������� ������ �� ���� ����������� �������)
	//������ ���������
	char* udc; //��� ���. � ���� ������, �.�. � �� �����, ����� � ���� ��������� (������ ����� ��� ������, �� ��� � ����� � ������ ����� ������ �����)
	char* lastname; // ������� ������
	char* title; // �������� �����
	int date; // ��� �������
	int count; // ���-�� ���� �� ������
}libr;

// �������� ������� ��������� ����
char* strGive(char* stringPtr, char* stringGive);
libr* swapNodePtr(libr* ptrBegin, libr* ptrL, libr* ptrR);
void inputData(libr* ptr);
void addNode(libr* ptrBegin);
libr* delNode(libr* ptrBegin, int del_i);
void freeList(libr* ptrBegin);
libr* sortList(libr* ptrBegin);
void printList(libr* ptrBegin);

int main() {
	libr* ptrBegin = NULL;

	ptrBegin = (libr*)malloc(sizeof(libr)); // �������� ������ ��� ������� ����
	inputData(ptrBegin); // ������ ������
	ptrBegin->next = NULL; // "���������"

	int choice = -1;  // ��� switch
	int hidePrint = 0; // ����, ��� ����, ����� ������ ������ ��� � ����� �� ��������� � ������������ ���������

	while (choice != 0) {

		if (hidePrint == 0) {
			printList(ptrBegin);
		}
		else {
			hidePrint = 0;
		}
		printf("Please enter: 1 - to add a book, 2 - to delete a book, 3 - to sort data by date, 0 - to exit:\n");

		scanf_s("%d", &choice);
		getchar(); // ������ enter ����� ������ ��������� ������ udc
		switch (choice) {
		case 1: { // �������� �����
			addNode(ptrBegin);

			break;
		}
		case 2: { // ������� ������������ �����
			int i;

			printf("Enter number of book to delete: ");
			scanf_s("%d", &i); // ��� ������������ ��������� ���������� � 1, � � ������� � 0
			i--; // ������� ���������
			ptrBegin = delNode(ptrBegin, i);

			break;
		}
		case 3: { // ������������� ����� �� ���� ����������
			ptrBegin = sortList(ptrBegin);

			break;
		}
		case 0: break; // ��������� ���������
		default: printf("You pressed the wrong key. Try again...\n"); hidePrint = 1;
		}
	}

	freeList(ptrBegin); // ���������� ������ ������
	return 0;
}

// �������, ������� �������� ������ stringGive � stringPtr(����� ��� ������������ ������, ������ � ��������� � �� ������� ������, � ������� ������ ���������)
// ��� ����, stringPtr ������ ���� ������� � �������, �������������� �� ���� �������� �� ���� ������, ������ ��� ���� ��������� � ���� �������
char* strGive(char* stringPtr, char* stringGive) {
	int i;
	int size = strlen(stringGive);

	// �� ����� ���������� ������ ��������� ������ ��� ����������� ������, � ��� + 1 ���� �� ����������� ������
	stringPtr = (char*)malloc(sizeof(char) * (size + 1));
	stringPtr[size] = '\0'; // ����������� ������

	// ������������ ����������� �����
	for (i = 0; i < size; i++) {
		stringPtr[i] = stringGive[i];
	}

	// � ������� ���������, ��� ��� ��� ���� ���������� ������
	return stringPtr;
}

// ������� ��� ������������ ���� ����� ������, �� ��� ��� ��� ����������� �� ���������� (��� ��-�� �������) ��� ���������� ����� � �����������, �������� �� ����������
libr* swapNodePtr(libr* ptrBegin, libr* ptrL, libr* ptrR) { // ���������: ������� ���������, ����, ������� ����� �������� - ����� � ������, ��� ��� ����������� � ������
	libr* ptr = ptrBegin;

	// �������� ������ ��������� 4 ��������, ����� ���: (1)����� ��-� ��������� ����, ���� ������, (2)������ - ����, ���� �����,
	// (3)���, ��� �������� �� ����� ������ ��������� �� ������, � (4) ��� ��� �� ������ - ������ �� �����.

	// ���� ������ ���� ����������� ������, �.�. ����� ��������� �� ������, �� ��� ������ ������, � ������� (2) � (4) �������� ��������� � ����  
	// ������� ������ �� ��� ��������
	if (ptrL->next != ptrR) {
		// ���� ����� ptrL � ptrR ���� ����, �� ������� �� ����, ��� ��������� �� ptrR � ��������� (4) ��������
		while (ptr->next != ptrR) {
			ptr = ptr->next;
		}
		ptr->next = ptrL;

		ptr = ptrBegin;
	}

	// � ����� ������ ����������� (1) � (3) ��������
	if (ptr == ptrL) {// �� ���� ��� ������� ������, ����� ptrL - ������ ����, �����, ����� "����" �� �����
		ptrBegin = ptrR; // (3) ��������
	}
	else {
		while (ptr->next != ptrL) {

			ptr = ptr->next;
		}
		ptr->next = ptrR; // (3) ��������
	}

	// ������ ���������� �������� � ������ ����� ( (1) � (2) ��������), �� ����� ��
	if (ptrL->next != ptrR) { // ���� ��� �� ����� - �� ������ �������
		libr* tmp;
		tmp = ptrL->next;
		ptrL->next = ptrR->next;
		ptrR->next = tmp;
	}
	else { // ����� 
		ptrL->next = ptrR->next; // ����� ��������� ����, ���� ������
		ptrR->next = ptrL; // ������ ��������� �� ��� ����� ����
	}

	return ptrBegin;
}

// ������� ����� ������ � ���� ������
void inputData(libr* ptr) {
	char strBuf[256]; // ��� ����� ������ � �������� � � ������, ������� ��������

	printf("Enter the book details:\n");

	printf("UDC code: ");
	gets(strBuf); // ��������� ������
	ptr->udc = strGive(ptr->udc, strBuf); // �������� ������ ���������, � ��������� �� ������

	// lastname � title ����������
	printf("Author's lastname: ");
	gets(strBuf);
	ptr->lastname = strGive(ptr->lastname, strBuf);

	printf("Book's title: ");
	gets(strBuf);
	ptr->title = strGive(ptr->title, strBuf);

	// ������� ���� �����
	printf("Publication date: ");
	scanf_s("%d", &ptr->date);

	printf("Number of copies in the library: ");
	scanf_s("%d", &ptr->count);
}

// ������� ���������� ���� � ����� ������ (��������� ������ � ���� ������)
void addNode(libr* ptrBegin) {
	libr* ptr = ptrBegin;
	libr* ptrCur = ptrBegin;

	// ptr ����� ���������� ����� � ���� ���, ��� ��������� �� NULL (�.�. ��������� ����), ptrCur - ���������� ��� ����
	while (ptr != NULL) {
		ptrCur = ptr;
		ptr = ptr->next;
	}

	ptr = (libr*)malloc(sizeof(libr)); // ��������� ������ ��� ����
	inputData(ptr); // ���� ������ �� ����� ������
	ptr->next = NULL; // ��������� ���� �������� �� NULL

	ptrCur->next = ptr; // ������������ ���� � ������
}

// ������� �������� ���������� ����
libr* delNode(libr* ptrBegin, int del_i) {
	// del_i - ����� ������� ����, � ������� ��������� ���� � ���� ��� � �������

	if (del_i == 0) { // ���� ��� ������ ����, �� ������ �������� ��������� ����������� ������ ����
		ptrBegin = ptrBegin->next;
	}
	else if (del_i > 0) {
		libr* ptr = ptrBegin;
		int i = 0;

		// ���� ��� ����, ������� ����� �� ����������
		while (i != del_i - 1 && ptr->next != NULL) {
			ptr = ptr->next;
			i++;
		}
		if (ptr->next == NULL) { // ��� ���� ���� ��� �����������, ���� ������������ ���� ����� ������ ���-��, ����� ��������� ������� � �����
			printf("You enter the wrong number...\n");
			return ptrBegin;
		}

		// ptr ����������� �� ����-��������� ���� � ����� ���������
		if ((ptr->next)->next == NULL) {// ���� ����� ������� ���������� ��-�, �� ����-���������� ����� ��������� NULL
			free(ptr->next);// � �������������� ���������� ������
			ptr->next = NULL;
		}
		else {// ����� ����-���������� ��������� ��������� ����-���������, �������������� ��������� ������ �� ���������� ��-��
			free(ptr->next);
			ptr->next = (ptr->next)->next;
		}
	}
	else printf("You enter the wrong number...\n");

	return ptrBegin;
}

// ������� ������������ ������ ������������ ������
void freeList(libr* ptrBegin) {
	libr* ptr;

	// ���� ������������� ������� � �������; ���� ������� ���� �� ��������� �� NULL, �� ��������� �� ���������, � ����. �����������
	while (ptrBegin != NULL) {
		ptr = ptrBegin->next;
		free(ptrBegin);
		ptrBegin = ptr;
	}
}

// ������� ���������� ������ �� �������� "���� ����������", � ������ �������� Selection Sort 
libr* sortList(libr* ptrBegin) {
	libr* ptrCur = ptrBegin; // ����� �� ������� ����, ������������ �������� ������ ������� (��� i � for)
	libr* ptrSeek = ptrBegin; // ���������� �� �����, ������� � ptrCur->next (��� i+1) (��� j � for)
	libr* ptrMin = ptrBegin; // ���������� ����������� ����
	int minEl; // �������� � ������� 

	// ���� ������ ����, � ������������ ����� ���������� - �� ����� � �������
	if (ptrBegin == NULL) {
		return ptrBegin;
	}

	while (ptrCur->next != NULL) { // for (i = 0;i < n;i++)
		minEl = ptrCur->date; // minEl = a[i];

		ptrSeek = ptrCur->next; // k = i + 1;
		while (ptrSeek != NULL) { // for (j = k; j < n;j++)

			if (ptrSeek->date < minEl) { // ����� ��������
				minEl = ptrSeek->date;
				ptrMin = ptrSeek;
			}

			ptrSeek = ptrSeek->next;
		}

		if (minEl != ptrCur->date) { // ���� ������� ���� ������, �� ������
			ptrBegin = swapNodePtr(ptrBegin, ptrCur, ptrMin);
		}

		ptrCur = ptrMin->next;
	}

	return ptrBegin;
}

// ������� ������ ������ (� ���������� ���� ��������� ��������)
void printList(libr* ptrBegin) {
	char* cat[6] = { "N","UDC","Author's lastname", "Book's title", "Publication date","Number of copies" };
	int i;

	if (ptrBegin == NULL) {
		printf("\n");
		for (i = 0; i < 6; i++) {
			printf("%-12s\t", cat[i]);
		}
		printf("\n");
		printf("---------------------------------------------------------------------------------------\n");
	}
	else {
		libr* ptr = ptrBegin;

		printf("\n");
		for (i = 0; i < 6; i++) {
			printf("%-12s\t", cat[i]);
		}
		printf("\n");
		printf("===========================================================================================\n");
		i = 0;
		while (ptr != NULL) {
			printf("%-12d\t%-12s\t%-20s\t%-20s\t%-20d\t%-20d\t\n", i + 1, ptr->udc, ptr->lastname, ptr->title, ptr->date, ptr->count);
			printf("\n");
			ptr = ptr->next;
			i++;
		}
		printf("\n");
	}
}
