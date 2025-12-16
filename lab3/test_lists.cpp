#include <iostream>
#include <cassert>
#include "OneList.h"
#include "DoubleList.h"

void testOneList() {
    std::cout << "Тестирование OneList...\n";
    
    OneList<int> list;
    
    // 1. Проверка пустого списка
    assert(list.empty());
    assert(list.size() == 0);
    
    // 2. push_back
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    assert(list.size() == 3);
    assert(list.front() == 1);
    assert(list.back() == 3);
    
    // 3. push_front
    list.push_front(0);
    assert(list.size() == 4);
    assert(list.front() == 0);
    
    // 4. insert
    list.insert(2, 99);
    assert(list.size() == 5);
    
    // 5. Итератор
    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }
    assert(sum == 0 + 1 + 99 + 2 + 3);
    
    // 6. pop_front
    list.pop_front();
    assert(list.front() == 1);
    assert(list.size() == 4);
    
    // 7. pop_back
    list.pop_back();
    assert(list.back() == 2);
    assert(list.size() == 3);
    
    // 8. remove
    list.push_back(1);
    list.push_back(1);
    list.remove(1);
    assert(list.size() <= 3); // Удалили все 1
    
    std::cout << "OneList тесты пройдены!\n";
}

void testDoubleList() {
    std::cout << "Тестирование DoubleList...\n";
    
    DoubleList<int> list;
    
    // 1. Проверка пустого списка
    assert(list.empty());
    assert(list.size() == 0);
    
    // 2. push_back
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    assert(list.size() == 3);
    assert(list.front() == 10);
    assert(list.back() == 30);
    
    // 3. push_front
    list.push_front(5);
    assert(list.size() == 4);
    assert(list.front() == 5);
    
    // 4. insert
    list.insert(2, 15);
    assert(list.size() == 5);
    
    // 5. Итератор вперед
    int sum = 0;
    for (auto it = list.begin(); it != list.end(); ++it) {
        sum += *it;
    }
    assert(sum == 5 + 10 + 15 + 20 + 30);
    
    // 6. Итератор назад
    auto it = list.end();
    --it; // последний элемент
    assert(*it == 30);
    --it;
    assert(*it == 20);
    
    // 7. pop_front
    list.pop_front();
    assert(list.front() == 10);
    assert(list.size() == 4);
    
    // 8. pop_back
    list.pop_back();
    assert(list.back() == 20);
    assert(list.size() == 3);
    
    // 9. remove
    list.push_back(10);
    list.remove(10);
    assert(list.size() <= 2);
    
    std::cout << "DoubleList тесты пройдены!\n";
}

int main() {
    testOneList();
    testDoubleList();
    
    std::cout << "\nВсе тесты пройдены успешно!\n";
    return 0;
}
