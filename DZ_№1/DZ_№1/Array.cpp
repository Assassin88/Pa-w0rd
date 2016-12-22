#include <iostream>
#include <ctime>
using namespace std;

class Array
{
private:
	float** arr = nullptr;
	int str = 0;
	int col = 0;
public:

	Array(int str_, int col_)
		: arr{ new float*[str] }, str{ str_ }, col{ col_ }
	{
		arr = new float*[str];
		for (int i = 0; i < str; ++i)
		{
			arr[i] = new float[col];
		}
	}

	Array(Array&& arr_)
		:arr{ arr_.arr }, str{ arr_.str }, col{ arr_.col }
	{
		arr_.arr = nullptr;
		arr_.str = 0;
		arr_.col = 0;
	}

	Array(const Array& arr_)
		:str{ arr_.str }, col{ arr_.col }
	{
		arr = new float*[str];
		for (int i = 0; i < str; ++i)
		{
			arr[i] = new float[col];
		}

		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				arr[i][j] = arr_.arr[i][j];
			}
		}
	}

	const Array& operator=(const Array& arr_)
	{
		if (this != &arr_)
		{
			str = arr_.str;
			col = arr_.col;
			delete[] arr;
			arr = new float*[arr_.str];
			for (int i = 0; i < str; ++i)
			{
				arr[i] = new float[arr_.col];
			}

			for (int i = 0; i < str; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					arr[i][j] = arr_.arr[i][j];
				}
			}
		}
		return *this;
	}

	~Array()
	{
		for (int i = 0; i < str; ++i)
		{
			delete arr[i];
		}
		delete[] arr;
		arr = nullptr;
	}

	void init_arr()
	{
		srand(static_cast<unsigned> (time(0)));
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				arr[i][j] = rand() % 25 * 0.3;
				if (arr[i][j] == 0) arr[i][j] = 0.1;
			}
		}
	}

	void init_arr2()
	{
		srand(static_cast<unsigned> (time(0)));
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				arr[i][j] = rand() % 20 * 0.9;
				if (arr[i][j] == 0) arr[i][j] = 0.1;
			}
		}
	}

	void print()
	{
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				cout << arr[i][j] << "\t";
			}
			cout << endl; cout << endl;
		}
	}

	int get_str()	const
	{
		return str;
	}

	float** get_arr() {
		return arr;
	}

	int get_col() const
	{
		return col;
	}

	float& Index(int str_, int col_) const
	{
		if (str_ >= get_str() || col_ >= get_col())
		{
			cout << "Invalid index. Return first element.";
			return arr[0][0];
		}
		return arr[str_][col_];
	}

	const Array& operator+=(const Array& arr_)
	{
		if (str != arr_.str || col != arr_.get_col())
		{
			cout << "Invalid size!!!\n";
		}
		else
		{
			for (int i = 0; i < str; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					arr[i][j] += arr_.arr[i][j];
				}
			}
		}
		return *this;
	}

	Array operator+(const Array& arr_)
	{
		Array ar(str, col);
		if (str == arr_.str && col == arr_.col)
		{
			for (int i = 0; i < str; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					ar.arr[i][j] = arr[i][j] + arr_.arr[i][j];
				}
			}
			return ar;
		}
		else
		{
			cout << "Invalid size!!!\n";
			return *this;
		}
	}

	const Array& operator-=(const Array& arr_)
	{
		if (str != arr_.str || col != arr_.get_col())
		{
			cout << "Invalid size!!!\n";
		}
		else
			for (int i = 0; i < str; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					arr[i][j] -= arr_.arr[i][j];
				}
			}
		return *this;
	}

	Array operator-(const Array& arr_)
	{
		Array ar(str, col);
		if (str == arr_.str && col == arr_.col)
		{
			for (int i = 0; i < str; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					ar.arr[i][j] = arr[i][j] - arr_.arr[i][j];
				}
			}
			return ar;
		}
		else
		{
			cout << "Invalid size!!!\n";
			return *this;
		}
	}

	const Array& operator*=(const Array& arr_)
	{
		if (col != arr_.str)
		{
			cout << "Invalid size!!!\n";
		}
		else
		{
			*this = *this * arr_;
		}
		return *this;
	}

	Array operator*(const Array& arr_)
	{
		Array ar(arr_.col, str);
		ar.init_arr();
		if (str != arr_.col)
		{
			cout << "Ivalid size!!!\n";
		}
		else
		{
			for (int i = 0; i < str; ++i)
			{
				for (int j = 0; j < arr_.col; ++j)
				{
					for (int l = 0; l < col; ++l)
					{
						ar.arr[i][j] = arr[i][l] * arr_.arr[l][j];
					}
				}
			}
			return ar;
		}
		return *this;
	}

	const Array& operator*(float value)
	{
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				arr[i][j] *= value;
			}
		}
		return *this;
	}

	const Array& operator/(float value)
	{
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				arr[i][j] /= value;
			}
		}
		return *this;
	}

	const Array& operator/=(Array& arr_) {
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				arr_.arr[i][j] = arr[i][j];
			}
		}
		arr_.transponier();
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < arr_.col; ++j)
			{
				for (int l = 0; l < col; ++l)
				{
					arr[i][j] = arr[i][l] * arr_.arr[l][j];
				}
			}
		}
		return *this;
	}

	Array& operator/(Array& arr_)
	{
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				arr_.arr[i][j] = arr[i][j];
			}
		}
		arr_.transponier();
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < arr_.col; ++j)
			{
				for (int l = 0; l < col; ++l)
				{
					arr[i][j] = arr[i][l] * arr_.arr[l][j];
				}
			}
		}
		return *this;
	}

	const Array& operator/=(float value)
	{
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				arr[i][j] *= value;
			}
		}
		return *this;
	}


	bool operator == (const Array& arr_)
	{
		if (str != arr_.str && col != arr_.col)
		{
			return false;
		}
		else
		{
			for (int i = 0; i < str; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					if (arr[i][j] != arr_.arr[i][j])
					{
						return false;
					}
				}
			}
		}
		return true;
	}

	bool operator !=(const Array& arr_)
	{
		return !operator == (arr_);
	}


	bool null_arr() const
	{
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (arr[i][j] != 0)
					return false;
			}
		}
		return true;
	}

	bool single_arr() const
	{
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (arr[i][j] != 0 || (arr[i][j] != 1 && i == j))
				{
					return false;
				}
			}
		}
		return true;
	}

	bool square_arr() const
	{
		return str == col;
	}

	bool diagonal_arr()	const
	{
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j) {
				if (j == i)
					continue;
				if (arr[i][j] != 0)
					return false;
			}
			return true;
		}
	}

	bool symmetric_arr() const
	{
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				if (arr[i][j] != arr[j][i])
					return false;
			}
		}
		return true;
	}

	bool upper_tr_arr()
	{
		for (int i = 1; i < str; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (arr[j][i] != 0)
					return false;
			}
		}
		return true;
	}

	bool lower_tr_arr()
	{
		for (int i = 0; i < str - 1; ++i)
		{
			for (int j = i + 1; j < col; ++j)
			{
				if (arr[i][j] != 0)
					return false;
			}
		}
		return true;
	}

	Array exponent(int value)
	{
		Array arr_(str, col);
		arr_ = *this;
		for (int i = 2; i < value; ++i)
		{
			arr_ *= *this;
		}
		return arr_;
	}

	float determinant()
	{
		int str_ = 0; float value = 0;
		if (str > 3) str_ = 3;
		if (str == 1)
		{
			value = arr[0][0];
		}
		else if (str == 2)
		{
			value = arr[0][0] * arr[1][1] -
				arr[1][0] * arr[0][1];
		}
		else if (str == 3 || str_ == 3)
		{
			value = arr[0][0] * arr[1][1] * arr[2][2] +
				arr[0][1] * arr[1][2] * arr[2][0] +
				arr[1][0] * arr[2][1] * arr[0][2] -
				arr[2][0] * arr[1][1] * arr[0][2] -
				arr[1][0] * arr[0][1] * arr[2][2] -
				arr[0][0] * arr[2][1] * arr[1][2];
		}
		return value;
	}

	Array transponier() const
	{
		Array t(col, str);
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				t.arr[j][i] = arr[i][j];
			}
		}
		return t;
	}

	float norm_Str() const
	{
		float n = 0, sum;
		for (int i = 0; i < str; ++i)
		{
			sum = 0;
			for (int j = 0; j < col; ++j)
			{
				sum += abs(arr[i][j]);
			}
			if (i == 0)
			{
				n = sum;
			}
			else if (sum > n)
			{
				n = sum;
			}
		}
		return n;
	}

	float norm_Col() const
	{
		double n = 0, sum;
		for (int i = 0; i < str; ++i)
		{
			sum = 0;
			for (int j = 0; j < col; ++j)
			{
				sum += arr[j][i];
			}
			if (i == 0)
			{
				n = sum;
			}
			else if (sum > n)
			{
				n = sum;
			}
		}
		return n;
	}

	float norm_E() const
	{
		float s = 0;
		for (int i = 0; i < str; ++i)
		{
			for (int j = 0; j < col; ++j)
			{
				s += pow(arr[i][j], 2);
			}
		}
		return sqrt(s);
	}

	friend ostream& operator<<(ostream& os, const Array& arr_);
	friend istream& operator >> (istream& is, Array& arr_);
};

