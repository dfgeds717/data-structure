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
#define MAXLEN 255
typedef struct {
	char ch[MAXLEN+1];//存储串的数组
	int length;//串的长度
}SString;
#define CHUNKSIZE 80
typedef struct Chunk {
	char ch[CHUNKSIZE];//存储串的数组
	struct Chunk* next;//指向下一个结点的指针
}Chunk;
typedef struct {
	Chunk* head, * tail;//指向串的结点
	int curlen;//串的长度
}LString;
int Index_BF(SString S, SString T, int pos) {
	int i = pos, j = 1;
	while (i <= S.length && j <= T.length) {
		if (S.ch[i] == T.ch[j]) {
			i++;
			j++;
		}
		else {
			i = i - j + 2;//回退
			j = 1;//重新开始匹配
		}
	}
	if (j > T.length) return i - T.length;//匹配成功，返回位置
	else return 0;//匹配失败，返回0
}//BF算法求子串T在主串S中第pos个字符之后的位置


void get_next(SString T, int next[]) {
	int j = 1, k = 0;
	next[1] = 0;
	while (j < T.length) {
		if (k == 0 || T.ch[j] == T.ch[k]) {
			j++;
			k++;
			next[j] = k;
		}
		else k = next[k];
	}
}//求模式串T的next数组ababc
int Index_KMP(SString S, SString T, int pos) {
	int i = pos, j = 1;
	int next[MAXLEN + 1];
	//求模式串T的next数组
	next[1] = 0;
	for (j = 2; j <= T.length; j++) {
		int k = next[j - 1];
		while (k > 0 && T.ch[k + 1] != T.ch[j]) k = next[k];
		if (T.ch[k + 1] == T.ch[j]) k++;
		next[j] = k;
	}
	//KMP算法匹配
	i = pos, j = 1;
	while (i <= S.length && j <= T.length) {
		if (S.ch[i] == T.ch[j]) {
			i++;
			j++;
		}
		else if (j > 1) j = next[j - 1] + 1;//回退
		else i++;//主串指针后移
	}
	if (j > T.length) return i - T.length;//匹配成功，返回位置
	else return 0;//匹配失败，返回0
}//KMP算法求子串T在主串S中第pos个字符之后的位置