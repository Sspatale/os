#include <stdio.h>


int main(int argc, char *argv[])
{
    int i,j,temp,n,c=0,count=0,array[20];
    char ch;
    FILE *file;
    printf("\n******* Task done by newly loaded Process *********");
    printf("\n file with sorted array get by new process is: %s\n", argv[1]);
    file=fopen(argv[1],"r");
    if (file==NULL) {
        printf("Error: Unable to open file %s\n", argv[1]);
        return 1;
    } 
   //while(fscanf(file,"%d ",&(array[c]))!=EOF){
       do {
       fscanf(file,"%d",&array[c]);
       c++;
       count++; 
    } while((ch=getc(file))!=EOF);
    n=count-1;
    
   // printf("size of an array is= %d",count-1);
     
 
printf("\n Array sort by new process in reverse order");
    for(i=0;i<n;i++)
    {
    for(j=0;j<n-i-1;j++)
    {
    	if(array[j]<array[j+1])
    	{
    	temp = array[j];
        array[j] = array[j+1];
        array[j+1] = temp;
    	}
    }
    }
    for(i=0;i<n;i++)
    {
    printf("\n %d",array[i]);
    }
       fclose(file);
    return 0;
}

