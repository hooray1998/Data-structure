#include"input.h"
char Precede(char top,char c)//比较字符串优先级关系，以及对括号的准确性检测 
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
			cout<<"错误：缺少 ）"<<endl;
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
				cout<<"错误：缺少 （"<<endl;
				exit(0);
			}
			else return '<';
	}
}

