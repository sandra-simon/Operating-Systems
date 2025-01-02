#include <stdio.h>

struct block
{
	int pid,size,allocated;
}b[10];

struct process
{
	int pid,size,allblocksz;
}p[10];
struct block temp,ltemp;
int  bn,pn,i,j;

void display()
{
	printf("\nPROCESS ID\tPROCESS SIZE\tBLOCK SIZE\n");
	printf("---------------------------------------------\n");
	for(i=0;i<pn;i++)
	{
		if(p[i].allblocksz == -1)
		{
			printf("%d\t\t%d\t\tNot allocated\n",p[i].pid,p[i].size);
		}
		else
		{
			printf("%d\t\t%d\t\t%d\n",p[i].pid,p[i].size,p[i].allblocksz);
		}
	}
}

void firstfit()
{
	for(i=0;i<bn;i++)
        {
                b[i].allocated=-1;
        }
        for(i=0;i<pn;i++)
        {
                p[i].allblocksz=-1;
        }
	for(i=0;i<pn;i++)
	{
		for(j=0;j<bn;j++)
		{
			if(b[j].allocated == -1 && b[j].size >= p[i].size)
			{
				p[i].allblocksz=b[j].size;
				b[j].allocated=1;
				break;
			}
		}
	}
	printf("\nFIRST FIT ALLOCATION\n");
	display();
}

void bestfit()
{
	for(i=0;i<bn;i++)
        {
                b[i].allocated=-1;
        }
	for(i=0;i<pn;i++)
        {
                p[i].allblocksz=-1;
        }
	for(i=0;i<bn-1;i++)
	{
        	for(j=0;j<bn-i-1;j++)
		{
            		if(b[j].size > b[j+1].size)
			{
                		temp=b[j];
                		b[j]=b[j+1];
                		b[j+1] =temp;
            		}
        	}
    	}
	for(i=0;i<pn;i++)
        {
                for(j=0;j<bn;j++)
                {
                        if(b[j].allocated == -1 && b[j].size >= p[i].size)
                        {
                                p[i].allblocksz=b[j].size;
                                b[j].allocated=1;
                                break;
                        }
                }
        }
	printf("\nBEST FIT ALLOCATION\n");
	display();
}

void worstfit()
{
	for(i=0;i<bn;i++)
        {
                b[i].allocated=-1;
        }
	for(i=0;i<pn;i++)
        {
                p[i].allblocksz=-1;
        }
	for(i=0;i<bn-1;i++)
	{
		for(j=0;j<bn-i-1;j++)
		{
			if(b[j].size < b[j+1].size)
			{
				ltemp=b[j];
				b[j]=b[j+1];
				b[j+1]=ltemp;
			}
		}
	}
        for(i=0;i<pn;i++)
        {
                for(j=0;j<bn;j++)
                {
                        if(b[j].allocated == -1 && b[j].size >= p[i].size)
                        {
                                p[i].allblocksz=b[j].size;
                                b[j].allocated=1;
                                break;
                        }
                }
        }
	printf("\nWORST FIT ALLOCATION\n");
	display();
}
void main()
{
	printf("Enter number of blocks : ");
	scanf("%d",&bn);
	for(i=0;i<bn;i++)
	{
		printf("Enter size of block %d : ",i+1);
		scanf("%d",&b[i].size);
		b[i].pid=i+1;
	}
	printf("Enter number of processes : ");
        scanf("%d",&pn);
        for(i=0;i<pn;i++)
        {
                printf("Enter size of process %d : ",i+1);
                scanf("%d",&p[i].size);
                p[i].pid=i+1;
        }
	firstfit();
	bestfit();
	worstfit();
}
