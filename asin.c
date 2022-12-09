/*
UNIVERSIDAD NACIONAL AUTÓNOMA DE MÉXICO
Facultad de Ingeniería
Compiladores  -  Grupo 03
Semestre 2023-1
Profesora: Laura Sandoval
Por: Zuriel Zárate García
Fecha: 08 de noviembre de 2022

Descripción: Funciones correspondientes para realizar el 
Análisis Sintáctico Descendente Recursivo que revisa programas 
escritos en el lenguaje definido por la gramática del Anexo A del
documento 'ProgAnalizadorSintactico2023-1.pdf'.
*/

#include "tablas.h"
#include "asin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int numAtomo=-1;
char atomo='x';

Nodo* aux;
int numLinea = 0;
char cadEsperada[100]="";

char cadAt[10000]="";
char* apStr;
Tabla* listAtom;
//char deriva[1000]="";
int errores=0;

void pasaInfo(char* alex, Tabla* atomos){
    strcpy(cadAt,alex);
    apStr = cadAt-1; //Se posiciona un elemento antes de la cadena
    listAtom = atomos; //Se obtiene la referencia de la lista de atomos
}

void concatena(char atomo, char* cadena){
    char nuevo[2];
    nuevo[0] = atomo;
    nuevo[1] = '\0';
    strcat(cadena,nuevo);
    printf("CADENA DE ATOMOS ACTUAL: %s \n",cadena);
}

void sigAtomo(){
    apStr++;
    atomo = *apStr;
    numAtomo++;
}

void rechaza(){
    errores++;
    //printf("\n\nCadena: %s",apStr);
    printf("\nSyntax Error ");
}

void acepta(){
    printf("\nCadena aceptada!\n");
}

void parser(){
    sigAtomo();
    Program();
    if(atomo=='\0' && errores==0){
        acepta();
        printf("Intento terminado. Numero de errores: %d",errores);
    }else{
        printf("\n\nIntento terminado. Numero de errores: %d",errores);
    }
}

