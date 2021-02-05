#include <iostream>
using namespace std;

struct subforwardlist
{
    int data;
    subforwardlist *next;
};

void clear(subforwardlist **sfl)
{
    if (*sfl == nullptr)
        return;
    else
    {
        subforwardlist *tmp = *sfl;
        while ((*sfl)->next)
        {
            while (tmp->next->next)
                tmp = tmp->next;
            delete tmp->next;
            tmp->next = nullptr;
            tmp = *sfl;
        }
        delete *sfl;
        *sfl = nullptr;
    }
}

bool init(subforwardlist **sfl)
{
    *sfl = nullptr;
    return true;

}

bool push_back(subforwardlist **sfl, int d)
{
    if(*sfl == nullptr)
    {
        *sfl = new subforwardlist;
        (*sfl)->data = d;
        (*sfl)->next = nullptr;
        return true;
    }
    else
    {
        subforwardlist *tmp = *sfl;
        while(tmp->next)
            tmp = tmp->next;
        auto newsfl = new subforwardlist;
        newsfl->next = nullptr;
        newsfl->data = d;
        tmp->next = newsfl;
        return true;
    }
}

int pop_back(subforwardlist **sfl)
{
    if(*sfl == nullptr)
        return 0;
    if((*sfl)->next == nullptr)
    {
        int d = (*sfl)->data;
        delete *sfl;
        *sfl = nullptr;
        return d;
    }
    else
    {
        subforwardlist *tmp = *sfl;
        while(tmp->next->next)
            tmp = tmp->next;
        int d = tmp->next->data;
        delete tmp->next;
        tmp->next = nullptr;
        return d;
    }
}

bool push_forward(subforwardlist **sfl, int d)
{
    if(*sfl == nullptr)
    {
        *sfl = new subforwardlist;
        (*sfl)->data = d;
        (*sfl)->next = nullptr;
        return true;
    }
    else
    {
        auto newsfl = new subforwardlist;
        newsfl->data = d;
        newsfl->next = *sfl;
        *sfl = newsfl;
        return true;
    }
}

int pop_forward(subforwardlist **sfl)
{
    if(*sfl == nullptr)
        return 0;
    else
    {
        subforwardlist *tmp;
        tmp = (*sfl)->next;
        int d = (*sfl)->data;
        delete *sfl;
        *sfl = tmp;
        return d;
    }
}

unsigned int size(subforwardlist **sfl)
{
    subforwardlist *tmp = *sfl;
    unsigned int k = 0;
    while(tmp)
    {
        tmp = tmp->next;
        k++;
    }
    return k;
}

bool push_where(subforwardlist **sfl, unsigned int where, int d)
{
    if(where == 0)
    {
        push_forward(sfl, d);
        return true;
    }
    else
    {
        if (*sfl == nullptr)
            return false;
        else
        {
            subforwardlist *tmp = *sfl;
            unsigned int k = size(sfl);
            tmp = *sfl;
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

bool erase_where(subforwardlist **sfl, unsigned int where)
{
    if(*sfl == nullptr)
        return false;
    if(where == 0)
    {
        int f = pop_forward(sfl);
        return true;
    }
    else
    {
        unsigned int k = size(sfl)-1;
        if (k < where)
            return false;
        else
        {
            subforwardlist *tmp = *sfl;
            for (int i = 1; i < where; i++)
                tmp = tmp->next;
            subforwardlist *newsfl = tmp->next->next;
            delete tmp->next;
            tmp->next = newsfl;
            return true;
        }
    }
}

