#include<iostream>
using namespace std;
#include<stdio.h>
#include<stdlib.h>
#include<stack>
#include<string.h>

#define MAX_LENGTH 50
stack<char>Ch;//�洢������ 
stack<char>Ch2;//�洢ch�����ã�ʵ��chջ�ı��� 
stack<float>Num;//�洢������ 
stack<float>Num2;//�洢Numջ�����ã�ʵ�ֱ��� 
class P{
	public:
	int flag;//��¼��ǰΪ���������ǲ�������0--����1--�� 
	float num;//0
	char c;//1
};
P p[MAX_LENGTH];//�洢���ʽ 


bool In(char c)//�ж��Ƿ�Ϊ������ 
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
		if(In(s[i]))//����ǰ�ַ�Ϊ���������洢 
		{
			p[num].flag=1;
			p[num++].c = s[i];
		}
		else if(s[i]>='0'&&s[i]<='9')//��Ϊ�����������ַ�����λ������ӳ�䣬�����ǰ��Ϊfloat�Ĳ��֡� 
		{
			float t;
			char k[30];
			sscanf(&s[i],"%f%s",&t,k);	//�ú����ڴ˴��Ĺ��ܾ���
										//���ַ���ǰ���float��ʽ�����ݴ���t���ַ���ʣ�ಿ�ִ���k 
			strcpy(s,k);//�����ַ��� 
			i=-1;//�ַ�����0�ٴα��� 
			p[num].flag = 0;
			p[num++].num = t;
		}
		else if(s[i]=='.')
		{
			printf("С�����λ������");
			exit(0);
		}
		else
		{
			printf("���ַǷ��ַ�");
			cout<<s[i]<<endl; 
			exit(0);
		}
	
	}
	
	if(p[0].flag==1&&p[0].c!='(')
	{
		cout<<"��ͷ����"<<endl;
	}
	
}