void Program(){
    //strcat(deriva,"->Program");
    if(atomo=='b'||atomo=='g'||atomo=='#'||atomo=='y'||atomo=='x'){
        Func();
        otraFunc();
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba un tipo de dato pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void otraFunc(){
    //strcat(deriva,"->otraFunc");
    if(atomo=='b'||atomo=='g'||atomo=='#'||atomo=='y'||atomo=='x'){
        Func();
        otraFunc();
        return;
    }else if(atomo=='\0'){
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba un tipo de dato o fin de cadena pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void Func(){
    //strcat(deriva,"->Func");
    if(atomo=='b'||atomo=='g'||atomo=='#'||atomo=='y'||atomo=='x'){
        Tipo();
        if(atomo=='i'){
            
            sigAtomo();
   //Lee caracter
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '$<nombre_identificador>' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        if(atomo=='('){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '(' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        Param();
        if(atomo==')'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ')' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        if(atomo=='{'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '{' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        Cuerpo();
        if(atomo=='}'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '}' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba un tipo de dato pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void Param(){
    //strcat(deriva,"->Param");
    if(atomo=='b'||atomo=='g'||atomo=='#'||atomo=='y'||atomo=='x'){
        Tipo();
        if(atomo=='i'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '$<nombre_identificador>' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        otroParam();
        return;
    }else if(atomo==')'){
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba un tipo de dato o ')' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    } 
}

void otroParam(){
    //strcat(deriva,"->otroParam");
    if(atomo==','){
        
        sigAtomo();
        Tipo();
        if(atomo=='i'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '$<nombre_identificador>' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        otroParam();
        return;
    }
    else if(atomo==')'){
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba ',' o ')' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    } 
}

void Cuerpo(){
    //strcat(deriva,"->Cuerpo");
    if(atomo=='b'||atomo=='g'||atomo=='#'||atomo=='y'||atomo=='x'||atomo=='i'||atomo=='f'||atomo=='h'||atomo=='w'||atomo=='j'||atomo=='['||atomo=='z'||atomo=='c'||atomo=='}'){
        Decl();
        listaP();
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '}', '[', un tipo de dato, '$<nombre_identificador>' o una estructura de control pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void Decl(){
    //strcat(deriva,"->Decl");
    if(atomo=='i'||atomo=='}'||atomo=='c'||atomo=='w'||atomo=='f'||atomo=='j'||atomo=='h'||atomo=='z'||atomo=='['){
        return;
    }else if(atomo=='b'||atomo=='g'||atomo=='#'||atomo=='y'||atomo=='x'){
        D();
        Decl();
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '}', '[', un tipo de dato, '$<nombre_identificador>' o una estructura de control pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void D(){
    //strcat(deriva,"->D");
    if(atomo=='b'||atomo=='g'||atomo=='#'||atomo=='y'||atomo=='x'){
        Tipo();
        K();
        if(atomo == ';'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ';' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba un tipo de dato pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void Tipo(){
    //strcat(deriva,"->Tipo");
    if(atomo=='b'||atomo=='g'||atomo=='#'||atomo=='y'||atomo=='x'){
        
        sigAtomo();
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba un tipo de dato pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void K(){
    //strcat(deriva,"->K");
    if(atomo=='i'){
        
        sigAtomo();
        Q();
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '$<nombre_identificador>' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void Q(){
    //strcat(deriva,"->Q");
    if(atomo==';'){
        return;
    }else if(atomo=='n'||atomo=='r'||atomo=='s'){
        
        sigAtomo();
        return;
    }else if(atomo==','){
        
        sigAtomo();
        K();
        return;
    }else if(atomo=='='){
        
        sigAtomo();
        N();
        C();
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba ';', ',', '=' o una constante pero se obtuvo '%s'",numLinea,cadEsperada);
        printf("\nCadena: %s \n\n",apStr);
        return;
    }
}

void N(){
    //strcat(deriva,"->N");
    if(atomo=='n'||atomo=='r'||atomo=='s'){
        
        sigAtomo();
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba una constante pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void C(){
    //strcat(deriva,"->C");
    if(atomo==';'){
        return;
    }else if(atomo==','){
        
        sigAtomo();
        K();
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba ';' o ',' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void A(){
    //strcat(deriva,"->A");
    if(atomo=='i'){
        
        sigAtomo();
        if(atomo=='='){
            
            sigAtomo();
   
        }
        else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '=' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        AP();
        if(atomo==';'){
            
            sigAtomo();
   
        }
        else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ';' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '$<nombre_identificador>' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void AP(){
    //strcat(deriva,"->AP");
    if(atomo=='s'){
        
        sigAtomo();
        return;
    }
    else if(atomo=='('||atomo=='i'||atomo=='n'||atomo=='r'||atomo=='['){
        E();
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '(','[','$<nombre_identificador>' o una constante pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void E(){
    //strcat(deriva,"->E");
    if(atomo=='('||atomo=='i'||atomo=='n'||atomo=='r'||atomo=='['){
        T();
        EP();
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '(','[','$<nombre_identificador>' o una constante numerica pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void EP(){
    //strcat(deriva,"->EP");
    if(atomo=='+'||atomo=='-'){
        
        sigAtomo();
        T();
        EP();
        return;
    }
    else if(atomo==';'||atomo==')'){
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba ';', ')', '+' o '-' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void T(){
    //strcat(deriva,"->T");
    if(atomo=='('||atomo=='i'||atomo=='n'||atomo=='r'||atomo=='['){
        F();
        TP();
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '(','[','$<nombre_identificador>' o una constante numerica pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void TP(){
    //strcat(deriva,"->TP");
    if(atomo=='*'||atomo=='/'||atomo=='\\'||atomo=='%'||atomo=='^'){
        
        sigAtomo();
        F();
        TP();
        return;
    }
    else if(atomo=='+'||atomo=='-'||atomo==';'||atomo==')'){
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba un operador aritmetico, ';' o ')' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void F(){
    //strcat(deriva,"->F");
    if(atomo=='('){
        
        sigAtomo();
        E();
        if(atomo==')'){
            
            sigAtomo();
        }
        else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ')' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        return;
    }
    else if(atomo=='i'||atomo=='n'||atomo=='r'){
        
        sigAtomo();
        return;
    }
    else if(atomo=='['){
        Llama();
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '(','[','$<nombre_identificador>' o una constante numerica pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void R(){
    //strcat(deriva,"->R");
    if(atomo=='i'){
        
        sigAtomo();
        RP();
        V();
        return;
    }
    else if(atomo=='n'){
        
        sigAtomo();
        RP();
        VP();
        return;
    }
    else if(atomo=='r'){
        
        sigAtomo();
        RP();
        VPP();
        return;
    }
    else if(atomo=='s'){
        
        sigAtomo();
        RP();
        VPPP();
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '$<nombre_identificador>' o una constante pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void RP(){
    //strcat(deriva,"->RP");
    if(atomo=='>'||atomo=='<'||atomo=='l'||atomo=='e'||atomo=='d'||atomo=='u'){
        
        sigAtomo();
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba un operador relacional pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void V(){
    //strcat(deriva,"->V");
    if(atomo=='i'||atomo=='n'||atomo=='r'||atomo=='s'){
        
        sigAtomo();
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '$<nombre_identificador>' o una constante pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void VP(){
    //strcat(deriva,"->VP");
    if(atomo=='i'||atomo=='n'){
        
        sigAtomo();
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '$<nombre_identificador>' o una constante entera pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void VPP(){
    //strcat(deriva,"->VPP");
    if(atomo=='r'||atomo=='i'){
        
        sigAtomo();
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '$<nombre_identificador>' o una constante real pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void VPPP(){
    //strcat(deriva,"->VPPP");
    if(atomo=='s'||atomo=='i'){
        
        sigAtomo();
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '$<nombre_identificador>' o una constante cadena pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void P(){
    //strcat(deriva,"->P");
    if(atomo=='i'){
        A();
        return;
    }else if(atomo=='f'){
        I();
        return;
    }else if(atomo=='h'){
        H();
        return;
    }else if(atomo=='w'){
        W();
        return;
    }else if(atomo=='j'){
        J();
        return;
    }else if(atomo=='['){
        Llama();
        return;
    }else if(atomo=='z'){
        Devuelve();
        return;
    }else if(atomo=='c'){
        
        sigAtomo();
        if(atomo==';'){
            
            sigAtomo();
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ';' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '$<nombre_identificador>', '[' o una estructura de control pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void listaP(){
    //strcat(deriva,"->listaP");
    if(atomo=='q'||atomo=='t'||atomo=='a'||atomo==':'||atomo=='}'){
        return;
    }else if(atomo=='i'||atomo=='f'||atomo=='h'||atomo=='w'||atomo=='j'||atomo=='['||atomo=='z'||atomo=='c'){
        P();
        listaP();
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '$<nombre_identificador>', '[', '}' o una estructura de control pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void W(){
    //strcat(deriva,"->W");
    if(atomo=='w'){
        
        sigAtomo();
        if(atomo=='('){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '(' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        R();
        if(atomo==')'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ')' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        if(atomo=='m'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba 'make' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        if(atomo=='{'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '{' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        listaP();
        if(atomo=='}'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '}' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba 'loop' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void I(){
    //strcat(deriva,"->W");
    if(atomo=='f'){
        
        sigAtomo();
        if(atomo=='('){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '(' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        R();
        if(atomo==')'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ')' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        listaP();
        IP();
        if(atomo==':'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ':' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        return;
    }else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba 'evaluate' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void IP(){
    //strcat(deriva,"->IP");
    if(atomo=='t'){
        
        sigAtomo();
        listaP();
        return;
    }
    else if(atomo==':'){
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba 'instead' o ':' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void J(){
    //strcat(deriva,"->J");
    if(atomo=='j'){
        
        sigAtomo();
        if(atomo=='('){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '(' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        Y();
        X();
        Z();
        if(atomo=='{'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '{' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        listaP();
        if(atomo=='}'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '}' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba 'repeat' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void Y(){
    //strcat(deriva,"->Y");
    if(atomo=='i'){
        
        sigAtomo();
        if(atomo=='='){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '=' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        E();
        if(atomo==';'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ';' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        return;
    }
    else if(atomo==';'){
        
        sigAtomo();
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba ';' o '$<nombre_identificador>' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void X(){
    //strcat(deriva,"->X");
    if(atomo=='i'||atomo=='n'||atomo=='r'||atomo=='s'){
        R();
        if(atomo==';'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ';' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        return;
    }
    else if(atomo==';'){
        
        sigAtomo();
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba ';', '$<nombre_identificador>' o una constante pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void Z(){
    //strcat(deriva,"->Z");
    if(atomo=='i'){
        
        sigAtomo();
        if(atomo=='='){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '=' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        E();
        if(atomo==')'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ')' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        return;
    }
    else if(atomo==')'){
        
        sigAtomo();
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba ')' o <$nombre_identificador> pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void H(){
    //strcat(deriva,"->H");
    if(atomo=='h'){
        
        sigAtomo();
        if(atomo=='('){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '(' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        if(atomo=='i'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '$<nombre_identificador>' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        if(atomo==')'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ')' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        if(atomo=='{'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '{' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        CP();
        OP();
        if(atomo=='}'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '}' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }

        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba 'select' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void CP(){
    //strcat(deriva,"->CP");
    if(atomo=='a'){
        
        sigAtomo();
        if(atomo=='n'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba una constante entera pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        if(atomo==':'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ':' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        listaP();
        U();
        CP();
        return;
    }
    else if(atomo=='o'||atomo=='}'){
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '}', 'alternative' o 'other'  pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void OP(){
    //strcat(deriva,"->OP");
    if(atomo=='o'){
        
        sigAtomo();
        if(atomo==':'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ':' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        listaP();
        return;
    }
    else if(atomo=='}'){
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '}' o 'other' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void U(){
    //strcat(deriva,"->U");
    if(atomo=='q'){
        
        sigAtomo();
        return;
    }
    else if(atomo=='a'||atomo=='o'||atomo=='}'){
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '}', 'stop', 'alternative' o 'other' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void Devuelve(){
    //strcat(deriva,"->Devuelve");
    if(atomo=='z'){
        
        sigAtomo();
        if(atomo=='('){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '(' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        valor();
        if(atomo==')'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ')' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        if(atomo==';'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ';' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba 'throw' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void valor(){
    //strcat(deriva,"->valor");
    if(atomo=='i'||atomo=='n'||atomo=='r'||atomo=='s'){
        V();
        return;
    }
    else if(atomo==')'){
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba ')', '$<nombre_identificador>' o una constante pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void Llama(){
    //strcat(deriva,"->Llama");
    if(atomo=='['){
        
        sigAtomo();
        if(atomo=='i'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '$<nombre_identificador>' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        if(atomo=='('){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba '(' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        arg();
        if(atomo==')'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ')' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        if(atomo==']'){
            
            sigAtomo();
   
        }else{
            aux = buscarToken(*listAtom,numAtomo);
            strcpy(cadEsperada,aux->info->cadena);
            numLinea = aux->info->tipo; 
            rechaza();
            printf("(Linea %d): Se esperaba ']' pero se obtuvo '%s'",numLinea,cadEsperada);
            return;
        }
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba '[' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void arg(){
    //strcat(deriva,"->arg");
    if(atomo==')'){
        return;
    }
    else if(atomo=='i'||atomo=='n'||atomo=='r'||atomo=='s'){
        V();
        otroArg();
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba ')', '$<nombre_identificador>' o una constante pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}

void otroArg(){
    //strcat(deriva,"->otroArg");
    if(atomo==','){
        
        sigAtomo();
        V();
        otroArg();
        return;        
    }
    else if(atomo==')'){
        return;
    }
    else{
        aux = buscarToken(*listAtom,numAtomo);
        strcpy(cadEsperada,aux->info->cadena);
        numLinea = aux->info->tipo; 
        rechaza();
        printf("(Linea %d): Se esperaba ',' o ')' pero se obtuvo '%s'",numLinea,cadEsperada);
        return;
    }
}