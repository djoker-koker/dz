#pragma once
#include "Element.h"
#include <stdexcept>

// Двусвязный список DoubleList<T>
template <class T>
class DoubleList {
private:
    Element<T>* _begin; // первый элемент списка
    Element<T>* _end;   // последний элемент списка
    int _count;         // количество элементов
    
    // Вспомогательный метод: получить указатель на элемент по индексу
    Element<T>* Move(int index) const {
        if (index < 0 || index >= _count) return nullptr;
        
        // Оптимизация: выбираем направление обхода
        if (index <= _count / 2) {
            Element<T>* cur = _begin;
            for (int i = 0; i < index; i++) {
                cur = cur->next;
            }
            return cur;
        } else {
            Element<T>* cur = _end;
            for (int i = _count - 1; i > index; i--) {
                cur = cur->prev;
            }
            return cur;
        }
    }
    
    // Очистка списка
    void clear() {
        Element<T>* cur = _begin;
        while (cur) {
            Element<T>* next = cur->next;
            delete cur;
            cur = next;
        }
        _begin = _end = nullptr;
        _count = 0;
    }
    
public:
    // Конструкторы/деструктор
    DoubleList() : _begin(nullptr), _end(nullptr), _count(0) {}
    
    DoubleList(const DoubleList& other) : _begin(nullptr), _end(nullptr), _count(0) {
        Element<T>* cur = other._begin;
        while (cur) {
            push_back(cur->data);
            cur = cur->next;
        }
    }
    
    DoubleList& operator=(const DoubleList& other) {
        if (this != &other) {
            clear();
            Element<T>* cur = other._begin;
            while (cur) {
                push_back(cur->data);
                cur = cur->next;
            }
        }
        return *this;
    }
    
    ~DoubleList() {
        clear();
    }
    
    // 1. Добавить элемент в начало
    void push_front(const T& value) {
        Element<T>* elem = new Element<T>(value, nullptr, _begin);
        
        if (_begin) {
            _begin->prev = elem;
        } else {
            _end = elem; // список был пуст
        }
        
        _begin = elem;
        ++_count;
    }
    
    // 2. Добавить элемент в конец
    void push_back(const T& value) {
        Element<T>* elem = new Element<T>(value, _end, nullptr);
        
        if (_end) {
            _end->next = elem;
        } else {
            _begin = elem; // список был пуст
        }
        
        _end = elem;
        ++_count;
    }
    
    // 3. Вставить элемент по позиции
    void insert(int index, const T& value) {
        if (index <= 0) {
            push_front(value);
        } else if (index >= _count) {
            push_back(value);
        } else {
            Element<T>* cur = Move(index); // элемент на позиции index
            
            if (!cur) {
                push_back(value);
                return;
            }
            
            Element<T>* prev = cur->prev;
            Element<T>* elem = new Element<T>(value, prev, cur);
            
            if (prev) prev->next = elem;
            cur->prev = elem;
            
            ++_count;
        }
    }
    
    // 4. Удалить элемент из начала
    void pop_front() {
        if (empty()) return;
        
        Element<T>* del = _begin;
        _begin = _begin->next;
        
        if (_begin) {
            _begin->prev = nullptr;
        } else {
            _end = nullptr; // список опустел
        }
        
        delete del;
        --_count;
    }
    
    // 5. Удалить элемент из конца
    void pop_back() {
        if (empty()) return;
        
        Element<T>* del = _end;
        _end = _end->prev;
        
        if (_end) {
            _end->next = nullptr;
        } else {
            _begin = nullptr; // список опустел
        }
        
        delete del;
        --_count;
    }
    
    // 6. Удалить все вхождения значения
    void remove(const T& value) {
        Element<T>* cur = _begin;
        
        while (cur) {
            if (cur->data == value) {
                Element<T>* del = cur;
                Element<T>* next = cur->next;
                
                if (del->prev) {
                    del->prev->next = del->next;
                } else {
                    _begin = del->next; // удалили первый
                }
                
                if (del->next) {
                    del->next->prev = del->prev;
                } else {
                    _end = del->prev; // удалили последний
                }
                
                delete del;
                cur = next;
                --_count;
            } else {
                cur = cur->next;
            }
        }
    }
    
    // 7. Количество элементов
    int size() const {
        return _count;
    }
    
    // 8. Ссылка на первый элемент
    T& front() {
        if (empty()) throw std::runtime_error("DoubleList::front(): empty list");
        return _begin->data;
    }
    
    const T& front() const {
        if (empty()) throw std::runtime_error("DoubleList::front(): empty list");
        return _begin->data;
    }
    
    // 9. Ссылка на последний элемент
    T& back() {
        if (empty()) throw std::runtime_error("DoubleList::back(): empty list");
        return _end->data;
    }
    
    const T& back() const {
        if (empty()) throw std::runtime_error("DoubleList::back(): empty list");
        return _end->data;
    }
    
    // 10. Проверка на пустоту
    bool empty() const {
        return _count == 0;
    }
    
    // Итератор
    class Iterator {
    private:
        Element<T>* m_ptr;
        DoubleList<T>* m_owner; // для корректного -- из end()
        
    public:
        Iterator(DoubleList<T>* owner = nullptr, Element<T>* ptr = nullptr)
            : m_owner(owner), m_ptr(ptr) {}
        
        T& operator*() const { return m_ptr->data; }
        T* operator->() const { return &(m_ptr->data); }
        
        // Префиксный ++
        Iterator& operator++() {
            if (m_ptr) m_ptr = m_ptr->next;
            return *this;
        }
        
        // Постфиксный ++
        Iterator operator++(int) {
            Iterator tmp(*this);
            ++(*this);
            return tmp;
        }
        
        // Префиксный --
        Iterator& operator--() {
            if (!m_owner) return *this;
            
            if (m_ptr == nullptr) {
                // из end() отступаем к последнему
                m_ptr = m_owner->_end;
                return *this;
            }
            
            m_ptr = m_ptr->prev;
            return *this;
        }
        
        // Постфиксный --
        Iterator operator--(int) {
            Iterator tmp(*this);
            --(*this);
            return tmp;
        }
        
        bool operator==(const Iterator& other) const {
            return m_ptr == other.m_ptr;
        }
        
        bool operator!=(const Iterator& other) const {
            return m_ptr != other.m_ptr;
        }
        
        friend class DoubleList<T>;
    };
    
    Iterator begin() { return Iterator(this, _begin); }
    Iterator end() { return Iterator(this, nullptr); }
};
