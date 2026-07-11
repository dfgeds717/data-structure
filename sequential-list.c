#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define OK 1
#define ERROR 0	
#define TRUE 1		
#define FALSE 0
#define OVERFLOW -2
typedef int Status;//Status是函数的类型,其值是函数结果状态代码，如OK等
typedef int ElemType;//ElemType类型根据实际情况而定，这里假设为int
typedef struct {
	float p;
	int e;
}ElemType;
typedef struct {
	ElemType *elem;//自定义数据类型
	int length;
}SqList;
Status InitList(SqList* L){
	L->elem = (ElemType*)malloc(sizeof(ElemType) * MaxSize);//(ElemType*)存储的类型,强制类型转换 sizeof(ElemType)*MaxSize分配的内存
	if (!L->elem) return OVERFLOW;//分配失败
	L->length = 0;
	return OK;
}//初始化线性表
void DestroyList(SqList* L) {
	if(L->elem)  free(L->elem);
	L->elem = NULL;
	L->length = 0;
}//销毁线性表
void ClearList(SqList* L) {
	L->length = 0;
}//清空线性表
int GetLength(SqList *L) {
	return L->length;
}//求线性表长度
int IsEmpty(SqList *L) {
	if (L->length == 0) return 1;
	else return 0;
}//判断线性表是否为空
int GetElem(SqList *L, int i, ElemType *e) {
	if (i < 1 || i > L->length) return ERROR;
	*e = L->elem[i - 1];
	return OK;
}//获取线性表元素
int LocateElem(SqList *L, ElemType e) {
	int i;
	for (i = 0; i < L->length; i++) {
		if (L->elem[i].p == e.p && L->elem[i].e == e.e) return i + 1;
	}
	return 0;
}//按值查找线性表元素
void ListInsert(SqList *L, int i, ElemType e) {
	int j;
	if (i < 1 || i > L->length + 1) return ERROR;
	if (L->length >= MaxSize) return ERROR;
	for (j = L->length; j >= i; j--) {
		L->elem[j] = L->elem[j - 1];
	}
	L->elem[i - 1] = e;
	L->length++;
	return OK;
}//在线性表中插入元素
void ListDelete(SqList *L, int i) {
	int j;
	if (i < 1 || i > L->length) return ERROR;
	for (j = i; j < L->length; j++) {
		L->elem[j - 1] = L->elem[j];
	}
	L->length--;
	return OK;
}//在线性表中删除元素
int main() {
	SqList *L;
	return 0;
}