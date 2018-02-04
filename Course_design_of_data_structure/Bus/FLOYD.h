#include"func_MGraph.h"
typedef bool PathMatrix[MAX_BUS_NUM][MAX_BUS_NUM][MAX_BUS_NUM]; 
typedef int DistancMatrix[MAX_BUS_NUM][MAX_BUS_NUM]; 


void findnext(MGraph &G,int a[10],int i,int n)//。a数组已存所有经过的车辆，该函数可以不断寻找找到下一个换乘的车
 {
 	int v[10],pre;
 	for(int k=0;k<n;k++)
 	{
 		v[k] = 0;
 		if(a[k]==i)
		 {
		 	pre = k;
		 	v[k]=1;
		  } 
 		
	}
	for(int jj=1;jj<n;jj++)
 	for(int j=0;j<n;j++)
 	{
 		if(!v[j]&&G.arcs[a[pre]][a[j]].adj==1)
	 	{
	 		v[j]=1;
	 		cout<<"从(";
	 		for(int i=0;i<G.arcs[a[pre]][a[j]].CPt.CPNumber;i++)
	 		cout<<G.arcs[a[pre]][a[j]].CPt.CPoint[i]<<" ";
			cout<<")"; 
			pre = j;
	 		
	 		cout<<"转站=>>bus: "<<G.vexs[a[j]].busFlag<<endl;
	 		break;
		 }
	}	
} 
int findsamestation(MGraph G,string m,string n)//查询是否有某公交车同时经过这两个站点，并将其位置返回 
{
	cout<<"乘坐(";
	for(int i=0;i<G.busnum;i++)
	{
		if(G.vexs[i].FindStation(m)&&G.vexs[i].FindStation(n))
		{
			cout<<" "<<G.vexs[i].busFlag<<" ";
		}
	}
	cout<<") =>"<<n<<endl;;
}
//各公交相连的则距离为一，不想练则距离为INITNUMBER.通过弗罗里达算法求各个公交车站之间的最短距离，即最少换乘次数。 
void ShortestPath_FLOYD(MGraph &G, PathMatrix &P,DistancMatrix &D)
{

	int v,w,u,i;
	int count3=0,count4=0;
	for(v=0;v<G.busnum;++v)
		for(w=0;w<G.busnum;w++)
		{
			D[v][w] = G.arcs[v][w].adj;
			for(u=0;u<G.busnum;u++) 
			P[v][w][u] = false;
			
			if(D[v][w]<INITNUMBER)
			{

				P[v][w][v] = true;
				P[v][w][w] = true;
			}
		}
	for(u=0;u<G.busnum;u++)
		for(v=0;v<G.busnum;v++)
			for(w=0;w<G.busnum;w++)
			if(D[v][u]+D[u][w]<D[v][w])
			{

				D[v][w] = D[v][u]+D[u][w];
				for(i=0;i<G.busnum;i++)
				P[v][w][i] = P[v][u][i]||P[u][w][i]; 
			}

 }

