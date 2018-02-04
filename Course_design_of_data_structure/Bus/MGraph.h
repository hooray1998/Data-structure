#include<stdio.h>
#include<malloc.h>
#include<conio.h>
#include<string>
#include<iostream>
#include<windows.h>
#include<fstream>
#include<string.h>//sprintf()
#include<queue>

using namespace std;


#define INFINITY 		INY_MAX
#define MAX_BUS_NUM 	55
#define	MAX_STATION		80
#define INITNUMBER      888
typedef int Status;
typedef int VRType; 



class Bus{
	public:
	int busFlag;//公交车号 
	string station[MAX_STATION];//经过的所有站 
	int staNum;//站的个数 
	Bus(){busFlag=0;staNum=0;	}
	bool FindStation(string s);//查询是否经过s站 
	void InsertStation(string s);//将s站存入 
	void busShow();
	
};
class crosspoint{
	public:
	int CPNumber;//两条公交路线共同经过的站的个数 
	string CPoint[20];//两条公交路线共同经过的公交站 
	crosspoint(){CPNumber = 0;	}
	
	
};
typedef Bus VertexType;
typedef char* InfoType;
class ArcCell{
	public: 
	VRType adj;//存储权值，联通则为1，反之为 INITNUMBER
	crosspoint CPt;//存储相交的公交站 
	ArcCell(){adj = INITNUMBER;	}
};

typedef struct{
	VertexType vexs[MAX_BUS_NUM];//存储所有公交车的信息 
	ArcCell arcs[MAX_BUS_NUM][MAX_BUS_NUM];//存储各个公交车与其他公交车的相邻情况 
	int busnum;//公交车个数 
	void show()
	{
		int n=busnum;
		for(int i=0;i<n;i++)
		{
			vexs[i].busShow();
		}
	}
}MGraph;



