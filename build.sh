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

# Gera o código do lexer com o Flex
echo "Gerando lexer com o Flex..."
flex lexer.l
if [ $? -ne 0 ]; then
    echo "Erro na geração do lexer com o Flex"
    exit 1
fi

# Gera o código do parser com o Bison
echo "Gerando parser com o Bison..."
bison -d parser.y
if [ $? -ne 0 ]; then
    echo "Erro na geração do parser com o Bison"
    exit 1
fi

# Compila o código gerado pelo Flex e Bison
echo "Compilando o código gerado..."
gcc lex.yy.c parser.tab.c -o compilador
if [ $? -ne 0 ]; then
    echo "Erro na compilação do código"
    exit 1
fi

# Mensagem de sucesso
echo "Compilador gerado com sucesso! Execute com ./compilador"
