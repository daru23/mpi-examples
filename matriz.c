/*
  Multiplicacion de matriz en paralelo
  Usando mas de un core
*/
#include <stdio.h>
#include <math.h>
#include "mpi.h"
#define FA 64         /* number of rows in matrix A */ 
#define CA 15         /* number of cols in matrix A */ 
#define CB 7          /* number of cols in matrix B */ 

//Array to be divided among the process
int a[FA][CA];
int b[CA][CB];
int c[FA][CB];
//Aux Variables 
int FB=CA;//To be sure that multiplication is possible

int main(int argc, char *argv[]){
	int i,j,k;
	double inicio, final, tiempo;

	MPI_Init(&argc,&argv);

//******* master process ***********/
// Fill the matrix out and print it out 
	inicio = MPI_Wtime();
	//Just the 0 procesor fill in the matrix
	for (i=0;i<FA;i++){
		for (j=0;j<CA;j++){
			a[i][j]=i*j+1;//Any function to give a value the matrix
			printf("%d\t",a[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
	for (i=0;i<FB;i++){
		for (j=0;j<CB;j++){
			b[i][j]=i+3*j;
			printf("%d\t",b[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	
	/*printf("From process %d\n",myid);
	for (i=0;i<FA;i++){
		for (j=0;j<CA;j++){
			printf("%d\t",a[i][j]);
		}
		printf("\n");
	}	
	printf("\n");
	for (i=0;i<FB;i++){
		for (j=0;j<CB;j++){
			printf("%d\t",b[i][j]);
		}
		printf("\n");
	}
	printf("\n");*/

	//Multiplication
	for (i=0;i<FA;i++){
		for(j=0;j<CB;j++){
			c[i][j]=0;
			for(k=0;k<CA;k++){
				c[i][j]= c[i][j] + a[i][k]*b[k][j];
			}
		}
	}

	printf("El Final result is:\n");
	for (i=0;i<FA;i++){
		for (j=0;j<CB;j++){
			printf("%d\t",c[i][j]);
		}
		printf("\n");
	}
	final=MPI_Wtime();
	tiempo = final - inicio;
	printf("It takes %lf ms to calculate the matrix\n",tiempo*1000);


	MPI_Finalize();
	return 0;
}

