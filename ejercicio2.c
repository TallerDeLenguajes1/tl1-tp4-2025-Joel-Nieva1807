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

void eliminarNodo(nodo **Start){
    nodo *Nnodo = *Start;

    free(Nnodo->T.Descripcion);
    free(Nnodo);
    
}

void quitarNodo(nodo **Start, int idBuscado){
    nodo *nodoActual = *Start;
    nodo *nodoAnterior = NULL;

    while (nodoActual != NULL && nodoActual->T.TareaID != idBuscado)
    {
        nodoAnterior = nodoActual;
        nodoActual = nodoActual->Siguiente;
    }

    if (nodoActual ==NULL) //significa que no se encontro el nodo con ese dato (o que la lista esta vacia)
    {
        if (*Start == NULL)
        {
            puts("La lista vacia");
        }else
        {
            puts("No se encontro el elemento en la lista");
        }
        
        
    }else
    {
        if (*Start == nodoActual) //es para borrar el primer elemento
        {
            *Start = nodoActual->Siguiente; //la cabecera apunta al segundo elemento (en este caso)
        }else
        {
            nodoAnterior->Siguiente = nodoActual->Siguiente;
            
        }
        /* free(nodoActual->T.Descripcion);
        free(nodoActual); */
        eliminarNodo(&nodoActual);
        
        
    }
    
    
    
}

nodo *buscarNodo(nodo *Start, int idBuscado){
    nodo *Aux = Start;
    while (Aux && Aux->T.TareaID != idBuscado)
    {
        Aux = Aux ->Siguiente;
    }
    return Aux;
    
}

void cargarTareasPendientes(nodo **listaPendiente, int *puntero);
void transferirTareas(nodo **listaPendiente, nodo **listaRealizada);
void imprimirLista(nodo *start);
void mostrarTodasLasTareas(nodo **listaPendiente, nodo **ListaRealizada);
void consultarTarea(nodo **listaPendiente, nodo **ListaRealizada);
void mostrarPorID(nodo **lista);
void mostrarPorPalabra(nodo *Start, char arreglo[]);
void liberarMemoria(nodo **listaPendiente, nodo **ListaRealizada);

int main()
{
    srand(time(NULL));

    tareaPendiente= crearListaVacia();
    tareaRealizada= crearListaVacia();

    int opcion, contador=0, *puntero;
    puntero= &contador;

    do
    {
        puts("-----Modulo To-Do-----");
        puts("'1' Para cargar tareas pendientes.");
        puts("'2' Para transferir tareas pendientes a tareas realizadas:");
        puts("'3' Para imprimir las tareas pendientes y las tareas realizadas:");
        puts("'4' Para buscar una tarea (pendiente o realizada), ya sea por ID o por palabra clave:");
        puts("'0' Para salir del menu:");
        
        scanf("%d", &opcion);

        switch (opcion)
        {
        case 1:
            cargarTareasPendientes(&tareaPendiente, puntero);
            
            break;
    
        case 2:
            transferirTareas(&tareaPendiente, &tareaRealizada);
            
            break;

        case 3:
            mostrarTodasLasTareas(&tareaPendiente, &tareaRealizada);
            
            break;

        case 4:
            consultarTarea(&tareaPendiente, &tareaRealizada)
            ;
            
            break;
        
        default:
            puts("Ingrese un valor valido (desde 0 hasta 4).");
            break;
        }
        
    } while (opcion !=0);

    liberarMemoria(&tareaPendiente, &tareaRealizada);

 
    return 0;
}

void cargarTareasPendientes(nodo **listaPendiente, int *puntero){
    char respuesta;
    int duracion;
    
    
    do
    {

        char arreglo[30];
        
        fflush(stdin);
        puts("Ingrese la descripcion de la tarea");
        gets(arreglo);
        int tamCadena = strlen(arreglo) + 1;;

            do
            {
                puts("Ingrese la duracion de la tarea (entre 10 y 100) horas:");
                scanf("%d", &duracion);

                if (duracion<10 || duracion >100)
                {
                    puts("Invalido. Recuerde que debe ingresar un numero entre 10 hasta 100.");
                }
                
            } while (duracion<10 || duracion >100);
    
        nodo *nuevo = crearNodo(arreglo, tamCadena, duracion );
        nuevo->T.TareaID= ID + (*puntero);
        (*puntero)++;


        InsertarNodo(listaPendiente, nuevo);

        fflush(stdin);

        puts("¿Desea ingresar una nueva tarea ('s') o finalizar la carga('n')?");
        scanf("%c", &respuesta);

        fflush(stdin);
        
        
    } while (respuesta == 's');
    
}

