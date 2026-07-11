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
typedef struct Stack {
	ElemType* base;//栈底指针
	ElemType* top;//栈顶指针
	int stacksize;//栈的容量
}*SqStack;
void InitStack(SqStack S ) {
	S->base = (ElemType*)malloc(MaxSize * sizeof(ElemType));
	if (!S->base) {
		printf("Memory overflow!\n");
		exit(OVERFLOW);
	}
	S->top = S->base;//栈顶指针指向栈底
	S->stacksize = MaxSize;//栈的容量
}//初始化栈
Status StackEmpty(SqStack S) {
	if (S->top == S->base) return TRUE;//栈空
	else return FALSE;//栈不空
}//判断栈是否为空
int StackLength(SqStack S) {
	return S->top - S->base;//栈的长度
}//求栈的长度
Status ClearStack(SqStack S) {
	S->top = S->base;//栈顶指针指向栈底
	return OK;
}//清空栈
Status DestroyStack(SqStack S) {
	free(S->base);//释放栈底指针
	S->base = NULL;
	S->top = NULL;
	S->stacksize = 0;
	return OK;
}//销毁栈
Status Push(SqStack S, ElemType e) {
	if (S->top - S->base >= S->stacksize) {//栈满
		S->base = (ElemType*)realloc(S->base, (S->stacksize + MaxSize) * sizeof(ElemType));
		if (!S->base) {
			printf("Memory overflow!\n");
			exit(OVERFLOW);
		}
		S->top = S->base + S->stacksize;//更新栈顶指针
		S->stacksize += MaxSize;//增加栈的容量
	}
	*S->top = e;
	S->top++;//将e压入栈顶
	return OK;
}//入栈
Status Pop(SqStack S, ElemType* e) {
	if (S->top == S->base) return ERROR;//栈空
	S->top--;//将栈顶指针下移
	*e = *S->top;//将栈顶元素赋值给e
	return OK;
}//出栈
int main() {
	SqStack S;
	return 0;
}