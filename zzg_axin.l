%{
/*
UNIVERSIDAD NACIONAL AUTÓNOMA DE MÉXICO
Facultad de Ingeniería
Compiladores  -  Grupo 03
Semestre 2023-1
Profesora: M.C. Laura Sandoval Montaño

Por: Zuriel Zárate García
Fecha: 08 de diciembre de 2022

Descripción: Construcción de un analizador Léxico-Sintáctico Recursivo Descendente
             que revisa programas escritos en el lenguaje definido por la gramática
             del "Anexo A" del documento: "ProgAnalizadorSintactico2023-1.pdf".
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include "tablas.h"
#include "asin.h"
FILE *archSal;
int linea=1; //Se agrega contador de lineas en el análisis léxico

int token = 0;    //Contador de tokens
int simbolo = -1; //Contador de identificadores
int real = -1;    //Contador de constantes reales
int cadenita = -1;//Contador de cadenas
int tipo = -1; //Valor por defecto del tipo

char str[10000]="";//Arreglo para la cadena de atomos
/*NOTA: Se agrega a "tipo" de la estructura de los tokens
        la linea donde se escribió la cadena reconocida.
        A su vez, se agregaron las evaluaciones necesarias
        para concatenar los átomos a la cadena de átomos 'str'.
        */

//Declaración de listas simplemente ligadas para tablas.
Tabla *catalogoPR;      //Catálogo de Palabras Reservadas
Tabla *catalogoOR;      //Catálogo de Operadores Relacionales
Tabla *identificadores; //Tabla de símbolos
Tabla *reales;          //Tabla de literales (constantes reales)
Tabla *cadenas;         //Tabla de literales (constantes cadena)
Tabla *tokens;          //Lista de tokens
%}

/* EXPRESIONES REGULARES */

/*0.- Palabras reservadas*/
CASE        "alternative"
LONG        "big"
IF          "evaluate"
ELSE        "instead"
DOUBLE      "large"
WHILE       "loop"
DO          "make"
INT         "number"
DEFAULT     "other"
FLOAT       "real"
FOR         "repeat"
SWITCH      "select"
SHORT       "small"
CONTINUE    "step"
BREAK       "stop"
CHAR        "symbol"
RETURN      "throw"

RESERVADAS {CASE}|{LONG}|{IF}|{ELSE}|{DOUBLE}|{WHILE}|{DO}|{INT}|{DEFAULT}|{FLOAT}|{FOR}|{SWITCH}|{SHORT}|{CONTINUE}|{BREAK}|{CHAR}|{RETURN}

/*1.- Identificadores*/
PESOS       "$"
LETRA       [a-zA-Z]
IDENTIFICADOR {PESOS}({LETRA})+

/*2.- Constantes numéricas enteras*/
ENTERODEC   [1-9]([0-9])*|(0)+
ENTEROCT    [oO]([0-7])+

/*3.- Constantes numéricas reales*/
PUNTO       "."
REAL -?([1-9]([0-9])*){0,8}{PUNTO}[0-9]{1,4}
                                            /*{min,max} min es el minimo de ocurrencias y max el maximo de
                                            ocurrencias que puede tener la expresión antes del {min,max}*/
/*4.- Constantes cadenas*/
CADENA (\"[^\n"']{2,100}\")|(\'[^\n']{1,1}\')|(\"[']\")
                                  /*
                                    \"         -> Comillas dobles.
                                    ^\n"'        -> Cualquier caracter menos \n, comillas dobles o apostrofo
                                    {2,*}      -> Para comilas dobles, debe haber al menos 2 caracteres y puede haber hasta 100 caracteres (valor arbitrario)
                                    [^\n']{1,1}  -> Para comillas simples, debe haber, como mínimo, 1 caracter y máximo 1 caracter (menos apostrofe)
                                    (\"\[']\")   -> Caso especial de la cadena de apostrofe
                                  */

