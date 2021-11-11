namespace LLVMToy {
  namespace ParserPrecedence {    
    const int Assign = 0;
    const int LogicalOR = 1;
    const int LogicalAND = 2;
    const int BitwiseOR = 3;
    const int BitwiseXOR = 4;
    const int BitwiseAND = 5;
    const int Equality = 6;
    const int Relational = 7;
    const int Multiplication = 8;
    const int Addition = 9;
    const int Unary = 10;
    const int Prefix = 11;
    const int Postfix = 12;
    const int MemberSelection = 13;
    const int Brackets = 14;
    const int Parentheses = 15;
  };
}