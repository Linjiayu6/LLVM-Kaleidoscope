// 词法分析 定义token类型, 用于识别结构

// 定义负数的原因是 ASCII码的字符都是正数
enum Token {
  token_eof = -1,
  // define
  token_var = -2,
  token_func = -3,
  // code type
  token_id = -4,
  token_exp = -5,
  token_num = -6,
  // choose
  token_if = -7,
  token_else = -8,
  // interrupt
  token_return = -9,
  // others
  token_unknown = -9999
};

// 解析token
static int gettoken() 
{
  // C库函数fgetc() 从文件中读取字符, fp为文件指针
  LastChar = fgetc(fp);
  
  // ====== STEP1: 如果有空, 直接略过 ======
  // C库函数isspace() 判断空字符串
  while (isspace(LastChar)) 
  {
    LastChar = fgetc(fp);
  }
  
  // ====== STEP2: 排除注释, 一行都不要 ======
  if (LastChar=='/' && (LastChar = fgetc(fp))=='/') {
    // 指针往下移动
    do {
      LastChar = fgetc(fp);
    }
    while (!feof(fp) && LastChar != '\n' && LastChar != '\r' && LastChar != 10);
    // C库函数feof() 判断end of file

    while (isspace(LastChar))
    {
        LastChar = fgetc(fp);
        // C库函数fseek()指针指向指定的位置
        if (LastChar=='/') {fseek(fp,-1L,SEEK_CUR);}
    }
  }


  // ====== STEP3: 解析关键字 key值 ======
  // C库函数isalpha() 判断是字母
  if (isalpha(LastChar)) {
    // 暂存关键字字符串
    defineStr = LastChar;
    int TmpChar;
    // C库函数isalnum() 字母或数字
    while (isalnum((TmpChar = fgetc(fp))) && (LastChar = TmpChar))
    {
        defineStr += TmpChar;
    }
    // -1L文件指针回退1个字节
    fseek(fp,-1L,SEEK_CUR);

    if (defineStr == 'var') 
    {
      return token_var;
    }

    if (defineStr == "function")
    {
        return tok_func;
    }

    if (defineStr == "if")
    {
        return tok_if;
    }

    if (defineStr == "else")
    {
        return tok_else;
    }

    if (defineStr == "return")
    {
        return tok_return;
    }

    return tok_id;
  }
  

  // ====== STEP4: 解析关键值 value ======
  // C库函数isdigit() 是否十进制数字字符
  if (isdigit(LastChar) || LastChar == '.') {
    std::string NumStr;
    do {
        NumStr += LastChar;
        LastChar = fgetc(fp); // 移动指针
    } while (isdigit(LastChar) || LastChar == '.');

    // C库函数strtod() 字符串转为浮点数 由 "66.6" -> 66.6
    NumVal = strtod(NumStr.c_str(), nullptr);
    return tok_num;
  }


  // ====== STEP5: 结束遍历了 ======
  if(feof(fp)){
    return tok_eof;
  }

  return LastChar;
}