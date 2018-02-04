/*
7、Hash表应用 （选做） （查找）
[问题描述]
设计散列表实现VIP客户发掘。对身份证号进行Hash, 通过对乘客某时间段内的乘机频率、里程数统计，发掘VIP客户。 
[基本要求]
（1） 设每个记录有下列数据项：身份证号码（虚构，位数和编码规则与真实一致即可）、姓名、航班号、航班日期、里程。 
（2） 从文件输入各记录，以身份证号码为关键字建立散列表。 
（3） 分别采用开放定址（自行选择和设计定址方案）和链地址两种方案解决冲突；显示发生冲突的次数、每次中解决冲突进行重定位的次数。
（4）记录条数至少在100条以上。
（5） 从记录中实现乘客乘机频率、里程数统计，从而发掘VIP客户。



*/

#include<iostream>
#include<fstream>
#include<string>
#include<ctype.h>
#include<windows.h>
#define MAX_PEOPLE 100
#define HashTableLen 25 
using namespace std;


bool vip[MAX_PEOPLE];
class record{//存数文件中单个记录 
	public:
	string id;
	string name;
	string flightNum;
	int mon; 
	int day;
	int route;

	
};
void operator>>(ifstream &in,record &r)
{
	in>>r.id>>r.name>>r.flightNum>>r.mon>>r.day>>r.route;
}
class people{//存储每个人的总统计信息 
	public:
		string id;
		string name;
		int flytime;
		int sum_route;
		people* next;
		
		people()
		{
			flytime = 0;
			sum_route = 0;
			next = NULL;
		}
		void show()
		{
			cout<<name<<"	"<<flytime<<"	"<<sum_route;
		}
		void operator = (people p)
		{
			id = p.id;
			name = p.name;
			flytime = p.flytime;
			sum_route = p.sum_route;
			next = p.next;
		}
		
};

people* pchain[HashTableLen];//开放定址法所用的hash表 
people 	parray[HashTableLen];//链地址法所用的hash表 

int to_asc(string s)//通过身份证id获得hash地址的函数 
{
	//取前六位与后四位的ascii码累加，取余 
	int sum=0;
	int len = s.length();
	for(int i=0;i<6;i++)
		sum+=toascii(s[i]);
	for(int i=14;i<18;i++)
		sum+=toascii(s[i]);
	return (sum+HashTableLen)%HashTableLen;

}

void HashArray(record r)//开放定址法hash记录r 
{
	int lct = to_asc(r.id);
	
	if(parray[lct].id.length()==0)//当前位置空 
	{
		parray[lct].id = r.id;
		parray[lct].name = r.name;
		parray[lct].flytime++;
		parray[lct].sum_route+=r.route;
	}
	else if(parray[lct].id == r.id)//当前位置恰好为该乘客的信息 
	{
		parray[lct].flytime++;
		parray[lct].sum_route+=r.route;
	}
	else 
	{
		for(int t=2;;t++)//二次冲突再散列处理冲突 
		{
			int k=(t/2)*(t/2);
			if(t%2==1) k=-k;
			int l = (lct+k+HashTableLen)%HashTableLen;//l为新的地址 
			if(parray[l].id.length()==0)
			{
				parray[l].id = r.id;
				parray[l].name = r.name;
				parray[l].flytime++;
				parray[l].sum_route+=r.route;
				break;
			}
			else if(parray[l].id == r.id)
			{
				parray[l].flytime++;
				parray[l].sum_route+=r.route;
				break;
			}
		}
	}
}
int LocateArray(string id)//查找 ，计算查找长度 
{
	int count=0;
	bool visit[HashTableLen];
	for(int i=0;i<HashTableLen;i++)
	visit[i] = false;
	
	int lct = to_asc(id);
	
	if(parray[lct].id.length()==0)
	{
		cout<<"not find1"<<endl;
		return -1;
	}
	else if(parray[lct].id == id)
	{
		count++;
		cout<<"开放定址法查找长度为："<<count<<endl; 
		return lct;
	}
	else 
	{
		count++;
		for(int t=2;;t++)
		{
			int k=(t/2)*(t/2);
			if(t%2==1) k=-k;
			int l = (lct+k+HashTableLen)%HashTableLen;
			if(parray[l].id.length()==0)
			{
				cout<<"not find2"<<endl;
				return -1;
			}
			else if(parray[l].id == id)
			{
				count++;
				cout<<"开放定址法查找长度为："<<count<<endl;
				return l;
			}
			count++; 
			visit[l] = true;
			//cout<<"l:"<<l<<endl;
			int i;
			for(i=0;i<HashTableLen;i++)
			if(!visit[i]) break;
			if(i==HashTableLen) 
			{
				cout<<"not find"<<endl;
				return -1;
			}
			
		}
	}
}
void HashChain(record r)//链地址法 
{
	int lct = to_asc(r.id);
	people temp;
	if(pchain[lct]==NULL)
	{
		temp.id = r.id;
		temp.name = r.name;
		temp.flytime++;
		temp.sum_route+=r.route;
		
		pchain[lct] = new people(temp);
	}
	else if(pchain[lct]->id == r.id)
	{
		pchain[lct]->flytime++;
		pchain[lct]->sum_route+=r.route;
	}
	else 
	{
		people* q = pchain[lct],*p=q->next;
		int k=0;
		while(p)
		{
			if(p->id == r.id)//接下来的节点中有该乘客的信息 
			{
				p->flytime++;
				p->sum_route+=r.route;
				k=1;
				break;
			}
			q=p;	
			p=p->next;
		}	
		if(k==0)//该乘客第一次存储 
		{
		
			temp.id = r.id;
			temp.name = r.name;
			temp.flytime++;
			temp.sum_route+=r.route;
		
			q->next = new people(temp);
		}
		
		
	}	
	
	
	
}


