#include "mpi.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

static int RAM;

void Proceso(int id, int nprocesos);
void Servidor(int id, int nprocesos);

int main(int argc,char** argv ){
 int rank,size;
 srand(time(0));
 MPI_Init( &argc, &argv );
 MPI_Comm_rank( MPI_COMM_WORLD, &rank );
 MPI_Comm_size( MPI_COMM_WORLD, &size );
 

 
 if( size!=6){
   
      cout<<"El numero de procesos debe ser 6"<<endl<<flush;
   MPI_Finalize( ); return 0; 
 }
 if ((rank) == 0) { 
       //cout<<"proceso "<< rank <<endl<<flush;
      Servidor(rank,size); // Los pares son Filosofos 
  
 }else  if ((rank) > 0) { 
            //cout<<"proceso "<< rank <<endl<<flush;
      Proceso(rank,size); // Los pares son Filosofos 
      }
 RAM=size;
 
 MPI_Finalize( );
 return 0;
}  

void Proceso(int id, int nprocesos){
  int testigo,var;
   
  
 MPI_Status status;
  
  
 while(1){

  	MPI_Ssend(&var, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
  	cout<<"Proceso "<<id<< " pide token al Servidor "<<endl<<flush;
  	MPI_Recv( &testigo, 1, MPI_INT, 0, 0, MPI_COMM_WORLD,&status);
	//si tenemos token ejecutamos seccion critica
  	if(testigo==4){
  		cout<<"Proceso "<<id<< " recibe token del Servidor "<<endl<<flush;
  	
  		cout<<" EJECUTA SECCION CRITICA "<<endl<<flush;
  	        sleep((rand() % 3)+1);  
  		cout<<"Proceso "<<id<< " devuelve token al Servidor "<<endl<<flush;
  	
  		MPI_Ssend(&testigo, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
 	}
  }
 
}

void Servidor(int id, int nprocesos){
int testigo=4,pro,var,count;
    

 MPI_Status status;


 while(1){
      // Espera un peticion desde cualquier proceso ...
      MPI_Probe(MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
     // Se averigua el tamaño y el proceso emisor del mensaje
    MPI_Get_count(&status, MPI_INT, &count);
    pro= status.MPI_SOURCE;
      
       MPI_Recv( &var, 1, MPI_INT, pro, 0, MPI_COMM_WORLD,&status);
       cout<<"Servidor  "<<id<< " recibe peticion de  proceso "<<pro <<endl<<flush;
             
      cout<<"Servidor  "<<id<< " envia token a proceso "<<pro <<endl<<flush;
      MPI_Ssend(&testigo, 1, MPI_INT, pro, 0, MPI_COMM_WORLD);
      

      MPI_Recv( &var, 1, MPI_INT, pro, 0, MPI_COMM_WORLD,&status);
      cout<<"Servidor  "<<id<< " recibe token de proceso "<<pro <<endl<<flush;
      
      
      
 }
}



