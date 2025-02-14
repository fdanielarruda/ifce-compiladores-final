/* A Bison parser, made by GNU Bison 3.8.2.  */

/* Bison implementation for Yacc-like parsers in C

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

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
   especially those whose name start with YY_ or yy_.  They are
   private implementation details that can be changed or removed.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output, and Bison version.  */
#define YYBISON 30802

/* Bison version string.  */
#define YYBISON_VERSION "3.8.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 1 "src/parser.y"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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
    return NULL; // Caso a variável não tenha sido declarada
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
            fprintf(stderr, "Falha na alocação de memória\n");
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

int verificarTipoAtribuicao(char *nomeVar, char *tipoVar, char *valor) {
    int tipoValor = 0; // 0: indefinido, 1: inteiro, 2: string

    // Verificar se "valor" é um número inteiro
    char *endptr;
    strtol(valor, &endptr, 10);

    if (*endptr == '\0') {
        tipoValor = 1; // inteiro
    }

    // Verificar se "valor" é uma string (começa e termina com aspas)
    else if (valor[0] == '"' && valor[strlen(valor) - 1] == '"') {
        tipoValor = 2; // string
    }

    // Comparar tipos e gerar mensagem de erro
    if (strcmp(tipoVar, "int") == 0 && tipoValor != 1) {
        char mensagem[256];
        snprintf(mensagem, sizeof(mensagem), "Tipos incompatíveis na atribuição. A variável '%s' deve ser do tipo %s.", nomeVar, tipoVar);
        yyerror(mensagem);
        return 0;
    }

    if (strcmp(tipoVar, "String") == 0 && tipoValor != 2) {
        char mensagem[256];
        snprintf(mensagem, sizeof(mensagem), "Tipos incompatíveis na atribuição. A variável '%s' deve ser do tipo %s.", nomeVar, tipoVar);
        yyerror(mensagem);
        return 0;
    }

    return 1;
}


#line 236 "temp/parser.tab.c"

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

#include "parser.tab.h"
/* Symbol kind.  */
enum yysymbol_kind_t
{
  YYSYMBOL_YYEMPTY = -2,
  YYSYMBOL_YYEOF = 0,                      /* "end of file"  */
  YYSYMBOL_YYerror = 1,                    /* error  */
  YYSYMBOL_YYUNDEF = 2,                    /* "invalid token"  */
  YYSYMBOL_IDENTIFICADOR = 3,              /* IDENTIFICADOR  */
  YYSYMBOL_NUMERO = 4,                     /* NUMERO  */
  YYSYMBOL_STRING = 5,                     /* STRING  */
  YYSYMBOL_VAR = 6,                        /* VAR  */
  YYSYMBOL_INTEIRO = 7,                    /* INTEIRO  */
  YYSYMBOL_TEXTO = 8,                      /* TEXTO  */
  YYSYMBOL_BOOLEANO = 9,                   /* BOOLEANO  */
  YYSYMBOL_CONFIG = 10,                    /* CONFIG  */
  YYSYMBOL_CONFIGURAR = 11,                /* CONFIGURAR  */
  YYSYMBOL_CONFIGURARPWM = 12,             /* CONFIGURARPWM  */
  YYSYMBOL_CONFIGURARSERIAL = 13,          /* CONFIGURARSERIAL  */
  YYSYMBOL_CONECTARWIFI = 14,              /* CONECTARWIFI  */
  YYSYMBOL_LIGAR = 15,                     /* LIGAR  */
  YYSYMBOL_DESLIGAR = 16,                  /* DESLIGAR  */
  YYSYMBOL_AJUSTARPWM = 17,                /* AJUSTARPWM  */
  YYSYMBOL_ESPERAR = 18,                   /* ESPERAR  */
  YYSYMBOL_ESCREVER_SERIAL = 19,           /* ESCREVER_SERIAL  */
  YYSYMBOL_LER_SERIAL = 20,                /* LER_SERIAL  */
  YYSYMBOL_ENVIAR_HTTP = 21,               /* ENVIAR_HTTP  */
  YYSYMBOL_LER_DIGITAL = 22,               /* LER_DIGITAL  */
  YYSYMBOL_LER_ANALOGICO = 23,             /* LER_ANALOGICO  */
  YYSYMBOL_SE = 24,                        /* SE  */
  YYSYMBOL_SENAO = 25,                     /* SENAO  */
  YYSYMBOL_ENTAO = 26,                     /* ENTAO  */
  YYSYMBOL_ENQUANTO = 27,                  /* ENQUANTO  */
  YYSYMBOL_REPITA = 28,                    /* REPITA  */
  YYSYMBOL_FIM = 29,                       /* FIM  */
  YYSYMBOL_COM = 30,                       /* COM  */
  YYSYMBOL_COMO = 31,                      /* COMO  */
  YYSYMBOL_SAIDA = 32,                     /* SAIDA  */
  YYSYMBOL_ENTRADA = 33,                   /* ENTRADA  */
  YYSYMBOL_FREQUENCIA = 34,                /* FREQUENCIA  */
  YYSYMBOL_RESOLUCAO = 35,                 /* RESOLUCAO  */
  YYSYMBOL_IGUAL = 36,                     /* IGUAL  */
  YYSYMBOL_IGUAL_IGUAL = 37,               /* IGUAL_IGUAL  */
  YYSYMBOL_DIFERENTE = 38,                 /* DIFERENTE  */
  YYSYMBOL_MENOR = 39,                     /* MENOR  */
  YYSYMBOL_MAIOR = 40,                     /* MAIOR  */
  YYSYMBOL_MENOR_IGUAL = 41,               /* MENOR_IGUAL  */
  YYSYMBOL_MAIOR_IGUAL = 42,               /* MAIOR_IGUAL  */
  YYSYMBOL_MAIS = 43,                      /* MAIS  */
  YYSYMBOL_MENOS = 44,                     /* MENOS  */
  YYSYMBOL_MULTIPLICACAO = 45,             /* MULTIPLICACAO  */
  YYSYMBOL_DIVISAO = 46,                   /* DIVISAO  */
  YYSYMBOL_MODULO = 47,                    /* MODULO  */
  YYSYMBOL_VIRGULA = 48,                   /* VIRGULA  */
  YYSYMBOL_PONTOEVIRGULA = 49,             /* PONTOEVIRGULA  */
  YYSYMBOL_DOISPONTOS = 50,                /* DOISPONTOS  */
  YYSYMBOL_VALOR = 51,                     /* VALOR  */
  YYSYMBOL_YYACCEPT = 52,                  /* $accept  */
  YYSYMBOL_programa = 53,                  /* programa  */
  YYSYMBOL_declaracoes = 54,               /* declaracoes  */
  YYSYMBOL_declaracao = 55,                /* declaracao  */
  YYSYMBOL_tipo = 56,                      /* tipo  */
  YYSYMBOL_listaIdentificadores = 57,      /* listaIdentificadores  */
  YYSYMBOL_configuracao = 58,              /* configuracao  */
  YYSYMBOL_comandos = 59,                  /* comandos  */
  YYSYMBOL_comando = 60,                   /* comando  */
  YYSYMBOL_atribuicao = 61,                /* atribuicao  */
  YYSYMBOL_expressao = 62,                 /* expressao  */
  YYSYMBOL_configuracaoPino = 63,          /* configuracaoPino  */
  YYSYMBOL_configuracaoPWM = 64,           /* configuracaoPWM  */
  YYSYMBOL_configuracaoSerial = 65,        /* configuracaoSerial  */
  YYSYMBOL_conexaoWifi = 66,               /* conexaoWifi  */
  YYSYMBOL_controleFluxo = 67,             /* controleFluxo  */
  YYSYMBOL_condicional = 68,               /* condicional  */
  YYSYMBOL_repeticao = 69,                 /* repeticao  */
  YYSYMBOL_operacaoHardware = 70,          /* operacaoHardware  */
  YYSYMBOL_loop = 71                       /* loop  */
};
typedef enum yysymbol_kind_t yysymbol_kind_t;




