#include <stdio.h>
#include <stdlib.h>
#define MaxSize 100
#define OK 1
#define ERROR 0	
#define TRUE 1		
#define FALSE 0
#define OVERFLOW -2
#define MVNum 100
#define MaxInt 32767
typedef int Status;
typedef int ArcType;
typedef char VerTexType;
typedef struct {
	VerTexType vexs[MVNum];//顶点表
	ArcType arcs[MVNum][MVNum];//邻接矩阵
	int vexnum, arcnum;//图的当前顶点数和弧数
}AMGraph;
int LocateVex(AMGraph G, VerTexType v) {
	int i;
	for (i = 0; i < G.vexnum; i++) {
		if (G.vexs[i] == v) return i;//找到顶点v，返回其下标
	}
	return -1;//未找到顶点v，返回-1
}//返回顶点v在图G中的位置
Status CreateUDN(AMGraph* G) {
	int i, j, k;
	printf("请输入顶点数和弧数：");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	printf("请输入顶点信息：");
	for (i = 0; i < G->vexnum; i++) {
		scanf(" %c", &G->vexs[i]);//输入顶点信息
	}
	//初始化邻接矩阵
	for (i = 0; i < G->vexnum; i++) {
		for (j = 0; j < G->vexnum; j++) {
			G->arcs[i][j] =MaxInt ;
		}
	}
	printf("请输入弧的信息（格式：<vi,vj>）,w：");//还有权值的输入
	for (k = 0; k < G->arcnum; k++) {
		char vi, vj;
		int w;
       scanf(" <%c,%c>,%d", &vi, &vj, &w);//输入弧的信息（修正格式）
		i = LocateVex(*G, vi);
		j = LocateVex(*G, vj);
		if (i == -1 || j == -1) {
			printf("输入的顶点不存在！\n");
			return ERROR;
		}
		G->arcs[i][j] = w;//有弧
		G->arcs[j][i] = w;//无向图对称赋值
	}
	return OK;
}//创建无向图
typedef struct ArcNode {
	int adjvex;//邻接点域，存储该弧所指向的顶点的位置
	struct ArcNode* nextarc;//链域，指向下一个邻接点
	ArcType info;//弧相关信息，如权值等
}ArcNode;
typedef struct VNode {
	VerTexType data;
	ArcNode* firstarc;
}VNode, * AdjList[MVNum];//顶点表，类型为VNode的数组AdjList，数组元素是VNode*类型
typedef struct {
	AdjList vertices;//邻接表
	int vexnum, arcnum;//图的当前顶点数和弧数
} ALGraph;
/* 在邻接表表示的图中查找顶点位置（因为 AdjList 元素是 VNode*） */
int LocateVex_AL(ALGraph G, VerTexType v) {
	int i;
	for (i = 0; i < G.vexnum; i++) {
		if (G.vertices[i] && G.vertices[i]->data == v) return i;
	}
	return -1;
}
Status CreateUDG(ALGraph* G) {
	int i, j, k;
	printf("请输入顶点数和弧数：");
	scanf("%d%d", &G->vexnum, &G->arcnum);
	printf("请输入顶点信息：");
	for (i = 0; i < G->vexnum; i++) {
     /* 为每个顶点分配内存并用指针访问成员 */
		G->vertices[i] = (VNode*)malloc(sizeof(VNode));
		scanf(" %c", &G->vertices[i]->data);//输入顶点信息
		G->vertices[i]->firstarc = NULL;//初始化邻接表
	}
	printf("请输入弧的信息（格式：<vi,vj>）,w：");//还有权值的输入
	for (k = 0; k < G->arcnum; k++) {
		char vi, vj;
		int w;
       scanf(" <%c,%c>,%d", &vi, &vj, &w);//输入弧的信息（修正格式）
		i = LocateVex_AL(*G, vi);
		j = LocateVex_AL(*G, vj);
		//创建弧节点并插入邻接表
		ArcNode* arc1 = (ArcNode*)malloc(sizeof(ArcNode));
		arc1->adjvex = j;
		arc1->info = w;
        arc1->nextarc = G->vertices[i]->firstarc;
		G->vertices[i]->firstarc = arc1;//将弧节点插入vi的邻接表
		ArcNode* arc2 = (ArcNode*)malloc(sizeof(ArcNode));
		arc2->adjvex = i;
		arc2->info = w;
        arc2->nextarc = G->vertices[j]->firstarc;
		G->vertices[j]->firstarc = arc2;//将弧节点插入vj的邻接表
	}
	return OK;
}//创建无向图
void DFS(AMGraph G, int v) {
	printf("%c ", G.vexs[v]);//访问顶点v	
	visited[v] = TRUE;//标记顶点v已访问
	for (w = 0; w < G.vexnum; w++) {
		if(G.arcs[v][w]!=MaxInt&&!visited[w]){//如果v和w邻接且w未访问
			DFS(G,w);//递归访问w
		}
	}
}
void BFS(AMGraph G, int v) {
	int queue[MVNum], front = 0, rear = 0;//定义队列
	printf("%c ", G.vexs[v]);//访问顶点v
	visited[v] = TRUE;//标记顶点v已访问
	queue[rear++] = v;//入队
	while (front != rear) {
		int u = queue[front++];//出队
		for (w = 0; w < G.vexnum; w++) {
			if(G.arcs[u][w]!=MaxInt&&!visited[w]){//如果u和w邻接且w未访问
				printf("%c ", G.vexs[w]);//访问顶点w
				visited[w] = TRUE;//标记顶点w已访问
				queue[rear++] = w;//入队
			}
		}
	}
}//广度优先搜索算法