#!/bin/bash

# Verifica se o Flex e Bison estão instalados
if ! command -v flex &> /dev/null; then
    echo "Flex não encontrado. Instale o Flex para continuar."
    exit 1
fi

if ! command -v bison &> /dev/null; then
    echo "Bison não encontrado. Instale o Bison para continuar."
    exit 1
fi

# Diretório onde os arquivos serão gerados
SRC_DIR="src"
TEMP_DIR="temp"

# Função para verificar e criar o diretório temp, se necessário
create_temp_dir() {
    if [ ! -d "$TEMP_DIR" ]; then
        echo "Diretório $TEMP_DIR não encontrado. Criando..."
        mkdir -p "$TEMP_DIR"
        if [ $? -ne 0 ]; then
            echo "Erro ao criar o diretório $TEMP_DIR"
            exit 1
        fi
        echo "Diretório $TEMP_DIR criado com sucesso."
    fi
}

# Cria o diretório temp, se necessário
create_temp_dir

# Gera o código do lexer com o Flex
echo "Gerando lexer com o Flex..."
flex -o $TEMP_DIR/lex.yy.c $SRC_DIR/lexer.l
if [ $? -ne 0 ]; then
    echo "Erro na geração do lexer com o Flex"
    exit 1
fi

# Gera o código do parser com o Bison
echo "Gerando parser com o Bison..."
bison -d -o $TEMP_DIR/parser.tab.c $SRC_DIR/parser.y
if [ $? -ne 0 ]; then
    echo "Erro na geração do parser com o Bison"
    exit 1
fi

# Compila o código gerado pelo Flex e Bison
echo "Compilando o código gerado..."
gcc $TEMP_DIR/lex.yy.c $TEMP_DIR/parser.tab.c -o compiler
if [ $? -ne 0 ]; then
    echo "Erro na compilação do código"
    exit 1
fi

# Mensagem de sucesso
echo "Compilador gerado com sucesso! Execute com ./compiler"