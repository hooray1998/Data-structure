#include"Store_func.cpp"
/*
1��������վ��Ϣ����������������
[��������]
���һ�����򣬶�������Ϣ����������Ϣ���������̱�ţ��������������ȣ�����Ʒ����1���۸�1������1��������Ʒ����2���۸�2������2��������Ʒ����3���۸�3������3������
������Ʒ���ư���(ë����ˢ���������࣬ϴ��ˮ����ԡ¶��)��ÿ�����̾�����������ȷ��������Ʒ���۸����ļ����룬������ʼΪ0��
[����Ҫ��]
��1������һ����������洢����������Ϣ������30�������Ա��Ϊ�򣬱�Ŵ�1��ʼ���������ļ��ж�ȡ���ݣ����ܽ����ݴ洢���ļ���������Ϣ�������ݽṹ������ơ�
��2����������ɾ���̡��������̣�����Զ���һ����������β����ɾ�������Ա��Ϊ׼�����޸ĺ������ı�ţ����ֱ�������ԡ�
��3����������ɾѡ�������е���Ʒ���޸���Ʒ�۸�
��4����ѯĳһ����Ʒ���ƣ�����һ��˫��ѭ�����������Ϣ�ǰ�������Ʒ���������̱�ţ��������������ȣ���Ʒ���ƣ��۸����������������������򣬲�����һ��ʾ��
��5������ĳһ���̵���Ʒ���޸ĵ�����������Ʒ����Ϣ��������
��6���κε�������Ϣ�仯��ʵ���ļ��洢��

*/
typedef struct SNode{
	Store store;
	SNode* nextstore;
}SNode,*Sptr; 

typedef struct BGNode{//˫�������洢��ǰ���ҵ���Ʒ 
	Goods goods;
	Sptr s;//�洢���̵�ַ �����㹺��ʱֱ�ӶԵ�����Ϣ���в��� 
	BGNode* pre;
	BGNode* next;

}BGNode,*BGN;

 
void menu()
{
	system("pause");
	printf("1--show stores\n");
	printf("2--add store\n");
	printf("3--delete store\n");
	printf("4--add store's goods\n");
	printf("5--delete store's goods\n");
	printf("6--modify store's goods\n");
	printf("7--buy buy buy\n");
	printf("0--exit\n");
	cout<<"please input order number."<<endl<<endl;
}
void Read_in_Store(Sptr slist);//���ļ����ݶ���������� 
void write_in_Store(Sptr slist);//��������Ϣ�����ļ� 
void ShowAllStore(Sptr slist);//չʾ���е�����Ϣ 
void ShowBGList(BGN bglist);//չʾ��ǰ˫������Ʒ��Ϣ 
bool SortBGList(BGN bl);//���������� 
void SearchGoods(Sptr slist);//����ĳ��Ʒ ����������ʾ������������ 
void AddStore(Sptr slist);//���ӵ��� 
void AddGoods(Sptr slist);//������Ʒ
void DeleteStore(Sptr slist);//ɾ������ 
void DeleteGoods(Sptr slist); //ɾ����Ʒ 
void ModifyGoods(Sptr slist);//�޸���Ʒ 
void Show(Sptr slist); //չʾ���� �� ��������ʾ�������� 
int main()
{
	Sptr slist;
	slist = new SNode;
	slist->nextstore = NULL;
	Read_in_Store(slist);
	
	do{
		system("cls");
		menu();
		int Exit = 0;//�˳��ж� 
		char ch = getch();
		switch(ch)
		{
			case '1':{
				
				Show(slist);
				
				break;
			}
			case '2':{
				AddStore(slist);
				write_in_Store(slist);
				break;
			}
			case '3':{
				DeleteStore(slist);
				write_in_Store(slist);
				break;
			}
			case '4':{
				AddGoods(slist);
				write_in_Store(slist);
				break;
			}
			case '5':{
				DeleteGoods(slist);
				write_in_Store(slist);
				break;
			}
			case '6':{
				ModifyGoods(slist);
				write_in_Store(slist);
				break;
			}
			case '7':{
				SearchGoods(slist);
				write_in_Store(slist);
				break;
			}
			case '0':{
				Exit = 1;
				break;
			}
			default :{
				cout<<"ָ��������������"<<endl;
				break;
			} 
		}
		if(Exit) break;
		
	}while(1);
	
	
	return 0;
 } 
 
 void Read_in_Store(Sptr slist)
{
	ifstream fs("store.txt");
	
	if(fs.fail())
	{
		cout<<"error in file'store.txt'. "<<endl;
		exit(0);
	}
	string storename,goodsname;
	int c,goodsnum;
	float p;
	int s;
	int count=1;
	Sptr temp=slist,sp;
	while(!fs.eof()) //������Ʒ����ʱ��ѭ��������Ʒ��Ϣ���������ӵ������� 
	{
		fs>>storename>>c;
		if(fs.eof()) break;
		fs>>goodsnum;
		sp = new SNode;
		sp->store.set(count,storename,c,0);
		temp->nextstore = sp;
		temp = sp;
		sp->nextstore = NULL;
		int k = goodsnum;
		while(k--)
		{
			fs>>goodsname>>p>>s;
			pGoods pg= new Goods;
			pg->name = goodsname;
			pg->price= p;
			pg->sales= s;
			sp->store.addGoods(pg);
			
		}
				
		count++;
		
	}
	temp->nextstore = NULL;

	fs.close(); 
}

