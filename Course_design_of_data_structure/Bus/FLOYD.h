#include"func_MGraph.h"
typedef bool PathMatrix[MAX_BUS_NUM][MAX_BUS_NUM][MAX_BUS_NUM]; 
typedef int DistancMatrix[MAX_BUS_NUM][MAX_BUS_NUM]; 


void findnext(MGraph &G,int a[10],int i,int n)//��a�����Ѵ����о����ĳ������ú������Բ���Ѱ���ҵ���һ�����˵ĳ�
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
	 		cout<<"��(";
	 		for(int i=0;i<G.arcs[a[pre]][a[j]].CPt.CPNumber;i++)
	 		cout<<G.arcs[a[pre]][a[j]].CPt.CPoint[i]<<" ";
			cout<<")"; 
			pre = j;
	 		
	 		cout<<"תվ=>>bus: "<<G.vexs[a[j]].busFlag<<endl;
	 		break;
		 }
	}	
} 
int findsamestation(MGraph G,string m,string n)//��ѯ�Ƿ���ĳ������ͬʱ����������վ�㣬������λ�÷��� 
{
	cout<<"����(";
	for(int i=0;i<G.busnum;i++)
	{
		if(G.vexs[i].FindStation(m)&&G.vexs[i].FindStation(n))
		{
			cout<<" "<<G.vexs[i].busFlag<<" ";
		}
	}
	cout<<") =>"<<n<<endl;;
}
//�����������������Ϊһ�������������ΪINITNUMBER.ͨ����������㷨�����������վ֮�����̾��룬�����ٻ��˴����� 
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