/*5.- Símbolos especiales*/
CORCHETEIZQ "["
CORCHETEDER "]"
PARIZQ      "("
PARDER      ")"
LLAVEIZQ    "{"
LLAVEDER    "}"
COMA        ","
DOSPUNTOS   ":"
PUNTOYCOMA  ";"

ESPECIALES {CORCHETEIZQ}|{CORCHETEDER}|{PARIZQ}|{PARDER}|{LLAVEIZQ}|{LLAVEDER}|{COMA}|{DOSPUNTOS}|{PUNTOYCOMA}

/*6.- Operadores aritméticos*/
MAS         "+"
MENOS       "-"
POR         "*"
DIAG        "/"
ANTIDIAG    "\\"
MOD         "%"
CIRCUNFLEJO "^"

OPARI {MAS}|{MENOS}|{POR}|{DIAG}|{ANTIDIAG}|{MOD}|{CIRCUNFLEJO}

/*7.- Operadores relacionales*/
MENQUE      "<"
MAYQUE      ">"
MENIG       "<="
MAYIG       ">="
IGUALIGUAL  "=="
DIFERENTE   "!="

OPREL {MENQUE}|{MAYQUE}|{MENIG}|{MAYIG}|{IGUALIGUAL}|{DIFERENTE}

/*8.- Operadores de asignación*/
IGUAL       "="

ASIGNACION {IGUAL}


LINEA .\n

/* ACCIONES A REALIZAR CON COMPONENTES LÉXICOS VÁLIDOS */
%%
{RESERVADAS}    {   printf("\nPALABRA RESERVADA RECONOCIDA ===> %s",yytext);
                    /*Si detecta un tipo de dato, cambia el valor de "tipo" globalmente*/

                    Componente* aux = CrearComponente();
                    Nodo* buscado = crearNodo(aux,NULL);
                    buscado = buscar(*catalogoPR,yytext);
                    if(buscado==NULL){
                        printf("no se encontro la palabra reservada en el catalogo");
                    }
                    tipo = buscado->info->valor;

                    /*Se genera el token*/
                    token++;
                    printf("\nTOKEN %d: (0,%d) \n",token,tipo);
                    fprintf(archSal,"TOKEN %d: (0,%d)\n",token,tipo);

                    Componente* nuevoToken = CrearComponente();
                    nuevoToken->clase = 0;
                    nuevoToken->valor = tipo;
                    nuevoToken->tipo = linea;
                    insertar(tokens,nuevoToken);

                    /* Añadimos átomo a la cadena */
                    
                    if(strcmp(yytext,"alternative")==0){
                        concatena('a',str);
                    }else if(strcmp(yytext,"big")==0){
                        concatena('b',str);
                    }else if(strcmp(yytext,"evaluate")==0){
                        concatena('f',str);
                    }else if(strcmp(yytext,"instead")==0){
                        concatena('t',str);
                    }else if(strcmp(yytext,"large")==0){
                        concatena('g',str);
                    }else if(strcmp(yytext,"loop")==0){
                        concatena('w',str);
                    }else if(strcmp(yytext,"make")==0){
                        concatena('m',str);
                    }else if(strcmp(yytext,"number")==0){
                        concatena('#',str);
                    }else if(strcmp(yytext,"other")==0){
                        concatena('o',str);
                    }else if(strcmp(yytext,"real")==0){
                        concatena('x',str);
                    }else if(strcmp(yytext,"repeat")==0){
                        concatena('j',str);
                    }else if(strcmp(yytext,"select")==0){
                        concatena('h',str);
                    }else if(strcmp(yytext,"small")==0){
                        concatena('p',str);
                    }else if(strcmp(yytext,"step")==0){
                        concatena('c',str);
                    }else if(strcmp(yytext,"stop")==0){
                        concatena('q',str);
                    }else if(strcmp(yytext,"symbol")==0){
                        concatena('y',str);
                    }else if(strcmp(yytext,"throw")==0){
                        concatena('z',str);
                    }else{
                        printf("Algo no salio bien en PALABRAS RESERVADAS");
                    }

                }

