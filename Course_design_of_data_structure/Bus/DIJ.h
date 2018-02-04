#include"func_ALGraph.h"
//迪杰斯特拉算法的实现

typedef bool PathMatrix2[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; 
typedef float ShortPathTable[MAX_VERTEX_NUM]; 

bool esist(int *a, int n,int pa)//判断a数组里是否有pa元素 
{
	for(int j=0;j<n;j++)
	if(a[j]==pa) return true;
	
	return false;
	
}
void end(ALGraph &G, int v0, int vn,PathMatrix2 &P, ShortPathTable &D)
{
	
    	int a[100],n=0,pre=v0; 
    	int k=0;
    	for(int i=0;i<G.vexnum;i++)//存储经过的站的下标 
    	if(P[vn][i])
    	{
    		k=1;
    		a[n]=i;
			n++;
		}
		cout<<endl;
    	if(k==0)
    	cout<<"此路不通"<<endl;
    	//有序输出路线
		bool f[100]; 
		for(int i=0;i<n;i++) 
		{
			f[i] = false;
			if(a[i]==v0)
			f[i] = true;
		}
		int count=0;
		int prebus=0;
		cout<<"最少经过"<<n<<"站"<<endl; 
		cout<<"从 "<<G.vertices[v0].data<<" 出发";
		for(int i=0;i<n&&count!=n-1;i++)
    	{
    		if(!f[i])
    		{
    			ArcNode*p = G.vertices[pre].firstarc;
    			while(p)
    			{
    				if(p->adjvex==a[i])
    				{
    					if(p->samebus!=prebus) 
						{	
							cout<<endl;
							cout<<"换乘（"<<p->samebus<<"）";
    					}
    					prebus = p->samebus;
						cout<<G.vertices[a[i]].data<<"=>";
												
						f[i] = true;
						pre = a[i];
						count++;
						i=-1;
						break;
					}
					p = p->nextarc;
				}
    		}
		}
		cout<<endl;	
 } 

void ShortestPath_DIJ(ALGraph &G, int v0, int vn,PathMatrix2 &P, ShortPathTable &D)
{ 
  
  
  int v, w, i, j;
  int min;
  bool final[MAX_VERTEX_NUM];
  for(v=0; v<G.vexnum; v++)
  { 
  	final[v]=false; 
    D[v]=INT_MAX; 
    for(w=0; w<G.vexnum; w++)
      P[v][w]=false; 
  }  
  for(ArcNode* T = G.vertices[v0].firstarc;T;T=T->nextarc)
  {
  	w = T->adjvex;
  	D[w] = T->weight;
    P[w][v0]=P[w][w]=true;
  }  

  D[v0]=0; 
  final[v0]=true; 
  
  for(i=1; i<G.vexnum; i++) 
  { 
  	//找最小值并设为永久标号 
    min=INT_MAX; 
    for(w=0; w<G.vexnum; w++) 
    if(!final[w] && D[w]<min) 
    { 
        v=w; 
        min=D[w]; 
    }
    final[v]=true; 
    if(v==vn)//求出最短距离则跳出 
    {
		end(G,v0,vn,P,D);
    	break;
	}
    //updata array D and array P, 
  	for(ArcNode* T = G.vertices[v].firstarc;T;T=T->nextarc)
	{
		//cout<<"updata"<<v<<endl;
		w = T->adjvex;
		if(!final[w]&&min<INT_MAX&&(min+T->weight<D[w]))
		{ 
	       	D[w]=min+T->weight;
	        for(j=0; j<G.vexnum; j++)
	        P[w][j]=P[v][j];
	       	P[w][w]=true;
     	}
	}
  }
}

