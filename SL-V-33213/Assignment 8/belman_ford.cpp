#include<bits/stdc++.h>
using namespace std;

int number_of_nodes,number_of_edges;
void init_graph(int **graph,int number_of_nodes){
	int e1,e2;
	
	for(int i=0;i<number_of_nodes;i++){
		graph[i]=new int[number_of_nodes];
	}
	for (int i = 0; i < number_of_nodes; i++)
		for (int j = 0; j < number_of_nodes; j++)		
			graph[i][j]=0;

	cout<<"\nENTER NUMBER OF EDGES : ";
	cin>>number_of_edges;
	cout<<"\nGIVE EDGE WEIGHTS : \n";
	for (int i = 0; i < number_of_edges; i++)
	{
		cout<<"\n\tEnter starting node\t: ";
		cin>>e1;
		e1--;
		cout<<"\tEnter ending node\t: ";
		cin>>e2;
		e2--;
		cout<<"\tEnter weight of edge\t: ";
		cin>>graph[e1][e2];
	}

}

void init_dist(int *dist,int number_of_nodes,int start_node){

	for (int i = 0; i < number_of_nodes; i++)
	{
		dist[i]=32767;
		if(i==start_node)
			dist[i]=0;
	}
}

void init_previous(int *previous,int number_of_nodes,int start_node){

	for (int i = 0; i < number_of_nodes; i++)
	{
		previous[i]=-1;
		if(i==start_node)
			previous[i]=i;
	}
}
int main(){
	int e1,e2,start_node,*dist,*previous,**graph;
	cout<<"ENTER NUMBER OF NODES : ";
	cin>>number_of_nodes;
	cout<<"\nENTER THE STARTING NODE : ";
	cin>>start_node;
	start_node--;
	graph = new int*[number_of_nodes];
	dist=new int[number_of_nodes];
	previous=new int[number_of_nodes];
	init_graph(graph,number_of_nodes);
	init_dist(dist,number_of_nodes,start_node);
	init_previous(previous,number_of_nodes,start_node);
	for (int k = 0; k < number_of_edges; k++)
	for (int i = 0; i < number_of_nodes; i++){
		for (int j = 0; j < number_of_nodes; j++ ){
			if (graph[i][j]!=0)
			{
				if(graph[i][j]+dist[i] < dist[j]){
					previous[j]=i;
					dist[j]=graph[i][j]+dist[i];
					cout<<"Distance : ";
	for (int i = 0; i < number_of_nodes; i++)
		cout<<dist[i]<<" ";
	cout<<"\nPrevious : ";
	for (int i = 0; i < number_of_nodes; i++)
		cout<<previous[i]<<" ";
	cout<<endl<<endl;
				}
			}
		}		
	}
	
	for (int i = 0; i < number_of_nodes; i++){
		for (int j = 0; j < number_of_nodes; j++ ){
			if (graph[i][j]!=0)
			{
				if(graph[i][j]+dist[i] < dist[j]){
					cout<<"Negative Edge exists, cannot find SSSP !\n";
					return 0;
				}
			}
		}		
	}
	
	for (int i = 0; i < number_of_nodes; i++){
		int temp = i;
		if(temp==start_node)
			continue;
		cout<<"PATH FOR NODE "<<i<<" : ";
		while(temp!=start_node){
		cout<<"<-"<<temp;
		temp=previous[temp];
		}
		cout<<"<-"<<start_node<<endl;
	}
	cout<<"Distance : ";
	for (int i = 0; i < number_of_nodes; i++)
		cout<<dist[i]<<" ";
	cout<<"\nPrevious : ";
	for (int i = 0; i < number_of_nodes; i++)
		cout<<previous[i]<<" ";
	cout<<endl;
	
}
