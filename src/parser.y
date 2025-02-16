%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* Estrutura para os nós da árvore sintática */
typedef struct NoArvore {
    char *rotulo;
    int numFilhos;
    struct NoArvore **filhos;
} NoArvore;

NoArvore *novoNoArvore(const char *rotulo) {
    NoArvore *no = (NoArvore *)malloc(sizeof(NoArvore));
    if (!no) {
        fprintf(stderr, "Erro ao alocar memória para o nó da árvore\n");
        exit(1);
    }
    no->rotulo = strdup(rotulo);
    no->numFilhos = 0;
    no->filhos = NULL;
    return no;
}

void adicionarFilho(NoArvore *pai, NoArvore *filho) {
    pai->numFilhos++;
    pai->filhos = (NoArvore **)realloc(pai->filhos, pai->numFilhos * sizeof(NoArvore *));
    if (!pai->filhos) {
        fprintf(stderr, "Erro ao alocar memória para os filhos da árvore\n");
        exit(1);
    }
    pai->filhos[pai->numFilhos - 1] = filho;
}

void imprimirArvore(NoArvore *no, int nivel) {
    for (int i = 0; i < nivel; i++) 
        printf("  ");
    printf("%s\n", no->rotulo);
    for (int i = 0; i < no->numFilhos; i++) {
        imprimirArvore(no->filhos[i], nivel + 1);
    }
}

void liberarArvore(NoArvore *no) {
    if (no) {
        for (int i = 0; i < no->numFilhos; i++) {
            liberarArvore(no->filhos[i]);
        }
        free(no->filhos);
        free(no->rotulo);
        free(no);
    }
}

void exportarArvoreParaArquivo(NoArvore *no, int nivel, FILE *arquivo) {
    for (int i = 0; i < nivel; i++) {
        fprintf(arquivo, "  ");
    }
    fprintf(arquivo, "%s\n", no->rotulo);
    for (int i = 0; i < no->numFilhos; i++) {
        exportarArvoreParaArquivo(no->filhos[i], nivel + 1, arquivo);
    }
}

typedef struct SemInfo {
    char *codigo;
    NoArvore *no;
} SemInfo;


NoArvore *arvoreSintatica = NULL;

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

struct Pino {
    char *nome;
    int configurado;
    struct Pino *prox;
};
struct Pino *pinosPWM = NULL;
struct Pino *pinosEntrada = NULL;
struct Pino *pinosSaida = NULL;

/* Funções de manipulação de variáveis e pinos */
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
        snprintf(erro, sizeof(erro), "Variável '%s' não foi declarada antes do uso", nome);
        yyerror(erro);
        return 0;
    }
    return 1;
}

char* obterTipoVariavel(const char *nome) {
    struct VariavelDeclarada *atual = variaveis;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual->tipo;
        }
        atual = atual->prox;
    }
    return NULL;
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

void acrescentarCodigo(const char *novoCodigo) {
    if (codigoGerado == NULL) {
        codigoGerado = strdup(novoCodigo);
    } else {
        size_t tamanhoNovo = strlen(codigoGerado) + strlen(novoCodigo) + 1;
        char *temp = (char *)malloc(tamanhoNovo);
        if (temp == NULL) {
            fprintf(stderr, "Falha na alocação de memória\n");
            exit(1);
        }
        strcpy(temp, codigoGerado);
        strcat(temp, novoCodigo);
        free(codigoGerado);
        codigoGerado = temp;
    }
}

