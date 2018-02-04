#include"func_传感器.h"

//迪杰斯特拉算法的实现

typedef bool PathMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 
typedef float ShortPathTable[MAX_VERTEX_NUM]; 
void ShortestPath_DIJ(ALGraph &G, int v0, PathMatrix &P, ShortPathTable &D)
{ 
  
  
  int v, w, i, j;
  float min;
  bool final[MAX_VERTEX_NUM];
  for(v=0; v<G.vexnum; v++)
  { 
  	final[v]=false; 
    D[v]=FLT_MAX; 
    for(w=0; w<G.vexnum; w++)
      P[v][w]=false; 
  }  
  for(ArcNode* T = G.vertices[v0].firstarc;T;T=T->nextarc)
  {
  	w = T->adjvex;
  	D[w] = T->inof->weight;
    P[w][v0]=P[w][w]=true;
  }  

  D[v0]=0; 
  final[v0]=true; 
  
  for(i=1; i<linkNum; i++) 
  { 
  	//找最小值并设为永久标号 
    min=FLT_MAX; 
    for(w=0; w<G.vexnum; w++) 
    if(!final[w] && D[w]<min) 
    { 

        v=w; 
        min=D[w]; 
      }
  //  cout<<"min:"<<v<<endl;
   // getch();
    final[v]=true; 
    
    //updata array D and array P, 
  	for(ArcNode* T = G.vertices[v].firstarc;T;T=T->nextarc)
	{
		//cout<<"updata"<<v<<endl;
		w = T->adjvex;
		if(!final[w]&&min<FLT_MAX&&(min+T->inof->weight<D[w]))
		{ 
	       	D[w]=min+T->inof->weight;
	        for(j=0; j<G.vexnum; j++)
	        P[w][j]=P[v][j];
	       	P[w][w]=true;
     	}
	}
    
  }

  
}

