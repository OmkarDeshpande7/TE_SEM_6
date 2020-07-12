#include <stdio.h> 
#include<iostream>
using namespace std;
void printBoard(int **board, int N) 
{ 

	static int count = 0;
	cout<<"Solution number : "<< count + 1 <<endl;
	for (int i = 0; i < N; i++) { 
		for (int j = 0; j < N; j++) 
			cout<<" "<< board[i][j]; 
		cout<<endl; 
	} 
	cout<<endl;
	count++;
} 


bool isSafe(int **board, int row, int col, int N) 
{ 
	int i, j;

	for (i = 0; i < col; i++) 
		if (board[row][i]) 
			return false; 


	for (i = row, j = col; i >= 0 && j >= 0; i--, j--) 
		if (board[i][j]) 
			return false; 


	for (i = row, j = col; j >= 0 && i < N; i++, j--) 
		if (board[i][j]) 
			return false; 

	return true; 
} 


bool solve(int **board, int col, int N) 
{ 

	if (col >= N) 
		return true; 


	for (int i = 0; i < N; i++) { 

		if (isSafe(board, i, col, N)) { 

			board[i][col] = 1; 

			printBoard(board,N);
			if (solve(board, col + 1, N)) 
				return true; 

			board[i][col] = 0; 
		} 
	} 

	return false; 
} 




int main() 
{ 
	int n,**board;
	cout<<"Enter the number of queens : ";
	cin>>n;
	int size = sizeof(int *) * n;
	board = new int * [size];

	for(int i=0;i<n;i++)
		board[i] = new int(sizeof(int) * n);

	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		board[i][j] = 0;


	if (solve(board, 0, n) == false) { 
		cout<<"Solution does not exist"; 
		return false; 
	} 
	cout<<"\nFinal ";
	printBoard(board, n); 
	return 0; 
} 