#ifdef short
# undef short
#endif

/* On compilers that do not define __PTRDIFF_MAX__ etc., make sure
   <limits.h> and (if available) <stdint.h> are included
   so that the code can choose integer types of a good width.  */

#ifndef __PTRDIFF_MAX__
# include <limits.h> /* INFRINGES ON USER NAME SPACE */
# if defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stdint.h> /* INFRINGES ON USER NAME SPACE */
#  define YY_STDINT_H
# endif
#endif

/* Narrow types that promote to a signed type and that can represent a
   signed or unsigned integer of at least N bits.  In tables they can
   save space and decrease cache pressure.  Promoting to a signed type
   helps avoid bugs in integer arithmetic.  */

#ifdef __INT_LEAST8_MAX__
typedef __INT_LEAST8_TYPE__ yytype_int8;
#elif defined YY_STDINT_H
typedef int_least8_t yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef __INT_LEAST16_MAX__
typedef __INT_LEAST16_TYPE__ yytype_int16;
#elif defined YY_STDINT_H
typedef int_least16_t yytype_int16;
#else
typedef short yytype_int16;
#endif

/* Work around bug in HP-UX 11.23, which defines these macros
   incorrectly for preprocessor constants.  This workaround can likely
   be removed in 2023, as HPE has promised support for HP-UX 11.23
   (aka HP-UX 11i v2) only through the end of 2022; see Table 2 of
   <https://h20195.www2.hpe.com/V2/getpdf.aspx/4AA4-7673ENW.pdf>.  */
#ifdef __hpux
# undef UINT_LEAST8_MAX
# undef UINT_LEAST16_MAX
# define UINT_LEAST8_MAX 255
# define UINT_LEAST16_MAX 65535
#endif

#if defined __UINT_LEAST8_MAX__ && __UINT_LEAST8_MAX__ <= __INT_MAX__
typedef __UINT_LEAST8_TYPE__ yytype_uint8;
#elif (!defined __UINT_LEAST8_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST8_MAX <= INT_MAX)
typedef uint_least8_t yytype_uint8;
#elif !defined __UINT_LEAST8_MAX__ && UCHAR_MAX <= INT_MAX
typedef unsigned char yytype_uint8;
#else
typedef short yytype_uint8;
#endif

#if defined __UINT_LEAST16_MAX__ && __UINT_LEAST16_MAX__ <= __INT_MAX__
typedef __UINT_LEAST16_TYPE__ yytype_uint16;
#elif (!defined __UINT_LEAST16_MAX__ && defined YY_STDINT_H \
       && UINT_LEAST16_MAX <= INT_MAX)
typedef uint_least16_t yytype_uint16;
#elif !defined __UINT_LEAST16_MAX__ && USHRT_MAX <= INT_MAX
typedef unsigned short yytype_uint16;
#else
typedef int yytype_uint16;
#endif

#ifndef YYPTRDIFF_T
# if defined __PTRDIFF_TYPE__ && defined __PTRDIFF_MAX__
#  define YYPTRDIFF_T __PTRDIFF_TYPE__
#  define YYPTRDIFF_MAXIMUM __PTRDIFF_MAX__
# elif defined PTRDIFF_MAX
#  ifndef ptrdiff_t
#   include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  endif
#  define YYPTRDIFF_T ptrdiff_t
#  define YYPTRDIFF_MAXIMUM PTRDIFF_MAX
# else
#  define YYPTRDIFF_T long
#  define YYPTRDIFF_MAXIMUM LONG_MAX
# endif
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif defined __STDC_VERSION__ && 199901 <= __STDC_VERSION__
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned
# endif
#endif

#define YYSIZE_MAXIMUM                                  \
  YY_CAST (YYPTRDIFF_T,                                 \
           (YYPTRDIFF_MAXIMUM < YY_CAST (YYSIZE_T, -1)  \
            ? YYPTRDIFF_MAXIMUM                         \
            : YY_CAST (YYSIZE_T, -1)))

