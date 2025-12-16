#include <iostream>
#include <cassert>
#include "OneList.h"
#include "DoubleList.h"

bool isVowel(char c) {
    c = std::tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

bool isConsonant(char c) {
    c = std::tolower(c);
    return std::isalpha(c) && !isVowel(c);
}

OneList<char> processStringOneList(const std::string& input) {
    OneList<char> result;
    
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] == '.' && i > 0 && i < input.length() - 1 &&
            isVowel(input[i - 1]) && isConsonant(input[i + 1])) {
            result.push_back('.');
            result.push_back('.');
            result.push_back('.');
        } else if (input[i] != '.') {
            result.push_back(input[i]);
        }
    }
    
    return result;
}

DoubleList<char> processStringDoubleList(const std::string& input) {
    DoubleList<char> result;
    
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] == '.' && i > 0 && i < input.length() - 1 &&
            isVowel(input[i - 1]) && isConsonant(input[i + 1])) {
            result.push_back('.');
            result.push_back('.');
            result.push_back('.');
        } else if (input[i] != '.') {
            result.push_back(input[i]);
        }
    }
    
    return result;
}

std::string listToString(const OneList<char>& list) {
    std::string result;
    for (auto it = list.begin(); it != list.end(); ++it) {
        result += *it;
    }
    return result;
}

std::string listToString(const DoubleList<char>& list) {
    std::string result;
    for (auto it = list.begin(); it != list.end(); ++it) {
        result += *it;
    }
    return result;
}

void testProcessing() {
    std::cout << "Тестирование обработки строк...\n";
    
    // Тест 1: Простая замена
    {
        std::string input = "a.b";
        OneList<char> oneResult = processStringOneList(input);
        DoubleList<char> doubleResult = processStringDoubleList(input);
        
        assert(listToString(oneResult) == "a...b");
        assert(listToString(doubleResult) == "a...b");
        std::cout << "Тест 1 пройден: a.b -> a...b\n";
    }
    
    // Тест 2: Удаление точки (не гласная перед)
    {
        std::string input = "b.c";
        OneList<char> oneResult = processStringOneList(input);
        DoubleList<char> doubleResult = processStringDoubleList(input);
        
        assert(listToString(oneResult) == "bc");
        assert(listToString(doubleResult) == "bc");
        std::cout << "Тест 2 пройден: b.c -> bc\n";
    }
    
    // Тест 3: Удаление точки (не согласная после)
    {
        std::string input = "a.a";
        OneList<char> oneResult = processStringOneList(input);
        DoubleList<char> doubleResult = processStringDoubleList(input);
        
        assert(listToString(oneResult) == "aa");
        assert(listToString(doubleResult) == "aa");
        std::cout << "Тест 3 пройден: a.a -> aa\n";
    }
    
    // Тест 4: Точка в конце строки
    {
        std::string input = "hello.";
        OneList<char> oneResult = processStringOneList(input);
        DoubleList<char> doubleResult = processStringDoubleList(input);
        
        assert(listToString(oneResult) == "hello");
        assert(listToString(doubleResult) == "hello");
        std::cout << "Тест 4 пройден: hello. -> hello\n";
    }
    
    // Тест 5: Точка в начале строки
    {
        std::string input = ".start";
        OneList<char> oneResult = processStringOneList(input);
        DoubleList<char> doubleResult = processStringDoubleList(input);
        
        assert(listToString(oneResult) == "start");
        assert(listToString(doubleResult) == "start");
        std::cout << "Тест 5 пройден: .start -> start\n";
    }
    
    // Тест 6: Сложный случай
    {
        std::string input = "hello.world test.abc.";
        OneList<char> oneResult = processStringOneList(input);
        DoubleList<char> doubleResult = processStringDoubleList(input);
        
        std::string expected = "hello...world testabc";
        assert(listToString(oneResult) == expected);
        assert(listToString(doubleResult) == expected);
        std::cout << "Тест 6 пройден: сложная строка\n";
    }
    
    // Тест 7: Пустая строка
    {
        std::string input = "";
        OneList<char> oneResult = processStringOneList(input);
        DoubleList<char> doubleResult = processStringDoubleList(input);
        
        assert(listToString(oneResult) == "");
        assert(listToString(doubleResult) == "");
        std::cout << "Тест 7 пройден: пустая строка\n";
    }
    
    std::cout << "Все тесты обработки пройдены!\n";
}

int main() {
    testProcessing();
    return 0;
}
