//
//  main.cpp
//  BinaryTree
//
//  Created by Sllimen on 2021/10/19.
//

#include <iostream>
#include <stack>
using namespace std;

template <class T>
struct BinTreeNode
{
    T data;
    BinTreeNode<T> *leftChild, *rightChild;
    BinTreeNode() : leftChild(NULL), rightChild(NULL) {}
    BinTreeNode(T x, BinTreeNode<T> *l = NULL, BinTreeNode<T> *r = NULL)
    : data(x), leftChild(l), rightChild(r) {}
};

template <class T>
class BinaryTree
{
public:
    BinaryTree() : root(NULL){};
    BinaryTree(T value) : refValue(value), root(NULL) {}
    // todo: compelete this code;
    BinaryTree(BinaryTree<T> &s);
    ~BinaryTree() { destroy(root); }
    void CreateBinTreeFromString(const string &binaryStr)
    {
        stack<BinTreeNode<T> *> s;
        BinTreeNode<T> *p = NULL, *t = NULL;
        unsigned long k = 0, strLen = binaryStr.length();
        for (int i = 0; i < strLen; i++)
        {
            const char ch = binaryStr[i];
            if (ch == refValue)
                continue;
            switch (ch)
            {
                case '(':
                    k = 1;
                    s.push(p);
                    break;
                case ')':
                    s.pop();
                    break;
                case ',':
                    k = 2;
                    break;
                default:
                    p = new BinTreeNode<T>(ch);
                    if (root == NULL)
                        root = p;
                    else if (k == 1)
                    {
                        t            = s.top();
                        t->leftChild = p;
                    }
                    else
                    {
                        t             = s.top();
                        t->rightChild = p;
                    }
                    break;
            }
        }
    }
    void PreOrder(void (*visit)(BinTreeNode<T> *p)) const { PreOrder(root, visit); }
    void InOrder(void (*visit)(BinTreeNode<T> *p)) const { InOrder(root, visit); }
    void PostOrder(void (*visit)(BinTreeNode<T> *p)) const { PostOrder(root, visit); }
    bool isEmpty() { return root == NULL; }
    BinTreeNode<T> *Parent(BinTreeNode<T> *current)
    {
        if (root == NULL || root == current)
        {
            return NULL;
        }
        else
        {
            Parent(root, current);
        }
    }
    BinTreeNode<T> *LeftChild(BinTreeNode<T> *current)
    {
        return (current != NULL) ? current->leftChild : NULL;
    }
    BinTreeNode<T> *RightChild(BinTreeNode<T> *current)
    {
        return (current != NULL) ? current->rightChild : NULL;
    }
    // todo: BinTreeNode<T> * const & subTree
    void Traverse(BinTreeNode<T> *&subTree, ostream &out) const
    {
        if (subTree != NULL)
        {
            out << subTree->data << ' ';
            Traverse(subTree->leftChild, out);
            Traverse(subTree->rightChild, out);
        }
    }
    friend ostream &operator<<(ostream &out, BinaryTree<T> &Tree)
    {
        out << "Antecedent traversal of binary trees \n";
        Tree.Traverse(Tree.root, out);
        out << endl;
        return out;
    }
    
protected:
    T refValue;
    BinTreeNode<T> *root;
    void destroy(BinTreeNode<T> *&subTree)
    {
        if (subTree != NULL)
        {
            destroy(subTree->leftChild);
            destroy(subTree->rightChild);
            delete subTree;
        }
    }
    void PreOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p)) const
    {
        if (subTree == NULL)
        {
            return;
        }
        visit(subTree);
        PreOrder(subTree->leftChild, visit);
        PreOrder(subTree->rightChild, visit);
    }
    void InOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p)) const
    {
        if (subTree == NULL)
        {
            return;
        }
        PreOrder(subTree->leftChild, visit);
        visit(subTree);
        PreOrder(subTree->rightChild, visit);
    }
    
    void PostOrder(BinTreeNode<T> *subTree, void (*visit)(BinTreeNode<T> *p)) const
    {
        if (subTree == NULL)
        {
            return;
        }
        PreOrder(subTree->leftChild, visit);
        PreOrder(subTree->rightChild, visit);
        visit(subTree);
    }
    BinTreeNode<T> *Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *current)
    {
        if (subTree == NULL)
        {
            return NULL;
        }
        if (subTree->leftChild == current || subTree->rightChild == current)
        {
            return subTree;
        }
        BinTreeNode<T> *p;
        if ((p = Parent(subTree->leftChild, current)) != NULL)
        {
            return p;
        }
        else
        {
            return Parent(subTree->rightChild, current);
        }
    }
};

void _visit(BinTreeNode<char> *p)
{
    cout << p->data << " ";
}

int main(int argc, const char *argv[])
{
    cout << "BinaryTree ( recursive implementation ) \n";
    const char endFlag = '#';
    BinaryTree<char> btree(endFlag);
    cout << "Is btree empty: " << (btree.isEmpty() ? "true" : "false") << endl;
    string binTreeStr = "A(B(D,E(G,)),C(,F))#";
    cout << "Start to create a btree: " << binTreeStr << endl;
    btree.CreateBinTreeFromString(binTreeStr);
    cout << "Default PreOrder: " << btree << endl;
    cout << "Visit BinTreeNode by PreOrder: " << endl;
    btree.PreOrder(_visit);
    cout << endl;
    cout << "Visit BinTreeNode by InOrder: " << endl;
    btree.InOrder(_visit);
    cout << endl;
    cout << "Visit BinTreeNode by PostOrder: " << endl;
    btree.PostOrder(_visit);
    cout << endl;
    return 0;
}