#define YYSIZEOF(X) YY_CAST (YYPTRDIFF_T, sizeof (X))


/* Stored state numbers (used for stacks). */
typedef yytype_uint8 yy_state_t;

/* State numbers in computations.  */
typedef int yy_state_fast_t;

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif


#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif


#define YY_ASSERT(E) ((void) (0 && (E)))

#if !defined yyoverflow

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* !defined yyoverflow */

#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYPTRDIFF_T yynewbytes;                                         \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * YYSIZEOF (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / YYSIZEOF (*yyptr);                        \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, YY_CAST (YYSIZE_T, (Count)) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYPTRDIFF_T yyi;                      \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   268

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  56
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  135

/* YYMAXUTOK -- Last valid token kind.  */
#define YYMAXUTOK   306


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK                     \
   ? YY_CAST (yysymbol_kind_t, yytranslate[YYX])        \
   : YYSYMBOL_YYUNDEF)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51
};

#if YYDEBUG
/* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,   202,   202,   210,   211,   219,   225,   230,   235,   243,
     264,   288,   296,   297,   306,   307,   308,   309,   310,   311,
     312,   316,   333,   344,   358,   365,   372,   379,   386,   390,
     394,   398,   402,   406,   410,   414,   420,   426,   434,   445,
     461,   469,   483,   484,   488,   493,   501,   509,   517,   525,
     536,   541,   546,   554,   559,   567,   578
};
#endif

/** Accessing symbol of state STATE.  */
#define YY_ACCESSING_SYMBOL(State) YY_CAST (yysymbol_kind_t, yystos[State])

#if YYDEBUG || 0
/* The user-facing name of the symbol whose (internal) number is
   YYSYMBOL.  No bounds checking.  */
static const char *yysymbol_name (yysymbol_kind_t yysymbol) YY_ATTRIBUTE_UNUSED;

/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "\"end of file\"", "error", "\"invalid token\"", "IDENTIFICADOR",
  "NUMERO", "STRING", "VAR", "INTEIRO", "TEXTO", "BOOLEANO", "CONFIG",
  "CONFIGURAR", "CONFIGURARPWM", "CONFIGURARSERIAL", "CONECTARWIFI",
  "LIGAR", "DESLIGAR", "AJUSTARPWM", "ESPERAR", "ESCREVER_SERIAL",
  "LER_SERIAL", "ENVIAR_HTTP", "LER_DIGITAL", "LER_ANALOGICO", "SE",
  "SENAO", "ENTAO", "ENQUANTO", "REPITA", "FIM", "COM", "COMO", "SAIDA",
  "ENTRADA", "FREQUENCIA", "RESOLUCAO", "IGUAL", "IGUAL_IGUAL",
  "DIFERENTE", "MENOR", "MAIOR", "MENOR_IGUAL", "MAIOR_IGUAL", "MAIS",
  "MENOS", "MULTIPLICACAO", "DIVISAO", "MODULO", "VIRGULA",
  "PONTOEVIRGULA", "DOISPONTOS", "VALOR", "$accept", "programa",
  "declaracoes", "declaracao", "tipo", "listaIdentificadores",
  "configuracao", "comandos", "comando", "atribuicao", "expressao",
  "configuracaoPino", "configuracaoPWM", "configuracaoSerial",
  "conexaoWifi", "controleFluxo", "condicional", "repeticao",
  "operacaoHardware", "loop", YY_NULLPTR
};

static const char *
yysymbol_name (yysymbol_kind_t yysymbol)
{
  return yytname[yysymbol];
}
#endif

#define YYPACT_NINF (-45)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      26,    62,    54,    47,    26,   -45,   -45,   -45,    25,   -45,
     202,    59,   -45,    89,    57,    92,    93,    94,    96,    97,
     116,   118,   119,    69,   121,    69,   137,   139,    69,    69,
     114,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,
     -45,   202,   -45,   -45,   -44,    30,    66,   115,    73,   141,
     113,   117,   134,   135,   -45,   -45,   -45,   193,   140,     5,
     157,   159,   -24,    39,   -45,   -45,   136,   143,   -45,   164,
     165,   206,   -21,   152,   -45,   161,   -45,   -45,   160,   -45,
      69,    69,    69,    69,    69,    69,    69,    69,    69,    69,
     -45,   -45,   219,   -45,   -45,   202,   202,   -45,   -45,   163,
     178,   -45,   179,   191,   184,   -45,   187,   -15,   -15,    -5,
      -5,    -5,    -5,    45,    45,   -45,   -45,   -45,    91,   158,
     -45,   -45,   -45,   -45,   218,   192,   202,   -45,   -45,   250,
     -45,   180,   217,   -45,   -45
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     0,     3,     6,     7,     8,     0,     1,
       0,     0,     4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,    14,    15,    16,    17,    18,    19,    42,    43,
      20,     0,     2,     9,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,    35,    34,    36,     0,     0,     0,
       0,     0,     0,     0,    11,    13,     0,     0,     5,     0,
       0,     0,     0,     0,    40,     0,    47,    48,     0,    50,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
      51,    52,     0,    54,    55,     0,     0,    56,    10,     0,
       0,    21,     0,     0,     0,    41,     0,    28,    29,    30,
      31,    32,    33,    24,    25,    26,    27,    53,     0,     0,
      22,    23,    37,    38,     0,     0,     0,    45,    46,     0,
      49,     0,     0,    44,    39
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -45,   -45,   263,   -45,   -45,   -45,   -45,   -40,   -30,   -45,
     -22,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45,   -45
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,     8,    44,    11,    30,    31,    32,
      57,    33,    34,    35,    36,    37,    38,    39,    40,    42
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      65,    66,    95,    59,    67,    68,    62,    63,    54,    55,
      56,   102,   103,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,    71,    82,    83,    84,    85,    86,    87,
      88,    89,     1,    54,    55,    56,    65,    92,    86,    87,
      88,    89,    80,    81,    82,    83,    84,    85,    86,    87,
      88,    89,    69,    70,     9,   118,   119,    10,   107,   108,
     109,   110,   111,   112,   113,   114,   115,   116,    96,     5,
       6,     7,    54,    55,    56,    13,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   131,    41,    65,    65,
      88,    89,    43,    45,    14,    46,    47,    72,    48,    49,
      50,    65,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,   126,    14,    29,    51,
     127,    52,    74,    53,    58,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,    25,    26,    27,    28,    14,
      60,    29,    61,    64,    75,    73,    98,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    25,    26,    27,
      28,    14,    76,    29,    78,    97,    77,    99,   100,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,    14,    79,    29,   104,   128,   124,    91,
     125,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,    25,    26,    27,    28,    14,    93,    29,    94,   133,
     105,   106,   120,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    26,    27,    28,   121,   122,    29,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
     123,   130,    90,    80,    81,    82,    83,    84,    85,    86,
      87,    88,    89,   129,   132,   101,    80,    81,    82,    83,
      84,    85,    86,    87,    88,    89,   134,    12,   117
};

