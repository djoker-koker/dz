#pragma once
#include <cstddef>
#include <stdexcept>
#include <cstring>  // Для работы со строками
#include <cctype>   // Для isspace, tolower и т.д.

template <class T>
struct Element
{
    T data;           // данные
    Element<T> *next; // указатель на следующий элемент

    Element(const T &value, Element<T> *nextPtr = nullptr)
        : data(value), next(nextPtr)
    {
    }
};

// Специализация для char* для работы со строками
template <>
struct Element<char*>
{
    char* data;           // данные - строка (динамически выделенная)
    Element<char*> *next; // указатель на следующий элемент

    Element(const char* value, Element<char*> *nextPtr = nullptr)
    {
        // Выделяем память для строки
        data = new char[strlen(value) + 1];
        strcpy(data, value);
        next = nextPtr;
    }

    ~Element()
    {
        delete[] data;
    }
};

// Односвязный список OneList<T>
template <class T>
class OneList
{
public:
    // Итератор для хождения по списку в обе стороны (++ и --)
    class iterator
    {
    public:
        iterator(OneList<T> *owner = nullptr, Element<T> *ptr = nullptr)
            : m_owner(owner), m_ptr(ptr)
        {
        }

        // доступ к данным
        T &operator*() const
        {
            return m_ptr->data;
        }

        T *operator->() const
        {
            return &(m_ptr->data);
        }

        // префиксный ++ : переход к следующему элементу
        iterator &operator++()
        {
            if (m_ptr)
                m_ptr = m_ptr->next;
            return *this;
        }

        // постфиксный ++
        iterator operator++(int)
        {
            iterator tmp(*this);
            ++(*this);
            return tmp;
        }

        // префиксный -- : переход к предыдущему элементу
        iterator &operator--()
        {
            if (!m_owner)
                return *this;

            // если сейчас end() (m_ptr == nullptr), шаг назад -> последний элемент
            if (m_ptr == nullptr)
            {
                m_ptr = m_owner->_end;
                return *this;
            }

            // если уже стоим на первом элементе — шаг назад не делаем
            if (m_ptr == m_owner->_begin)
                return *this;

            // ищем элемент, предшествующий текущему
            Element<T> *prev = m_owner->_begin;
            while (prev && prev->next != m_ptr)
                prev = prev->next;

            m_ptr = prev;
            return *this;
        }

        // постфиксный --
        iterator operator--(int)
        {
            iterator tmp(*this);
            --(*this);
            return tmp;
        }

        bool operator==(const iterator &other) const
        {
            return m_ptr == other.m_ptr;
        }

        bool operator!=(const iterator &other) const
        {
            return m_ptr != other.m_ptr;
        }

    private:
        OneList<T> *m_owner; // чтобы уметь двигаться назад, знаем список
        Element<T> *m_ptr;   // текущий узел

        friend class OneList<T>;
    };

public:
    // Конструкторы/деструктор/присваивание
    OneList()
        : _begin(nullptr), _end(nullptr), _count(0)
    {
    }

    OneList(const OneList &other)
        : _begin(nullptr), _end(nullptr), _count(0)
    {
        // копируем элементы по одному в конец
        Element<T> *cur = other._begin;
        while (cur)
        {
            push_back(cur->data);
            cur = cur->next;
        }
    }

    OneList &operator=(const OneList &other)
    {
        if (this == &other)
            return *this;

        clear();

        Element<T> *cur = other._begin;
        while (cur)
        {
            push_back(cur->data);
            cur = cur->next;
        }
        return *this;
    }

    ~OneList()
    {
        clear();
    }

    // добавить элемент в начало списка – push_front(T)
    void push_front(const T &value)
    {
        // 1) создать новый элемент, заполнить данными
        Element<T> *elem = new Element<T>(value);

        // 2) указатель next = текущему началу списка
        elem->next = _begin;

        // 3) сдвинуть начало на новый элемент
        _begin = elem;

        // если список был пуст, то и конец теперь указывает на этот элемент
        if (_end == nullptr)
            _end = elem;

        // 4) увеличить количество
        ++_count;
    }

    // добавить элемент в конец списка – push_back(T)
    void push_back(const T &value)
    {
        // 1) создать новый элемент, заполнить данными, next = nullptr
        Element<T> *elem = new Element<T>(value, nullptr);

        if (_begin == nullptr)
        {
            // список пуст: begin и end указывают на новый элемент
            _begin = _end = elem;
        }
        else
        {
            // список не пуст: end->next = новый элемент, end = elem
            _end->next = elem;
            _end = elem;
        }

        ++_count;
    }

