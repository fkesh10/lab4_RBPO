#include <iostream>
#include <initializer_list>
#include <iterator>

//Дек на основе массива
template <typename T> class DequeBasedOnArray
{
public:
    using Iterator = T*;

    //конструктор по умолчанию
    DequeBasedOnArray();

    //явный конструктор преобразования
    explicit DequeBasedOnArray(int _size);

    //конструктор копирования
    DequeBasedOnArray(const DequeBasedOnArray& _object);

    //конструктор перемещения
    DequeBasedOnArray(DequeBasedOnArray&& _object);

    //конструктор с использованием списка инициализации
    DequeBasedOnArray(std::initializer_list<int> _ilist);

    //деконструктор
    ~DequeBasedOnArray();

    //перегрузка оператора присваивания для копирования
    DequeBasedOnArray& operator=(const DequeBasedOnArray& _object);

    //перегрузка оператора присваивания для перемещения
    DequeBasedOnArray& operator=(DequeBasedOnArray&& _object);

    //перегрузка оператора присваивания для списка инициализации
    DequeBasedOnArray& operator=(std::initializer_list<int> _ilist);

    //итераторы для работы с элементами дека
    DequeBasedOnArray::Iterator begin();
    const DequeBasedOnArray::Iterator begin() const;
    DequeBasedOnArray::Iterator end();
    const DequeBasedOnArray::Iterator end() const;

    //перегрузка оператора индексации
    const int& operator[](int _index) const;
    int& operator[](int _index);

    //потоковый вывод
    template <typename T>
    friend std::ostream& operator<<(std::ostream& stream, const DequeBasedOnArray<T>& _object);

    //функции члены
    //получение размера
    unsigned GetSize() const;
    //вставка элемента в начало
    bool PushFront(const T& _element);
    //удаление элемента в начале
    bool PopFront(T& _element);
    //вставка элемента в конец
    bool PushBack(const T& _element);
    //удаление элемента с конца
    bool PopBack(T& _element);
    //получение элемента с начала
    bool PeekFront(T& _element) const;
    //получение элемента с конца
    bool PeekBack(T& _element) const;


private:
    T* arr;
    int size;
};

//конструктор по умолчанию
template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray()
{
    size = 0;
    arr = new int(size);
}
//конструктор преобразования
template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray(int _size) : size(_size)
{
    arr = new int[_size];
}
//консруктор копирования
template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray(const DequeBasedOnArray& _object)
{
    arr = new int[_object.size];
    size = _object.size;
    for (int i = 0; i < size; ++i)
    {
        arr[i] = _object.arr[i];
    }
}
//конструктор перемещения
template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray(DequeBasedOnArray&& _object)
{
    arr = _object.arr;
    size = _object.size;
    _object.arr = nullptr;
}
//конструктор для листа инициализации
template <typename T>
DequeBasedOnArray<T>::DequeBasedOnArray(std::initializer_list<int> _ilist)
    : arr(new int[_ilist.size()]), size(_ilist.size())
{
    int i = 0;
    for (const auto& element : _ilist)
    {
        arr[i++] = element;
    }
}
//деструктор
template <typename T>
DequeBasedOnArray<T>::~DequeBasedOnArray() {
    delete[] arr;
}
//операция присвоение
template <typename T>
DequeBasedOnArray<T>& DequeBasedOnArray<T>::operator=(const DequeBasedOnArray& _object)
{
    if (this == &_object)
    {
        return *this;
    }
    delete[] arr;
    arr = new int[_object.size];
    size = _object.size;
    for (int i = 0; i < size; ++i)
    {
        arr[i] = _object.arr[i];
    }
    return *this;
}
//операция присвоение с перемещением
template <typename T>
DequeBasedOnArray<T>& DequeBasedOnArray<T>::operator=(DequeBasedOnArray&& _object)
{
    if (this == &_object)
    {
        return *this;
    }
    delete[] arr;
    arr = _object.arr;
    size = _object.size;
    _object.arr = nullptr;
}

template<typename T>
DequeBasedOnArray<T>& DequeBasedOnArray<T>::operator=(std::initializer_list<int> _ilist)
{
    delete[] arr;
    arr = new int[_ilist.size()];
    size = _ilist.size();
    int i = 0;
    for (const auto& element : _ilist)
    {
        arr[i++] = element;
    }
    return *this;
}


template<typename T>
typename DequeBasedOnArray<T>::Iterator DequeBasedOnArray<T>::begin()
{
    return Iterator(arr);
}

template<typename T>
const typename DequeBasedOnArray<T>::Iterator DequeBasedOnArray<T>::begin() const
{
    return Iterator(arr);
}

template<typename T>
typename DequeBasedOnArray<T>::Iterator DequeBasedOnArray<T>::end()
{
    return Iterator(arr + size);
}

template<typename T>
const typename DequeBasedOnArray<T>::Iterator DequeBasedOnArray<T>::end() const
{
    return Iterator(arr + size);
}

const int& DequeBasedOnArray<int>::operator[](int _index) const
{
    // TODO: вставьте здесь оператор return
    return _index;
}

int& DequeBasedOnArray<int>::operator[](int _index)
{
    return _index;
}

//перегруженный оператр вывода
template<typename T>
std::ostream& operator<<(std::ostream& stream, const DequeBasedOnArray<T>& _object)
{
    for (int* i1 = _object.begin(); i1 != _object.end(); i1++)
        stream << *i1 << " ";
    stream << std::endl;
    return stream;
}

//функции члены
//получение размера
template <typename T>
unsigned DequeBasedOnArray<T>::GetSize() const
{
    return size;
}

