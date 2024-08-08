#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main() {

    char p1[] = "abcde";
    char* p2 = (char*)malloc(5);
    memcpy(p2, p1, 5);
    printf("%d\n", strlen(p2));
    printf("%s\n", p2);
    return 0;
}