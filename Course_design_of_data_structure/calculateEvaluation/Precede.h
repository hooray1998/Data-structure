#include"input.h"
char Precede(char top,char c)//�Ƚ��ַ������ȼ���ϵ���Լ������ŵ�׼ȷ�Լ�� 
{
	
	if(top=='+'||top=='-')
	{
		if(c=='+'||c=='-'||c==')'||c=='#')
		{
			return '>';
		}
		else return '<';
	}
	if(top=='*'||top=='/')
	{
		if(c=='(')
		{
			return '<';
		
		}
		else{
			 return '>';
		}
	}
	if(top=='(')
	{
		if(c=='#'||c=='(')
		{
			cout<<"����ȱ�� ��"<<endl;
			exit(0);
		}
		else if(c==')')
			{
				return '=';
			}
			else{
				return '<';
			} 
	}
	if(top==')')
	{
		return '>';
	}
	if(top=='#')
	{
		if(c=='#')
		{
			return '=';
		}
		else if(c==')')
			{
				cout<<"����ȱ�� ��"<<endl;
				exit(0);
			}
			else return '<';
	}
}

