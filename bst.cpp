/*
 * =====================================================================================
 *
 *       Filename:  bst.cpp
 *
 *    Description:  Input is number of cases. One line with the order of the matrix.
 *    BST contains at most 100 elements. A line in which contains the value of -1 
 *    indicates the end of input.
 *
 *    Output, for each test case, print the case number, followed by messages
 *    indicating the height of the BST and the average of comparisons to search
 *    the keys of the BST in the form.
 *
 *        Version:  1.0
 *        Created:  28/10/13 00:47:32
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  YOUR NAME (), 
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <iomanip>

using namespace std;

const int maxRows = 100, maxColumns = 100;
int matrix[maxRows][maxColumns];
int rows, columns;

int leftNode(int rootRow, int rootColumn)
{
	rootColumn--;
	while(matrix[rootRow][rootColumn]==matrix[rootRow][rootColumn+1])
	{
		rootColumn--;
	}
	return rootColumn;
}
int rightNode(int rootRow, int rootColumn)
{
	rootRow++;
	while(matrix[rootRow][rootColumn]==matrix[rootRow-1][rootColumn])
	{
		rootRow++;
	}
	return rootRow;
}
int calculateTotalNodes ( int rootRow, int rootColumn )
{
	if (matrix[rootRow][rootColumn]!=0) {
		return  (
				1
				+ calculateTotalNodes ( rootRow, leftNode(rootRow,rootColumn) )
				+ calculateTotalNodes ( rightNode(rootRow,rootColumn), rootColumn )
			);
	}else{
		return 0;
	}

}		
int calculateHeight( int rootRow, int rootColumn )
{
	int heightLeft = 0, heightRight = 0;
	int left, right; 
	if(matrix[rootRow][rootColumn]!=0){
		left = leftNode(rootRow,rootColumn);
		right = rightNode(rootRow,rootColumn);
		if(matrix[rootRow][left]!=0){
			heightLeft = calculateHeight( rootRow, left ); 
		}
		if(matrix[right][rootColumn]!=0){
			heightRight = calculateHeight( right, rootColumn );
		}

		return ( (heightLeft>heightRight) ? heightLeft+1:heightRight+1 ); 
	}else{
		return 0;
	}

}
double calculateAverageComparisons ( int rootRow,  int rootColumn, int totalNodes, int comparisons )
{
	if (matrix[rootRow][rootColumn]!=0) {
		return  (
				comparisons*(1.0/totalNodes) 
				+ calculateAverageComparisons(rootRow,leftNode(rootRow,rootColumn), totalNodes, (comparisons+1)) 
				+ calculateAverageComparisons(rightNode(rootRow,rootColumn),rootColumn,totalNodes, (comparisons+1))
			);
	}else{
		return 0.0;
	}

}		
int main(int argc, const char *argv[])
{
	int matrixOrder;
	cin>>matrixOrder;
	rows = columns = matrixOrder;
	
	int caseNum = 1;
	while(matrixOrder!=-1)
	{
		for (int r = 0; r < rows; r++) {
			for (int c = 0; c < columns; c++) {
				cin>>matrix[r][c];
			}
		}
		
		int totalNodes = calculateTotalNodes( 0, columns-1 );
		int height = calculateHeight(0, columns-1);
		double averageComparisons = calculateAverageComparisons( 0, columns-1, totalNodes, 1 );
		
		cout<<"Case "<<caseNum<<":"<<endl;
		cout<<"The height of the BST is: "<<height<<endl;
		cout<<setprecision(2);
		cout<<"The average of the search in the BST is: "<<fixed<<averageComparisons<<endl;

		cin>>matrixOrder;
		rows = columns = matrixOrder;
	}	
	return 0;
}
