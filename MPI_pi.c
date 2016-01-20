
/******************************************************************* 
* MPI_pi.c 
* 
*Programa que calcula el valor de pi, usando una aproximación 
*rectangular a la integral de la funcion f(x) = 4/(1+x*x) 
*usando MPI. 
********************************************************************/ 

#include <stdio.h> 
#include "mpi.h" 

double pieza_de_pi(int,int,long); 

void main(int argc, char ** argv) 
{
long intervalos=160000000; 
int miproc, numproc; 
double pi, di; 
int i; 
MPI_Status status; 
double t3, t4; 

t3 = MPI_Wtime(); /* tiempo de inicio */ 
MPI_Init (&argc, &argv); /* Inicializar MPI */ 
MPI_Comm_rank(MPI_COMM_WORLD,&miproc); /* Determinar el rango del proceso invocado*/ 
MPI_Comm_size(MPI_COMM_WORLD,&numproc); /* Determinar el numero de procesos */ 

/* cada proceso ejecuta pieza_de_pi */ 
pi = pieza_de_pi(miproc, numproc, intervalos); 

if (miproc == 0) /* si es maestro recoge los resultados, suma y los imprime */ 
{
for (i = 1; i < numproc; i++) 
{ 
MPI_Recv (&di, 1, MPI_DOUBLE, i, 99, MPI_COMM_WORLD, &status); 
pi += di; 
} 

t4 = MPI_Wtime(); /* tiempo final */ 
printf("Valor de pi: %lf \n",pi); 
printf("Tiempo de ejecucion: %.3lf seg\n",t4-t3);
} 
else 
{ /* el esclavo envia los resultados al maestro */ 
MPI_Send(&pi, 1, MPI_DOUBLE, 0, 99, MPI_COMM_WORLD); 
} 
MPI_Finalize (); 

} 


double pieza_de_pi(int idproc, int nproc, long intervalos) 
{
double ancho, x, localsum; 
long j; 

ancho = 1.0 / intervalos; /* peso de la muestra */ 
localsum = 0.0; 
for (j = idproc; j < intervalos; j += nproc) 
{ 
x = (j + 0.5) * ancho; 
localsum += 4 / (1 + x * x); 
} 

return(localsum * ancho);
} 

