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


 
typedef struct Letter//�洢�ַ���ֵ�����ֵ��������Լ����� 
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


//int letter[256];//��¼��Ч�ģ������ڵģ�����������ַ���λ�� 
int letterNum;
int asc[256];//a-z, 
int locate[256];//�ַ�c��λ�ô�����letterlist��lacate��c������������������¼�ַ����ڱ�����λ�� 
Letter letterlist[256];//����� 

queue<char>compressCode;//�洢ѹ����ɺ������ѹ���ַ� 
queue<char>rcode;//
char in[20];//��¼Ԥѹ�����ļ��� 
char cmp[20];//��¼ѹ������ļ��� 
char fd[20];//��¼�������ļ��� 
