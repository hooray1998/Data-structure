ofstream fDecode(fd);
void match_succeed(Letter l)//ƥ��ɹ� 
{
	cout<<l.value;
	fDecode<<l.value;
}
int current_letter_match(char*rline_char,char*letter_code,int &cur_len)
{
	int code_len =strlen(letter_code);
	
	for(int j=0;j<code_len;j++)
	{
		if(rline_char[cur_len+j]!=letter_code[j])
		return false;	
	}
	cur_len+=code_len;
	
	return true;
}
void match(char *rline_char)
{
	int len = strlen(rline_char);
	bool sw = 0;
	int cur_len = 0;
	while(cur_len!=len)
	{
		for(int i=0;i<letterNum;i++)//�����������ƥ�� 
		{
			if(current_letter_match(rline_char,letterlist[i].code,cur_len))
			{
				match_succeed(letterlist[i]);
				break;
			}
			if(i==letterNum-1) sw=1;
		}
		if(sw)
		{

			break;	
		}
	}	
}


void Decode()
{
	ifstream cmps(cmp);
	if(cmps.fail())
	{
		cout<<"error in open cmps"<<endl;
		exit(0);
	}
	unsigned char remain_len=0,word,word_end=0,ch;
	cmps>>remain_len;
	cmps>>word_end;


	int count2 = 0,char_len=0;
	char rline_char[10000];
	char ccc[9];
	while(!cmps.eof())
	{
		cmps>>ch;
		if(!cmps.eof())
		{
			for(int i=0;i<8;i++,ch/=2)//����ÿһ��ѹ��������Ҫͨ��8��ȡ�࣬��ÿ��ȡ��Ľ���洢
			{
			ccc[7-i]=(ch%2==0)?'0':'1';
			rline_char[char_len+7-i] = ccc[7-i];
			}
			ccc[8]='\0';
			char_len+=8;
			rline_char[char_len] = '\0';
			if(char_len==80)//ÿ80��ѹ�������һ�� 
			{
				match(rline_char);
				char_len = strlen(rline_char);
			}
		}
	}
	
		for(int i=0;i<remain_len;i++,word_end/=2)//��ĩβʣ�ಿ�ֽ��� 
		{
			ccc[remain_len-1-i] = (word_end%2==0)?'0':'1';
			rline_char[char_len+remain_len-i-1]=(word_end%2==0)?'0':'1';
			
		}
		ccc[remain_len] = '\0';
		char_len+=remain_len;
		rline_char[char_len] = '\0';
		match(rline_char);//ƥ��ʣ�����в��� 
		fDecode.close();
	
}