{IDENTIFICADOR} {   printf("\nIDENTIFICADOR RECONOCIDO ===> %s",yytext);
                    if(buscar(*identificadores,yytext) == NULL){
                        simbolo++; //Posición nueva del identificador en la tabla
                        Componente* aux = CrearComponente();
                        aux->clase = 1;
                        aux->valor = simbolo;
                        strcpy(aux->cadena,yytext);
                        aux->tipo = tipo;

                        insertar(identificadores,aux);
                        printf("\nIdentificador agregado. >>> %s \n",aux->cadena);
                        //ImprimeTabla(*identificadores);

                        /*Se genera el token*/
                        token++;
                        printf("\nTOKEN %d: (1,%d) \n",token,simbolo);
                        fprintf(archSal,"TOKEN %d: (1,%d)\n",token,simbolo);

                        Componente* nuevoToken = CrearComponente();
                        nuevoToken->clase = 1;
                        nuevoToken->valor = simbolo;
                        nuevoToken->tipo = linea;
                        insertar(tokens,nuevoToken);
                    }
                    else{
                        printf("\nEl identificador ya está en la tabla de simbolos. \n");
                        Componente* aux = CrearComponente();
                        Nodo* buscado = crearNodo(aux,NULL);
                        buscado = buscar(*identificadores,yytext);
                        if(buscado==NULL){
                            printf("no se encontro el identificador en la tabla de simbolos");
                        }
                        int val = buscado->info->valor;

                        /*Se genera el token*/
                        token++;
                        printf("\nTOKEN %d: (1,%d) \n",token,val);
                        fprintf(archSal,"TOKEN %d: (1,%d)\n",token,val);

                        Componente* nuevoToken = CrearComponente();
                        nuevoToken->clase = 1;
                        nuevoToken->valor = val;
                        insertar(tokens,nuevoToken);
                    }

                    /* Añadimos átomo a la cadena*/
                    
                    concatena('i',str);
                }


{ENTERODEC}     {   printf("\nENTERO DECIMAL RECONOCIDO ===> %s",yytext);
                    /*Se genera el token*/
                    token++;
                    printf("\nTOKEN %d: (2,%s) \n",token,yytext);
                    fprintf(archSal,"TOKEN %d: (2,%s)\n",token,yytext);

                    Componente* nuevoToken = CrearComponente();
                    nuevoToken->clase = 2;
                    strcpy(nuevoToken->cadena,yytext); //Aquí el valor es la cadena
                    nuevoToken->valor = (int) atoi(yytext);
                    nuevoToken->tipo = linea;
                    insertar(tokens,nuevoToken);

                    /* Añadimos átomo a la cadena*/
                    
                    concatena('n',str);
                }
{ENTEROCT}      {   printf("\nENTERO OCTAL RECONOCIDO ===> %s",yytext);

                    Componente* nuevoToken = CrearComponente();
                    nuevoToken->clase = 2;
                    strcpy(nuevoToken->cadena,yytext); //Aquí el valor es la cadena
                    int entoct = octadec(nuevoToken->cadena); //Se convierte a decimal
                    nuevoToken->valor = entoct;
                    nuevoToken->tipo = linea;
                    printf("\n   Valor decimal: %d\n",entoct);
                    insertar(tokens,nuevoToken);

                    /*Se genera el token*/
                    token++;
                    printf("\nTOKEN %d: (2,%d) \n",token,nuevoToken->valor);
                    fprintf(archSal,"TOKEN %d: (2,%d)\n",token,nuevoToken->valor);

                    /* Añadimos átomo a la cadena*/
                    
                    concatena('n',str);
                }


