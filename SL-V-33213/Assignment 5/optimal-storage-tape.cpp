#include<iostream>
using namespace std;
void merge(int* arr, int low, int mid, int high) 
{ 
    int i, j, k; 
    int n1 = mid - low + 1; 
    int n2 =  high - mid; 
  
    int L[n1], R[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = arr[low + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = arr[mid + 1+ j]; 
  
    i = 0; 
    j = 0; 
    k = low; 
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            arr[k] = L[i]; 
            i++; 
        } 
        else
        { 
            arr[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  

    while (i < n1) 
    { 
        arr[k] = L[i]; 
        i++; 
        k++; 
    } 
  

    while (j < n2) 
    { 
        arr[k] = R[j]; 
        j++; 
        k++; 
    } 
} 


void sortArray(int *array,int low, int high){
	if(high <= low)
		return;

	int mid = (low + high)/2;
	sortArray(array, low, mid);
	sortArray(array, mid + 1, high);
	merge(array, low, mid, high);	
}

int calculateTime(int *size, int * array, int n){
	array[0] = size[0];
	int sum=0;
	for(int i=1;i<n;i++)
	{
		array[i] = array[i-1] + size[i];
	}
	for(int i=0;i<n;i++)
	{
		sum+=array[i];
	}
	return sum;
}

int main(){
	int n,*size,*time,totalTime;
	cout<<"How many programs are there : ";
	cin>>n;
	size = new int(sizeof(int) * n);
	time = new int(sizeof(int) * n);
	cout<<"Enter the retrival time of each program :- ";
	for(int i=0;i<n;i++)
	{
		cin>>size[i];
	}
	
	for(int i=0;i<n;i++)
	{
		cout<<" "<<size[i];
	}

	sortArray(size,0,n-1);
	totalTime = calculateTime(size,time,n);
	cout<<"Average seek time is : "<<(float)totalTime/n;
	return 0;
}
