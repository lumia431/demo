#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include <iostream>
#include <string>
#include "Gragh.hpp"
using namespace std;
int visited[127];
void DFSTraverse(Graph G, int v) {
	Edge *p; //辅助结点 
	cout << "(" << v << "," << G.nodeList[v].data << ")" << ' '; //输出顶点信息 
	visited[v] = 1;
	p = G.nodeList[v].firstEdge; //访问第v个顶点
	while (p != NULL) {
		if (visited[p->aimNode] == 0) {
			DFSTraverse(G, p->aimNode);
		}
		p = p->nextEdge;
	}
}

//广度优先遍历
void BFSTraverse(Graph G, int v) {
	int i, j, visited[MAX]; //辅助变量、标志数组 
	Edge *p; //辅助结点 
	int queue[MAX], front = 0, rear = 0; //定义循环队列  
	for (i = 0; i < G.n; i++) {
		visited[i] = 0; //标志数组信息初始化 
	}
	cout << "(" << v << "," << G.nodeList[v].data << ")" << ' '; //输出顶点信息 
	visited[v] = 1; //对应顶点的标志置为1 
	rear = (rear + 1) % MAX; //队尾指针后移 
	queue[rear] = v; //查找的顶点对应序号入队列 
	//循环遍历 
	while (front != rear) {
		front = (front + 1) % MAX; //队头指针后移
		j = queue[front]; //从队列中取出顶点对应序号 
		p = G.nodeList[j].firstEdge; //取对应序号的顶点信息 
		while (p != NULL) {
			if (visited[p->aimNode] == 0) {
				visited[p->aimNode] = 1;
				cout << "(" << p->aimNode << "," << G.nodeList[p->aimNode].data << ")" << ' '; //输出顶点信息 
				rear = (rear + 1) % MAX; //队尾指针后移 
				queue[rear] = p->aimNode; //查找的顶点对应序号入队列
			}
			p = p->nextEdge;
		}
	}
}

//主函数 
int main() {
	Graph G; //定义图结构变量 
	int v1, v2, choose;
	cout << "请选择：0-退出；1-创建有向图（采用邻接表存储结构）；2-深度优先遍历；3-广度优先遍历" << endl;
	cin >> choose;
	while (choose != 0) {
		switch (choose) {
		case 1: {
			createGraph(G); //创建有向图 
			printGraph(G); //输出 
			break;
		}
		case 2: {
			cout << "输入从哪个顶点开始遍历(序号从0开始)：";
			cin >> v1;
			DFSTraverse(G, v1);
			for (int i = 0; i < G.n; i++) {
				visited[i] = 0; //标志数组信息初始化
			}
			cout << endl;
			break;
		}
		//case 3: {
		//	cout << "输入从哪个顶点开始遍历(序号从0开始)：";
		//	cin >> v2;
		//	BFSTraverse(G, v2);
		//	cout << endl;
		//	break;
		//}
		default:cout << "输入错误，请重新选择！" << endl;
		}
		cout << "请选择：0-退出；1-创建有向图（采用邻接表存储结构）；2-深度优先遍历；3-广度优先遍历" << endl;
		cin >> choose;
	}
}