{REAL}          {   printf("\nCONSTANTE REAL RECONOCIDA ===> %s",yytext);
                    real++; //Posición nueva en la tabla
                    Componente* aux = CrearComponente();
                    aux->clase = 3;
                    aux->valor = real;
                    strcpy(aux->cadena,yytext);

                    insertar(reales,aux);
                    printf("\nConstante real agregada. >>> %s \n",aux->cadena);
                    //ImprimeTabla(*reales);

                    /*Se genera el token*/
                    token++;
                    printf("\nTOKEN %d: (%d,%d) \n",token,aux->clase,aux->valor);
                    fprintf(archSal,"TOKEN %d: (%d,%d)\n",token,aux->clase,aux->valor);

                    Componente* nuevoToken = CrearComponente();
                    nuevoToken->clase = 3;
                    nuevoToken->valor = real;
                    nuevoToken->tipo = linea;
                    strcpy(nuevoToken->cadena,yytext);
                    insertar(tokens,nuevoToken);

                    /* Añadimos átomo a la cadena*/
                    
                    concatena('r',str);
                }

{CADENA}        {   printf("\nCONSTANTE CADENA RECONOCIDA ===> %s",yytext);
                    cadenita++; //Posición nueva en la tabla
                    Componente* aux = CrearComponente();
                    aux->clase = 4;
                    aux->valor = cadenita;
                    strcpy(aux->cadena,yytext);

                    insertar(cadenas,aux);
                    printf("\nConstante cadena agregada. >>> %s \n",aux->cadena);
                    //ImprimeTabla(*cadenas);

                    token++;
                    printf("\nTOKEN %d: (%d,%d) \n",token,aux->clase,aux->valor);
                    fprintf(archSal,"TOKEN %d: (%d,%d)\n",token,aux->clase,aux->valor);

                    Componente* nuevoToken = CrearComponente();
                    nuevoToken->clase = 4;
                    nuevoToken->valor = cadenita;
                    nuevoToken->tipo = linea;
                    strcpy(nuevoToken->cadena,yytext);
                    insertar(tokens,nuevoToken);

                    /* Añadimos átomo a la cadena*/
                    
                    concatena('s',str);
                }

{ESPECIALES}    {   printf("\nSIMBOLO ESPECIAL RECONOCIDO ===> %s",yytext);
                    token++;
                    printf("\nTOKEN %d: (5,%s) \n",token,yytext);
                    fprintf(archSal,"TOKEN %d: (5,%s)\n",token,yytext);

                    Componente* nuevoToken = CrearComponente();
                    nuevoToken->clase = 5;
                    strcpy(nuevoToken->cadena,yytext); //Aquí el valor es la cadena
                    char especial = nuevoToken->cadena[0];
                    nuevoToken->valor = (int) especial;
                    nuevoToken->tipo = linea;
                    insertar(tokens,nuevoToken);

                    /* Añadimos átomo a la cadena*/
                    
                    if(strcmp(yytext,"[")==0){
                        concatena('[',str);
                    }else if(strcmp(yytext,"]")==0){
                        concatena(']',str);
                    }else if(strcmp(yytext,"(")==0){
                        concatena('(',str);
                    }else if(strcmp(yytext,")")==0){
                        concatena(')',str);
                    }else if(strcmp(yytext,"{")==0){
                        concatena('{',str);
                    }else if(strcmp(yytext,"}")==0){
                        concatena('}',str);
                    }else if(strcmp(yytext,",")==0){
                        concatena(',',str);
                    }else if(strcmp(yytext,":")==0){
                        concatena(':',str);
                    }else if(strcmp(yytext,";")==0){
                        concatena(';',str);
                    }else{
                        printf("Algo no salio bien en ESPECIALES");
                    }
                }

