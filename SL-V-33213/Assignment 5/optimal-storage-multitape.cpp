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

int calculateTime(int *size,  int n){
	int array[n];
	array[0] = 0;
	int sum=0;
	for(int i=1;i<n;i++)
	{
		array[i] = array[i-1] + size[i-1];
	}
	for(int i=0;i<n;i++)
	{
		sum+=array[i];
	}
	return sum;
}



int generateTapesVertical(int *size,int *capacity,int number_of_tapes,int n){
	int tapes[number_of_tapes][20],tape_counter[number_of_tapes],loop_counter=0,sum=0;
	for(int i=0;i<number_of_tapes;i++){
		tape_counter[i]=0;
	}
	
	for(int i=0,j=0;i<n;i++){
		if((capacity[j%number_of_tapes] - size[i]) >= 0){
				tapes[j%number_of_tapes][tape_counter[j%number_of_tapes]++] = size[i];	
				capacity[j%number_of_tapes] -= size[i];		
			}
		else{
			i--;
			loop_counter++;
		}
		j++;
		if(loop_counter==n)
			break;
	}
	
	
	cout<<"\n\tPrograms are arranged vertically !\n";
	for(int i=0;i<number_of_tapes;i++){
		cout<<"\t";
		for(int j=0;j<tape_counter[i];j++)
			cout<<tapes[i][j]<<" ";
		cout<<endl;
	}
	
	for(int i=0;i<number_of_tapes;i++){
		sum += calculateTime(tapes[i],tape_counter[i]);
	}
	
	return sum;
	
}


int generateTapesHorizontal(int *size,int *capacity,int number_of_tapes,int n){
	int tapes[number_of_tapes][20],tape_counter[number_of_tapes],sum=0;
	for(int i=0;i<number_of_tapes;i++){
		tape_counter[i]=0;
	}
	
	for(int i=0,j=0;i<n;i++){
		if((capacity[j] - size[i]) >= 0){
				tapes[j][tape_counter[j]++] = size[i];	
				capacity[j] -= size[i];		
			}
		else{
			i--;
			j++;
		}
		
		if(j==number_of_tapes)
			break;
	}
	
	
	cout<<"\n\tPrograms are arranged Horizontal !\n";
	for(int i=0;i<number_of_tapes;i++){
		cout<<"\t";
		for(int j=0;j<tape_counter[i];j++)
			cout<<tapes[i][j]<<" ";
		cout<<endl;
	}
	
	for(int i=0;i<number_of_tapes;i++){
		sum += calculateTime(tapes[i],tape_counter[i]);
	}
	
	return sum;
	
}

void sortArray(int *array,int low, int high){
	if(high <= low)
		return;

	int mid = (low + high)/2;
	sortArray(array, low, mid);
	sortArray(array, mid + 1, high);
	merge(array, low, mid, high);	
}



int main(){
	int n,*size,*capacity,totalTime,number_of_tapes,*capacity_temp;
	cout<<"How many programs are there : ";
	cin>>n;
	
	size = new int[n];
	for(int i=0;i<n;i++){
	cout<<"Enter the retrival time of each program :- ";
	cin>>size[i];
	}
	cout<<"How many tapes are there : ";
	cin>>number_of_tapes;
	capacity = new int[number_of_tapes];
	capacity_temp = new int[number_of_tapes];
	for(int i=0;i<number_of_tapes;i++){
	cout<<"Please Enter the capacity of tape "<<i+1<<" : ";
	cin>>capacity[i];
	capacity_temp[i] = capacity[i];
	}

	sortArray(size,0,n-1);
	
	totalTime = generateTapesVertical(size,capacity,number_of_tapes,n);
	cout<<"\n\tAverage seek time for Vertical is : "<<(float)totalTime/n<<endl;
	totalTime = generateTapesHorizontal(size,capacity_temp,number_of_tapes,n);
	cout<<"\n\tAverage seek time for Horizontal is : "<<(float)totalTime/n<<endl;
	return 0;
}
