#include <iostream>
#include <cassert>
#include <cstring>
#include "OneList.h"

// Функция для тестирования
void testStringOperations() {
    std::cout << "=== ТЕСТИРОВАНИЕ ОПЕРАЦИЙ СО СТРОКАМИ ===" << std::endl;
    
    // Тест 1: Создание строки и базовые операции
    {
        std::cout << "\n1. Создание строки 'Hello': ";
        StringList str("Hello");
        str.print();
        
        assert(str.size() == 5);
        std::cout << " - OK" << std::endl;
    }
    
    // Тест 2: Удаление пробелов
    {
        std::cout << "\n2. Удаление пробелов из '  Hello World  ':" << std::endl;
        StringList str("  Hello World  ");
        
        std::cout << "   До: '";
        str.print();
        std::cout << "'" << std::endl;
        
        str.removeWhitespace();
        
        std::cout << "   После: '";
        str.print();
        std::cout << "'" << std::endl;
        
        assert(strcmp(str.c_str(), "HelloWorld") == 0);
        std::cout << "   - OK" << std::endl;
    }
    
    // Тест 3: Приведение к нижнему регистру
    {
        std::cout << "\n3. Приведение 'HeLLo WoRLd' к нижнему регистру:" << std::endl;
        StringList str("HeLLo WoRLd");
        
        std::cout << "   До: '";
        str.print();
        std::cout << "'" << std::endl;
        
        str.toLowercase();
        
        std::cout << "   После: '";
        str.print();
        std::cout << "'" << std::endl;
        
        assert(strcmp(str.c_str(), "hello world") == 0);
        std::cout << "   - OK" << std::endl;
    }
    
    // Тест 4: Приведение к верхнему регистру
    {
        std::cout << "\n4. Приведение 'hello world' к верхнему регистру:" << std::endl;
        StringList str("hello world");
        
        std::cout << "   До: '";
        str.print();
        std::cout << "'" << std::endl;
        
        str.toUppercase();
        
        std::cout << "   После: '";
        str.print();
        std::cout << "'" << std::endl;
        
        assert(strcmp(str.c_str(), "HELLO WORLD") == 0);
        std::cout << "   - OK" << std::endl;
    }
    
    // Тест 5: Удаление символа
    {
        std::cout << "\n5. Удаление символа 'l' из 'hello world':" << std::endl;
        StringList str("hello world");
        
        std::cout << "   До: '";
        str.print();
        std::cout << "'" << std::endl;
        
        str.removeChar('l');
        
        std::cout << "   После: '";
        str.print();
        std::cout << "'" << std::endl;
        
        assert(strcmp(str.c_str(), "heo word") == 0);
        std::cout << "   - OK" << std::endl;
    }
    
    // Тест 6: Проверка палиндрома
    {
        std::cout << "\n6. Проверка строк на палиндром:" << std::endl;
        
        StringList str1("A man a plan a canal Panama");
        std::cout << "   Строка: 'A man a plan a canal Panama'" << std::endl;
        std::cout << "   Является палиндромом? " << (str1.isPalindrome() ? "Да" : "Нет") << std::endl;
        assert(str1.isPalindrome() == true);
        std::cout << "   - OK" << std::endl;
        
        StringList str2("Hello");
        std::cout << "\n   Строка: 'Hello'" << std::endl;
        std::cout << "   Является палиндромом? " << (str2.isPalindrome() ? "Да" : "Нет") << std::endl;
        assert(str2.isPalindrome() == false);
        std::cout << "   - OK" << std::endl;
    }
    
    // Тест 7: Сортировка символов строки (пузырьком)
    {
        std::cout << "\n7. Сортировка символов строки 'hello' (пузырьком):" << std::endl;
        StringList str("hello");
        
        std::cout << "   До: '";
        str.print();
        std::cout << "'" << std::endl;
        
        str.sort_bubble();
        
        std::cout << "   После сортировки: '";
        str.print();
        std::cout << "'" << std::endl;
        
        assert(strcmp(str.c_str(), "ehllo") == 0);
        std::cout << "   - OK" << std::endl;
    }
    
    // Тест 8: Сортировка символов строки (вставками)
    {
        std::cout << "\n8. Сортировка символов строки 'world' (вставками):" << std::endl;
        StringList str("world");
        
        std::cout << "   До: '";
        str.print();
        std::cout << "'" << std::endl;
        
        str.sort_insertion();
        
        std::cout << "   После сортировки: '";
        str.print();
        std::cout << "'" << std::endl;
        
        assert(strcmp(str.c_str(), "dlorw") == 0);
        std::cout << "   - OK" << std::endl;
    }
    
    // Тест 9: Вставка символов
    {
        std::cout << "\n9. Вставка символов в строку 'abc':" << std::endl;
        StringList str("abc");
        
        std::cout << "   Исходная строка: '";
        str.print();
        std::cout << "'" << std::endl;
        
        str.insert(0, 'X'); // В начало
        str.insert(2, 'Y'); // В середину
        str.insert(str.size(), 'Z'); // В конец
        
        std::cout << "   После вставок: '";
        str.print();
        std::cout << "'" << std::endl;
        
        assert(strcmp(str.c_str(), "XaYbcZ") == 0);
        std::cout << "   - OK" << std::endl;
    }
    
    // Тест 10: Комплексная обработка строки
    {
        std::cout << "\n10. Комплексная обработка строки '  AbC  DeF  ':" << std::endl;
        StringList str("  AbC  DeF  ");
        
        std::cout << "   Исходная: '";
        str.print();
        std::cout << "'" << std::endl;
        
        str.removeWhitespace();
        std::cout << "   Без пробелов: '";
        str.print();
        std::cout << "'" << std::endl;
        
        str.toLowercase();
        std::cout << "   Нижний регистр: '";
        str.print();
        std::cout << "'" << std::endl;
        
        str.sort_bubble();
        std::cout << "   Отсортированная: '";
        str.print();
        std::cout << "'" << std::endl;
        
        assert(strcmp(str.c_str(), "abcdef") == 0);
        std::cout << "   - OK" << std::endl;
    }
    
    std::cout << "\n=== ВСЕ ТЕСТЫ ПРОЙДЕНЫ УСПЕШНО! ===" << std::endl;
}

int main() {
    testStringOperations();
    
    // Дополнительно: демонстрация работы
    std::cout << "\n\n=== ДЕМОНСТРАЦИЯ РАБОТЫ ===" << std::endl;
    
    StringList demo("  MaDaM, I'm Adam  ");
    std::cout << "Исходная строка: '";
    demo.print();
    std::cout << "'" << std::endl;
    
    std::cout << "Является палиндромом? " << (demo.isPalindrome() ? "Да" : "Нет") << std::endl;
    
    demo.removeWhitespace();
    demo.removeChar(',');
    demo.removeChar('\'');
    demo.toLowercase();
    
    std::cout << "После обработки: '";
    demo.print();
    std::cout << "'" << std::endl;
    
    std::cout << "Теперь является палиндромом? " << (demo.isPalindrome() ? "Да" : "Нет") << std::endl;
    
    return 0;
}
