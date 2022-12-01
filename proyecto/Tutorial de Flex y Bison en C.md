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
\n        { chars++; lines++; }
.         { chars++; }
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

## Instalacion
Antes de entrar a detalles en cuanto a ambas herramientras, primero hay que explicar como se instalan. Cabe mencionar que este tutorial esta pensado para un Sistema Operativo Windows. Tambien se usara CodeBlocks como nuestro ambiente de trabajo: https://www.codeblocks.org/downloads/binaries/

### Flex
1 - Descargue el instalador Setup de Flex de la siguiente direccion: https://gnuwin32.sourceforge.net/packages/flex.htm

2 - Ejecute "flex-x.x.x.exe" siguiendo las instrucciones.

3 - Dirijase a la carpeta donde instalo GnuWin32 y copie la direccion de la carpeta bin en las Variables de Entorno->Variables de Sistema->PATH

4 - Asegurese de que la direccion de GnuWin32 este debajo de la direccion de Codeblocks/MinGW/bin

### Bison
1 - Descargue el instalador Setup de Bison de la siguiente direccion: http://gnuwin32.sourceforge.net/packages/bison.htm

2 - Ejecute "bison-x.x.x-setup.exe" siguiendo las instrucciones, pero elija otra carpeta fuera de la default

3 - Dirijase a la carpeta donde instalo GnuWin32 y copie la direccion de la carpeta bin en las Variables de Entorno->Variables de Sistema->PATH

4 - Asegurese de que la direccion de GnuWin32 este debajo de la direccion de Codeblocks/MinGW/bin

Para verificar que ambas se hayan instalado correctamente, abra una ventana de comandos(Windows+R y escriba cmd) y escriba "flex --version" y "bison --version". Si fueron instalados correctamente se mostrara un mensaje con la version actual de cada uno de los programas.

## Flex
Primero se vera mas de cerca como funciona Flex como una herramienta propia con varios ejemplos.

### Expresiones Regulares
Estas son combinaciones de caracteres, por ejemplo para definir todo numero Fortran que puede ser decimal, esta se escribre asi:

[-+]?[0-9]+

Donde [-+] significa que el valor dado puede ser tanto positivo o negativo, ? que puede ser un punto decimal, [0-9] que significa todo numero de 0 a 9 y '+' dice que puede ser uno o mas valores. Sin embargo esta expresion esta erronea, pues esta puede aceptar un valor como '1.2.3.4', pero esto se puede arreglar expandiendo un poco la Expresion y usando el operador '|', el cual permite la combinacion de dos versiones:

[-+]?([0-9]*\.?[0-9]+|[0-9]+\.)

Sin embargo esto es internamente ambiguo, pues hay muchos hilos que concuerdan con cualquiera de las alternativas, pero Flex permite dos patrones coincidir con la misma entrada usando el exponente opcional 'E':

E(+|-)?[0-9]+

[-+]?([0-9]*\.?[0-9]+|[0-9]+\.)(E(+|-)?[0-9]+)?

### Tokens Dependientes de Contexto
Normalmente, escanear es algo dependiente de contexto, como por ejemplo, en Pascal, 1. es usualmente un numero punto-flotante, pero en una declaracion 1..2 son dos integrantes separados por un token '..'. Flex provee estados de inicio, los cuales pueden convertir patrones dinamicamente y son generalmente suficientes para manejar tales dependencias.

### File I/O en Escaners de Flex
Un escaner Flex leera de una entrada estandar almenos de que se le indique de otra forma. Esto se demostrara con una modificacion del ejemplo anterior:

```
%option noyywrap
%{
int chars = 0;
int words = 0;
int lines = 0;
%}

%%

[a-zA-Z]+ { words++; chars += strlen(yytext); }
\n        { chars++; lines++; }
.         { chars++; }

%%

main(argc, argv)
int argc;
char **argv;
{
  if(argc > 1) {
    if(!(yyin = fopen(argv[1], "r"))) {
      perror(argv[1]);
      return (1);
    }
  }
  yylex();
  printf("%8d%8d%8d\n", lines, words, chars);
}
```

La unica diferencia que tiene esta version es que ahora abre un archivo segun la linea de comando, asignandolo a yyin para que yylex lo asigne automaticante a la entrada estandar.

