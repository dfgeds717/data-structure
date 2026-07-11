#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define OK 1
#define ERROR 0	
#define TRUE 1		
#define FALSE 0
#define OVERFLOW -2
#define MaxSize 20
typedef int KeyType;
typedef int InfoType;
typedef struct{
	KeyType key;
	InfoType OtherInfo;
}RedType;
typedef struct {
	RedType r[MaxSize + 1];
	int length;
}SqList;
void InsertSort(SqList* L)
{
	int i, j;
	RedType temp;
	for (i = 2; i <= L->length; i++){
		if (L->r[i].key < L->r[i - 1].key){
			temp = L->r[i];
			j = i - 1;
			while (j > 0 && L->r[j].key > temp.key){
				L->r[j + 1] = L->r[j];
				j--;
			}
			L->r[j + 1] = temp;
		}
	}
}
void BInsertSort(SqList* L)
{
	int i, j, low, high, mid;
	RedType temp;
	for (i = 2; i <= L->length; i++) {
		if (L->r[i].key < L->r[i - 1].key) {
			temp = L->r[i];
			low = 1;
			high = i - 1;
			while (low <= high) {
				mid = (low + high) / 2;
				if (temp.key < L->r[mid].key)
					high = mid - 1;
				else
					low = mid + 1;
			}
			for (j = i - 1; j >= high + 1; j--)
				L->r[j + 1] = L->r[j];
			L->r[high + 1] = temp;
		}
	}
}
void ShellInsert(SqList* L, int dk)
{
	int i, j;
	RedType temp;
	for (i = dk + 1; i <= L->length; i++) {
		if (L->r[i].key < L->r[i - dk].key) {
			temp = L->r[i];
			j = i - dk;
			while (j > 0 && L->r[j].key > temp.key) {
				L->r[j + dk] = L->r[j];
				j -= dk;
			}
			L->r[j + dk] = temp;
		}
	}
}
void ShellSort(SqList* L, int dlta[], int t)
{
	int k;
	for (k = 0; k < t; k++)
		ShellInsert(L, dlta[k]);
}
void BubbleSort(SqList* L)
{
	int i, j;
	RedType temp;
	for (i = 1; i < L->length; i++)
		for (j = 1; j <= L->length - i; j++)
			if (L->r[j].key > L->r[j + 1].key) {
				temp = L->r[j];
				L->r[j] = L->r[j + 1];
				L->r[j + 1] = temp;
			}
}

void QuickSort(SqList* L, int low, int high)
{
	int i, j;
	RedType temp;
	if (low < high) {
		i = low;
		j = high;
		temp = L->r[low];
		while (i < j) {
			while (i < j && L->r[j].key >= temp.key)
				j--;
			if (i < j) {
				L->r[i] = L->r[j];
				i++;
			}
			while (i < j && L->r[i].key <= temp.key)
				i++;
			if (i < j) {
				L->r[j] = L->r[i];
				j--;
			}
		}
		L->r[i] = temp;
		QuickSort(L, low, i - 1);
		QuickSort(L, i + 1, high);
	}
}
void SelectSort(SqList* L)
{
	int i, j, min;
	RedType temp;
	for (i = 1; i < L->length; i++) {
		min = i;
		for (j = i + 1; j <= L->length; j++)
			if (L->r[j].key < L->r[min].key)
				min = j;
		if (min != i) {
			temp = L->r[i];
			L->r[i] = L->r[min];
			L->r[min] = temp;
		}
	}
}