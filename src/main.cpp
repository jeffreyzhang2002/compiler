#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "./token/Token.h"
#include "./lexer/Lexer.h"

int main() {

    std::ifstream file("D:\\source\\FirLang\\examples\\example1.txt");
    Lexer lexer(file);

    std::cout << "Done lexing" << "\n";



    while(lexer.hasNext()) {

        Token t = lexer.nextToken();

        std::cout << "(  " << t.value << "  ,  " << (int) t.type << "  ) \n";
    }


}