# Kaleidoscope Introduction and the Lexer
> [Kaleidoscope Introduction and the Lexer](https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl01.html#id1)

## Lexer (词法分析器 / scanner)
- aim: implementing a language. 
  process a text file and **recognize** what it says
  break the input into **tokens**
- Lexer: token code + metadata 标记 + 标记值


见index.c 文件, 核心处理如下:

0. 定义词法分析的标识, 如 var a = 66.6; var 是token_var key, 对应值是 66.6, gettoken() 方法用来解析的。
1. 如果有空, 直接略过, 指针向下移动;
2. 如果有注释, 直接略过, 指针向下移动;
3. 如果是字母或者数字, 解析关键字, 捕获到 为 var, 那就是token_var类型;
4. 对数字也同理;
5. 最后全部读取完毕, 给个tok_eof标志位。