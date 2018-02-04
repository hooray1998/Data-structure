#include"code.h"
#include"huffman.h" 
#include"count.h"
#include"coding.h"
#include"decode.h"


void Init();//初始化 
void Count();//统计各字符出现的次数 

void Select(HuffmanTree ht, int num, unsigned int &s1, unsigned int &s2);
void HuffmanCoding(Letter *letterlist, int n);//根据出现频率对所有字符进行压缩 

void Show();//展示编码情况（编码表） 

int Coding();//将预压缩文件中的字符翻译成对应编码并按照算法压缩到文件中 

void Decode();//将压缩文件中的压缩码按照编码表解码 到指定文件中。 

void match(char *rline_char);
int current_letter_match(char*rline_char,char*letter_code,int &cur_len);
void match_succeed(Letter l);


int main()
{
	cout<<"请输入预压缩文件名:	"; 
	cin>>in;
	cout<<"请输入压缩后的文件名:	";
	cin>>cmp;
	cout<<"请输入解压缩后的文件名:	"; 
	cin>>fd;
	Init();
	Count();

	HuffmanCoding(letterlist,letterNum);
	Show();
	
	Coding();
	
	Decode();
	return 0;
 } 




void Show()
{
	
	for(int i=0;i<letterNum;i++)
	{
		printf("%c  %d  %s\n",letterlist[i].value,letterlist[i].num,letterlist[i].code);
	}

}

 
