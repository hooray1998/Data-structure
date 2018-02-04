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
int graph[ROW_MAX][ROW_MAX];//存储迷宫的每个单元的属性 
int start_x,start_y,end_x,end_y;//开始坐标与结束坐标 
int m,n;//设定几行几列 
	
class Cube{
	
	public:
	Cube(){	}
	Cube(int xx,int yy):x(xx),y(yy){ nextDirection = 0 ;movetime = 0;} 
	Cube(const Cube&c){x =c.x;y = c.y; nextDirection=c.nextDirection;movetime = c.movetime;	}//初始化方向和转向次数
	void move();//移动到方向所指定的方格 
	int get_x(){return x;	}
	int get_y(){return y;	}
	int get_dir(){return nextDirection;	}

	bool next();//查找下一个可以移动的方向，若无（movetime已达三次），则返回false 
	void go()//转向下一个方向 
	{
		nextDirection=(++nextDirection)%4;
		movetime++;
	}
	void eraser();//擦出当前方格的属性，使其变为空白 

	void showGraph();//打印迷宫 
	void print();//设置当前方格的新属性，5678分别代表 ↑→↓← 
	void end();//判断是否结束 
		private:
		int x,y;
		int nextDirection;	//存储下一个的方向 
		int movetime; //记录移动次数 
		
}; 
stack<Cube> route;//栈中存储路线中每个位置的cube（位置，方向）。 


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

	while(movetime!=3)//移动次数为三则该返回false，表示该位置已经不可能为通路上的点 
	{
	
		switch(nextDirection)
		{
			case 1:{i=0;j=1;break;}
			case 0:{i=-1;j=0;break;}
			case 3:{i=0;j=-1;break;}
			case 2:{i=1;j=0;break;}
			default:{cout<<"error in next"<<nextDirection<<endl;}
		}
		if(x+i<0||y+j<0||x+i>=m||y+j>=n)//越界，则变向 
		{
			go();continue;
		}
		if(graph[x+i][y+j]==1)//撞墙，则变向 
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

void f()//主函数，不断寻找下一个移动目标 
{
	route.push(Cube(start_x,start_y));//将初始位置存入 
	
	int kk=0;
	while(!route.empty())//若四处碰壁不断pop最后空栈则游戏结束 
	{
		Cube temp = route.top();//通路的火车头 
		route.pop();
		if(kk>=1)//开始的位置因为还没判断所以无需转向 ，以后每次从队列里pop出的位置都要变向一次，
		{		//因为之前的方向已经退回，所以当前方向失效。 
			temp.go();
		}
		kk++;
		while(temp.next())//若可以移动到下一个位置 
		{
			route.push(temp);
			temp.move();//移动 
			temp.print();//修改该方格属性 
			temp.showGraph();//展示 
		//	Sleep(200); 
			system("pause");
			system("cls");
			
			temp.end();//结束判断 
		}
		temp.eraser(); //擦除当前无下一个通路的方格 
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
		graph[x][y] = nextDirection+5;//设置当前方格属性。
				//并初始化新的位置 
		x = x+i;
		y = y+j;
		nextDirection = (3+nextDirection)%4;//加三是为了让下一个方向初始化为当前方向的左边方向。
											//依据的原理就是任何迷宫一直靠左边走地定能找到出路。即靠左走，顺时针变想 
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
void Cube::showGraph()//按照属性打印迷宫 
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
						cout<<"↑";
						break;
					}
					case 6:{
						cout<<"→";
						break;
					}
					case 7:{
						cout<<"↓";
						break;
					}
					case 8:{
						cout<<"←";
						break;
					}
				} 	
			}
		}
		cout<<endl;
}