void acrescentarConstantes(const char *novaConstante) {
    if (constantesGlobais == NULL) {
        constantesGlobais = strdup(novaConstante);
    } else {
        size_t tamanhoNovo = strlen(constantesGlobais) + strlen(novaConstante) + 1;
        char *temp = (char *)malloc(tamanhoNovo);
        if (temp == NULL) {
            fprintf(stderr, "Falha na alocação de memória\n");
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
        yyerror("Variáveis não declaradas");
        return 0;
    }
    if (strcmp(v1->tipo, "int") != 0 || strcmp(v2->tipo, "int") != 0) {
        yyerror("Operações aritméticas permitidas apenas para variáveis inteiras");
        return 0;
    }
    return 1;
}

void gerarErroTipoIncompativel(const char *nomeVar, const char *tipoEsperado) {
    char mensagem[256];
    snprintf(mensagem, sizeof(mensagem), "Tipos incompatíveis na atribuição. A variável '%s' deve ser do tipo %s.", nomeVar, tipoEsperado);
    yyerror(mensagem);
}

int verificarTipoAtribuicao(char *nomeVar, char *tipoVar, char *valor) {
    int tipoValor = 0; // 0: indefinido, 1: inteiro, 2: string

    char *endptr;
    strtol(valor, &endptr, 10);
    if (*endptr == '\0') {
        tipoValor = 1;
    } else if (valor[0] == '"' && valor[strlen(valor) - 1] == '"') {
        tipoValor = 2;
    }
    if (strcmp(tipoVar, "int") == 0 && tipoValor != 1) {
        gerarErroTipoIncompativel(nomeVar, "int");
        return 0;
    }
    if (strcmp(tipoVar, "String") == 0 && tipoValor != 2) {
        gerarErroTipoIncompativel(nomeVar, "String");
        return 0;
    }
    return 1;
}

void adicionarPino(struct Pino **lista, const char *nome) {
    struct Pino *novo = malloc(sizeof(struct Pino));
    novo->nome = strdup(nome);
    novo->configurado = 1;
    novo->prox = *lista;
    *lista = novo;
}

int pinoConfigurado(struct Pino *lista, const char *nome) {
    struct Pino *atual = lista;
    while (atual != NULL) {
        if (strcmp(atual->nome, nome) == 0) {
            return atual->configurado;
        }
        atual = atual->prox;
    }
    return 0;
}

void liberarPinos(struct Pino **lista) {
    struct Pino *atual = *lista;
    while (atual != NULL) {
        struct Pino *temp = atual;
        atual = atual->prox;
        free(temp->nome);
        free(temp);
    }
    *lista = NULL;
}

char* gerarCodigoAtribuicao(const char *nomeVar, const char *valor) {
    char *codigo = malloc(strlen(nomeVar) + strlen(valor) + 10);
    sprintf(codigo, "%s = %s;\n", nomeVar, valor);
    return codigo;
}

char* gerarCodigoOperacaoHardware(const char *comando, const char *pino, const char *valor) {
    char *codigo = malloc(strlen(comando) + strlen(pino) + (valor ? strlen(valor) : 0) + 20);
    if (valor) {
        sprintf(codigo, "%s(%s, %s);\n", comando, pino, valor);
    } else {
        sprintf(codigo, "%s(%s);\n", comando, pino);
    }
    return codigo;
}

void adicionarPinoPWM(const char *nome) { adicionarPino(&pinosPWM, nome); }
int pinoPWMConfigurado(const char *nome) { return pinoConfigurado(pinosPWM, nome); }
void liberarPinosPWM() { liberarPinos(&pinosPWM); }

void adicionarPinoEntrada(const char *nome) { adicionarPino(&pinosEntrada, nome); }
int pinoEntradaConfigurado(const char *nome) { return pinoConfigurado(pinosEntrada, nome); }
void liberarPinosEntrada() { liberarPinos(&pinosEntrada); }

void adicionarPinoSaida(const char *nome) { adicionarPino(&pinosSaida, nome); }
int pinoSaidaConfigurado(const char *nome) { return pinoConfigurado(pinosSaida, nome); }
void liberarPinosSaida() { liberarPinos(&pinosSaida); }
%}

/* ======================================================= */
/* Definição do %union – agora inclui o ponteiro para SemInfo */
%union {
    char *str;
    int num;
    char *id;
    struct SemInfo *info;
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

/* Para os não-terminais que geram código e árvore, usamos o tipo <info> */
%type <info> programa declaracoes declaracao configuracao loop comandos comando atribuicao expressao configuracaoPino configuracaoPWM configuracaoSerial conexaoWifi controleFluxo condicional repeticao operacaoHardware listaIdentificadores tipo

%%

programa:
    declaracoes configuracao loop {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($1->codigo) +
                  (constantesGlobais ? strlen(constantesGlobais) : 0) +
                  strlen($2->codigo) + strlen($3->codigo) + 100;
        char *temp = malloc(len);
        sprintf(temp, "#include <Arduino.h>\n#include <WiFi.h>\n#include <HTTPClient.h>\n\n%s%s%s%s",
                $1->codigo, (constantesGlobais ? constantesGlobais : ""), $2->codigo, $3->codigo);
        info->codigo = temp;
        info->no = novoNoArvore("programa");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, $2->no);
        adicionarFilho(info->no, $3->no);
        acrescentarCodigo(temp);
        arvoreSintatica = info->no; /* Guarda a raiz da árvore */
        $$ = info;
    }
    ;

