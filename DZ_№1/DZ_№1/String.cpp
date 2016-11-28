#include <iostream>

class String
{
private:
	int size;
	char* str;
public:
	String(const char* st)
		: size{ (int)strlen(st) }, str{ new char[size + 1] }
	{
		strcpy_s(str, size + 2, st);
	}

	~String()
	{
		delete[] str;
	}

	char* getString()
	{
		return str;
	}

	int length()
	{
		return size;
	}

	char* change(const char* s)
	{
		delete[] str;
		size = strlen(s);
		str = new char[size + 1];
		strcpy_s(str, size + 1, s);
		return str;
	}

	char* add(const char* st)
	{
		int Size = strlen(st) + size;
		char* ptr = new char[Size + 1];
		strcpy_s(ptr, Size + 1, str);
		strcat_s(ptr, Size + 1, st);
		delete[] str;
		str = ptr;
		size = Size;
		return str;
	}

	char* symbol(char s, int index)
	{
		if (index < 0 || index > size)
		{
			std::cout << "Invalid index." << std::endl;
			return str;
		}
		++size;
		char* tmp_str = new char[size + 1];
		strncpy_s(tmp_str, size + 1, str, index);
		strcat_s(tmp_str, size + 1, &str[index - 1]);
		tmp_str[index] = s;
		delete[] str;
		str = tmp_str;
		return str;
	}

	void ascii()
	{
		int x;
		for (int i = 0; i < size; ++i)
		{
			std::cout << (x = str[i]) << " ";
			if (i % 10 == 0 && i) std::cout << "\n";
		}
		std::cout << std::endl;
	}

	char* upper_Case()
	{
		for (int i = 0; str; ++i)
		{
			if (str[i] == '\0') break;
			if (islower(str[i]))
			{
				str[i] -= 32;
			}
		}
		return str;
	}

	char* lower_Case()
	{
		for (int i = 0; str; ++i)
		{
			if (str[i] == '\0') break;
			if (isupper(str[i]))
			{
				str[i] += 32;
			}
		}
		return str;
	}




};

void main()
{
	String string("Hello my friend");
	std::cout << string.getString() << std::endl;
	std::cout << string.length() << std::endl;
	std::cout << string.change("Hello my brother") << std::endl;
	std::cout << string.add(" and syster!!!") << std::endl;
	std::cout << string.symbol('!', 28) << std::endl;
	string.ascii();
	std::cout << string.upper_Case() << std::endl;
	std::cout << string.lower_Case() << std::endl;

	system("pause");
}