    // добавить элемент в указанное положение списка – insert(int index, T)
    void insert(int index, const T &value)
    {
        if (index <= 0)
        {
            // вставка в начало
            push_front(value);
        }
        else if (index >= _count)
        {
            // вставка за последним = добавление в конец
            push_back(value);
        }
        else
        {
            // вставка в середину перед элементом с номером index
            // 1) создаём новый элемент
            Element<T> *elem = new Element<T>(value);

            // 2) находим элемент, который стоит перед позицией вставки (index-1)
            Element<T> *elemPrev = Move(index - 1);

            // 3) elem->next = elemPrev->next (элемент, который был на позиции index)
            elem->next = elemPrev->next;

            // 4) elemPrev->next = elem
            elemPrev->next = elem;

            ++_count;
        }
    }

    // удалить элемент в начале списка – pop_front()
    void pop_front()
    {
        if (empty())
            return;

        // 1) получить адрес первого элемента
        Element<T> *delElem = _begin;

        // 2) begin = begin->next
        _begin = _begin->next;

        // если после удаления список пуст — end = nullptr
        if (_begin == nullptr)
            _end = nullptr;

        // 3) освободить память
        delete delElem;

        --_count;
    }

    // удалить элемент в конце списка – pop_back()
    void pop_back()
    {
        if (empty())
            return;

        // если в списке один элемент
        if (_begin == _end)
        {
            delete _begin;
            _begin = _end = nullptr;
            _count = 0;
            return;
        }

        // список содержит больше одного элемента
        // 1) найти предпоследний элемент
        Element<T> *elemPrev = _begin;
        while (elemPrev->next != _end)
            elemPrev = elemPrev->next;

        // 2) запомнить последний
        Element<T> *elemDel = _end;

        // 3) сдвинуть end на предпоследний
        _end = elemPrev;
        _end->next = nullptr;

        // 4) удалить последний
        delete elemDel;

        --_count;
    }

    // удалить из списка совпадающие с элементом значения – remove(T)
    void remove(const T &value)
    {
        if (empty())
            return;

        // сначала удаляем все совпадения в начале списка
        while (_begin && _begin->data == value)
        {
            pop_front();
        }

        if (!_begin)
            return;

        // теперь внутри и в конце
        Element<T> *prev = _begin;
        Element<T> *cur = _begin->next;

        while (cur)
        {
            if (cur->data == value)
            {
                prev->next = cur->next;

                if (cur == _end)
                    _end = prev;

                delete cur;
                cur = prev->next;
                --_count;
            }
            else
            {
                prev = cur;
                cur = cur->next;
            }
        }
    }

    // вернуть количество элементов в списке – size()
    int size() const
    {
        return _count;
    }

    // проверить пуст ли список – empty()
    bool empty() const
    {
        return _count == 0;
    }

    // вернуть ссылку на первый элемент – front()
    T &front()
    {
        if (empty())
            throw std::runtime_error("OneList::front(): list is empty");
        return _begin->data;
    }

    const T &front() const
    {
        if (empty())
            throw std::runtime_error("OneList::front(): list is empty");
        return _begin->data;
    }

    // вернуть ссылку на последний элемент – back()
    T &back()
    {
        if (empty())
            throw std::runtime_error("OneList::back(): list is empty");
        return _end->data;
    }

    const T &back() const
    {
        if (empty())
            throw std::runtime_error("OneList::back(): list is empty");
        return _end->data;
    }

    // итератор на первый элемент
    iterator begin()
    {
        return iterator(this, _begin);
    }

    // итератор "за последним" элементом
    iterator end()
    {
        return iterator(this, nullptr);
    }

    // Сортировка пузырьком (по возрастанию, используя operator>)
    void sort_bubble()
    {
        if (_count < 2)
            return;

        bool swapped;
        do
        {
            swapped = false;
            Element<T> *cur = _begin;

            while (cur && cur->next)
            {
                if (cur->data > cur->next->data)
                {
                    // меняем местами значения в узлах
                    T tmp = cur->data;
                    cur->data = cur->next->data;
                    cur->next->data = tmp;
                    swapped = true;
                }
                cur = cur->next;
            }
        } while (swapped);
    }

    // Сортировка вставками
    void sort_insertion()
    {
        if (_count < 2)
            return;

        // создаём новый "отсортированный" список,
        // по одному выдёргиваем узлы из старого и вставляем в нужное место
        Element<T> *sorted = nullptr; // начало отсортированной части
        Element<T> *cur = _begin;     // текущий узел из исходного списка

        while (cur)
        {
            Element<T> *next = cur->next; // запоминаем следующий до того, как перекрутим ссылки

            // если отсортированная часть пуста или вставка в самое начало
            if (!sorted || cur->data < sorted->data)
            {
                cur->next = sorted;
                sorted = cur;
            }
            else
            {
                // ищем позицию внутри отсортированной части
                Element<T> *s = sorted;
                while (s->next && s->next->data <= cur->data)
                    s = s->next;

                cur->next = s->next;
                s->next = cur;
            }

            cur = next;
        }

        // теперь sorted — это новый _begin,
        // а _end нужно найти, пройдя до конца
        _begin = sorted;
        _end = _begin;
        if (_end)
        {
            while (_end->next)
                _end = _end->next;
        }
        // _count не менялся
    }