declaracoes:
    /* vazio */
    {
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = strdup("");
        info->no = novoNoArvore("declaracoes (vazio)");
        $$ = info;
    }
    | declaracao declaracoes {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($1->codigo) + strlen($2->codigo) + 1;
        char *temp = malloc(len);
        sprintf(temp, "%s%s", $1->codigo, $2->codigo);
        info->codigo = temp;
        info->no = novoNoArvore("declaracoes");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, $2->no);
        $$ = info;
    }
    ;

declaracao:
    VAR tipo DOISPONTOS listaIdentificadores PONTOEVIRGULA {
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = strdup($4->codigo);
        info->no = novoNoArvore("declaracao");
        adicionarFilho(info->no, novoNoArvore("VAR"));
        adicionarFilho(info->no, $2->no);
        adicionarFilho(info->no, novoNoArvore(":"));
        adicionarFilho(info->no, $4->no);
        adicionarFilho(info->no, novoNoArvore(";"));
        $$ = info;
    }
    ;

tipo:
    INTEIRO { 
        if (tipoAtual) free(tipoAtual);
        tipoAtual = strdup("int"); 
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = strdup("int ");
        info->no = novoNoArvore("INTEIRO");
        $$ = info;
    }
    | TEXTO { 
        if (tipoAtual) free(tipoAtual);
        tipoAtual = strdup("String"); 
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = strdup("String ");
        info->no = novoNoArvore("TEXTO");
        $$ = info;
    }
    | BOOLEANO { 
        if (tipoAtual) free(tipoAtual);
        tipoAtual = strdup("bool"); 
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = strdup("bool ");
        info->no = novoNoArvore("BOOLEANO");
        $$ = info;
    }
    ;

listaIdentificadores:
    IDENTIFICADOR { 
        if (!tipoAtual) { 
            yyerror("tipo não definido antes dos identificadores."); 
            YYABORT; 
        }
        if (variavelJaDeclarada($1)) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Variável '%s' já foi declarada", $1);
            yyerror(erro);
            YYABORT;
        }
        adicionarVariavel($1, tipoAtual);
        int tamanho = strlen(tipoAtual) + strlen($1) + 10;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "%s %s;\n", tipoAtual, $1);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore($1);
        $$ = info;
    }
    | listaIdentificadores VIRGULA IDENTIFICADOR {
        if (!tipoAtual) { 
            yyerror("tipo não definido antes dos identificadores."); 
            YYABORT; 
        }
        if (variavelJaDeclarada($3)) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Variável '%s' já foi declarada", $3);
            yyerror(erro);
            YYABORT;
        }
        adicionarVariavel($3, tipoAtual);
        int tamanho = strlen($1->codigo) + strlen(tipoAtual) + strlen($3) + 10;
        char *temp = malloc(tamanho);
        sprintf(temp, "%s%s %s;\n", $1->codigo, tipoAtual, $3);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = temp;
        info->no = novoNoArvore("listaIdentificadores");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, novoNoArvore(","));
        adicionarFilho(info->no, novoNoArvore($3));
        $$ = info;
    }
    ;

configuracao:
    CONFIG comandos FIM {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($2->codigo) + 50;
        char *codigo = malloc(len);
        sprintf(codigo, "\nvoid setup()\n{\n%s}\n", $2->codigo);
        info->codigo = codigo;
        info->no = novoNoArvore("configuracao");
        adicionarFilho(info->no, novoNoArvore("CONFIG"));
        adicionarFilho(info->no, $2->no);
        adicionarFilho(info->no, novoNoArvore("FIM"));
        $$ = info;
    }
    ;

comandos:
    comando { $$ = $1; }
    | comandos comando {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($1->codigo) + strlen($2->codigo) + 1;
        char *temp = malloc(len);
        strcpy(temp, $1->codigo);
        strcat(temp, $2->codigo);
        info->codigo = temp;
        info->no = novoNoArvore("comandos");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, $2->no);
        $$ = info;
    }
    ;

comando:
      atribuicao            { $$ = $1; }
    | configuracaoPino      { $$ = $1; }
    | configuracaoPWM       { $$ = $1; }
    | configuracaoSerial    { $$ = $1; }
    | conexaoWifi           { $$ = $1; }
    | controleFluxo         { $$ = $1; }
    | operacaoHardware      { $$ = $1; }
    ;

