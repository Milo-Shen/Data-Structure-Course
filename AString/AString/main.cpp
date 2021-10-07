//
//  main.cpp
//  AString
//
//  Created by Sllimen on 2021/10/6.
//

#include <string.h>

#include <iostream>
using namespace std;

const int defaultSize = 128;

class AString {
private:
    char* ch;
    int curLength;
    int maxSize;
    
public:
    AString(int size = defaultSize) {
        maxSize = size;
        ch = new char[maxSize + 1];
        if (ch == NULL) {
            cerr << "Allocation Error !" << endl;
            exit(1);
        }
        curLength = 0;
        ch[0] = '\0';
    }
    
    AString(const char* init) {
        int len = (int)strlen(init);
        maxSize = len > maxSize ? len : maxSize;
        ch = new char[maxSize + 1];
        if (ch == NULL) {
            cerr << "Allocation Error !" << endl;
            exit(1);
        }
        curLength = len;
        strcpy(ch, init);
    }
    
    AString(const AString& obj) {
        maxSize = obj.maxSize;
        curLength = obj.curLength;
        ch = new char[maxSize + 1];
        if (ch == NULL) {
            cerr << "Allocation Error !" << endl;
            exit(1);
        }
        strcpy(ch, obj.ch);
        cout << "Copy Constructor has been called !" << endl;
    }
    
    ~AString() {
        delete[] ch;
        ch = NULL;
    }
    
    int Length() { return curLength; }
    
    // Copy Constructor will be called if we return AString&
    // Warning: Reference to stack memory associated with local variable 'temp'
    // returned ( AString& )
    AString operator()(int pos, int len) {
        AString temp;
        if (pos < 0 || len < 0 || pos + len - 1 >= maxSize) {
            temp.curLength = 0;
            temp.ch[0] = '\0';
        } else {
            if (pos + len - 1 >= curLength) len = curLength - pos;
            temp.curLength = len;
            for (int i = 0, j = pos; i < len; i++, j++) {
                temp.ch[i] = ch[j];
            }
            temp.ch[len] = '\0';
        }
        return temp;
    }
    
    int operator==(const AString& obj) const { return strcmp(ch, obj.ch) == 0; }
    
    int operator!=(const AString& obj) const { return strcmp(ch, obj.ch) != 0; }
    
    int operator!() const { return curLength == 0; }
    
    // To avoid: error for object 0x100766ab0: pointer being freed was not
    // allocated If & is missing: Copy Constructor has been called !
    AString& operator=(const AString& obj) {
        if (&obj != this) {
            if (ch != NULL) delete[] ch;
            ch = new char[obj.maxSize];
            if (ch == NULL) {
                cerr << "Allocation Error !" << endl;
                exit(1);
            }
            curLength = obj.curLength;
            strcpy(ch, obj.ch);
        } else
            cerr << "Error assigning the string itself !" << endl;
        cout << "overload operator = has been called !" << endl;
        return *this;
    }
    
    // If & is missing: Copy Constructor has been called !
    AString& operator+=(const AString& obj) {
        char* temp = ch;
        int curLen = curLength + obj.curLength;
        int finalLen = curLen >= maxSize ? curLen : maxSize;
        ch = new char[finalLen];
        if (ch == NULL) {
            cerr << "Allocation Error !" << endl;
            exit(1);
        }
        maxSize = finalLen;
        curLength = curLen;
        strcpy(ch, temp);
        strcat(ch, obj.ch);
        delete[] temp;
        temp = NULL;
        cout << "overload operator += has been called !" << endl;
        return *this;
    }
    
    char* getCH() { return ch; }
    
    char& operator[](int i) {
        if (i <= 0 || i > curLength) {
            cout << "out of boundary !" << endl;
        }
        return ch[i];
    }
    
    friend ostream& operator<<(ostream& out, AString& M) {
        out << M.ch;
        return out;
    }
};

int main(int argc, const char* argv[]) {
    cout << "Hello World" << endl;
    AString a("I am Hubery");
    // Test operator: ()
    AString b = a(5, 6);
    AString empty;
    // Test operator: ==
    cout << (a == b ? "true" : "false") << endl;
    // Test operator: !=
    cout << (a != b ? "true" : "false") << endl;
    // Test operator: !
    cout << (!empty ? "true" : "false") << endl;
    // Test operator: =
    AString c;
    c = a;
    cout << static_cast<void*>(&a.getCH()[0]) << endl;
    cout << static_cast<void*>(&c.getCH()[0]) << endl;
    // Test: Copy Constructor
    AString d = c;
    cout << d << endl;
    cout << static_cast<void*>(&c.getCH()[0]) << endl;
    cout << static_cast<void*>(&d.getCH()[0]) << endl;
    // Test operator: +=
    AString e("I Like: ");
    // Const variable can only call const functions
    const AString f("C++");
    e += f;
    cout << e << endl;
    // Test operator: []
    cout << e[2] << endl;
    return 0;
}
