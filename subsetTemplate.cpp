#include <iostream>
using namespace std;

template<typename T>
class subset_class
{
private:
    struct subset_node
    {
        T key;
        subset_node *left;
        subset_node *right;
    };
    struct list
    {
        subset_node *tree;
        list *next;
        list *prev;
    };
    subset_node* root;
    list* l;
    void destructor(subset_node* sn);
    unsigned int size1(subset_node *sn);
    void add(subset_node *sn, T *mas, int *i);
    unsigned int height1(subset_node* sn);
    void push_tree(subset_node *sn);
    void processing(T* mas);

public:
    subset_class();
    ~subset_class();
    bool insert(T k);
    bool remove(T k);
    bool find(T k);
    unsigned int size();
    unsigned int height();
    void DFS();
    void BFS();
};

template<typename T>
subset_class<T>::subset_class()
{
    this->root = nullptr;
    this->l = nullptr;
}

int main()
{
    subset_class<float> f;
    f.insert(3.45);
    f.insert(3.3);
    f.insert(3.5);
    f.insert(2.45);
    f.insert(1.45);
    f.insert(5.45);

    f.DFS();
    f.BFS();
    cout << f.size() << endl;

    f.remove(3.5);
    f.remove(1.0);

    f.DFS();
    cout << f.size() << endl;

    cout << f.find(1.0) << endl;
    cout << f.find(1.45) << endl;

}

template<typename T>
void subset_class<T>::destructor(subset_node* sn)
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

template<typename T>
subset_class<T>::~subset_class()
{
    delete l;
    if (this->root == nullptr)
        return;
    else
    {
        if (this->root->left == nullptr && this->root->right == nullptr)
        {
            delete this->root;
        }
        else
        {
            this->destructor(this->root->left);
            this->destructor(this->root->right);
            delete this->root;
            return;
        }
    }
}

template<typename T>
bool subset_class<T>::insert(T k)
{
    if (this->root == nullptr)
    {
        this->root = new subset_node;
        this->root->left = nullptr;
        this->root->right = nullptr;
        this->root->key = k;
        return true;
    }
    else
    {
        auto *newsn = new subset_node;
        newsn->key = k;
        newsn->left = nullptr;
        newsn->right = nullptr;
        subset_node *tmp = this->root;
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

template<typename T>
bool subset_class<T>::remove(T k)
{
    if (this->root == nullptr)
        return false;
    if (this->root->key == k)
    {
        subset_node *tmpR = this->root->right;
        subset_node *tmpL = this->root->left;
        delete this->root;
        if (tmpR)
        {
            this->root = tmpR;
            while (tmpR->left)
                tmpR = tmpR->left;
            tmpR->left = tmpL;
        }
        else
            this->root = tmpL;
        return true;
    }
    else
    {
        subset_node *tmp = this->root;
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

template<typename T>
bool subset_class<T>::find(T k)
{
    if (this->root == nullptr)
        return false;
    else
    {
        subset_node* sn = this->root;
        while (true)
        {
            if (k == sn->key)
                return true;
            if (k > sn->key)
            {
                sn = sn->right;
                if (sn == nullptr)
                    return false;
                continue;
            }
            if (k < sn->key)
            {
                sn = sn->left;
                if (sn == nullptr)
                    return false;
                continue;
            }
        }
    }
}

template<typename T>
unsigned int subset_class<T>::size1(subset_node *sn)
{
    unsigned int k = 0;
    if (sn == nullptr)
        return 0;
    if (sn->left == nullptr && sn->right == nullptr)
        return 1;
    else
    {
        k++;
        k += size1(sn->right);
        k += size1(sn->left);
        return k;
    }
}

template<typename T>
unsigned int subset_class<T>::size()
{
    unsigned int k = 0;
    subset_node* sn = this->root;
    if (sn == nullptr)
        return 0;
    if (sn->left == nullptr && sn->right == nullptr)
        return 1;
    else
    {
        k++;
        k += size1(sn->right);
        k += size1(sn->left);
        return k;
    }
}

template<typename T>
unsigned int subset_class<T>::height1(subset_node *sn)
{
    unsigned int k = 0;
    if (sn == nullptr)
        return k;
    if (sn->left == nullptr && sn->right == nullptr)
        return 1;
    else
    {
        k++;
        unsigned int a1 = height1(sn->left);
        unsigned int a2 = height1(sn->right);
        if (a1 < a2)
            k += a2;
        else
            k += a1;
        return k;
    }
}

template<typename T>
unsigned int subset_class<T>::height()
{
    subset_node* sn = this->root;
    unsigned int k = 0;
    if (sn == nullptr)
        return k;
    if (sn->left == nullptr && sn->right == nullptr)
        return 1;
    else
    {
        k++;
        unsigned int a1 = height1(sn->left);
        unsigned int a2 = height1(sn->right);
        if (a1 < a2)
            k += a2;
        else
            k += a1;
        return k;
    }
}

template<typename T>
void subset_class<T>::add(subset_node *sn, T *mas, int *i)
{
    if (!sn)
        return;
    add(sn->left, mas, i);
    mas[*i] = sn->key;
    (*i)++;
    add(sn->right, mas, i);
}

template<typename T>
void subset_class<T>::DFS()
{
    subset_node* sn = this->root;
    T *mas = new T[this->size()];
    int i = 0;
    add(sn, mas, &i);
    for(int j = 0; j < i; j++)
        cout << mas[j] << " ";
    delete [] mas;
    cout << endl;
}

template<typename T>
void subset_class<T>::push_tree (subset_node *sn)
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
        list* newlist = new list;
        list* helplist = l;
        newlist->tree = sn;
        newlist->next = nullptr;
        while (helplist->next != nullptr)
            helplist = helplist->next;
        helplist->next = newlist;
        newlist->prev = helplist;
    }
}

template<typename T>
void subset_class<T>::processing (T* mas)
{
    int k = 0;
    list* helplist;
    while (l != nullptr)
    {
        helplist = l;
        mas[k] =  helplist->tree->key;
        k++;
        if (helplist->tree->left != nullptr)
            this->push_tree(helplist->tree->left);
        if (helplist->tree->right != nullptr)
            this->push_tree(helplist->tree->right);
        l = l->next;
        if (l != nullptr)
            l->prev = nullptr;
        delete helplist;
    }
}

template<typename T>
void subset_class<T>::BFS()
{
    if (root == nullptr)
        return;
    else
    {
        unsigned int size = this->size();
        T *mas = new T[size];
        l = new list;
        l->next = nullptr;
        l->tree = root;
        l->prev = nullptr;
        processing(mas);
        for (int i = 0; i < size; i++)
            cout << mas[i] << " ";
        delete [] mas;
        cout << endl;
    }
}

