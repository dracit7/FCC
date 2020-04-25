/* A Bison parser, made by GNU Bison 3.5.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.5.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* First part of user prologue.  */
#line 5 "scripts/parser.y"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <inc/ds.h>

#include <lib/ast.h>

extern int yylineno;

int yylex();
void yyerror(const char* fmt, ...);


#line 87 "lib/parser.c"

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

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* Use api.header.include to #include this header
   instead of duplicating it here.  */
#ifndef YY_YY_LIB_PARSER_H_INCLUDED
# define YY_YY_LIB_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    T_CHAR = 258,
    T_INT = 259,
    T_FLOAT = 260,
    T_STRING = 261,
    T_VOID = 262,
    ASSIGN = 263,
    COMP_ASSIGN = 264,
    OP_OR = 265,
    OP_AND = 266,
    OP_EQ = 267,
    OP_NEQ = 268,
    OP_G = 269,
    OP_L = 270,
    OP_GE = 271,
    OP_LE = 272,
    OP_ADD = 273,
    OP_SUB = 274,
    OP_STAR = 275,
    OP_DIV = 276,
    OP_MOD = 277,
    OP_NOT = 278,
    OP_INC = 279,
    OP_DEC = 280,
    UMINUS = 281,
    IF = 282,
    ELSE = 283,
    RETURN = 284,
    WHILE = 285,
    BREAK = 286,
    CONTINUE = 287,
    IDENT = 288,
    L_INT = 289,
    L_FLOAT = 290,
    L_STRING = 291,
    EXT_DEF_LIST = 292,
    EXT_VAR_DEF = 293,
    FUNC_DEF = 294,
    EXT_DECL_LIST = 295,
    FUNC_DECL = 296,
    PARAM_LIST = 297,
    PARAM_DEC = 298,
    STMT_LIST = 299,
    IF_THEN = 300,
    IF_THEN_ELSE = 301,
    VAR_DEF = 302,
    DEC_LIST = 303,
    FUNC_CALL = 304,
    ARG_LIST = 305,
    ARRAY_CALL = 306,
    VAR_INIT = 307,
    NO_ELSE = 308
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 23 "scripts/parser.y"

  int integer;
  float floatpoint;
  char* str;
  ast_node* node;

#line 200 "lib/parser.c"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif


extern YYSTYPE yylval;
extern YYLTYPE yylloc;
int yyparse (void);

