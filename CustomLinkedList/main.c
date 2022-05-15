#include<stdio.h>
#include<stdlib.h>
#include<string.h> // для strlen()

/* Сразу скажу: во всех функциях используется ptrBegin - это указатель типа libr*, который лежит в локальной памяти
и не имеет у себя данных, он только указывает на первый узел, который уже лежит в динамической памяти и является по сути началом цепочки как элемент цепочки.
Также в функциях используется libr* ptr = ptrBegin - это вспомогательный указатель, который ходит по узлам и, если надо, меняет значения их указателям*/

// объявление структуры и нового типа libr
typedef struct libr {
	struct libr* next; // указатель на следующий элемент (реализация хранения памяти на куче односвязным списком)
	//данные структуры
	char* udc; //код УДК. В виде строки, т.к. я не понял, какая у него структура (просто число или массив, но там и точки в начале могут стоять вроде)
	char* lastname; // фамилия автора
	char* title; // название книги
	int date; // год выпуска
	int count; // кол-во книг на складе
}libr;

// описание функция находится ниже
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

	ptrBegin = (libr*)malloc(sizeof(libr)); // выделяем память для первого узла
	inputData(ptrBegin); // вводим данные
	ptrBegin->next = NULL; // "закрываем"

	int choice = -1;  // для switch
	int hidePrint = 0; // флаг, для того, чтобы список лишний раз в цикле не печатался в определенных ситуациях

	while (choice != 0) {

		if (hidePrint == 0) {
			printList(ptrBegin);
		}
		else {
			hidePrint = 0;
		}
		printf("Please enter: 1 - to add a book, 2 - to delete a book, 3 - to sort data by date, 0 - to exit:\n");

		scanf_s("%d", &choice);
		getchar(); // съесть enter перед вводом следующей строки udc
		switch (choice) {
		case 1: { // добавить книгу
			addNode(ptrBegin);

			break;
		}
		case 2: { // удалить определенную книгу
			int i;

			printf("Enter number of book to delete: ");
			scanf_s("%d", &i); // для пользователя нумерация начинается с 1, а в массиве с 0
			i--; // поэтому уменьшаем
			ptrBegin = delNode(ptrBegin, i);

			break;
		}
		case 3: { // отсортировать книги по дате публикации
			ptrBegin = sortList(ptrBegin);

			break;
		}
		case 0: break; // завершить программу
		default: printf("You pressed the wrong key. Try again...\n"); hidePrint = 1;
		}
	}

	freeList(ptrBegin); // освободить память списка
	return 0;
}

// функция, которая передает строку stringGive в stringPtr(нужна для динамической строки, тоесть в структуре я не выделял буффер, а объявил только указатель)
// при этом, stringPtr должен быть передан в функцию, предварительно не имея указания на блок памяти, память для него выделятся в этой функции
char* strGive(char* stringPtr, char* stringGive) {
	int i;
	int size = strlen(stringGive);

	// по длине переданной строки выделется память для назначаемой строки, и еще + 1 байт на закрывающий символ
	stringPtr = (char*)malloc(sizeof(char) * (size + 1));
	stringPtr[size] = '\0'; // закрывающий символ

	// посимвольное копирование строк
	for (i = 0; i < size; i++) {
		stringPtr[i] = stringGive[i];
	}

	// и вернуть указатель, так как для него выделялась память
	return stringPtr;
}

// функция для перестановки двух узлов списка, но так как они расположены не непрерывно (как эл-ты массива) тут происходят танцы с указателями, значения не изменяются
libr* swapNodePtr(libr* ptrBegin, libr* ptrL, libr* ptrR) { // параметры: главный указатель, узлы, которые нужно заменить - левый и правый, как они расположены в списке
	libr* ptr = ptrBegin;

	// алгоритм должен совершить 4 действия, таких что: (1)левый эл-т указывает туда, куда правый, (2)правый - туда, куда левый,
	// (3)тот, кто указывал на левый теперь указывает на правый, и (4) тот кто на правый - теперь на левый.

	// если нужные узлы расположены вместо, т.е. левый указывает на правый, то это особый случай, в котором (2) и (4) действия сливаются в одно  
	// сначала делаем на это проверку
	if (ptrL->next != ptrR) {
		// если между ptrL и ptrR есть узлы, то доходим до того, кто указывает на ptrR и выполняем (4) действие
		while (ptr->next != ptrR) {
			ptr = ptr->next;
		}
		ptr->next = ptrL;

		ptr = ptrBegin;
	}

	// в любом случае выполняется (1) и (3) действие
	if (ptr == ptrL) {// но есть еще частный случай, когда ptrL - первый узел, спика, тогда "цикл" не нужен
		ptrBegin = ptrR; // (3) действие
	}
	else {
		while (ptr->next != ptrL) {

			ptr = ptr->next;
		}
		ptr->next = ptrR; // (3) действие
	}

	// теперь изменяются указтели у нужных узлов ( (1) и (2) действия), но опять же
	if (ptrL->next != ptrR) { // если они не рядом - то меняем местами
		libr* tmp;
		tmp = ptrL->next;
		ptrL->next = ptrR->next;
		ptrR->next = tmp;
	}
	else { // иначе 
		ptrL->next = ptrR->next; // левый указывает туда, куда правый
		ptrR->next = ptrL; // правый укзаывает на сам левый узел
	}

	return ptrBegin;
}

