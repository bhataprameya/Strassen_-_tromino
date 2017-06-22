#include<stdio.h>
#include<string.h>
#include<math.h>
#include<time.h>
#include <stdlib.h>

//Function to print the 2 dimentional matrix
void printmatrix(int n,float a[n][n])
{
	int i,j;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
			printf("%.2f ",a[i][j]);
		printf("\n");
	}

	printf("\n");

}

//Function to calculate the sum of 2 dimentional matrices
void sum(int n,float a[n][n], float b[n][n],float c[n][n])
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			c[i][j]=a[i][j]+b[i][j];
}

//Function to subtract 2 2-dimentional matrices
void sub(int n,float a[n][n], float b[n][n],float c[n][n])
{
	int i,j;
	for(i=0;i<n;i++)
		for(j=0;j<n;j++)
			c[i][j]=a[i][j]-b[i][j];
}

//Function to calculate the calculate Strassens multiplication
void recusriveStrassensMultFunction(int n,float a[n][n], float b[n][n], float c[n][n])
{
	float m1,m2,m3,m4,m5,m6,m7;
	m1= (a[0][0] + a[1][1])*(b[0][0]+b[1][1]);
	m2= (a[1][0]+a[1][1])*b[0][0];
	m3= a[0][0]*(b[0][1]-b[1][1]);
	m4= a[1][1]*(b[1][0]-b[0][0]);
	m5= (a[0][0]+a[0][1])*b[1][1];
	m6= (a[1][0]-a[0][0])*(b[0][0]+b[0][1]);
	m7= (a[0][1]-a[1][1])*(b[1][0]+b[1][1]);

	c[0][0]=m1+m4-m5+m7;
	c[0][1]=m3+m5;
	c[1][0]=m2+m4;
	c[1][1]=m1+m3-m2+m6;

}


//Recursive function to compute matricx multiplication using Strassens methord
void customRecusriveStrassensMultFunction(int n, float a[n][n], float b[n][n], float c[n][n])
{
	if(n==2)
	{
		recusriveStrassensMultFunction( n,a,b,c);
	}
	else
	{
		float a00[n/2][n/2],b00[n/2][n/2],a11[n/2][n/2],b11[n/2][n/2],a10[n/2][n/2],b10[n/2][n/2],a01[n/2][n/2],b01[n/2][n/2],m1[n/2][n/2],m2[n/2][n/2],m3[n/2][n/2],m4[n/2][n/2],m5[n/2][n/2],m6[n/2][n/2],m7[n/2][n/2],temp[n/2][n/2],temp1[n/2][n/2],c00[n/2][n/2],c01[n/2][n/2],c10[n/2][n/2],c11[n/2][n/2];
		int i,j,k,l;
		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				a00[i][j]=a[i][j];
				b00[i][j]=b[i][j];
			}
			for(j=n/2,k=0;j<n;j++,k++)
			{
				a01[i][k]=a[i][j];
				b01[i][k]=b[i][j];
			}
		}

		for(i=n/2,k=0;i<n;i++,k++)
		{
			for(j=0;j<n/2;j++)
			{
				a10[k][j]=a[i][j];
				b10[k][j]=b[i][j];
			}
			for(j=n/2,l=0;j<n;j++,l++)
			{
				a11[k][l]=a[i][j];
				b11[k][l]=b[i][j];
			}
		}


		sum(n/2,a00,a11,temp);sum(n/2,b00,b11,temp1);
		customRecusriveStrassensMultFunction(n/2,temp,temp1,m1);   //Calculate M1

		sum(n/2,a10,a11,temp);
		customRecusriveStrassensMultFunction(n/2,temp,b00,m2);   //Calculate M2

		sub(n/2,b01,b11,temp);
		customRecusriveStrassensMultFunction(n/2,a00,temp,m3);   //Calculate M3

		sub(n/2,b10,b00,temp);
		customRecusriveStrassensMultFunction(n/2,a11,temp,m4);   //Calculate M4

		sum(n/2,a00,a01,temp);
		customRecusriveStrassensMultFunction(n/2,temp,b11,m5);   //Calculate M5

		sub(n/2,a10,a00,temp);sum(n/2,b00,b01,temp1);
		customRecusriveStrassensMultFunction(n/2,temp,temp1,m6);   //Calculate M6

		sub(n/2,a01,a11,temp);sum(n/2,b10,b11,temp1);
		customRecusriveStrassensMultFunction(n/2,temp,temp1,m7);   //Calculate M7

		sum(n/2,m1,m4,temp);sub(n/2,temp,m5,temp1);sum(n/2,temp1,m7,c00); //Claculate c00

		sum(n/2,m3,m5,c01);//Claculate c01

		sum(n/2,m2,m4,c10);//Claculate c10

		sum(n/2,m1,m3,temp);sub(n/2,temp,m2,temp1);sum(n/2,temp1,m6,c11); //Claculate c11

		for(i=0;i<n/2;i++)
		{
			for(j=0;j<n/2;j++)
			{
				c[i][j]=c00[i][j];
			}
			for(j=n/2,k=0;j<n;j++,k++)
			{
				c[i][j]=c01[i][k];
			}
		}

		for(i=n/2,k=0;i<n;i++,k++)
		{
			for(j=0;j<n/2;j++)
			{
				c[i][j]=c10[k][j];
			}
			for(j=n/2,l=0;j<n;j++,l++)
			{
				c[i][j]=c11[k][l];
			}
		}

	}

}

