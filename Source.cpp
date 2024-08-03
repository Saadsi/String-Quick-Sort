#include<iostream>
#include <Windows.h>
using namespace std;

class MyString
{
public:
	int length = 0;
	char* str;
	int count = 0;
	//конструктор без параметров
	MyString()
	{
		str = nullptr;
		int length = 0;
	}

	//конструктор с параметрами, при создании объекта класса необходимо перелать строку которую он будет хранить
	MyString(const char* str)
	{
		int length = strlen(str);// функция strlen получает количество символов в строке которую мы передаём в объект

		// выделяем память для динамического массива где будет храниться наша строка
		// +1 символ так как нужно место в массиве под терминирующий 0
		this->str = new char[length + 1];

		// копируем символы строки в массив нашего класса
		for (int i = 0; i < length; i++)
		{
			this->str[i] = str[i];
		}

		//закрываем строку терминирующим нулём
		this->str[length] = '\0';

	}
	// деструктор, отвечает за освобождение ресурвов занятых объектом, вызывается при уничтожении объекта класса
	~MyString()
	{
		delete[] this->str;
	}

	// конструктор копировании, необходим для создании точной копи объекта класса но в другой области памяти
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

	// перегруженый оператор присваивания, вызывается когда необходимо присвоить значение одного объекта другому
	MyString& operator =(const MyString& other)
	{
		// здесь логика похожа на ту которая реализована в конструкторе, за исключением того, что нам нужно позаботиться
		// об освобождении ресурсов объекта если до копирования в него новой строки он уже содержал код
		//+ страндартный синтаксис перегрузки оператора =
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

	//перегруженный оператор сложения, в текущей реализации класса String необходим для конкатенации строк
	MyString operator+(const MyString& other)
	{
		//создаём новый пустой объект где будим хранить результат конкатенации строк и который будет результатом работы
		// перегруженного оператора +
		MyString newStr;
		// получаем количество символов в обеих строках для конкатенации

		int thisLength = strlen(this->str);
		int otherLength = strlen(other.str);

		newStr.length = thisLength + otherLength;

		// выделяем место в динамической памяти под новую строку
		newStr.str = new char[thisLength + otherLength + 1];

		//копируем данные из 2х конкатенируемых строк в новую строку
		int i = 0;
		for (; i < thisLength; i++)
		{
			newStr.str[i] = this->str[i];
		}

		for (int j = 0; j < otherLength; j++, i++)
		{
			newStr.str[i] = other.str[j];
		}

		newStr.str[thisLength + otherLength] = '\0';

		// возвращаем результат конкатенации
		return newStr;
	}

	void Print()
	{
		cout << str;
	}

	int Length()
	{
		length = strlen(str);
		return length;
	}

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

	bool operator !=(const MyString& other)
	{
		return !(this->operator==(other));
	}

	char& operator [](int index)
	{
		return this->str[index];
	}

	MyString CreateWord()
	{
		MyString usr;
		usr.str = new char[32];
		cin >> usr.str;
		return usr;
	}
	void find_symbol(char inp)
	{
		for (int i = 0; i < strlen(str); i++)
		{
			if (inp == str[i])
			{
				cout << "Символ " << inp << " имеет индекс " << i;
				cout << '\n';
			}
		}
	}
};


char to_upper(char ch)
{
	if (ch >= 'a' && ch <= 'z') {
		return ch - 32;
	}
	return ch;
}


void qsortRecursive(MyString* mas, int size) {
	int i = 0;
	int j = size - 1;

	MyString mid = mas[size / 2];

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


	if (j > 0) {
		qsortRecursive(mas, j + 1);
	}
	if (i < size) {
		qsortRecursive(&mas[i], size - i);
	}
}


int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	MyString str1;
	int length = 0;
	cout << "Введите кол-во строк: ";
	cin >> length;
	MyString* word_array = new MyString[length];
	for (int i = 0; i < length; i++)
	{
		cout << "Строка #" << i + 1 << " ";
		word_array[i] = str1.CreateWord();
	}
	qsortRecursive(word_array, length);
	cout << "Отсортированный массив: ";
	for (int i = 0; i < length; i++)
	{
		word_array[i].Print();
		cout << " ";
	}
	return 0;
}