atribuicao:
    IDENTIFICADOR IGUAL expressao PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($1)) {
            YYABORT;
        }
        char *tipoVar = obterTipoVariavel($1);
        if (!verificarTipoAtribuicao($1, tipoVar, $3->codigo)) {
            YYABORT;
        }
        int tamanho = strlen($1) + strlen($3->codigo) + 10;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "%s = %s;\n", $1, $3->codigo);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("atribuicao");
        adicionarFilho(info->no, novoNoArvore($1));
        adicionarFilho(info->no, novoNoArvore("="));
        adicionarFilho(info->no, $3->no);
        adicionarFilho(info->no, novoNoArvore(";"));
        $$ = info;
    }
    | IDENTIFICADOR IGUAL LER_DIGITAL IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($1)) { YYABORT; }
        if (!verificarVariavelDeclarada($4)) { YYABORT; }
        if (!pinoEntradaConfigurado($4)) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Pino '%s' não foi configurado como entrada", $4);
            yyerror(erro);
            YYABORT;
        }
        int tamanho = strlen($1) + strlen($4) + 30;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "%s = digitalRead(%s);\n", $1, $4);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("atribuicao (LER_DIGITAL)");
        adicionarFilho(info->no, novoNoArvore($1));
        adicionarFilho(info->no, novoNoArvore("="));
        adicionarFilho(info->no, novoNoArvore("digitalRead"));
        adicionarFilho(info->no, novoNoArvore("("));
        adicionarFilho(info->no, novoNoArvore($4));
        adicionarFilho(info->no, novoNoArvore(")"));
        adicionarFilho(info->no, novoNoArvore(";"));
        $$ = info;
    }
    | IDENTIFICADOR IGUAL LER_ANALOGICO IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($1)) { YYABORT; }
        if (!verificarVariavelDeclarada($4)) { YYABORT; }
        if (!pinoEntradaConfigurado($4)) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Pino '%s' não foi configurado como entrada", $4);
            yyerror(erro);
            YYABORT;
        }
        int tamanho = strlen($1) + strlen($4) + 30;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "%s = analogRead(%s);\n", $1, $4);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("atribuicao (LER_ANALOGICO)");
        adicionarFilho(info->no, novoNoArvore($1));
        adicionarFilho(info->no, novoNoArvore("="));
        adicionarFilho(info->no, novoNoArvore("analogRead"));
        adicionarFilho(info->no, novoNoArvore("("));
        adicionarFilho(info->no, novoNoArvore($4));
        adicionarFilho(info->no, novoNoArvore(")"));
        adicionarFilho(info->no, novoNoArvore(";"));
        $$ = info;
    }
    ;

