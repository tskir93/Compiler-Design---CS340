/* A Bison parser, made by GNU Bison 3.0.2.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2013 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

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

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.2"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 8 "parser.y" /* yacc.c:339  */


#include <stdio.h>
#include <string.h>
#include "parser.h"
#include "functions.h"

int yylex(void);
int yyerror (char* yaccProvidedMessage);

int scope = 0;

SymbolTableEntry *SymTable; 

extern char* yytext; 				
extern int yylineno;  				
extern FILE* yyin; 					


#line 86 "parser.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "parser.h".  */
#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    CONST_INT = 258,
    IF = 259,
    ELSE = 260,
    WHILE = 261,
    FOR = 262,
    FUNCTION = 263,
    RETURN = 264,
    BREAK = 265,
    CONTINUE = 266,
    AND = 267,
    NOT = 268,
    OR = 269,
    LOCAL = 270,
    TRUE = 271,
    FALSE = 272,
    NIL = 273,
    ASSIGN = 274,
    PLUS = 275,
    MINUS = 276,
    MULTIPLY = 277,
    DEVIDE = 278,
    PERCENTAGE = 279,
    EQUAL = 280,
    NOTEQUAL = 281,
    DOUBLE_PLUS = 282,
    DOUBLE_MINUS = 283,
    GREATER_THAN = 284,
    LESS_THAN = 285,
    GR_EQ = 286,
    LE_EQ = 287,
    ID = 288,
    STRING = 289,
    DOT = 290,
    DOUBLE_DOT = 291,
    UNDERSCORE = 292,
    COLON = 293,
    DOUBLE_COL = 294,
    LEFT_BR = 295,
    RIGHT_BR = 296,
    LEFT_SQ_BR = 297,
    RIGHT_SQ_BR = 298,
    LEFT_PAR = 299,
    RIGHT_PAR = 300,
    SEMICOLON = 301,
    COMMA = 302,
    CONST_REAL = 303,
    UMINUS = 304
  };
#endif
/* Tokens.  */
#define CONST_INT 258
#define IF 259
#define ELSE 260
#define WHILE 261
#define FOR 262
#define FUNCTION 263
#define RETURN 264
#define BREAK 265
#define CONTINUE 266
#define AND 267
#define NOT 268
#define OR 269
#define LOCAL 270
#define TRUE 271
#define FALSE 272
#define NIL 273
#define ASSIGN 274
#define PLUS 275
#define MINUS 276
#define MULTIPLY 277
#define DEVIDE 278
#define PERCENTAGE 279
#define EQUAL 280
#define NOTEQUAL 281
#define DOUBLE_PLUS 282
#define DOUBLE_MINUS 283
#define GREATER_THAN 284
#define LESS_THAN 285
#define GR_EQ 286
#define LE_EQ 287
#define ID 288
#define STRING 289
#define DOT 290
#define DOUBLE_DOT 291
#define UNDERSCORE 292
#define COLON 293
#define DOUBLE_COL 294
#define LEFT_BR 295
#define RIGHT_BR 296
#define LEFT_SQ_BR 297
#define RIGHT_SQ_BR 298
#define LEFT_PAR 299
#define RIGHT_PAR 300
#define SEMICOLON 301
#define COMMA 302
#define CONST_REAL 303
#define UMINUS 304

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef union YYSTYPE YYSTYPE;
union YYSTYPE
{
#line 30 "parser.y" /* yacc.c:355  */

    int intVal;
    float floatVal;
    char *stringVal;

#line 230 "parser.c" /* yacc.c:355  */
};
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 245 "parser.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

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

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
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