{OPARI}         {   printf("\nOPERADOR ARITMETICO RECONOCIDO ===> %s",yytext);
                    token++;
                    printf("\nTOKEN %d: (6,%s) \n",token,yytext);
                    fprintf(archSal,"TOKEN %d: (5,%s)\n",token,yytext);

                    Componente* nuevoToken = CrearComponente();
                    nuevoToken->clase = 6;
                    strcpy(nuevoToken->cadena,yytext); //Aquí el valor es la cadena
                    char especial = nuevoToken->cadena[0];
                    nuevoToken->valor = (int) especial;
                    nuevoToken->tipo = linea;
                    insertar(tokens,nuevoToken);

                    /* Añadimos átomo a la cadena*/
                    
                    if(strcmp(yytext,"+")==0){
                        concatena('+',str);
                    }else if(strcmp(yytext,"-")==0){
                        concatena('-',str);
                    }else if(strcmp(yytext,"*")==0){
                        concatena('*',str);
                    }else if(strcmp(yytext,"/")==0){
                        concatena('/',str);
                    }else if(strcmp(yytext,"%")==0){
                        concatena('%',str);
                    }else if(strcmp(yytext,"\\")==0){
                        concatena('\\',str);
                    }else if(strcmp(yytext,"^")==0){
                        concatena('^',str);
                    }else{
                        printf("Algo no salio bien en OPARI");
                    }
                }

{OPREL}         {   printf("\nOPERADOR RELACIONAL RECONOCIDO ===> %s",yytext);
                    //Recuperamos clase y valor...
                    Componente* comp = CrearComponente();
                    Nodo* aux = crearNodo(comp,NULL);
                    aux = buscar(*catalogoOR,yytext);
                    if(aux==NULL){
                        printf("Algo salio mal.");
                    }else{
                        /*Agregamos el token*/
                        token++;
                        printf("\nTOKEN %d: (%d,%d) \n",token,aux->info->clase,aux->info->valor);
                        fprintf(archSal,"TOKEN %d: (%d,%d)\n",token,aux->info->clase,aux->info->valor);
                        Componente* nuevoToken = CrearComponente();
                        nuevoToken->clase = aux->info->clase;
                        nuevoToken->valor = aux->info->valor;
                        nuevoToken->tipo = linea;
                        strcpy(nuevoToken->cadena,yytext);
                        insertar(tokens,nuevoToken);
                    }

                    /* Añadimos átomo a la cadena*/
                    
                    if(strcmp(yytext,"<")==0){
                        concatena('<',str);
                    }else if(strcmp(yytext,">")==0){
                        concatena('>',str);
                    }else if(strcmp(yytext,"<=")==0){
                        concatena('l',str);
                    }else if(strcmp(yytext,">=")==0){
                        concatena('u',str);
                    }else if(strcmp(yytext,"==")==0){
                        concatena('e',str);
                    }else if(strcmp(yytext,"!=")==0){
                        concatena('d',str);
                    }else{
                        printf("Algo no salio bien en OPREL");
                    }
                }

{ASIGNACION}    {   printf("\nOPERADOR DE ASIGNACION RECONOCIDO ===> %s",yytext);
                    /*Agregamos el token*/
                    token++;
                    printf("\nTOKEN %d: (8,=) \n",token);
                    fprintf(archSal,"TOKEN %d: (8,=)\n",token);

                    Componente* nuevoToken = CrearComponente();
                    nuevoToken->clase = 8;
                    nuevoToken->valor = 61;
                    nuevoToken->cadena = "=";
                    nuevoToken->tipo = linea;
                    insertar(tokens,nuevoToken);

                    /* Añadimos átomo a la cadena*/
                    
                    concatena('=',str);
                }

{LINEA}         {
                    printf("\nNUEVA LINEA");
                    linea++;
                }
%%



