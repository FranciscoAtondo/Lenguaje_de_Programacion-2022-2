/*
    Nombre: Analizador Letrec
    Autor: Francisco Javier Atondo Nubes
    Descripcion: Analizador Lexico para lenguaje Letrec.

    Instrucciones: Escriba una cadena de caracteres basado en un coman
*/


/* Buscar biblioteca(?)
1 - Leer archivo para leer los tokes
2 - Analizador Lexico
3 - Analizador Sintactico
4 - Semantica
5 -
*/
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <letrec.h>


using namespace std;







//Los diferentes procedimientos que se desarrollaran en el programa y llamaran en su momento desde el metodo main()


int main()
{
    //system("COLOR 0A");
    char entrada[MAX];
   char *p = entrada;
   printf("Ingrese la primera linea del lenguaje: ");
   fflush(stdin);
   gets(entrada);
	fflush(stdin);
   //clrscr();
   //system("COLOR 0B");

	char palabra[MAX]; //Esta variable es muy importante, pues guardara caracter por caracter formando asi una palabra y termina de guardar cuando detecta un espacio.
   int indexPalabra=0;
   int indexSimbolos = 0;

   //Ciclos para Iniciar diferentes arreglos.
   for(int i=0;i<MAX;i++){tokenReservadas[i] = "";} // Fin del ciclo

   for(int i=0;i<MAX;i++){tokensNoValidos[i] = "";}

   for(int i=0;i<MAX;i++){
		palabra[i] = '\0';
   }

   //Este bucle es el que recorre cada caracter de la entrada(programa fuente) que ingreso el usuario, el procedimiento dentro del bucle es para formar los tokens necesarios.
   while(*p!='\0')
   {
		if((*p != ' ') && (*p !=','))  	//Primero revisa que sea distinto de un espacio ' ' y una coma ','
      {
      	if((*p== ';') || (*p=='"') || (*p=='(') || (*p==')') || (*p=='+') || (*p=='-') || (*p=='*') || (*p=='/') || (*p=='#') || (*p=='<') || (*p=='>') || (*p=='='))
	      {
      	   tokenSimbolos[indexSimbolos] = *p;
         	indexSimbolos++;
	      }
         else
         {
				palabra[indexPalabra] = *p;
            auxWord[indexPalabra] = *p;	//La razon de usar este arreglo es para mandar como parametro al metodo verificarNumero()... debido a un problema de programacion.
            indexPalabra++;
         }
      }
      else if((*p ==' ') || (*p ==','))
      {
      	// Guarda la palabra en los respectivos tokens segun las funciones hayan examinado la palabra.
         if(verificarReservada(palabra) == true){
				tokenReservadas[auxTR] = palabra;
          	auxTR++;
         }else if(verificarIdentificador(palabra) == true){
         	tokenIdentificadores[auxTI] = palabra;
		      auxTI++;
         }else if(verificarNumero(auxWord)==true){
         	tokenNumeros[auxTN] = auxWord;
		      auxTN++;
         }
         for(int i=0;i<MAX;i++){palabra[i]='\0';}	//Para vaciar el arreglo de la palabra
         for(int i=0;i<MAX;i++){auxWord[i]='\0';}	//Para vaciar el arreglo del arreglo auxiliar
         indexPalabra=0;
      }
      p++;
   }

   //Esto es para revisar la ultima palabra formada que no se pudo examinar en el bucle while anterior
	if(verificarReservada(palabra) == true){
   	tokenReservadas[auxTR] = palabra;
    	auxTR++;
   }else if(verificarIdentificador(palabra) == true){
		tokenIdentificadores[auxTI] = palabra;
		auxTI++;
   }else if(verificarNumero(auxWord)==true){
    	tokenNumeros[auxTN] = auxWord;
      auxTN++;
   }

   //FINALMENTE SE LLAMAN A IMPRIMIR LOS RESULTADOS OBTENIDOS.
   printf("\t\tEXPRESION: %s\n",entrada);
   imprimirTokenReservadas();
   imprimirTokenSimbolos();
   imprimirTokenIdentificadores();
   imprimirTokenNumeros();
   imprimirIdentificadoresNoValidos();
    getch();
}
