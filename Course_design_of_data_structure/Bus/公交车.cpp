
#include"FLOYD.h"
#include"DIJ.h"

int main()
{

	MGraph G;
	ALGraph G2;
	
	CreateMGraph(G);
	PathMatrix P;
	DistancMatrix D;
	ShortestPath_FLOYD(G,P,D);
	string a="��һҽԺ",b="��ɽ��ͷ";
	cout<<"�����������յ�"<<endl;
//	cin>>a>>b;
	{

		int m[50],n[50],p=0,q=0;

		for(int i=0;i<G.busnum;i++)
		{
			if(G.vexs[i].FindStation(a)) 
			m[p++] = i;
			if(G.vexs[i].FindStation(b)) 
			n[q++] = i;
		} 
		if(p==0)
		{
			cout<<a<<"������"<<endl;
			return 0;
		} 
		if(q==0)
		{
			cout<<b<<"������"<<endl;
			return 0;
		} 
		int min=888,mina=888,minb=888;
		for(int i=0;i<p;i++)
		for(int j=0;j<q;j++)
		if(D[m[i]][n[j]]<min)
		{
			min = D[m[i]][n[j]];
			mina = m[i];
			minb = n[j];
		}
		
			int t[10],r=0;
			cout<<"��"<<a<<"����"<<b<<endl; 
			cout<<"�����軻��"<<min<<"վ"<<endl;
			cout<<"����·������:"<<endl; 
			
			cout<<"��"<<a<<"���� bus:"<<G.vexs[mina].busFlag<<endl;
			for(int k=0;k<G.busnum;k++)
			if(P[mina][minb][k])
			{
				t[r++]=k;
			} 
			findnext(G,t,mina,r);
		 	cout<<"����"<<b<<endl<<endl;
		 	
		{				
			PathMatrix2 P2;
			ShortPathTable D2;
			CreateALGraph(G2);
			system("pause");
			int m=findstation(G2,a);
			int n=findstation(G2,b);
			ShortestPath_DIJ(G2,m,n,P2,D2);		
		}
	}
		 	system("pause");
	

	return 0;
 } 
