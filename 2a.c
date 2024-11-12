
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
void bubbleSort(int arr[], int n)
{
int i, j, temp;
for (i = 0; i < n-1; i++)
{
for (j = 0; j < n-i-1; j++)
{
if (arr[j] > arr[j+1])
{
temp = arr[j];
arr[j] = arr[j+1];
arr[j+1] = temp;
}
}
}
}
void selectionSort(int arr[], int n)
{
int i, j, min_idx, temp;
for (i = 0; i < n-1; i++)
{
min_idx = i;
for (j = i+1; j < n; j++)
{
if (arr[j] < arr[min_idx])
min_idx = j;
}
temp = arr[min_idx];
arr[min_idx] = arr[i];
arr[i] = temp;
}
}
void printArray(int arr[], int n)
{
int i;

for (i = 0; i < n; i++)
printf("%d ", arr[i]);
printf("\n");
}
int main()
{
pid_t pid;
int n, i;
// Take input from the user
printf("Enter the number of elements: ");
scanf("%d", &n);
int arr[n];
printf("Enter %d elements: ", n);
for (i = 0; i < n; i++)
{
scanf("%d", &arr[i]);
}
printf("Demonstration of fork system call\n");
pid = fork();
if (pid == 0)
{
// Child process
printf("\nThis is child process\n");
printf("Array before sorting: ");
printArray(arr, n);
bubbleSort(arr, n);
printf("Array after Bubble Sort in child process: ");
printArray(arr, n);
system("ps -l");
}
else if (pid > 0)
{
// Parent process
sleep(5);
printf("\nThis is parent process\n");
printf("Array before sorting: ");
printArray(arr, n);
selectionSort(arr, n);
printf("Array after Selection Sort in parent process: ");
printArray(arr, n);


sleep(5);
system("ps -l");
}
else
{
// Fork failed
printf("\nFork failed, no child process created at all\n");
system("ps -l");
}
return 0;
}