people* LocateChain(string id)
{
	int count=0;
	bool visit[HashTableLen];
	for(int i=0;i<HashTableLen;i++)
	visit[i] = true;
	
	int lct = to_asc(id);
	people temp;
	if(pchain[lct]==NULL)
	{
		cout<<"not find"<<endl;
		return NULL;
	}
	else if(pchain[lct]->id == id)
	{
		count++;
		cout<<"链地址法查找长度为："<<count<<endl; 
		return pchain[lct];
	}
	else 
	{
		count++;
		 
		people* q = pchain[lct],*p=q->next;
		int k=0;
		while(p)
		{
			if(p->id == id)
			{
				count++;
				cout<<"链地址法查找长度为："<<count<<endl; 
				return p;
			}
			q=p;	
			p=p->next;
			count++;
		}
			
		if(p==NULL)
		{
			cout<<"not find"<<endl;
			return NULL;
		}
		
		
	}	
	
	
	
}
void Init()
{
	
	for(int i=0;i<HashTableLen;i++)
	vip[i] = false;	
}
void Storage()
{
	ifstream fin("data.txt");
	if(fin.eof())
	{
		cout<<"error in opening"<<endl;
		exit(1);
	}
	record temp;
	int num=0;
	while(!fin.eof())//文件中读取记录，读一个hash一个。 
	{
		fin>>temp;
		if(fin.eof())	break;
		
		HashArray(temp);
		HashChain(temp);					
	}
	
	fin.close();

	cout<<"parray:"<<endl;	
	for(int i=0;i<HashTableLen;i++)
	{
		if(parray[i].flytime!=0)
		{
			cout<<i<<"	";
			parray[i].show();
			if(parray[i].flytime>15||parray[i].sum_route>20000)//若该乘客的里程超过20000或乘机次数超过15则推荐为vip 
			vip[i]=true;
			cout<<endl;
		}
	}
	cout<<"pchain:"<<endl;
	for(int i=0;i<HashTableLen;i++)
	{
		people*p = pchain[i];
		if(p)
		cout<<endl<<i<<"	";
		while(p)
		{
			cout<<" -> ";
			p->show();
			p=p->next;
		}
		
	}
	
	
	
}
void Vip()
{
	cout<<endl<<"vip 推荐："<<endl; 
	for(int i=0;i<HashTableLen;i++)
	if(vip[i])
	{
		cout<<parray[i].id<<" ";
		parray[i].show(); 
		cout<<endl;
	}
 } 

int main()
{
	Init();
	Storage();
	Vip();
	char c;
	string ID[6];
	ID[0]="102228196201120226";
	ID[1]="119718199601207677";
	ID[2]="112859199701211177";
	ID[3]="105097197301061161";
	ID[4]="122386199306252072";
	ID[5]="115574197501222215";
	system("pause");
	while(1)
	{
		string id;
		int order;
		cout<<"请输入查找的人的id"<<endl;//由于输入这么长的id过于复杂，故提供几个选项 
		cout<<"0--102228196201120226"<<endl;
		cout<<"1--119718199601207677"<<endl;
		cout<<"2--112859199701211177"<<endl;
		cout<<"3--105097197301061161"<<endl;
		cout<<"4--132439198403234538"<<endl;
		cout<<"5--109374199605061348"<<endl;
		cin>>order;
		if(order>-1&&order<6)
		id = ID[order];
		else
		{
			cout<<"input error"<<endl;
			continue;
		}
		
		
		int loc=LocateArray(id);
		if(loc!=-1)
		cout<<parray[loc].id<<" "<<parray[loc].name<<" "<<parray[loc].flytime<<" "<<parray[loc].sum_route<<endl;
		people*p=LocateChain(id);
		if(p)
		cout<<p->id<<" "<<p->name<<" "<<p->flytime<<" "<<p->sum_route<<endl;
		system("pause");
	}
	return 0;
}

