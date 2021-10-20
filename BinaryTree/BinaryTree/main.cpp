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
struct BinTreeNode {
    T data;
    BinTreeNode<T> *leftChild, *rightChild;
    BinTreeNode() : leftChild(NULL), rightChild(NULL) {}
    BinTreeNode(T x, BinTreeNode<T> *l = NULL, BinTreeNode<T> *r = NULL)
    : data(x), leftChild(l), rightChild(r) {}
};

template <class T>
class BinaryTree {
public:
    BinaryTree() : root(NULL){};
    BinaryTree(T value) : refValue(value), root(NULL) {}
    BinaryTree(BinaryTree<T> &s);  // todo: compelete this code;
    ~BinaryTree() { destroy(root); }
    bool isEmpty() { return root == NULL; }
    BinTreeNode<T> *Parent(BinTreeNode<T> *current) {
        if (root == NULL || root == current)
            return NULL;
        else
            Parent(root, current);
    }
    BinTreeNode<T> *LeftChild(BinTreeNode<T> *current) {
        return (current != NULL) ? current->leftChild : NULL;
    }
    BinTreeNode<T> *RightChild(BinTreeNode<T> *current) {
        return (current != NULL) ? current->rightChild : NULL;
    }
    BinaryTree<T> Traverse(BinTreeNode<T> *subTree, ostream &out) {
        if (subTree == NULL) return NULL;
        out << subTree->data << ' ';
        Traverse(subTree->leftChild, out);
        Traverse(subTree->rightChild, out);
    }
    friend ostream &operator<<(ostream &out, BinaryTree<T> &Tree) {
        out << "Antecedent traversal of binary trees \n";
        Tree.Traverse(Tree.root, out);
        out << endl;
        return out;
    }
    
protected:
    T refValue;
    BinaryTree<T> *root;
    void CreateBinTree(istream &in, BinTreeNode<T> *&subTree) {
        stack<BinTreeNode<T> *> s;
    }
    void destroy(BinTreeNode<T> *&subTree) {
        if (subTree != NULL) {
            destroy(subTree->leftChild);
            destroy(subTree->rightChild);
            delete subTree;
        }
    }
    BinTreeNode<T> *Parent(BinTreeNode<T> *subTree, BinTreeNode<T> *current) {
        if (subTree == NULL) return NULL;
        if (subTree->leftChild == current || subTree->rightChild == current)
            return subTree;
        BinTreeNode<T> *p;
        if ((p = Parent(subTree->leftChild, current)) != NULL)
            return p;
        else
            return Parent(subTree->rightChild, current);
    }
};

int main(int argc, const char *argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    return 0;
}
