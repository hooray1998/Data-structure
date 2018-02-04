/*
排序算法比较 （必做）（排序）
[问题描述]
利用随机函数产生10个样本的Len个随机整数（其中之一已经是正序，之一是逆序），利用直接插入排序、希尔排序，冒泡排序、快速排序、选择排序、堆排序，归并排序、基数排序8种排序方法进行排序（结果为由小到大的顺序），并统计每一种排序算法对不同样本所耗费的时间。
 [基本要求]
（1） 原始数据存在文件中，用相同样本对不同算法进行测试；
（2） 屏幕显示每种排序算法对不同样本所花的时间；
*/ 

#include<iostream>
#include<math.h>
#include<ctype.h>
#include<fstream>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string> 
#define Len 20001
using namespace std;

typedef int List[Len];
List l[10];
int Time[10];
typedef int ArrType[10];
ArrType f,e;

int dlta[5]={9,5,3,2,1};
int t=5;

typedef struct  
{  
  int num;  
  int next;  
}slcell;  
typedef slcell List2[Len];
List2 l2[10]; 

void input(List l[10]);
void Print(List r);
void Show(List r,string s);
//void Show2(List2 r,string s);

void InsertSort(List r);//000000000000

int Min(List a, int k);
void ChooseSort(List a);//1111111111111

void BubbleSort(List a);//222222222222222

void Merge(List s,List t,int i, int m,int n);
void MSort(List S,List T,int s,int t);
void MergeSort(List a);//333333333333333

void HeapAdjust(List r, int s, int m);
void HeapSort(List r);//44444444444

int Partition(List &r, int low, int high);
void QSort(List &a, int low, int high);
void QuickSort(List &a);//555555555555555

void ShellInsert(List r,int dk);
void ShellSort(List r,int dlta[],int t);//66666666666

void distribute(slcell r[],int i,ArrType &f,ArrType &e);
void collect(slcell r[],int i,ArrType &f,ArrType &e);    
void Output(slcell r[], int head);
void RadixSort(slcell r[]);//l2l2l2l2l2ll2

int main()
{
		
	
//	Print(l[3]);
	for(int j=0;j<7;j++)
	{
		input(l);
		switch(j)
		{
			case 0:{
				cout<<endl<<"InsertSort"<<endl;
				for(int i=0;i<10;i++) 
				InsertSort(l[i]);
				break;
			}
			case 1:{
				cout<<endl<<"ChooseSort"<<endl;
				for(int i=0;i<10;i++) 
				ChooseSort(l[i]);
				break;
			}
			case 2:{
				cout<<endl<<"BubbleSort"<<endl;
				for(int i=0;i<10;i++) 
				BubbleSort(l[i]);
				break;
			}
			case 3:{
				cout<<endl<<"MergeSort"<<endl;
				for(int i=0;i<10;i++) 
				MergeSort(l[i]);
				break;
			}
			case 4:{
				cout<<endl<<"HeapSort"<<endl;
				for(int i=0;i<10;i++) 
				HeapSort(l[i]);
				break;
			}
			case 5:{
				cout<<endl<<"QuickSort"<<endl;
				for(int i=0;i<10;i++) 
				QuickSort(l[i]);
				break;
			}
			case 6:{
				cout<<endl<<"ShellSort"<<endl;
				for(int i=0;i<10;i++) 
				ShellSort(l[i],dlta,t);
				break;
			}
			
		}	
	}
				cout<<endl<<"RadixSort"<<endl;
				for(int i=0;i<10;i++) 
				RadixSort(l2[i]);
	
//	Show(l[3],"insert");
//	ChooseSort(l);
//	BubbleSort(l);
//	MergeSort(l);
//	HeapSort();
//	QuickSort();
//	ShellSort();
//	RadixSort(l2);



	return 0;
}
void input(List r[10])
{
	{
		ifstream in[10];
		in[0].open("data.txt");
		in[1].open("data2.txt");
		in[2].open("data3.txt");
		in[3].open("data4.txt");
		in[4].open("data5.txt");
		in[5].open("data6.txt");
		in[6].open("data7.txt");
		in[7].open("data8.txt");
		in[8].open("data9.txt");
		in[9].open("data10.txt");
		int n=Len,i=1;
		int temp;
		while(i<=n)
		{
		
			for(int j=0;j<10;j++)
			in[j]>>r[j][i];
		
			i++;
			
		}
		in[0].close(); 
		in[1].close(); 
		in[2].close(); 
		in[3].close(); 
		in[4].close(); 
		in[5].close(); 
		in[6].close(); 
		in[7].close(); 
		in[8].close(); 
		in[9].close(); 

	}
	
	
}

