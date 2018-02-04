#include<iostream>
using namespace std;
#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<string.h>

#define MAX_LENGTH 50
stack<char>Ch;//存储操作符 
stack<char>Ch2;//存储ch的逆置，实现ch栈的遍历 
stack<float>Num;//存储操作数 
stack<float>Num2;//存储Num栈的逆置，实现遍历 
class P{
	public:
	int flag;//记录当前为操作数还是操作符，0--数，1--符 
	float num;//0
	char c;//1
};
P p[MAX_LENGTH];//存储表达式 


bool In(char c)//判断是否为操作符 
{
	if(c=='#'||c=='('||c==')'||c=='+'||c=='-'||c=='*'||c=='/')
	return true;
	return false;	
}

void input()
{

	
	int num=0;
	char s[30];
	cin>>s;
	for(int i=0;i<strlen(s);i++)
	{
		if(In(s[i]))//若当前字符为操作符，存储 
		{
			p[num].flag=1;
			p[num++].c = s[i];
		}
		else if(s[i]>='0'&&s[i]<='9')//若为操作数，则将字符串该位置往后映射，隔离出前面为float的部分。 
		{
			float t;
			char k[30];
			sscanf(&s[i],"%f%s",&t,k);	//该函数在此处的功能就是
										//将字符串前面的float格式的内容存入t，字符串剩余部分存入k 
			strcpy(s,k);//更新字符串 
			i=-1;//字符串从0再次遍历 
			p[num].flag = 0;
			p[num++].num = t;
		}
		else if(s[i]=='.')
		{
			printf("小数点的位置有误");
			exit(0);
		}
		else
		{
			printf("出现非法字符");
			cout<<s[i]<<endl; 
			exit(0);
		}
	
	}
	
	if(p[0].flag==1&&p[0].c!='(')
	{
		cout<<"开头出错"<<endl;
	}
	
}
