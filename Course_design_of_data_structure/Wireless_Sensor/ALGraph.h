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

typedef struct Location{//���� 
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
typedef struct Weight{//��¼Ȩֵ�Լ�Ȩֵ��ƽ�� 
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
	int adjvex;//�洢��ǰ�ڽӶ����ڶ��������е�λ�� 
	struct ArcNode*nextarc;//�洢��һ���ڽӵ� 
	InfoType *inof;//�洢Ȩֵ��Ϣ 
}ArcNode;
typedef struct VNode{
	VertexType data;//���涥��λ����Ϣ 
	ArcNode *firstarc;//��¼��һ���ڽӶ����λ�� 
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct{
	AdjList vertices; //�������ж���������� 
	int vexnum;
}ALGraph;

bool d[100][100];
bool link[1000];
int locate[100][100];
int linkNum = 0;
