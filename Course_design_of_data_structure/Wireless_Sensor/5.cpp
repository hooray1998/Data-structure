/*
5�����ߴ���������(����) ��ͼ��
[��������]
��һ��ֱ�����꣨��Ϊ100*100��ƽ���У�����ֲ�n���ߴ�������㣬��۵�Ϊԭ�㣨0��0����Ҫ��ÿ�����ߴ�����������Ϣ���䵽��۵㣬�������ͨ��������ʽʵ�֣������ߴ���������������ͨ�ž���Ϊ10�������ܺ������ƽ�������ȣ�����ʱ�����������ȡ�
����һ������ÿ����㴫�䵽��۵�����ʱ��ͨ���������޷�ʵ�ִ���Ľ�㣬�����ų���
������������������紫�䵽��۵��ƽ���ܺ���С����ṹ��
[����Ҫ��]
�����ʽ�� ����ĵ�һ�а���һ��������n����ʾ���ߴ�����������������ʹ��1, 2, 3, ����n���α�š�  ������n�У�ÿ�а�����������ni, xi, yi������xi, yi��ʾ��ni���������꣬Ҫ����ı��ļ������롣
�����ʽ��
����һ�����ÿ����㵽��۵�����ʱ��ͨ�����������ʱ��;�����㡣  
�����������������絽��۵��ƽ���ܺ���С����ṹ������ƽ����С�ܺĺ����ӷ�ʽ��

*/
//#include"func_������.h"
#include<fstream>
#include"MiniSpanTree.h"




int main()
{
	ALGraph G;
	CreateALGraph(G);
	DeleteDot(G);
	
	PathMatrix P;
	ShortPathTable D; 
	ShortestPath_DIJ(G,0,P,D);
  //Show Answer  
  	ofstream out("���·��.txt");
	for(int i=0;i<G.vexnum;i++)
	{
		if(link[i])
		{
			cout<<"dot "<<i<<" shortPath across dots is follow��";
			out<<"dot "<<i<<" shortPath across dots is follow��";
			for(int j=0;j<G.vexnum;j++)
			{
				if(P[i][j])
				{
				  	cout<<j<<" ";
					out<<j<<" ";
				}
			}
			cout<<"path is ";
			out<<"path is ";
			printf("%4.2f\n",D[i]);
			out<<" "<<D[i]<<endl;
		}
	}
	out.close();
  	system("pause"); 
	
	MiniSpanTree_PRIM(G);
		
	
	return 0;
 } 
