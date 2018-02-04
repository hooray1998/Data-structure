#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<fstream>
#include<stack>
#include<conio.h>
#include<windows.h>
#include<unistd.h>
#define ROW_MAX	20 
using namespace std;
int graph[ROW_MAX][ROW_MAX];//�洢�Թ���ÿ����Ԫ������ 
int start_x,start_y,end_x,end_y;//��ʼ������������� 
int m,n;//�趨���м��� 
	
class Cube{
	
	public:
	Cube(){	}
	Cube(int xx,int yy):x(xx),y(yy){ nextDirection = 0 ;movetime = 0;} 
	Cube(const Cube&c){x =c.x;y = c.y; nextDirection=c.nextDirection;movetime = c.movetime;	}//��ʼ�������ת�����
	void move();//�ƶ���������ָ���ķ��� 
	int get_x(){return x;	}
	int get_y(){return y;	}
	int get_dir(){return nextDirection;	}

	bool next();//������һ�������ƶ��ķ������ޣ�movetime�Ѵ����Σ����򷵻�false 
	void go()//ת����һ������ 
	{
		nextDirection=(++nextDirection)%4;
		movetime++;
	}
	void eraser();//������ǰ��������ԣ�ʹ���Ϊ�հ� 

	void showGraph();//��ӡ�Թ� 
	void print();//���õ�ǰ����������ԣ�5678�ֱ���� �������� 
	void end();//�ж��Ƿ���� 
		private:
		int x,y;
		int nextDirection;	//�洢��һ���ķ��� 
		int movetime; //��¼�ƶ����� 
		
}; 
stack<Cube> route;//ջ�д洢·����ÿ��λ�õ�cube��λ�ã����򣩡� 


void Cube::eraser()
{
	graph[x][y] = 0;
}
void Cube::print()
{
	graph[x][y] = nextDirection+5;
}

bool Cube::next()
{
	int i,j;

	while(movetime!=3)//�ƶ�����Ϊ����÷���false����ʾ��λ���Ѿ�������Ϊͨ·�ϵĵ� 
	{
	
		switch(nextDirection)
		{
			case 1:{i=0;j=1;break;}
			case 0:{i=-1;j=0;break;}
			case 3:{i=0;j=-1;break;}
			case 2:{i=1;j=0;break;}
			default:{cout<<"error in next"<<nextDirection<<endl;}
		}
		if(x+i<0||y+j<0||x+i>=m||y+j>=n)//Խ�磬����� 
		{
			go();continue;
		}
		if(graph[x+i][y+j]==1)//ײǽ������� 
		{
			go();continue;
		} 
		return true;
	}
	return false;
	
}
void Cube::end()
{
	if(x==end_x&&y==end_y)
	{
	//	system("cls"); 
	//	for(;!route.empty();route.pop())
	//	{
	//	Cube cc = route.top();
	//	cc.print();
	//	}
		cout<<"champain"<<endl;
		
		showGraph(); 
		exit(0);
	}
	if(x==start_x&&y==start_y)
	{
		showGraph(); 
		cout<<"no route"<<endl;
		exit(0);
	}

}

void f()//������������Ѱ����һ���ƶ�Ŀ�� 
{
	route.push(Cube(start_x,start_y));//����ʼλ�ô��� 
	
	int kk=0;
	while(!route.empty())//���Ĵ����ڲ���pop����ջ����Ϸ���� 
	{
		Cube temp = route.top();//ͨ·�Ļ�ͷ 
		route.pop();
		if(kk>=1)//��ʼ��λ����Ϊ��û�ж���������ת�� ���Ժ�ÿ�δӶ�����pop����λ�ö�Ҫ����һ�Σ�
		{		//��Ϊ֮ǰ�ķ����Ѿ��˻أ����Ե�ǰ����ʧЧ�� 
			temp.go();
		}
		kk++;
		while(temp.next())//�������ƶ�����һ��λ�� 
		{
			route.push(temp);
			temp.move();//�ƶ� 
			temp.print();//�޸ĸ÷������� 
			temp.showGraph();//չʾ 
		//	Sleep(200); 
			system("pause");
			system("cls");
			
			temp.end();//�����ж� 
		}
		temp.eraser(); //������ǰ����һ��ͨ·�ķ��� 
	}
	
 } 


void Cube::move() 
{
	int i,j;
		switch(nextDirection)
		{
			case 1:{i=0;j=1;break;}
			case 0:{i=-1;j=0;break;}
			case 3:{i=0;j=-1;break;}
			case 2:{i=1;j=0;break;}
			default:{cout<<"error in move"<<endl;}
		}
		graph[x][y] = nextDirection+5;//���õ�ǰ�������ԡ�
				//����ʼ���µ�λ�� 
		x = x+i;
		y = y+j;
		nextDirection = (3+nextDirection)%4;//������Ϊ������һ�������ʼ��Ϊ��ǰ�������߷���
											//���ݵ�ԭ������κ��Թ�һֱ������ߵض����ҵ���·���������ߣ�˳ʱ����� 
		movetime = 0;
}

int main()
{
	ifstream fin("data2.txt");
	for(int i=0;i<ROW_MAX;i++)
	for(int j=0;j<ROW_MAX;j++)
	graph[i][j] = 1;	

	fin>>m>>n;
	for(int i=0;i<m;i++)
	for(int j=0;j<n;j++)
	fin>>graph[i][j];
	
	fin>>start_x>>start_y;
	fin>>end_x>>end_y;
	f();
	return 0;
}
void Cube::showGraph()//�������Դ�ӡ�Թ� 
{
		for(int i=0;i<m;i++)
		{
			cout<<endl;
			for(int j=0;j<n;j++)
			{
				switch(graph[i][j])
				{
					case 0:{
						cout<<"  ";
						break;
					}
					case 1:{
						cout<<"##";
						break;
					}
					case 5:{
						cout<<"��";
						break;
					}
					case 6:{
						cout<<"��";
						break;
					}
					case 7:{
						cout<<"��";
						break;
					}
					case 8:{
						cout<<"��";
						break;
					}
				} 	
			}
		}
		cout<<endl;
}
