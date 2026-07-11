#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define OK 1
#define ERROR 0	
#define TRUE 1		
#define FALSE 0
#define OVERFLOW -2
typedef int Status;
typedef int ElemType;
void InitArray(ElemType **A,int n){
	A = (ElemType*)malloc(n * sizeof(ElemType));
	if (!A) {
		printf("Memory overflow!\n");
		exit(OVERFLOW);
	}
	}//初始化数组)