template<typename T>
bool DequeBasedOnArray<T>::PushFront(const T& _element)
{
    int* arr2 = arr;
    try {
        arr = new int[size + 1];
        arr[0] = _element;
        for (int i = 0; i < size; i++)
            arr[i+1] = arr2[i];
        size++;
        if (size > 1)
            delete[] arr2;
        return true;
    }
    catch (...)
    {
        arr = arr2;
        return false;
    }
}

template<typename T>
bool DequeBasedOnArray<T>::PopFront(T& _element)
{
    if (size == 0)
        return false;
    else {
        int* arr2;
        _element = arr[0];
        arr2 = new int[size - 1];
        size--;
        for (int i = 0; i < size; i++)
            arr2[i] = arr[i + 1];
        if (size > 0)
            delete[] arr;
        arr = arr2;
        return true;
    }
}

template<typename T>
bool DequeBasedOnArray<T>::PushBack(const T& _element)
{
    int* arr2 = arr;
    try {
        arr = new int[size + 1];
        for (int i = 0; i < size; i++)
            arr[i] = arr2[i];
        arr[size] = _element;
        size++;
        if (size > 1)
            delete[] arr2;
        return true;
    }
    catch (...)
    {
        arr = arr2;
        return false;
    }
}

template<typename T>
bool DequeBasedOnArray<T>::PopBack(T& _element)
{
    if (size == 0)
        return false;
    else {
        int* arr2;
        _element = arr[size - 1];
        arr2 = new int[size - 1];
        size--;
        for (int i = 0; i < size; i++)
            arr2[i] = arr[i];
        if (size > 0)
            delete[] arr;
        arr = arr2;
        return true;
    }
}

template<typename T>
bool DequeBasedOnArray<T>::PeekFront(T& _element) const
{
    if (size > 0)
    {
        _element = arr[0];
        return true;
    }
    else
        return false;
}

template<typename T>
bool DequeBasedOnArray<T>::PeekBack(T& _element) const
{
    if (size > 0)
    {
        _element = arr[size - 1];
        return true;
    }
    else
        return false;
}

int main()
{
    bool flag = true;
    std::cout << "!start!" << std::endl;
    std::cout << "---------" << std::endl;
    int peekElement = 0;
    int popElement = 0;

    //тестирование конструкторов
    DequeBasedOnArray<int> default_deque;// Конструктор по умолчанию
    DequeBasedOnArray<int> convering_deque(3);// Явный конструктор преобразования
    DequeBasedOnArray<int> initialization_deque = { 1, 2, 3, 4, 5 };// Конструктор с использованием списка инициализации
    DequeBasedOnArray<int> copy_deque{ initialization_deque };// Конструктор кпирования
    DequeBasedOnArray<int> temp_deque{ initialization_deque };// Конструктор кпирования
    DequeBasedOnArray<int> move_deque{ std::move(temp_deque) };//конструктор переноса

    //провера вывода GetSize()
    std::cout << "Size of default_deque default constructor: " << default_deque.GetSize() << std::endl;
    std::cout << "Size of convering_deque converting constructor: " << convering_deque.GetSize() << std::endl;
    std::cout << "Size of initialization_deque initialization_list: " << initialization_deque.GetSize() << std::endl;
    std::cout << "Size of copy_deque copy constructor: " << copy_deque.GetSize() << std::endl;
    std::cout << "Size of move_deque move constructor: " << move_deque.GetSize() << std::endl << std::endl;
    
    //проверка вывода с использованием итераторов через переруженный оператор потокового вывода 
    std::cout << "Elements of initialization list: " << initialization_deque << std::endl;

    //тестирование заполнения масива
    default_deque = { 1,2,3,4 };
    convering_deque = { 2,3,4 };

    //вывод элементов заполненых массивов 
    std::cout << "filled new elements of default_deque: ";
    std::cout << default_deque;
    std::cout << "filled new elements of convering_deque: ";
    std::cout << convering_deque << std::endl;

    //проверка перегруженных операторов Pop, Push, Peek
    //-------------------------------------------------------------
    std::cout << "PushFront >> PeekFront >> PopBack:" << std::endl;
    std::cout << "All elements of default_deque before PushFront: ";
    std::cout << default_deque;
    default_deque.PushFront(10);
    std::cout << "All elements of default_deque after PushFront: ";
    std::cout << default_deque;
    std::cout << "Peeked Front element of default_deque: ";
    default_deque.PeekFront(peekElement);
    std::cout << peekElement << std::endl;
    default_deque.PopBack(popElement);
    std::cout << "Popped back element of default_deque: ";
    std::cout << popElement << std::endl;
    std::cout << "All elements of default_deque after PopBack: ";
    std::cout << default_deque << std::endl;

    std::cout << "PushBack >> PeekBack >> PopFront:" << std::endl;
    std::cout << "All elements of convering_deque before PushBack: ";
    std::cout << convering_deque;
    convering_deque.PushBack(300);
    std::cout << "All elements of convering_deque after PushBack: ";
    std::cout << convering_deque;
    std::cout << "Peeked Back element of convering_deque: ";
    convering_deque.PeekBack(peekElement);
    std::cout << peekElement << std::endl;
    convering_deque.PopFront(popElement);
    std::cout << "Popped front element of convering_deque: ";
    std::cout << popElement << std::endl;
    std::cout << "All elements of convering_deque after PopFront: ";
    std::cout << convering_deque;
    //---------------------------------------------------------
    std::cout << "---------" << std::endl;
    std::cout << "!end!" << std::endl;
    return 0;
}