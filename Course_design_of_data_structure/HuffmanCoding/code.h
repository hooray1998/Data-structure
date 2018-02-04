#include<iostream>
#include<malloc.h>
#include<stdio.h>
#include<conio.h>
#include<fstream>
#include<stdlib.h>
#include<string.h >
#include<queue>
#include<list>
//#include<vector>

using namespace std;


 
typedef struct Letter//存储字符的值，出现的数量，以及编码 
{
	char value;
	int num;
	char *code;
	bool operator <(Letter l2)
	{
		if(num>l2.num) return true;
		else return false;
	}
}Letter;
typedef struct{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode,*HuffmanTree;

typedef char **HuffmanCode;


//int letter[256];//记录有效的，即存在的，个数非零的字符的位置 
int letterNum;
int asc[256];//a-z, 
int locate[256];//字符c的位置存在了letterlist【lacate【c】】。该数组用来记录字符存在编码表的位置 
Letter letterlist[256];//编码表 

queue<char>compressCode;//存储压缩完成后的所有压缩字符 
queue<char>rcode;//
char in[20];//记录预压缩的文件名 
char cmp[20];//记录压缩后的文件名 
char fd[20];//记录解码后的文件名 
