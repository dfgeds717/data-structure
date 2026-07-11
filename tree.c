#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define OK 1
#define ERROR 0	
#define TRUE 1		
#define FALSE 0
#define OVERFLOW -2
typedef int Status;
typedef char TElemType;
typedef struct BiNode {
	TElemType data;
	struct BiNode* lchild, * rchild;
}BiNode, *BiTree;
Status PreOrderTraverse(BiTree T) {
	if (T) {
		printf("%c ", T->data);//访问根节点
		PreOrderTraverse(T->lchild);//递归访问左子树
		PreOrderTraverse(T->rchild);//递归访问右子树
	}
	return OK;
}//先序遍历二叉树
Status InOrderTraverse(BiTree T) {
	if (T) {
		InOrderTraverse(T->lchild);//递归访问左子树
		printf("%c ", T->data);//访问根节点
		InOrderTraverse(T->rchild);//递归访问右子树
	}
	return OK;
}//中序遍历二叉树
Status PostOrderTraverse(BiTree T) {
	if (T) {
		PostOrderTraverse(T->lchild);//递归访问左子树
		PostOrderTraverse(T->rchild);//递归访问右子树
		printf("%c ", T->data);//访问根节点
	}
	return OK;
}//后序遍历二叉树
Status InOrderTraverseNonRecursion(BiTree T) {
	BiNode* stack[MaxSize];
	int top = -1;
	BiNode* p = T;
	while (p || top != -1) {
		while (p) {
			stack[++top] = p;//将当前节点入栈
			p = p->lchild;//访问左子树
		}
		if (top != -1) {
			p = stack[top--];//弹出栈顶节点
			printf("%c ", p->data);//访问根节点
			p = p->rchild;//访问右子树
		}
	}
	return OK;
}//非递归中序遍历二叉树
Status LevelOrderTraverse(BiTree T) {
	BiNode* queue[MaxSize];
	int front = 0, rear = 0;
	BiNode* p = T;
	if (p) {
		queue[rear++] = p;//将根节点入队
	}
	while (front != rear) {
		p = queue[front++];//出队
		printf("%c ", p->data);//访问当前节点
		if (p->lchild) {
			queue[rear++] = p->lchild;//将左子树入队
		}
		if (p->rchild) {
			queue[rear++] = p->rchild;//将右子树入队
		}
	}
	return OK;
}//层序遍历二叉树
Status CreateBiTree(BiTree* T) {
	char ch;
	scanf("%c", &ch);
	if (ch == '#') {
		*T = NULL;//空树
	}
	else {
		*T = (BiNode*)malloc(sizeof(BiNode));
		if (!*T) {
			printf("Memory overflow!\n");
			exit(OVERFLOW);
		}
		(*T)->data = ch;//创建根节点
		CreateBiTree(&(*T)->lchild);//递归创建左子树
		CreateBiTree(&(*T)->rchild);//递归创建右子树
	}
	return OK;
}//创建二叉树
int Copy (BiTree T, BiTree* NewT) {
	if (T) {
		*NewT = (BiNode*)malloc(sizeof(BiNode));
		if (!*NewT) {
			printf("Memory overflow!\n");
			exit(OVERFLOW);
		}
		(*NewT)->data = T->data;//复制当前节点
		Copy(T->lchild, &(*NewT)->lchild);//递归复制左子树
		Copy(T->rchild, &(*NewT)->rchild);//递归复制右子树
	}
	else {
		*NewT = NULL;//空树
	}
	return OK;
}//复制二叉树
int Depth(BiTree T) {
	if (!T) return 0;//空树深度为0
	int m = Depth(T->lchild);//左子树深度
	int n= Depth(T->rchild);//右子树深度
	if (m > n) return m + 1;
	else return n + 1;//返回较大深度加1
}//求二叉树的深度
int NodeCount(BiTree T) {
	if (!T) return 0;//空树节点数为0
	return NodeCount(T->lchild) + NodeCount(T->rchild) + 1;//返回左右子树节点数之和加1
}//求二叉树的节点数
int LeadCount(BiTree T) {
	if (!T) return 0;//空树叶子节点数为0
	if (!T->lchild && !T->rchild) return 1;//当前节点为叶子节点
	return LeadCount(T->lchild) + LeadCount(T->rchild);//返回左右子树叶子节点数之和
}//求二叉树的叶子节点数

typedef struct {
	int weight;
	int parent, lch, rch;
}HTNode,*HuffmanTree;


void CreatHuffmanTree(HuffmanTree* HT, int n) {
	// 若节点数≤1，无需建树
	if (n <= 1) return;

	int m = 2 * n - 1;  // 哈夫曼树总节点数（n个叶子 + n-1个内部节点）

	// 动态分配内存：m+1个节点（下标0未使用，方便从1开始索引）
	*HT = (HTNode*)malloc((m + 1) * sizeof(HTNode));
	if (*HT == NULL) {  // 内存分配失败处理
		printf("内存分配失败！\n");
		exit(1);
	}

	// 初始化所有节点的 lch、rch、parent 为 0（表示“无”）
	for (int i = 1; i <= m; ++i) {
		(*HT)[i].lch = 0;
		(*HT)[i].rch = 0;
		(*HT)[i].parent = 0;
	}

	// 输入前 n 个叶子节点的权重
	printf("请输入 %d 个叶子节点的权重：", n);
	for (int i = 1; i <= n; ++i) {
		scanf("%d", &(*HT)[i].weight);
	}
	int s1, s2;  // 用于存储每次选择的两个最小权重节点的下标
	for (int i = n + 1; i <= m; i++) {
		Select(*HT, i - 1, &s1, &s2);  // 从前 i-1 个节点中选择权重最小的两个节点 s1 和 s2
		(*HT)[s1].parent = i;  // 将 s1 的父节点设置为 i
		(*HT)[s2].parent = i;  // 将 s2 的父节点设置为 i
		(*HT)[i].lch = s1;     // 将 s1 设置为 i 的左子树
		(*HT)[i].rch = s2;     // 将 s2 设置为 i 的右子树
		(*HT)[i].weight = (*HT)[s1].weight + (*HT)[s2].weight;  // 设置 i 的权重为 s1 和 s2 权重之和
	}
}//创建哈夫曼树
void CreateHuffmanCode(HuffmanTree HT, char** HC, int n) {
	char* cd = (char*)malloc(n * sizeof(char));  // 临时数组存储当前节点的哈夫曼编码
	cd[n - 1] = '\0';  // 哈夫曼编码以 '\0' 结尾
	for (int i = 1; i <= n; i++) {
		int start = n - 1;  // 从 cd 的末尾开始构建哈夫曼编码
		int c = i;          // 当前节点的下标
		int f = HT[c].parent;  // 当前节点的父节点下标
		while (f != 0) {    // 当父节点存在时
			if (HT[f].lch == c) {  // 如果当前节点是父节点的左子树
				cd[--start] = '0';  // 在 cd 中添加 '0'
			} else {                // 如果当前节点是父节点的右子树
				cd[--start] = '1';  // 在 cd 中添加 '1'
			}
			c = f;  // 将当前节点更新为父节点，继续向上遍历
			f = HT[c].parent;  // 更新父节点下标
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));  // 为 HC[i] 分配内存，存储最终的哈夫曼编码
		strcpy(HC[i], &cd[start]);  // 将构建好的哈夫曼编码复制到 HC[i]
	}
	free(cd);  // 释放临时数组 cd 的内存
}//生成哈夫曼编码