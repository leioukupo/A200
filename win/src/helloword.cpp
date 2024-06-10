//
// Created by leioukupo on 2024/3/23.
//
#include <iostream>
#include <string>
int main() {
    std::string input;
    std::cout << "请输入一些文本：" << std::endl;
    std::getline(std::cin, input);  // 读取整行输入
    std::cout << "你输入的是：" << input << std::endl;
    return 0;
}