#if ! defined yyoverflow || YYERROR_VERBOSE

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
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
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
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  68
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   640

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  50
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  29
/* YYNRULES -- Number of rules.  */
#define YYNRULES  89
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  177

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   304

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
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
      45,    46,    47,    48,    49
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint8 yyrline[] =
{
       0,    80,    80,    83,    84,    87,    88,    89,    90,    91,
      92,    93,    94,    95,    96,    99,   100,   101,   102,   103,
     104,   105,   106,   107,   108,   109,   110,   111,   112,   113,
     118,   119,   120,   121,   122,   123,   124,   125,   128,   131,
     132,   133,   134,   135,   139,   140,   141,   142,   146,   147,
     148,   149,   152,   153,   154,   157,   158,   161,   165,   168,
     169,   172,   173,   174,   178,   179,   182,   183,   187,   190,
     193,   194,   198,   199,   200,   201,   202,   203,   208,   209,
     210,   213,   214,   217,   220,   221,   224,   228,   231,   232
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "CONST_INT", "IF", "ELSE", "WHILE",
  "FOR", "FUNCTION", "RETURN", "BREAK", "CONTINUE", "AND", "NOT", "OR",
  "LOCAL", "TRUE", "FALSE", "NIL", "ASSIGN", "PLUS", "MINUS", "MULTIPLY",
  "DEVIDE", "PERCENTAGE", "EQUAL", "NOTEQUAL", "DOUBLE_PLUS",
  "DOUBLE_MINUS", "GREATER_THAN", "LESS_THAN", "GR_EQ", "LE_EQ", "ID",
  "STRING", "DOT", "DOUBLE_DOT", "UNDERSCORE", "COLON", "DOUBLE_COL",
  "LEFT_BR", "RIGHT_BR", "LEFT_SQ_BR", "RIGHT_SQ_BR", "LEFT_PAR",
  "RIGHT_PAR", "SEMICOLON", "COMMA", "CONST_REAL", "UMINUS", "$accept",
  "program", "stmts", "stmt", "expr", "term", "assignexpr", "primary",
  "lvalue", "member", "call", "callsuffix", "normcall", "methodcall",
  "elist", "elists", "objectdef", "indexed", "indexedelem", "block",
  "funcdef", "const", "idlist", "idlists", "ifstmt", "else", "whilestmt",
  "forstmt", "returnstmt", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304
};
# endif

