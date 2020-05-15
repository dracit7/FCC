
#ifndef _LLVM_H
#define _LLVM_H

#include <lib/ast.h>
#include <lib/semantic.h>

#define LLVM_TYPE(type, symbol) (\
  (type == T_INT) ? LLVMInt32Type() : (\
  (type == T_FLOAT) ? LLVMFloatType() : (\
  (type == T_CHAR) ? LLVMInt8Type() : (\
  (type == T_VOID) ? LLVMVoidType() : (\
  (type == T_STRING) ? LLVMPointerType(LLVMInt8Type(), 0) : (\
    SYMBOL(symbol).llvm_type\
))))))

#define LLVM_BUILD_BIN(builder, type, lval, rval, name) (\
  (type == OP_AND) ? LLVMBuildAnd(builder, lval, rval, name) : (\
  (type == OP_OR) ? LLVMBuildOr(builder, lval, rval, name) : (\
  (type == OP_G) ? LLVMBuildICmp(builder, LLVMIntSGT, lval, rval, name) : (\
  (type == OP_L) ? LLVMBuildICmp(builder, LLVMIntSLT, lval, rval, name) : (\
  (type == OP_GE) ? LLVMBuildICmp(builder, LLVMIntSGE, lval, rval, name) : (\
  (type == OP_LE) ? LLVMBuildICmp(builder, LLVMIntSLE, lval, rval, name) : (\
  (type == OP_EQ) ? LLVMBuildICmp(builder, LLVMIntEQ, lval, rval, name) : (\
  (type == OP_NEQ) ? LLVMBuildICmp(builder, LLVMIntNE, lval, rval, name) : (\
  (type == OP_ADD) ? LLVMBuildAdd(builder, lval, rval, name) : (\
  (type == OP_SUB) ? LLVMBuildSub(builder, lval, rval, name) : (\
  (type == OP_STAR) ? LLVMBuildMul(builder, lval, rval, name) : (\
  (type == OP_DIV) ? LLVMBuildSDiv(builder, lval, rval, name) : (\
  (type == OP_MOD) ? LLVMBuildSRem(builder, lval, rval, name) : (\
    NULL\
))))))))))))))

#define LLVM_BUILD_UN(builder, type, val, name) (\
  (type == UMINUS) ? LLVMBuildNeg(builder, val, name) : (\
  (type == OP_NOT) ? LLVMBuildNot(builder, val, name) : (\
  (type == OP_INC) ? LLVMBuildAdd(builder, val, LLVMConstInt(LLVMInt32Type(), 1, 0), name) : (\
  (type == OP_DEC) ? LLVMBuildSub(builder, val, LLVMConstInt(LLVMInt32Type(), 1, 0), name) : (\
    NULL\
)))))

#define LLVM_BUILD_COMP(builder, ope, lval, rval, name) (\
  (ope[0] == '+') ? LLVMBuildAdd(builder, lval, rval, name) : (\
  (ope[0] == '-') ? LLVMBuildSub(builder, lval, rval, name) : (\
  (ope[0] == '*') ? LLVMBuildMul(builder, lval, rval, name) : (\
  (ope[0] == '/') ? LLVMBuildSDiv(builder, lval, rval, name) : (\
  (ope[0] == '%') ? LLVMBuildSRem(builder, lval, rval, name) : (\
    NULL\
))))))

void generate_IR(ast_node* T, char* input, char* output);

#endif