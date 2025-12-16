#include <iostream>
#include <cctype>
#include "OneList.h"
#include "DoubleList.h"

// Функции проверки гласных/согласных (как в 1-й лабе)
bool isVowel(char c) {
    c = std::tolower(c);
    return (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' || c == 'y');
}

bool isConsonant(char c) {
    c = std::tolower(c);
    return std::isalpha(c) && !isVowel(c);
}

// Обработка строки в односвязном списке
OneList<char> processStringOneList(const std::string& input) {
    OneList<char> result;
    
    for (size_t i = 0; i < input.length(); i++) {
        if (input[i] == '.' && i > 0 && i < input.length() - 1 &&
            isVowel(input[i - 1]) && isConsonant(input[i + 1])) {
            // Заменяем на три точки
            result.push_back('.');
            result.push_back('.');
            result.push_back('.');
        } else if (input[i] != '.') {
            // Оставляем символ
            result.push_back(input[i]);
        }
        // Точка, не удовлетворяющая условиям, удаляется (не добавляется)
    }
    
    return result;
}

// Обработка строки в двусвязном списке
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

// Вывод списка в строку
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

int main() {
    std::cout << "=== Лабораторная работа 3: Односвязные и двусвязные списки ===\n\n";
    
    std::string input;
    std::cout << "Введите строку для обработки: ";
    std::getline(std::cin, input);
    
    // Обработка односвязным списком
    OneList<char> oneResult = processStringOneList(input);
    std::cout << "\nРезультат (односвязный список): " << listToString(oneResult) << std::endl;
    std::cout << "Количество символов: " << oneResult.size() << std::endl;
    
    // Обработка двусвязным списком
    DoubleList<char> doubleResult = processStringDoubleList(input);
    std::cout << "\nРезультат (двусвязный список): " << listToString(doubleResult) << std::endl;
    std::cout << "Количество символов: " << doubleResult.size() << std::endl;
    
    // Демонстрация работы итераторов
    std::cout << "\n=== Демонстрация итераторов ===" << std::endl;
    
    // Обратный вывод через DoubleList (используем --)
    std::cout << "Обратный вывод (двусвязный список): ";
    if (!doubleResult.empty()) {
        auto it = doubleResult.end();
        --it; // Переходим к последнему элементу
        while (true) {
            std::cout << *it;
            if (it == doubleResult.begin()) break;
            --it;
        }
    }
    std::cout << std::endl;
    
    return 0;
}