static const yytype_uint8 yycheck[] =
{
      30,    41,    26,    25,    48,    49,    28,    29,     3,     4,
       5,    32,    33,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    45,    39,    40,    41,    42,    43,    44,
      45,    46,     6,     3,     4,     5,    66,    59,    43,    44,
      45,    46,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    22,    23,     0,    95,    96,    10,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    29,     7,
       8,     9,     3,     4,     5,    50,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,   126,    28,   118,   119,
      45,    46,     3,    36,     3,     3,     3,    31,     4,     3,
       3,   131,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,     3,    27,     3,
      29,     3,    49,     4,     3,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,     3,
       3,    27,     3,    29,     3,    30,     3,    11,    12,    13,
      14,    15,    16,    17,    18,    19,    20,    21,    22,    23,
      24,     3,    49,    27,    30,    29,    49,     3,     3,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,     3,    49,    27,    34,    29,     4,    49,
       3,    11,    12,    13,    14,    15,    16,    17,    18,    19,
      20,    21,    22,    23,    24,     3,    49,    27,    49,    29,
      49,    51,    49,    11,    12,    13,    14,    15,    16,    17,
      18,    19,    20,    21,    22,    23,    24,    49,    49,    27,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      49,    49,    49,    37,    38,    39,    40,    41,    42,    43,
      44,    45,    46,    35,     4,    49,    37,    38,    39,    40,
      41,    42,    43,    44,    45,    46,    49,     4,    49
};

/* YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
   state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     6,    53,    54,    55,     7,     8,     9,    56,     0,
      10,    58,    54,    50,     3,    11,    12,    13,    14,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    27,
      59,    60,    61,    63,    64,    65,    66,    67,    68,    69,
      70,    28,    71,     3,    57,    36,     3,     3,     4,     3,
       3,     3,     3,     4,     3,     4,     5,    62,     3,    62,
       3,     3,    62,    62,    29,    60,    59,    48,    49,    22,
      23,    62,    31,    30,    49,     3,    49,    49,    30,    49,
      37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
      49,    49,    62,    49,    49,    26,    29,    29,     3,     3,
       3,    49,    32,    33,    34,    49,    51,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    49,    59,    59,
      49,    49,    49,    49,     4,     3,    25,    29,    29,    35,
      49,    59,     4,    29,    49
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    54,    54,    55,    56,    56,    56,    57,
      57,    58,    59,    59,    60,    60,    60,    60,    60,    60,
      60,    61,    61,    61,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    62,    63,    63,    64,
      65,    66,    67,    67,    68,    68,    69,    70,    70,    70,
      70,    70,    70,    70,    70,    70,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     0,     2,     5,     1,     1,     1,     1,
       3,     3,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     4,     5,     5,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     1,     1,     1,     5,     5,     8,
       3,     4,     1,     1,     7,     5,     5,     3,     3,     6,
       3,     3,     3,     4,     3,     3,     3
};


enum { YYENOMEM = -2 };

#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYNOMEM         goto yyexhaustedlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                    \
  do                                                              \
    if (yychar == YYEMPTY)                                        \
      {                                                           \
        yychar = (Token);                                         \
        yylval = (Value);                                         \
        YYPOPSTACK (yylen);                                       \
        yystate = *yyssp;                                         \
        goto yybackup;                                            \
      }                                                           \
    else                                                          \
      {                                                           \
        yyerror (YY_("syntax error: cannot back up")); \
        YYERROR;                                                  \
      }                                                           \
  while (0)

/* Backward compatibility with an undocumented macro.
   Use YYerror or YYUNDEF. */
#define YYERRCODE YYUNDEF


/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)




# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Kind, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo,
                       yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  FILE *yyoutput = yyo;
  YY_USE (yyoutput);
  if (!yyvaluep)
    return;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo,
                 yysymbol_kind_t yykind, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyo, "%s %s (",
             yykind < YYNTOKENS ? "token" : "nterm", yysymbol_name (yykind));

  yy_symbol_value_print (yyo, yykind, yyvaluep);
  YYFPRINTF (yyo, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yy_state_t *yybottom, yy_state_t *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp,
                 int yyrule)
{
  int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %d):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       YY_ACCESSING_SYMBOL (+yyssp[yyi + 1 - yynrhs]),
                       &yyvsp[(yyi + 1) - (yynrhs)]);
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args) ((void) 0)
# define YY_SYMBOL_PRINT(Title, Kind, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif






