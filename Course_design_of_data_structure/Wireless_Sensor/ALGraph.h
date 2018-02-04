#include<stdio.h>
#include<iostream>
#include<malloc.h>
#include<stack>
#include<string>
#include<conio.h>
#include<math.h>
#include<time.h> 
#include<stdio.h>
#include<stdlib.h>
#include<float.h>//FLT_MAX

#define MAX_VERTEX_NUM 1000 
using namespace std;

typedef struct Location{//坐标 
	int x;
	int y;
	void set(int xx, int yy){x = xx; y = yy;	}
	void operator = (Location l)
	{
		x = l.x;
		y = l.y;
	}
	bool operator < (const Location l)
	{
		if(x<l.x) return true;
		else if(x==l.x&&y<l.y) return true;
		else return false;
	}
}Location;
typedef struct Weight{//记录权值以及权值的平方 
	float weight;
	int w_weight;
	void set(int ww)
	{
		w_weight = ww;
		weight = (float)sqrt((double)w_weight);
	}
}Weight;

typedef int Status;
typedef Location VertexType;

typedef Weight InfoType;
typedef struct ArcNode{
	int adjvex;//存储当前邻接顶点在顶点向量中的位置 
	struct ArcNode*nextarc;//存储下一个邻接点 
	InfoType *inof;//存储权值信息 
}ArcNode;
typedef struct VNode{
	VertexType data;//储存顶点位置信息 
	ArcNode *firstarc;//记录第一个邻接顶点的位置 
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList vertices; //储存所有顶点连接情况 
	int vexnum;
}ALGraph;

bool d[100][100];
bool link[1000];
int locate[100][100];
int linkNum = 0;
