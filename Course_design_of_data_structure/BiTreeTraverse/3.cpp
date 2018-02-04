#include"BiTree�ı���.h"

int pre_value = -1;
int compare(int k)//�ؼ��������滻��ԭ����wisit������ 
{
	if(k<pre_value) 
	return false;
	pre_value = k;
	return true;
}
//�������--�ǵݹ�
int Judge_sort_BiTree(BiTree T,int (*visit)(TElemType e))//�������������ֻ�Ǹ��˸����� 
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
			if(!visit(p->data)) return 0;  //ÿ�η��ʵ�ʱ���жϸ�����ǰһ�����Ĵ�С��������ok����С���򷵻�false����������������� 
			p=p->rchild;
		}
	}
	return 1;   //��������
}
////���������˳�������ȡ� 
//��˫����ʵ�֡�������һ��ջ�еĽ��pop���������亢�ӽ��浽��һ��ջ�У�����ȡ��size�����ֵ��ѭ��ֱ����ջ���� 
Status LeverOrderTraverse(BiTree T,Status(*Visit)(TElemType e))
{
	if(!T) return 0;
	int max=1;
	queue<BiTree> Q;
	queue<BiTree> Q2;//ʹ��˫���� 
	BiTree p = NULL;
	Q.push(T);//���Ƚ����ڵ�ѹջ 
	while(!Q.empty()||!Q2.empty())
	{
		while(!Q.empty())//����pop�����ӽڵ������һ��ջ 
		{
		
			p = Q.front();
			Q.pop();
			if(!Visit(p->data)) return 0;
			
			if(p->lchild) 
				Q2.push(p->lchild);
			if(p->rchild)
				Q2.push(p->rchild);
		}
		max = (Q2.size()>max)?Q2.size():max;//ȡ��ȵ����ֵ 
		while(!Q2.empty())//ͬ�� 
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

//����T�����
int BiTreeDepth(BiTree T) 
{
	if(T)
	{
		int ldepth = BiTreeDepth(T->lchild);//�ݹ����ӽ������ 
		int rdepth = BiTreeDepth(T->rchild);
		return (ldepth>rdepth)?(ldepth+1):(rdepth+1);//���ؽϴ���Ǹ���һΪ��������� 
	}
	else
	return 0;//���򷵻����0 
	
	
	
}



int main()
{
	BiTree T;
	InitBiTree(T);
//	printf("�������봴��һ���������������ÿո��ʾ\n");
	T = createBiTreePreOrder();
//	ShowBiTree(T);	
	
	 
	
	if(Judge_sort_BiTree(T,compare))
	cout<<"�Ƕ���������"<<endl;
	else
	cout<<"���Ƕ���������"<<endl; 
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