/* MAIN*/
int main(int argc, char *argv[]){
    yyin = fopen(argv[1],"r");
    archSal = fopen("salida.txt","w");

    system("clear");
    printf("BIENVENIDO!! \n\n");

    catalogoPR = crearTabla();
    printf("Creando catalogo de palabras reservadas...\n");
    int numPR = 17;
    char palabrasR[][12] = {
    "alternative",
    "big",
    "evaluate",
    "instead",
    "large",
    "loop",
    "make",
    "number",
    "other",
    "real",
    "repeat",
    "select",
    "small",
    "step",
    "stop",
    "symbol",
    "throw"
    };
    for(int i=0; i<numPR; i++){
        Componente* aux;
        aux = CrearComponente();
        aux->clase = 0;
        aux->valor = i;
        aux->cadena = palabrasR[i];

        insertar(catalogoPR,aux);
        printf("Palabra reservada agregada a la tabla!!! >>> %s \n",palabrasR[i]);
    }
    //ImprimeTabla(*catalogoPR);

    catalogoOR = crearTabla();
    printf("Creando catalogo de operadores relacionales...\n");
    int numOR = 6;
    char operadoresR[][3] = {
    "<",
    ">",
    "<=",
    ">=",
    "==",
    "!="
    };
    for(int i=0; i<numOR; i++){
        Componente* aux;
        aux = CrearComponente();
        aux->clase = 7;
        aux->valor = i;
        aux->cadena = operadoresR[i];

        insertar(catalogoOR,aux);
        printf("Operador relacional agregado a la tabla!!! >>> %s \n",operadoresR[i]);
    }
    //ImprimeTabla(*catalogoOR);

    /*do{
        printf("Presione 'Enter' para continuar... ");
    }while (getchar() != '\n');
    system("clear");*/

    identificadores = crearTabla();
    reales = crearTabla();
    cadenas = crearTabla();
    tokens = crearTabla();

    yylex();

    do{
        printf("Presione 'Enter' para imprimir las tablas finales... ");
    }while (getchar() != '\n');
    system("clear");


    printf("\n ====== CATALOGO DE PALABRAS RESERVADAS ======\n");
	printf("Clase	Valor	Cadena \n");
	fprintf(archSal,"\n ====== CATALOGO DE PALABRAS RESERVADAS ======\n");
	fprintf(archSal,"Clase	Valor	Cadena \n");
    ImprimeTabla(*catalogoPR,archSal);

    printf("=== CATALOGO DE OPERADORES RELACIONALES ===\n");
	printf("Clase	Valor	Cadena \n");
	fprintf(archSal,"=== CATALOGO DE OPERADORES RELACIONALES ===\n");
	fprintf(archSal,"Clase	Valor	Cadena \n");
    ImprimeTabla(*catalogoOR,archSal);

    printf("========== TABLA DE SIMBOLOS ==========\n");
	printf("Clase	Valor	Cadena \n");
	fprintf(archSal,"========== TABLA DE SIMBOLOS ==========\n");
	fprintf(archSal,"Clase	Valor	Cadena \n");
    ImprimeTabla(*identificadores,archSal);

    printf("======= TABLA DE LITERALES (REALES) =======\n");
	printf("Clase	Valor	Cadena \n");
	fprintf(archSal,"======= TABLA DE LITERALES (REALES) =======\n");
	fprintf(archSal,"Clase	Valor	Cadena \n");
    ImprimeTabla(*reales,archSal);

    printf("===== TABLA DE LITERALES (CADENAS) =====\n");
	printf("Clase	Valor	Cadena \n");
	fprintf(archSal,"===== TABLA DE LITERALES (CADENAS) =====\n");
	fprintf(archSal,"Clase	Valor	Cadena \n");
    ImprimeTabla(*cadenas,archSal);

    printf("=== LISTA DE TOKENS ===\n");
    ImprimeListaTokens(*tokens);

    printf("\nCadena de atomos generada: ");
    printf("%s",str);
    printf("\n\nTamanio de la cadena: %d\n",strlen(str));
    fprintf(archSal,"\nCadena de atomos generada: ");
    fprintf(archSal,"%s",str);
    fprintf(archSal,"\n\nTamanio de la cadena: %d\n",strlen(str));


    /*Comienza análisis sintáctico*/
    pasaInfo(str,tokens);
    parser();

    fclose(yyin);
    fclose(archSal);
    printf("\n\nFin de la ejecucion. \nRevise el archivo 'salida.txt' ");

    return 0;
}
