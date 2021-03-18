#include <iostream>
using namespace std;

template<typename T>
class subclass
{
public:
    subclass();
    ~subclass();
    bool push_back(T d);
    bool pop_back();
    bool push_forward(T d);
    bool pop_forward();
    unsigned int size();
    bool push_where(unsigned int where, T d);
    bool erase_where(unsigned int where);
    void print();
private:
    struct subforwardlist
    {
        T data;
        subforwardlist *next;
    };
    subforwardlist *start;
};

int main()
{
    subclass<string> s1;
    s1.push_back("A");
    s1.push_back("B");
    s1.push_back("C");
    s1.push_back("D");
    s1.print();
    s1.pop_back();
    s1.push_forward("E");
    s1.print();
    s1.pop_forward();
    s1.print();
    cout << endl;
    cout << s1.size() << endl;
    s1.erase_where(0);
    s1.print();
    cout << endl;
    s1.push_where(1, "F");
    s1.print();
}

template<typename T>
subclass<T>::subclass()
{
    this->start = nullptr;
}

template<typename T>
subclass<T>::~subclass()
{
    if (this->start == nullptr)
        return;
    else
    {
        subforwardlist *tmp = this->start;
        while (this->start->next)
        {
            while (tmp->next->next)
                tmp = tmp->next;
            delete tmp->next;
            tmp->next = nullptr;
            tmp = this->start;
        }
        delete this->start;
        this->start = nullptr;
    }
}

template<typename T>
bool subclass<T>::push_back(T d)
{
    if(this->start == nullptr)
    {
        this->start = new subforwardlist;
        this->start->data = d;
        this->start->next = nullptr;
        return true;
    }
    else
    {
        subforwardlist *tmp = this->start;
        while(tmp->next)
            tmp = tmp->next;
        auto newsfl = new subforwardlist;
        newsfl->next = nullptr;
        newsfl->data = d;
        tmp->next = newsfl;
        return true;
    }
}

template<typename T>
bool subclass<T>::pop_back()
{
    if(this->start == nullptr)
        return false;
    if(this->start->next == nullptr)
    {
        delete this->start;
        this->start = nullptr;
        return true;
    }
    else
    {
        subforwardlist *tmp = this->start;
        while(tmp->next->next)
            tmp = tmp->next;
        delete tmp->next;
        tmp->next = nullptr;
        return true;
    }
}

template<typename T>
bool subclass<T>::push_forward(T d)
{
    if(this->start == nullptr)
    {
        this->start = new subforwardlist;
        this->start->data = d;
        this->start->next = nullptr;
        return true;
    }
    else
    {
        auto newsfl = new subforwardlist;
        newsfl->data = d;
        newsfl->next = this->start;
        this->start = newsfl;
        return true;
    }
}

template<typename T>
bool subclass<T>::pop_forward()
{
    if(this->start == nullptr)
        return false;
    else
    {
        subforwardlist *tmp;
        tmp = this->start->next;
        delete this->start;
        this->start = tmp;
        return true;
    }
}

template<typename T>
unsigned int subclass<T>::size()
{
    subforwardlist *tmp = this->start;
    unsigned int k = 0;
    while(tmp)
    {
        tmp = tmp->next;
        k++;
    }
    return k;
}

template<typename T>
bool subclass<T>::push_where(unsigned int where, T d)
{
    if(where == 0)
    {
        this->push_forward(d);
        return true;
    }
    else
    {
        if (this->start == nullptr)
            return false;
        else
        {
            subforwardlist *tmp = this->start;
            unsigned int k = this->size();
            tmp = this->start;
            if (k < where)
                return false;
            if (k >= where)
            {
                for (int i = 1; i < where; i++)
                    tmp = tmp->next;
                auto *newsfl = new subforwardlist;
                newsfl->data = d;
                newsfl->next = tmp->next;
                tmp->next = newsfl;
                return true;
            }
            return true;
        }
    }
}

template<typename T>
bool subclass<T>::erase_where(unsigned int where)
{
    if(this->start == nullptr)
        return false;
    if(where == 0)
    {
        this->pop_forward();
        return true;
    }
    else
    {
        unsigned int k = this->size()-1;
        if (k < where)
            return false;
        else
        {
            subforwardlist *tmp = this->start;
            for (int i = 1; i < where; i++)
                tmp = tmp->next;
            subforwardlist *newsfl = tmp->next->next;
            delete tmp->next;
            tmp->next = newsfl;
            return true;
        }
    }
}

template<typename T>
void subclass<T>::print()
{
    subforwardlist *tmp = this->start;
    while(tmp)
    {
        cout << tmp->data << " ";
        tmp = tmp->next;
    }
    cout << endl;
}
