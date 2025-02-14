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

void yyerror(const char *s);
int yylex();

extern FILE *yyin;

char *codigoGerado = NULL;
char *tipo_atual = NULL;
char *constantesGlobais = NULL;

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

void appendConstantes(const char *novaConstante) {
    if (constantesGlobais == NULL) {
        constantesGlobais = strdup(novaConstante);
    } else {
        char *temp = malloc(strlen(constantesGlobais) + strlen(novaConstante) + 1);
        strcpy(temp, constantesGlobais);
        strcat(temp, novaConstante);
        free(constantesGlobais);
        constantesGlobais = temp;
    }
}

#line 110 "temp/parser.tab.c"

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
#define YYLAST   251

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  52
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  20
/* YYNRULES -- Number of rules.  */
#define YYNRULES  55
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  131

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
       0,    76,    76,    84,    85,    93,    99,   104,   109,   117,
     125,   137,   145,   146,   155,   156,   157,   158,   159,   160,
     161,   165,   170,   178,   182,   186,   190,   195,   199,   203,
     207,   211,   215,   219,   223,   226,   232,   237,   245,   259,
     267,   275,   276,   280,   285,   293,   301,   306,   311,   316,
     321,   326,   331,   336,   341,   349
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

#define YYPACT_NINF (-41)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
static const yytype_int16 yypact[] =
{
      44,     5,    53,    46,    44,   -41,   -41,   -41,     4,   -41,
     175,    29,   -41,    65,    33,    67,    68,    69,    71,    73,
      74,    75,    76,    78,    81,    80,    84,    85,    42,    42,
      87,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,
     -41,   175,   -41,   -41,    -6,    12,    41,    49,    32,    86,
      43,    45,    61,    47,    64,    66,    70,    88,    90,   -41,
     -41,   -41,   174,   192,   -41,   -41,   109,    92,   -41,   114,
     202,    16,    59,   -41,    91,   -41,   -41,   106,   -41,   -41,
     -41,   -41,   -41,   -41,   175,    42,    42,    42,    42,    42,
      42,    42,    42,    42,    42,   175,   -41,   -41,   110,   -41,
     112,   113,   137,   -41,   115,     8,   -36,   -36,    -5,    -5,
      -5,    -5,     6,     6,   -41,   -41,   131,   -41,   -41,   -41,
     100,   130,   175,   -41,   -41,   159,   -41,   153,   132,   -41,
     -41
};

/* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
   Performed when YYTABLE does not specify something else to do.  Zero
   means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       3,     0,     0,     0,     3,     6,     7,     8,     0,     1,
       0,     0,     4,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    12,    14,    15,    16,    17,    18,    19,    41,    42,
      20,     0,     2,     9,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,    34,
      33,    35,     0,     0,    11,    13,     0,     0,     5,     0,
       0,     0,     0,    39,     0,    46,    47,     0,    49,    50,
      51,    52,    53,    54,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    55,    10,     0,    21,
       0,     0,     0,    40,     0,     0,    27,    28,    29,    30,
      31,    32,    23,    24,    25,    26,     0,    22,    36,    37,
       0,     0,     0,    44,    45,     0,    48,     0,     0,    43,
      38
};

/* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -41,   -41,   179,   -41,   -41,   -41,   -41,   -40,   -30,   -41,
     -27,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41,   -41
};

/* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
       0,     2,     3,     4,     8,    44,    11,    30,    31,    32,
      62,    33,    34,    35,    36,    37,    38,    39,    40,    42
};

/* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule whose
   number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      65,    66,    63,    87,    88,    89,    90,    91,    92,    93,
      94,    14,     5,     6,     7,    59,    60,    61,    70,    15,
      16,    17,    18,    19,    20,    21,    22,    23,    24,    25,
      26,    27,    28,   122,    69,    29,    65,   123,    91,    92,
      93,    94,    67,    68,   105,    59,    60,    61,   100,   101,
       1,    93,    94,     9,    13,   116,    10,    41,   106,   107,
     108,   109,   110,   111,   112,   113,   114,   115,    43,    45,
      46,    47,    71,    48,    49,    65,    50,    51,    52,    72,
      53,    73,   127,    54,    55,    56,    65,    57,    58,    74,
      14,    77,    75,   102,    76,    97,    78,    65,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
      27,    28,    14,    79,    29,    80,    64,    98,   121,    81,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    14,   125,    29,    82,    96,    83,
     103,   120,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,    25,    26,    27,    28,    14,   104,    29,   117,
     124,   118,   119,   128,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,    25,    26,    27,    28,    14,   126,
      29,   130,   129,    12,     0,     0,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,    25,    26,    27,    28,
      84,     0,    29,     0,     0,     0,     0,     0,     0,     0,
       0,    85,    86,    87,    88,    89,    90,    91,    92,    93,
      94,    95,     0,     0,     0,     0,     0,     0,     0,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,    85,
      86,    87,    88,    89,    90,    91,    92,    93,    94,     0,
       0,    99
};

static const yytype_int8 yycheck[] =
{
      30,    41,    29,    39,    40,    41,    42,    43,    44,    45,
      46,     3,     7,     8,     9,     3,     4,     5,    45,    11,
      12,    13,    14,    15,    16,    17,    18,    19,    20,    21,
      22,    23,    24,    25,    22,    27,    66,    29,    43,    44,
      45,    46,    48,    49,    84,     3,     4,     5,    32,    33,
       6,    45,    46,     0,    50,    95,    10,    28,    85,    86,
      87,    88,    89,    90,    91,    92,    93,    94,     3,    36,
       3,     3,    31,     4,     3,   105,     3,     3,     3,    30,
       4,    49,   122,     5,     3,     5,   116,     3,     3,     3,
       3,    30,    49,    34,    49,     3,    49,   127,    11,    12,
      13,    14,    15,    16,    17,    18,    19,    20,    21,    22,
      23,    24,     3,    49,    27,    49,    29,     3,     3,    49,
      11,    12,    13,    14,    15,    16,    17,    18,    19,    20,
      21,    22,    23,    24,     3,    35,    27,    49,    29,    49,
      49,     4,    11,    12,    13,    14,    15,    16,    17,    18,
      19,    20,    21,    22,    23,    24,     3,    51,    27,    49,
      29,    49,    49,     4,    11,    12,    13,    14,    15,    16,
      17,    18,    19,    20,    21,    22,    23,    24,     3,    49,
      27,    49,    29,     4,    -1,    -1,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      26,    -1,    27,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    37,    38,    39,    40,    41,    42,    43,    44,    45,
      46,    29,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    37,
      38,    39,    40,    41,    42,    43,    44,    45,    46,    -1,
      -1,    49
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
       3,     3,     3,     4,     5,     3,     5,     3,     3,     3,
       4,     5,    62,    62,    29,    60,    59,    48,    49,    22,
      62,    31,    30,    49,     3,    49,    49,    30,    49,    49,
      49,    49,    49,    49,    26,    37,    38,    39,    40,    41,
      42,    43,    44,    45,    46,    29,    29,     3,     3,    49,
      32,    33,    34,    49,    51,    59,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    59,    49,    49,    49,
       4,     3,    25,    29,    29,    35,    49,    59,     4,    29,
      49
};

/* YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr1[] =
{
       0,    52,    53,    54,    54,    55,    56,    56,    56,    57,
      57,    58,    59,    59,    60,    60,    60,    60,    60,    60,
      60,    61,    61,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    62,    62,    62,    62,    63,    63,    64,    65,
      66,    67,    67,    68,    68,    69,    70,    70,    70,    70,
      70,    70,    70,    70,    70,    71
};

/* YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     3,     0,     2,     5,     1,     1,     1,     1,
       3,     3,     1,     2,     1,     1,     1,     1,     1,     1,
       1,     4,     5,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     1,     1,     1,     5,     5,     8,     3,
       4,     1,     1,     7,     5,     5,     3,     3,     6,     3,
       3,     3,     3,     3,     3,     3
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
#line 76 "src/parser.y"
                                  {
        char *temp = malloc(strlen((yyvsp[-2].str)) + (constantesGlobais ? strlen(constantesGlobais) : 0) + strlen((yyvsp[-1].str)) + strlen((yyvsp[0].str)) + 100);
        sprintf(temp, "#include <Arduino.h>\n#include <WiFi.h>\n\n%s%s%s%s", (yyvsp[-2].str), constantesGlobais ? constantesGlobais : "", (yyvsp[-1].str), (yyvsp[0].str));
        appendCode(temp);
        (yyval.str) = temp;
    }
#line 1283 "temp/parser.tab.c"
    break;

  case 3: /* declaracoes: %empty  */
