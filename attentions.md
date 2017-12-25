# 注意事项
## 汉字编码统一：UTF-8
用统一汉字编码保证不同电脑上注释不出乱码。
## 成员函数避免直接输入输出流
方便对输出样式的调整
## 只需对hpp、cpp文件进行修改
考虑到不同编译器的工程不同，只需修改hpp，与cpp。
## 在hpp文件中类内声明，类外定义，对自己新建的成员变量及函数进行必要注释
方便之后理清代码结构