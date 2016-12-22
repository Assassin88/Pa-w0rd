// count в классе General надо допилить, а так всё гуд!!!
#include <iostream>
using namespace std;

class Resource
{
private:
	int n;
public:
	Resource()
		:n{ 0 }
	{}
	Resource(int n_)
		:n(n_)
	{}
	~Resource() = default;
	int& getN()
	{
		return n;
	}
};

//==================================================================================
template<typename T>
class Egoist
{
private:
	int value = 0;
	T* ptr = nullptr;
public:
	Egoist() = default;

	Egoist(int value_)
		: value(value_), ptr{ new T{ value_ } }
	{}

	Egoist(const Egoist& a) = delete;

	Egoist& operator=(const Egoist& a) = delete;

	int& getSize()
	{
		return value;
	}

	~Egoist()
	{
		delete ptr;
		ptr = nullptr;
	}

	template<typename T>
	friend ostream& operator<<(ostream& os, const Egoist<T>& a);
};

template<typename T>
ostream& operator<<(ostream& os, const Egoist<T>& a)
{
	if (a.ptr == nullptr)
	{
		os << "object does not contain rights!!!\n";
	}
	else
	{
		os << "value = " << a.value << "; ptr(Resourse) = " << a.ptr->getN() << endl;
	}
	return os;
}

//==================================================================================
template<typename T>
class General
{
private:
	int value = 0;
	int count = 0;
	T* ptr = nullptr;
public:
	General() = default;

	General(int value_) 
		: value{ value_ }, ptr{ new T(value_) }, count{ (1) }
	{}

	General(const General& a) 
		: value{ a.value }, ptr{ a.ptr }, count{ 2 }
	{}

	General& operator=(const General& a)
	{
		if (&a != this)
		{
			count = 3;
			value = a.value;
			ptr = a.ptr;
		}
		return *this;
	}

	~General()
	{
		if (count == 1)
		{
			delete ptr;
			ptr = nullptr;
		}
		else
		{
			--count;
		}
	}

	int& getSize()
	{
		return value;
	}

	template<typename T>
	friend ostream& operator<<(ostream& os, const General<T>& a);
};

template<typename T>
ostream& operator<<(ostream& os, const General<T>& a)
{
	if (a.ptr == nullptr)
	{
		os << "object does not contain rights!!!\n";
	}
	else
	{
		os << "count = " << a.count << "; value = " << a.value <<
			"; ptr(Resource) = " << a.ptr->getN() << endl;
	}
	return os;
}

//==================================================================================
template<typename T>
class Assignment
{
private:
	int value = 0;
	T* ptr = nullptr;
public:
	Assignment() = default;

	Assignment(int value_)
		: value(value_), ptr{ new T{ value_ } }
	{}

	Assignment(Assignment& a)
		: value(a.value)
	{
		a.value = 0;
		ptr = a.ptr;
		a.ptr = nullptr;
	}

	Assignment& operator=(Assignment& a)
	{
		if (this != &a)
		{
			value = a.value;
			a.value = 0;
			ptr = a.ptr;
			a.ptr = nullptr;
		}
		return *this;
	}

	~Assignment()
	{
		delete ptr;
		ptr = nullptr;
	}

	int& getSize()
	{
		return value;
	}

	template<typename T>
	friend ostream& operator<<(ostream& os, const Assignment<T>& a);
};

template<typename T>
ostream& operator<<(ostream& os, const Assignment<T>& a)
{
	if (a.ptr == nullptr)
	{
		os << "object does not contain rights!!!\n";
	}
	else
	{
		os << "value = " << a.value << "; ptr(Resource) = " << a.ptr->getN() << endl;
	}
	return os;
}

void list()
{
	cout << "--------------------\n";
	cout << "1. class Egoist;" << endl;
	cout << "2. class General;" << endl;
	cout << "3. class Assignment;" << endl;
	cout << "0. Close;" << endl;
}

void main()
{
	int menu; bool menu_ = true;
	cout << "                            <= RAII =>\n\n";

	while (menu_)
	{
		list();
		cout << "--------------------\n";
		cout << "Enter point_menu: ";
		cin >> menu;
		cout << "--------------------\n";
		switch (menu)
		{
		case 1:
		{
			cout << "\nEnter parametr object(int): ";
			int n; cin >> n;
			cout << "\nEgoist<Resource> ob1(" << n << ");\n";
			Egoist<Resource> ob1(n);
			cout << "ob1: "; cout << ob1;
			//Egoist<Resource> ob2(ob);
			cout << "\nEgoist<Resource> ob2(ob1); - Error(deleted function)!!!\n";
			//Egoist<Resource> ob3 = ob;
			cout << "\nEgoist<Resource> ob3; ob3 = ob1; - Error(deleted function)!!!\n";
			cout << "\n\n";
			break;
		}
		case 2:
		{
			cout << "\nEnter parametr object(int): ";
			int n; cin >> n;
			cout << "\nGeneral<Resource> ob1(" << n << ");\n";
			General<Resource> ob1(n);
			cout << "ob1: "; cout << ob1;
			General<Resource> ob2(ob1);
			cout << "\nGeneral<Resource> ob2(ob1);\n";
			cout << "ob2: "; cout << ob2;
			General<Resource> ob3;
			ob3 = ob1;
			cout << "\nGeneral<Resource> ob3; ob3 = ob1;\n";
			cout << "ob3: "; cout << ob3;
			cout << "\n\n";
			break;
		}
		case 3:
		{
			cout << "\nEnter parametr object(int): ";
			int n; cin >> n;
			cout << "\nAssignment<Resource> ob1(" << n << ");\n";
			Assignment<Resource> ob1(n);
			cout << "ob1: "; cout << ob1;
			cout << "------------------------------------\n";
			Assignment<Resource> ob2(ob1);
			cout << "\nAssignment<Resource> ob2(ob1);\n";
			cout << "ob2: "; cout << ob2;
			cout << "\nAssignment<Resource> ob1;\n";
			cout << "ob1: "; cout << ob1;
			cout << "------------------------------------\n";
			Assignment<Resource> ob3 = ob2;
			cout << "\nAssignment<Resource> ob3 = ob2;\n";
			cout << "ob3: "; cout << ob3;
			cout << "\nAssignment<Resource> ob2;\n";
			cout << "ob2: "; cout << ob2;
			cout << "------------------------------------\n";
			cout << "\n\n";
			break;
			cout << "\n\n";
			break;
		}
		case 0: menu_ = false; break;
		default: menu_ = false; break;
		}
	}
}
