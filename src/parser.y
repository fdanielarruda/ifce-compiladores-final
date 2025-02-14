%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex();

extern FILE *yyin;

char *codigoGerado = NULL;
char *tipoAtual = NULL;
char *constantesGlobais = NULL;

struct VariavelDeclarada {
    char *nome;
    char *tipo;
    struct VariavelDeclarada *prox;
};

struct VariavelDeclarada *variaveis = NULL;

int variavelJaDeclarada(const char *nome) {
    struct VariavelDeclarada *atual = variaveis;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return 1;
        }
        atual = atual->prox;
    }
    return 0;
}

int verificarVariavelDeclarada(const char *nome) {
    if (!variavelJaDeclarada(nome)) {
        char erro[256];
        snprintf(erro, sizeof(erro), "Erro: Variável '%s' não foi declarada antes do uso", nome);
        yyerror(erro);
        return 0;
    }
    return 1;
}

void adicionarVariavel(const char *nome, const char *tipo) {
    struct VariavelDeclarada *nova = malloc(sizeof(struct VariavelDeclarada));
    nova->nome = strdup(nome);
    nova->tipo = strdup(tipo);
    nova->prox = variaveis;
    variaveis = nova;
}

void liberarVariaveis() {
    struct VariavelDeclarada *atual = variaveis;
    while (atual != NULL) {
        struct VariavelDeclarada *temp = atual;
        atual = atual->prox;
        free(temp->nome);
        free(temp->tipo);
        free(temp);
    }
    variaveis = NULL;
}

void appendCode(const char *novoCodigo) {
    if (codigoGerado == NULL) {
        codigoGerado = strdup(novoCodigo);
    } else {
        size_t novoTamanho = strlen(codigoGerado) + strlen(novoCodigo) + 1;
        char *temp = (char *)malloc(novoTamanho);
        if (temp == NULL) {
            fprintf(stderr, "Erro: Falha na alocação de memória\n");
            exit(1);
        }
        strcpy(temp, codigoGerado);
        strcat(temp, novoCodigo);
        free(codigoGerado);
        codigoGerado = temp;
    }
}

void appendConstantes(const char *novaConstante) {
    if (constantesGlobais == NULL) {
        constantesGlobais = strdup(novaConstante);
    } else {
        size_t novoTamanho = strlen(constantesGlobais) + strlen(novaConstante) + 1;
        char *temp = (char *)malloc(novoTamanho);
        if (temp == NULL) {
            fprintf(stderr, "Erro: Falha na alocação de memória\n");
            exit(1);
        }
        strcpy(temp, constantesGlobais);
        strcat(temp, novaConstante);
        free(constantesGlobais);
        constantesGlobais = temp;
    }
}

