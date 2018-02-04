void Select(HuffmanTree ht, int num, unsigned int &s1, unsigned int &s2)
{
	
	//初始化s1,s2; 
	s1 = 0;
	s2 = 0; 
	for(int i=1;i<=num;i++)
	{
		if(ht[i].parent == 0)
		{
			if(s1==0)
			s1 = i;
			else 
			{
				s2 = i;
				break;
			}		
		} 
	}
	
	for(int i=1;i<=num;i++)
	{
		unsigned int max = (ht[s1].weight>ht[s2].weight)?ht[s1].weight:ht[s2].weight;
		if(ht[i].parent == 0)
		if(ht[i].weight<max&&i!=s1&&i!=s2) 
		{ 
			if(ht[s1].weight==max) s1 = i;
			else 		s2 = i;
		}
	}

}


void HuffmanCoding(Letter letterlist[256], int n)
{
	HuffmanTree HT;
	if(n<=1) return ;	
	int m = 2*n-1;
	HT = (HuffmanTree)malloc( (m+1)*sizeof(HTNode));
	
	HuffmanTree p;
	int i;
	for(p = HT+1,i=1;i<=n;i++,p++)
	{
		p->weight = letterlist[i-1].num;//这个-1找了好久，妈耶 
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for(;i<=m;i++,p++)
	{
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}

	
	
	unsigned int s1,s2;
	
	for(i=n+1;i<=m;i++)
	{
		

		Select(HT,i-1,s1,s2);
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;

	}

	
	char *cd = (char *)malloc(n*sizeof(char));
	cd[n-1] = '\0';
	
	int start;
	for(i=1;i<=n;i++)
	{
		start = n-1;
		
		int c,f;
		for(c=i,f=HT[i].parent;f!=0;c=f,f=HT[f].parent)
			if(HT[f].lchild == c) 	cd[--start] = '0';//if "0"
			else 					cd[--start] = '1';
		letterlist[i-1].code = (char*)malloc((n-start)*sizeof(char));
		strcpy(letterlist[i-1].code,&cd[start]);

	 } 
	free(cd);
	 
 } 
