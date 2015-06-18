#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define m 7
#define n 15
int F[m];

void preindex(char P[])
{
	int i,j;
	i=1;j=0;
	while(i<m)
	{
		if(P[i]==P[j])
		{
			F[i]=j+1;
			i++;j++;
		}
		else if(j>0)
		j=F[j-1];
		else
		{
			F[i]=0;
			i++;
		}
	}
}

int matching(char *T,char *P)
{
	int i,j;
	preindex(P);
	for(i=0;i<m;i++)
	printf("%d\t",F[i]);
	i=0;j=0;
	while(i<n)
	{
		if(T[i]==P[j])
		{
			if(j==m-1)
			return i-j;
			else
			{
				i++;j++;
			}
		}
		else if(j>0)
		{
			j=F[j-1];
		}
		else
		i++;
	}
	return 0;
}

int main()
{
	char P[m]={'a','b','a','b','a','c','a'};
	char T[n]={'b','a','c','b','a','b','a','b','a','b','a','c','a','c','a'};
	int i;

	printf("\n%d\n",matching(T,P));
	return 0;
}
