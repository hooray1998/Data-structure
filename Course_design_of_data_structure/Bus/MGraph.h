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
	int busFlag;//�������� 
	string station[MAX_STATION];//����������վ 
	int staNum;//վ�ĸ��� 
	Bus(){busFlag=0;staNum=0;	}
	bool FindStation(string s);//��ѯ�Ƿ񾭹�sվ 
	void InsertStation(string s);//��sվ���� 
	void busShow();
	
};
class crosspoint{
	public:
	int CPNumber;//��������·�߹�ͬ������վ�ĸ��� 
	string CPoint[20];//��������·�߹�ͬ�����Ĺ���վ 
	crosspoint(){CPNumber = 0;	}
	
	
};
typedef Bus VertexType;
typedef char* InfoType;
class ArcCell{
	public: 
	VRType adj;//�洢Ȩֵ����ͨ��Ϊ1����֮Ϊ INITNUMBER
	crosspoint CPt;//�洢�ཻ�Ĺ���վ 
	ArcCell(){adj = INITNUMBER;	}
};

typedef struct{
	VertexType vexs[MAX_BUS_NUM];//�洢���й���������Ϣ 
	ArcCell arcs[MAX_BUS_NUM][MAX_BUS_NUM];//�洢������������������������������� 
	int busnum;//���������� 
	void show()
	{
		int n=busnum;
		for(int i=0;i<n;i++)
		{
			vexs[i].busShow();
		}
	}
}MGraph;



