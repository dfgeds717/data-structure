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
typedef struct Lnode {
	ElemType data;
	struct Lnode* next;//节点的指针域
}Lnode, * LinkList;//ListNode结构体定义，LinkList为指向ListNode的指针类型
Status InitList(LinkList L) {
	L = (LinkList)malloc(sizeof(Lnode));//分配一个头结点
	if (!L) return OVERFLOW;//分配失败
	L->next = NULL;//头结点的指针域置空
	return OK;
}//初始化链表
int Listempty(LinkList L) {
	if (L->next == NULL) return TRUE;//链表为空
	else return FALSE;//链表不空
}//判断链表是否为空
Status DestroyList(LinkList L) {
	Lnode* p;
	while (L) {
		p = L;
		L = L->next;//L指向下一个结点
		free(p);//释放当前结点
	}
	L->next = NULL;
	return OK;
}//销毁链表
Status ClearList(LinkList L) {
	Lnode* p = L->next;
	L->next = NULL;//清空链表
	while (p) {
		Lnode* q = p;
		p = p->next;//p指向下一个结点
		free(q);//释放当前结点
	}
	return OK;
}//清空链表
int GetLength(LinkList L) {
	int count = 0;
	Lnode* p = L->next;//p指向第一个结点
	while (p) {
		count++;
		p = p->next;//p指向下一个结点
	}
	return count;
}//求链表长度
int GetElem(LinkList L, int i, ElemType* e) {
	int count = 0;
	Lnode* p = L->next;//p指向第一个结点
	while (p) {
		count++;
		if (count == i) {
			*e = p->data;//将第i个结点的数据赋值给e
			return OK;
		}
		p = p->next;//p指向下一个结点
	}
	return ERROR;//没有找到第i个结点
}//获取链表元素
Status LocateElem(LinkList L, ElemType e) {
	int count = 0;
	Lnode* p = L->next;//p指向第一个结点
	while (p) {
		count++;
		if (p->data == e) return count;//返回第i个结点的位置
		p = p->next;//p指向下一个结点
	}
	return 0;//没有找到元素e
}//按值查找链表元素
Status ListInsert(LinkList L, int i, ElemType e) {
	int count = 0;
	Lnode* p = L;//p指向头结点
	while (p) {
		count++;
		if (count == i) {
			Lnode* s = (Lnode*)malloc(sizeof(Lnode));//分配一个新结点
			if (!s) return OVERFLOW;//分配失败
			s->data = e;//将e赋值给新结点的数据域
			s->next = p->next;//将新结点的指针域指向p的下一个结点
			p->next = s;//将p的指针域指向新结点
			return OK;
		}
		p = p->next;//p指向下一个结点
	}
	return ERROR;//没有找到第i个结点
}//插入链表元素
Status ListDelete(LinkList L, int i, ElemType* e) {
	int count = 0;
	Lnode* p = L;//p指向头结点
	while (p->next) {
		count++;
		if (count == i) {
			Lnode* q = p->next;//q指向第i个结点
			*e = q->data;//将第i个结点的数据赋值给e
			p->next = q->next;//将p的指针域指向q的下一个结点
			free(q);//释放第i个结点
			return OK;
		}
		p = p->next;//p指向下一个结点
	}
	return ERROR;//没有找到第i个结点
}//删除链表元素
void CreateList_H(LinkList L, int n) {
	L = (LinkList)malloc(sizeof(Lnode));//分配一个头结点
	L->next = NULL;//头结点的指针域置空
	for (int i = 0; i < n; i++) {
		Lnode* p= (Lnode*)malloc(sizeof(Lnode));//分配一个新结点
		scanf("%d", &p->data);//输入新结点的数据
		p->next = L->next;
		L->next =p ;//p指向新结点
	}
}//创建链表;头插法
void CreateList_R(LinkList L, int n) {
	L = (LinkList)malloc(sizeof(Lnode));//分配一个头结点
	L->next = NULL;//头结点的指针域置空
	Lnode* r = L;//r指向尾结点
	for (int i = 0; i < n; i++) {
		Lnode* p = (Lnode*)malloc(sizeof(Lnode));//分配一个新结点
		scanf("%d", &p->data);//输入新结点的数据
		r->next = p;//将尾结点的指针域指向新结点
		r = p;//r指向新结点
	}
	r->next = NULL;//将尾结点的指针域置空
}//创建链表;尾插法
int main() {
	LinkList L;
	Lnode* p;//定义一个指针p,等同于LinkList p;
}