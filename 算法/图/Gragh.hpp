#pragma once
#include <iostream>
using namespace std;
#define MAX 20 //定义常量值为20 

struct Edge {
	int weight;
	int aimNode;//指向的节点
	Edge* nextEdge;
};
typedef struct Node {
	char data; //点名 
	Edge *firstEdge; //从该点出去的第一条边，该点出去的其他的边串在后面
};
//定义图的邻接表存储结构 
typedef struct {
	Node nodeList[127]; //节点数组 
	int n; //图的顶点数
	int e; //图的边数 
}Graph;

//建立图的邻接表
void createGraph(Graph &G) {
	int i, j, k, w; //辅助变量 
	cout << "输入图的顶点数:";
	cin >> G.n;
	cout << "输入图的边数:";
	cin >> G.e;
	cout << endl; //换行 
	cout << "输入图的各顶点(存储序号从0开始)：" << endl;
	for (i = 0; i < G.n; i++) {  //生成有n个顶点的顶点表
		cout << "第" << i << "个顶点信息：";
		cin >> G.nodeList[i].data; //顶点数据存入表头 
		G.nodeList[i].firstEdge = NULL; //边表头指针域置为空 
	}
	cout << endl; //换行 
	cout << "输入图中的边，顶点序号从0开始:" << endl;
	Edge* tempEdge;
	for (k = 0; k < G.e; k++) {
		cout << endl; //换行 
		cout << "输入第" << k + 1 << "条边:" << endl;
		cout << "输入出发顶点的序号：";
		cin >> i;
		cout << "输入指向顶点的序号:";
		cin >> j;
		cout << "输入权值:";
		cin >> w;
		//邻接表存储连接 
		tempEdge = new Edge; //分配存储空间 
		tempEdge->weight = w;
		tempEdge->aimNode = j;
		//指针加入头的作法，让原来的头节点称为新节点的儿子，在让新的节点成为头
		tempEdge->nextEdge = G.nodeList[i].firstEdge; //新的结点的指针域置为空 
		G.nodeList[i].firstEdge = tempEdge; //新结点信息依次存入邻接表中 
	}
}

//输出邻接表
void printGraph(Graph G) {
	int i; //辅助变量 
	Edge *edge; //辅助结点 
	cout << "邻接表中的存储内容如下所示：" << endl;
	for (i = 0; i < G.n; i++) {
		cout << i << ' ' << G.nodeList[i].data; //输出表头结点的数据 
		edge = G.nodeList[i].firstEdge; //指向下一结点 
		while (edge != NULL) {
			cout << "--->" << edge->aimNode << ' '; //顺次输出结点信息 
			edge = edge->nextEdge;
		}
		cout << endl; //换行 
	}
}