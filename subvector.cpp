#include <iostream>
using namespace std;

class subvector
{
public:
    subvector();
    ~subvector();
    bool resize(unsigned int new_capacity);
    bool push_back(int d);
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
    return true;
}

subvector::~subvector()
{
    delete [] this->mas;
}

bool resize(unsigned int new_capacity)
{
    if (new_capacity > 0)
    {
        if (new_capacity >= this->capacity)
        {
            int *a = new int[new_capacity];
            for (int i = 0; i < qv->top; i++)
                a[i] = (qv->mas)[i];
            delete[] qv->mas;
            qv->mas = a;
            qv->capacity = new_capacity;
            return true;
        }
    }
    else
    {
        delete[] qv->mas;
        init(qv);
        return true;
    }
}

bool push_back(int d)
{
    if (qv->capacity <= qv->top)
        resize(qv, (qv->capacity + 5));
    (qv->mas)[qv->top] = d;
    qv->top ++;
    return true;
}

void clear(subvector *qv)
{
    qv->top = 0;
}

int pop_back(subvector *qv)
{
    if (qv->top <= 0)
        return 0;
    else
    {
        qv->top --;
        return (qv->mas)[qv->top];
    }
}

void shrink_to_fit(subvector *qv)
{
    if (qv->top == 0)
    {
        delete[] qv->mas;
        init(qv);
        return;
    }
    if (qv->top >= qv->capacity)
        return;
    else
    {
        int *a = new int[qv->top];
        for(int i = 0; i < qv->top; i++)
            a[i] = (qv->mas)[i];
        delete[] qv->mas;
        qv->mas = a;
        qv->capacity = qv->top;
    }
}

void destructor(subvector *qv)
{
    delete[] qv->mas;
    init(qv);
}

int main()
{
    b = 10;
}