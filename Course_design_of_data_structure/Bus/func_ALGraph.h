#include"ALGraph.h"
int findstation(ALGraph G,string s)
{
	for(int i=0;i<G.vexnum;i++)
	if(G.vertices[i].data==s) return i;
	
	return -1;
	
}
int insertadj(ALGraph &G,string ss,string s,int samebus)//����������վ����
{
	int k=findstation(G,ss);
	int t=findstation(G,s);
	//t����k 
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
	//k����t
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
	ifstream in("����·��.txt");//��һ�ζ�ȡ�ļ���������վ�б� 
	string s;
	int tempbus;
	while(!in.eof())
	{
		in>>s;
		if(in.eof()) break;
		int i,len=s.length();
		for(i=0;i<len;i++)//�ж��Ƿ�Ϊ���� 
		if(s[i]>'9'||s[i]<'0')
		break;
		
		if(i!=len)
		{
			int k=findstation(G,s);//�����б����Ƿ���ڸ�վ���������ڣ��½�����ʼ�� 
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
		ifstream in("����·��.txt");//�ٴζ�ȡ��������վ֮����ڽ���� 
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
				if(v==1)//�ж��Ƿ�Ϊĳ����·�ߵ���㡣��Ϊ�������preվ�����ڽӹ�ϵ��
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


