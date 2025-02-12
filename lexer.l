%{
#include "parser.tab.h"
%}

%%

"var"                   { return VAR; }
"inteiro"               { return INTEIRO; }
"texto"                 { return TEXTO; }
"config"                { return CONFIG; }
"fim"                   { return FIM; }
"repita"                { return REPITA; }
"como"                  { return COMO; }
"com"                   { return COM; }
"configurar"            { return CONFIGURAR; }
"configurarPWM"         { return CONFIGURARPWM; }
"conectarWifi"          { return CONECTARWIFI; }
"ajustarPWM"            { return AJUSTARPWM; }
"esperar"               { return ESPERAR; }
"saida"                 { return SAIDA; }
"frequencia"            { return FREQUENCIA; }
"resolucao"             { return RESOLUCAO; }
"="                     { return IGUAL; }
";"                     { return PONTOEVIRGULA; }
":"                     { return DOISPONTOS; }
[0-9]+                  { yylval.num = atoi(yytext); return NUMERO; }
[a-zA-Z_][a-zA-Z0-9_]*  { yylval.str = strdup(yytext); return IDENTIFICADOR; }
\"[^\"]*\"              { yylval.str = strdup(yytext); return STRING; }
[ \t\n]                 ; // Ignora espaços, tabs e novas linhas
"//".*                  ; // Ignora comentários de linha
.                       { return yytext[0]; }

%%

int yywrap() {
    return 1;
}