void write_in_Store(Sptr slist)
{
	ofstream fs("store.txt");
	
	string storename,goodsname;
	int c,goodsnum;
	float p;
	int s;
	int count=1;
	Sptr temp=slist->nextstore,sp;
	pGoods  pg,pg2;
	while(temp)//д�������Ϣ��������Ʒд���ļ� 
	{
		goodsnum = temp->store.getgoodsnum();
		fs<<temp->store.getname()<<" "<<temp->store.getCredit()<<" "<<goodsnum<<" "<<endl;
		pg = temp->store.getfirstGoods();
		while(goodsnum--)
		{
			fs<<pg->name<<" "<<pg->price<<" "<<pg->sales<<endl;
			pg = pg->nextG;
		}
		temp = temp->nextstore;
		
	}
		
	fs.close(); 	

}
void Show(Sptr slist)
{
	cout<<"1-չʾ����	others-����������"<<endl;
	char c = getch();
	if(c=='1')
	 ShowAllStore(slist);
	else
	{
		cout<<"please Store's name"<<endl;
		string n;
		cin>>n;
		Sptr p;
		pGoods q;
		p = slist->nextstore;
		while(p)
		{
			if(p->store.getname()==n)//���ҳɹ� 
			{
				break;
			}
			p=p->nextstore;
		}
		if(p==NULL) 
		{
			cout<<"Not find this store"<<endl;
		}
		else
		{
			p->store.showGoods();
		}
		
	}
	system("pause");
	
	
 } 
void ShowAllStore(Sptr slist)
{
	cout<<"���е�����Ϣ����"<<endl;
	Sptr pp = slist->nextstore;
	while(pp)
	{
		pp->store.showGoods();
		pp = pp->nextstore;
		
	 } 	
	cout<<endl; 
}
void AddStore(Sptr slist)
{
	cout<<"������������Ϣ(����+����)"<<endl;
	string n;
	int c,count=1;
	cin>>n>>c;
	Sptr newstore = new SNode;
	
	Sptr p=slist;
	while(p->nextstore)//ͳ�Ƶ��̱�� 
	{
		count++;
		p=p->nextstore;
	}
	newstore->store.set(count,n,c,0);//�����Ӧ���̺�һ����������� 
	p->nextstore = newstore;
	newstore->nextstore = NULL;
	cout<<"������ӳɹ�"<<endl;
	
	cout<<"�Ƿ����������Ʒ�� 1-�ǣ�other key-��"<<endl;
	char cc = getch();
	if(cc=='1')
	{
		cout<<"�����뽫Ҫ���ӵ���Ʒ����"<<endl;
		int goodsnum;
		cin>>goodsnum;
		
		while(goodsnum--)
		{
			pGoods pg = new Goods;
			cout<<"��������Ʒ����+�۸�"<<endl;
			string n;
			float p;
			cin>>n>>p;
			pg->setvalue(n,p,0);
			newstore->store.addGoods(pg);
		}
		cout<<"��Ʒ��ӳɹ�"<<endl;
	 } 
}
void ShowBGList(BGN bglist)
{
	cout<<"+++++++++++++++++++++++"<<endl; 
	BGN bb = bglist->next;
	while(bb)
	{
		cout<<"�̺ţ�";
		printf("%-4d",bb->s->store.getNumber());
		cout<<"��������"<<bb->s->store.getname();
		cout<<"	�۸�";
		printf("%-5.2f",bb->goods.price);
		cout<<"	������"<<bb->goods.sales<<endl;
		
		bb = bb->next;
	}
	cout<<"+++++++++++++++++++++++"<<endl; 	

}
bool SortBGList(BGN bl)//��������������Ʒ��Ϣ 
{
	if(!bl->next) return false;
	BGN p=bl->next->next,q,r,pp;
	
	
	for(;p;p=p->next)
	{
		int k=0,kk=0;
		for(q=p->pre;q->pre;q=q->pre)
		{
			if(q->goods.sales>=p->goods.sales)
			{
				if(q!=p->pre)//���ǵ�ǰλ������� 
				{
	
				pp= p;
				p = p->pre;
				if(pp->next)//�ж��Ƿ񵽴�ĩβ 
				pp->next->pre = pp->pre;
				else
					kk=1;
				pp->pre->next = pp->next;
				
				pp->next = q->next;
				pp->pre  = q;
				q->next = pp;
				pp->next->pre = pp; 
				
				}
				k=1;
				break;
			}	
		} 
		
		if(!k)
		{	
				pp= p;
				p=p->pre;

				if(pp->next)//�ж��Ƿ񵽴�ĩβ 
				pp->next->pre = pp->pre;
				else
					kk=1;
				pp->pre->next = pp->next;
				pp->next = bl->next;
				pp->pre  = bl;
				bl->next = pp;
				pp->next->pre = pp; 				
		 }
		if(kk) break;
	} 
	return true;
}

