#include <iostream>

using namespace std;

class StringManager {
private:
    char* str;  

public:
    StringManager(const char* initStr = "") {
        int length = 0;
        while (initStr[length] != '\0') {
            length++;
        }
        
        str = new char[length + 1];  
        
       
        for (int i = 0; i < length; i++) {
            str[i] = initStr[i];
        }
        str[length] = '\0';  
    }

    ~StringManager() {
        delete[] str;  
    }

    void concatenate(const char* newStr) {
        int oldLength = 0, newLength = 0;

        
        while (str[oldLength] != '\0') {
            oldLength++;
        }

       
        while (newStr[newLength] != '\0') {
            newLength++;
        }

        
        char* temp = new char[oldLength + newLength + 1];

        
        for (int i = 0; i < oldLength; i++) {
            temp[i] = str[i];
        }

        
        for (int i = 0; i < newLength; i++) {
            temp[oldLength + i] = newStr[i];
        }

        temp[oldLength + newLength] = '\0';   

        delete[] str;  
        str = temp;  
    }

    
    void display() const {
        cout << str << endl;
    }
};

int main() {
    StringManager str1("Hello");
    str1.display();  

    str1.concatenate(", World!");  
    str1.display();  

    StringManager str2("Dynamic String");
    str2.display();  

    str2.concatenate(" Manager!");
    str2.display();  

    return 0;
}