expressao:
    expressao MAIS expressao {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($1->codigo) + strlen($3->codigo) + 4;
        char *temp = malloc(len);
        sprintf(temp, "%s + %s", $1->codigo, $3->codigo);
        info->codigo = temp;
        info->no = novoNoArvore("expressao +");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, novoNoArvore("+"));
        adicionarFilho(info->no, $3->no);
        $$ = info;
    }
    | expressao MENOS expressao {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($1->codigo) + strlen($3->codigo) + 4;
        char *temp = malloc(len);
        sprintf(temp, "%s - %s", $1->codigo, $3->codigo);
        info->codigo = temp;
        info->no = novoNoArvore("expressao -");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, novoNoArvore("-"));
        adicionarFilho(info->no, $3->no);
        $$ = info;
    }
    | expressao MULTIPLICACAO expressao {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($1->codigo) + strlen($3->codigo) + 4;
        char *temp = malloc(len);
        sprintf(temp, "%s * %s", $1->codigo, $3->codigo);
        info->codigo = temp;
        info->no = novoNoArvore("expressao *");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, novoNoArvore("*"));
        adicionarFilho(info->no, $3->no);
        $$ = info;
    }
    | expressao DIVISAO expressao {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($1->codigo) + strlen($3->codigo) + 4;
        char *temp = malloc(len);
        sprintf(temp, "%s / %s", $1->codigo, $3->codigo);
        info->codigo = temp;
        info->no = novoNoArvore("expressao /");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, novoNoArvore("/"));
        adicionarFilho(info->no, $3->no);
        $$ = info;
    }
    | expressao IGUAL_IGUAL expressao {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($1->codigo) + strlen($3->codigo) + 4;
        char *temp = malloc(len);
        sprintf(temp, "%s == %s", $1->codigo, $3->codigo);
        info->codigo = temp;
        info->no = novoNoArvore("expressao ==");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, novoNoArvore("=="));
        adicionarFilho(info->no, $3->no);
        $$ = info;
    }
    | expressao DIFERENTE expressao {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($1->codigo) + strlen($3->codigo) + 4;
        char *temp = malloc(len);
        sprintf(temp, "%s != %s", $1->codigo, $3->codigo);
        info->codigo = temp;
        info->no = novoNoArvore("expressao !=");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, novoNoArvore("!="));
        adicionarFilho(info->no, $3->no);
        $$ = info;
    }
    | expressao MENOR expressao {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($1->codigo) + strlen($3->codigo) + 4;
        char *temp = malloc(len);
        sprintf(temp, "%s < %s", $1->codigo, $3->codigo);
        info->codigo = temp;
        info->no = novoNoArvore("expressao <");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, novoNoArvore("<"));
        adicionarFilho(info->no, $3->no);
        $$ = info;
    }
    | expressao MAIOR expressao {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($1->codigo) + strlen($3->codigo) + 4;
        char *temp = malloc(len);
        sprintf(temp, "%s > %s", $1->codigo, $3->codigo);
        info->codigo = temp;
        info->no = novoNoArvore("expressao >");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, novoNoArvore(">"));
        adicionarFilho(info->no, $3->no);
        $$ = info;
    }
    | expressao MENOR_IGUAL expressao {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($1->codigo) + strlen($3->codigo) + 4;
        char *temp = malloc(len);
        sprintf(temp, "%s <= %s", $1->codigo, $3->codigo);
        info->codigo = temp;
        info->no = novoNoArvore("expressao <=");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, novoNoArvore("<="));
        adicionarFilho(info->no, $3->no);
        $$ = info;
    }
    | expressao MAIOR_IGUAL expressao {
        SemInfo *info = malloc(sizeof(SemInfo));
        int len = strlen($1->codigo) + strlen($3->codigo) + 4;
        char *temp = malloc(len);
        sprintf(temp, "%s >= %s", $1->codigo, $3->codigo);
        info->codigo = temp;
        info->no = novoNoArvore("expressao >=");
        adicionarFilho(info->no, $1->no);
        adicionarFilho(info->no, novoNoArvore(">="));
        adicionarFilho(info->no, $3->no);
        $$ = info;
    }
    | NUMERO {
        SemInfo *info = malloc(sizeof(SemInfo));
        char buffer[20];
        sprintf(buffer, "%d", $1);
        info->codigo = strdup(buffer);
        info->no = novoNoArvore(buffer);
        $$ = info;
    }
    | IDENTIFICADOR {
        if (!verificarVariavelDeclarada($1)) {
            YYABORT;
        }
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = strdup($1);
        info->no = novoNoArvore($1);
        $$ = info;
    }
    | STRING {
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = strdup($1);
        info->no = novoNoArvore($1);
        $$ = info;
    }
    ;

configuracaoPino:
    CONFIGURAR IDENTIFICADOR COMO SAIDA PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) { YYABORT; }
        adicionarPinoSaida($2);
        int tamanho = strlen($2) + 30;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "pinMode(%s, OUTPUT);\n", $2);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("configuracaoPino (SAIDA)");
        adicionarFilho(info->no, novoNoArvore("CONFIGURAR"));
        adicionarFilho(info->no, novoNoArvore($2));
        adicionarFilho(info->no, novoNoArvore("COMO"));
        adicionarFilho(info->no, novoNoArvore("SAIDA"));
        adicionarFilho(info->no, novoNoArvore(";"));
        $$ = info;
    }
    | CONFIGURAR IDENTIFICADOR COMO ENTRADA PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) { YYABORT; }
        adicionarPinoEntrada($2);
        int tamanho = strlen($2) + 30;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "pinMode(%s, INPUT);\n", $2);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("configuracaoPino (ENTRADA)");
        adicionarFilho(info->no, novoNoArvore("CONFIGURAR"));
        adicionarFilho(info->no, novoNoArvore($2));
        adicionarFilho(info->no, novoNoArvore("COMO"));
        adicionarFilho(info->no, novoNoArvore("ENTRADA"));
        adicionarFilho(info->no, novoNoArvore(";"));
        $$ = info;
    }
    ;