void SearchGoods( Sptr slist)
{
	string n;
	cout<<"��������Ҫ��ѯ����Ʒ����"<<endl;
	cin>>n;
	
	BGN bglist= new BGNode;
	BGN bg = bglist;
	bg->next = NULL;
	bg->pre = NULL;
	
	Sptr p = slist->nextstore;
	pGoods pg;
	while(p)
	{
		pg = p->store.findGoods(n);
		if(pg)//�����ҳɹ�����ӵ������� 
		{
			bg->next = new BGNode;
			bg->next->goods.setvalue(n,pg->price,pg->sales);
			bg->next->s = p;
			bg->next->next = NULL;
			BGN b = bg;
			bg = bg->next;
			bg->pre = b;
			
		}
		
		p = p->nextstore;
	}
	
	SortBGList(bglist);
	ShowBGList(bglist);
	cout<<"�Ƿ���1-�ǣ�0-��"<<endl;
	char c = getch();
	if(c=='1')
	{
		cout<<"������õ��̱��"<<endl;
		int num;
		cin>>num;
		
		BGN buy=bglist->next;
		int k=0;
		while(buy)
		{
			if(num==buy->s->store.getNumber())
			{
				buy->s->store.addSales(buy->s->store.findGoods(n));
				cout<<"����ɹ�"<<endl; 
				buy->s->store.showGoods();
				k=1;
				break;
			}
			buy = buy->next;
		}
		if(k==0) cout<<"δ�ҵ��õ���,����ʧ��"<<endl;
		system("pause");
		
	}
	
	 
}
void DeleteStore(Sptr slist)
{
	Sptr p,q;
	int count=1;
	string n;
	cout<<"������ɾ���ĵ�����"<<endl;
	cin>>n;
	p = slist;
	while(p->nextstore)
	{
		if(p->nextstore->store.getname()==n)
		{
			count = p->nextstore->store.getNumber();
			break;
		}
		
		p=p->nextstore;
	}
	q = p->nextstore;
	p->nextstore = q->nextstore;
	delete q;
	p = p->nextstore;
	while(p)
	{
		p->store.setnumber(count++);
		p = p->nextstore;
	}
	
	cout<<"ɾ���ɹ�"<<endl;
	
}
void DeleteGoods(Sptr slist)
{
	cout<<"please Store's name"<<endl;
	string n;
	cin>>n;
	Sptr p;
	pGoods q;
	p = slist->nextstore;
	while(p)
	{
		if(p->store.getname()==n)	break;
		p=p->nextstore;
	}
	if(p==NULL) 
	{
		cout<<"Not find this store"<<endl;
	}
	else
	{
		p->store.showGoods();
		cout<<endl;
		cout<<"please input Goods'name"<<endl;
		string gn;
		cin>>gn;
		if(p->store.deGoods(gn))
		cout<<"ɾ���ɹ�"<<endl;
		else
		cout<<"ɾ��ʧ��"<<endl;
	}
}
void ModifyGoods(Sptr slist)
{
	cout<<"please Store's name"<<endl;
	string n;
	cin>>n;
	Sptr p;
	pGoods q;
	p = slist->nextstore;
	while(p)
	{
		if(p->store.getname()==n)	break;
		p=p->nextstore;
	}
	if(p==NULL) 
	{
		cout<<"Not find this store"<<endl;
	}
	else
	{
		p->store.showGoods();
		cout<<endl;
		cout<<"please input Goods'name"<<endl;
		string gn;
		cin>>gn;
		q=p->store.findGoods(gn); 
		cout<<"please input it's price"<<endl;
		cin>>q->price;
		cout<<"modify �ɹ�"<<endl;
	}
	
}
void AddGoods(Sptr slist)
{
	cout<<"please Store's name"<<endl;
	string n;
	cin>>n;
	Sptr p;
	pGoods q;
	p = slist->nextstore;
	while(p)
	{
		if(p->store.getname()==n)
		{
			break;
		}
		p=p->nextstore;
	}
	if(p==NULL) 
	{
		cout<<"Not find this store"<<endl;
	}
	else
	{
		cout<<"�����뽫Ҫ���ӵ���Ʒ����"<<endl;
		int goodsnum;
		cin>>goodsnum;
		
		while(goodsnum--)
		{
			pGoods pg = new Goods;
			cout<<"��������Ʒ����+�۸�"<<endl;
			string n;
			float p2;
			cin>>n>>p2;
			pg->setvalue(n,p2,0);
			p->store.addGoods(pg);
		}
		cout<<"��Ʒ��ӳɹ�"<<endl;
		system("pause"); 
	}	
}