/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg,
            yysymbol_kind_t yykind, YYSTYPE *yyvaluep)
{
  YY_USE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yykind, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YY_USE (yykind);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/* Lookahead token kind.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;




/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate = 0;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus = 0;

    /* Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* Their size.  */
    YYPTRDIFF_T yystacksize = YYINITDEPTH;

    /* The state stack: array, bottom, top.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss = yyssa;
    yy_state_t *yyssp = yyss;

    /* The semantic value stack: array, bottom, top.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs = yyvsa;
    YYSTYPE *yyvsp = yyvs;

  int yyn;
  /* The return value of yyparse.  */
  int yyresult;
  /* Lookahead symbol kind.  */
  yysymbol_kind_t yytoken = YYSYMBOL_YYEMPTY;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;



#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yychar = YYEMPTY; /* Cause a token to be read.  */

  goto yysetstate;


/*------------------------------------------------------------.
| yynewstate -- push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;


/*--------------------------------------------------------------------.
| yysetstate -- set current state (the top of the stack) to yystate.  |
`--------------------------------------------------------------------*/
yysetstate:
  YYDPRINTF ((stderr, "Entering state %d\n", yystate));
  YY_ASSERT (0 <= yystate && yystate < YYNSTATES);
  YY_IGNORE_USELESS_CAST_BEGIN
  *yyssp = YY_CAST (yy_state_t, yystate);
  YY_IGNORE_USELESS_CAST_END
  YY_STACK_PRINT (yyss, yyssp);

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    YYNOMEM;
#else
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYPTRDIFF_T yysize = yyssp - yyss + 1;

# if defined yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        yy_state_t *yyss1 = yyss;
        YYSTYPE *yyvs1 = yyvs;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        YYNOMEM;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          YYNOMEM;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YY_IGNORE_USELESS_CAST_BEGIN
      YYDPRINTF ((stderr, "Stack size increased to %ld\n",
                  YY_CAST (long, yystacksize)));
      YY_IGNORE_USELESS_CAST_END

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }
#endif /* !defined yyoverflow && !defined YYSTACK_RELOCATE */


  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;


/*-----------.
| yybackup.  |
`-----------*/
yybackup:
  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either empty, or end-of-input, or a valid lookahead.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token\n"));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = YYEOF;
      yytoken = YYSYMBOL_YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else if (yychar == YYerror)
    {
      /* The scanner already issued an error message, process directly
         to error recovery.  But do not keep the error token as
         lookahead, it is too special and may lead us to an endless
         loop in error recovery. */
      yychar = YYUNDEF;
      yytoken = YYSYMBOL_YYerror;
      goto yyerrlab1;
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  /* Discard the shifted token.  */
  yychar = YYEMPTY;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2: /* programa: declaracoes configuracao loop  */
#line 202 "src/parser.y"
                                  {
        char *temp = malloc(strlen((yyvsp[-2].str)) + (constantesGlobais ? strlen(constantesGlobais) : 0) + strlen((yyvsp[-1].str)) + strlen((yyvsp[0].str)) + 100);
        sprintf(temp, "#include <Arduino.h>\n#include <WiFi.h>\n\n%s%s%s%s", (yyvsp[-2].str), constantesGlobais ? constantesGlobais : "", (yyvsp[-1].str), (yyvsp[0].str));
        appendCode(temp);
        (yyval.str) = temp;
    }
#line 1411 "temp/parser.tab.c"
    break;

  case 3: /* declaracoes: %empty  */
#line 210 "src/parser.y"
                { (yyval.str) = strdup(""); }
#line 1417 "temp/parser.tab.c"
    break;

  case 4: /* declaracoes: declaracao declaracoes  */
#line 211 "src/parser.y"
                             { 
        char *temp = malloc(strlen((yyvsp[-1].str)) + strlen((yyvsp[0].str)) + 2);
        sprintf(temp, "%s%s", (yyvsp[-1].str), (yyvsp[0].str));
        (yyval.str) = temp;
    }
#line 1427 "temp/parser.tab.c"
    break;

  case 5: /* declaracao: VAR tipo DOISPONTOS listaIdentificadores PONTOEVIRGULA  */
#line 219 "src/parser.y"
                                                           {
        (yyval.str) = strdup((yyvsp[-1].str));
    }
#line 1435 "temp/parser.tab.c"
    break;

  case 6: /* tipo: INTEIRO  */
#line 225 "src/parser.y"
            { 
        if (tipoAtual) free(tipoAtual);
        tipoAtual = strdup("int"); 
        (yyval.str) = tipoAtual; 
    }
#line 1445 "temp/parser.tab.c"
    break;

  case 7: /* tipo: TEXTO  */
#line 230 "src/parser.y"
            { 
        if (tipoAtual) free(tipoAtual);
        tipoAtual = strdup("String"); 
        (yyval.str) = tipoAtual; 
    }
#line 1455 "temp/parser.tab.c"
    break;

  case 8: /* tipo: BOOLEANO  */
#line 235 "src/parser.y"
               { 
        if (tipoAtual) free(tipoAtual);
        tipoAtual = strdup("bool"); 
        (yyval.str) = tipoAtual; 
    }
#line 1465 "temp/parser.tab.c"
    break;

  case 9: /* listaIdentificadores: IDENTIFICADOR  */
#line 243 "src/parser.y"
                  { 
        if (!tipoAtual) { 
            yyerror("tipo não definido antes dos identificadores."); 
            YYABORT; 
        }
        if (variavelJaDeclarada((yyvsp[0].str))) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Variável '%s' já foi declarada", (yyvsp[0].str));
            yyerror(erro);
            YYABORT;
        }
        adicionarVariavel((yyvsp[0].str), tipoAtual);
        size_t tamanho = strlen(tipoAtual) + strlen((yyvsp[0].str)) + 10;
        char *codigo = (char *)malloc(tamanho);
        if (codigo == NULL) {
            yyerror("Falha na alocação de memória");
            YYABORT;
        }
        snprintf(codigo, tamanho, "%s %s;\n", tipoAtual, (yyvsp[0].str));
        (yyval.str) = codigo;
    }
#line 1491 "temp/parser.tab.c"
    break;

  case 10: /* listaIdentificadores: listaIdentificadores VIRGULA IDENTIFICADOR  */