configuracaoPWM:
    CONFIGURARPWM IDENTIFICADOR COM FREQUENCIA NUMERO RESOLUCAO NUMERO PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) { YYABORT; }
        adicionarPinoPWM($2);
        char constantes[200];
        char codigo[200];
        sprintf(constantes, "\nconst int canalPWM = 0;\nconst int frequencia = %d;\nconst int resolucao = %d;\n", $5, $7);
        acrescentarConstantes(constantes);
        sprintf(codigo, "ledcSetup(canalPWM, frequencia, resolucao);\nledcAttachPin(%s, canalPWM);\n", $2);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = strdup(codigo);
        info->no = novoNoArvore("configuracaoPWM");
        adicionarFilho(info->no, novoNoArvore("CONFIGURARPWM"));
        adicionarFilho(info->no, novoNoArvore($2));
        adicionarFilho(info->no, novoNoArvore("COM FREQUENCIA"));
        adicionarFilho(info->no, novoNoArvore("NUMERO"));
        adicionarFilho(info->no, novoNoArvore("RESOLUCAO"));
        adicionarFilho(info->no, novoNoArvore("PONTOEVIRGULA"));
        $$ = info;
    }
    ;

configuracaoSerial:
    CONFIGURARSERIAL NUMERO PONTOEVIRGULA {
        int tamanho = 50;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "Serial.begin(%d);\n", $2);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("configuracaoSerial");
        adicionarFilho(info->no, novoNoArvore("CONFIGURARSERIAL"));
        adicionarFilho(info->no, novoNoArvore("NUMERO"));
        adicionarFilho(info->no, novoNoArvore("PONTOEVIRGULA"));
        $$ = info;
    }
    ;

conexaoWifi:
    CONECTARWIFI IDENTIFICADOR IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) { YYABORT; }
        if (!verificarVariavelDeclarada($3)) { YYABORT; }
        int tamanho = strlen($2) + strlen($3) + 170;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "WiFi.begin(%s.c_str(), %s.c_str());\nwhile (WiFi.status() != WL_CONNECTED)\n{\n    delay(500);\n    Serial.println(\"Conectando ao WiFi...\");\n}\nSerial.println(\"Conectado ao WiFi!\");\n", $2, $3);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("conexaoWifi");
        adicionarFilho(info->no, novoNoArvore("CONECTARWIFI"));
        adicionarFilho(info->no, novoNoArvore($2));
        adicionarFilho(info->no, novoNoArvore($3));
        adicionarFilho(info->no, novoNoArvore("PONTOEVIRGULA"));
        $$ = info;
    }
    ;

controleFluxo:
    condicional { $$ = $1; }
    | repeticao { $$ = $1; }
    ;

condicional:
    SE expressao ENTAO comandos SENAO comandos FIM {
        int tamanho = strlen($2->codigo) + strlen($4->codigo) + strlen($6->codigo) + 50;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "if (%s)\n{\n%s}\nelse\n{\n%s}\n", $2->codigo, $4->codigo, $6->codigo);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("condicional");
        adicionarFilho(info->no, novoNoArvore("SE"));
        adicionarFilho(info->no, $2->no);
        adicionarFilho(info->no, novoNoArvore("ENTAO"));
        adicionarFilho(info->no, $4->no);
        adicionarFilho(info->no, novoNoArvore("SENAO"));
        adicionarFilho(info->no, $6->no);
        adicionarFilho(info->no, novoNoArvore("FIM"));
        $$ = info;
    }
    | SE expressao ENTAO comandos FIM {
        int tamanho = strlen($2->codigo) + strlen($4->codigo) + 30;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "if (%s)\n{\n%s}\n", $2->codigo, $4->codigo);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("condicional");
        adicionarFilho(info->no, novoNoArvore("SE"));
        adicionarFilho(info->no, $2->no);
        adicionarFilho(info->no, novoNoArvore("ENTAO"));
        adicionarFilho(info->no, $4->no);
        adicionarFilho(info->no, novoNoArvore("FIM"));
        $$ = info;
    }
    ;

repeticao:
    ENQUANTO expressao FIM comandos FIM {
        int tamanho = strlen($2->codigo) + strlen($4->codigo) + 30;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "while (%s)\n{\n%s}\n", $2->codigo, $4->codigo);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("repeticao");
        adicionarFilho(info->no, novoNoArvore("ENQUANTO"));
        adicionarFilho(info->no, $2->no);
        adicionarFilho(info->no, novoNoArvore("FIM"));
        adicionarFilho(info->no, $4->no);
        adicionarFilho(info->no, novoNoArvore("FIM"));
        $$ = info;
    }
    ;

