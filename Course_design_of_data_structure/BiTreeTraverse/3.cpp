#include"BiTree的遍历.h"

int pre_value = -1;
int compare(int k)//关键函数。替换掉原来的wisit函数。 
{
	if(k<pre_value) 
	return false;
	pre_value = k;
	return true;
}
//中序遍历--非递归
int Judge_sort_BiTree(BiTree T,int (*visit)(TElemType e))//中序遍历函数，只是改了个名字 
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
			if(!visit(p->data)) return 0;  //每次访问的时候判断该数与前一个数的大小，若大则ok，若小，则返回false，不是排序二叉树。 
			p=p->rchild;
		}
	}
	return 1;   //正常返回
}
////层序遍历，顺便求其宽度。 
//用双队列实现。将其中一个栈中的结点pop出，并将其孩子结点存到另一个栈中，不断取其size的最大值，循环直到两栈均空 
Status LeverOrderTraverse(BiTree T,Status(*Visit)(TElemType e))
{
	if(!T) return 0;
	int max=1;
	queue<BiTree> Q;
	queue<BiTree> Q2;//使用双队列 
	BiTree p = NULL;
	Q.push(T);//首先将根节点压栈 
	while(!Q.empty()||!Q2.empty())
	{
		while(!Q.empty())//不断pop并将子节点存入另一个栈 
		{
		
			p = Q.front();
			Q.pop();
			if(!Visit(p->data)) return 0;
			
			if(p->lchild) 
				Q2.push(p->lchild);
			if(p->rchild)
				Q2.push(p->rchild);
		}
		max = (Q2.size()>max)?Q2.size():max;//取宽度的最大值 
		while(!Q2.empty())//同上 
		{
		
			p = Q2.front();
			Q2.pop();
			if(!Visit(p->data)) return 0;
			
			if(p->lchild) 
				Q.push(p->lchild);
			if(p->rchild)
				Q.push(p->rchild);
	
		}
		max = (Q.size()>max)?Q.size():max;
	}
	
	cout<<endl<<"width:"<<max<<endl; 
	
}

//返回T的深度
int BiTreeDepth(BiTree T) 
{
	if(T)
	{
		int ldepth = BiTreeDepth(T->lchild);//递归求孩子结点的深度 
		int rdepth = BiTreeDepth(T->rchild);
		return (ldepth>rdepth)?(ldepth+1):(rdepth+1);//返回较大的那个加一为本结点的深度 
	}
	else
	return 0;//空则返回深度0 
	
	
	
}



int main()
{
	BiTree T;
	InitBiTree(T);
//	printf("先序输入创建一个二叉树，空树用空格表示\n");
	T = createBiTreePreOrder();
//	ShowBiTree(T);	
	
	 
	
	if(Judge_sort_BiTree(T,compare))
	cout<<"是二叉排序树"<<endl;
	else
	cout<<"不是二叉排序树"<<endl; 
	printf("\nPreOrderTraverse   "); 
	
	PreOrderTraverse(T,Print);
	putchar(10);
	printf("InOrderTraverse   "); 
	InOrderTraverse(T,Print);
	putchar(10);
	printf("PostOrderTraverse   "); 
	PostOrderTraverse(T,Print);

	putchar(10);

	printf("PreOrderTraverse2  "); 
	PreOrderTraverse2(T,Print);
	putchar(10);
	printf("InOrderTraverse2  "); 
	InOrderTraverse2(T,Print);
	putchar(10);
	printf("PostOrderTraverse2  "); 
	PostOrderTraverse2(T,Print);

	putchar(10);

	printf("LeverOrderTraverse  "); 
	LeverOrderTraverse(T,Print);
	
	cout<<"Depth:"<<BiTreeDepth(T)<<endl;



	
}
//A
