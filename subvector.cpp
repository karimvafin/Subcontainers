#include <iostream>
using namespace std;

struct subvector
{
    int *mas;
    unsigned int top;
    unsigned int capacity;
};

bool init(subvector *qv)
{
    qv->capacity = 0;
    qv->top = 0;
    qv->mas = nullptr;
    return true;
}

bool resize(subvector *qv, unsigned int new_capacity)
{
    if (new_capacity > 0)
    {
        if (new_capacity >= qv->capacity)
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

bool push_back(subvector *qv, int d)
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
