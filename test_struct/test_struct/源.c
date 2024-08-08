#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
typedef struct M
{
	int a;
	float b;
}Me;

void alloc(Me **m, int len, void** p) {
	*m = (Me*)malloc(sizeof(Me) + len);
	*m = (Me*)malloc(sizeof(Me) + len);
	*p = (char*)*m + sizeof(Me);
}

int main(void)
{
	Me* m = NULL;
	char* p;
	alloc(&m, 10, &p);
	m->a = 6;
	char a[10] = "123456789\0";
	int len = strlen(a);
	memcpy(p,a,10);
	printf("m->a = %d,p = %s", m->a, p);
	free(m);
	printf("m->a = %d,p = %s", m->a, p);
	return 0;
}
