#include <iostream>
using namespace std;

class subvector
{
public:
    subvector();
    ~subvector();
    bool resize(unsigned int new_capacity);
    bool push_back(int d);
    void clear();
    int pop_back();
    void shrink_to_fit();
    void print();
    unsigned int get_top();
private:
    int *mas;
    unsigned int top;
    unsigned int capacity;
};

subvector::subvector()
{
    this->capacity = 0;
    this->top = 0;
    this->mas = nullptr;
}

subvector::~subvector()
{
    delete [] this->mas;
}

unsigned int subvector::get_top()
{
    return top;
}

bool subvector::resize(unsigned int new_capacity)
{
    if (new_capacity > 0)
    {
        if (new_capacity >= this->capacity)
        {
            int *a = new int[new_capacity];
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

bool subvector::push_back(int d)
{
    if (this->capacity <= this->top)
        this->resize(this->capacity + 5);
    (this->mas)[this->top] = d;
    this->top ++;
    return true;
}

void subvector::clear()
{
    this->top = 0;
}

int subvector::pop_back()
{
    if (this->top <= 0)
        return 0;
    else
    {
        this->top --;
        return (this->mas)[this->top];
    }
}

void subvector::shrink_to_fit()
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
        int *a = new int[this->top];
        for(int i = 0; i < this->top; i++)
            a[i] = (this->mas)[i];
        delete[] this->mas;
        this->mas = a;
        this->capacity = this->top;
    }
}

void subvector::print()
{
    for (int i = 0; i < this->top; i++)
        cout << this->mas[i] << " ";
}