int verificarTipoParaOperacao(char *var1, char *var2) {
    struct VariavelDeclarada *v1 = variaveis;
    struct VariavelDeclarada *v2 = variaveis;
    while (v1 != NULL && strcmp(v1->nome, var1) != 0) {
        v1 = v1->prox;
    }
    while (v2 != NULL && strcmp(v2->nome, var2) != 0) {
        v2 = v2->prox;
    }
    if (v1 == NULL || v2 == NULL) {
        yyerror("Erro: Variáveis não declaradas");
        return 0;
    }
    if (strcmp(v1->tipo, "int") != 0 || strcmp(v2->tipo, "int") != 0) {
        yyerror("Erro: Operações aritméticas permitidas apenas para variáveis inteiras");
        return 0;
    }
    return 1;
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
%token COM COMO SAIDA ENTRADA FREQUENCIA RESOLUCAO
%token IGUAL IGUAL_IGUAL DIFERENTE MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL 
%token MAIS MENOS MULTIPLICACAO DIVISAO MODULO VIRGULA PONTOEVIRGULA DOISPONTOS
%token VALOR

/* Declaração de precedência e associatividade */
%left IGUAL_IGUAL DIFERENTE
%left MENOR MAIOR MENOR_IGUAL MAIOR_IGUAL
%left MAIS MENOS
%left MULTIPLICACAO DIVISAO MODULO
%right IGUAL

/* Declaração de não terminais */
%type <str> programa declaracoes declaracao configuracao loop comandos comando atribuicao
%type <str> tipo listaIdentificadores
%type <str> configuracaoPino configuracaoPWM configuracaoSerial conexaoWifi controleFluxo
%type <str> condicional repeticao operacaoHardware expressao

%%

programa:
    declaracoes configuracao loop {
        char *temp = malloc(strlen($1) + (constantesGlobais ? strlen(constantesGlobais) : 0) + strlen($2) + strlen($3) + 100);
        sprintf(temp, "#include <Arduino.h>\n#include <WiFi.h>\n\n%s%s%s%s", $1, constantesGlobais ? constantesGlobais : "", $2, $3);
        appendCode(temp);
        $$ = temp;
    }

declaracoes:
    /* vazio */ { $$ = strdup(""); }
    | declaracao declaracoes { 
        char *temp = malloc(strlen($1) + strlen($2) + 2);
        sprintf(temp, "%s%s", $1, $2);
        $$ = temp;
    }
    ;

declaracao:
    VAR tipo DOISPONTOS listaIdentificadores PONTOEVIRGULA {
        $$ = strdup($4);
    }
    ;

tipo:
    INTEIRO { 
        if (tipoAtual) free(tipoAtual);
        tipoAtual = strdup("int"); 
        $$ = tipoAtual; 
    }
    | TEXTO { 
        if (tipoAtual) free(tipoAtual);
        tipoAtual = strdup("String"); 
        $$ = tipoAtual; 
    }
    | BOOLEANO { 
        if (tipoAtual) free(tipoAtual);
        tipoAtual = strdup("bool"); 
        $$ = tipoAtual; 
    }
    ;

listaIdentificadores:
    IDENTIFICADOR { 
        if (!tipoAtual) { 
            yyerror("Erro: tipo não definido antes dos identificadores."); 
            YYABORT; 
        }
        if (variavelJaDeclarada($1)) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Erro: Variável '%s' já foi declarada", $1);
            yyerror(erro);
            YYABORT;
        }
        adicionarVariavel($1, tipoAtual);
        size_t tamanho = strlen(tipoAtual) + strlen($1) + 10;
        char *codigo = (char *)malloc(tamanho);
        if (codigo == NULL) {
            yyerror("Erro: Falha na alocação de memória");
            YYABORT;
        }
        snprintf(codigo, tamanho, "%s %s;\n", tipoAtual, $1);
        $$ = codigo;
    }
    | listaIdentificadores VIRGULA IDENTIFICADOR {
        if (!tipoAtual) { 
            yyerror("Erro: tipo não definido antes dos identificadores."); 
            YYABORT; 
        }
        if (variavelJaDeclarada($3)) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Erro: Variável '%s' já foi declarada", $3);
            yyerror(erro);
            YYABORT;
        }
        adicionarVariavel($3, tipoAtual);
        size_t tamanho = strlen($1) + strlen(tipoAtual) + strlen($3) + 10;
        char *temp = (char *)malloc(tamanho);
        if (temp == NULL) {
            yyerror("Erro: Falha na alocação de memória");
            YYABORT;
        }
        snprintf(temp, tamanho, "%s%s %s;\n", $1, tipoAtual, $3);
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
    | configuracaoSerial
    | conexaoWifi
    | controleFluxo
    | operacaoHardware
    ;

atribuicao:
    IDENTIFICADOR IGUAL expressao PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($1)) {
            YYABORT;
        }
        char *codigo = malloc(strlen($1) + strlen($3) + 10);
        sprintf(codigo, "%s = %s;\n", $1, $3);
        $$ = codigo;
    }
    | IDENTIFICADOR IGUAL LER_DIGITAL IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($1)) {
            YYABORT;
        }
        if (!verificarVariavelDeclarada($4)) {
            YYABORT;
        }
        char *codigo = malloc(strlen($1) + strlen($4) + 30);
        sprintf(codigo, "%s = digitalRead(%s);\n", $1, $4);
        $$ = codigo;
    }
    | IDENTIFICADOR IGUAL LER_ANALOGICO IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($1)) {
            YYABORT;
        }
        if (!verificarVariavelDeclarada($4)) {
            YYABORT;
        }
        char *codigo = malloc(strlen($1) + strlen($4) + 30);
        sprintf(codigo, "%s = analogRead(%s);\n", $1, $4);
        $$ = codigo;
    }
    ;

