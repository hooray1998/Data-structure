#include"MGraph.h"

void (*VisitFunc)(VertexType e);
bool visited[MAX_BUS_NUM];//访问标志数组，全局

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
//初始化存储公交信息 
int CreateMGraph(MGraph &G)
{
	G.busnum = 0; 
	ifstream in("公交路线.txt");
	string s;
	int tempbus;
	while(!in.eof())
	{
		in>>s;
		if(in.eof()) break;
		int i,len=s.length();
		for(i=0;i<len;i++)//判断是否为公交车号 
		if(s[i]>'9'||s[i]<'0')
		break;
		
		if(i==len)//若为车号，则将该字符串转化成号码 
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
		else//否则将公交站存入当前公交车的信息里 
		{
			G.vexs[G.busnum-1].InsertStation(s);
		}
	
		
		
	}
	
	in.close();
	//建立邻接矩阵 
	//查找其他公交车有没有相同的公交站，有则联通，更新相交车站信息 
	
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
	
	//将联通信息写入文件，方便查询。 
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


