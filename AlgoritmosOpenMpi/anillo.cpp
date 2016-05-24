#include "mpi.h"
#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

static int RAM;

void Proceso(int id, int nprocesos);

void ServidorProceso(int id, int nprocesos,int t);


int main(int argc,char** argv ){
 int rank,size,testigo=4,t=0;
 srand(time(0));
 MPI_Init( &argc, &argv );
 MPI_Comm_rank( MPI_COMM_WORLD, &rank );
 MPI_Comm_size( MPI_COMM_WORLD, &size );
 

 
 if( size!=10){
   
      cout<<"El numero de procesos debe ser 10"<<endl<<flush;
   MPI_Finalize( ); return 0; 
 }
 if ((rank) == 0) { 
       //cout<<"ServidorProceso "<< rank <<endl<<flush;
      ServidorProceso(rank,size,testigo);  
  
 }else  if ((rank) < 5) { 
      // cout<<"ServidorProceso "<< rank <<endl<<flush;
      ServidorProceso(rank,size,t); 
      }else if(rank>4 && rank<11){
                  Proceso(rank,size);  
                 //  cout<<"Proceso "<< rank <<endl<<flush;
      }
 RAM=size;
 
 MPI_Finalize( );
 return 0;
}  

void ServidorProceso(int id, int nprocesos,int tes){
 int ten,testigo,de,ed;
    
    if(id==0)
       de=4;
    else de=id-1;
    
    if(id==4)
       ed=0;
     else ed=id+1;
    
 MPI_Status status;

 
 testigo=tes;
 
  
 while(1){

  if(testigo == 4){
  	 
 	 cout<<"Servidor Proceso "<<id<< " recibe token de Servidor Proceso "<<de <<endl<<flush;
 	 cout<<"Servidor Proceso "<<id<< " envia  a seccion critica a proceso "<<id+5 <<endl<<flush;
  	MPI_Ssend(&testigo, 1, MPI_INT, id+5, 0, MPI_COMM_WORLD); //le indico a proceso que entre a seccion critica
  	
 	MPI_Recv(&testigo, 1, MPI_INT, id+5, 0, MPI_COMM_WORLD,&status);
 	

        //envio el token a otro servidor proceso
        cout<<"Servidor Proceso "<<id<< " envia token a Servidor Proceso "<<ed <<endl<<flush;
 	MPI_Ssend(&testigo, 1, MPI_INT, ed, 0, MPI_COMM_WORLD);
  	
  	//cout<<"Ssale "<<ed<< " " <<de <<endl<<flush;
  	
  	testigo=0;
  	
  }else if(testigo==0){     

    MPI_Recv( &ten, 1, MPI_INT, de, 0, MPI_COMM_WORLD,&status);
    testigo=ten;
  }
 }
}

void Proceso(int id, int nprocesos){
int ten;
    
    
 MPI_Status status;


  
 while(1){
 
  
     MPI_Recv( &ten, 1, MPI_INT, id-5, 0, MPI_COMM_WORLD,&status);
 
      cout<<"Proceso "<<id<< " ejecutando seccion critica "<<endl<<flush;
      sleep((rand() % 3)+1);  
 	
        //envio el token
 	MPI_Ssend(&ten, 1, MPI_INT, id-5, 0, MPI_COMM_WORLD);
  	
  	      
  
 }
}