expressao:
    expressao MAIS expressao {
        if (!verificarTipoParaOperacao($1, $3)) {
            YYABORT;
        }
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s + %s", $1, $3);
    }
    | expressao MENOS expressao {
        if (!verificarTipoParaOperacao($1, $3)) {
            YYABORT;
        }
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s - %s", $1, $3);
    }
    | expressao MULTIPLICACAO expressao {
        if (!verificarTipoParaOperacao($1, $3)) {
            YYABORT;
        }
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s * %s", $1, $3);
    }
    | expressao DIVISAO expressao {
        if (!verificarTipoParaOperacao($1, $3)) {
            YYABORT;
        }
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s / %s", $1, $3);
    }
    | expressao IGUAL_IGUAL expressao {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s == %s", $1, $3);
    }
    | expressao DIFERENTE expressao {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s != %s", $1, $3);
    }
    | expressao MENOR expressao {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s < %s", $1, $3);
    }
    | expressao MAIOR expressao {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s > %s", $1, $3);
    }
    | expressao MENOR_IGUAL expressao {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s <= %s", $1, $3);
    }
    | expressao MAIOR_IGUAL expressao {
        $$ = malloc(strlen($1) + strlen($3) + 4);
        sprintf($$, "%s >= %s", $1, $3);
    }
    | NUMERO {
        $$ = malloc(20);
        sprintf($$, "%d", $1);
    }
    | IDENTIFICADOR {
        if (!verificarVariavelDeclarada($1)) {
            YYABORT;
        }
        $$ = strdup($1);
    }
    | STRING {
        $$ = strdup($1);
    }
    ;

configuracaoPino:
    CONFIGURAR IDENTIFICADOR COMO SAIDA PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) {
            YYABORT;
        }
        char *codigo = malloc(strlen($2) + 30);
        sprintf(codigo, "pinMode(%s, OUTPUT);\n", $2);
        $$ = codigo;
    }
    | CONFIGURAR IDENTIFICADOR COMO ENTRADA PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) {
            YYABORT;
        }
        char *codigo = malloc(strlen($2) + 30);
        sprintf(codigo, "pinMode(%s, INPUT);\n", $2);
        $$ = codigo;
    }
    ;

configuracaoPWM:
    CONFIGURARPWM IDENTIFICADOR COM FREQUENCIA NUMERO RESOLUCAO NUMERO PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) {
            YYABORT;
        }
        char constantes[200];
        char codigo[200];

        sprintf(constantes, "\nconst int canalPWM = 0;\nconst int frequencia = %d;\nconst int resolucao = %d;\n", $5, $7);
        appendConstantes(constantes);

        sprintf(codigo, "ledcSetup(canalPWM, frequencia, resolucao);\nledcAttachPin(%s, canalPWM);\n", $2);
        $$ = strdup(codigo);
    }
    ;

configuracaoSerial:
    CONFIGURARSERIAL NUMERO PONTOEVIRGULA {
        char *codigo = malloc(50);
        sprintf(codigo, "Serial.begin(%d);\n", $2);
        $$ = codigo;
    }
    ;

conexaoWifi:
    CONECTARWIFI IDENTIFICADOR IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) {
            YYABORT;
        }
        if (!verificarVariavelDeclarada($3)) {
            YYABORT;
        }
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
        sprintf(codigo, "if (%s)\n{\n%s}\nelse\n{\n%s}\n", $2, $4, $6);
        $$ = codigo;
    }
    | SE expressao ENTAO comandos FIM {
        char *codigo = malloc(strlen($2) + strlen($4) + 30);
        sprintf(codigo, "if (%s)\n{\n%s}\n", $2, $4);
        $$ = codigo;
    }
    ;

