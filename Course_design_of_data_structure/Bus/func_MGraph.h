#include"MGraph.h"

void (*VisitFunc)(VertexType e);
bool visited[MAX_BUS_NUM];//���ʱ�־���飬ȫ��

void Bus::InsertStation(string s)
{
	station[staNum++] = s;
}
bool Bus::FindStation(string s)
{
	for(int i=0;i<staNum;i++)
	{
		if(station[i]==s) return true;
	}
	return false;
}
void Bus::busShow()
{
	cout<<"Number:	"<<busFlag<<endl;
	for(int i=0;i<staNum;i++)
	{
		cout<<"->"<<station[i];
	 } 
	 cout<<endl;
}
//��ʼ���洢������Ϣ 
int CreateMGraph(MGraph &G)
{
	G.busnum = 0; 
	ifstream in("����·��.txt");
	string s;
	int tempbus;
	while(!in.eof())
	{
		in>>s;
		if(in.eof()) break;
		int i,len=s.length();
		for(i=0;i<len;i++)//�ж��Ƿ�Ϊ�������� 
		if(s[i]>'9'||s[i]<'0')
		break;
		
		if(i==len)//��Ϊ���ţ��򽫸��ַ���ת���ɺ��� 
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
			G.vexs[G.busnum++].busFlag = tempbus;
		}
		else//���򽫹���վ���뵱ǰ����������Ϣ�� 
		{
			G.vexs[G.busnum-1].InsertStation(s);
		}
	
		
		
	}
	
	in.close();
	//�����ڽӾ��� 
	//����������������û����ͬ�Ĺ���վ��������ͨ�������ཻ��վ��Ϣ 
	
	int busNum = G.busnum;
	for(int i=0;i<busNum;i++)
	{
		int sn = G.vexs[i].staNum;
		for(int ii=0;ii<sn;ii++)
		{
			string temps = G.vexs[i].station[ii];
			for(int j=i+1;j<busNum;j++)
			{
				G.arcs[i][j].adj = INITNUMBER;
				if(G.vexs[j].FindStation(temps))
				{
					G.arcs[i][j].adj = 1;
					G.arcs[i][j].CPt.CPoint[G.arcs[i][j].CPt.CPNumber++] = temps;
					G.arcs[j][i].adj = 1;
					G.arcs[j][i].CPt.CPoint[G.arcs[j][i].CPt.CPNumber++] = temps;
				}
			}
		}
		G.arcs[i][i].adj = 0;
	
	}
	
	//����ͨ��Ϣд���ļ��������ѯ�� 
	int count2=0;
	ofstream crossfile("cross.txt");
	for(int i=0;i<busNum;i++)
	for(int j=0;j<busNum;j++)
	{
		if(G.arcs[i][j].adj<INITNUMBER)
		{
			crossfile<<G.vexs[i].busFlag<<"<=>"<<G.vexs[j].busFlag<<"	";
			count2++;
			for(int k=0;k<G.arcs[i][j].CPt.CPNumber;k++)
			{
				crossfile<<"~"<<G.arcs[i][j].CPt.CPoint[k];
			}
			crossfile<<endl;
		}
	}
	crossfile.close();

}


