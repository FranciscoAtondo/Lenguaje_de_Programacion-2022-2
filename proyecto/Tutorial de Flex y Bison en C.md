# Tutorial Flex-Bison en C
## Introduccion
Flex y Bison son herramientras usadas para la creacion de programas orientadas al manejo de entrada de estructuras. Flex genera analizadores lexicos con los cuales busca tokens en expresiones regulares y los compara con un Fichero de Entrada para realizar tareas relacionadas a estas. Bison por otro lado es un generador de Analizadores Sintacticos de uso general que indica si el Fichero de Entrada dado pertenece al lenguaje generado por su gramatica.

```
/* just like Unix wc */
%{
int chars = 0;
int words = 0;
int lines = 0;
%}
%%
[a-zA-Z]+ { words++; chars += strlen(yytext); }
\n { chars++; lines++; }
. { chars++; }
%%
main(int argc, char **argv)
{
yylex();
printf("%8d%8d%8d\n", lines, words, chars);
}
```
<em>Ejemplo de un programa Flex en C que cuenta palabras y las categoriza por lineas, palabras y caracteres</em>

Un programa Flex esta compuesto por 3 secciones: Declaracion y Configuracion de Opciones, Lista de Patrones y Acciones y Codigo. Estas se dividen por lineas "%%". En el ejemplo de arriba, la seccion de Declaraciones prepara 3 valores a usar en el contador, en la seccion de Patrones y Acciones se encuentran al inicio de la linea y se encuentran en sincronia con el codigo C para ser ejecutados cuando se encuentre un patron. En este caso, solo hay 3 patrones a reconocer: cualquier string de letras entre el grupo declarado [a-zA-Z]+, osea cualquier letra del abecedario, ya sea Minuscula o Mayuscula, "\n" osea las declaraciones de nueva linea y un punto(.), osea una expresion regular para cualquier caracter.

Bison se maneja de forma similar, pues tambien separa sus secciones con lineas de "%%", sin embargo estas se declaran en 4 secciones distintas:
```
%{
Declaracion y Configuracion de Opciones
%}
Declaraciones de Bison
%%
Reglas Gramaticales
%%
Codigo
```

Las secciones de Declaracion y Configuracion de Opciones y el Codigo son identicos a un programa Flex, sin embargo las Declaraciones de Bison definen los nombres de simbolos terminales y no terminales, asi como la descripcion de presedencia u orden de operadores y los tipos de datos de los valores semanticos dados y las Reglas Gramaticales son las producciones de la dramatica, las cuales pueden llevar asociadas acciones de acuerdo a lo que encuentre el analizador.

## Flex
Primero se vera mas de cerca como funciona Flex como una herramienta propia con varios ejemplos.

# Expresiones Regulares
