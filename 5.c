#include <stdio.h>
int n, m, i, j, k,pid,ch;
	int alloc[10][10],max[10][10],need[10][10],avail[10]; 
	int f[10],work[10],safe_seq[10],ind=0,flag,req[10];
	
void input()
{
printf("\n Enter the number of processes");
	scanf("%d",&n);
	printf("\n Enter the number of resources");
	scanf("%d",&m);
// get the max from user	
	printf("\n Enter the max of the problem");
	for(i=0;i<n;i++)
	{
	for(j=0;j<m;j++)
	{
		scanf("%d",&max[i][j]);	
	}
	}
// get the alloc from user	
	printf("\n Enter the allocation of the problem");
	for(i=0;i<n;i++)
	{
	for(j=0;j<m;j++)
	{
		scanf("%d",&alloc[i][j]);	
	}
	}
//get available from user
printf("Enter the available of problem");
for(j=0;j<m;j++)
{
scanf("%d",&avail[j]);
}
// calculate need need=max-alloc	
for (i=0;i<n;i++) {
		for (j=0;j<m;j++)
			{
			need[i][j]=max[i][j]-alloc[i][j];
			}	
		   }
// print the need
printf("\n need calulated is");
 
for (i=0;i<n;i++) {
	printf("\n P%d ",i);
		for (j=0;j<m;j++)
			{
			printf("%d\t",need[i][j]);
			}
		}
}

void safety_algo()
{
// step 1 initialise finish[i]=false i.e.(0) for all processes and letr work=avail
for (k=0;k<n;k++) { 
		f[k]=0;
	}
for (i=0;i<m;i++) { 
	work[i]=avail[i];	
	}
int y=0;
	for (k=0;k<n;k++) {
		for (i=0;i<n;i++) {
			if (f[i]==0) {         // finish condition 
				int flag=0;
				for (j=0;j<m;j++) {
					if (need[i][j] > work[j]){   // unsatisfy second condition
						flag=1;
						break;
					}
				}

				if (flag==0) {
					safe_seq[ind]=i;
					ind++;
					for (y=0;y<m;y++)
						work[y]+=alloc[i][y];
					f[i]=1;
				}
			}
		}
	}

for(int i=0;i<n;i++)
	{
	if(f[i]==0)
	{
		flag=0;
		printf("The following system is not safe");
		break;
	}
else{
printf("\n SYSTEM IS IN SAFE STATE\n");
	printf("\n Following is the SAFE Sequence\n");
	for (i=0;i<n;i++)
		printf(" P%d ->",safe_seq[i]);
}

}

}

void resource_req()
{
printf("enter the process number for additional request");
scanf("%d",&pid);
printf("enter additional request for each resource");
for(j=0;j<m;j++)
{
scanf("%d",&req[j]);
}
for(j=0;j<m;j++)
{
	if(req[j]>need[pid][j])
{
printf("request could not be granted and if so system may lead to deadlock");
break;
}
else
	{
		
	
		alloc[pid][j]=alloc[pid][j]+req[j];
		need[pid][j]=need[pid][j]-req[j];
		avail[j]=avail[j]-req[j];
	
	
	safety_algo();

	}
}
}
void main()
{
input();
safety_algo();
printf("\nIs there any process makes additional request yes(1)/no(0)");
scanf("%d",&ch);
if(ch==1)
{
resource_req();
}
else
{
printf("\n");
}

}

