/*	AUTOMATAS Y LENGUAJES FORMALES SECCION C
*
* PROGRAMA HECHO POR: CRISTIAN LOPEZ
* ESTE PROGRAMA CONSISTE EN UN ANALIZADOR LEXICO: RECIBE UNA CADENA, PROGRAMA FUENTE, PARA REPARTIR CADA PALABRA EN TOKENS. LOS TOKENS PUEDEN SER IDENTIFICADORES, NUMEROS Y PALABRAS RESERVADAS
* Y VERIFICA QUE CADA TOKEN SEA VALIDO CONFORME A LAS REGLAS DE LA SINTAXIS:
*	 		-   TODO IDENTIFICADOR DEBE EMPEZAR CON UN '_' O UNA LETRA.
*			-	 TODO IDENTIFICADOR DEBE ESTAR FORMADO POR DIGITOS, LETRAS O '_' NO OTROS CARACTERES FUERA DE ESTOS.
*			-   NINGUN NUMERO, YA SEA DECIMAL O ENTERO, PUEDE EMPEZAR CON UN '.' O TERMINAR CON UN '.'
* 			-	 NINGUN NUMERO PUEDE CONTENER UNA LETRA
* DEL USUARIO LE CORRESPONDE INGRESAR UNA LINEA DE PROGRAMA FUENTE CON VARIAS PALABRAS, ENTRE ELLAS INGRESE LAS PALABRAS RESERVADAS(EN MINUSCULAS), PARA PONER A PRUEBA ESTE ANALIZADOR.
* ES IMPORTANTE QUE EL USUARIO SIEMPRE DEJE UN ESPACIO ENTRE LOS BUCLES, CONDICIONALES Y SUS PARENTESIS. VER MANUAL DE USUARIO. 
*/

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <string>
#include <iostream>
#define MAX 650
#define MAX_RES 23

using namespace std;

char *PalabrasReservadas[MAX_RES] = {"si","entonces","sino","entero","decimal","logico","texto","char","mientras","haga","repita",
"hasta","var","como","verdadero","falso","declare","inicie","termine","lea","imprima","rompa","nop"};
char tokenSimbolos[MAX];
char auxWord[MAX];	//Una variable auxiliar para guardar dos veces la palabra(token) que se vaya formando
string tokenNumeros[MAX];
string tokenIdentificadores[MAX];
string tokenReservadas[MAX];
string tokensNoValidos[MAX];
bool esNumero=true;
bool esIdentificador = true;

//Variables auxiliares para guardar en Tokens
int auxTR=0;
int auxTI=0;
int auxTN=0;
int auxTNV=0;

//Los diferentes procedimientos que se desarrollaran en el programa y llamaran en su momento desde el metodo main()
bool verificarNumero(char palabra[]);
bool verificarIdentificador(char palabra[]);
bool verificarReservada(char palabra[]);
void imprimirTokenNumeros();
void imprimirTokenSimbolos();
void imprimirTokenReservadas();
void imprimirTokenIdentificadores();
void imprimirIdentificadoresNoValidos();

main()
{
	system("COLOR 0A");
	unsigned char entrada[MAX];
   char *p = entrada;
   printf("Ingrese la primera linea del lenguaje: ");
   fflush(stdin);
   gets(entrada);
	fflush(stdin);
   clrscr();
   system("COLOR 0B");

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

// Metodo para verificar si el token formado corresponde a una palabra reservada
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

// Metodo para verificar si el token formado cumple para ser un identificador
bool verificarIdentificador(char palabra[]){
	string auxPalabra = palabra;
   esIdentificador = false;
   short estado = 0;
   char *p = palabra;
   while(*p != '\0')
   {
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

//Metodo para revisar si el token formado cumple para ser un numero entero o decimal. Aparte, aqui se guardan los tokens No Validos para mostrarlos en el metodo imprimirIdentificadoresNoValidos()
bool verificarNumero(char palabra[]){
	string auxPalabra = palabra;
   esNumero = false;
	short estado = 0,cont=0;
   char *p = palabra;
	while(*p!='\0')
   {
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
