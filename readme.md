# Compilador Personalizado

Este projeto é um compilador personalizado que utiliza **Flex** para análise léxica e **Bison** para análise sintática.

## Requisitos

Antes de compilar e executar o compilador, certifique-se de que os seguintes pacotes estão instalados no seu sistema Ubuntu:

```sh
sudo apt update
sudo apt install flex bison gcc -y
```

## Compilação

Após instalar as dependências, basta executar o seguinte comando para compilar o compilador:

```sh
./build.sh
```

Isso gerará o executável `compiler`.

## Execução

Para executar o compilador, utilize o comando:

```sh
./compiler langs/example1.lang
```

O arquivo `langs/example1.lang` deve conter o código-fonte na linguagem personalizada a ser analisado pelo compilador.

## Estrutura do Projeto

- `lexer.l`: Definições da análise léxica (tokens).
- `parser.y`: Definições da análise sintática e geração de código.
- `lex.yy.c`: Código gerado pelo **Flex**.
- `parser.tab.c` e `parser.tab.h`: Código gerado pelo **Bison**.
- `build.sh`: Script para compilar o projeto.
- `compiler`: Executável final.

## Observações

Caso tenha problemas com permissões ao executar `./compiler`, utilize:

```sh
chmod +x compiler
```

Se precisar de mais informações sobre Flex e Bison:
- [Flex Documentation](https://westes.github.io/flex/manual/)
- [Bison Documentation](https://www.gnu.org/software/bison/manual/)

---
**Desenvolvido para o projeto de compiladores no IFCE.**