#define YYPACT_NINF -136

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-136)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  (!!((Yytable_value) == (-1)))

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     156,  -136,   -32,   -23,    -9,   -27,    15,    -5,    -2,   232,
      12,  -136,  -136,  -136,   232,   -10,   -10,  -136,  -136,    13,
     156,    78,   198,  -136,  -136,    50,  -136,   156,   317,  -136,
    -136,  -136,   106,  -136,    16,  -136,  -136,  -136,  -136,  -136,
    -136,  -136,  -136,   232,   232,   232,     8,    23,  -136,   344,
    -136,  -136,  -136,  -136,  -136,    54,   -22,    16,   -22,  -136,
      36,   232,   261,    37,    39,    32,   398,    40,  -136,  -136,
     232,   232,   232,   232,   232,   232,   232,   232,   232,   232,
     232,   232,   232,  -136,   232,  -136,  -136,    53,    55,   232,
     232,  -136,  -136,  -136,    59,   232,   232,   424,   450,    41,
      23,    51,    52,  -136,    62,  -136,   546,   232,  -136,  -136,
      60,  -136,    64,   595,   582,   -13,   -13,  -136,  -136,  -136,
     608,   608,   275,   275,   275,   275,   567,  -136,    65,   476,
      68,  -136,   500,    69,   156,   156,   232,    74,    71,    70,
      64,   232,   289,  -136,  -136,   232,   232,  -136,  -136,  -136,
    -136,   118,  -136,   371,    70,    77,  -136,  -136,   524,   232,
      82,    83,   156,  -136,   232,  -136,    71,  -136,  -136,  -136,
    -136,  -136,    85,  -136,    84,   156,  -136
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
       4,    72,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    76,    77,    75,     0,     0,     0,    44,    74,     0,
       0,     0,     0,    14,    73,     0,     2,     4,     0,    29,
      15,    37,    39,    47,    40,    41,    12,    13,    43,     6,
       7,     8,     9,     0,     0,     0,     0,    80,    88,     0,
      10,    11,    32,    45,    31,     0,    33,     0,    35,    46,
       0,     0,    59,     0,     0,    66,     0,     0,     1,     3,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     5,     0,    34,    36,     0,     0,     0,
       0,    53,    55,    56,     0,     0,     0,     0,     0,     0,
      80,    78,     0,    89,     0,    69,     0,    63,    64,    65,
       0,    30,    42,    27,    28,    16,    17,    18,    19,    20,
      25,    26,    21,    23,    22,    24,    38,    48,     0,     0,
       0,    50,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    61,    60,    67,     0,     0,    49,    57,    51,
      52,    85,    86,     0,     0,    81,    79,    71,     0,    63,
       0,     0,     0,    83,     0,    70,     0,    68,    62,    54,
      58,    84,     0,    82,     0,     0,    87
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
    -136,  -136,   105,   -19,    -6,  -136,  -136,  -136,     9,  -136,
      11,  -136,  -136,  -136,   -43,   -21,  -136,    26,  -136,  -135,
     -15,  -136,    44,   -29,  -136,  -136,  -136,  -136,  -136
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    25,    26,    27,    28,    29,    30,    31,    32,    33,
      34,    91,    92,    93,    63,   143,    35,    64,    65,    36,
      37,    38,   102,   156,    39,   163,    40,    41,    42
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int16 yytable[] =
{
      49,    60,    99,    52,   157,    10,    46,    67,    54,    74,
      75,    76,    43,    87,    88,    62,    66,    47,     1,   165,
      89,    44,    90,    17,    56,    58,    57,    57,     9,    19,
      10,    11,    12,    13,    55,    45,    14,    97,    98,    62,
     104,    50,    15,    16,    51,    53,    59,   130,    17,    18,
      68,    94,   100,   133,    19,   106,   101,    21,    95,    22,
      96,    48,     5,    24,   113,   114,   115,   116,   117,   118,
     119,   120,   121,   122,   123,   124,   125,   105,   126,   110,
     108,     1,   109,   129,    62,   112,   127,   136,   128,   132,
      62,     9,   131,    10,    11,    12,    13,   139,   138,    14,
      61,   142,   160,   161,   155,    15,    16,   140,   145,   146,
      20,    17,    18,   148,   150,   151,   152,    19,    61,   154,
      21,   172,    22,   162,   166,    84,    24,   169,   170,   175,
     153,   174,    69,    85,    86,   158,   144,   173,   168,    62,
      62,    87,    88,   171,   137,     0,     0,     0,    89,     0,
      90,     0,     0,   142,     0,     0,   176,     0,    62,     1,
       2,     0,     3,     4,     5,     6,     7,     8,     0,     9,
       0,    10,    11,    12,    13,     0,     0,    14,     0,     0,
       0,     0,     0,    15,    16,     0,     0,     0,     0,    17,
      18,     0,     0,     0,     0,    19,    20,     0,    21,     0,
      22,     1,    23,     0,    24,     0,     5,     0,     0,     0,
       0,     9,     0,    10,    11,    12,    13,     0,     0,    14,
       0,     0,     0,     0,     0,    15,    16,     0,     0,     0,
       0,    17,    18,     0,     0,     1,     0,    19,     0,     0,
      21,     0,    22,     0,     0,     9,    24,    10,    11,    12,
      13,     0,     0,    14,     0,     0,     0,     0,     0,    15,
      16,     0,     0,     0,     0,    17,    18,     0,     0,     0,
       0,    19,     0,    70,    21,    71,    22,     0,     0,     0,
      24,    72,    73,    74,    75,    76,    77,    78,     0,     0,
      79,    80,    81,    82,     0,    72,    73,    74,    75,    76,
       0,    70,     0,    71,    -1,    -1,    -1,    -1,   107,    72,
      73,    74,    75,    76,    77,    78,     0,     0,    79,    80,
      81,    82,     0,     0,     0,     0,     0,     0,     0,    70,
       0,    71,     0,     0,     0,     0,   159,    72,    73,    74,
      75,    76,    77,    78,     0,     0,    79,    80,    81,    82,
       0,     0,     0,     0,     0,     0,    70,     0,    71,     0,
       0,     0,     0,    83,    72,    73,    74,    75,    76,    77,
      78,     0,     0,    79,    80,    81,    82,     0,     0,     0,
       0,     0,     0,    70,     0,    71,     0,     0,     0,     0,
     103,    72,    73,    74,    75,    76,    77,    78,     0,     0,
      79,    80,    81,    82,     0,     0,     0,     0,     0,     0,
      70,     0,    71,     0,     0,     0,     0,   164,    72,    73,
      74,    75,    76,    77,    78,     0,     0,    79,    80,    81,
      82,     0,     0,     0,     0,     0,    70,     0,    71,     0,
       0,     0,     0,   111,    72,    73,    74,    75,    76,    77,
      78,     0,     0,    79,    80,    81,    82,     0,     0,     0,
       0,     0,    70,     0,    71,     0,     0,     0,     0,   134,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    79,
      80,    81,    82,     0,     0,     0,     0,     0,    70,     0,
      71,     0,     0,     0,     0,   135,    72,    73,    74,    75,
      76,    77,    78,     0,     0,    79,    80,    81,    82,     0,
       0,     0,    70,     0,    71,     0,     0,     0,     0,   147,
      72,    73,    74,    75,    76,    77,    78,     0,     0,    79,
      80,    81,    82,     0,     0,     0,    70,     0,    71,     0,
       0,     0,     0,   149,    72,    73,    74,    75,    76,    77,
      78,     0,     0,    79,    80,    81,    82,     0,    70,     0,
      71,     0,     0,     0,     0,   167,    72,    73,    74,    75,
      76,    77,    78,     0,     0,    79,    80,    81,    82,    70,
       0,    71,     0,     0,   141,     0,     0,    72,    73,    74,
      75,    76,    77,    78,    70,     0,    79,    80,    81,    82,
       0,     0,    72,    73,    74,    75,    76,    77,    78,     0,
       0,    79,    80,    81,    82,    72,    73,    74,    75,    76,
      77,    78,     0,     0,    79,    80,    81,    82,    72,    73,
      74,    75,    76,    -1,    -1,     0,     0,    79,    80,    81,
      82
};

