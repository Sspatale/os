#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>


// Forward declarations
void bubble_sort(int arr[], int n);
int main(int argc, char *argv[])
{
    FILE *fp;
    int pid;
    int i, n,arr[20],status;
    char *newargv[] = {NULL, "sort.txt", NULL};
    char *newenviron[] = {NULL};
    
    // Input size of array
    printf("Enter the total number of elements: ");
    scanf("%d", &n);
    
    // Input the elements
    printf("Enter the elements: ");
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    

    // Fork process
    newargv[0] = argv[1];
    pid = fork();
    if (pid == 0) {
        wait(0);
        execve(argv[1], newargv, NULL);
    } else if (pid > 0) {
    printf("\n******* Task done by Parent Process*********");
        bubble_sort(arr,n);
        printf("\n sorted array by parent written in %s:\n",newargv[1]);
        for(i=0;i<n;i++)
    	{
    	printf("\n %d",arr[i]);
   	 }

        // Write array element to the file
        fp = fopen("sort.txt", "w");
        if (fp == NULL) {
            printf("Error: can't open file.\n");
            return 1;
        } else {
            printf("\n parent written sorted element in file sort.txt");
        }

        for (i = 0; i < n; i++) {
           
            fprintf(fp,"%d ", arr[i]);
        }
        fclose(fp);
       wait(&status);
    } else {
        printf("\nError.\n");
    }
    return 0;
}


// Function to sort the array
void bubble_sort(int arr[], int n) {
    int i,j,temp;
    for(i=0;i<n;i++)
    {
    for(j=0;j<n-i-1;j++)
    {
    	if(arr[j]>arr[j+1])
    	{
    	temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
    	}
    }
    }
    
    }