void input2(List2 r[10])
{
	{
		ifstream in[10];
		in[0].open("data.txt");
		in[1].open("data2.txt");
		in[2].open("data3.txt");
		in[3].open("data4.txt");
		in[4].open("data5.txt");
		in[5].open("data6.txt");
		in[6].open("data7.txt");
		in[7].open("data8.txt");
		in[8].open("data9.txt");
		in[9].open("data10.txt");
		int n=Len,i=1;
		int temp;
		while(i<=n)
		{
		
			for(int j=0;j<10;j++)
			in[j]>>r[j][i].num;
		
			i++;
			
		}
		in[0].close(); 
		in[1].close(); 
		in[2].close(); 
		in[3].close(); 
		in[4].close(); 
		in[5].close(); 
		in[6].close(); 
		in[7].close(); 
		in[8].close(); 
		in[9].close(); 

	}
	
	
}
int Min(List a, int k)
{
	int min=k;
	for(int i=k;i<=Len;i++)
	{
		if(a[i]<a[min])
		min = i;

	}
//	cout<<"  min->"<<a[min];
	return min;
}
void Show(List r,string s)
{
	int pre=1,i,j=0;
	for(i=1;i<Len&&pre<=r[i];pre=r[i],i++);
	if(j!=Len) 
	cout<<s<<"	in order"<<endl;
	else
	cout<<s<<"	not in order"<<endl;
}

void Print(List r)
{
	for(int i=1;i<=Len;i++)
	cout<<r[i]<<' ';
 } 
 void InsertSort(List r)
{
	clock_t st = clock();
	for(int i=1;i<=Len;i++)
		for(int j=i;j<=Len;j++)
		{
			if(r[j]<r[i])
		{
			int temp = r[i];
			r[i] = r[j];
			r[j] = temp;
		}
	}
//	Show(r,"InsertSort");
	cout<<" time:"<<(clock()-st);
}
void ChooseSort(List a)
{
	clock_t st = clock();
	for(int i=0;i<Len;i++)
	{
		int j=Min(a,i);
		int temp = a[i];
		a[i]=a[j];
		a[j]=temp;
	}
//	cout<<"ChooseSort:"<<endl;
//	Show(a,"ChooseSort");
	cout<<" time:"<<(clock()-st);
}
void BubbleSort(List a)
{
	clock_t st = clock();
	for(int i=1;i<=Len;i++)
	for(int j=i;j<=Len;j++)
	{
		if(a[j]<a[i])
		{
			int temp = a[i];
			a[i] = a[j];
			a[j] = temp;
		}
	}
//	cout<<"BubbleSort:"<<endl;
//	Show(a,"BubbleSort");
	cout<<" time:"<<(clock()-st);	
	
}
void Merge(List s,List t,int i, int m,int n)
{
	int j, k ,p;
	for(j= m +1,k=i;i<=m&&j<=n;k++)
	{
		if(s[i]<s[j])
		t[k] = s[i++];
		else
		t[k] = s[j++];
	 } 	 
	if(i<=m) 
	for(p=0;p<=m-i;p++)
	t[k+p] = s[i+p];
	if(j<=n)
	for(p=0;p<=n-j;p++)
	t[k+p] = s[j+p];
}
void MSort(List S,List T,int s,int t)
{
//	show(T);
//	getch();
	int m;
	List t2;
	if(s==t)
	{
		T[s]=S[s];
	}
	else 
	{
		m = (s+t)/2;
		MSort(S,t2,s,m);
		MSort(S,t2,m+1,t);
		Merge(t2,T,s,m,t);
	}
	
	
}
void MergeSort(List a)
{
//	Print(a);
	clock_t st = clock();
	MSort(a,a,1,Len-1);
//	Print(a);
//	Show(a,"MergeSort:");
	cout<<" time:"<<(clock()-st);
}
void HeapAdjust(List r, int s, int m)
{
	int rc = r[s];
	for(int j=2*s;j<=m;j*=2)
	{
		if(j<m&&r[j]<r[j+1]) ++j;
		if(rc>=r[j]) break;
		r[s] = r[j];
		s = j;
	}
	r[s] = rc;
}