static const yytype_int16 yycheck[] =
{
       6,    20,    45,     9,   139,    15,    33,    22,    14,    22,
      23,    24,    44,    35,    36,    21,    22,    44,     3,   154,
      42,    44,    44,    33,    15,    16,    15,    16,    13,    39,
      15,    16,    17,    18,    44,    44,    21,    43,    44,    45,
      55,    46,    27,    28,    46,    33,    33,    90,    33,    34,
       0,    35,    44,    96,    39,    61,    33,    42,    42,    44,
      44,    46,     8,    48,    70,    71,    72,    73,    74,    75,
      76,    77,    78,    79,    80,    81,    82,    41,    84,    47,
      43,     3,    43,    89,    90,    45,    33,    46,    33,    95,
      96,    13,    33,    15,    16,    17,    18,    45,    47,    21,
      40,   107,   145,   146,    33,    27,    28,    45,    44,    44,
      40,    33,    34,    45,    45,   134,   135,    39,    40,    45,
      42,   164,    44,     5,    47,    19,    48,    45,    45,    45,
     136,    46,    27,    27,    28,   141,   110,   166,   159,   145,
     146,    35,    36,   162,   100,    -1,    -1,    -1,    42,    -1,
      44,    -1,    -1,   159,    -1,    -1,   175,    -1,   164,     3,
       4,    -1,     6,     7,     8,     9,    10,    11,    -1,    13,
      -1,    15,    16,    17,    18,    -1,    -1,    21,    -1,    -1,
      -1,    -1,    -1,    27,    28,    -1,    -1,    -1,    -1,    33,
      34,    -1,    -1,    -1,    -1,    39,    40,    -1,    42,    -1,
      44,     3,    46,    -1,    48,    -1,     8,    -1,    -1,    -1,
      -1,    13,    -1,    15,    16,    17,    18,    -1,    -1,    21,
      -1,    -1,    -1,    -1,    -1,    27,    28,    -1,    -1,    -1,
      -1,    33,    34,    -1,    -1,     3,    -1,    39,    -1,    -1,
      42,    -1,    44,    -1,    -1,    13,    48,    15,    16,    17,
      18,    -1,    -1,    21,    -1,    -1,    -1,    -1,    -1,    27,
      28,    -1,    -1,    -1,    -1,    33,    34,    -1,    -1,    -1,
      -1,    39,    -1,    12,    42,    14,    44,    -1,    -1,    -1,
      48,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      29,    30,    31,    32,    -1,    20,    21,    22,    23,    24,
      -1,    12,    -1,    14,    29,    30,    31,    32,    47,    20,
      21,    22,    23,    24,    25,    26,    -1,    -1,    29,    30,
      31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    12,
      -1,    14,    -1,    -1,    -1,    -1,    47,    20,    21,    22,
      23,    24,    25,    26,    -1,    -1,    29,    30,    31,    32,
      -1,    -1,    -1,    -1,    -1,    -1,    12,    -1,    14,    -1,
      -1,    -1,    -1,    46,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    29,    30,    31,    32,    -1,    -1,    -1,
      -1,    -1,    -1,    12,    -1,    14,    -1,    -1,    -1,    -1,
      46,    20,    21,    22,    23,    24,    25,    26,    -1,    -1,
      29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
      12,    -1,    14,    -1,    -1,    -1,    -1,    46,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    29,    30,    31,
      32,    -1,    -1,    -1,    -1,    -1,    12,    -1,    14,    -1,
      -1,    -1,    -1,    45,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    29,    30,    31,    32,    -1,    -1,    -1,
      -1,    -1,    12,    -1,    14,    -1,    -1,    -1,    -1,    45,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    29,
      30,    31,    32,    -1,    -1,    -1,    -1,    -1,    12,    -1,
      14,    -1,    -1,    -1,    -1,    45,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    29,    30,    31,    32,    -1,
      -1,    -1,    12,    -1,    14,    -1,    -1,    -1,    -1,    43,
      20,    21,    22,    23,    24,    25,    26,    -1,    -1,    29,
      30,    31,    32,    -1,    -1,    -1,    12,    -1,    14,    -1,
      -1,    -1,    -1,    43,    20,    21,    22,    23,    24,    25,
      26,    -1,    -1,    29,    30,    31,    32,    -1,    12,    -1,
      14,    -1,    -1,    -1,    -1,    41,    20,    21,    22,    23,
      24,    25,    26,    -1,    -1,    29,    30,    31,    32,    12,
      -1,    14,    -1,    -1,    38,    -1,    -1,    20,    21,    22,
      23,    24,    25,    26,    12,    -1,    29,    30,    31,    32,
      -1,    -1,    20,    21,    22,    23,    24,    25,    26,    -1,
      -1,    29,    30,    31,    32,    20,    21,    22,    23,    24,
      25,    26,    -1,    -1,    29,    30,    31,    32,    20,    21,
      22,    23,    24,    25,    26,    -1,    -1,    29,    30,    31,
      32
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,     3,     4,     6,     7,     8,     9,    10,    11,    13,
      15,    16,    17,    18,    21,    27,    28,    33,    34,    39,
      40,    42,    44,    46,    48,    51,    52,    53,    54,    55,
      56,    57,    58,    59,    60,    66,    69,    70,    71,    74,
      76,    77,    78,    44,    44,    44,    33,    44,    46,    54,
      46,    46,    54,    33,    54,    44,    58,    60,    58,    33,
      53,    40,    54,    64,    67,    68,    54,    70,     0,    52,
      12,    14,    20,    21,    22,    23,    24,    25,    26,    29,
      30,    31,    32,    46,    19,    27,    28,    35,    36,    42,
      44,    61,    62,    63,    35,    42,    44,    54,    54,    64,
      44,    33,    72,    46,    70,    41,    54,    47,    43,    43,
      47,    45,    45,    54,    54,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    33,    33,    54,
      64,    33,    54,    64,    45,    45,    46,    72,    47,    45,
      45,    38,    54,    65,    67,    44,    44,    43,    45,    43,
      45,    53,    53,    54,    45,    33,    73,    69,    54,    47,
      64,    64,     5,    75,    46,    69,    47,    41,    65,    45,
      45,    53,    64,    73,    46,    45,    53
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    50,    51,    52,    52,    53,    53,    53,    53,    53,
      53,    53,    53,    53,    53,    54,    54,    54,    54,    54,
      54,    54,    54,    54,    54,    54,    54,    54,    54,    54,
      55,    55,    55,    55,    55,    55,    55,    55,    56,    57,
      57,    57,    57,    57,    58,    58,    58,    58,    59,    59,
      59,    59,    60,    60,    60,    61,    61,    62,    63,    64,
      64,    65,    65,    65,    66,    66,    67,    67,    68,    69,
      70,    70,    71,    71,    71,    71,    71,    71,    72,    72,
      72,    73,    73,    74,    75,    75,    76,    77,    78,    78
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     1,     2,     0,     2,     1,     1,     1,     1,
       2,     2,     1,     1,     1,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     1,
       3,     2,     2,     2,     2,     2,     2,     1,     3,     1,
       1,     1,     3,     1,     1,     2,     2,     1,     3,     4,
       3,     4,     4,     2,     6,     1,     1,     3,     5,     1,
       3,     1,     3,     0,     3,     3,     1,     3,     5,     3,
       6,     5,     1,     1,     1,     1,     1,     1,     1,     3,
       0,     1,     3,     6,     2,     0,     5,    10,     2,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



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

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
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
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
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
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
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


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
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
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

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

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
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

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

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
| yyreduce -- Do a reduction.  |
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
        case 5:
#line 87 "parser.y" /* yacc.c:1646  */
    {printf("stmt -> expr;\n");}
#line 1537 "parser.c" /* yacc.c:1646  */
    break;

  case 6:
#line 88 "parser.y" /* yacc.c:1646  */
    {printf("stmt -> ifstmt\n");}
#line 1543 "parser.c" /* yacc.c:1646  */
    break;

  case 7:
#line 89 "parser.y" /* yacc.c:1646  */
    {printf("stmt -> whilestmt\n");}
#line 1549 "parser.c" /* yacc.c:1646  */
    break;

  case 8:
#line 90 "parser.y" /* yacc.c:1646  */
    {printf("stmt -> forstmt\n");}
#line 1555 "parser.c" /* yacc.c:1646  */
    break;

  case 9:
#line 91 "parser.y" /* yacc.c:1646  */
    {printf("stmt -> returnstmt\n");}
#line 1561 "parser.c" /* yacc.c:1646  */
    break;

  case 10:
#line 92 "parser.y" /* yacc.c:1646  */
    {printf("stmt -> break;\n");}
#line 1567 "parser.c" /* yacc.c:1646  */
    break;

  case 11:
#line 93 "parser.y" /* yacc.c:1646  */
    {printf("stmt -> continue;\n");}
#line 1573 "parser.c" /* yacc.c:1646  */
    break;

  case 12:
#line 94 "parser.y" /* yacc.c:1646  */
    {printf("stmt -> block\n");}
#line 1579 "parser.c" /* yacc.c:1646  */
    break;

  case 13:
#line 95 "parser.y" /* yacc.c:1646  */
    {printf("stmt -> funcdef\n");}
#line 1585 "parser.c" /* yacc.c:1646  */
    break;

  case 14:
#line 96 "parser.y" /* yacc.c:1646  */
    {printf("stmt -> ;\n");}
#line 1591 "parser.c" /* yacc.c:1646  */
    break;

  case 15:
#line 99 "parser.y" /* yacc.c:1646  */
    {printf("expr -> assignexpr\n");}
#line 1597 "parser.c" /* yacc.c:1646  */
    break;

  case 16:
#line 100 "parser.y" /* yacc.c:1646  */
    {printf("expr -> expr op expr\n");}
#line 1603 "parser.c" /* yacc.c:1646  */
    break;

  case 17:
#line 101 "parser.y" /* yacc.c:1646  */
    {printf("expr -> expr op expr\n");}
#line 1609 "parser.c" /* yacc.c:1646  */
    break;

  case 18:
#line 102 "parser.y" /* yacc.c:1646  */
    {printf("expr -> expr op expr\n");}
#line 1615 "parser.c" /* yacc.c:1646  */
    break;

  case 19:
#line 103 "parser.y" /* yacc.c:1646  */
    {printf("expr -> expr op expr\n");}
#line 1621 "parser.c" /* yacc.c:1646  */
    break;

  case 20:
#line 104 "parser.y" /* yacc.c:1646  */
    {printf("expr -> expr op expr\n");}
#line 1627 "parser.c" /* yacc.c:1646  */
    break;

  case 21:
#line 105 "parser.y" /* yacc.c:1646  */
    {printf("expr -> expr op expr\n");}
#line 1633 "parser.c" /* yacc.c:1646  */
    break;

  case 22:
#line 106 "parser.y" /* yacc.c:1646  */
    {printf("expr -> expr op expr\n");}
#line 1639 "parser.c" /* yacc.c:1646  */
    break;

  case 23:
#line 107 "parser.y" /* yacc.c:1646  */
    {printf("expr -> expr op expr\n");}
#line 1645 "parser.c" /* yacc.c:1646  */
    break;

  case 24:
#line 108 "parser.y" /* yacc.c:1646  */
    {printf("expr -> expr op expr\n");}
#line 1651 "parser.c" /* yacc.c:1646  */
    break;

  case 25:
#line 109 "parser.y" /* yacc.c:1646  */
    {printf("expr -> expr op expr\n");}
#line 1657 "parser.c" /* yacc.c:1646  */
    break;

  case 26:
#line 110 "parser.y" /* yacc.c:1646  */
    {printf("expr -> expr op expr\n");}
#line 1663 "parser.c" /* yacc.c:1646  */
    break;

  case 27:
#line 111 "parser.y" /* yacc.c:1646  */
    {printf("expr -> expr op expr\n");}
#line 1669 "parser.c" /* yacc.c:1646  */
    break;

  case 28:
#line 112 "parser.y" /* yacc.c:1646  */
    {printf("expr -> expr op expr\n");}
#line 1675 "parser.c" /* yacc.c:1646  */
    break;

  case 29:
#line 113 "parser.y" /* yacc.c:1646  */
    {printf("expr -> term\n");}
#line 1681 "parser.c" /* yacc.c:1646  */
    break;

  case 30:
#line 118 "parser.y" /* yacc.c:1646  */
    {printf("term -> ( expr )\n");}
#line 1687 "parser.c" /* yacc.c:1646  */
    break;

  case 31:
#line 119 "parser.y" /* yacc.c:1646  */
    {printf("term -> -expr \n");}
#line 1693 "parser.c" /* yacc.c:1646  */
    break;

  case 32:
#line 120 "parser.y" /* yacc.c:1646  */
    {printf("term -> not expr \n");}
#line 1699 "parser.c" /* yacc.c:1646  */
    break;

  case 33:
#line 121 "parser.y" /* yacc.c:1646  */
    {printf("term -> ++lvalue \n");}
#line 1705 "parser.c" /* yacc.c:1646  */
    break;

  case 34:
#line 122 "parser.y" /* yacc.c:1646  */
    {printf("term -> lvalue++ \n");}
#line 1711 "parser.c" /* yacc.c:1646  */
    break;

  case 35:
#line 123 "parser.y" /* yacc.c:1646  */
    {printf("term -> --lvalue \n");}
#line 1717 "parser.c" /* yacc.c:1646  */
    break;

  case 36:
#line 124 "parser.y" /* yacc.c:1646  */
    {printf("term -> lvalue-- \n");}
#line 1723 "parser.c" /* yacc.c:1646  */
    break;

  case 37:
#line 125 "parser.y" /* yacc.c:1646  */
    {printf("term -> primary \n");}
#line 1729 "parser.c" /* yacc.c:1646  */
    break;

  case 38:
#line 128 "parser.y" /* yacc.c:1646  */
    {printf("assignexpr -> lvalue = expr \n");}
#line 1735 "parser.c" /* yacc.c:1646  */
    break;

  case 39:
#line 131 "parser.y" /* yacc.c:1646  */
    {printf("primary -> lvalue \n");}
#line 1741 "parser.c" /* yacc.c:1646  */
    break;

  case 40:
#line 132 "parser.y" /* yacc.c:1646  */
    {printf("primary -> -call \n");}
#line 1747 "parser.c" /* yacc.c:1646  */
    break;

  case 41:
#line 133 "parser.y" /* yacc.c:1646  */
    {printf("primary -> objectdef \n");}
#line 1753 "parser.c" /* yacc.c:1646  */
    break;

  case 42:
#line 134 "parser.y" /* yacc.c:1646  */
    {printf("primary -> ( funcdef ) \n");}
#line 1759 "parser.c" /* yacc.c:1646  */
    break;

  case 43:
#line 135 "parser.y" /* yacc.c:1646  */
    {printf("primary -> const \n");}
#line 1765 "parser.c" /* yacc.c:1646  */
    break;

  case 44:
#line 139 "parser.y" /* yacc.c:1646  */
    {printf("lvalue -> ID \n");}
#line 1771 "parser.c" /* yacc.c:1646  */
    break;

  case 45:
#line 140 "parser.y" /* yacc.c:1646  */
    {printf("lvalue ->  LOCAL ID\n");}
#line 1777 "parser.c" /* yacc.c:1646  */
    break;

  case 46:
#line 141 "parser.y" /* yacc.c:1646  */
    {printf("lvalue ->  ::ID\n");}
#line 1783 "parser.c" /* yacc.c:1646  */
    break;

  case 47:
#line 142 "parser.y" /* yacc.c:1646  */
    {printf("lvalue ->  member\n");}
#line 1789 "parser.c" /* yacc.c:1646  */
    break;

  case 48:
#line 146 "parser.y" /* yacc.c:1646  */
    {printf("member -> lvalue.ID \n");}
#line 1795 "parser.c" /* yacc.c:1646  */
    break;

  case 49:
#line 147 "parser.y" /* yacc.c:1646  */
    {printf("member -> lvalue { expr } \n");}
#line 1801 "parser.c" /* yacc.c:1646  */
    break;

  case 50:
#line 148 "parser.y" /* yacc.c:1646  */
    {printf("member -> call.ID \n");}
#line 1807 "parser.c" /* yacc.c:1646  */
    break;

  case 51:
#line 149 "parser.y" /* yacc.c:1646  */
    {printf("member -> call { expr } \n");}
#line 1813 "parser.c" /* yacc.c:1646  */
    break;

  case 52:
#line 152 "parser.y" /* yacc.c:1646  */
    {printf("call -> call ( elist ) \n");}
#line 1819 "parser.c" /* yacc.c:1646  */
    break;

  case 53:
#line 153 "parser.y" /* yacc.c:1646  */
    {printf("call -> lvalue callsuffix \n");}
#line 1825 "parser.c" /* yacc.c:1646  */
    break;

  case 54:
#line 154 "parser.y" /* yacc.c:1646  */
    {printf("call -> ( funcdef )( elist )\n");}
#line 1831 "parser.c" /* yacc.c:1646  */
    break;

  case 55:
#line 157 "parser.y" /* yacc.c:1646  */
    {printf("callsuffix -> normcall\n");}
#line 1837 "parser.c" /* yacc.c:1646  */
    break;

  case 56:
#line 158 "parser.y" /* yacc.c:1646  */
    {printf("callsuffix -> methodcall\n");}
#line 1843 "parser.c" /* yacc.c:1646  */
    break;

  case 57:
#line 161 "parser.y" /* yacc.c:1646  */
    {printf("normcall -> ( elist )\n");}
#line 1849 "parser.c" /* yacc.c:1646  */
    break;

  case 58:
#line 165 "parser.y" /* yacc.c:1646  */
    {printf("methodcall -> ..ID ( elist )\n");}
#line 1855 "parser.c" /* yacc.c:1646  */
    break;

  case 59:
#line 168 "parser.y" /* yacc.c:1646  */
    {printf("elist -> expr\n");}
#line 1861 "parser.c" /* yacc.c:1646  */
    break;

  case 60:
#line 169 "parser.y" /* yacc.c:1646  */
    {printf("elist -> ,expr\n");}
#line 1867 "parser.c" /* yacc.c:1646  */
    break;

  case 64:
#line 178 "parser.y" /* yacc.c:1646  */
    {printf("objectdef -> [ elist ]\n");}
#line 1873 "parser.c" /* yacc.c:1646  */
    break;

  case 65:
#line 179 "parser.y" /* yacc.c:1646  */
    {printf("objectdef -> [ indexed ]\n");}
#line 1879 "parser.c" /* yacc.c:1646  */
    break;

  case 66:
#line 182 "parser.y" /* yacc.c:1646  */
    {printf("indexed -> indexedelem\n");}
#line 1885 "parser.c" /* yacc.c:1646  */
    break;

  case 67:
#line 183 "parser.y" /* yacc.c:1646  */
    {printf("indexed -> ,indexedelem \n");}
#line 1891 "parser.c" /* yacc.c:1646  */
    break;

  case 68:
#line 187 "parser.y" /* yacc.c:1646  */
    {printf("indexedelem -> {expr : expr}\n");}
#line 1897 "parser.c" /* yacc.c:1646  */
    break;

  case 69:
#line 190 "parser.y" /* yacc.c:1646  */
    {printf("block -> { stmt }\n");}
#line 1903 "parser.c" /* yacc.c:1646  */
    break;

  case 70:
#line 193 "parser.y" /* yacc.c:1646  */
    {printf("funcdef -> function ID ( idlist ) block \n");}
#line 1909 "parser.c" /* yacc.c:1646  */
    break;

  case 71:
#line 194 "parser.y" /* yacc.c:1646  */
    {printf("funcdef -> function ( idlist ) block \n");}
#line 1915 "parser.c" /* yacc.c:1646  */
    break;

  case 72:
#line 198 "parser.y" /* yacc.c:1646  */
    {printf("const -> CONST_INT \n");}
#line 1921 "parser.c" /* yacc.c:1646  */
    break;

  case 73:
#line 199 "parser.y" /* yacc.c:1646  */
    {printf("const -> CONST_REAL \n");}
#line 1927 "parser.c" /* yacc.c:1646  */
    break;

  case 74:
#line 200 "parser.y" /* yacc.c:1646  */
    {printf("const -> STRING \n");}
#line 1933 "parser.c" /* yacc.c:1646  */
    break;

  case 75:
#line 201 "parser.y" /* yacc.c:1646  */
    {printf("const -> NIL \n");}
#line 1939 "parser.c" /* yacc.c:1646  */
    break;

  case 76:
#line 202 "parser.y" /* yacc.c:1646  */
    {printf("const -> TRUE \n");}
#line 1945 "parser.c" /* yacc.c:1646  */
    break;

  case 77:
#line 203 "parser.y" /* yacc.c:1646  */
    {printf("const -> FALSE \n");}
#line 1951 "parser.c" /* yacc.c:1646  */
    break;

  case 78:
#line 208 "parser.y" /* yacc.c:1646  */
    {printf("idlist -> ID \n");}
#line 1957 "parser.c" /* yacc.c:1646  */
    break;

  case 79:
#line 209 "parser.y" /* yacc.c:1646  */
    {printf("idlist -> ,ID \n");}
#line 1963 "parser.c" /* yacc.c:1646  */
    break;

  case 83:
#line 217 "parser.y" /* yacc.c:1646  */
    {printf("ifstmt -> if ( expr ) stmt \n");}
#line 1969 "parser.c" /* yacc.c:1646  */
    break;

  case 86:
#line 224 "parser.y" /* yacc.c:1646  */
    {printf("whilestmt -> while ( expr ) stmt \n");}
#line 1975 "parser.c" /* yacc.c:1646  */
    break;

  case 87:
#line 228 "parser.y" /* yacc.c:1646  */
    {printf("forstmt -> for ( elist; expr; elist; ) stmt \n");}
#line 1981 "parser.c" /* yacc.c:1646  */
    break;

  case 88:
#line 231 "parser.y" /* yacc.c:1646  */
    {printf("returnstmt -> return; \n");}
#line 1987 "parser.c" /* yacc.c:1646  */
    break;

  case 89:
#line 232 "parser.y" /* yacc.c:1646  */
    {printf("returnstmt -> return expr; \n");}
#line 1993 "parser.c" /* yacc.c:1646  */
    break;


#line 1997 "parser.c" /* yacc.c:1646  */
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
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
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

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

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

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
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
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
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
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 237 "parser.y" /* yacc.c:1906  */

/*programs   -   epilogos   */

int yyerror(char* yaccProvidedMessage){
	fprintf(stderr, "%s: at line %, before token: %s\n",yaccProvidedMessage,yylineno,yytext);
	printf("INPUT NOT VALID\n");
}





int main(int argc, char **argv) {
		yyin = stdin;

		
		SymTable = new_Symtable();
		
		yyparse();

		
		return 0;
}
