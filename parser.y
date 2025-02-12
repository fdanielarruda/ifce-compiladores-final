%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex();

extern FILE *yyin;

char *codigoGerado = NULL;

%}

%union {
    int num;
    char *str;
}

%token VAR INTEIRO TEXTO CONFIG FIM REPITA COMO COM CONFIGURAR CONFIGURARPWM CONECTARWIFI AJUSTARPWM ESPERAR
%token IGUAL PONTOEVIRGULA DOISPONTOS
%token <num> NUMERO
%token <str> IDENTIFICADOR STRING
%token SAIDA FREQUENCIA RESOLUCAO

%%

programa:
    declaracoes configuracao loop
    ;

declaracoes:
    declaracao
    | declaracoes declaracao
    ;

declaracao:
    VAR tipo DOISPONTOS listaIdentificadores PONTOEVIRGULA
    ;

tipo:
    INTEIRO
    | TEXTO
    ;

listaIdentificadores:
    IDENTIFICADOR
    | listaIdentificadores PONTOEVIRGULA IDENTIFICADOR
    ;

configuracao:
    CONFIG comandos FIM
    ;

comandos:
    comando
    | comandos comando
    ;

comando:
    atribuicao
    | configuracaoPino
    | configuracaoPWM
    | conexaoWifi
    ;

atribuicao:
    IDENTIFICADOR IGUAL valor PONTOEVIRGULA
    ;

valor:
    NUMERO
    | STRING
    ;

configuracaoPino:
    CONFIGURAR IDENTIFICADOR COMO SAIDA PONTOEVIRGULA
    ;

configuracaoPWM:
    CONFIGURARPWM IDENTIFICADOR COM FREQUENCIA NUMERO RESOLUCAO NUMERO PONTOEVIRGULA
    ;

conexaoWifi:
    CONECTARWIFI IDENTIFICADOR IDENTIFICADOR PONTOEVIRGULA
    ;

loop:
    REPITA comandos FIM
    ;

%%

void yyerror(const char *msg) {
    extern int yylineno;  // Declara a variável global yylineno
    extern char *yytext;   // Declara a variável global yytext

    fprintf(stderr, "Erro de sintaxe na linha %d: %s\n", yylineno, msg);
    fprintf(stderr, "Token inesperado: '%s'\n", yytext);
}

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Erro ao abrir o arquivo");
            return 1;
        }
    }

    yyparse();

    if (codigoGerado) {
        printf("%s", codigoGerado);
        free(codigoGerado);
    }

    return 0;
}