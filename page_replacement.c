#include <stdio.h>

int fn,pn,pages[30],frames[10];

void fifo()
{
	int i,j,k=0,count=0;
	for(i=0;i<fn;i++)
        {
                frames[i]=-1;
        }
	printf("\nFIRST_IN_FIRST_OUT_PAGE_REPLACEMENT :\n");
	printf("\nREF_STRING | PAGE_FRAMES\n\n");
	for(i=0;i<pn;i++)
	{
		printf("%d\t\t",pages[i]);
		int avail=0;
		for(j=0;j<fn;j++)
		{
			if(frames[j] == pages[i])
			{
				avail=1;
			}
		}
		if(avail == 0)
		{
			count++;
			frames[k]=pages[i];
			k=(k+1)%fn;
		}
		for(j=0;j<fn;j++)
		{
			printf("%d\t",frames[j]);
		}
		printf("\n");
	}
	printf("\nPAGE_FAULTS : %d\n",count);
}

int findlru(int time[],int n)
{
	int i,min=time[0],pos=0;
	for(i=1;i<n;++i)
	{
		if(min > time[i])
		{
			min=time[i];
			pos=i;
		}
	}
	return pos;
}

void lru()
{
	int i,j,flag1,flag2,counter=0,faults=0,pos,time[10];
	for(i=0;i<fn;++i)
        {
                frames[i]=-1;
        }
	printf("LEAST_RECENTLY_USED_PAGE_REPLACEMENT :\n");
	printf("\nREF_STRING | PAGE_FRAMES\n\n");
	for(i=0;i<pn;++i)
	{
		printf("%d\t\t",pages[i]);
		flag1=flag2=0;
		for(j=0;j<fn;++j)
		{
			if(frames[j] == pages[i])
			{
				counter++;
				time[j]=counter;
				flag1=flag2=1;
				break;
			}
		}
		if(flag1 == 0)
		{
			for(j=0;j<fn;++j)
			{
				if(frames[j] == -1)
				{
					counter++;
					faults++;
					frames[j]=pages[i];
					time[j]=counter;
					flag2=1;
					break;
				}
			}
		}
		if(flag2 == 0)
		{
			pos = findlru(time,fn);
			counter++;
			faults++;
			frames[pos]=pages[i];
			time[pos]=counter;
		}
		for(j=0;j<fn;++j)
		{
			printf("%d\t",frames[j]);
		}
		printf("\n");
	}
	printf("\nPAGE_FAULTS : %d\n",faults);
}

void lfu()
{
	int i,j,move=0,count=0,flag,count1[20];
	for(i=0;i<fn;i++)
	{
		frames[i]=-1;
	}
	printf("LEAST_FREQUENTLY_USED_PAGE_REPLACEMENT\n");
	printf("\nREF_STRING | PAGE_FRAMES\n\n");
	for(i=0;i<pn;i++)
	{
		printf("%d\t\t",pages[i]);
		flag=0;
		for(j=0;j<fn;j++)
		{
			if(frames[j] == pages[i])
			{
				count1[j]++;
				flag=1;
				break;
			}
		}
		if(flag == 0 && count < fn)
		{
			frames[move]=pages[i];
			count1[move]=1;
			move=(move+1)%fn;
			count++;
		}
		else if(flag == 0)
		{
			int repindex=0,mincount=count1[0];
			for(j=1;j<fn;j++)
			{
				if(count1[j] < mincount)
				{
					mincount=count1[j];
					repindex=j;
				}
			}
			frames[repindex]=pages[i];
			count1[repindex]=1;
			count++;
		}
		for(j=0;j<fn;j++)
		{
			printf("%d\t",frames[j]);
		}
		printf("\n");
	}
	printf("\nPAGE FAULTS : %d\n\n",count);
}

void main()
{
	int i;
        printf("Enter number of frames : ");
        scanf("%d",&fn);
        printf("Enter number of pages : ");
        scanf("%d",&pn);
        printf("Enter reference string : ");
        for(i=0;i<pn;i++)
        {
                scanf("%d",&pages[i]);
        }
        fifo();
        lru();
	lfu();
}
