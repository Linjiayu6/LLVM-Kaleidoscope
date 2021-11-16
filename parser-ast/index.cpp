class ExprAST {
  public:
    virtual ~ExprAST() {}
    // 这是用于实现IR代码生成的东西
    virtual llvm::Value *codegen() = 0;
  };
}

// 定义解析的 数字 的语法树
class NumberExprAST : public ExprAST {
  double Val;

public:
  NumberExprAST(double Val) : Val(Val) {}
  llvm::Value *codegen() override;
};

// 定义解析的 变量 的语法树
class VariableExprAST : public ExprAST {
  std::string Name;

public:
  VariableExprAST(const std::string &Name) : Name(Name) {}
  llvm::Value *codegen() override;
};