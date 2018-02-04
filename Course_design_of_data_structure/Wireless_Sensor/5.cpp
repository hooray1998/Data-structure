/*
5、无线传感器网络(必做) （图）
[问题描述]
在一个直角坐标（设为100*100）平面中，随机分布n无线传感器结点，汇聚点为原点（0，0），要求将每个无线传感器结点的信息传输到汇聚点，传输可以通过多跳方式实现，设无线传感器结点最大无线通信距离为10，传输能耗与距离平方成正比，传输时间与距离成正比。
问题一：建立每个结点传输到汇聚点的最短时间通道，并给无法实现传输的结点，将其排除。
问题二：建立整个网络传输到汇聚点的平均能耗最小网络结构。
[基本要求]
输入格式： 输入的第一行包含一个正整数n，表示无线传感器结点数量。结点使用1, 2, 3, ……n依次标号。  接下来n行，每行包含三个整数ni, xi, yi，其中xi, yi表示第ni个结点的坐标，要求从文本文件中输入。
输出格式：
问题一：输出每个结点到汇聚点的最短时间通道，包括最短时间和经过结点。  
问题二：输出整个网络到汇聚点的平均能耗最小网络结构，包括平均最小能耗和连接方式。

*/
//#include"func_传感器.h"
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
  	ofstream out("最短路径.txt");
	for(int i=0;i<G.vexnum;i++)
	{
		if(link[i])
		{
			cout<<"dot "<<i<<" shortPath across dots is follow：";
			out<<"dot "<<i<<" shortPath across dots is follow：";
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
