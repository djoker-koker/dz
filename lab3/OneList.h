#pragma once
#include "Element.h"
#include <stdexcept>

template <typename T>
class OneList {
private:
    Element<T>* head;  // первый элемент
    Element<T>* tail;  // последний элемент
    int count;
    
    // Вспомогательный метод для получения элемента по индексу
    Element<T>* getNode(int index) const {
        if (index < 0 || index >= count) return nullptr;
        Element<T>* current = head;
        for (int i = 0; i < index && current; i++) {
            current = current->next;
        }
        return current;
    }
    
    // Очистка списка
    void clear() {
        Element<T>* current = head;
        while (current) {
            Element<T>* next = current->next;
            delete current;
            current = next;
        }
        head = tail = nullptr;
        count = 0;
    }
    
public:
    // Конструкторы/деструктор
    OneList() : head(nullptr), tail(nullptr), count(0) {}
    
    OneList(const OneList& other) : head(nullptr), tail(nullptr), count(0) {
        Element<T>* current = other.head;
        while (current) {
            push_back(current->data);
            current = current->next;
        }
    }
    
    OneList& operator=(const OneList& other) {
        if (this != &other) {
            clear();
            Element<T>* current = other.head;
            while (current) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    ~OneList() {
        clear();
    }
    
    // 1. Добавить элемент в начало
    void push_front(const T& value) {
        Element<T>* newElem = new Element<T>(value);
        newElem->next = head;
        
        if (!head) {
            // Список был пуст
            tail = newElem;
        }
        head = newElem;
        count++;
    }
    
    // 2. Добавить элемент в конец
    void push_back(const T& value) {
        Element<T>* newElem = new Element<T>(value);
        
        if (!head) {
            // Список пуст
            head = tail = newElem;
        } else {
            tail->next = newElem;
            tail = newElem;
        }
        count++;
    }
    
    // 3. Вставить элемент по позиции
    void insert(int pos, const T& value) {
        if (pos <= 0) {
            push_front(value);
        } else if (pos >= count) {
            push_back(value);
        } else {
            // Вставка в середину
            Element<T>* prev = getNode(pos - 1);
            if (prev) {
                Element<T>* newElem = new Element<T>(value);
                newElem->next = prev->next;
                prev->next = newElem;
                count++;
            }
        }
    }
    
    // 4. Удалить элемент из конца
    void pop_back() {
        if (empty()) return;
        
        if (head == tail) {
            // Один элемент
            delete head;
            head = tail = nullptr;
        } else {
            // Найти предпоследний элемент
            Element<T>* current = head;
            while (current->next != tail) {
                current = current->next;
            }
            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        count--;
    }
    
    // 5. Удалить элемент из начала
    void pop_front() {
        if (empty()) return;
        
        Element<T>* temp = head;
        head = head->next;
        
        if (!head) {
            tail = nullptr; // Список опустел
        }
        
        delete temp;
        count--;
    }
    
    // 6. Удалить все вхождения значения
    void remove(const T& value) {
        // Удаление из начала
        while (head && head->data == value) {
            pop_front();
        }
        
        // Удаление из середины и конца
        Element<T>* current = head;
        Element<T>* prev = nullptr;
        
        while (current) {
            if (current->data == value) {
                if (prev) {
                    prev->next = current->next;
                    if (current == tail) {
                        tail = prev;
                    }
                    delete current;
                    current = prev->next;
                    count--;
                }
            } else {
                prev = current;
                current = current->next;
            }
        }
    }
    
    // 7. Количество элементов
    int size() const {
        return count;
    }
    
    // 8. Ссылка на первый элемент
    T& front() {
        if (empty()) throw std::runtime_error("OneList::front(): empty list");
        return head->data;
    }
    
    const T& front() const {
        if (empty()) throw std::runtime_error("OneList::front(): empty list");
        return head->data;
    }
    
    // 9. Ссылка на последний элемент
    T& back() {
        if (empty()) throw std::runtime_error("OneList::back(): empty list");
        return tail->data;
    }
    
    const T& back() const {
        if (empty()) throw std::runtime_error("OneList::back(): empty list");
        return tail->data;
    }
    
    // 10. Проверка на пустоту
    bool empty() const {
        return count == 0;
    }
    
    // Итератор (упрощенный, только вперед)
    class Iterator {
    private:
        Element<T>* current;
        
    public:
        Iterator(Element<T>* ptr = nullptr) : current(ptr) {}
        
        T& operator*() const { return current->data; }
        T* operator->() const { return &(current->data); }
        
        // Префиксный ++
        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }
        
        // Постфиксный ++
        Iterator operator++(int) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
        
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
    
    Iterator begin() { return Iterator(head); }
    Iterator end() { return Iterator(nullptr); }
};
