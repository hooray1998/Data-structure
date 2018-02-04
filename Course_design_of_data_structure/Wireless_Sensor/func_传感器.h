#include"ALGraph.h"
void CreateALGraph(ALGraph &G)
{
	srand(time(NULL));
	cout<<"����������ͼG�Ķ�����"<<endl;
	cin>>G.vexnum;//������㣬�������ʱ��һ 

	for(int i=0;i<100;i++)
	for(int j=0;j<100;j++)
	d[i][j] = 0;
	
	cout<<"��������"<<G.vexnum<<"���������Ϣ"<<endl;	
	int x,y;
	Location l[1000];//�������� 
	int lNum = 0;
	l[lNum++].set(0,0);
	for(int i=1;i<G.vexnum;)
	{
		x = rand()%100;
		y = rand()%100; 
		if(d[x][y]==0)
		{
			d[x][y] = 1;
			l[lNum++].set(x,y);
			i++;
		}
	} 
	
	//BubbleSort
	Location temp;
	for(int i=0;i<lNum;i++)
	for(int j=i;j<lNum;j++)
	{
		if(l[j]<l[i])
		{
			temp = l[i];
			l[i] = l[j];
			l[j] = temp;
			
		}
	}
	
	//Init Vex
	for(int i=0;i<G.vexnum;i++)
	{
		x = l[i].x;
		y = l[i].y; 
		locate[x][y] = i;
		G.vertices[i].data.set(x,y);
		G.vertices[i].firstarc = NULL;	
	} 
	
	//Init Arc
	for(int k=0;k<G.vexnum;k++)
	{
		x = G.vertices[k].data.x;
		y = G.vertices[k].data.y;
		
		for(int i=0;i<=10&&x+i<100;i++)
		for(int j=0;j<=10&&y+j<100;j++)
		if(d[x+i][y+j]==1)
		if((i*i+j*j)<=100&&(i+j)!=0)
		{
			int adj = locate[x+i][y+j];
			ArcNode*p = new ArcNode;
			p->adjvex = adj;
			p->inof = new Weight;
			p->inof->set(i*i+j*j);
			p->nextarc =  G.vertices[k].firstarc;
			G.vertices[k].firstarc = p;
			
			ArcNode *q = new ArcNode;
			q->adjvex = k;
			q->inof = new Weight;
			q->inof->set(i*i+j*j);
			q->nextarc = G.vertices[adj].firstarc;
			G.vertices[adj].firstarc = q;
			
		}
		
		
	}
	
	ofstream out("vex.txt");
	//Show VexList
	for(int i=0;i<G.vexnum;i++)
	{
		cout<<endl;
		cout<<i<<" ("<<G.vertices[i].data.x<<","<<G.vertices[i].data.y<<")";
		out<<endl;
		out<<i<<" ("<<G.vertices[i].data.x<<","<<G.vertices[i].data.y<<")";
		for(ArcNode* T = G.vertices[i].firstarc;T;T=T->nextarc)
		{
		
		cout<<" => "<<T->adjvex<<" ("<<G.vertices[T->adjvex].data.x<<","<<G.vertices[T->adjvex].data.y<<")";
		cout<<"["<<T->inof->weight<<","<<T->inof->w_weight<<"] "	;
		out<<" => "<<T->adjvex<<" ("<<G.vertices[T->adjvex].data.x<<","<<G.vertices[T->adjvex].data.y<<")";
		out<<"["<<T->inof->weight<<","<<T->inof->w_weight<<"] "	;
		}
		cout<<endl;
		out<<endl;
	}
}
void DFS(ALGraph G,ArcNode* v)//�ӵ�v����������ݹ�������ȱ���ͼG 
{
	ArcNode* w;
	link[v->adjvex]=1;
//	cout<<" "<<v->adjvex;
//	VisitFunc(GetVex(G,v));//���ʵ�v������ 
	for(w = G.vertices[v->adjvex].firstarc;w;w=w->nextarc )//�Ӷ���v�ĵ�һ���ڽӶ���w��ʼ �����Ҳ�����һ���ڽӶ���ʱ��w����-1����������ڵ����㣬ѭ������ 
	{
		if(!link[w->adjvex])//�ڽӶ�����δ������ 
		DFS(G,w); //�� w���ڽӶ���ݹ����DFS 
	}
	
} 

void DeleteDot(ALGraph G)
{
	for(int i=0;i<G.vexnum;i++)
	link[i] = 0;
	link[0] = 1;
	for(ArcNode*p = G.vertices[0].firstarc;p;p=p->nextarc)
	DFS(G,p);
	
	
	cout<<endl<<"!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl; 
	for(int i=0;i<G.vexnum;i++)
	if(link[i]) 
	{
		linkNum++;
		cout<<" "<<i;	
	}
	cout<<endl<<"!!!!!!!!!!!!!!!!!!!!!!!!!!"<<endl;
	cout<<"������Ĺ�"<<linkNum<<"��"<<endl;	
	
	
}
