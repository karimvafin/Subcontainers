#include <iostream>
using namespace std;

template<typename T>
class subvector
{
private:
    T *mas;
    unsigned int top;
    unsigned int capacity;

public:
    subvector();

    ~subvector();
    bool resize(unsigned int new_capacity);
    bool push_back(T d);
    void clear();
    bool pop_back();
    void shrink_to_fit();
    void print();
    unsigned int get_top();
    unsigned int get_capacity();
};

int main()
{
    subvector<string> f;
    f.push_back("karim");
    f.push_back("vafin");

    cout << f.pop_back() << endl;
    cout << f.pop_back() << endl;
    cout << "Pop done" << endl;
    //cout << f.pop_back() << endl;
    cout << "Pop done" << endl;

    f.push_back("karim");
    f.push_back("vafin");
    cout << "Push done" << endl;

    //f.clear();

    //cout << f.pop_back() << endl;
    cout << f.get_capacity() << endl;
    f.shrink_to_fit();
    cout << f.get_top() << endl;
    cout << f.get_capacity() << endl;

    f.print();
}

template<typename T>
subvector<T>::subvector()
{
    capacity = 0;
    top = 0;
    mas = nullptr;
}

template<typename T>
subvector<T>::~subvector()
{
    delete [] mas;
}

template<typename T>
unsigned int subvector<T>::get_top()
{
    return top;
}

template<typename T>
unsigned int subvector<T>::get_capacity()
{
    return capacity;
}

template<typename T>
bool subvector<T>::resize(unsigned int new_capacity)
{
    if (new_capacity > 0)
    {
        if (new_capacity >= this->capacity)
        {
            T *a = new T[new_capacity];
            for (int i = 0; i < this->top; i++)
                a[i] = (this->mas)[i];
            delete[] this->mas;
            this->mas = a;
            this->capacity = new_capacity;
            return true;
        }
        return true;
    }
    else
    {
        delete[] this->mas;
        this->mas = nullptr;
        return true;
    }
}

template<typename T>
bool subvector<T>::push_back(T d)
{
    if (this->capacity <= this->top)
        this->resize(this->capacity + 5);
    mas[top] = d;
    top ++;
    return true;
}

template<typename T>
void subvector<T>::clear()
{
    top = 0;
}

template<typename T>
bool subvector<T>::pop_back()
{
    if (top <= 0)
        return false;
    else
    {
        top --;
        return true;
    }
}

template<typename T>
void subvector<T>::shrink_to_fit()
{
    if (this->top == 0)
    {
        delete[] this->mas;
        this->mas = nullptr;
        this->capacity = 0;
        return;
    }
    if (this->top >= this->capacity)
        return;
    else
    {
        T *a = new T[this->top];
        for(int i = 0; i < this->top; i++)
            a[i] = (this->mas)[i];
        delete[] this->mas;
        this->mas = a;
        this->capacity = this->top;
    }
}

template<typename T>
void subvector<T>::print()
{
    for (int i = 0; i < this->top; i++)
        cout << this->mas[i] << " ";
}