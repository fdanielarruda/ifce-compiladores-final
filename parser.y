%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex();

extern FILE *yyin;

char *codigoGerado = NULL;

void appendCode(const char *novoCodigo) {
    if (codigoGerado == NULL) {
        codigoGerado = strdup(novoCodigo);
    } else {
        char *temp = malloc(strlen(codigoGerado) + strlen(novoCodigo) + 1);
        strcpy(temp, codigoGerado);
        strcat(temp, novoCodigo);
        free(codigoGerado);
        codigoGerado = temp;
    }
}
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

/* Declaração de não terminais */
%type <str> programa declaracoes declaracao configuracao loop comandos comando atribuicao
%type <str> tipo listaIdentificadores
%type <str> configuracaoPino configuracaoPWM conexaoWifi controleFluxo
%type <str> condicional repeticao operacaoHardware expressao

%%

programa:
    declaracoes configuracao loop {
        char *temp = malloc(strlen($1) + strlen($2) + strlen($3) + 50);
        sprintf(temp, "#include <Arduino.h>\n#include <WiFi.h>\n\n%s%s%s", $1, $2, $3);
        appendCode(temp);
        $$ = temp;
    }
    ;

declaracoes:
    /* vazio */ { $$ = strdup(""); }
    | declaracao declaracoes { 
        char *temp = malloc(strlen($1) + strlen($2) + 2);
        sprintf(temp, "%s\n%s", $1, $2);
        $$ = temp;
    }
    ;

declaracao:
    VAR tipo DOISPONTOS listaIdentificadores PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + strlen($4) + 20);
        sprintf(codigo, "%s %s;", $2, $4);
        $$ = codigo;
    }
    ;

tipo:
    INTEIRO { $$ = strdup("int"); }
    | TEXTO { $$ = strdup("String"); }
    | BOOLEANO { $$ = strdup("bool"); }
    ;

listaIdentificadores:
    IDENTIFICADOR { $$ = strdup($1); }
    | listaIdentificadores VIRGULA IDENTIFICADOR {
        char *temp = malloc(strlen($1) + strlen($3) + 3);
        sprintf(temp, "%s, %s", $1, $3);
        $$ = temp;
    }
    ;

configuracao:
    CONFIG comandos FIM {
        char *codigo = malloc(strlen($2) + 50);
        sprintf(codigo, "\nvoid setup()\n{\n%s}\n", $2);
        $$ = codigo;
    }
    ;

comandos:
    comando { $$ = strdup($1); }
    | comandos comando {
        char *temp = malloc(strlen($1) + strlen($2) + 1);
        strcpy(temp, $1);
        strcat(temp, $2);
        $$ = temp;
    }
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
    IDENTIFICADOR IGUAL expressao PONTOEVIRGULA {
        char *codigo = malloc(strlen($1) + strlen($3) + 10);
        sprintf(codigo, "%s = %s;\n", $1, $3);
        $$ = codigo;
    }
    ;

expressao:
    expressao MAIS expressao {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s + %s", $1, $3);
    }
    
    | expressao MENOS expressao {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s - %s", $1, $3);
    }
    
    | expressao MULTIPLICACAO expressao {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s * %s", $1, $3);
    }
    
    | expressao DIVISAO expressao {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s / %s", $1, $3);
    }
    
    | NUMERO {
        $$ = malloc(20);
        sprintf($$, "%d", $1);
    }
    
    | IDENTIFICADOR {
        $$ = strdup($1);
    }
    | STRING {
        $$ = strdup($1);
    }
    ;

configuracaoPino:
    CONFIGURAR IDENTIFICADOR COMO SAIDA PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + 30);
        sprintf(codigo, "pinMode(%s, OUTPUT);\n", $2);
        $$ = codigo;
    }
    ;

configuracaoPWM:
    CONFIGURARPWM IDENTIFICADOR COM FREQUENCIA NUMERO RESOLUCAO NUMERO PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + 50);
        sprintf(codigo, "ledcSetup(%s, %d, %d);\n", $2, $5, $7);
        $$ = codigo;
    }
    ;

conexaoWifi:
    CONECTARWIFI IDENTIFICADOR IDENTIFICADOR PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + strlen($3) + 170);
        sprintf(codigo, "WiFi.begin(%s.c_str(), %s.c_str());\nwhile (WiFi.status() != WL_CONNECTED)\n{\n    delay(500);\n    Serial.println(\"Conectando ao WiFi...\");\n}\nSerial.println(\"Conectado ao WiFi!\");\n", $2, $3);
        $$ = codigo;
    }
    ;

controleFluxo:
    condicional { $$ = $1; }
    | repeticao { $$ = $1; }
    ;

condicional:
    SE expressao ENTAO comandos SENAO comandos FIM {
        char *codigo = malloc(strlen($2) + strlen($4) + strlen($6) + 50);
        sprintf(codigo, "if (%s) { %s } else { %s }", $2, $4, $6);
        $$ = codigo;
    }
    | SE expressao ENTAO comandos FIM {
        char *codigo = malloc(strlen($2) + strlen($4) + 30);
        sprintf(codigo, "if (%s) { %s }", $2, $4);
        $$ = codigo;
    }
    ;

repeticao:
    ENQUANTO expressao FIM comandos FIM {
        char *codigo = malloc(strlen($2) + strlen($4) + 30);
        sprintf(codigo, "while (%s) { %s }", $2, $4);
        $$ = codigo;
    }
    ;

operacaoHardware:
    LIGAR IDENTIFICADOR PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + 20);
        sprintf(codigo, "digitalWrite(%s, HIGH);\n", $2);
        $$ = codigo;
    }
    | DESLIGAR IDENTIFICADOR PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + 25);
        sprintf(codigo, "digitalWrite(%s, LOW);\n", $2);
        $$ = codigo;
    }
    | AJUSTARPWM IDENTIFICADOR COM VALOR IDENTIFICADOR PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + strlen($5) + 40);
        sprintf(codigo, "ledcWrite(%s, %s);\n", $2, $5);
        $$ = codigo;
    }
    | ESPERAR NUMERO PONTOEVIRGULA {
        char *codigo = malloc(20);
        sprintf(codigo, "delay(%d);\n", $2);
        $$ = codigo;
    }
    | ESCREVER_SERIAL STRING PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + 30);
        sprintf(codigo, "Serial.println(%s);\n", $2);
        $$ = codigo;
    }
    | LER_SERIAL IDENTIFICADOR PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + 30);
        sprintf(codigo, "%s = Serial.readString();\n", $2);
        $$ = codigo;
    }
    | ENVIAR_HTTP STRING PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + 50);
        sprintf(codigo, "http.begin(%s);\nhttp.GET();\n", $2);
        $$ = codigo;
    }
    | LER_DIGITAL IDENTIFICADOR PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + 30);
        sprintf(codigo, "%s = digitalRead(%s);\n", $2, $2);
        $$ = codigo;
    }
    | LER_ANALOGICO IDENTIFICADOR PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + 30);
        sprintf(codigo, "%s = analogRead(%s);\n", $2, $2);
        $$ = codigo;
    }
    ;

loop:
    REPITA comandos FIM {
        char *codigo = malloc(strlen($2) + 30);
        sprintf(codigo, "\nvoid loop()\n{\n%s}\n", $2);
        $$ = codigo;
    }
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
        FILE *arquivo = fopen("resultados/output.cpp", "w");
        if (arquivo) {
            fprintf(arquivo, "%s", codigoGerado);
            fclose(arquivo);
        } else {
            perror("Erro ao criar o arquivo de saída");
        }
        free(codigoGerado);
    }

    return 0;
}
