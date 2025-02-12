# Compilador Personalizado

Este projeto é um compilador personalizado que utiliza **Flex** para análise léxica e **Bison** para análise sintática.

## Requisitos

Antes de compilar e executar o compilador, certifique-se de que os seguintes pacotes estão instalados no seu sistema Ubuntu:

```sh
sudo apt update
sudo apt install flex bison gcc -y
```

## Compilação

Após instalar as dependências, siga os passos abaixo para compilar o compilador:

```sh
flex lexer.l
bison -d parser.y
gcc lex.yy.c parser.tab.c -o compilador
```

Isso gerará um executável chamado `compilador`.

## Execução

Para executar o compilador, use o seguinte comando:

```sh
./compilador proposta/personalizado
```

O arquivo `proposta/personalizado` deve conter o código-fonte na linguagem personalizada a ser analisado pelo compilador.

## Estrutura do Projeto

- `lexer.l`: Definições da análise léxica (tokens).
- `parser.y`: Definições da análise sintática e geração de código.
- `lex.yy.c`: Código gerado pelo **Flex**.
- `parser.tab.c` e `parser.tab.h`: Código gerado pelo **Bison**.
- `compilador`: Executável final.

## Observações

Caso tenha problemas com permissões ao executar `./compilador`, use:

```sh
chmod +x compilador
```

Se precisar de mais informações sobre Flex e Bison:
- [Flex Documentation](https://westes.github.io/flex/manual/)
- [Bison Documentation](https://www.gnu.org/software/bison/manual/)

---
**Desenvolvido para o projeto de compiladores no IFCE.**

