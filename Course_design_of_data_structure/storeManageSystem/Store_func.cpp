#include"Store.h"
void Store::set(int n, string na, int c,int num) 
{
	name = na;
	number = n;
	credit = c;
	goodsnum = num;
}
Store::Store()
{
	number = 0;
	credit = 0;
	goodsnum = 0;
	first_goods = NULL;
}
string Store::getname()
{
	return name;
}
int Store::getCredit()
{
	return credit;
}
int Store::getNumber()
{
	return number;
}
int Store::getgoodsnum()
{
	return goodsnum;
}
void Store::setnumber(int i)
{
	number = i;
}
void Store::addGoods(pGoods p)
{
	p->nextG = first_goods;
	first_goods = p;
	goodsnum++;
}
void Store::addSales(pGoods p)
{
	p->sales++;
}
int Store::deGoods(string n)
{
	pGoods p = first_goods;
	if(p->name == n)
	{
		first_goods = p->nextG; 
		delete p;
		goodsnum--;
		return 1;
	}
	pGoods q;
	q = p;
	p = p->nextG;
	while(p)
	{
		if(p->name == n)
		{
			q->nextG = p->nextG;
			delete p;
			goodsnum--;
			return 1;
		}
		q = p;
		p = p->nextG;			
	}
	return 0;
	
}
void Store::showGoods()
{
	pGoods p = getfirstGoods();
	printf("\nµÍ∆Ã∫≈£∫%-4d",number);
	cout<<"Store"<<name;
	printf("	credit:%-4d\n",credit);
	cout<<goodsnum<<" Goods is follow."<<endl;
	cout<<"Goodsname	price	sales\n";
	
	while(p)
	{
		cout<<p->name<<"		"<<p->price<<"	"<<p->sales<<endl;
		p=p->nextG;
	}
}
pGoods Store::findGoods(string n)//≤È’“…Ã∆∑ 
{
	pGoods p = first_goods;
	while(p)
	{
		if(p->name == n)
		{
			break;
		}
		p = p->nextG;
	}
	return p;
}
pGoods Store::getfirstGoods()
{
	return first_goods;
}
