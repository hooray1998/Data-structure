/*
7��Hash��Ӧ�� ��ѡ���� �����ң�
[��������]
���ɢ�б�ʵ��VIP�ͻ����򡣶����֤�Ž���Hash, ͨ���Գ˿�ĳʱ����ڵĳ˻�Ƶ�ʡ������ͳ�ƣ�����VIP�ͻ��� 
[����Ҫ��]
��1�� ��ÿ����¼��������������֤���루�鹹��λ���ͱ����������ʵһ�¼��ɣ�������������š��������ڡ���̡� 
��2�� ���ļ��������¼�������֤����Ϊ�ؼ��ֽ���ɢ�б� 
��3�� �ֱ���ÿ��Ŷ�ַ������ѡ�����ƶ�ַ������������ַ���ַ��������ͻ����ʾ������ͻ�Ĵ�����ÿ���н����ͻ�����ض�λ�Ĵ�����
��4����¼����������100�����ϡ�
��5�� �Ӽ�¼��ʵ�ֳ˿ͳ˻�Ƶ�ʡ������ͳ�ƣ��Ӷ�����VIP�ͻ���



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
class record{//�����ļ��е�����¼ 
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
class people{//�洢ÿ���˵���ͳ����Ϣ 
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

people* pchain[HashTableLen];//���Ŷ�ַ�����õ�hash�� 
people 	parray[HashTableLen];//����ַ�����õ�hash�� 

int to_asc(string s)//ͨ�����֤id���hash��ַ�ĺ��� 
{
	//ȡǰ��λ�����λ��ascii���ۼӣ�ȡ�� 
	int sum=0;
	int len = s.length();
	for(int i=0;i<6;i++)
		sum+=toascii(s[i]);
	for(int i=14;i<18;i++)
		sum+=toascii(s[i]);
	return (sum+HashTableLen)%HashTableLen;

}

void HashArray(record r)//���Ŷ�ַ��hash��¼r 
{
	int lct = to_asc(r.id);
	
	if(parray[lct].id.length()==0)//��ǰλ�ÿ� 
	{
		parray[lct].id = r.id;
		parray[lct].name = r.name;
		parray[lct].flytime++;
		parray[lct].sum_route+=r.route;
	}
	else if(parray[lct].id == r.id)//��ǰλ��ǡ��Ϊ�ó˿͵���Ϣ 
	{
		parray[lct].flytime++;
		parray[lct].sum_route+=r.route;
	}
	else 
	{
		for(int t=2;;t++)//���γ�ͻ��ɢ�д����ͻ 
		{
			int k=(t/2)*(t/2);
			if(t%2==1) k=-k;
			int l = (lct+k+HashTableLen)%HashTableLen;//lΪ�µĵ�ַ 
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
int LocateArray(string id)//���� ��������ҳ��� 
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
		cout<<"���Ŷ�ַ�����ҳ���Ϊ��"<<count<<endl; 
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
				cout<<"���Ŷ�ַ�����ҳ���Ϊ��"<<count<<endl;
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
void HashChain(record r)//����ַ�� 
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
			if(p->id == r.id)//�������Ľڵ����иó˿͵���Ϣ 
			{
				p->flytime++;
				p->sum_route+=r.route;
				k=1;
				break;
			}
			q=p;	
			p=p->next;
		}	
		if(k==0)//�ó˿͵�һ�δ洢 
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
		cout<<"����ַ�����ҳ���Ϊ��"<<count<<endl; 
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
				cout<<"����ַ�����ҳ���Ϊ��"<<count<<endl; 
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
	while(!fin.eof())//�ļ��ж�ȡ��¼����һ��hashһ���� 
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
			if(parray[i].flytime>15||parray[i].sum_route>20000)//���ó˿͵���̳���20000��˻���������15���Ƽ�Ϊvip 
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
	cout<<endl<<"vip �Ƽ���"<<endl; 
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
		cout<<"��������ҵ��˵�id"<<endl;//����������ô����id���ڸ��ӣ����ṩ����ѡ�� 
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

