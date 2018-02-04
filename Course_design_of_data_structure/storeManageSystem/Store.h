#include<stdio.h>
#include<iostream>
#include<fstream>
#include<windows.h>
#include<list>
#include<conio.h>
using namespace std;
typedef struct Goods{
	string 	name;
	float 	price;
	int		sales;
	Goods* nextG; //下一个邻接的商品 
	void setvalue(string n, float p, int s)
	{
		name = n;
		price = p;
		sales = s;
	}
	bool operator > (Goods g)//为了插入排序 
	{
		if(sales>g.sales) return true;
		else return false;
	}
}Goods,*pGoods;

class Store{
	public:
		Store();
		Store(int ,string,int,int);
		void set(int ,string,int,int);
		void addGoods(pGoods);
		pGoods getfirstGoods();
		int getNumber();
		int getCredit();
		string getname();
		int getgoodsnum();
		void setnumber(int i);
		pGoods findGoods(string);
		int deGoods(string ); 
		void modifygoodsprice(pGoods,float);//修改商品价格 
		void addSales(pGoods);//增加销量 
		void showGoods();
	private:
		int number;
		string name;
		int credit;
		int goodsnum;
		pGoods first_goods;
};
