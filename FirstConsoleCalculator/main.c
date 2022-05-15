#include <stdio.h>

int main()
{
    int a, b;
    char op[2];

    printf("Input a:"); scanf_s("%d", &a);
    printf("Input op:"); scanf_s("%c", &op[0]); scanf_s("%c", &op[1]);
    printf("Input b:"); scanf_s("%d", &b);
    op[0] = '0';
    switch (op[1])
    {
    case '+':
        printf("%d %c %d = %d\n", a, op[1], b, a + b);
        break;
    case '-':
        printf("%d %c %d = %d\n", a, op[1], b, a - b);
        break;
    case '*':
        printf("%d %c %d = %d\n", a, op[1], b, a * b);
        break;
    case '/':
        printf("%d %c %d = %f\n", a, op[1], b, (double)a / b);
        break;
    default:
        printf("NON operation\n");
        break;
    }


    return 0;
}
