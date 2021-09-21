//
//  main.cpp
//  SeqList
//
//  Created by Milo-Shen on 2021/9/21.
//

#include <stdlib.h>

#include <iostream>
using namespace std;

/**
 The definition of LinearList ( Abstract Class )
 */
template <class T>
class LinearList {
public:
    LinearList();                                    // constructed function
    ~LinearList();                                   // destructor function
    virtual int Size() const = 0;                    // pure virtual function: get the max size of SeqList
    virtual int Length() const = 0;                  // get the length of the current SeqList
    virtual int Search(T& x) const = 0;
    virtual int Locate(int i) const = 0;
    virtual bool getData(int i, T& x) const = 0;
    virtual void setData(int i, T& x) = 0;
    virtual void Insert(int i, T& x) = 0;
    virtual void Remove(int i, T& x) = 0;
    virtual bool IsEmpty() const = 0;
    virtual bool IsFull() const = 0;
    virtual void Sort() = 0;
    virtual void input() = 0;
    virtual void output() = 0;
    virtual LinearList<T> operator=(LinearList<T>& L) = 0;
};

/**
 The definition of SeqList
 */

const unsigned int defaultSize = 100;

template <class T>
class SeqList : public LinearList<T> {
protected:
    T* data;
    int maxSize;
    int last;
    void reSize(int newSize) {
        if (newSize <= 0) {
            cerr << "Invalid array size" << endl;
            return;
        }
        if (newSize != maxSize) {
            T* newArray = new T[maxSize];
            if (newArray == NULL) {
                cerr << "storage allocation error";
                exit(1);
            }
            int n = last + 1;
            T* srcptr = data;
            T* destptr = newArray;
            while (n--) {
                *destptr++ = *srcptr++;
                delete[] data;
                data = newArray;
                maxSize = newSize;
            }
        }
    }
    
public:
    SeqList(int size = defaultSize) {
        if (size > 0) {
            maxSize = size;
            last = -1;
            data = new T[maxSize];
            if (data == NULL) {
                cerr << "storage allocation error";
                exit(1);
            }
        }
    }
    SeqList(SeqList<T>& L) {
        maxSize = L.Size();
        last = L.Length() - 1;
        T value;
        data = new T[maxSize];
        if (data == NULL) {
            cerr << "storage allocation error";
            exit(1);
        }
        for (int i = 0; i <= last; i++) {
            L.getData(i, value);
            data[i - 1] = value;
        }
    }
    ~SeqList() { delete[] data; }
    int Size() { return maxSize; }
    int Length() { return last + 1; }
    int Search(T& x) {
        for (int i = 0; i <= last; i++) {
            if (data[i] == x) {
                return i;
            }
        }
        return -1;
    }
    int Locate(int i) {
        
    }
    bool getData(int i, T& x) {
        if (i > 0 && i < last + 1) {
            x = data[i - 1];
            return true;
        }
        else return false;
    }
    void setData(int i, T& x) = 0;
    void Insert(int i, T& x) = 0;
    void Remove(int i, T& x) = 0;
    bool IsEmpty() const {
        return last == -1;
    }
    bool IsFull() const {
        return last == maxSize - 1;
    }
    void Sort() = 0;
    void input() = 0;
    void output() = 0;
    LinearList<T> operator=(LinearList<T>& L) = 0;
};

int main(int argc, const char* argv[]) {
    // insert code here...
    cout << "Hello, World!\n";
    return 0;
}
