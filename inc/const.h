
#ifndef _CONST_H
#define _CONST_H

#define NONE 0

// Global
#define PROJECT_NAME "minic"
#define LIST_INIT_SIZE 8

// Semantic
#define MAX_IDENT_LEN 64
#define MAX_ALIAS_LEN 16

#define MAX_SYMBOLTABLE_SIZE 256
#define MAX_SYMBOLSCOPE_NUM 32

#define BASE_OFFSET (3 * sizeof(int))

// AST
#define MAX_CHILD_NUM 4
#define MAX_ARRAY_DIM 16
#define INDENT_SIZE 2

// LLVM
#define LLVM_ENTRY_LABEL "entry"
#define MAX_INDICE_NUM 16

/*
 * Error handling
 */

enum error_code {

  // Semantic analysis
  ENOSYMBOL = 1, // No such symbol in the symbol table.
  ELACKARG, // Lack of arguments.
  EEXTRAARG, // Too much arguments.
  EWRONGARGTYPE, // Argument's type could not match parameter's.
  EDIFFOPETYPE, // Operands' types are different.
  EWRONGOPETYPE, // Operator does not support the operands' datatype.
  EWRONGINITTYPE, // Initializer's type differs from variable's type.
  EWRONGRETTYPE, // Wrong return type.
  EWRONGSUBSCRIPTTYPE, // Wrong array subscript type.
  ENOTSTRUCT, // Operand of dot is not a struct.
  ENOTMEMBER, // Right operand of dot is not the member of left operand.
  ENOTFUNC, // Try to call a non-function identifier.
  ENOTARRAY, // Try to subscript a non-array identifier.
  ENOTLEFTVALUE, // Assign to a non-left value.
  ENOTINLOOP, // Use break or continue out of a loop.
  ENOTRETURNED, // Non-void function is not returned.
  EFUNCASVAR, // Use a function name as variable.
  EDUPSYMBOL, // Duplicated name in the symbol table.

  // Others
  EOPEN, // Failed to open a file.
};

static const char* error_msg[] = {
  [ENOSYMBOL] = "undefined identifier %s.",
  [ELACKARG] = "%s has %d parameters but only %d arguments are passed.",
  [EEXTRAARG] = "%s only has %d parameters but more arguments are passed.",
  [EDIFFOPETYPE] = "Operands of %s should have the same type.",
  [EWRONGARGTYPE] = "Parameter %d of %s should be %s, but the type of argument is %s.",
  [EWRONGOPETYPE] = "Operands of %s can not be %s.",
  [EWRONGINITTYPE] = "Can not use an expression with type %s to init %s.",
  [EWRONGRETTYPE] = "returning '%s' from a function with return type '%s'.",
  [EWRONGSUBSCRIPTTYPE] = "array subscript is not an integer.",
  [ENOTSTRUCT] = "%s is not struct and has no member.",
  [ENOTMEMBER] = "%s is not the member of %s.",
  [ENOTFUNC] = "%s is not a function and can not be called.",
  [ENOTARRAY] = "%s is not array and can not be subscripted.",
  [ENOTLEFTVALUE] = "assigned to a non-left data type '%s'.",
  [ENOTINLOOP] = "%s statement not within loop.",
  [ENOTRETURNED] = "non-void function %s is not returned.",
  [EFUNCASVAR] = "%s is a function name, but used as a variable.",
  [EDUPSYMBOL] = "Repeated declaration of %s.",
  [EOPEN] = "Can not open file %s.",
};

static const char* error_src[] = {
  [ENOSYMBOL ... EDUPSYMBOL] = "semantic",
  [EOPEN ... EOPEN] = "others",
};

#endif