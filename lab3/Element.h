#pragma once

// Шаблонный класс элемента для списков
template <typename T>
class Element {
public:
    T data;
    Element<T>* next;
    Element<T>* prev;  // Для односвязного списка не используется
    
    Element(const T& value) 
        : data(value), next(nullptr), prev(nullptr) {}
    
    // Конструктор с указателями (для удобства)
    Element(const T& value, Element<T>* p, Element<T>* n)
        : data(value), next(n), prev(p) {}
};