#line 84 "src/parser.y"
                { (yyval.str) = strdup(""); }
#line 1289 "temp/parser.tab.c"
    break;

  case 4: /* declaracoes: declaracao declaracoes  */
#line 85 "src/parser.y"
                             { 
        char *temp = malloc(strlen((yyvsp[-1].str)) + strlen((yyvsp[0].str)) + 2);
        sprintf(temp, "%s\n%s", (yyvsp[-1].str), (yyvsp[0].str));
        (yyval.str) = temp;
    }
#line 1299 "temp/parser.tab.c"
    break;

  case 5: /* declaracao: VAR tipo DOISPONTOS listaIdentificadores PONTOEVIRGULA  */
#line 93 "src/parser.y"
                                                           {
        (yyval.str) = strdup((yyvsp[-1].str));
    }
#line 1307 "temp/parser.tab.c"
    break;

  case 6: /* tipo: INTEIRO  */
#line 99 "src/parser.y"
            { 
        if (tipo_atual) free(tipo_atual);
        tipo_atual = strdup("int"); 
        (yyval.str) = tipo_atual; 
    }
#line 1317 "temp/parser.tab.c"
    break;

  case 7: /* tipo: TEXTO  */
#line 104 "src/parser.y"
            { 
        if (tipo_atual) free(tipo_atual);
        tipo_atual = strdup("String"); 
        (yyval.str) = tipo_atual; 
    }
#line 1327 "temp/parser.tab.c"
    break;

  case 8: /* tipo: BOOLEANO  */
#line 109 "src/parser.y"
               { 
        if (tipo_atual) free(tipo_atual);
        tipo_atual = strdup("bool"); 
        (yyval.str) = tipo_atual; 
    }
#line 1337 "temp/parser.tab.c"
    break;

  case 9: /* listaIdentificadores: IDENTIFICADOR  */
#line 117 "src/parser.y"
                  { 
        if (!tipo_atual) { 
            yyerror("Erro: tipo não definido antes dos identificadores."); 
            YYABORT; 
        }
        (yyval.str) = malloc(strlen(tipo_atual) + strlen((yyvsp[0].str)) + 10);
        sprintf((yyval.str), "%s %s;\n", tipo_atual, (yyvsp[0].str));
    }
#line 1350 "temp/parser.tab.c"
    break;

  case 10: /* listaIdentificadores: listaIdentificadores VIRGULA IDENTIFICADOR  */
#line 125 "src/parser.y"
                                                 {
        if (!tipo_atual) { 
            yyerror("Erro: tipo não definido antes dos identificadores."); 
            YYABORT; 
        }
        char *temp = malloc(strlen((yyvsp[-2].str)) + strlen(tipo_atual) + strlen((yyvsp[0].str)) + 10);
        sprintf(temp, "%s%s %s;", (yyvsp[-2].str), tipo_atual, (yyvsp[0].str));
        (yyval.str) = temp;
    }
#line 1364 "temp/parser.tab.c"
    break;

  case 11: /* configuracao: CONFIG comandos FIM  */
