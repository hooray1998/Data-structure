#include"DIJ.h"
int branch[MAX_VERTEX_NUM][2];//0用来存前一个，1存后一个。 
int energy = 0;
typedef struct dd{
	int adjvex;
	int lowcost;//耗能 
}CloseDge[MAX_VERTEX_NUM];
CloseDge closedge;

int minimum(CloseDge &c,int num)
{
	int k=num,i;
	int min;
	for(i=0;i<num;i++)
	{
		if(c[i].lowcost!=0)
		{
			k=i;
			min=c[i].lowcost;
			break;
		}
	}
	for(i=k+1;i<num;i++)
	{
		if(c[i].lowcost!=0&&c[i].lowcost<min)
		{
			min = c[i].lowcost;
			k = i;
		}
	}
	energy+=min;
	return k;
}

void MiniSpanTree_PRIM(ALGraph &G)
{
	int k = 0; 
	int num = G.vexnum;
	
	int j,i,w;
	for(j=0;j<G.vexnum;++j)
		if(j!=k)
		{
			closedge[j].adjvex = 0;
			closedge[j].lowcost = INT_MAX;
		}
	for(ArcNode* T = G.vertices[0].firstarc;T;T=T->nextarc)
	{
		w = T->adjvex;
		closedge[w].lowcost = T->inof->w_weight;
	}
	closedge[k].lowcost = 0;
//	puts("eee\n");
	for(i=1;i<linkNum;i++)
	{
		//puts("eeefor\n");
		k = minimum(closedge,num);
		
		branch[i-1][0] =  closedge[k].adjvex;
		branch[i-1][1] =  k;
		closedge[k].lowcost = 0;
		
		for(ArcNode* T = G.vertices[k].firstarc;T;T=T->nextarc)
		{
			w = T->adjvex;
			if(T->inof->w_weight<closedge[w].lowcost)
			{
				closedge[w].adjvex = k;
				closedge[w].lowcost = T->inof->w_weight;
			}
		}
		
		

	}
	ofstream out("最少消耗.txt");
	cout<<"平均最少费用为"<<(float)energy/(linkNum-1)<<endl;
	cout<<"建立以下"<<linkNum-1<<"条路线"<<endl;
	out<<"平均最少费用为"<<(float)energy/(linkNum-1)<<endl;
	out<<"建立以下"<<linkNum-1<<"条路线"<<endl;
	for(int i=0;i<linkNum-1;i++)
	{
		cout<<"传感器"<<branch[i][0]<<"与传感器"<<branch[i][1]<<endl; 
		out<<"传感器"<<branch[i][0]<<"与传感器"<<branch[i][1]<<endl; 
	}	
	out.close();
	
 } 