#endif /* !YY_YY_LIB_PARSER_H_INCLUDED  */



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
typedef yytype_int8 yy_state_t;

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
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && ! defined __ICC && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                            \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
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
         || (defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL \
             && defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yy_state_t yyss_alloc;
  YYSTYPE yyvs_alloc;
  YYLTYPE yyls_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (YYSIZEOF (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (YYSIZEOF (yy_state_t) + YYSIZEOF (YYSTYPE) \
             + YYSIZEOF (YYLTYPE)) \
      + 2 * YYSTACK_GAP_MAXIMUM)

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
#define YYFINAL  11
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   333

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  62
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  19
/* YYNRULES -- Number of rules.  */
#define YYNRULES  63
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  119

#define YYUNDEFTOK  2
#define YYMAXUTOK   308


/* YYTRANSLATE(TOKEN-NUM) -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, with out-of-bounds checking.  */
#define YYTRANSLATE(YYX)                                                \
  (0 <= (YYX) && (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex.  */
static const yytype_int8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
      58,    59,     2,     2,    55,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,    54,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,    56,     2,    57,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,    60,     2,    61,     2,     2,     2,     2,
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
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_int16 yyrline[] =
{
       0,    87,    87,    91,    93,    96,    98,   100,   104,   108,
     110,   111,   112,   115,   116,   120,   124,   128,   134,   138,
     144,   146,   150,   154,   158,   159,   160,   163,   165,   167,
     169,   171,   173,   175,   177,   181,   185,   186,   190,   191,
     195,   199,   201,   203,   205,   207,   209,   211,   213,   215,
     217,   219,   221,   223,   225,   227,   231,   235,   239,   242,
     246,   250,   256,   258
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "T_CHAR", "T_INT", "T_FLOAT", "T_STRING",
  "T_VOID", "ASSIGN", "COMP_ASSIGN", "OP_OR", "OP_AND", "OP_EQ", "OP_NEQ",
  "OP_G", "OP_L", "OP_GE", "OP_LE", "OP_ADD", "OP_SUB", "OP_STAR",
  "OP_DIV", "OP_MOD", "OP_NOT", "OP_INC", "OP_DEC", "UMINUS", "IF", "ELSE",
  "RETURN", "WHILE", "BREAK", "CONTINUE", "IDENT", "L_INT", "L_FLOAT",
  "L_STRING", "EXT_DEF_LIST", "EXT_VAR_DEF", "FUNC_DEF", "EXT_DECL_LIST",
  "FUNC_DECL", "PARAM_LIST", "PARAM_DEC", "STMT_LIST", "IF_THEN",
  "IF_THEN_ELSE", "VAR_DEF", "DEC_LIST", "FUNC_CALL", "ARG_LIST",
  "ARRAY_CALL", "VAR_INIT", "NO_ELSE", "';'", "','", "'['", "']'", "'('",
  "')'", "'{'", "'}'", "$accept", "program", "ext_def_list", "ext_def",
  "type_void", "var_type", "ext_decl_list", "var_name", "func_decl",
  "param_list", "param", "code_block", "stmt_list", "stmt", "decl",
  "decl_list", "var_decl", "expr", "arg_list", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_int16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,    59,    44,    91,    93,    40,    41,
     123,   125
};
# endif

#define YYPACT_NINF (-71)

#define yypact_value_is_default(Yyn) \
  ((Yyn) == YYPACT_NINF)

#define YYTABLE_NINF (-1)

#define yytable_value_is_error(Yyn) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     129,   -71,   -71,   -71,   -71,   -71,     3,   -71,   129,   -21,
     -13,   -71,   -71,   -36,   -35,   -36,   -17,    11,   -35,   -22,
      12,    45,   -71,   -71,   275,   -33,   -71,     8,   -71,     8,
     -16,   -11,   275,   275,   275,   275,     4,   275,    15,     7,
      33,    -6,   -71,   -71,   -71,   275,     8,   -71,    27,    45,
      45,   147,   209,    32,   -71,   -71,   -71,    39,   -71,   171,
     -20,   -20,   -20,   -20,   275,   170,   275,   -71,   -71,   275,
     255,    72,    46,    47,   -71,   -71,   -71,   275,   275,   275,
     275,   275,   275,   275,   -71,   -71,   -71,   275,   -71,   -71,
      88,   -71,   105,   209,   -71,   186,    42,   -71,   -71,     8,
     225,    10,    97,    97,   -20,   -20,   -20,   130,   237,   237,
     275,   -71,   -71,   -71,    76,   -71,   -71,   237,   -71
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_int8 yydefact[] =
{
       4,    11,     9,    10,    12,     8,     0,     2,     4,     0,
       0,     1,     3,     0,     0,    15,     0,    38,     0,    13,
       0,    24,     7,     5,     0,     0,     6,     0,    19,     0,
       0,    20,     0,     0,     0,     0,     0,     0,     0,     0,
       0,    57,    59,    60,    61,     0,     0,    28,     0,    24,
      24,     0,    39,     0,    16,    15,    14,    22,    18,     0,
      49,    50,    51,    53,     0,     0,     0,    33,    34,     0,
       0,     0,     0,    36,    23,    25,    26,     0,     0,     0,
       0,     0,     0,     0,    52,    54,    27,     0,    17,    21,
       0,    29,     0,    40,    56,    63,     0,    48,    35,     0,
      42,    41,    43,    44,    45,    46,    47,     0,     0,     0,
       0,    55,    37,    58,    30,    32,    62,     0,    31
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int8 yypgoto[] =
{
     -71,   -71,   103,   -71,   -71,     6,    87,    91,   127,    79,
     -71,     9,    35,   -70,   -71,    40,   -39,   -24,    36
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int8 yydefgoto[] =
{
      -1,     6,     7,     8,     9,    46,    16,    17,    14,    30,
      31,    47,    48,    49,    50,    72,    19,    51,    96
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_int8 yytable[] =
{
      52,    53,    69,    11,    84,    85,    10,    73,    60,    61,
      62,    63,    13,    65,    10,     1,     2,     3,     4,    24,
      15,    71,    20,    22,    54,    21,    29,    26,    79,    80,
      81,    82,    83,    27,    84,    85,    87,    23,   114,   115,
      90,    55,    92,    58,    59,    93,    95,   118,     1,     2,
       3,     4,    70,   100,   101,   102,   103,   104,   105,   106,
      73,    67,    64,   107,    32,    29,    87,    25,    33,    34,
      35,    28,    36,    66,    37,    38,    39,    40,    41,    42,
      43,    44,    77,    78,    75,    76,    95,    68,    74,    88,
      79,    80,    81,    82,    83,    25,    84,    85,    77,    78,
      98,   111,    99,    45,   117,    21,    79,    80,    81,    82,
      83,    12,    84,    85,    56,    77,    78,    81,    82,    83,
      57,    84,    85,    79,    80,    81,    82,    83,    87,    84,
      85,    97,     1,     2,     3,     4,     5,    18,    89,   112,
      77,    78,     0,     0,    87,     0,   116,   108,    79,    80,
      81,    82,    83,    87,    84,    85,     0,    77,    78,     0,
       0,    87,     0,     0,   109,    79,    80,    81,    82,    83,
       0,    84,    85,     0,     1,     2,     3,     4,     0,     0,
      77,    78,     0,     0,     0,     0,    87,   113,    79,    80,
      81,    82,    83,     0,    84,    85,    77,    78,     0,     0,
       0,    86,     0,    87,    79,    80,    81,    82,    83,     0,
      84,    85,     0,     0,     0,     0,     0,     0,     0,    77,
      78,     0,     0,     0,    91,     0,    87,    79,    80,    81,
      82,    83,     0,    84,    85,     0,    78,     0,     0,     0,
       0,   110,    87,    79,    80,    81,    82,    83,     0,    84,
      85,     0,     0,     0,     0,     0,    32,     0,     0,     0,
      33,    34,    35,     0,    36,    87,    37,    38,    39,    40,
      41,    42,    43,    44,    32,     0,     0,     0,    33,    34,
      35,    87,     0,     0,     0,     0,     0,     0,    41,    42,
      43,    44,     0,     0,    32,    45,     0,    21,    33,    34,
      35,     0,     0,     0,     0,     0,     0,     0,    41,    42,
      43,    44,     0,    45,    94,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    45
};

static const yytype_int8 yycheck[] =
{
      24,    34,     8,     0,    24,    25,     0,    46,    32,    33,
      34,    35,    33,    37,     8,     3,     4,     5,     6,     8,
      33,    45,    58,    14,    57,    60,    20,    18,    18,    19,
      20,    21,    22,    55,    24,    25,    56,    54,   108,   109,
      64,    33,    66,    59,    55,    69,    70,   117,     3,     4,
       5,     6,    58,    77,    78,    79,    80,    81,    82,    83,
      99,    54,    58,    87,    19,    59,    56,    56,    23,    24,
      25,    59,    27,    58,    29,    30,    31,    32,    33,    34,
      35,    36,    10,    11,    49,    50,   110,    54,    61,    57,
      18,    19,    20,    21,    22,    56,    24,    25,    10,    11,
      54,    59,    55,    58,    28,    60,    18,    19,    20,    21,
      22,     8,    24,    25,    27,    10,    11,    20,    21,    22,
      29,    24,    25,    18,    19,    20,    21,    22,    56,    24,
      25,    59,     3,     4,     5,     6,     7,    10,    59,    99,
      10,    11,    -1,    -1,    56,    -1,   110,    59,    18,    19,
      20,    21,    22,    56,    24,    25,    -1,    10,    11,    -1,
      -1,    56,    -1,    -1,    59,    18,    19,    20,    21,    22,
      -1,    24,    25,    -1,     3,     4,     5,     6,    -1,    -1,
      10,    11,    -1,    -1,    -1,    -1,    56,    57,    18,    19,
      20,    21,    22,    -1,    24,    25,    10,    11,    -1,    -1,
      -1,    54,    -1,    56,    18,    19,    20,    21,    22,    -1,
      24,    25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    10,
      11,    -1,    -1,    -1,    54,    -1,    56,    18,    19,    20,
      21,    22,    -1,    24,    25,    -1,    11,    -1,    -1,    -1,
      -1,    55,    56,    18,    19,    20,    21,    22,    -1,    24,
      25,    -1,    -1,    -1,    -1,    -1,    19,    -1,    -1,    -1,
      23,    24,    25,    -1,    27,    56,    29,    30,    31,    32,
      33,    34,    35,    36,    19,    -1,    -1,    -1,    23,    24,
      25,    56,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    -1,    -1,    19,    58,    -1,    60,    23,    24,
      25,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    33,    34,
      35,    36,    -1,    58,    59,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    -1,    58
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_int8 yystos[] =
{
       0,     3,     4,     5,     6,     7,    63,    64,    65,    66,
      67,     0,    64,    33,    70,    33,    68,    69,    70,    78,
      58,    60,    73,    54,     8,    56,    73,    55,    59,    67,
      71,    72,    19,    23,    24,    25,    27,    29,    30,    31,
      32,    33,    34,    35,    36,    58,    67,    73,    74,    75,
      76,    79,    79,    34,    57,    33,    68,    69,    59,    55,
      79,    79,    79,    79,    58,    79,    58,    54,    54,     8,
      58,    79,    77,    78,    61,    74,    74,    10,    11,    18,
      19,    20,    21,    22,    24,    25,    54,    56,    57,    71,
      79,    54,    79,    79,    59,    79,    80,    59,    54,    55,
      79,    79,    79,    79,    79,    79,    79,    79,    59,    59,
      55,    59,    77,    57,    75,    75,    80,    28,    75
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_int8 yyr1[] =
{
       0,    62,    63,    64,    64,    65,    65,    65,    66,    67,
      67,    67,    67,    68,    68,    69,    69,    69,    70,    70,
      71,    71,    72,    73,    74,    74,    74,    75,    75,    75,
      75,    75,    75,    75,    75,    76,    77,    77,    78,    78,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    79,    79,    79,    79,    79,    79,    79,    79,
      79,    79,    80,    80
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_int8 yyr2[] =
{
       0,     2,     1,     2,     0,     3,     3,     3,     1,     1,
       1,     1,     1,     1,     3,     1,     3,     4,     4,     3,
       1,     3,     2,     3,     0,     2,     2,     2,     1,     3,
       5,     7,     5,     2,     2,     3,     1,     3,     1,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     2,
       2,     2,     2,     2,     2,     4,     3,     1,     4,     1,
       1,     1,     3,     1
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


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

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256


/* YYLLOC_DEFAULT -- Set CURRENT to span from RHS[1] to RHS[N].
   If N is 0, then set CURRENT to the empty location which ends
   the previous symbol: RHS[0] (always defined).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)                                \
    do                                                                  \
      if (N)                                                            \
        {                                                               \
          (Current).first_line   = YYRHSLOC (Rhs, 1).first_line;        \
          (Current).first_column = YYRHSLOC (Rhs, 1).first_column;      \
          (Current).last_line    = YYRHSLOC (Rhs, N).last_line;         \
          (Current).last_column  = YYRHSLOC (Rhs, N).last_column;       \
        }                                                               \
      else                                                              \
        {                                                               \
          (Current).first_line   = (Current).last_line   =              \
            YYRHSLOC (Rhs, 0).last_line;                                \
          (Current).first_column = (Current).last_column =              \
            YYRHSLOC (Rhs, 0).last_column;                              \
        }                                                               \
    while (0)
#endif

#define YYRHSLOC(Rhs, K) ((Rhs)[K])


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


/* YY_LOCATION_PRINT -- Print the location on the stream.
   This macro was not mandated originally: define only if we know
   we won't break user code: when these are the locations we know.  */

#ifndef YY_LOCATION_PRINT
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL

/* Print *YYLOCP on YYO.  Private, do not rely on its existence. */

YY_ATTRIBUTE_UNUSED
static int
yy_location_print_ (FILE *yyo, YYLTYPE const * const yylocp)
{
  int res = 0;
  int end_col = 0 != yylocp->last_column ? yylocp->last_column - 1 : 0;
  if (0 <= yylocp->first_line)
    {
      res += YYFPRINTF (yyo, "%d", yylocp->first_line);
      if (0 <= yylocp->first_column)
        res += YYFPRINTF (yyo, ".%d", yylocp->first_column);
    }
  if (0 <= yylocp->last_line)
    {
      if (yylocp->first_line < yylocp->last_line)
        {
          res += YYFPRINTF (yyo, "-%d", yylocp->last_line);
          if (0 <= end_col)
            res += YYFPRINTF (yyo, ".%d", end_col);
        }
      else if (0 <= end_col && yylocp->first_column < end_col)
        res += YYFPRINTF (yyo, "-%d", end_col);
    }
  return res;
 }

#  define YY_LOCATION_PRINT(File, Loc)          \
  yy_location_print_ (File, &(Loc))

# else
#  define YY_LOCATION_PRINT(File, Loc) ((void) 0)
# endif
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value, Location); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*-----------------------------------.
| Print this symbol's value on YYO.  |
`-----------------------------------*/

static void
yy_symbol_value_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  FILE *yyoutput = yyo;
  YYUSE (yyoutput);
  YYUSE (yylocationp);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyo, yytoknum[yytype], *yyvaluep);
# endif
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}


/*---------------------------.
| Print this symbol on YYO.  |
`---------------------------*/

static void
yy_symbol_print (FILE *yyo, int yytype, YYSTYPE const * const yyvaluep, YYLTYPE const * const yylocationp)
{
  YYFPRINTF (yyo, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  YY_LOCATION_PRINT (yyo, *yylocationp);
  YYFPRINTF (yyo, ": ");
  yy_symbol_value_print (yyo, yytype, yyvaluep, yylocationp);
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
yy_reduce_print (yy_state_t *yyssp, YYSTYPE *yyvsp, YYLTYPE *yylsp, int yyrule)
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
                       yystos[+yyssp[yyi + 1 - yynrhs]],
                       &yyvsp[(yyi + 1) - (yynrhs)]
                       , &(yylsp[(yyi + 1) - (yynrhs)])                       );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, yylsp, Rule); \
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
#   define yystrlen(S) (YY_CAST (YYPTRDIFF_T, strlen (S)))
#  else
/* Return the length of YYSTR.  */
static YYPTRDIFF_T
yystrlen (const char *yystr)
{
  YYPTRDIFF_T yylen;
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
static YYPTRDIFF_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYPTRDIFF_T yyn = 0;
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
            else
              goto append;

          append:
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

  if (yyres)
    return yystpcpy (yyres, yystr) - yyres;
  else
    return yystrlen (yystr);
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
yysyntax_error (YYPTRDIFF_T *yymsg_alloc, char **yymsg,
                yy_state_t *yyssp, int yytoken)
{
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat: reported tokens (one for the "unexpected",
     one per "expected"). */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Actual size of YYARG. */
  int yycount = 0;
  /* Cumulated lengths of YYARG.  */
  YYPTRDIFF_T yysize = 0;

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
      int yyn = yypact[+*yyssp];
      YYPTRDIFF_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
      yysize = yysize0;
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
                  YYPTRDIFF_T yysize1
                    = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
                    yysize = yysize1;
                  else
                    return 2;
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
    default: /* Avoid compiler warnings. */
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    /* Don't count the "%s"s in the final size, but reserve room for
       the terminator.  */
    YYPTRDIFF_T yysize1 = yysize + (yystrlen (yyformat) - 2 * yycount) + 1;
    if (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM)
      yysize = yysize1;
    else
      return 2;
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
          ++yyp;
          ++yyformat;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep, YYLTYPE *yylocationp)
{
  YYUSE (yyvaluep);
  YYUSE (yylocationp);
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
/* Location data for the lookahead symbol.  */
YYLTYPE yylloc
# if defined YYLTYPE_IS_TRIVIAL && YYLTYPE_IS_TRIVIAL
  = { 1, 1, 1, 1 }
# endif
;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    yy_state_fast_t yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.
       'yyls': related to locations.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yy_state_t yyssa[YYINITDEPTH];
    yy_state_t *yyss;
    yy_state_t *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    /* The location stack.  */
    YYLTYPE yylsa[YYINITDEPTH];
    YYLTYPE *yyls;
    YYLTYPE *yylsp;

    /* The locations where the error started and ended.  */
    YYLTYPE yyerror_range[3];

    YYPTRDIFF_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;
  YYLTYPE yyloc;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYPTRDIFF_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N), yylsp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yylsp = yyls = yylsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  yylsp[0] = yylloc;
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

  if (yyss + yystacksize - 1 <= yyssp)
#if !defined yyoverflow && !defined YYSTACK_RELOCATE
    goto yyexhaustedlab;
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
        YYLTYPE *yyls1 = yyls;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * YYSIZEOF (*yyssp),
                    &yyvs1, yysize * YYSIZEOF (*yyvsp),
                    &yyls1, yysize * YYSIZEOF (*yylsp),
                    &yystacksize);
        yyss = yyss1;
        yyvs = yyvs1;
        yyls = yyls1;
      }
# else /* defined YYSTACK_RELOCATE */
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yy_state_t *yyss1 = yyss;
        union yyalloc *yyptr =
          YY_CAST (union yyalloc *,
                   YYSTACK_ALLOC (YY_CAST (YYSIZE_T, YYSTACK_BYTES (yystacksize))));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
        YYSTACK_RELOCATE (yyls_alloc, yyls);
# undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;
      yylsp = yyls + yysize - 1;

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
  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END
  *++yylsp = yylloc;

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

  /* Default location. */
  YYLLOC_DEFAULT (yyloc, (yylsp - yylen), yylen);
  yyerror_range[1] = yyloc;
  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
  case 2:
#line 88 "scripts/parser.y"
    {ast_trav((yyvsp[0].node), 1);}
#line 1615 "lib/parser.c"
    break;

  case 3:
#line 92 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, EXT_DEF_LIST, yylineno, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1621 "lib/parser.c"
    break;

  case 4:
#line 93 "scripts/parser.y"
    {(yyval.node) = NULL;}
#line 1627 "lib/parser.c"
    break;

  case 5:
#line 97 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, EXT_VAR_DEF, yylineno, (yyvsp[-2].node), (yyvsp[-1].node));}
#line 1633 "lib/parser.c"
    break;

  case 6:
#line 99 "scripts/parser.y"
    {(yyval.node) = ast_new_node(3, FUNC_DEF, yylineno, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1639 "lib/parser.c"
    break;

  case 7:
#line 101 "scripts/parser.y"
    {(yyval.node) = ast_new_node(3, FUNC_DEF, yylineno, (yyvsp[-2].node), (yyvsp[-1].node), (yyvsp[0].node));}
#line 1645 "lib/parser.c"
    break;

  case 8:
#line 105 "scripts/parser.y"
    {(yyval.node) = ast_new_node(0, T_VOID, yylineno);}
#line 1651 "lib/parser.c"
    break;

  case 9:
#line 109 "scripts/parser.y"
    {(yyval.node) = ast_new_node(0, T_INT, yylineno);}
#line 1657 "lib/parser.c"
    break;

  case 10:
#line 110 "scripts/parser.y"
            {(yyval.node) = ast_new_node(0, T_FLOAT, yylineno);}
#line 1663 "lib/parser.c"
    break;

  case 11:
#line 111 "scripts/parser.y"
           {(yyval.node) = ast_new_node(0, T_CHAR, yylineno);}
#line 1669 "lib/parser.c"
    break;

  case 12:
#line 112 "scripts/parser.y"
             {(yyval.node) = ast_new_node(0, T_STRING, yylineno);}
#line 1675 "lib/parser.c"
    break;

  case 13:
#line 115 "scripts/parser.y"
                        {(yyval.node) = (yyvsp[0].node);}
#line 1681 "lib/parser.c"
    break;

  case 14:
#line 117 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, EXT_DECL_LIST, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1687 "lib/parser.c"
    break;

  case 15:
#line 120 "scripts/parser.y"
                {
    (yyval.node) = ast_new_node(0, IDENT, yylineno);
    strcpy((yyval.node)->value.str, (yyvsp[0].str));
  }
#line 1696 "lib/parser.c"
    break;

  case 16:
#line 124 "scripts/parser.y"
                     {
    (yyval.node) = (yyvsp[-2].node);
    (yyval.node)->capacity[(yyval.node)->dim++] = 0;
  }
#line 1705 "lib/parser.c"
    break;

  case 17:
#line 128 "scripts/parser.y"
                           {
    (yyval.node) = (yyvsp[-3].node);
    (yyval.node)->capacity[(yyval.node)->dim++] = (yyvsp[-1].integer);
  }
#line 1714 "lib/parser.c"
    break;

  case 18:
#line 134 "scripts/parser.y"
                                    {
    (yyval.node) = ast_new_node(1, FUNC_DECL, yylineno, (yyvsp[-1].node));
    strcpy((yyval.node)->value.str, (yyvsp[-3].str));
  }
#line 1723 "lib/parser.c"
    break;

  case 19:
#line 138 "scripts/parser.y"
                  {
    (yyval.node) = ast_new_node(0, FUNC_DECL, yylineno);
    strcpy((yyval.node)->value.str, (yyvsp[-2].str));
  }
#line 1732 "lib/parser.c"
    break;

  case 20:
#line 145 "scripts/parser.y"
    {(yyval.node) = ast_new_node(1, PARAM_LIST, yylineno, (yyvsp[0].node));}
#line 1738 "lib/parser.c"
    break;

  case 21:
#line 147 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, PARAM_LIST, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1744 "lib/parser.c"
    break;

  case 22:
#line 151 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, PARAM_DEC, yylineno, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1750 "lib/parser.c"
    break;

  case 23:
#line 155 "scripts/parser.y"
    {(yyval.node) = (yyvsp[-1].node);}
#line 1756 "lib/parser.c"
    break;

  case 24:
#line 158 "scripts/parser.y"
           {(yyval.node) = NULL;}
#line 1762 "lib/parser.c"
    break;

  case 25:
#line 159 "scripts/parser.y"
                   {(yyval.node) = ast_new_node(2, STMT_LIST, yylineno, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1768 "lib/parser.c"
    break;

  case 26:
#line 160 "scripts/parser.y"
                   {(yyval.node) = ast_new_node(2, STMT_LIST, yylineno, (yyvsp[-1].node), (yyvsp[0].node));}
#line 1774 "lib/parser.c"
    break;

  case 27:
#line 164 "scripts/parser.y"
    {(yyval.node) = (yyvsp[-1].node);}
#line 1780 "lib/parser.c"
    break;

  case 28:
#line 166 "scripts/parser.y"
    {(yyval.node) = (yyvsp[0].node);}
#line 1786 "lib/parser.c"
    break;

  case 29:
#line 168 "scripts/parser.y"
    {(yyval.node) = ast_new_node(1, RETURN, yylineno, (yyvsp[-1].node));}
#line 1792 "lib/parser.c"
    break;

  case 30:
#line 170 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, IF_THEN, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1798 "lib/parser.c"
    break;

  case 31:
#line 172 "scripts/parser.y"
    {(yyval.node) = ast_new_node(3, IF_THEN_ELSE, yylineno, (yyvsp[-4].node), (yyvsp[-2].node), (yyvsp[0].node));}
#line 1804 "lib/parser.c"
    break;

  case 32:
#line 174 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, WHILE, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1810 "lib/parser.c"
    break;

  case 33:
#line 176 "scripts/parser.y"
    {(yyval.node) = ast_new_node(0, BREAK, yylineno);}
#line 1816 "lib/parser.c"
    break;

  case 34:
#line 178 "scripts/parser.y"
    {(yyval.node) = ast_new_node(0, CONTINUE, yylineno);}
#line 1822 "lib/parser.c"
    break;

  case 35:
#line 182 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, VAR_DEF, yylineno, (yyvsp[-2].node), (yyvsp[-1].node));}
#line 1828 "lib/parser.c"
    break;

  case 36:
#line 185 "scripts/parser.y"
                    {(yyval.node) = (yyvsp[0].node);}
#line 1834 "lib/parser.c"
    break;

  case 37:
#line 187 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, DEC_LIST, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1840 "lib/parser.c"
    break;

  case 38:
#line 190 "scripts/parser.y"
                   {(yyval.node) = (yyvsp[0].node);}
#line 1846 "lib/parser.c"
    break;

  case 39:
#line 192 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, VAR_INIT, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1852 "lib/parser.c"
    break;

  case 40:
#line 195 "scripts/parser.y"
                        {
    (yyval.node) = ast_new_node(1, ASSIGN, yylineno, (yyvsp[0].node));
    strcpy((yyval.node)->value.str, (yyvsp[-2].str));
  }
#line 1861 "lib/parser.c"
    break;

  case 41:
#line 200 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, OP_AND, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1867 "lib/parser.c"
    break;

  case 42:
#line 202 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, OP_OR, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1873 "lib/parser.c"
    break;

  case 43:
#line 204 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, OP_ADD, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1879 "lib/parser.c"
    break;

  case 44:
#line 206 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, OP_SUB, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1885 "lib/parser.c"
    break;

  case 45:
#line 208 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, OP_STAR, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1891 "lib/parser.c"
    break;

  case 46:
#line 210 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, OP_DIV, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1897 "lib/parser.c"
    break;

  case 47:
#line 212 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, OP_MOD, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 1903 "lib/parser.c"
    break;

  case 48:
#line 214 "scripts/parser.y"
    {(yyval.node) = (yyvsp[-1].node);}
#line 1909 "lib/parser.c"
    break;

  case 49:
#line 216 "scripts/parser.y"
    {(yyval.node) = ast_new_node(1, UMINUS, yylineno, (yyvsp[0].node));}
#line 1915 "lib/parser.c"
    break;

  case 50:
#line 218 "scripts/parser.y"
    {(yyval.node) = ast_new_node(1, OP_NOT, yylineno, (yyvsp[0].node));}
#line 1921 "lib/parser.c"
    break;

  case 51:
#line 220 "scripts/parser.y"
    {(yyval.node) = ast_new_node(1, OP_INC, yylineno, (yyvsp[0].node));}
#line 1927 "lib/parser.c"
    break;

  case 52:
#line 222 "scripts/parser.y"
    {(yyval.node) = ast_new_node(1, OP_INC, yylineno, (yyvsp[-1].node));}
#line 1933 "lib/parser.c"
    break;

  case 53:
#line 224 "scripts/parser.y"
    {(yyval.node) = ast_new_node(1, OP_DEC, yylineno, (yyvsp[0].node));}
#line 1939 "lib/parser.c"
    break;

  case 54:
#line 226 "scripts/parser.y"
    {(yyval.node) = ast_new_node(1, OP_DEC, yylineno, (yyvsp[-1].node));}
#line 1945 "lib/parser.c"
    break;

  case 55:
#line 227 "scripts/parser.y"
                           {
      (yyval.node) = ast_new_node(1, FUNC_CALL, yylineno, (yyvsp[-1].node));
      strcpy((yyval.node)->value.str, (yyvsp[-3].str));
    }
#line 1954 "lib/parser.c"
    break;

  case 56:
#line 231 "scripts/parser.y"
                  {
      (yyval.node) = ast_new_node(0, FUNC_CALL, yylineno);
      strcpy((yyval.node)->value.str, (yyvsp[-2].str));
    }
#line 1963 "lib/parser.c"
    break;

  case 57:
#line 235 "scripts/parser.y"
          {
      (yyval.node) = ast_new_node(0, IDENT, yylineno);
      strcpy((yyval.node)->value.str, (yyvsp[0].str));
    }
#line 1972 "lib/parser.c"
    break;

  case 58:
#line 239 "scripts/parser.y"
                      {
      (yyval.node) = ast_new_node(2, ARRAY_CALL, yylineno, (yyvsp[-3].node), (yyvsp[-1].node));
    }
#line 1980 "lib/parser.c"
    break;

  case 59:
#line 242 "scripts/parser.y"
          {
      (yyval.node) = ast_new_node(0, L_INT, yylineno);
      (yyval.node)->value.itg=(yyvsp[0].integer);
    }
#line 1989 "lib/parser.c"
    break;

  case 60:
#line 246 "scripts/parser.y"
            {
      (yyval.node) = ast_new_node(0, L_FLOAT, yylineno);
      (yyval.node)->value.flt=(yyvsp[0].floatpoint);
    }
#line 1998 "lib/parser.c"
    break;

  case 61:
#line 250 "scripts/parser.y"
             {
      (yyval.node) = ast_new_node(0, L_STRING, yylineno);
      strcpy((yyval.node)->value.str, (yyvsp[0].str));
    }
#line 2007 "lib/parser.c"
    break;

  case 62:
#line 257 "scripts/parser.y"
    {(yyval.node) = ast_new_node(2, ARG_LIST, yylineno, (yyvsp[-2].node), (yyvsp[0].node));}
#line 2013 "lib/parser.c"
    break;

  case 63:
#line 258 "scripts/parser.y"
         {(yyval.node) = (yyvsp[0].node);}
#line 2019 "lib/parser.c"
    break;


#line 2023 "lib/parser.c"

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
  *++yylsp = yyloc;

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
            yymsg = YY_CAST (char *, YYSTACK_ALLOC (YY_CAST (YYSIZE_T, yymsg_alloc)));
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

  yyerror_range[1] = yylloc;

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
                      yytoken, &yylval, &yylloc);
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

      yyerror_range[1] = *yylsp;
      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp, yylsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  yyerror_range[2] = yylloc;
  /* Using YYLLOC is tempting, but would change the location of
     the lookahead.  YYLOC is available though.  */
  YYLLOC_DEFAULT (yyloc, yyerror_range, 2);
  *++yylsp = yyloc;

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


/*-----------------------------------------------------.
| yyreturn -- parsing is finished, return the result.  |
`-----------------------------------------------------*/
yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval, &yylloc);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[+*yyssp], yyvsp, yylsp);
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
#line 261 "scripts/parser.y"


void yyerror(const char* fmt, ...) {
  va_list ap;
  va_start(ap, fmt);
  fprintf(stderr, "Grammar error (%d.%d): ", yylloc.first_line, yylloc.first_column);
  vfprintf(stderr, fmt, ap);
  fprintf(stderr, ".\n");
}
