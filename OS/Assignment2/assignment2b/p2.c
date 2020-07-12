#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int* convert(char* );

int binarySearch(int arr[], int l, int r, int x) ;

int main(int argc, char *argv[])
       {
        //printf("%d is arg no\n",argc);
        int len=strlen(argv[0]),no,result;
        int *arr=convert(argv[0]);       	
       	printf("\nEnter the element to search : ");
       	scanf("%d",&no);
       	result = binarySearch(arr,1,len,no);
       	if (result != -1)
       	printf("Number found at location %d !\n",result);
       	else 
       	printf("Number not found  !\n");
       }  

int* convert(char* c)
{
	int len=strlen(c),i;
	int *a=(int*)malloc(len*sizeof(int));
	for(i=0;i<len;i++)
		a[i]=c[i]-48;
	return a;
}


int binarySearch(int arr[], int l, int r, int x) 
{ 
    if (r >= l) { 
        int mid = l + (r - l) / 2; 
  
       
        if (arr[mid] == x) 
            return mid; 
  
     
        if (arr[mid] > x) 
            return binarySearch(arr, l, mid - 1, x); 
  
      
        return binarySearch(arr, mid + 1, r, x); 
    } 
  
   
    return -1; 
} 
  