#line 264 "src/parser.y"
                                                 {
        if (!tipoAtual) { 
            yyerror("tipo não definido antes dos identificadores."); 
            YYABORT; 
        }
        if (variavelJaDeclarada((yyvsp[0].str))) {
            char erro[256];
            snprintf(erro, sizeof(erro), "Variável '%s' já foi declarada", (yyvsp[0].str));
            yyerror(erro);
            YYABORT;
        }
        adicionarVariavel((yyvsp[0].str), tipoAtual);
        size_t tamanho = strlen((yyvsp[-2].str)) + strlen(tipoAtual) + strlen((yyvsp[0].str)) + 10;
        char *temp = (char *)malloc(tamanho);
        if (temp == NULL) {
            yyerror("Falha na alocação de memória");
            YYABORT;
        }
        snprintf(temp, tamanho, "%s%s %s;\n", (yyvsp[-2].str), tipoAtual, (yyvsp[0].str));
        (yyval.str) = temp;
    }
#line 1517 "temp/parser.tab.c"
    break;

  case 11: /* configuracao: CONFIG comandos FIM  */
#line 288 "src/parser.y"
                        {
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 50);
        sprintf(codigo, "\nvoid setup()\n{\n%s}\n", (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1527 "temp/parser.tab.c"
    break;

  case 12: /* comandos: comando  */
#line 296 "src/parser.y"
            { (yyval.str) = strdup((yyvsp[0].str)); }
#line 1533 "temp/parser.tab.c"
    break;

  case 13: /* comandos: comandos comando  */
#line 297 "src/parser.y"
                       {
        char *temp = malloc(strlen((yyvsp[-1].str)) + strlen((yyvsp[0].str)) + 1);
        strcpy(temp, (yyvsp[-1].str));
        strcat(temp, (yyvsp[0].str));
        (yyval.str) = temp;
    }
#line 1544 "temp/parser.tab.c"
    break;

  case 21: /* atribuicao: IDENTIFICADOR IGUAL expressao PONTOEVIRGULA  */
#line 316 "src/parser.y"
                                                {
        if (!verificarVariavelDeclarada((yyvsp[-3].str))) {
            YYABORT;
        }

        // Verificando se o tipo da variável e da expressão são compatíveis
        char *tipoVar = obterTipoVariavel((yyvsp[-3].str));
        char *tipoExpr = (yyvsp[-1].str);

        if (!verificarTipoAtribuicao((yyvsp[-3].str), tipoVar, tipoExpr)) {
            YYABORT;
        }

        char *codigo = malloc(strlen((yyvsp[-3].str)) + strlen((yyvsp[-1].str)) + 10);
        sprintf(codigo, "%s = %s;\n", (yyvsp[-3].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1566 "temp/parser.tab.c"
    break;

  case 22: /* atribuicao: IDENTIFICADOR IGUAL LER_DIGITAL IDENTIFICADOR PONTOEVIRGULA  */
#line 333 "src/parser.y"
                                                                  {
        if (!verificarVariavelDeclarada((yyvsp[-4].str))) {
            YYABORT;
        }
        if (!verificarVariavelDeclarada((yyvsp[-1].str))) {
            YYABORT;
        }
        char *codigo = malloc(strlen((yyvsp[-4].str)) + strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "%s = digitalRead(%s);\n", (yyvsp[-4].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1582 "temp/parser.tab.c"
    break;

  case 23: /* atribuicao: IDENTIFICADOR IGUAL LER_ANALOGICO IDENTIFICADOR PONTOEVIRGULA  */
#line 344 "src/parser.y"
                                                                    {
        if (!verificarVariavelDeclarada((yyvsp[-4].str))) {
            YYABORT;
        }
        if (!verificarVariavelDeclarada((yyvsp[-1].str))) {
            YYABORT;
        }
        char *codigo = malloc(strlen((yyvsp[-4].str)) + strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "%s = analogRead(%s);\n", (yyvsp[-4].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1598 "temp/parser.tab.c"
    break;

  case 24: /* expressao: expressao MAIS expressao  */
#line 358 "src/parser.y"
                             {
        if (!verificarTipoParaOperacao((yyvsp[-2].str), (yyvsp[0].str))) {
            YYABORT;
        }
        (yyval.str) = strdup("operacao de soma");
        sprintf((yyval.str), "%s + %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1610 "temp/parser.tab.c"
    break;

  case 25: /* expressao: expressao MENOS expressao  */
#line 365 "src/parser.y"
                                {
        if (!verificarTipoParaOperacao((yyvsp[-2].str), (yyvsp[0].str))) {
            YYABORT;
        }
        (yyval.str) = strdup("operacao de subtração");
        sprintf((yyval.str), "%s - %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1622 "temp/parser.tab.c"
    break;

  case 26: /* expressao: expressao MULTIPLICACAO expressao  */
#line 372 "src/parser.y"
                                        {
        if (!verificarTipoParaOperacao((yyvsp[-2].str), (yyvsp[0].str))) {
            YYABORT;
        }
        (yyval.str) = strdup("operacao de multiplicação");
        sprintf((yyval.str), "%s * %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1634 "temp/parser.tab.c"
    break;

  case 27: /* expressao: expressao DIVISAO expressao  */
#line 379 "src/parser.y"
                                  {
        if (!verificarTipoParaOperacao((yyvsp[-2].str), (yyvsp[0].str))) {
            YYABORT;
        }
        (yyval.str) = strdup("operacao de divisão");
        sprintf((yyval.str), "%s / %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1646 "temp/parser.tab.c"
    break;

  case 28: /* expressao: expressao IGUAL_IGUAL expressao  */
#line 386 "src/parser.y"
                                      {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s == %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1655 "temp/parser.tab.c"
    break;

  case 29: /* expressao: expressao DIFERENTE expressao  */
#line 390 "src/parser.y"
                                    {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s != %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1664 "temp/parser.tab.c"
    break;

  case 30: /* expressao: expressao MENOR expressao  */
#line 394 "src/parser.y"
                                {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s < %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1673 "temp/parser.tab.c"
    break;

  case 31: /* expressao: expressao MAIOR expressao  */
#line 398 "src/parser.y"
                                {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s > %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1682 "temp/parser.tab.c"
    break;

  case 32: /* expressao: expressao MENOR_IGUAL expressao  */
#line 402 "src/parser.y"
                                      {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s <= %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1691 "temp/parser.tab.c"
    break;

  case 33: /* expressao: expressao MAIOR_IGUAL expressao  */
#line 406 "src/parser.y"
                                      {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s >= %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1700 "temp/parser.tab.c"
    break;

  case 34: /* expressao: NUMERO  */
#line 410 "src/parser.y"
             {
        (yyval.str) = malloc(20);
        sprintf((yyval.str), "%d", (yyvsp[0].num));
    }
#line 1709 "temp/parser.tab.c"
    break;

  case 35: /* expressao: IDENTIFICADOR  */
#line 414 "src/parser.y"
                    {
        if (!verificarVariavelDeclarada((yyvsp[0].str))) {
            YYABORT;
        }
        (yyval.str) = strdup((yyvsp[0].str));
    }
#line 1720 "temp/parser.tab.c"
    break;

  case 36: /* expressao: STRING  */
#line 420 "src/parser.y"
             {
        (yyval.str) = strdup((yyvsp[0].str));
    }
#line 1728 "temp/parser.tab.c"
    break;

  case 37: /* configuracaoPino: CONFIGURAR IDENTIFICADOR COMO SAIDA PONTOEVIRGULA  */
#line 426 "src/parser.y"
                                                      {
        if (!verificarVariavelDeclarada((yyvsp[-3].str))) {
            YYABORT;
        }
        char *codigo = malloc(strlen((yyvsp[-3].str)) + 30);
        sprintf(codigo, "pinMode(%s, OUTPUT);\n", (yyvsp[-3].str));
        (yyval.str) = codigo;
    }
#line 1741 "temp/parser.tab.c"
    break;

  case 38: /* configuracaoPino: CONFIGURAR IDENTIFICADOR COMO ENTRADA PONTOEVIRGULA  */
#line 434 "src/parser.y"
                                                          {
        if (!verificarVariavelDeclarada((yyvsp[-3].str))) {
            YYABORT;
        }
        char *codigo = malloc(strlen((yyvsp[-3].str)) + 30);
        sprintf(codigo, "pinMode(%s, INPUT);\n", (yyvsp[-3].str));
        (yyval.str) = codigo;
    }
#line 1754 "temp/parser.tab.c"
    break;

  case 39: /* configuracaoPWM: CONFIGURARPWM IDENTIFICADOR COM FREQUENCIA NUMERO RESOLUCAO NUMERO PONTOEVIRGULA  */
#line 445 "src/parser.y"
                                                                                     {
        if (!verificarVariavelDeclarada((yyvsp[-6].str))) {
            YYABORT;
        }
        char constantes[200];
        char codigo[200];

        sprintf(constantes, "\nconst int canalPWM = 0;\nconst int frequencia = %d;\nconst int resolucao = %d;\n", (yyvsp[-3].num), (yyvsp[-1].num));
        appendConstantes(constantes);

        sprintf(codigo, "ledcSetup(canalPWM, frequencia, resolucao);\nledcAttachPin(%s, canalPWM);\n", (yyvsp[-6].str));
        (yyval.str) = strdup(codigo);
    }
#line 1772 "temp/parser.tab.c"
    break;

  case 40: /* configuracaoSerial: CONFIGURARSERIAL NUMERO PONTOEVIRGULA  */
#line 461 "src/parser.y"
                                          {
        char *codigo = malloc(50);
        sprintf(codigo, "Serial.begin(%d);\n", (yyvsp[-1].num));
        (yyval.str) = codigo;
    }
#line 1782 "temp/parser.tab.c"
    break;

  case 41: /* conexaoWifi: CONECTARWIFI IDENTIFICADOR IDENTIFICADOR PONTOEVIRGULA  */
#line 469 "src/parser.y"
                                                           {
        if (!verificarVariavelDeclarada((yyvsp[-2].str))) {
            YYABORT;
        }
        if (!verificarVariavelDeclarada((yyvsp[-1].str))) {
            YYABORT;
        }
        char *codigo = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[-1].str)) + 170);
        sprintf(codigo, "WiFi.begin(%s.c_str(), %s.c_str());\nwhile (WiFi.status() != WL_CONNECTED)\n{\n    delay(500);\n    Serial.println(\"Conectando ao WiFi...\");\n}\nSerial.println(\"Conectado ao WiFi!\");\n", (yyvsp[-2].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1798 "temp/parser.tab.c"
    break;

  case 42: /* controleFluxo: condicional  */
#line 483 "src/parser.y"
                { (yyval.str) = (yyvsp[0].str); }
#line 1804 "temp/parser.tab.c"
    break;

  case 43: /* controleFluxo: repeticao  */
#line 484 "src/parser.y"
                { (yyval.str) = (yyvsp[0].str); }
#line 1810 "temp/parser.tab.c"
    break;

  case 44: /* condicional: SE expressao ENTAO comandos SENAO comandos FIM  */
#line 488 "src/parser.y"
                                                   {
        char *codigo = malloc(strlen((yyvsp[-5].str)) + strlen((yyvsp[-3].str)) + strlen((yyvsp[-1].str)) + 50);
        sprintf(codigo, "if (%s)\n{\n%s}\nelse\n{\n%s}\n", (yyvsp[-5].str), (yyvsp[-3].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1820 "temp/parser.tab.c"
    break;

  case 45: /* condicional: SE expressao ENTAO comandos FIM  */
#line 493 "src/parser.y"
                                      {
        char *codigo = malloc(strlen((yyvsp[-3].str)) + strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "if (%s)\n{\n%s}\n", (yyvsp[-3].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1830 "temp/parser.tab.c"
    break;

  case 46: /* repeticao: ENQUANTO expressao FIM comandos FIM  */
#line 501 "src/parser.y"
                                        {
        char *codigo = malloc(strlen((yyvsp[-3].str)) + strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "while (%s)\n{\n%s}\n", (yyvsp[-3].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1840 "temp/parser.tab.c"
    break;

  case 47: /* operacaoHardware: LIGAR IDENTIFICADOR PONTOEVIRGULA  */
#line 509 "src/parser.y"
                                      {
        if (!verificarVariavelDeclarada((yyvsp[-1].str))) {
            YYABORT;
        }
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 20);
        sprintf(codigo, "digitalWrite(%s, HIGH);\n", (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1853 "temp/parser.tab.c"
    break;

  case 48: /* operacaoHardware: DESLIGAR IDENTIFICADOR PONTOEVIRGULA  */
#line 517 "src/parser.y"
                                           {
        if (!verificarVariavelDeclarada((yyvsp[-1].str))) {
            YYABORT;
        }
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 25);
        sprintf(codigo, "digitalWrite(%s, LOW);\n", (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1866 "temp/parser.tab.c"
    break;

  case 49: /* operacaoHardware: AJUSTARPWM IDENTIFICADOR COM VALOR IDENTIFICADOR PONTOEVIRGULA  */
#line 525 "src/parser.y"
                                                                     {
        if (!verificarVariavelDeclarada((yyvsp[-4].str))) {
            YYABORT;
        }
        if (!verificarVariavelDeclarada((yyvsp[-1].str))) {
            YYABORT;
        }
        char *codigo = malloc(strlen((yyvsp[-4].str)) + strlen((yyvsp[-1].str)) + 40);
        sprintf(codigo, "ledcWrite(%s, %s);\n", (yyvsp[-4].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1882 "temp/parser.tab.c"
    break;

  case 50: /* operacaoHardware: ESPERAR NUMERO PONTOEVIRGULA  */
#line 536 "src/parser.y"
                                   {
        char *codigo = malloc(20);
        sprintf(codigo, "delay(%d);\n", (yyvsp[-1].num));
        (yyval.str) = codigo;
    }
#line 1892 "temp/parser.tab.c"
    break;

  case 51: /* operacaoHardware: ESCREVER_SERIAL expressao PONTOEVIRGULA  */
#line 541 "src/parser.y"
                                              {
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "Serial.println(%s);\n", (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1902 "temp/parser.tab.c"
    break;

  case 52: /* operacaoHardware: LER_SERIAL IDENTIFICADOR PONTOEVIRGULA  */
#line 546 "src/parser.y"
                                             {
        if (!verificarVariavelDeclarada((yyvsp[-1].str))) {
            YYABORT;
        }
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "%s = Serial.readString();\n", (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1915 "temp/parser.tab.c"
    break;

  case 53: /* operacaoHardware: ENVIAR_HTTP expressao expressao PONTOEVIRGULA  */
#line 554 "src/parser.y"
                                                    {
        char *codigo = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[-1].str)) + 500);
        sprintf(codigo, "if (WiFi.status() == WL_CONNECTED)\n{\n    http.begin(%s);\n    int httpResponseCode = http.GET();\n    if (httpResponseCode > 0) {\n        Serial.print(\"Resposta HTTP: \");\n        Serial.println(httpResponseCode);\n    } else {\n        Serial.print(\"Erro na requisição: \");\n        Serial.println(httpResponseCode);\n    }\n    http.end();\n} else {\n    Serial.println(\"WiFi desconectado, tentando reconectar...\");\n    WiFi.begin(%s, %s);\n}\n", (yyvsp[-2].str), (yyvsp[-2].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1925 "temp/parser.tab.c"
    break;

  case 54: /* operacaoHardware: LER_DIGITAL IDENTIFICADOR PONTOEVIRGULA  */
#line 559 "src/parser.y"
                                              {
        if (!verificarVariavelDeclarada((yyvsp[-1].str))) {
            YYABORT;
        }
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "%s = digitalRead(%s);\n", (yyvsp[-1].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1938 "temp/parser.tab.c"
    break;

  case 55: /* operacaoHardware: LER_ANALOGICO IDENTIFICADOR PONTOEVIRGULA  */
#line 567 "src/parser.y"
                                                {
        if (!verificarVariavelDeclarada((yyvsp[-1].str))) {
            YYABORT;
        }
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "%s = analogRead(%s);\n", (yyvsp[-1].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1951 "temp/parser.tab.c"
    break;

  case 56: /* loop: REPITA comandos FIM  */
#line 578 "src/parser.y"
                        {
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "\nvoid loop()\n{\n%s}\n", (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1961 "temp/parser.tab.c"
    break;


#line 1965 "temp/parser.tab.c"

      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", YY_CAST (yysymbol_kind_t, yyr1[yyn]), &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */
  {
    const int yylhs = yyr1[yyn] - YYNTOKENS;
    const int yyi = yypgoto[yylhs] + *yyssp;
    yystate = (0 <= yyi && yyi <= YYLAST && yycheck[yyi] == *yyssp
               ? yytable[yyi]
               : yydefgoto[yylhs]);
  }

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYSYMBOL_YYEMPTY : YYTRANSLATE (yychar);
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
      yyerror (YY_("syntax error"));
    }

  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:
  /* Pacify compilers when the user code never invokes YYERROR and the
     label yyerrorlab therefore never appears in user code.  */
  if (0)
    YYERROR;
  ++yynerrs;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  /* Pop stack until we find a state that shifts the error token.  */
  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYSYMBOL_YYerror;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYSYMBOL_YYerror)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  YY_ACCESSING_SYMBOL (yystate), yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", YY_ACCESSING_SYMBOL (yyn), yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturnlab;


/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturnlab;


/*-----------------------------------------------------------.
| yyexhaustedlab -- YYNOMEM (memory exhaustion) comes here.  |
`-----------------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  goto yyreturnlab;


/*----------------------------------------------------------.
| yyreturnlab -- parsing is finished, clean up and return.  |
`----------------------------------------------------------*/
yyreturnlab:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  YY_ACCESSING_SYMBOL (+*yyssp), yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif

  return yyresult;
}

#line 585 "src/parser.y"


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
