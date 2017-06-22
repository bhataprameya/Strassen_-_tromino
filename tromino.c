#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#include <math.h>

int num=1;
//Function to print the 2 dimentional matrix
void printmatrix(int n,int a[n][n])
{
	int i,j;
	char c='x';
	printf("\n");
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			if(a[i][j]==0)
				printf("%c  ",c);
			else
			{
				if(a[i][j]>9)
					printf("%d ",a[i][j]);
				else
					printf("%d  ",a[i][j]);
			}
		}
		printf("\n");
	}

	printf("\n");

}

//Recursive function to compute Tromino algorithum
void trominoTile(int n,int row,int col,int mat[n][n])
{
	int i,j;
	if(n==2)
	{
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
			{
				if(!(i==row && j==col))
					mat[i][j]=num;
			}
		num++;
	}
	else
	{
		int k,l,a00[n/2][n/2],a11[n/2][n/2],a10[n/2][n/2],a01[n/2][n/2];
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				a00[i][j]=mat[i][j];
			}
			for(j=n/2,k=0;j<n;j++,k++)
			{
				a01[i][k]=mat[i][j];
			}
		}

		for(i=n/2,k=0;i<n;i++,k++)
		{
			for(j=0;j<n/2;j++)
			{
				a10[k][j]=mat[i][j];
			}
			for(j=n/2,l=0;j<n;j++,l++)
			{
				a11[k][l]=mat[i][j];
			}
		}

		if(row<n/2 && col<n/2)
		{
			a01[n/2-1][0]=num;
			a10[0][n/2-1]=num;
			a11[0][0]=num;
			num++;
			trominoTile(n/2,row,col,a00);
			trominoTile(n/2,n/2-1,0,a01);
			trominoTile(n/2,0,n/2-1,a10);
			trominoTile(n/2,0,0,a11);

		}

		else if(row<n/2 && col<n)
		{
			a00[n/2-1][n/2-1]=num;
			a10[0][n/2-1]=num;
			a11[0][0]=num;
			num++;
			trominoTile(n/2,n/2-1,n/2-1,a00);
			trominoTile(n/2,row,col-(n/2),a01);
			trominoTile(n/2,0,n/2-1,a10);
			trominoTile(n/2,0,0,a11);
		}

		else if(row<n && col<n/2)
		{
			a00[n/2-1][n/2-1]=num;
			a01[n/2-1][0]=num;
			a11[0][0]=num;
			num++;
			trominoTile(n/2,n/2-1,n/2-1,a00);
			trominoTile(n/2,n/2-1,0,a01);
			trominoTile(n/2,row-(n/2),col,a10);
			trominoTile(n/2,0,0,a11);
		}
		else 
		{
			a00[n/2-1][n/2-1]=num;
			a01[n/2-1][0]=num;
			a10[0][n/2-1]=num;
			num++;
			trominoTile(n/2,n/2-1,n/2-1,a00);
			trominoTile(n/2,n/2-1,0,a01);
			trominoTile(n/2,0,n/2-1,a10);
			trominoTile(n/2,row-(n/2),col-(n/2),a11);
		}

		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				mat[i][j]=a00[i][j];
			}
			for(j=n/2,k=0;j<n;j++,k++)
			{
				mat[i][j]=a01[i][k];
			}
		}

		for(i=n/2,k=0;i<n;i++,k++)
		{
			for(j=0;j<n/2;j++)
			{
				mat[i][j]=a10[k][j];
			}
			for(j=n/2,l=0;j<n;j++,l++)
			{
				mat[i][j]=a11[k][l];
			}
		}

	}
}

//main function that take 3 argument k,row,column
int main (int argc, char* argv[])
{
	int n,row,col,i,j,k;
	if(argc!=4)
	{
		printf("Invalid No of Arguments\n ");
		exit(1);
	}
	k=atoi(argv[1]);
if(k<1)
{
printf("Invalid Parmeters\n");
exit(1);
}
	n=pow(2,k);
	row=atoi(argv[2]);
	col=atoi(argv[3]);
	if(n==0)
	{
		printf("Size of matrix cannot be 0\n ");
		exit(1);
	}
	int matrix[n][n];
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
		{
			matrix[i][j]=0;
		}

	//matrix[row][clo]=X;


	trominoTile(n,row,col,matrix);
	printmatrix(n,matrix);
}


