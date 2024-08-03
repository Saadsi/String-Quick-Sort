#include<iostream>
#include <Windows.h>
using namespace std;

// Class to handle string operations
class MyString
{
public:
    int length = 0;   // Length of the string
    char* str;        // Pointer to dynamically allocated array holding the string
    int count = 0;

    // Default constructor
    MyString()
    {
        str = nullptr;
        length = 0;
    }

    // Parameterized constructor, initializes the object with the given string
    MyString(const char* str)
    {
        int length = strlen(str); // Get the number of characters in the string

        // Allocate memory for the dynamic array to store the string (+1 for null-terminator)
        this->str = new char[length + 1];

        // Copy the characters of the string into the class array
        for (int i = 0; i < length; i++)
        {
            this->str[i] = str[i];
        }

        // Null-terminate the string
        this->str[length] = '\0';
    }

    // Destructor, responsible for releasing the resources occupied by the object
    ~MyString()
    {
        delete[] this->str;
    }

    // Copy constructor, creates an exact copy of the object in a different memory area
    MyString(const MyString& other)
    {
        int length = strlen(other.str);
        this->str = new char[length + 1];

        for (int i = 0; i < length; i++)
        {
            this->str[i] = other.str[i];
        }

        this->str[length] = '\0';
    }

    // Overloaded assignment operator, called when assigning one object's value to another
    MyString& operator =(const MyString& other)
    {
        // Ensure we don't leak memory if the object already contained data before assignment
        if (this->str != nullptr)
        {
            delete[] str;
        }

        int length = strlen(other.str);
        this->str = new char[length + 1];

        for (int i = 0; i < length; i++)
        {
            this->str[i] = other.str[i];
        }

        this->str[length] = '\0';

        return *this;
    }

    // Overloaded addition operator, used for string concatenation
    MyString operator+(const MyString& other)
    {
        // Create a new empty object to store the result of concatenation
        MyString newStr;

        // Get the number of characters in both strings for concatenation
        int thisLength = strlen(this->str);
        int otherLength = strlen(other.str);

        newStr.length = thisLength + otherLength;

        // Allocate memory for the new string (+1 for null-terminator)
        newStr.str = new char[thisLength + otherLength + 1];

        // Copy data from both strings into the new string
        int i = 0;
        for (; i < thisLength; i++)
        {
            newStr.str[i] = this->str[i];
        }

        for (int j = 0; j < otherLength; j++, i++)
        {
            newStr.str[i] = other.str[j];
        }

        // Null-terminate the new string
        newStr.str[thisLength + otherLength] = '\0';

        // Return the concatenated result
        return newStr;
    }

    // Print the string
    void Print()
    {
        cout << str;
    }

    // Get the length of the string
    int Length()
    {
        length = strlen(str);
        return length;
    }

    // Overloaded equality operator, checks if two strings are equal
    bool operator ==(const MyString& other)
    {
        if (this->length != other.length)
        {
            return false;
        }

        for (int i = 0; i < this->length; i++)
        {
            if (this->str[i] != other.str[i])
            {
                return false;
            }
        }
        return true;
    }

    // Overloaded inequality operator, checks if two strings are not equal
    bool operator !=(const MyString& other)
    {
        return !(this->operator==(other));
    }

    // Overloaded subscript operator, allows access to character at specified index
    char& operator [](int index)
    {
        return this->str[index];
    }

    // Create a new string by reading input from the user
    MyString CreateWord()
    {
        MyString usr;
        usr.str = new char[32];
        cin >> usr.str;
        return usr;
    }

    // Find a symbol in the string and print its index
    void find_symbol(char inp)
    {
        for (int i = 0; i < strlen(str); i++)
        {
            if (inp == str[i])
            {
                cout << "Character " << inp << " has index " << i << '\n';
            }
        }
    }
};

// Convert a character to uppercase
char to_upper(char ch)
{
    if (ch >= 'a' && ch <= 'z') {
        return ch - 32;
    }
    return ch;
}

// Recursive quicksort function to sort an array of MyString objects
void qsortRecursive(MyString* mas, int size) {
    int i = 0;
    int j = size - 1;

    // Select a pivot element
    MyString mid = mas[size / 2];

    // Partition the array
    do {
        while (strcmp(mas[i].str, mid.str) < 0) {
            i++;
        }
        while (strcmp(mas[j].str, mid.str) > 0) {
            j--;
        }

        if (i <= j) {
            MyString tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);

    // Recursively sort the partitions
    if (j > 0) {
        qsortRecursive(mas, j + 1);
    }
    if (i < size) {
        qsortRecursive(&mas[i], size - i);
    }
}

int main()
{
    // Set console code page to handle Cyrillic characters
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    MyString str1;
    int length = 0;
    cout << "Enter the number of strings: ";
    cin >> length;
    
    // Create an array of MyString objects
    MyString* word_array = new MyString[length];
    for (int i = 0; i < length; i++)
    {
        cout << "String #" << i + 1 << " ";
        word_array[i] = str1.CreateWord();
    }

    // Sort the array of strings
    qsortRecursive(word_array, length);
    cout << "Sorted array: ";
    for (int i = 0; i < length; i++)
    {
        word_array[i].Print();
        cout << " ";
    }

    // Release the memory allocated for the array
    delete[] word_array;

    return 0;
}
