#include <iostream>
using namespace std;

// Закомменченные функции и структура данных list относятся к функции BFS, которая в
// настоящий момент времени не рефакторена

class subset_class
{
private:
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
    subset_node* root;
    void destructor(subset_node* sn);
    unsigned int size1(subset_node *sn);
    void add(subset_node *sn, int *mas, int *i);
    unsigned int height1(subset_node* sn);
public:
    subset_class();
    ~subset_class();
    bool insert(int k);
    bool remove(int k);
    bool find(int k);
    unsigned int size();
    unsigned int height();
    void DFS();
};


/*void push_tree (list *l, subset_node *sn)
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
}*/

subset_class::subset_class()
{
    this->root = nullptr;
}

void subset_class::destructor(subset_node* sn)
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

subset_class::~subset_class()
{
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

bool subset_class::insert(int k)
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

bool subset_class::remove(int k)
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

bool subset_class::find(int k)
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

unsigned int subset_class::size1(subset_node *sn)
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

unsigned int subset_class::size()
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

unsigned int subset_class::height1(subset_node *sn)
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

unsigned int subset_class::height()
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

void subset_class::add(subset_node *sn, int *mas, int *i)
{
    if (!sn)
        return;
    add(sn->left, mas, i);
    mas[*i] = sn->key;
    (*i)++;
    add(sn->right, mas, i);
}

void subset_class::DFS()
{
    subset_node* sn = this->root;
    int *mas = new int[this->size()];
    int i = 0;
    add(sn, mas, &i);
    for(int j = 0; j < i; j++)
        cout << mas[j] << " ";
    delete [] mas;
    cout << endl;
}

/*void processing (subset_node *sn, int *mas, int *k, list *l)
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
}*/

int main()
{
    subset_class tree;

    //checking insert

    tree.insert(60);
    tree.insert(90);
    tree.insert(50);
    tree.insert(91);
    tree.insert(6);
    tree.insert(9);
    tree.insert(3);
    tree.insert(2);

    tree.DFS();

    //checking remove

    /*tree.remove(60);
    tree.remove(90);
    tree.remove(1);
    tree.remove(60);
    tree.remove(3);
    tree.remove(60);

    tree.DFS();*/

    //checking find

    cout << tree.find(2) << " ";
    cout << tree.find(7) << " ";
    cout << tree.find(6) << " ";
    cout << tree.find(91) << " ";
    cout << tree.find(49) << endl;

    //checking size && height

    cout << tree.size() << " " << tree.height() << endl;
    tree.insert(5);
    tree.insert(100);
    cout << tree.size() << " " << tree.height() << endl;
    tree.remove(91);
    tree.remove(6);
    cout << tree.size() << " " << tree.height() << endl;

    return 0;
}
