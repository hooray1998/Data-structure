#include<stdio.h>
#include<malloc.h>
#include<stdlib.h>
#include<string.h> 
#include<conio.h>
#include<stack>
#include<queue>
#include<iostream>
#include<fstream>
#define TRUE              1
#define FALSE             0
#define OK                1
#define ERROR             0
#define INFEASIBLE       -1 
#define OVERFLOW         -2
using namespace std;

int depth ;
int count ;
char s[64][20];

typedef int TElemType;
typedef int Status; 
typedef struct BiTNode
{
	TElemType data;
	struct BiTNode  *lchild,*rchild; 
}BiTNode,*BiTree;

ifstream in("data2.txt");
//最简单的visit函数
Status Print(TElemType e)
{
	printf("%-4d ",e);
	return OK;
 } 

Status InitBiTree(BiTree &T)
{
	T = NULL;
	return OK;
} 

 //创建二叉树--先序输入--递归
BiTree  createBiTreePreOrder()
{
	BiTree bt=NULL;
	TElemType ch;
	in>>ch;
//	cout<<ch<<" ";
	if(ch==-1)
		bt=NULL;
	else
	{
		bt=(BiTree )malloc(sizeof(BiTNode));
		bt->data=ch;
		bt->lchild=createBiTreePreOrder();
		bt->rchild=createBiTreePreOrder();
	}
	return bt;
}


//按照definition构造二叉树
Status CreateBiTree(BiTree &T) 
{
  	T = createBiTreePreOrder();
  	return OK;

}
//先序遍历T
Status PreOrderTraverse(BiTree T,Status(*Visit)(TElemType e) )
{
	if(T)
	{
		if(Visit(T->data))
			if(PreOrderTraverse(T->lchild,Visit))
				if(PreOrderTraverse(T->rchild,Visit))
				return 1;
		return 0;
	}
	return 1;
}
//中序遍历T
Status InOrderTraverse(BiTree T,Status(*Visit)(TElemType e) )
{
	if(T)
	{
		if(InOrderTraverse(T->lchild,Visit))
			if(Visit(T->data))
				if(InOrderTraverse(T->rchild,Visit))
				return 1;
		return 0;
	}
	return 1;
}

//

////后序遍历T
Status PostOrderTraverse(BiTree T,Status(*Visit)(TElemType e) )
{
	if(T)
	{
		if(PostOrderTraverse(T->lchild,Visit))
			if(PostOrderTraverse(T->rchild,Visit))
				if(Visit(T->data))
				return 1;
		return 0;
	}
	return 1;
}

//




//先序遍历--非递归
int PreOrderTraverse2(BiTree T,int (*visit)(TElemType e))
{
	stack <BiTree> S;
	BiTree p = T;
	while(p || !S.empty())
	{
		if(p)
		{
			if(!visit(p->data)) return 0;  //错误返回
			S.push(p->rchild);
			p=p->lchild;
		}
		else 
		{
			p = S.top();
			S.pop();
		}
	  
	}
	return 1; //正常返回

}

//中序遍历--非递归
int InOrderTraverse2(BiTree T,int (*visit)(TElemType e))
{
	stack <BiTree> S;
	BiTree p = T;
	while(p || !S.empty())
	{
		if(p)
		{
			S.push(p);	
			p=p->lchild;
		}
		else 
		{
			p = S.top();
			S.pop();
			if(!visit(p->data)) return 0;  //错误返回
			p=p->rchild;
		}
	}
	return 1;   //正常返回
}
int PostOrderTraverse2(BiTree T,int (*Visit)(TElemType e)) //用last记录上一个访问的右子树 
{
	BiTree last = NULL;
	BiTree p = T;
	stack<BiTree> S;
	while(p||!S.empty())
	{
		while(p)
		{
			S.push(p);
			p = p->lchild;
		}
		p = S.top();
		if(p->rchild&&p->rchild!=last)
			p = p->rchild;
		else
		{
			if(!Visit(p->data)) return 0;
			S.pop();
			last = p;
			p = NULL;//为了下一次的循环 ,因为p的左子树已经遍历过了. 
		} 
	
	}
	return 1;
} 