repeticao:
    ENQUANTO expressao FIM comandos FIM {
        char *codigo = malloc(strlen($2) + strlen($4) + 30);
        sprintf(codigo, "while (%s)\n{\n%s}\n", $2, $4);
        $$ = codigo;
    }
    ;

operacaoHardware:
    LIGAR IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) {
            YYABORT;
        }
        char *codigo = malloc(strlen($2) + 20);
        sprintf(codigo, "digitalWrite(%s, HIGH);\n", $2);
        $$ = codigo;
    }
    | DESLIGAR IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) {
            YYABORT;
        }
        char *codigo = malloc(strlen($2) + 25);
        sprintf(codigo, "digitalWrite(%s, LOW);\n", $2);
        $$ = codigo;
    }
    | AJUSTARPWM IDENTIFICADOR COM VALOR IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) {
            YYABORT;
        }
        if (!verificarVariavelDeclarada($5)) {
            YYABORT;
        }
        char *codigo = malloc(strlen($2) + strlen($5) + 40);
        sprintf(codigo, "ledcWrite(%s, %s);\n", $2, $5);
        $$ = codigo;
    }
    | ESPERAR NUMERO PONTOEVIRGULA {
        char *codigo = malloc(20);
        sprintf(codigo, "delay(%d);\n", $2);
        $$ = codigo;
    }
    | ESCREVER_SERIAL expressao PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + 30);
        sprintf(codigo, "Serial.println(%s);\n", $2);
        $$ = codigo;
    }
    | LER_SERIAL IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) {
            YYABORT;
        }
        char *codigo = malloc(strlen($2) + 30);
        sprintf(codigo, "%s = Serial.readString();\n", $2);
        $$ = codigo;
    }
    | ENVIAR_HTTP expressao expressao PONTOEVIRGULA {
        char *codigo = malloc(strlen($2) + strlen($3) + 500);
        sprintf(codigo, "if (WiFi.status() == WL_CONNECTED)\n{\n    http.begin(%s);\n    int httpResponseCode = http.GET();\n    if (httpResponseCode > 0) {\n        Serial.print(\"Resposta HTTP: \");\n        Serial.println(httpResponseCode);\n    } else {\n        Serial.print(\"Erro na requisição: \");\n        Serial.println(httpResponseCode);\n    }\n    http.end();\n} else {\n    Serial.println(\"WiFi desconectado, tentando reconectar...\");\n    WiFi.begin(%s, %s);\n}\n", $2, $2, $3);
        $$ = codigo;
    }
    | LER_DIGITAL IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) {
            YYABORT;
        }
        char *codigo = malloc(strlen($2) + 30);
        sprintf(codigo, "%s = digitalRead(%s);\n", $2, $2);
        $$ = codigo;
    }
    | LER_ANALOGICO IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) {
            YYABORT;
        }
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
}

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Erro ao abrir o arquivo");
            return 1;
        }
    } else {
        fprintf(stderr, "Uso: %s <arquivo de entrada>\n", argv[0]);
        return 1;
    }

    yyparse();

    if (codigoGerado) {
        char *entrada = argv[1];
        char *nomeArquivo = strrchr(entrada, '/');
        nomeArquivo = (nomeArquivo) ? nomeArquivo + 1 : entrada;

        char saida[256];
        snprintf(saida, sizeof(saida), "langs/%s", nomeArquivo);

        char *ponto = strrchr(saida, '.');
        if (ponto) {
            strcpy(ponto, ".cpp");
        } else {
            strcat(saida, ".cpp");
        }

        FILE *arquivo = fopen(saida, "w");
        if (arquivo) {
            fprintf(arquivo, "%s", codigoGerado);
            fclose(arquivo);
            printf("Código gerado salvo em: %s\n", saida);
        } else {
            perror("Erro ao criar o arquivo de saída");
        }

        free(codigoGerado);
    }

    liberarVariaveis(); // Libera a memória da lista de variáveis
    return 0;
}