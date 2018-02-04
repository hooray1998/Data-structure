#include<stdio.h>
#include<iostream>
#include<malloc.h>
#include<stack>
#include<fstream>
#include<string>
#include<conio.h>
#include<math.h>
#include<time.h> 
#include<stdio.h>
#include<stdlib.h>
#include<float.h>//FLT_MAX

#define MAX_VERTEX_NUM 1000 
using namespace std;



typedef struct ArcNode{
	int adjvex;//存储该邻接的站的位置 
	int samebus;//存储该邻接关系是在哪个公交路线上 
	struct ArcNode*nextarc;//存储下一个邻接的站 
	int weight;//记录距离，该题相邻均为1
}ArcNode;
typedef struct VNode{
	string data;//记录车站名 
	ArcNode *firstarc;//出 
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList vertices; //存储所有车站信息 
	int vexnum;
}ALGraph;


