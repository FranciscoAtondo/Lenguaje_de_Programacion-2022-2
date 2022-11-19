#include <iostream>

#ifndef LETREC_H
#define LETREC_H

#define MAX 650
#define MAX_RES 23

using namespace std;

bool esNumero=true;
bool esIdentificador = true;

char tokenSimbolos[MAX];
char auxWord[MAX];	//Una variable auxiliar para guardar dos veces la palabra(token) que se vaya formando
string tokenNumeros[MAX];
string tokenIdentificadores[MAX];
string tokenReservadas[MAX];
string tokensNoValidos[MAX];

class letrec
{
    public:
        letrec();
        virtual ~letrec();

        bool verificarNumero(char palabra[]);
        /*
        *   Metodo para revisar si el token formado cumple para ser un numero entero o decimal.
        *   Aparte, aqui se guardan los tokens No Validos para mostrarlos en el metodo imprimirIdentificadoresNoValidos()
        */

        bool verificarIdentificador(char palabra[]);
        /*
        *   Metodo para verificar si el token formado cumple para ser un identificador.
        */

        bool verificarReservada(char palabra[]);
        /*
        *   Metodo para verificar si el token formado corresponde a una palabra reservada
        */

        void imprimirTokenNumeros();
        void imprimirTokenSimbolos();
        void imprimirTokenReservadas();
        void imprimirTokenIdentificadores();
        void imprimirIdentificadoresNoValidos();

    protected:

    private:
};

#endif // LETREC_H