### Inicializar Estados y Archivos de Entrada Anidados
Ahora probaremos nuestro conocimiento de Flex I/O con un simple programa que maneja archivos anidados y los imprime señalando el numero de linea en los archivos. Para ello, el programa mantiene una pila de Archivos de Entrada Anidados y el numero de lineas, empujando una entrada cada vez que encuentra un '#include':

```
%option noyywrap
%x IFILE
%{
struct bufstack {
  struct bufstack *prev; /* previous entry */
  YY_BUFFER_STATE bs; /* saved buffer */
  int lineno; /* saved line number */
  char *filename; /* name of this file */
  FILE *f; /* current file */
} *curbs = 0;

char *curfilename; /* name of current input file */
int newfile(char *fn);
int popfile(void);
%}

%%
/* match #include statement up through the quote or <
^"#"[ \t]*include[ \t]*\[\"<] { BEGIN IFILE; } */
<IFILE>[^ \t\n\">]+ {
{ 
  int c;
  while((c = input()) && c != '\n') ;
}

yylineno++;
if(!newfile(yytext))
yyterminate(); /* no such file */
BEGIN INITIAL;
}

handle bad input in IFILE state
<IFILE>.|\n { 
  fprintf(stderr, "%4d bad include line\n", yylineno);
  yyterminate();
}

// pop the file stack at end of file, terminate if it's the outermost file
<<EOF>> {if(!popfile()) yyterminate(); }

/*print the line number at the beginning of each line
and bump the line number each time a \n is read*/

^. { fprintf(yyout, "%4d %s", yylineno, yytext); }
^\n { fprintf(yyout, "%4d %s", yylineno++, yytext); }
\n { ECHO; yylineno++; }
. { ECHO; }

%%

// Main
main(int argc, char **argv)
{
  if(argc < 2) {
    fprintf(stderr, "need filename\n");
    return 1;
  }
  if(newfile(argv[1])) yylex();
}

// Inicializa un nuevo Archivo
int newfile(char *fn)
{
  FILE *f = fopen(fn, "r");
  struct bufstack *bs = malloc(sizeof(struct bufstack));
  
  /* die if no file or no room */
  if(!f) { perror(fn); return 0; }
  if(!bs) { perror("malloc"); exit(1); }
  
  /* remember state */
  if(curbs)curbs->lineno = yylineno;
  bs->prev = curbs;
  
  /* set up current entry */
  bs->bs = yy_create_buffer(f, YY_BUF_SIZE);
  bs->f = f;
  bs->filename = fn;
  yy_switch_to_buffer(bs->bs);
  curbs = bs;
  yylineno = 1;
  curfilename = fn;
  
  return 1;
}

// Elimina la direccion del Archivo de la Memoria
int popfile(void)
{
  struct bufstack *bs = curbs;
  struct bufstack *prevbs;
  
  if(!bs) return 0;
  
  /* get rid of current entry
  fclose(bs->f);
  yy_delete_buffer(bs->bs);
  
  /* switch back to previous */
  prevbs = bs->prev;
  free(bs);
  if(!prevbs) return 0;
  yy_switch_to_buffer(prevbs->bs);
  curbs = prevbs;
  yylineno = curbs->lineno;
  curfilename = curbs->filename;
  
  return 1;
}
```

Primero define los estados iniciales y tambien usa codigo C para declarar las estructuras bufstack que mantendran las entradas en la lista de archivos entrates guardados. En la seccion de Patrones, el primer patron a reconocer son todas las declaraciones "#include" hasta las comillas, despues cambia a las declaraciones "IFILE" para leer el siguiente archivo entrante. El segundo patron reconoce las entradas que coincidan con el nombre de un archivo hasta una comilla cerrante, espacio en blanco o fin de linea, el nombre de archivo es llevado a "newfile" para una pila que acumula la entrada actual y prepara el siguiente nivel de entrada.

, but first there’s the matter of dealing with whatever remains of
the #include line. One possibility would be to use another start state and patterns that
absorb the rest of the line, but that would be tricky, since the action switches to the
included file, so the start state and pattern would have to be used after the end of the
included file. Instead, this is one of the few places where input() makes a scanner
simpler. A short loop reads until it finds the \n at the end of the line or EOF. Then,
when scanning returns to this file after the end of the included one, it resumes at the
beginning of the next line.