operacaoHardware:
    LIGAR IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) { YYABORT; }
        if (!pinoSaidaConfigurado($2)) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Pino '%s' não foi configurado como saída", $2);
            yyerror(erro);
            YYABORT;
        }
        int tamanho = strlen($2) + 20;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "digitalWrite(%s, HIGH);\n", $2);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("operacaoHardware (LIGAR)");
        adicionarFilho(info->no, novoNoArvore("LIGAR"));
        adicionarFilho(info->no, novoNoArvore($2));
        adicionarFilho(info->no, novoNoArvore("PONTOEVIRGULA"));
        $$ = info;
    }
    | DESLIGAR IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) { YYABORT; }
        if (!pinoSaidaConfigurado($2)) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Pino '%s' não foi configurado como saída", $2);
            yyerror(erro);
            YYABORT;
        }
        int tamanho = strlen($2) + 25;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "digitalWrite(%s, LOW);\n", $2);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("operacaoHardware (DESLIGAR)");
        adicionarFilho(info->no, novoNoArvore("DESLIGAR"));
        adicionarFilho(info->no, novoNoArvore($2));
        adicionarFilho(info->no, novoNoArvore("PONTOEVIRGULA"));
        $$ = info;
    }
    | AJUSTARPWM IDENTIFICADOR COM VALOR IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) { YYABORT; }
        if (!pinoPWMConfigurado($2)) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Pino '%s' não foi configurado para PWM", $2);
            yyerror(erro);
            YYABORT;
        }
        if (!verificarVariavelDeclarada($5)) { YYABORT; }
        int tamanho = strlen($2) + strlen($5) + 40;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "ledcWrite(%s, %s);\n", $2, $5);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("operacaoHardware (AJUSTARPWM)");
        adicionarFilho(info->no, novoNoArvore("AJUSTARPWM"));
        adicionarFilho(info->no, novoNoArvore($2));
        adicionarFilho(info->no, novoNoArvore("COM"));
        adicionarFilho(info->no, novoNoArvore("VALOR"));
        adicionarFilho(info->no, novoNoArvore($5));
        adicionarFilho(info->no, novoNoArvore("PONTOEVIRGULA"));
        $$ = info;
    }
    | ESPERAR NUMERO PONTOEVIRGULA {
        int tamanho = 20;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "delay(%d);\n", $2);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("operacaoHardware (ESPERAR)");
        adicionarFilho(info->no, novoNoArvore("ESPERAR"));
        adicionarFilho(info->no, novoNoArvore("NUMERO"));
        adicionarFilho(info->no, novoNoArvore("PONTOEVIRGULA"));
        $$ = info;
    }
    | ESCREVER_SERIAL expressao PONTOEVIRGULA {
        int tamanho = strlen($2->codigo) + 30;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "Serial.println(%s);\n", $2->codigo);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("operacaoHardware (ESCREVER_SERIAL)");
        adicionarFilho(info->no, novoNoArvore("ESCREVER_SERIAL"));
        adicionarFilho(info->no, $2->no);
        adicionarFilho(info->no, novoNoArvore("PONTOEVIRGULA"));
        $$ = info;
    }
    | LER_SERIAL IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) { YYABORT; }
        int tamanho = strlen($2) + 30;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "%s = Serial.readString();\n", $2);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("operacaoHardware (LER_SERIAL)");
        adicionarFilho(info->no, novoNoArvore("LER_SERIAL"));
        adicionarFilho(info->no, novoNoArvore($2));
        adicionarFilho(info->no, novoNoArvore("PONTOEVIRGULA"));
        $$ = info;
    }
    | ENVIAR_HTTP expressao expressao PONTOEVIRGULA {
        int tamanho = strlen($2->codigo) + strlen($3->codigo) + 500;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "if (WiFi.status() == WL_CONNECTED)\n{\n    http.begin(%s);\n    int httpResponseCode = http.GET();\n    if (httpResponseCode > 0) {\n        Serial.print(\"Resposta HTTP: \");\n        Serial.println(httpResponseCode);\n    } else {\n        Serial.print(\"Erro na requisição: \");\n        Serial.println(httpResponseCode);\n    }\n    http.end();\n} else {\n    Serial.println(\"WiFi desconectado, tentando reconectar...\");\n    WiFi.begin(%s, %s);\n}\n", $2->codigo, $2->codigo, $3->codigo);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("operacaoHardware (ENVIAR_HTTP)");
        adicionarFilho(info->no, novoNoArvore("ENVIAR_HTTP"));
        adicionarFilho(info->no, $2->no);
        adicionarFilho(info->no, $3->no);
        adicionarFilho(info->no, novoNoArvore("PONTOEVIRGULA"));
        $$ = info;
    }
    | LER_DIGITAL IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) { YYABORT; }
        int tamanho = strlen($2) + 30;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "%s = digitalRead(%s);\n", $2, $2);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("operacaoHardware (LER_DIGITAL)");
        adicionarFilho(info->no, novoNoArvore("LER_DIGITAL"));
        adicionarFilho(info->no, novoNoArvore($2));
        adicionarFilho(info->no, novoNoArvore("PONTOEVIRGULA"));
        $$ = info;
    }
    | LER_ANALOGICO IDENTIFICADOR PONTOEVIRGULA {
        if (!verificarVariavelDeclarada($2)) { YYABORT; }
        int tamanho = strlen($2) + 30;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "%s = analogRead(%s);\n", $2, $2);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("operacaoHardware (LER_ANALOGICO)");
        adicionarFilho(info->no, novoNoArvore("LER_ANALOGICO"));
        adicionarFilho(info->no, novoNoArvore($2));
        adicionarFilho(info->no, novoNoArvore("PONTOEVIRGULA"));
        $$ = info;
    }
    ;

