%{
#include "parser.tab.h"
#include <stdio.h>
%}

%%
"var"                   { printf("Token: VAR, Valor: %s\n", yytext); return VAR; }
"inteiro"               { printf("Token: INTEIRO, Valor: %s\n", yytext); return INTEIRO; }
"texto"                 { printf("Token: TEXTO, Valor: %s\n", yytext); return TEXTO; }
"booleano"              { printf("Token: BOOLEANO, Valor: %s\n", yytext); return BOOLEANO; }

"config"                { printf("Token: CONFIG, Valor: %s\n", yytext); return CONFIG; }
"configurar"            { printf("Token: CONFIGURAR, Valor: %s\n", yytext); return CONFIGURAR; }
"configurarPWM"         { printf("Token: CONFIGURARPWM, Valor: %s\n", yytext); return CONFIGURARPWM; }
"configurarSerial"      { printf("Token: CONFIGURARSERIAL, Valor: %s\n", yytext); return CONFIGURARSERIAL; }
"conectarWifi"          { printf("Token: CONECTARWIFI, Valor: %s\n", yytext); return CONECTARWIFI; }

"ligar"                 { printf("Token: LIGAR, Valor: %s\n", yytext); return LIGAR; }
"desligar"              { printf("Token: DESLIGAR, Valor: %s\n", yytext); return DESLIGAR; }
"ajustarPWM"            { printf("Token: AJUSTARPWM, Valor: %s\n", yytext); return AJUSTARPWM; }
"esperar"               { printf("Token: ESPERAR, Valor: %s\n", yytext); return ESPERAR; }
"escreverSerial"        { printf("Token: ESCREVER_SERIAL, Valor: %s\n", yytext); return ESCREVER_SERIAL; }
"lerSerial"             { printf("Token: LER_SERIAL, Valor: %s\n", yytext); return LER_SERIAL; }
"enviarHttp"            { printf("Token: ENVIAR_HTTP, Valor: %s\n", yytext); return ENVIAR_HTTP; }
"lerDigital"            { printf("Token: LER_DIGITAL, Valor: %s\n", yytext); return LER_DIGITAL; }
"lerAnalogico"          { printf("Token: LER_ANALOGICO, Valor: %s\n", yytext); return LER_ANALOGICO; }

"se"                    { printf("Token: SE, Valor: %s\n", yytext); return SE; }
"senao"                 { printf("Token: SENAO, Valor: %s\n", yytext); return SENAO; }
"entao"                 { printf("Token: ENTAO, Valor: %s\n", yytext); return ENTAO; }
"enquanto"              { printf("Token: ENQUANTO, Valor: %s\n", yytext); return ENQUANTO; }
"repita"                { printf("Token: REPITA, Valor: %s\n", yytext); return REPITA; }
"fim"                   { printf("Token: FIM, Valor: %s\n", yytext); return FIM; }

"com"                   { printf("Token: COM, Valor: %s\n", yytext); return COM; }
"como"                  { printf("Token: COMO, Valor: %s\n", yytext); return COMO; }
"saida"                 { printf("Token: SAIDA, Valor: %s\n", yytext); return SAIDA; }
"entrada"               { printf("Token: ENTRADA, Valor: %s\n", yytext); return ENTRADA; }
"frequencia"            { printf("Token: FREQUENCIA, Valor: %s\n", yytext); return FREQUENCIA; }
"resolucao"             { printf("Token: RESOLUCAO, Valor: %s\n", yytext); return RESOLUCAO; }
"valor"                 { printf("Token: VALOR, Valor: %s\n", yytext); return VALOR; }

"="                     { printf("Token: IGUAL, Valor: %s\n", yytext); return IGUAL; }
"=="                    { printf("Token: IGUAL_IGUAL, Valor: %s\n", yytext); return IGUAL_IGUAL; }
"!="                    { printf("Token: DIFERENTE, Valor: %s\n", yytext); return DIFERENTE; }
"<"                     { printf("Token: MENOR, Valor: %s\n", yytext); return MENOR; }
">"                     { printf("Token: MAIOR, Valor: %s\n", yytext); return MAIOR; }
"<="                    { printf("Token: MENOR_IGUAL, Valor: %s\n", yytext); return MENOR_IGUAL; }
">="                    { printf("Token: MAIOR_IGUAL, Valor: %s\n", yytext); return MAIOR_IGUAL; }

"+"                     { printf("Token: MAIS, Valor: %s\n", yytext); return MAIS; }
"-"                     { printf("Token: MENOS, Valor: %s\n", yytext); return MENOS; }
"*"                     { printf("Token: MULTIPLICACAO, Valor: %s\n", yytext); return MULTIPLICACAO; }
"/"                     { printf("Token: DIVISAO, Valor: %s\n", yytext); return DIVISAO; }
"%"                     { printf("Token: MODULO, Valor: %s\n", yytext); return MODULO; }
","                     { printf("Token: VIRGULA, Valor: %s\n", yytext); return VIRGULA; }
";"                     { printf("Token: PONTOEVIRGULA, Valor: %s\n", yytext); return PONTOEVIRGULA; }
":"                     { printf("Token: DOISPONTOS, Valor: %s\n", yytext); return DOISPONTOS; }

"\n"                    { yylineno++; }
[0-9]+                  { yylval.num = atoi(yytext); printf("Token: NUMERO, Valor: %s\n", yytext); return NUMERO; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.id = strdup(yytext); printf("Token: IDENTIFICADOR, Valor: %s\n", yytext); return IDENTIFICADOR; }
\"[^\"]*\"              { yylval.str = strdup(yytext); printf("Token: STRING, Valor: %s\n", yytext); return STRING; }
[ \t]                   { /* Ignora espaços e tabs */ }
"//".*                  { /* Ignora comentários de linha */ }

%%

int yywrap() {
    return 1;
}