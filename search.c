#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define OK 1
#define ERROR 0	
#define TRUE 1		
#define FALSE 0
#define OVERFLOW -2
typedef int Status;
typedef int KeyType;
typedef int InfoType;
typedef struct {
	KeyType key;//关键字
	InfoType otherinfo;//其他数据项
}ElemType;
typedef struct {
	ElemType* R;//存储空间基址，动态分配数组
	int length;//当前长度
}SSTable;
int Search_Seq(SSTable ST, KeyType key) {
	int i;
	for (i = 0; i < ST.length; i++) {
		if (ST.R[i].key == key) return i;//找到关键字，返回其下标
	}
	return -1;//未找到关键字，返回-1
}//顺序查找
int Search_Bin(SSTable ST, KeyType key) {
	int low = 0, high = ST.length - 1, mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (ST.R[mid].key == key) return mid;//找到关键字，返回其下标
		else if (ST.R[mid].key > key) high = mid - 1;//关键字在左半区
		else low = mid + 1;//关键字在右半区
	}
	return -1;//未找到关键字，返回-1
}//二分查找（前提是表中元素按关键字有序）
typedef struct BSTNode {
	ElemType data;//节点数据
	struct BSTNode* lchild, * rchild;//左右孩子指针
}BSTNode, * BSTree;
BSTree Search_BST(BSTree T, KeyType key) {
	if (!T) return NULL;//树空，未找到关键字
	if (T->data.key == key) return T;//找到关键字，返回节点指针
	else if (T->data.key > key) return Search_BST(T->lchild, key);//关键字在左子树
	else return Search_BST(T->rchild, key);//关键字在右子树
}//二叉排序树查找（前提是树中元素按关键字有序）