void HeapSort(List r)
{
//	cout<<"HeapSort:"<<endl;
	clock_t st = clock();
	for(int i=Len/2;i>0;--i)
	HeapAdjust(r,i,Len);
	int temp;
	for(int i=Len;i>1;i--)
	{
		temp = r[1];
		r[1] = r[i];
		r[i] = temp;
		HeapAdjust(r,1,i-1);
	}
//	Show(r,"HeapSort");
	cout<<" time:"<<(clock()-st);	
}

int Partition(List &r, int low, int high)
{
	int p = r[low];
	while(low<high)
	{
		while(low<high&&r[high]>=p)
		--high;
		r[low] = r[high];
		while(low<high&&r[low]<=p)
		++low;
		r[high] = r[low];
	}
	r[low] = p;
	return low;
	
}
void QSort(List &a, int low, int high)
{
	if(low<high)
	{
		int p = Partition(a,low,high);
		QSort(a,low,p-1);
		QSort(a,p+1,high);		
		
	}
	
	
}
void QuickSort(List &a)
{
	clock_t st = clock();
//	cout<<"QuickSort:"<<endl;
	QSort(a,1,Len);
//	Show(a,"QuickSort:");
	cout<<" time:"<<(clock()-st);
}





void distribute(slcell r[],int i,ArrType &f,ArrType &e)  
{  

  	int j,p;  
	
	for(j=0;j<10;j++) 
	{
		f[j]=0;
 	}
	for(p=r[0].next; p; p=r[p].next)  
	{  
	    j=(r[p].num/i)%10;

	    if(!f[j])
	    {
	    	f[j]=p;
		}
		else r[e[j]].next=p;
		e[j]=p;
	}
}
      
void collect(slcell r[],int i,ArrType &f,ArrType &e)  
{  
 	int j,t;  
   
	for (j=0; !f[j]; j++);
	r[0].next=f[j];
	t=e[j];
	while(j<10)
	{
		for(j=j+1; j<9&&!f[j]; j++ );
		
			if(f[j])
			{
				r[t].next=f[j];
				t=e[j];
			}
	 } 
	 r[t].next=0;
}                   
void Output(slcell r[], int head)  
{  
    while (head!=0)
	{  
        printf("%d ", r[head].num);  
        head = r[head].next; 
    }  
    cout<<endl;
}      

void RadixSort(slcell r[])
{
	clock_t st = clock();

	int i;
	for(i=0;i<Len;i++)
	{
		r[i].next=i+1;
	}
	r[Len].next=0;
	for(i=1; i<=100000; i*=10)
	{
		distribute(r,i,f,e);
		collect(r,i,f,e);
	}
	cout<<" time:"<<(clock()-st);
	
//	Output(r,1);
//	Show2(r,"end:");
}


void ShellInsert(List r,int dk)	//3
{
	int i,j;
//	cout<<" ";
	for(i=dk+1;i<=Len;i++)
	{
		if(r[i]<r[i-dk])
		{
			r[0]=r[i];
			for(j=i-dk;j>0&&r[0]<r[j];j-=dk)
			{
				r[j+dk]=r[j];
			}
			r[j+dk]=r[0];
		}
	}
}

void ShellSort(List r,int dlta[],int t)
{
	clock_t st = clock();
	int k;
	for(k=0;k<t;k++)
	{
		ShellInsert(r,dlta[k]);
	}

	cout<<" time:"<<(clock()-st);
}
