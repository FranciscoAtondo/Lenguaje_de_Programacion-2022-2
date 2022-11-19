#include "letrec.h"
#include <iostream>
#include <string>
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>

using namespace std;

letrec::letrec()
{
    //ctor
}

letrec::~letrec()
{
    //dtor
}





//Variables auxiliares para guardar en Tokens
int auxTR=0;
int auxTI=0;
int auxTN=0;
int auxTNV=0;

char *PalabrasReservadas[MAX_RES] = {"if","then","else","let","in","proc","letrec"};

bool verificarNumero(char palabra[]){
	string auxPalabra = palabra;
    esNumero = false;
	short estado = 0, cont=0;
    char *p = palabra;
    while(*p!='\0')
    {
        //Lee el token ingresado. Si la primera letra es un numero se cumple el caso 0 y regresa como verdadero. Si es un punto, verificara en el caso 1.
        switch(estado)
        {
        case 0:
            if(isdigit(*p)){
					estado = 0;
               esNumero = true;
               cont++;
            }
            else if( ((*p == '.') && (cont==0)) || (isalpha(*p))){
					estado = 2;
               esNumero=false;
            }else if(*p=='.'){
					estado = 1;
            	esNumero = false;
            }
         	p++;
         break;
         case 1:
            if(isdigit(*p)){
            	estado = 1;
               esNumero = true;
            }else
            {
            	estado = 2;
               esNumero = false;
            }
         	p++;
         break;
         case 2:
				esNumero = false;
         	*p = '\0';
         break;
        }
   }

   if(esNumero == false){
      if(auxPalabra != ""){
   	   tokensNoValidos[auxTNV] = auxPalabra;
	      auxTNV++;
      }
   }
 	return esNumero;
}

//
bool verificarIdentificador(char palabra[]){
    string auxPalabra = palabra;
    esIdentificador = false;
    short estado = 0;
    char *p = palabra;
    while(*p != '\0')
    {
        //Lee el token ingresado. Si la primera letra es un espacio, se cumple el caso 1 y verifica ahi si le sigue una letra. Si es un numero, va al caso 2.
        switch(estado)
        {
        case 0:
         	if((isalpha(*p)) || (*p=='_')){
            	estado = 1;
               esIdentificador = true;
            }
            else{
            	estado = 2;
               esIdentificador = false;
            }
            p++;
         break;
         case 1:
         	if((isalpha(*p)) || (isdigit(*p)) || (*p=='_')){
            	estado = 1;
               esIdentificador = true;
            }
            else{
            	estado = 2;
               esIdentificador = false;
            }
            p++;
         break;
         case 2:
				//No es un identificador
            esIdentificador = false;
            *p = '\0';
         break;
      }
   }
   return esIdentificador;
}

bool verificarReservada(char palabra[]){
    int comp;
   bool esReservada=false;
   string str(palabra);
	for(int i=0; i<MAX_RES; i++)
   {
   	comp = strcmp(PalabrasReservadas[i],palabra);
      if(comp == 0)
      {
         esReservada = true;
         break;
      }
   }
   return esReservada;
}

//Inicio del desarrollo de los metodos para imprimir los resultados.

void imprimirTokenSimbolos(){
	puts("\n\n----------------\n|TOKENS SIMBOLOS|\n----------------");
	for(int i=0;i<strlen(tokenSimbolos);i++){printf("%c\n",tokenSimbolos[i]);}
}

void imprimirTokenReservadas(){
	puts("\n-----------------------\n|TOKENS Reservadas|\n-----------------------");
	for(int i=0;i<auxTR;i++){printf("%d %s\n",i+1,tokenReservadas[i]);}
}

void imprimirTokenIdentificadores(){
	puts("\n-----------------------\n|TOKENS IDENTIFICADORES|\n-----------------------");
	for(int i=0;i<auxTI;i++){printf("%d %s\n",i+1,tokenIdentificadores[i]);}
}

void imprimirTokenNumeros(){
	puts("\n-----------------------\n|TOKENS NUMEROS|\n-----------------------");
	for(int i=0;i<auxTN;i++){printf("%d %s\n",i+1,tokenNumeros[i]);}
}

void imprimirIdentificadoresNoValidos(){
	puts(" ");
	printf("********************************* MENSAJES *********************************\n");
   if(auxTNV == 0){
   	printf("\t\t 0 Errores, programa fuente exitoso...");
   }else{
   	for(int i=0;i<auxTNV;i++)
	   {
   		printf("\t\tERROR: No es Valido el Token: %s \n",tokensNoValidos[i]);
   	}
   }
}

//Fin del desarrollo de metodos para imprimir