// функция ввода данных в узел списка
void inputData(libr* ptr) {
	char strBuf[256]; // для ввода строки и передачи её в данные, заданые строками

	printf("Enter the book details:\n");

	printf("UDC code: ");
	gets(strBuf); // считываем строку
	ptr->udc = strGive(ptr->udc, strBuf); // передаем пустой указатель, и указатель на строку

	// lastname и title аналогично
	printf("Author's lastname: ");
	gets(strBuf);
	ptr->lastname = strGive(ptr->lastname, strBuf);

	printf("Book's title: ");
	gets(strBuf);
	ptr->title = strGive(ptr->title, strBuf);

	// обычный ввод чисел
	printf("Publication date: ");
	scanf_s("%d", &ptr->date);

	printf("Number of copies in the library: ");
	scanf_s("%d", &ptr->count);
}

// функция добавления узла в конец списка (выделение памяти и ввод данных)
void addNode(libr* ptrBegin) {
	libr* ptr = ptrBegin;
	libr* ptrCur = ptrBegin;

	// ptr ходит указателям узлов и ищет тот, кто указывает на NULL (т.е. последний узел), ptrCur - запоминает сам узел
	while (ptr != NULL) {
		ptrCur = ptr;
		ptr = ptr->next;
	}

	ptr = (libr*)malloc(sizeof(libr)); // выделение памяти для узла
	inputData(ptr); // ввод данных по этому адресу
	ptr->next = NULL; // последний узел указвает на NULL

	ptrCur->next = ptr; // присоединяем узел к списку
}

// функция удаления указанного узла
libr* delNode(libr* ptrBegin, int del_i) {
	// del_i - номер нужного узла, в функции нумерация идет с нуля как в массиве

	if (del_i == 0) { // если это первый узел, то просто главному указателю присваиваем второй узел
		ptrBegin = ptrBegin->next;
	}
	else if (del_i > 0) {
		libr* ptr = ptrBegin;
		int i = 0;

		// ищем тот узел, который стоит до удаляемого
		while (i != del_i - 1 && ptr->next != NULL) {
			ptr = ptr->next;
			i++;
		}
		if (ptr->next == NULL) { // при этом цикл мог завершиться, если пользователь ввел число больше кол-ва, тогда указатель упрется в конец
			printf("You enter the wrong number...\n");
			return ptrBegin;
		}

		// ptr остановился на пред-удаляемом узле и нужно проверить
		if ((ptr->next)->next == NULL) {// если нужно удалить последнить эл-т, то пред-удаляемому нужно присвоить NULL
			free(ptr->next);// и предварительно освободить память
			ptr->next = NULL;
		}
		else {// иначе пред-удаляемому указателю присвоить пост-удаляемый, предварительно освободив память от удаляемого эл-та
			free(ptr->next);
			ptr->next = (ptr->next)->next;
		}
	}
	else printf("You enter the wrong number...\n");

	return ptrBegin;
}

// функция освобождения памяти односвязного списка
void freeList(libr* ptrBegin) {
	libr* ptr;

	// узлы освобождаются начиная с первого; если текущий узел не указывает на NULL, то переходим на следующий, а пред. освобождаем
	while (ptrBegin != NULL) {
		ptr = ptrBegin->next;
		free(ptrBegin);
		ptrBegin = ptr;
	}
}

// функция сортировки списка по значению "дата публикации", в основе алгоритм Selection Sort 
libr* sortList(libr* ptrBegin) {
	libr* ptrCur = ptrBegin; // стоит на текущем узле, относительно которого ищется минимум (как i в for)
	libr* ptrSeek = ptrBegin; // проходится по узлам, начиная с ptrCur->next (как i+1) (как j в for)
	libr* ptrMin = ptrBegin; // запоминает минимальный узел
	int minEl; // работает с числами 

	// если список пуст, а пользователь нажал сортировку - то выйти с функции
	if (ptrBegin == NULL) {
		return ptrBegin;
	}

	while (ptrCur->next != NULL) { // for (i = 0;i < n;i++)
		minEl = ptrCur->date; // minEl = a[i];

		ptrSeek = ptrCur->next; // k = i + 1;
		while (ptrSeek != NULL) { // for (j = k; j < n;j++)

			if (ptrSeek->date < minEl) { // поиск минимума
				minEl = ptrSeek->date;
				ptrMin = ptrSeek;
			}

			ptrSeek = ptrSeek->next;
		}

		if (minEl != ptrCur->date) { // если нашелся узел меньше, то меняем
			ptrBegin = swapNodePtr(ptrBegin, ptrCur, ptrMin);
		}

		ptrCur = ptrMin->next;
	}

	return ptrBegin;
}

// функция вывода списка (с табуляцией есть небольшие проблемы)
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
