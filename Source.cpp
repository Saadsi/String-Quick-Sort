#include<iostream>
#include <Windows.h>
using namespace std;

class MyString
{
public:
	int length = 0;
	char* str;
	int count = 0;
	//����������� ��� ����������
	MyString()
	{
		str = nullptr;
		int length = 0;
	}

	//����������� � �����������, ��� �������� ������� ������ ���������� �������� ������ ������� �� ����� �������
	MyString(const char* str)
	{
		int length = strlen(str);// ������� strlen �������� ���������� �������� � ������ ������� �� ������� � ������

		// �������� ������ ��� ������������� ������� ��� ����� ��������� ���� ������
		// +1 ������ ��� ��� ����� ����� � ������� ��� ������������� 0
		this->str = new char[length + 1];

		// �������� ������� ������ � ������ ������ ������
		for (int i = 0; i < length; i++)
		{
			this->str[i] = str[i];
		}

		//��������� ������ ������������� ����
		this->str[length] = '\0';

	}
	// ����������, �������� �� ������������ �������� ������� ��������, ���������� ��� ����������� ������� ������
	~MyString()
	{
		delete[] this->str;
	}

	// ����������� �����������, ��������� ��� �������� ������ ���� ������� ������ �� � ������ ������� ������
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

	// ������������ �������� ������������, ���������� ����� ���������� ��������� �������� ������ ������� �������
	MyString& operator =(const MyString& other)
	{
		// ����� ������ ������ �� �� ������� ����������� � ������������, �� ����������� ����, ��� ��� ����� ������������
		// �� ������������ �������� ������� ���� �� ����������� � ���� ����� ������ �� ��� �������� ���
		//+ ������������ ��������� ���������� ��������� =
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

	//������������� �������� ��������, � ������� ���������� ������ String ��������� ��� ������������ �����
	MyString operator+(const MyString& other)
	{
		//������ ����� ������ ������ ��� ����� ������� ��������� ������������ ����� � ������� ����� ����������� ������
		// �������������� ��������� +
		MyString newStr;
		// �������� ���������� �������� � ����� ������� ��� ������������

		int thisLength = strlen(this->str);
		int otherLength = strlen(other.str);

		newStr.length = thisLength + otherLength;

		// �������� ����� � ������������ ������ ��� ����� ������
		newStr.str = new char[thisLength + otherLength + 1];

		//�������� ������ �� 2� ��������������� ����� � ����� ������
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

		// ���������� ��������� ������������
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
				cout << "������ " << inp << " ����� ������ " << i;
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
	cout << "������� ���-�� �����: ";
	cin >> length;
	MyString* word_array = new MyString[length];
	for (int i = 0; i < length; i++)
	{
		cout << "������ #" << i + 1 << " ";
		word_array[i] = str1.CreateWord();
	}
	qsortRecursive(word_array, length);
	cout << "��������������� ������: ";
	for (int i = 0; i < length; i++)
	{
		word_array[i].Print();
		cout << " ";
	}
	return 0;
}
