#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define ID 1000
typedef struct Tarea{ 
    int TareaID;//Numérico autoincremental comenzando en 1000 
    char *Descripcion;  //       
    int Duracion; // entre 10 – 100  
}tarea;  

typedef struct Nodo{ 
    tarea T;  

    struct Nodo *Siguiente;  
}nodo;

nodo *crearNodo(char arreglo[], int tamaArreglo, int tiempo)
{
    nodo *NNodo=(nodo *)malloc(sizeof(nodo));
    NNodo->T.Duracion= tiempo;
    NNodo->T.Descripcion= (char*)malloc(sizeof(char)*tamaArreglo);
    strcpy(NNodo->T.Descripcion, arreglo);
    NNodo->Siguiente=NULL;
    return NNodo;
}

nodo *crearListaVacia()
{
    return NULL;
}

nodo *tareaPendiente, *tareaRealizada; // declaracion las listas a usar

void InsertarNodo(nodo **Start, nodo *Nodo){
    Nodo->Siguiente=*Start;
    *Start = Nodo;
}

nodo *buscarNodo(nodo *Start, int idBuscado){
    nodo *Aux = Start;
    while (Aux && Aux->T.TareaID != idBuscado)
    {
        Aux = Aux ->Siguiente;
    }
    return Aux;
    
}

void cargarTareasPendientes();
void transferirTareas();
void imprimirLista(nodo *start);

int main()
{
    srand(time(NULL));

    tareaPendiente= crearListaVacia();
    tareaRealizada= crearListaVacia();

    int opcion;

    do
    {
        puts("-----Modulo To-Do-----");
        puts("'1' Para cargar tareas pendientes.");
        puts("'2' Para transferir tareas pendientes a tareas realizdas:");
        
        
    
        scanf("%d", &opcion);
        
    } while (opcion < 1 || opcion > 4);

    switch (opcion)
    {
    case 1:
        cargarTareasPendientes(&tareaPendiente);
        
        break;

    case 2:
        ;
        
        break;

    
    
    default:
        break;
    }

    imprimirLista(tareaPendiente);
 
    return 0;
}

void cargarTareasPendientes(nodo **listaPendiente){
    char respuesta;
    int i=0, duracion;
    
    
    do
    {

        char arreglo[30];
        
        fflush(stdin);
        puts("Ingrese la descripcion de la tarea");
        gets(arreglo);
        int tamCadena = strlen(arreglo) + 1;;

        puts("Ingrese la duracion de la tarea (entre 10 y 100 horas):");
        scanf("%d", &duracion);

        nodo *nuevo = crearNodo(arreglo, tamCadena, duracion );
        nuevo->T.TareaID= ID +i;
        i++;


        InsertarNodo(listaPendiente, nuevo);

        fflush(stdin);

        puts("¿Desea ingresar una nueva tarea ('s') o finalizar la carga('n')?");
        scanf("%c", &respuesta);

        fflush(stdin);
        
        
    } while (respuesta == 's');
    
}

void transferirTareas(){
    
    puts("A continuacion se mostraran los ID de las tareas:");

}

void imprimirLista(nodo *start){
    nodo *actual;

    puts("La lista es:");

    for ( actual=start;actual!=NULL ;actual=actual->Siguiente )
    {
        printf("%s\n", actual->T.Descripcion);
        printf("%d\n", actual->T.Duracion);
        printf("%d\n", actual->T.TareaID);
        puts("-----------------");
    }
    
}
    