#include <iostream>
using namespace std;


class subclass
{
public:
    subclass();
    ~subclass();
    bool push_back(int d);
    int pop_back();
    bool push_forward(int d);
    int pop_forward();
    unsigned int size();
    bool push_where(unsigned int where, int d);
    bool erase_where(unsigned int where);
    void print();
private:
    struct subforwardlist
    {
        int data;
        subforwardlist *next;
    };
    subforwardlist *start;
};

subclass::subclass()
{
    this->start = nullptr;
}

subclass::~subclass()
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


bool subclass::push_back(int d)
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

int subclass::pop_back()
{
    if(this->start == nullptr)
        return 0;
    if(this->start->next == nullptr)
    {
        int d = this->start->data;
        delete this->start;
        this->start = nullptr;
        return d;
    }
    else
    {
        subforwardlist *tmp = this->start;
        while(tmp->next->next)
            tmp = tmp->next;
        int d = tmp->next->data;
        delete tmp->next;
        tmp->next = nullptr;
        return d;
    }
}

bool subclass::push_forward(int d)
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

int subclass::pop_forward()
{
    if(this->start == nullptr)
        return 0;
    else
    {
        subforwardlist *tmp;
        tmp = this->start->next;
        int d = this->start->data;
        delete this->start;
        this->start = tmp;
        return d;
    }
}

unsigned int subclass::size()
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

bool subclass::push_where(unsigned int where, int d)
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

bool subclass::erase_where(unsigned int where)
{
    if(this->start == nullptr)
        return false;
    if(where == 0)
    {
        int f = this->pop_forward();
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

void subclass::print()
{
    subforwardlist *tmp = this->start;
    while(tmp)
    {
        cout << tmp->data << " ";
        tmp = tmp->next;
    }
}

int main()
{
    subclass s1;
    s1.push_back(3);
    s1.push_back(4);
    s1.push_back(5);
    s1.push_back(6);
    s1.pop_back();
    s1.push_forward(1);
    s1.pop_forward();
    s1.print();
    cout << endl;
    cout << s1.size() << endl;
    s1.erase_where(0);
    s1.print();
    cout << endl;
    s1.push_where(1, 10);
    s1.print();
}
