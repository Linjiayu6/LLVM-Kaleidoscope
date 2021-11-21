// #include "llvm/ADT/STLExtras.h"

// #include <algorithm>
// #include <cctype>
// #include <cstdio>
// #include <cstdlib>
// #include <map>
// #include <memory>

#include <string>
#include <vector>

// ========================================
// Abstract Syntax Tree (AST对语言进行密切建模)
// ========================================
namespace {
  // 对表达式基准类
  class ExprAST {
    public:
      virtual ~ExprAST() = default; // ~代表析构函数, 当执行完成后会执行该函数来释放内存空间
  };

  // 数字类
  class NumberExprAST : public ExprAST {
    double Val;
    public:
      NumberExprAST(double Val) : Val(Val) {} // 构造函数
  };

  // 变量类 let a = 66.6, like a
  class VariableExprAST: public ExprAST {
    std::string Name;
    public:
      // const限定为只读; &引用作用, 避免复制; 
      VariableExprAST(const std::string &Name) : Name(Name) {}
  };

  // 二元运算符类 eg: a == b; a > b; 即 Op为 ==, LHS为'a', RHS为'b'
  class BinaryExprAST : public ExprAST {
    char Op;
    std::unique_ptr<ExprAST> LHS, RHS; // unique_ptr不会贡献它的指针

    public:
      BinaryExprAST(char Op, std::unique_ptr<ExprAST> LHS, std::unique_ptr<ExprAST> RHS)
        : Op(Op), LHS(std::move(LHS)), RHS(std::move(RHS)) {}
  };

  // 函数类
  class PrototypeAST {
    std::string Name;
    // vector 封装了动态大小数组的顺序容器
    std::vector<std::string> Args;

    public:
      // move是为了转移所有权，将快要销毁的对象转移给其他变量，这样可以继续使用这个对象
      PrototypeAST(const std::string &Name, std::vector<std::string> Args) 
        : Name(Name), Args(std::move(Args)) {}

      const std::string &getName() const { return Name; }
  };

  class FunctionAST {
    std::unique_ptr<PrototypeAST> Proto;
    std::unique_ptr<ExprAST> Body;

  public:
    FunctionAST(std::unique_ptr<PrototypeAST> Proto,
                std::unique_ptr<ExprAST> Body)
        : Proto(std::move(Proto)), Body(std::move(Body)) {}
  };
}


// ========================================
// 解析Parser
// ========================================

// 1. 基本表达式解析
// eg: 'let' IdentifierStr = 'let'; NumVal = -4 (token_identifier = -4,)
static std::string IdentifierStr;
static double NumVal;

static std::unique_ptr<ExprAST> ParseNumberExpr() {
  auto Result = llvm::make_unique<NumberExprAST>(NumVal);
  // getNextToken(); // 取下一个值
  return std::move(Result);
}