loop:
    REPITA comandos FIM {
        int tamanho = strlen($2->codigo) + 30;
        char *codigo = malloc(tamanho);
        sprintf(codigo, "\nvoid loop()\n{\n%s}\n", $2->codigo);
        SemInfo *info = malloc(sizeof(SemInfo));
        info->codigo = codigo;
        info->no = novoNoArvore("loop");
        adicionarFilho(info->no, novoNoArvore("REPITA"));
        adicionarFilho(info->no, $2->no);
        adicionarFilho(info->no, novoNoArvore("FIM"));
        $$ = info;
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
        char nomeBase[256];
        char *entrada = argv[1];
        /* Extrai apenas o nome do arquivo (removendo o caminho) */
        char *nomeArquivo = strrchr(entrada, '/');
        nomeArquivo = (nomeArquivo) ? nomeArquivo + 1 : entrada;
        /* Copia para nomeBase e remove a extensão, se houver */
        strncpy(nomeBase, nomeArquivo, sizeof(nomeBase));
        nomeBase[sizeof(nomeBase) - 1] = '\0';
        char *ponto = strrchr(nomeBase, '.');
        if (ponto) {
            *ponto = '\0';
        }

        /* Monta o nome do arquivo cpp, por exemplo: langs/exemplo_codigo.cpp */
        char saidaCpp[256];
        snprintf(saidaCpp, sizeof(saidaCpp), "langs/%s_codigo.cpp", nomeBase);

        FILE *arquivo = fopen(saidaCpp, "w");
        if (arquivo) {
            fprintf(arquivo, "%s", codigoGerado);
            fclose(arquivo);
        } else {
            perror("Erro ao criar o arquivo de saída");
        }
        free(codigoGerado);
    }

    /* Exporta a árvore sintática para um arquivo com nome baseado no arquivo de entrada */
    if (arvoreSintatica) {
        char nomeBase[256];
        char *nomeArquivo = strrchr(argv[1], '/');
        nomeArquivo = (nomeArquivo) ? nomeArquivo + 1 : argv[1];
        strncpy(nomeBase, nomeArquivo, sizeof(nomeBase));
        nomeBase[sizeof(nomeBase)-1] = '\0';
        
        /* Remove a extensão, se houver */
        char *ponto = strrchr(nomeBase, '.');
        if (ponto) {
            *ponto = '\0';
        }

        /* Monta o nome do arquivo da árvore, por exemplo: langs/exemplo_arvore.txt */
        char saidaArvore[256];
        snprintf(saidaArvore, sizeof(saidaArvore), "langs/%s_arvore.txt", nomeBase);

        FILE *arquivoArvore = fopen(saidaArvore, "w");
        if (arquivoArvore) {
            exportarArvoreParaArquivo(arvoreSintatica, 0, arquivoArvore);
            fclose(arquivoArvore);
            printf("Árvore sintática exportada para: %s\n", saidaArvore);
        } else {
            perror("Erro ao criar o arquivo de visualização da árvore");
        }
        liberarArvore(arvoreSintatica);
    }

    liberarVariaveis();
    liberarPinosPWM();
    liberarPinosEntrada();
    liberarPinosSaida();
    return 0;
}