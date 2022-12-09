#ifndef TABLAS_H_INCLUDED
#define TABLAS_H_INCLUDED
#include <stdio.h>

/*
	Información que pueden incluir
	los componentes. Clase y valor
	ayudan a obtener la posición para
	el token.

	Cadena es la cadena reconocida (yytext)
	y tipo sirve para los identificadores
*/
typedef struct{
	int clase;
	int valor;
	char *cadena;
	int tipo;
} Componente;

/*
	Definición de un nodo de la lista ligada
*/
typedef struct nodo{
	Componente *info;
	struct nodo *sig;
} Nodo;

/*
	Definición de la lista ligada
*/
typedef struct{
	Nodo *H; //HEAD
	Nodo *T; //TAIL

} Tabla;

/*
	Prototipos
*/
Componente* CrearComponente();
void ImprimeComponente(Componente componente, FILE* archivo);
Nodo *crearNodo(Componente *componente, Nodo *sig);
Tabla *crearTabla();
int TablaVacia(Tabla tabla);
void insertar(Tabla *tabla, Componente *componente);
void ImprimeTabla(Tabla tabla, FILE* archivo);
Nodo *buscar(Tabla tabla, char* cadena);
void LiberaMemoria(Componente *componente);

void ImprimeToken(Componente infotoken);
void ImprimeListaTokens(Tabla lista);

Nodo* buscarToken(Tabla tabla, int numAtomo);
int octadec(char* octal);

#endif // TABLAS_H_INCLUDED
