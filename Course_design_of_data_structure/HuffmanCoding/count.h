void Init()//³õÊ¼»¯±àÂë±í 
{
	letterNum = 0;
	for(int i=0;i<256;i++)
	{
		asc[i]=0;
	}
	
	
}
void Count()
{
	FILE *fp=fopen(in,"r");
	char ch;

	while(!feof(fp))
	{
		ch = fgetc(fp);
		asc[ch]++;
	}
	
	
	fclose(fp);
	for(int i=0;i<256;i++)
	{
		if(asc[i])
		{
			letterlist[letterNum].value = i;
			letterlist[letterNum].num = asc[i];
			locate[i] = letterNum++;
		}
	}
}
