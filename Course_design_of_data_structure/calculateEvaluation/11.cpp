/*
11、算术表达式求值 (选做) （栈）
[问题描述]
　　一个算术表达式是由操作数(operand)、运算符(operator)和界限符(delimiter)组成的。假设操作数是正实数，运算符只含加减
乘除等四种运算符，界限符有左右括号和表达式起始、结束符“#”，如：#6+15*（21-8/4）#。引入表达式起始、结束符是为了方便。
编程利用“运算符优先法”求算术表达式的值。
[基本要求]
（1） 从键盘或文件读入一个合法的算术表达式，输出正确的结果。
（2） 显示输入序列和栈的变化过程。
（3） 考虑算法的健壮性，当表达式错误时，要给出错误原因的提示。
（4） 实现非整数的处理。
*/
#include"Precede.h"

float Operat(float a, char t, float b)//运算a t b。 
{
	if(t=='*')
	return a*b;
	else if(t=='+')
	return a+b;
	else if(t=='-')
	return a-b;
	else if(t=='/')//除数不能为零 
	{
		if(b<0.0001&&b>-0.0001)
		{
			cout<<"error in /"<<endl;
			exit(0);
		}
		return a/b;
	 } 
	
	
}
void Expression()
{
	int n=0;
	Ch.push('#');
	
	
	while(p[n].flag==0||p[n].c!='#'||Ch.top()!='#')//当栈顶为#并且当前字符也为#时退出循环 
	{

		if(p[n].flag==0)//若为操作数，则存入Num栈 
		{
			Num.push(p[n].num);
			n++;
		}	
		else//若为符号 
		{
			switch(Precede(Ch.top(),p[n].c))//判断优先级关系 
			{
				case '<':{
					Ch.push(p[n].c); 
					n++;//读取下一个 
					break;
				}	
				case'=':{//去括号 
					Ch.pop();
					n++;//读取下一个 
					break;
					
				}			
				case'>':{//出栈进行运算 
					char t;
					float a,b;
					t = Ch.top();
					Ch.pop();
					b = Num.top();
					Num.pop();
					a = Num.top();
					Num.pop();
					Num.push(Operat(a,t,b));//将结果压栈 
					
					break;
				}		
			}
		}
		
		//展示两个栈中的存储情况，用2栈辅助。全部出栈再压栈 
		cout<<endl<<"Ch:";
		while(!Ch.empty())
		{
			Ch2.push(Ch.top());
			Ch.pop();
		}
		while(!Ch2.empty())
		{
			cout<<Ch2.top()<<" ";
			Ch.push(Ch2.top());
			Ch2.pop();
		}
		cout<<endl<<"Num:";
		while(!Num.empty())
		{
			Num2.push(Num.top());
			Num.pop();
		}
		while(!Num2.empty())
		{
			cout<<Num2.top()<<" ";
			Num.push(Num2.top());
			Num2.pop();
		}
		system("pause");	//操作一次暂停一次	

	}	
	
}
int main()
{
	while(1)
	{
		input();//将表达式存储 
		Expression();//运算 
	}
	return 0;
}
