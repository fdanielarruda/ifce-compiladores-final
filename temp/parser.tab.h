/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2021 Free Software Foundation,
   Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <https://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

#ifndef YY_YY_TEMP_PARSER_TAB_H_INCLUDED
# define YY_YY_TEMP_PARSER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token kinds.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    YYEMPTY = -2,
    YYEOF = 0,                     /* "end of file"  */
    YYerror = 256,                 /* error  */
    YYUNDEF = 257,                 /* "invalid token"  */
    IDENTIFICADOR = 258,           /* IDENTIFICADOR  */
    NUMERO = 259,                  /* NUMERO  */
    STRING = 260,                  /* STRING  */
    VAR = 261,                     /* VAR  */
    INTEIRO = 262,                 /* INTEIRO  */
    TEXTO = 263,                   /* TEXTO  */
    BOOLEANO = 264,                /* BOOLEANO  */
    CONFIG = 265,                  /* CONFIG  */
    CONFIGURAR = 266,              /* CONFIGURAR  */
    CONFIGURARPWM = 267,           /* CONFIGURARPWM  */
    CONFIGURARSERIAL = 268,        /* CONFIGURARSERIAL  */
    CONECTARWIFI = 269,            /* CONECTARWIFI  */
    LIGAR = 270,                   /* LIGAR  */
    DESLIGAR = 271,                /* DESLIGAR  */
    AJUSTARPWM = 272,              /* AJUSTARPWM  */
    ESPERAR = 273,                 /* ESPERAR  */
    ESCREVER_SERIAL = 274,         /* ESCREVER_SERIAL  */
    LER_SERIAL = 275,              /* LER_SERIAL  */
    ENVIAR_HTTP = 276,             /* ENVIAR_HTTP  */
    LER_DIGITAL = 277,             /* LER_DIGITAL  */
    LER_ANALOGICO = 278,           /* LER_ANALOGICO  */
    SE = 279,                      /* SE  */
    SENAO = 280,                   /* SENAO  */
    ENTAO = 281,                   /* ENTAO  */
    ENQUANTO = 282,                /* ENQUANTO  */
    REPITA = 283,                  /* REPITA  */
    FIM = 284,                     /* FIM  */
    COM = 285,                     /* COM  */
    COMO = 286,                    /* COMO  */
    SAIDA = 287,                   /* SAIDA  */
    FREQUENCIA = 288,              /* FREQUENCIA  */
    RESOLUCAO = 289,               /* RESOLUCAO  */
    IGUAL = 290,                   /* IGUAL  */
    IGUAL_IGUAL = 291,             /* IGUAL_IGUAL  */
    DIFERENTE = 292,               /* DIFERENTE  */
    MENOR = 293,                   /* MENOR  */
    MAIOR = 294,                   /* MAIOR  */
    MENOR_IGUAL = 295,             /* MENOR_IGUAL  */
    MAIOR_IGUAL = 296,             /* MAIOR_IGUAL  */
    MAIS = 297,                    /* MAIS  */
    MENOS = 298,                   /* MENOS  */
    MULTIPLICACAO = 299,           /* MULTIPLICACAO  */
    DIVISAO = 300,                 /* DIVISAO  */
    MODULO = 301,                  /* MODULO  */
    VIRGULA = 302,                 /* VIRGULA  */
    PONTOEVIRGULA = 303,           /* PONTOEVIRGULA  */
    DOISPONTOS = 304,              /* DOISPONTOS  */
    VALOR = 305                    /* VALOR  */
  };
  typedef enum yytokentype yytoken_kind_t;
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 41 "src/parser.y"

    char *str;
    int num;
    char *id;

#line 120 "temp/parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;


int yyparse (void);


#endif /* !YY_YY_TEMP_PARSER_TAB_H_INCLUDED  */