#line 137 "src/parser.y"
                        {
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 50);
        sprintf(codigo, "\nvoid setup()\n{\n%s}\n", (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1374 "temp/parser.tab.c"
    break;

  case 12: /* comandos: comando  */
#line 145 "src/parser.y"
            { (yyval.str) = strdup((yyvsp[0].str)); }
#line 1380 "temp/parser.tab.c"
    break;

  case 13: /* comandos: comandos comando  */
#line 146 "src/parser.y"
                       {
        char *temp = malloc(strlen((yyvsp[-1].str)) + strlen((yyvsp[0].str)) + 1);
        strcpy(temp, (yyvsp[-1].str));
        strcat(temp, (yyvsp[0].str));
        (yyval.str) = temp;
    }
#line 1391 "temp/parser.tab.c"
    break;

  case 21: /* atribuicao: IDENTIFICADOR IGUAL expressao PONTOEVIRGULA  */
#line 165 "src/parser.y"
                                                {
        char *codigo = malloc(strlen((yyvsp[-3].str)) + strlen((yyvsp[-1].str)) + 10);
        sprintf(codigo, "%s = %s;\n", (yyvsp[-3].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1401 "temp/parser.tab.c"
    break;

  case 22: /* atribuicao: IDENTIFICADOR IGUAL LER_DIGITAL IDENTIFICADOR PONTOEVIRGULA  */
#line 170 "src/parser.y"
                                                                  {
        char *codigo = malloc(strlen((yyvsp[-4].str)) + strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "%s = digitalRead(%s);\n", (yyvsp[-4].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1411 "temp/parser.tab.c"
    break;

  case 23: /* expressao: expressao MAIS expressao  */
#line 178 "src/parser.y"
                             {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s + %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1420 "temp/parser.tab.c"
    break;

  case 24: /* expressao: expressao MENOS expressao  */
#line 182 "src/parser.y"
                                {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s - %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1429 "temp/parser.tab.c"
    break;

  case 25: /* expressao: expressao MULTIPLICACAO expressao  */
#line 186 "src/parser.y"
                                        {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s * %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1438 "temp/parser.tab.c"
    break;

  case 26: /* expressao: expressao DIVISAO expressao  */
#line 190 "src/parser.y"
                                  {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s / %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1447 "temp/parser.tab.c"
    break;

  case 27: /* expressao: expressao IGUAL_IGUAL expressao  */
#line 195 "src/parser.y"
                                      {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s == %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1456 "temp/parser.tab.c"
    break;

  case 28: /* expressao: expressao DIFERENTE expressao  */
#line 199 "src/parser.y"
                                    {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s != %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1465 "temp/parser.tab.c"
    break;

  case 29: /* expressao: expressao MENOR expressao  */
#line 203 "src/parser.y"
                                {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s < %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1474 "temp/parser.tab.c"
    break;

  case 30: /* expressao: expressao MAIOR expressao  */
#line 207 "src/parser.y"
                                {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s > %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1483 "temp/parser.tab.c"
    break;

  case 31: /* expressao: expressao MENOR_IGUAL expressao  */
#line 211 "src/parser.y"
                                      {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s <= %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1492 "temp/parser.tab.c"
    break;

  case 32: /* expressao: expressao MAIOR_IGUAL expressao  */
#line 215 "src/parser.y"
                                      {
        (yyval.str) = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[0].str)) + 4);
        sprintf((yyval.str), "%s >= %s", (yyvsp[-2].str), (yyvsp[0].str));
    }
#line 1501 "temp/parser.tab.c"
    break;

  case 33: /* expressao: NUMERO  */
#line 219 "src/parser.y"
             {
        (yyval.str) = malloc(20);
        sprintf((yyval.str), "%d", (yyvsp[0].num));
    }
#line 1510 "temp/parser.tab.c"
    break;

  case 34: /* expressao: IDENTIFICADOR  */
#line 223 "src/parser.y"
                    {
        (yyval.str) = strdup((yyvsp[0].str));
    }
#line 1518 "temp/parser.tab.c"
    break;

  case 35: /* expressao: STRING  */
#line 226 "src/parser.y"
             {
        (yyval.str) = strdup((yyvsp[0].str));
    }
#line 1526 "temp/parser.tab.c"
    break;

  case 36: /* configuracaoPino: CONFIGURAR IDENTIFICADOR COMO SAIDA PONTOEVIRGULA  */
#line 232 "src/parser.y"
                                                      {
        char *codigo = malloc(strlen((yyvsp[-3].str)) + 30);
        sprintf(codigo, "pinMode(%s, OUTPUT);\n", (yyvsp[-3].str));
        (yyval.str) = codigo;
    }
#line 1536 "temp/parser.tab.c"
    break;

  case 37: /* configuracaoPino: CONFIGURAR IDENTIFICADOR COMO ENTRADA PONTOEVIRGULA  */
#line 237 "src/parser.y"
                                                          {
        char *codigo = malloc(strlen((yyvsp[-3].str)) + 30);
        sprintf(codigo, "pinMode(%s, INPUT);\n", (yyvsp[-3].str));
        (yyval.str) = codigo;
    }
#line 1546 "temp/parser.tab.c"
    break;

  case 38: /* configuracaoPWM: CONFIGURARPWM IDENTIFICADOR COM FREQUENCIA NUMERO RESOLUCAO NUMERO PONTOEVIRGULA  */
#line 245 "src/parser.y"
                                                                                     {
        char constantes[200];
        char codigo[200];

        // Gerando as constantes globais
        sprintf(constantes, "\nconst int canalPWM = 0;\nconst int frequencia = %d;\nconst int resolucao = %d;\n", (yyvsp[-3].num), (yyvsp[-1].num));
        appendConstantes(constantes);  // Armazena como global

        // Código do setup
        sprintf(codigo, "ledcSetup(canalPWM, frequencia, resolucao);\nledcAttachPin(%s, canalPWM);\n", (yyvsp[-6].str));
        (yyval.str) = strdup(codigo);
    }
#line 1563 "temp/parser.tab.c"
    break;

  case 39: /* configuracaoSerial: CONFIGURARSERIAL NUMERO PONTOEVIRGULA  */
#line 259 "src/parser.y"
                                          {
        char *codigo = malloc(50);
        sprintf(codigo, "Serial.begin(%d);\n", (yyvsp[-1].num));
        (yyval.str) = codigo;
    }
#line 1573 "temp/parser.tab.c"
    break;

  case 40: /* conexaoWifi: CONECTARWIFI IDENTIFICADOR IDENTIFICADOR PONTOEVIRGULA  */
#line 267 "src/parser.y"
                                                           {
        char *codigo = malloc(strlen((yyvsp[-2].str)) + strlen((yyvsp[-1].str)) + 170);
        sprintf(codigo, "WiFi.begin(%s.c_str(), %s.c_str());\nwhile (WiFi.status() != WL_CONNECTED)\n{\n    delay(500);\n    Serial.println(\"Conectando ao WiFi...\");\n}\nSerial.println(\"Conectado ao WiFi!\");\n", (yyvsp[-2].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1583 "temp/parser.tab.c"
    break;

  case 41: /* controleFluxo: condicional  */
#line 275 "src/parser.y"
                { (yyval.str) = (yyvsp[0].str); }
#line 1589 "temp/parser.tab.c"
    break;

  case 42: /* controleFluxo: repeticao  */
#line 276 "src/parser.y"
                { (yyval.str) = (yyvsp[0].str); }
#line 1595 "temp/parser.tab.c"
    break;

  case 43: /* condicional: SE expressao ENTAO comandos SENAO comandos FIM  */
#line 280 "src/parser.y"
                                                   {
        char *codigo = malloc(strlen((yyvsp[-5].str)) + strlen((yyvsp[-3].str)) + strlen((yyvsp[-1].str)) + 50);
        sprintf(codigo, "if (%s)\n{\n%s}\nelse\n{\n%s}\n", (yyvsp[-5].str), (yyvsp[-3].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1605 "temp/parser.tab.c"
    break;

  case 44: /* condicional: SE expressao ENTAO comandos FIM  */
#line 285 "src/parser.y"
                                      {
        char *codigo = malloc(strlen((yyvsp[-3].str)) + strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "if (%s)\n{\n%s}\n", (yyvsp[-3].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1615 "temp/parser.tab.c"
    break;

  case 45: /* repeticao: ENQUANTO expressao FIM comandos FIM  */
#line 293 "src/parser.y"
                                        {
        char *codigo = malloc(strlen((yyvsp[-3].str)) + strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "while (%s)\n{\n%s}\n", (yyvsp[-3].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1625 "temp/parser.tab.c"
    break;

  case 46: /* operacaoHardware: LIGAR IDENTIFICADOR PONTOEVIRGULA  */
#line 301 "src/parser.y"
                                      {
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 20);
        sprintf(codigo, "digitalWrite(%s, HIGH);\n", (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1635 "temp/parser.tab.c"
    break;

  case 47: /* operacaoHardware: DESLIGAR IDENTIFICADOR PONTOEVIRGULA  */
#line 306 "src/parser.y"
                                           {
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 25);
        sprintf(codigo, "digitalWrite(%s, LOW);\n", (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1645 "temp/parser.tab.c"
    break;

  case 48: /* operacaoHardware: AJUSTARPWM IDENTIFICADOR COM VALOR IDENTIFICADOR PONTOEVIRGULA  */
#line 311 "src/parser.y"
                                                                     {
        char *codigo = malloc(strlen((yyvsp[-4].str)) + strlen((yyvsp[-1].str)) + 40);
        sprintf(codigo, "ledcWrite(%s, %s);\n", (yyvsp[-4].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1655 "temp/parser.tab.c"
    break;

  case 49: /* operacaoHardware: ESPERAR NUMERO PONTOEVIRGULA  */
#line 316 "src/parser.y"
                                   {
        char *codigo = malloc(20);
        sprintf(codigo, "delay(%d);\n", (yyvsp[-1].num));
        (yyval.str) = codigo;
    }
#line 1665 "temp/parser.tab.c"
    break;

  case 50: /* operacaoHardware: ESCREVER_SERIAL STRING PONTOEVIRGULA  */
#line 321 "src/parser.y"
                                           {
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "Serial.println(%s);\n", (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1675 "temp/parser.tab.c"
    break;

  case 51: /* operacaoHardware: LER_SERIAL IDENTIFICADOR PONTOEVIRGULA  */
#line 326 "src/parser.y"
                                             {
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "%s = Serial.readString();\n", (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1685 "temp/parser.tab.c"
    break;

  case 52: /* operacaoHardware: ENVIAR_HTTP STRING PONTOEVIRGULA  */
#line 331 "src/parser.y"
                                       {
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 50);
        sprintf(codigo, "http.begin(%s);\nhttp.GET();\n", (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1695 "temp/parser.tab.c"
    break;

  case 53: /* operacaoHardware: LER_DIGITAL IDENTIFICADOR PONTOEVIRGULA  */
#line 336 "src/parser.y"
                                              {
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "%s = digitalRead(%s);\n", (yyvsp[-1].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1705 "temp/parser.tab.c"
    break;

  case 54: /* operacaoHardware: LER_ANALOGICO IDENTIFICADOR PONTOEVIRGULA  */
#line 341 "src/parser.y"
                                                {
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "%s = analogRead(%s);\n", (yyvsp[-1].str), (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1715 "temp/parser.tab.c"
    break;

  case 55: /* loop: REPITA comandos FIM  */
#line 349 "src/parser.y"
                        {
        char *codigo = malloc(strlen((yyvsp[-1].str)) + 30);
        sprintf(codigo, "\nvoid loop()\n{\n%s}\n", (yyvsp[-1].str));
        (yyval.str) = codigo;
    }
#line 1725 "temp/parser.tab.c"
    break;


#line 1729 "temp/parser.tab.c"

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

#line 356 "src/parser.y"


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

    return 0;
}