void transferirTareas(nodo **listaPendiente, nodo **listaRealizada){
    int numero;
    nodo *cambio;
    puts("A continuacion se mostraran los ID con sus respectivas tareas:");
    imprimirLista(*listaPendiente);
    do
    {
        puts("Ingrese el ID de la tarea que quiere que se añada a las tareas realizadas. Si desea salir o terminar el proceso solo presione (0):");
        scanf("%d", &numero);
        fflush(stdin);
        cambio=buscarNodo(*listaPendiente, numero);
        if (cambio!=NULL)
        {
            // Crear un nuevo nodo con los mismos datos
            nodo *nuevo = crearNodo(cambio->T.Descripcion, strlen(cambio->T.Descripcion) + 1, cambio->T.Duracion);
            nuevo->T.TareaID = cambio->T.TareaID;

            InsertarNodo(listaRealizada, nuevo);
            quitarNodo(listaPendiente, numero);
        }
        
        
        
    } while (numero!=0);


    
}

void mostrarTodasLasTareas(nodo **listaPendiente, nodo **ListaRealizada){
    puts("");
    puts("Las tareas pendientes son:");
    imprimirLista(*listaPendiente);
    puts("");
    puts("Las tareas realizadas son:");
    imprimirLista(*ListaRealizada);
    
}

void imprimirLista(nodo *start){
    nodo *actual;
    for ( actual=start;actual!=NULL ;actual=actual->Siguiente )
    {
        printf("El ID de esta tarea es: %d.\n", actual->T.TareaID);
        printf("Su descripcion es: %s.\n", actual->T.Descripcion);
        printf("La duracion de la tarea es: %d\n", actual->T.Duracion);
        puts("-----------------");
    }
}

void consultarTarea(nodo **listaPendiente, nodo **ListaRealizada){
    int opcion;
    char palabra[25];
    puts("Indique si quiere buscar en tareas realizadas(1) o tareas pendientes (2)");
    scanf("%d", &opcion);
    fflush(stdin);

    if (opcion == 1)
    {
        puts("Indique si quiere hacer una busqueda por ID (3) o por palabra (4)");
        scanf("%d", &opcion);
        fflush(stdin);
        

        if (opcion==3)
        {
            
            mostrarPorID(ListaRealizada);
            puts("Lo mostrado corresponde a una tarea realizada:");
            
            
        }else if (opcion==4)
        {
            puts("Ingrese la palabra para buscar una tarea:");
            gets(palabra);
            mostrarPorPalabra(*ListaRealizada, palabra);
            puts("Lo mostrado corresponde a una tarea realizada:");

        }else
        {
            puts("Error. La proxima ingrese 3 o 4.");
            
        }
        
        
        
        
        
    }else if (opcion == 2)
    {
        puts("Indique si quiere hacer una busqueda por ID (3) o por palabra (4)");
        scanf("%d", &opcion);
        fflush(stdin);

        if (opcion==3)
        {
            mostrarPorID(listaPendiente);
            puts("Lo mostrado corresponde a una tarea pendiente:");
            
        }else if (opcion==4)
        {
            puts("Ingrese la palabra para buscar una tarea:");
            gets(palabra);
            mostrarPorPalabra(*listaPendiente, palabra);
            puts("Lo mostrado corresponde a una tarea pendiente:");

        }else
        {
            puts("Error. La proxima ingrese 3 o 4.");
            
        }
    }else
    {
        puts("Error. La proxima ingrese 1 o 2.");
    }

    fflush(stdin);
    
    
    
}

void mostrarPorID(nodo **lista){
    int numero;
    nodo *mostar;

    do
    {
        puts("Ingrese el ID de la tarea que quiere buscar. Si desea salir o terminar el proceso solo presione (0):");
        scanf("%d", &numero);
        fflush(stdin);
        mostar=buscarNodo(*lista, numero);
        if (mostar!=NULL)
        {


            printf("El ID de esta tarea es: %d.\n", mostar->T.TareaID);
            printf("Su descripcion es: %s.\n", mostar->T.Descripcion);
            printf("La duracion de la tarea es: %d\n", mostar->T.Duracion);
            puts("-----------------");
           

            
        }else
        {
            puts("No se encontró una tarea con ese ID.");
            
        }
        
        
        
        
    } while (numero!=0);
}

void mostrarPorPalabra(nodo *Start, char arreglo[]){
    nodo *Aux = Start;
    while (Aux && strstr(Aux->T.Descripcion, arreglo) == NULL)
    {
        Aux = Aux ->Siguiente;
    }
    
    if (Aux!=NULL)
    {
        printf("El ID de esta tarea es: %d.\n", Aux->T.TareaID);
        printf("Su descripcion es: %s.\n",Aux->T.Descripcion );
        printf("La duracion de la tarea es: %d\n", Aux->T.Duracion);
        puts("-----------------");
        
    }else
    {
        puts("No se encontró una tarea con esa palabra.");
        
    }
    

}

void liberarMemoria(nodo **listaPendiente, nodo **ListaRealizada){
    nodo *Aux = *listaPendiente;
    nodo *Aux2 = *ListaRealizada;
    nodo *siguiente = NULL;
    while (Aux!=NULL)
    {
        siguiente= Aux->Siguiente;
        free(Aux->T.Descripcion);
        free(Aux);
        Aux= siguiente;
    }
    while (Aux2!=NULL)
    {
        siguiente= Aux2->Siguiente;
        free(Aux2->T.Descripcion);
        free(Aux2);
        Aux2= siguiente;
    }

    
    
}
    