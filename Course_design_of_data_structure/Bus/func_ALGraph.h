#include"ALGraph.h"
int findstation(ALGraph G,string s)
{
	for(int i=0;i<G.vexnum;i++)
	if(G.vertices[i].data==s) return i;
	
	return -1;
	
}
int insertadj(ALGraph &G,string ss,string s,int samebus)//将这两个车站互接
{
	int k=findstation(G,ss);
	int t=findstation(G,s);
	//t插入k 
	int flag=0;
	ArcNode*p=G.vertices[k].firstarc;
	while(p)
	{
		if(p->adjvex==t)
		{
			flag=1;
			break;
		}
		
		p=p->nextarc;
	}
	if(flag==0)
	{
		p = new ArcNode;
		p->adjvex = t;
		p->weight = 1;
		p->samebus = samebus;
		p->nextarc = G.vertices[k].firstarc;
		G.vertices[k].firstarc = p;
	}
	//k插入t
	int flag2=0;
	ArcNode*q=G.vertices[t].firstarc;
	while(q)
	{
		if(q->adjvex==k)
		{
			flag2=1;
			break;
		}
		
		q=q->nextarc;
	}
	if(flag2==0)
	{
		q = new ArcNode;
		q->adjvex = k;
		q->weight = 1;
		q->samebus = samebus;
		q->nextarc = G.vertices[t].firstarc;
		G.vertices[t].firstarc = q;
	}
	return 0;
	
}
int CreateALGraph(ALGraph &G)
{
	G.vexnum=0;
	ifstream in("公交路线.txt");//第一次读取文件，建立车站列表。 
	string s;
	int tempbus;
	while(!in.eof())
	{
		in>>s;
		if(in.eof()) break;
		int i,len=s.length();
		for(i=0;i<len;i++)//判断是否为数字 
		if(s[i]>'9'||s[i]<'0')
		break;
		
		if(i!=len)
		{
			int k=findstation(G,s);//查找列表里是否存在该站，若不存在，新建并初始化 
			if(k==-1) 
			{
				G.vertices[G.vexnum].data = s;
				G.vertices[G.vexnum++].firstarc = NULL;
			}	

		}
		else
		{
			char *p = new char[len];
			p[len] = '\0';
			for(int j=0;j<len;j++)
			p[j] = s[j];
			
			tempbus = 0;
			for(int k=0;k<len;k++)
			{
				tempbus*=10;
				tempbus+=s[k]-'0';
			}	
		}	
	}
	
	in.close();
	{	
		ifstream in("公交路线.txt");//再次读取，建立各站之间的邻接情况 
		string pre,s;
		int tempbus;
		int v=0;
		while(!in.eof())
		{
			in>>s;
			if(in.eof()) break;
			int i,len=s.length();
			for(i=0;i<len;i++)
			if(s[i]>'9'||s[i]<'0')
			break;
			
			if(i==len)
			{	
				char *p = new char[len];
				p[len] = '\0';
				for(int j=0;j<len;j++)
				p[j] = s[j];
				
				tempbus = 0;
				for(int k=0;k<len;k++)
				{
					tempbus*=10;
					tempbus+=s[k]-'0';
				}
				v=1;
				
			}
			else
			{
				if(v==1)//判断是否为某公交路线的起点。若为起点则不与pre站建立邻接关系。
				{
					pre=s;
					v=0;
				}
				else
				{
					insertadj(G,pre,s,tempbus);
					pre = s;
				}
			}

		}
		
		in.close();
	}
}


