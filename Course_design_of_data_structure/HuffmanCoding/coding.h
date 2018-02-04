void code_line(char *linecode)
{
	unsigned char word = 0;
	int pre_word=0;
	char k;
	int i; 
	char t[9];
	for(i=0;i<strlen(linecode);)
	{
		if(linecode[i]=='1') k=1;
		else k=0;

		word*=2; 
		word+=k;
	

		i++; 
		if(i%8==0)//每8个形成一个压缩码 
		{
			compressCode.push(word);
			word=0;
		}
		
	}
	char kk[8];
	strcpy(linecode,&linecode[strlen(linecode)-i%8]);

}
int Coding()
{
	FILE *fp=fopen(in,"r");

	char linecode[10000]; 
	linecode[0]='\0'; 
	int count1 = 0;//每读100个进队一次。 
	unsigned char ch;
	while(!feof(fp))
	{
		ch=fgetc(fp);
		if(!feof(fp))
		{
			strcat(linecode,letterlist[locate[ch]].code);
			count1++;
			if(count1%64==0) //每64个压缩一次 
			{
				code_line(linecode);
			}
		}

	}
	cout<<endl;

	if(count1%64!=0)
	code_line(linecode);

	unsigned char remain_len = strlen(linecode);
	unsigned char k,word=0;
		
	for(int i=0;i<remain_len;i++)//处理剩余部分 
	{
		word<<1;
		word+=(linecode[i]=='0')?0:1;
	}
	
	ofstream cmps_file(cmp);
	cmps_file<<remain_len;
	cmps_file<<word;

	unsigned char c;
	
	while(!compressCode.empty())//将队中元素存入文件 
	{
		c = compressCode.front();
		cmps_file<<c;
		compressCode.pop();
	}


	cmps_file.close();
	return 1;
}

