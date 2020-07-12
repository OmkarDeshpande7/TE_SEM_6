#include<iostream>
#include<stdio.h>

using namespace std;
struct minmax{
	int min;
	int max;
};

int count =0;
struct minmax divide(int *,int, int);
int checkSorted(int *,int, int);
int main(){
	int n,*arr,sorting;
	char status[][20] = {"Descending","Ascending","Unsorted"};
	struct minmax Minmax;
	
	cout<<"Enter the number of elements : ";
	cin>>n;
	arr =  new int(sizeof(int)*n);
	
	for(int i=0;i<n;i++){
		cout<<"Enter the element "<<i+1<<" : ";
		cin>>arr[i];
	} 
	cout<<endl;
		
	cout<<"The elements are :";
	for(int i=0;i<n;i++){
		cout<<" "<<arr[i];

	}
	cout<<endl;
	sorting = checkSorted(arr,0,n-1);
	cout<< endl << "sorting status : "<<status[sorting]<<endl;
	if(sorting == 1)
		{
			Minmax.max = arr[n-1];
			Minmax.min = arr[0];
		}
	else if (sorting == 0)
		{
			Minmax.max = arr[0];
			Minmax.min = arr[n-1];
		}
	else
		Minmax = divide(arr,0,n-1);
	cout<<endl<<"Maximum is : "<<Minmax.max<<endl;
	cout<<"Minimum is : "<<Minmax.min<<endl;
	
	cout<<endl<<"Number of comparisons is : "<<count<<endl;
	
}

int checkSorted(int *arr,int low, int high){
	if(high == low)
		return - 1;
	if(arr[low] < arr[low+1])
		{
		for(int i=0;i<high;i++)
			{
			count++;
			if(arr[i]>arr[i+1])
				return 2;
			}
		return 1;
						
		}
		
	if(arr[low] > arr[low+1])
		{
		for(int i=0;i<high;i++)
			{
			count++;
			if(arr[i]<arr[i+1])
				return 2;
			}
		return 0;
						
		}
}

minmax divide(int * arr,int low, int high){	
	struct minmax temp;
	if(low==high)
		{
		temp.min = temp.max = arr[low];
		return temp;
		}

	else{
		struct minmax left,right;
		
		int mid = (low + high)/2;
		left = divide(arr,low,mid);
		right = divide(arr,mid+1,high);
		if (left.max > right.max)
			{
			temp.max = left.max;
			count++;
			}
		else
			temp.max = right.max;
		
		
		if (left.min < right.min)
			{
			temp.min = left.min;
			count++;
			}
		else
			temp.min = right.min;
			
			return temp;
		
	}
}