    // === СПЕЦИАЛЬНЫЕ МЕТОДЫ ДЛЯ СТРОК (char[]) ===
    
    // Обработать строку: удалить все пробельные символы
    void removeWhitespace()
    {
        if (empty())
            return;

        // Сначала удаляем пробелы в начале
        while (_begin && std::isspace(static_cast<unsigned char>(_begin->data)))
        {
            pop_front();
        }

        if (!_begin)
            return;

        // Теперь удаляем пробелы внутри и в конце
        Element<T> *prev = _begin;
        Element<T> *cur = _begin->next;

        while (cur)
        {
            if (std::isspace(static_cast<unsigned char>(cur->data)))
            {
                prev->next = cur->next;

                if (cur == _end)
                    _end = prev;

                delete cur;
                cur = prev->next;
                --_count;
            }
            else
            {
                prev = cur;
                cur = cur->next;
            }
        }
    }

    // Привести все символы к нижнему регистру
    void toLowercase()
    {
        Element<T> *cur = _begin;
        while (cur)
        {
            cur->data = std::tolower(static_cast<unsigned char>(cur->data));
            cur = cur->next;
        }
    }

    // Привести все символы к верхнему регистру
    void toUppercase()
    {
        Element<T> *cur = _begin;
        while (cur)
        {
            cur->data = std::toupper(static_cast<unsigned char>(cur->data));
            cur = cur->next;
        }
    }

    // Удалить все вхождения указанного символа
    void removeChar(T ch)
    {
        remove(ch); // используем существующий метод remove
    }

    // Проверить, является ли строка палиндромом (игнорируя регистр и пробелы)
    bool isPalindrome()
    {
        if (empty())
            return true;

        // Создаем копию для обработки
        OneList<T> copy = *this;
        
        // Удаляем пробелы и приводим к нижнему регистру
        copy.removeWhitespace();
        copy.toLowercase();

        // Проверяем палиндром
        iterator it_begin = copy.begin();
        iterator it_end = copy.end();
        
        if (it_begin == it_end)
            return true;
            
        --it_end; // переходим к последнему элементу
        
        while (it_begin != it_end)
        {
            if (*it_begin != *it_end)
                return false;
                
            ++it_begin;
            if (it_begin == it_end)
                break;
            --it_end;
        }
        
        return true;
    }

    // Преобразовать список символов в C-строку
    // ВНИМАНИЕ: вызывающий должен освободить память delete[]
    char* toString() const
    {
        if (empty())
        {
            char* result = new char[1];
            result[0] = '\0';
            return result;
        }

        char* result = new char[_count + 1];
        Element<T>* cur = _begin;
        int i = 0;
        
        while (cur && i < _count)
        {
            result[i++] = cur->data;
            cur = cur->next;
        }
        
        result[i] = '\0';
        return result;
    }

private:
    Element<T> *_begin; // указатель на первый элемент списка
    Element<T> *_end;   // указатель на последний элемент списка
    int _count;         // количество элементов в списке

    // Вспомогательный метод: вернуть указатель на элемент по индексу [0.._count-1]
    Element<T> *Move(int index) const
    {
        if (index < 0 || index >= _count)
            return nullptr;

        Element<T> *cur = _begin;
        int i = 0;
        while (cur && i < index)
        {
            cur = cur->next;
            ++i;
        }
        return cur; // либо элемент, либо nullptr
    }

    // очистка списка
    void clear()
    {
        Element<T> *cur = _begin;
        while (cur)
        {
            Element<T> *next = cur->next;
            delete cur;
            cur = next;
        }
        _begin = _end = nullptr;
        _count = 0;
    }
};

// Специализация для работы со строками (массивами char)
class StringList : public OneList<char>
{
public:
    // Конструктор из C-строки
    StringList(const char* str = "")
    {
        if (str)
        {
            for (int i = 0; str[i] != '\0'; i++)
            {
                push_back(str[i]);
            }
        }
    }

    // Преобразование в C-строку
    const char* c_str() const
    {
        char* result = toString();
        // Храним результат в статическом буфере для простоты
        // В реальном коде нужно было бы использовать более сложное управление памятью
        static char buffer[1024];
        strcpy(buffer, result);
        delete[] result;
        return buffer;
    }

    // Вывод строки
    void print() const
    {
        char* str = toString();
        std::cout << str;
        delete[] str;
    }
};
