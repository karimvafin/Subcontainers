#include <iostream>
using namespace std;

struct subset_node
{
    int key;
    subset_node *left;
    subset_node *right;
};

struct list
{
    subset_node *tree;
    list *next;
    list *prev;
};

void push_tree (list *l, subset_node *sn)
{
    if (l == nullptr)
    {
        l = new list;
        l->next = nullptr;
        l->prev = nullptr;
        l->tree = sn;
    }
    else
    {
        auto newlist = new list;
        newlist->tree = sn;
        newlist->next = nullptr;
        while (l->next != nullptr)
            l = l->next;
        l->next = newlist;
        newlist->prev = l;
    }
}

subset_node* get_tree (list **l)
{
    if (*l == nullptr)
        return nullptr;
    else
    {
        subset_node *newsub = (*l)->tree;
        *l = (*l)->next;
        delete (*l)->prev;
        if ((*l) != nullptr)
            (*l)->prev = nullptr;
        return newsub;
    }
}

bool init(subset_node **sn)
{
    *sn = nullptr;
    return true;
}

bool insert(subset_node **sn, int k)
{
    if (*sn == nullptr)
    {
        *sn = new subset_node;
        (*sn)->left = nullptr;
        (*sn)->right = nullptr;
        (*sn)->key = k;
        return true;
    }
    else
    {
        auto *newsn = new subset_node;
        newsn->key = k;
        newsn->left = nullptr;
        newsn->right = nullptr;
        subset_node *tmp = *sn;
        while (true)
        {
            if (k == tmp->key)
            {
                delete newsn;
                return false;
            }
            if (k > tmp->key)
            {
                if (tmp->right == nullptr)
                {
                    tmp->right = newsn;
                    return true;
                }
                else
                {
                    tmp = tmp->right;
                    continue;
                }
            }
            if (k < tmp->key)
            {
                if (tmp->left == nullptr)
                {
                    tmp->left = newsn;
                    return true;
                }
                else
                {
                    tmp = tmp->left;
                    continue;
                }
            }
        }
    }
}

bool remove(subset_node **sn, int k)
{
    if (*sn == nullptr)
        return false;
    if ((*sn)->key == k)
    {
        subset_node *tmpR = (*sn)->right;
        subset_node *tmpL = (*sn)->left;
        delete *sn;
        if (tmpR)
        {
            *sn = tmpR;
            while (tmpR->left)
                tmpR = tmpR->left;
            tmpR->left = tmpL;
        }
        else
            *sn = tmpL;
        return true;
    }
    else
    {
        subset_node *tmp = *sn;
        while (true)
        {
            if (k < tmp->key)
            {
                if (tmp->left == nullptr)
                    return false;
                if (tmp->left->key == k)
                {
                    subset_node *tmpR = tmp->left->right;
                    subset_node *tmpL = tmp->left->left;
                    delete tmp->left;
                    if (tmpR != nullptr)
                    {
                        tmp->left = tmpR;
                        while (tmpR->left != nullptr)
                            tmpR = tmpR->left;
                        tmpR->left = tmpL;
                        return true;
                    }
                    else
                    {
                        tmp->left = tmpL;
                        return true;
                    }
                }
                else
                {
                    tmp = tmp->left;
                    continue;
                }
            }
            if (k > tmp->key)
            {
                if (tmp->right == nullptr)
                    return false;
                if (tmp->right->key == k)
                {
                    subset_node *tmpR;
                    subset_node *tmpL;
                    tmpR = tmp->right->right;
                    tmpL = tmp->right->left;
                    delete tmp->right;
                    if (tmpR != nullptr)
                    {
                        tmp->right = tmpR;
                        while (tmpR->left != nullptr)
                            tmpR = tmpR->left;
                        tmpR->left = tmpL;
                        return true;
                    }
                    else
                    {
                        tmp->right = tmpL;
                        return true;
                    }
                }
                else
                {
                    tmp = tmp->right;
                    continue;
                }
            }
        }
    }
}

subset_node* find(subset_node *sn, int k)
{
    if (sn == nullptr)
        return nullptr;
    else
    {
        while (true)
        {
            if (k == sn->key)
                return sn;
            if (k > sn->key)
            {
                sn = sn->right;
                if (sn == nullptr)
                    return nullptr;
                continue;
            }
            if (k < sn->key)
            {
                sn = sn->left;
                if (sn == nullptr)
                    return nullptr;
                continue;
            }
        }
    }
}

unsigned int size(subset_node *sn)
{
    unsigned int k = 0;
    if (sn == nullptr)
        return 0;
    if (sn->left == nullptr && sn->right == nullptr)
        return 1;
    else
    {
        k++;
        k += size(sn->right);
        k += size(sn->left);
        return k;
    }
}

unsigned int height(subset_node *sn)
{
    unsigned int k = 0;
    if (sn == nullptr)
        return k;
    if (sn->left == nullptr && sn->right == nullptr)
        return 1;
    else
    {
        k++;
        unsigned int a1 = height(sn->left);
        unsigned int a2 = height(sn->right);
        if (a1 < a2)
            k += a2;
        else
            k += a1;
        return k;
    }
}

void destructor (subset_node *sn)
{
    if (sn == nullptr)
        return;
    else
    {
        if (sn->left == nullptr && sn->right == nullptr)
        {
            delete sn;
        }
        else
        {
            destructor(sn->left);
            destructor(sn->right);
            delete sn;
            return;
        }
    }
}

void add(subset_node *sn, int *mas, int *i)
{
    if (!sn)
        return;
    add(sn->left, mas, i);
    mas[*i] = sn->key;
    (*i)++;
    add(sn->right, mas, i);
}

int* DFS(subset_node *sn)
{
    int *mas = new int[size(sn)];
    int i = 0;
    add(sn, mas, &i);
    return mas;
}

void processing (subset_node *sn, int *mas, int *k, list *l)
{
    mas[*k] = sn->key;
    (*k)++;
    if (sn->right != nullptr)
        push_tree(l, sn->right);
    if (sn->left != nullptr)
        push_tree(l, sn->left);
}

int* BFS(subset_node *sn)
{
    if (sn == nullptr)
        return nullptr;
    else
    {
        int *mas = new int[size(sn)];
        int k = 0;
        list *l = new list;
        do
        {
            push_tree(l, sn);
            processing(get_tree(&l), mas, &k, l);
            l = l->next;
        }
        while (l != nullptr);
        return mas;
    }
}