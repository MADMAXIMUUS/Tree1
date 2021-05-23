#include <iostream>
#include <ctime>
#define N 27
using namespace std;
struct node
{
    int data = 0;
    node* Left = NULL, * Right = NULL;
};
void show(node*& root, int level) // вывод дерева на экран
{
    if (root)
    {
        show(root->Right, level + 1);
        for (int i = 0; i < level; i++) cout << "      ";
        cout << root->data << endl;
        show(root->Left, level + 1);
    }
}
void Add_Arm(node*& nroot, int data) //заполняем дерово элементами
{
    if (nroot == NULL) //создаем новый элемент, если его не существует
    {
        nroot = new node;
        nroot->data = data;
        nroot->Left = nroot->Right = NULL;
    }
    if (data < nroot->data)  //если меньше текущего значения 
    {
        if (nroot->Left != NULL) Add_Arm(nroot->Left, data);
        else
        {
            nroot->Left = new node;
            nroot->Left->Left = nroot->Left->Right = NULL;
            nroot->Left->data = data;
        }
    }
    if (data > nroot->data) //если больше текущего значения
    {
        if (nroot->Right != NULL) Add_Arm(nroot->Right, data);
        else
        {
            nroot->Right = new node;
            nroot->Right->Left = nroot->Right->Right = NULL;
            nroot->Right->data = data;
        }
    }
}
void postOrderTravers(node* root) // обход дерева
{
    if (root)
    {
        postOrderTravers(root->Left);
        postOrderTravers(root->Right);
        cout << root->data << " ";
    }
}
void Search(int k, node* root) // найти ключ
{
    if (k == root->data)
        cout << "Ключ " << k << " найден" << endl;
    else if (k > root->data&& root->Right != NULL)
        Search(k, root->Right);
    else  if (k < root->data && root->Left != NULL)
        Search(k, root->Left);
    else
        cout << "Ключ не найден" << endl;
}
void Del(int k, node* root) // удаление узла
{
    int fl = 0;
    node* delet;
    if (k == root->data);
    else if (k > root->data&& root->Right != NULL)
    {
        Del(k, root->Right);
        if (root->Right->data == k)
        {
            delet = root->Right;
            if (root->Right->Left != NULL && root->Right->Right == NULL)
            {
                root->Left = root->Right->Left;
                delete delet;
                cout << "Ключ " << k << " удален" << endl;
            }
            else if (root->Right->Right != NULL && root->Right->Left == NULL)
            {
                root->Right = root->Right->Right;
                delete delet;
                cout << "Ключ " << k << " удален" << endl;
            }
            else fl = 1;
        }
    }
    else if (k < root->data && root->Left != NULL)
    {
        Del(k, root->Left);
        if (root->Left->data == k)
        {
            delet = root->Left;
            if (root->Left->Left != NULL && root->Left->Right == NULL)
            {
                root->Left = root->Left->Left;
                delete delet;
                cout << "Ключ " << k << " удален" << endl;
            }
            else if (root->Left->Right != NULL && root->Left->Left == NULL)
            {
                root->Right = root->Left->Right;
                delete delet;
                cout << "Ключ " << k << " удален" << endl;
            }
            else fl = 1;
        }
    }
    if (fl)
    {
        cout << "Ключ не найден или не соответствует критериям удаления узла" << endl;
    }
}
void SearchMin(node* root) // найти минимальное
{
    if (root->Left == NULL)
        cout << "Минимальный элемент дерева: " << root->data << endl;
    else
        SearchMin(root->Left);
}
int main()
{
    int k, n = -1;
    setlocale(LC_ALL, "russian");
    node* Tree = new node;
    srand(time(NULL));
    Tree->data = 50;
    Tree->Left = NULL;
    Tree->Right = NULL;
    int Mas[N] = { 
        30, 10, 33, 5, 11, 31, 40, 
        18, 14, 25, 75, 52, 51, 95, 
        76, 97, 86, 79, 89, 74, 70, 
        73, 69, 60, 64, 62, 67 },
        srand(time(NULL));
    for (int i = 0; i < N; i++)
        Add_Arm(Tree, Mas[i]);
    if (Tree == NULL) {
        cout << "Дерева не существует";
        return 0;
    }
    while (n != 0) {
        cout << "1: Показать дерево;" << endl
            << "2: Найти ключ;" << endl
            << "3: Вставить узел;" << endl
            << "4: Обойти дерево;" << endl
            << "5: Найти минимальный ключ;" << endl
            << "6: Удалить узел с одним дочерним объектом;" << endl
            << "0: Выход;" << endl
            << "Введите номер операции: ";
        cin >> n;
        switch (n)
        {
        case 1:
            cout << endl;
            show(Tree, 0);
            cout << endl;
            break;
        case 2:
            cout << endl;
            cout << "Введите ключ поиска: ";
            cin >> k;
            Search(k, Tree);
            cout << endl;
            break;
        case 3:
            cout << endl;
            cout << "Введите элемент для добавления: ";
            cin >> k;
            cout << endl;
            Add_Arm(Tree, k);
            break;
        case 4:
            cout << endl;
            postOrderTravers(Tree);
            cout << endl << endl;
            break;
        case 5:
            cout << endl;
            SearchMin(Tree);
            cout << endl;
            break;
        case 6:
            cout << endl;
            cout << "Введите ключ удаления: ";
            cin >> k;
            Del(k, Tree);
            cout << endl;
        case 0: break;
        default:
            cout << endl << "Вы ввели неверное значение" << endl << endl; break;
        }
    }
    system("pause");
    return 0;
}