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
	int adjvex;//�洢���ڽӵ�վ��λ�� 
	int samebus;//�洢���ڽӹ�ϵ�����ĸ�����·���� 
	struct ArcNode*nextarc;//�洢��һ���ڽӵ�վ 
	int weight;//��¼���룬�������ھ�Ϊ1
}ArcNode;
typedef struct VNode{
	string data;//��¼��վ�� 
	ArcNode *firstarc;//�� 
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList vertices; //�洢���г�վ��Ϣ 
	int vexnum;
}ALGraph;


