/*
11���������ʽ��ֵ (ѡ��) ��ջ��
[��������]
����һ���������ʽ���ɲ�����(operand)�������(operator)�ͽ��޷�(delimiter)��ɵġ��������������ʵ���������ֻ���Ӽ�
�˳�����������������޷����������źͱ��ʽ��ʼ����������#�����磺#6+15*��21-8/4��#��������ʽ��ʼ����������Ϊ�˷��㡣
������á���������ȷ������������ʽ��ֵ��
[����Ҫ��]
��1�� �Ӽ��̻��ļ�����һ���Ϸ����������ʽ�������ȷ�Ľ����
��2�� ��ʾ�������к�ջ�ı仯���̡�
��3�� �����㷨�Ľ�׳�ԣ������ʽ����ʱ��Ҫ��������ԭ�����ʾ��
��4�� ʵ�ַ������Ĵ���
*/
#include"Precede.h"

float Operat(float a, char t, float b)//����a t b�� 
{
	if(t=='*')
	return a*b;
	else if(t=='+')
	return a+b;
	else if(t=='-')
	return a-b;
	else if(t=='/')//��������Ϊ�� 
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
	
	
	while(p[n].flag==0||p[n].c!='#'||Ch.top()!='#')//��ջ��Ϊ#���ҵ�ǰ�ַ�ҲΪ#ʱ�˳�ѭ�� 
	{

		if(p[n].flag==0)//��Ϊ�������������Numջ 
		{
			Num.push(p[n].num);
			n++;
		}	
		else//��Ϊ���� 
		{
			switch(Precede(Ch.top(),p[n].c))//�ж����ȼ���ϵ 
			{
				case '<':{
					Ch.push(p[n].c); 
					n++;//��ȡ��һ�� 
					break;
				}	
				case'=':{//ȥ���� 
					Ch.pop();
					n++;//��ȡ��һ�� 
					break;
					
				}			
				case'>':{//��ջ�������� 
					char t;
					float a,b;
					t = Ch.top();
					Ch.pop();
					b = Num.top();
					Num.pop();
					a = Num.top();
					Num.pop();
					Num.push(Operat(a,t,b));//�����ѹջ 
					
					break;
				}		
			}
		}
		
		//չʾ����ջ�еĴ洢�������2ջ������ȫ����ջ��ѹջ 
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
		system("pause");	//����һ����ͣһ��	

	}	
	
}
int main()
{
	while(1)
	{
		input();//�����ʽ�洢 
		Expression();//���� 
	}
	return 0;
}
