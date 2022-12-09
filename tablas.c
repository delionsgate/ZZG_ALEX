/*
UNIVERSIDAD NACIONAL AUTÓNOMA DE MÉXICO
Facultad de Ingeniería
Compiladores  -  Grupo 03
Semestre 2023-1
Profesora: Laura Sandoval

Por: Zuriel Zárate García
Fecha: 2 de noviembre de 2022
Descripción: Conjunto de funciones para la creación de tablas
			 y catálogos de un analizador léxico.
*/

#include "tablas.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


//>>>>>>>>>>>>>>>>>>>>>>>> FUNCIONES DE CUALQUIER COMPONENTE LÉXICO

/*
  Reserva memoria para la información de un componente léxico.
  Devuelve la dirección de memoria del nuevo componente.
*/
Componente* CrearComponente(){
	Componente *componente;
	componente = (Componente*) malloc(sizeof(Componente));
    if (componente == NULL){
        printf("\nError: Espacio insuficiente para crear el componente");
        return NULL;
    }
    componente->clase = (int) malloc(sizeof(int));
    componente->valor = (int) malloc(sizeof(int));
    componente->cadena = (char*) malloc(100*sizeof(char));
    componente->tipo = (int) malloc(sizeof(int));
    return componente;
}

/*
  Recibe un componente léxico para imprimir su información.
  Además, recibe el apuntador a un archivo para escribir
  dicha información en él.
*/
void ImprimeComponente(Componente componente, FILE* archivo){
	printf(" %d", componente.clase);
	printf(" 	  %d", componente.valor);
	printf(" 	%s", componente.cadena);
	if(componente.tipo >= 0 && componente.tipo <= 16){
		printf("  (tipo %d)", componente.tipo);
	}

	fprintf(archivo,"  %d", componente.clase);
	fprintf(archivo," 	  %d", componente.valor);
	fprintf(archivo," 	%s", componente.cadena);
	if(componente.tipo >= 0 && componente.tipo <= 16){
		fprintf(archivo,"  (tipo %d)", componente.tipo);
	}
}


//>>>>>>>>>>>>>>>>>>>>>>>> FUNCIONES PARA  LA CREACION DE LAS TABLAS

/*
	Recibe la información de un componente para apropiarla
	y la dirección del nodo siguiente.
	Devuelve la dirección de memoria del nuevo nodo.
*/
Nodo *crearNodo(Componente *componente, Nodo *sig){
    Nodo *nuevo;
	//Apartamos lugar en memoria
    nuevo = (Nodo*) malloc (sizeof(Nodo));
    if (nuevo == NULL){
        printf("\nError: Espacio insuficiente para crear el nodo...\n");
    	return NULL;
	}
	nuevo->info=(Componente*) malloc(sizeof(Componente));
    nuevo->info = componente;
    nuevo->sig = sig;

    return nuevo;
}

/*
	Creación de una lista ligada para la representación
	de las tablas.
	Devuelve la dirección de memoria de la lista.
*/
Tabla *crearTabla(){
    Tabla *nuevaTabla;
    nuevaTabla = (Tabla*) malloc (sizeof(Tabla));
    if (nuevaTabla == NULL){
        printf("\nError: Espacio insuficiente para crear el catalogo de palabras reservadas...\n");
    	return NULL;
	}
    nuevaTabla->H = NULL;
    nuevaTabla->T = NULL;

    return nuevaTabla;
}

/*
	Simplemente retorna la comparación entre
	el primer nodo de la tabla que recibe y NULL.
*/
int TablaVacia(Tabla tabla){ //regresa diferente de cero, dif de 0 es verdadero
    return tabla.H == NULL;
}

/*	
	Recibe la dirección de la lista en la que se quiere insertar un
	nuevo componente y la dirección del componente que se quiere agregar.
*/
void insertar(Tabla *tabla, Componente *componente){
    Nodo *nuevo;
    nuevo = crearNodo(componente, NULL); //sigiente siempre debe de ser NULL
    if (TablaVacia(*tabla)){ //vacia caso a
        tabla->H = nuevo;
    }
    else{
        tabla->T->sig = nuevo;
    }
    tabla->T = nuevo; //caso a y b
}

/*
	Recibe la lista que se quiere imprimir y la dirección
	de un archivo para escribir en él
*/
void ImprimeTabla(Tabla tabla, FILE* archivo){
    Nodo *q = tabla.H;
    while(q != NULL){
        ImprimeComponente(*q->info,archivo);
        printf("\n");
        fprintf(archivo,"\n");
        q = q->sig;
    }
    printf("\n");
    fprintf(archivo,"\n");
}

/*
	Recibe la lista en la que va a buscar y la cadena de
	la que se evaluará su existencia en dicha tabla.
	El algorítmo es de búsqueda lineal, es decir, 
	prueba elemento por elemento y revisa si
	coincide con el valor buscado.
*/
Nodo *buscar(Tabla tabla, char* cad){
    Nodo *q = tabla.H;
    while(q != NULL){
        if(strcmp(q->info->cadena,cad) == 0){ //Si la cadena coincide
            return q;
        }
        q = q->sig;
    }
    printf("\n");
    return NULL;
}

/*
	Libera la memoria ocupada por un componente
	Recibe la dirección de memoria del componente a liberar.
*/
void LiberaMemoria(Componente *componente){
	free(componente->clase);
	free(componente->valor);
	free(componente->cadena);
	free(componente->tipo);
	free(componente);
	componente = NULL;
}

/*
	Imprime la información de un Componente
	con el formato de Token.
	Recibe el componente.
*/
void ImprimeToken(Componente infotoken){
	int clase = infotoken.clase;
	if(clase==5|clase==6|clase==8){
		printf("(%d,%s)", clase,infotoken.cadena);
	}else{
		printf("(%d,%d)",clase,infotoken.valor);	
	}
}

/*
	Imprime la lista de tokens
	Recibe la lista que se quiere imprimir.
*/
void ImprimeListaTokens(Tabla lista){
    Nodo *q = lista.H;
    while(q != NULL){
        ImprimeToken(*q->info);
        printf("\n");
        q = q->sig;
    }
    printf("\n");
}

/*
	Recibe la lista en la que va a buscar y la
	posición del atomo en la cadena de átomos.
	Con esto, podemos devolver el token y 
	obtener su información.
*/
Nodo* buscarToken(Tabla tabla, int numAtomo){
    Nodo *q = tabla.H;
    for(int i=0; i<numAtomo; i++){
        q = q->sig;
    }
    return q;
}

/*
	Convierte de octal a decimal. Recibe la cadena
	con la forma o<numeros> y devuelve el valor
	decimal.
*/
int octadec(char* octal){
	int i = strlen(octal)-2;
	char c;
	int ent;
	int decim = 0;
	while(i>=0){
		octal = octal+1;
		c = *octal;
		ent = c-'0';
		printf("\nn: %d*pow(8,%d)",ent,i);
		decim = decim + ent*pow(8,i);
		i--;
	}
	return decim;
}