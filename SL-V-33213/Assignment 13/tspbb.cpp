#include <iostream>
#include <cstring> 
using namespace std; 
int N=0;
int final_path[100]; 
bool visited[100]; 
int final_res = 32000; 



void copyToFinal(int curr_path[]) { 
	for (int i=0; i<N; i++) 
		final_path[i] = curr_path[i]; 
	final_path[100] = curr_path[0]; 
} 


int firstMin(int adj[100][100], int i){ 
	int min = 32000; 
	for (int k=0; k<N; k++) 
		if (adj[i][k]<min && i != k) 
			min = adj[i][k]; 
	return min; 
} 


int secondMin(int adj[100][100], int i)  { 
	int first = 32000, second = 32000; 
	for (int j=0; j<N; j++) { 
		if (i == j) 
			continue; 

		if (adj[i][j] <= first) { 
			second = first; 
			first = adj[i][j]; 
		}else if (adj[i][j] <= second && adj[i][j] != first) 
			second = adj[i][j]; 
	} 
	return second; 
} 


void TSPRec(int adj[100][100], int curr_bound, int curr_weight, int level, int curr_path[]) { 

	
	if (level==N) { 
		
		if (adj[curr_path[level-1]][curr_path[0]] != 0) { 
			
			int curr_res = curr_weight + adj[curr_path[level-1]][curr_path[0]]; 


			
			if (curr_res < final_res) { 
				copyToFinal(curr_path); 
				final_res = curr_res; 
			} 
		} 
		return; 
	} 


	
	for (int i=0; i<N; i++) { 
		if (adj[curr_path[level-1]][i] != 0 && visited[i] == false) { 
			int temp = curr_bound; 
			curr_weight += adj[curr_path[level-1]][i]; 

			if (level==1) 
				curr_bound -= ((firstMin(adj, curr_path[level-1]) + firstMin(adj, i))/2); 
			else
				curr_bound -= ((secondMin(adj, curr_path[level-1]) + firstMin(adj, i))/2); 

		
			 
			if (curr_bound + curr_weight < final_res) { 
				curr_path[level] = i; 
				visited[i] = true; 

				TSPRec(adj, curr_bound, curr_weight, level+1, curr_path); 
			} 

		
			curr_weight -= adj[curr_path[level-1]][i]; 
			curr_bound = temp; 

			memset(visited, false, sizeof(visited)); 
			for (int j=0; j<=level-1; j++) 
				visited[curr_path[j]] = true; 
		} 
	} 
} 

 
void TSP(int adj[100][100]) { 
	int curr_path[100]; 

	
	int curr_bound = 0; 
	memset(curr_path, -1, sizeof(curr_path)); 
	memset(visited, 0, sizeof(curr_path)); 

	for (int i=0; i<N; i++) 
		curr_bound += (firstMin(adj, i) + 
					secondMin(adj, i)); 

	curr_bound = (curr_bound&1)? curr_bound/2 + 1 : curr_bound/2; 

	
	visited[0] = true; 
	curr_path[0] = 0; 

	
	TSPRec(adj, curr_bound, 0, 1, curr_path); 
} 


int main() { 
	cout<<"Enter the number of nodes : ";
	cin>>N;
	int adj[100][100] ;

	cout<<"Enter the adjacency matrix : \n"	;
	for(int i=0;i<N;i++){
		for(int j=0;j<N;j++){
			cin>>adj[i][j];	
		}
	}
	TSP(adj); 

	cout<<"Minimum cost : "<<final_res<<"\n"; 
	cout<<"Path Taken : "; 
	for (int i=0; i<=N; i++) 
		cout<<final_path[i]+1<<" ";
		 
	cout<<endl;
	return 0; 
}