ostream& operator<<(ostream& os, const Array& arr_)
{
	for (int i = 0; i < arr_.str; ++i)
	{
		for (int j = 0; j < arr_.col; ++j)
		{
			os << arr_.Index(i, j) << "\t";
		}
		os << endl << endl;
	}
	return os;
}

istream& operator >> (istream& is, Array& arr_)
{
	for (int i = 0; i < arr_.str; ++i)
	{
		for (int j = 0; j < arr_.col; ++j)
		{
			cout << "Array[" << i << "][" << j << "] = ";
			is >> arr_.Index(i, j);
		}
		cout << endl;
	}
	return is;
}

void list()
{
	cout << "--------------------\n";
	cout << "Enter function_case:" << endl;
	cout << "1. + " << endl;
	cout << "2. - " << endl;
	cout << "3. += " << endl;
	cout << "4. -= " << endl;
	cout << "5. * " << endl;
	cout << "6. * (value)" << endl;
	cout << "7. *= " << endl;
	cout << "8. /= " << endl;
	cout << "9. / " << endl;
	cout << "10. / (value) " << endl;
	cout << "11. == " << endl;
	cout << "12. != " << endl;
	cout << "13. Transponier_array " << endl;
	cout << "14. Exponent_array " << endl;
	cout << "15. Determinant " << endl;
	cout << "16. Norms_array " << endl;
	cout << "17. Type_array " << endl;
	cout << "0. Close " << endl;
}


