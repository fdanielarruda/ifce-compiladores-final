%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex();

extern FILE *yyin;

char *codigoGerado = NULL;
%}

/* Declaração dos tipos de dados utilizados no %union */
%union {
    char *str;
    int num;
    char *id;
}

/* Tokens terminais */
%token <str> IDENTIFICADOR
%token <num> NUMERO
%token <str> STRING
%token VAR INTEIRO TEXTO BOOLEANO 
%token CONFIG CONFIGURAR CONFIGURARPWM CONFIGURARSERIAL CONECTARWIFI
%token LIGAR DESLIGAR AJUSTARPWM ESPERAR ESCREVER_SERIAL LER_SERIAL ENVIAR_HTTP LER_DIGITAL LER_ANALOGICO
%token SE SENAO ENTAO ENQUANTO REPITA FIM
%token COM COMO SAIDA FREQUENCIA RESOLUCAO
%token IGUAL IGUAL_IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL 
%token MAIS MENOS MULTIPLICACAO DIVISAO MODULO VIRGULA PONTOEVIRGULA DOISPONTOS
%token VALOR

/* Declaração de precedência e associatividade */
%left MAIS MENOS
%left MULTIPLICACAO DIVISAO MODULO
%right IGUAL

/* Declaração de não terminais e seus tipos */


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
    | BOOLEANO
    ;

listaIdentificadores:
    IDENTIFICADOR
    | listaIdentificadores VIRGULA IDENTIFICADOR
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
    | controleFluxo
    | operacaoHardware
    ;

atribuicao:
    IDENTIFICADOR IGUAL expressao PONTOEVIRGULA
    ;

expressao:
    expressao MAIS expressao
    | expressao MENOS expressao
    | expressao MULTIPLICACAO expressao
    | expressao DIVISAO expressao
    | NUMERO
    | IDENTIFICADOR
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

controleFluxo:
    condicional
    | repeticao
    ;

condicional:
    SE expressao ENTAO comandos SENAO comandos FIM
    | SE expressao ENTAO comandos FIM
    ;

repeticao:
    ENQUANTO expressao FIM comandos FIM
    ;

operacaoHardware:
    LIGAR IDENTIFICADOR PONTOEVIRGULA
    | DESLIGAR IDENTIFICADOR PONTOEVIRGULA
    | AJUSTARPWM IDENTIFICADOR COM VALOR IDENTIFICADOR PONTOEVIRGULA
    | ESPERAR NUMERO PONTOEVIRGULA
    | ESCREVER_SERIAL STRING PONTOEVIRGULA
    | LER_SERIAL IDENTIFICADOR PONTOEVIRGULA
    | ENVIAR_HTTP STRING PONTOEVIRGULA
    | LER_DIGITAL IDENTIFICADOR PONTOEVIRGULA
    | LER_ANALOGICO IDENTIFICADOR PONTOEVIRGULA
    ;

loop:
    REPITA comandos FIM
    ;

%%

void yyerror(const char *msg) {
    extern int yylineno;
    extern char *yytext;

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