//Wrapper function to calculate strassen matrix multiplication
void strassensMultiplication(int n, float a[n][n], float b[n][n], float c[n][n])
{ 
	int i,j,k;
	if(n==1)
	{
		c[0][0]=a[0][0]*b[0][0];
	}
	else
	{
		if(!(n & (n - 1)))
		{
			customRecusriveStrassensMultFunction(n,a,b,c);
		}
		else
		{
			int newN = pow(2, ceil(log(n)/log(2)));
			float aNew[newN][newN],bNew[newN][newN],cNew[newN][newN];

			for(i=0;i<newN;i++)
				for(j=0;j<newN;j++)
				{
					if(i<n && j<n)
					{
						aNew[i][j]=a[i][j];
						bNew[i][j]=b[i][j];
					}
					else
					{
						aNew[i][j]=0;
						bNew[i][j]=0;
					}
					cNew[i][j]=0;
				}
			customRecusriveStrassensMultFunction(newN,aNew,bNew,cNew);
			for(i=0;i<n;i++)
				for(j=0;j<n;j++)
					c[i][j]=cNew[i][j];
		}
	}
	printf("Strassen’s Multiplication Output: \n");
	printmatrix(n,c);
}



//Standard matrix Multiplication function
void standardMultiplication(int n, float a[n][n], float b[n][n], float d[n][n])
{ 
	int i,j,k;
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			d[i][j]=0;
			for(k=0;k<n;k++)
			{
				d[i][j]+=a[i][k]*b[k][j];
			}
		}
	}
	printf("Standard Multiplication Output:\n");
	printmatrix(n,d);
}


//Main function To generate 2 random matrrix and call the matrix multiplication functions
int main(int argc, char *argv[])
{
	int i,j,n,k,range=10;

	if(argc!=2)
	{
		printf("Invalid No of Arguments\n ");
		exit(1);
	}
	n=atoi(argv[1]);
	if(n==0)
	{
		printf("Size of matrix cannot be 0\n ");
		exit(1);
	}
	float a[n][n],b[n][n],c[n][n],d[n][n];

	srand((unsigned int)time(NULL));
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			a[i][j]=roundf(((((float)rand()/(float)(RAND_MAX)) * range)-5)*100)/100;
			b[i][j]=roundf(((((float)rand()/(float)(RAND_MAX)) * range)-5)*100)/100;
		}
	}
	printf("\n");
	printf("Matrix A:\n");
	printmatrix(n,a);
	printf("Matrix B:\n");
	printmatrix(n,b);
	printf("\n\n");
	strassensMultiplication(n,a,b,c);
	standardMultiplication(n,a,b,d);
	return 0;
}
