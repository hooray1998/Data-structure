#include"Store_func.cpp"
/*
1、购物网站信息管理（必做）（链表）
[问题描述]
设计一个程序，对商铺信息管理，商铺信息包括：商铺编号，商铺名，信誉度，（商品名称1，价格1，销量1），（商品名称2，价格2，销量2），（商品名称3，价格3，销量3）…。
假设商品名称包括(毛巾，牙刷，肥皂，牙膏，洗发水，沐浴露等)，每个商铺具有其中事先确定若干商品及价格，由文件输入，销量初始为0。
[基本要求]
（1）建立一个单向链表存储所有商铺信息（至少30个），以编号为序，编号从1开始递增，从文件中读取数据，并能将数据存储在文件。商铺信息结点的数据结构自行设计。
（2）可以增、删商铺。增加商铺，编号自动加一，插入链表尾部；删除商铺以编号为准，并修改后续结点的编号，保持编号连续性。
（3）可以增、删选定商铺中的商品，修改商品价格。
（4）查询某一种商品名称，建立一个双向循环链表，结点信息是包含该商品的所有商铺编号，商铺名，信誉度，商品名称，价格，销量，按销量高至低排序，并可逐一显示。
（5）购买某一商铺的商品，修改单向链表中商品的信息的销量。
（6）任何的商铺信息变化，实现文件存储。

*/
typedef struct SNode{
	Store store;
	SNode* nextstore;
}SNode,*Sptr; 

typedef struct BGNode{//双向链表，存储当前查找的商品 
	Goods goods;
	Sptr s;//存储商铺地址 ，方便购买时直接对店铺信息进行操作 
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
void Read_in_Store(Sptr slist);//将文件内容读入店铺链表 
void write_in_Store(Sptr slist);//将链表信息存入文件 
void ShowAllStore(Sptr slist);//展示所有店铺信息 
void ShowBGList(BGN bglist);//展示当前双链表商品信息 
bool SortBGList(BGN bl);//按销量排序 
void SearchGoods(Sptr slist);//查找某商品 ，并排序，显示，包含购买功能 
void AddStore(Sptr slist);//增加店铺 
void AddGoods(Sptr slist);//增加商品
void DeleteStore(Sptr slist);//删除店铺 
void DeleteGoods(Sptr slist); //删除商品 
void ModifyGoods(Sptr slist);//修改商品 
void Show(Sptr slist); //展示所有 ， 或按条件显示单个店铺 
int main()
{
	Sptr slist;
	slist = new SNode;
	slist->nextstore = NULL;
	Read_in_Store(slist);
	
	do{
		system("cls");
		menu();
		int Exit = 0;//退出判断 
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
				cout<<"指令有误，重新输入"<<endl;
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
	while(!fs.eof()) //读入商品数量时，循环读入商品信息并将其增加到店铺下 
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
	while(temp)//写入店铺信息并将其商品写入文件 
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
	cout<<"1-展示所有	others-按条件查找"<<endl;
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
			if(p->store.getname()==n)//查找成功 
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
	cout<<"所有店铺信息如下"<<endl;
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
	cout<<"请输入商铺信息(名称+信用)"<<endl;
	string n;
	int c,count=1;
	cin>>n>>c;
	Sptr newstore = new SNode;
	
	Sptr p=slist;
	while(p->nextstore)//统计店铺标号 
	{
		count++;
		p=p->nextstore;
	}
	newstore->store.set(count,n,c,0);//将其对应店铺号一起插入链表中 
	p->nextstore = newstore;
	newstore->nextstore = NULL;
	cout<<"店铺添加成功"<<endl;
	
	cout<<"是否继续增加商品。 1-是，other key-否"<<endl;
	char cc = getch();
	if(cc=='1')
	{
		cout<<"请输入将要增加的商品数量"<<endl;
		int goodsnum;
		cin>>goodsnum;
		
		while(goodsnum--)
		{
			pGoods pg = new Goods;
			cout<<"请输入商品名称+价格"<<endl;
			string n;
			float p;
			cin>>n>>p;
			pg->setvalue(n,p,0);
			newstore->store.addGoods(pg);
		}
		cout<<"商品添加成功"<<endl;
	 } 
}
void ShowBGList(BGN bglist)
{
	cout<<"+++++++++++++++++++++++"<<endl; 
	BGN bb = bglist->next;
	while(bb)
	{
		cout<<"铺号：";
		printf("%-4d",bb->s->store.getNumber());
		cout<<"商铺名："<<bb->s->store.getname();
		cout<<"	价格：";
		printf("%-5.2f",bb->goods.price);
		cout<<"	销量："<<bb->goods.sales<<endl;
		
		bb = bb->next;
	}
	cout<<"+++++++++++++++++++++++"<<endl; 	

}
bool SortBGList(BGN bl)//插入排序整理商品信息 
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
				if(q!=p->pre)//不是当前位置则插入 
				{
	
				pp= p;
				p = p->pre;
				if(pp->next)//判断是否到达末尾 
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

				if(pp->next)//判断是否到达末尾 
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
	cout<<"请输入想要查询的商品名称"<<endl;
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
		if(pg)//若查找成功则添加到链表中 
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
	cout<<"是否购买。1-是，0-否"<<endl;
	char c = getch();
	if(c=='1')
	{
		cout<<"请输入该店铺编号"<<endl;
		int num;
		cin>>num;
		
		BGN buy=bglist->next;
		int k=0;
		while(buy)
		{
			if(num==buy->s->store.getNumber())
			{
				buy->s->store.addSales(buy->s->store.findGoods(n));
				cout<<"购买成功"<<endl; 
				buy->s->store.showGoods();
				k=1;
				break;
			}
			buy = buy->next;
		}
		if(k==0) cout<<"未找到该店铺,购买失败"<<endl;
		system("pause");
		
	}
	
	 
}
void DeleteStore(Sptr slist)
{
	Sptr p,q;
	int count=1;
	string n;
	cout<<"请输入删除的店铺名"<<endl;
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
	
	cout<<"删除成功"<<endl;
	
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
		cout<<"删除成功"<<endl;
		else
		cout<<"删除失败"<<endl;
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
		cout<<"modify 成功"<<endl;
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
		cout<<"请输入将要增加的商品数量"<<endl;
		int goodsnum;
		cin>>goodsnum;
		
		while(goodsnum--)
		{
			pGoods pg = new Goods;
			cout<<"请输入商品名称+价格"<<endl;
			string n;
			float p2;
			cin>>n>>p2;
			pg->setvalue(n,p2,0);
			p->store.addGoods(pg);
		}
		cout<<"商品添加成功"<<endl;
		system("pause"); 
	}	
}