void main()
{
	int menu; bool menu_ = true;
	cout << "                            <- Class Array ->\n\n";
	int str_a, col_a, str_b, col_b;
	cout << "Enter size 1_array: \n";
	cout << "\nstr_a = "; cin >> str_a;
	cout << "str_b = "; cin >> col_a; cout << endl;
	Array A(str_a, col_a);

	cout << "\nEnter size 2_array: ";
	cout << "\nstr_b = "; cin >> str_b;
	cout << "col_b = "; cin >> col_b; cout << endl;
	Array B(str_b, col_b);
	system("cls");

	cout << "Select initialization array:\n";
	cout << "\n1. Random_initialization;\n2. Istream_initialization;\n0. Close;\n";
	int init; cin >> init;
	system("cls");
	if (init == 1)
	{
		A.init_arr();
		B.init_arr2();
	}
	else if (init == 2)
	{
		cout << "Enter element 1_array:\n\n";
		cin >> A;
		cout << endl;
		cout << "Enter element 2_array:\n\n";
		cin >> B;
		cout << endl;
		system("cls");
	}
	else
	{
		cout << "Invalid index!!!\n";
		exit(1);
	}

	cout << "Array A:\n\n" << A;
	cout << endl;
	cout << "\nArray B:\n\n" << B;
	cout << endl;

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
			cout << "\n";
			cout << (A + B);
			cout << "\n\n";
			break;
		}
		case 2:
		{
			cout << "\n";
			cout << (A - B);
			cout << "\n\n";
			break;
		}
		case 3:
		{
			cout << "\n";
			cout << (A += B);
			cout << "\n\n";
			break;
		}
		case 4:
		{
			cout << "\n";
			cout << (A -= B);
			cout << "\n\n";
			break;
		}
		case 5:
		{
			cout << "\n";
			cout << (A * B);
			cout << "\n\n";
			break;
		}
		case 6:
		{
			cout << "\n";
			cout << "Enter Value: ";
			int value_;
			cin >> value_;
			cout << (A*(value_));
			cout << "\n\n";
			break;
		}
		case 7:
		{
			std::cout << "\n";
			cout << (A *= B);
			std::cout << "\n\n";
			break;
		}
		case 8:
		{
			std::cout << "\n";
			cout << (A /= B);
			std::cout << "\n\n";
			break;
		}
		case 9:
		{
			std::cout << "\n";
			cout << (A / B);
			std::cout << "\n\n";
			break;
		}
		case 10:
		{
			cout << "Enter Value: ";
			int value_;
			cin >> value_;
			cout << (A / (value_));
			cout << "\n\n";
			break;
		}
		case 11:
		{
			cout << "\n";
			bool b = (A == B);
			cout << "A == B: ";
			(b == 0) ? cout << "false\n" : cout << "true\n";
			cout << "\n\n";
			break;
		}
		case 12:
		{
			cout << "\n";
			bool b = (A != B);
			cout << "A != B: ";
			(b != 0) ? cout << "true\n" : cout << "false\n";
			cout << "\n\n";
			break;
		}
		case 13:
		{
			std::cout << "\n";
			cout << (A.transponier());
			cout << "\n\n";
			break;
		}
		case 14:
		{
			int value_;
			cout << "Enter value:";
			cin >> value_;
			cout << A.exponent(value_);
			break;
		}
		case 15:
		{
			cout << "\n";
			cout << "determinant " << A.determinant();
			std::cout << "\n\n";
			break;
		}
		case 16:
		{
			cout << "\n";
			{
				cout << "String_norm: " << A.norm_Str() << endl;
			}
			{
				cout << "Column_norm: " << A.norm_Col() << endl;
			}
			{
				cout << "Evklid_norm: " << A.norm_E() << endl;
			}
			cout << "\n\n";
			break;
		}
		case 17:
		{
			cout << "\n";
			bool b;
			{
				cout << "Square: "; b = A.square_arr();
				(b == 0) ? cout << "false\n" : cout << "true\n";
			}
			{
				cout << "Zero: "; b = A.null_arr();
				(b == 0) ? cout << "false\n" : cout << "true\n";
			}
			{
				cout << "Single: "; b = A.single_arr();
				(b == 0) ? cout << "false\n" : cout << "true\n";
			}
			{
				cout << "Diagonal: "; b = A.diagonal_arr();
				(b == 0) ? cout << "false\n" : cout << "true\n";
			}
			{
				cout << "Symetric: "; b = A.symmetric_arr();
				(b == 0) ? cout << "false\n" : cout << "true\n";
			}
			{
				cout << "Upper_triangle: "; b = A.upper_tr_arr();
				(b == 0) ? cout << "false\n" : cout << "true\n";
			}
			{
				cout << "Lower_triangle: "; b = A.lower_tr_arr();
				(b == 0) ? cout << "false\n" : cout << "true\n";
			}
			cout << "\n\n";
			break;
		}
		case 0: menu_ = false; break;
		default: menu_ = false; break;
		}
	}
}