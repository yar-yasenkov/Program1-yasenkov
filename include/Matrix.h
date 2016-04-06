#include <iostream>
#include <fstream>


using namespace std;


template <typename T>
class Matrix
{
private:
	T **m;
	int columns, rows;
	friend void input (Matrix& object)
	{
		for (int i = 0; i < object.rows; i++)
		{
			for (int j = 0; j < object.columns; j++)
			{
				cin >> object.m[i][j];
			}
		}
	}
	friend void output(Matrix& object)
	{
		for (int i = 0; i < object.rows; i++)
		{
			for (int j = 0; j < object.columns; j++)
			{
				cout << object.m[i][j] << " ";
			}
			cout << endl;
		}
	}
public:
	Matrix() :rows(0), columns(0), m(nullptr)
	{}
	Matrix(int kolstr, int kolstl):
		columns(kolstl), rows(kolstr)
	{
		try
		{
			if ((kolstr < 0) || (kolstl < 0))
			{
				throw "Размерность матрицы не может быть отрицательной!";
			}
			m = new T *[rows];
			for (int i = 0; i<rows; i++)
			{
				m[i] = new T[columns];
				for (int j = 0; j < columns; j++)
				{
					m[i][j] = 0;
				}

			}
		}
		catch (char *str)
			{
			cout << str << endl;
			}
		}

	Matrix(int _rows, int _columns, int time);
	void Zapoln(char path[256])
	{
		char fulpath[256] = "D:\\labiu8\\2 сем\\lab3\\Debug\\";
		int a;
		fstream fin;
		strcat_s(fulpath, path);
		fin.open(fulpath, ios::in);//открытие файла
		if (fin.is_open())
		{
			for (int j = 0; j<rows; j++)
			{
				for (int i = 0; i < columns; i++)
				{
					fin >> a;
					m[j][i] = a;
				}

			}
		}
		fin.close();
	}
	void Show(int kolstr, int kolstl) const
	{
		for (int i = 0; i < kolstr; i++)
		{
			cout << endl;
			for (int j = 0; j < kolstl; j++)
			{

				cout << " " << m[i][j];
			}
		}
		cout << endl;
	}
	Matrix(const Matrix &M) :
		columns(M.columns),
		rows(M.rows)
	{
		m = new T*[rows];
	    for (int i = 0; i < rows; i++)
		{
			m[i] = new T[columns];
			for (int j = 0; j < columns; j++)
			{

				m[i][j] = M.m[i][j];
			}
		}
	}



	Matrix & operator=(const Matrix & matrix) {
		if (this != &matrix) { //перегруженный оператор присваивания
			for (int i = 0; i < rows; i++)
				delete[] m[i];
			delete[] m;
			columns = matrix.columns;
			rows = matrix.rows;
			m = new T *[rows];
			for (int j = 0; j<rows; j++)
			{
				m[j] = new T[columns];
				for (int i = 0; i < columns; i++)
				{
					m[j][i] = matrix.m[j][i];
				}

			}
		}
		return *this;
	}







	~Matrix()
	{
		if (m != nullptr)
		{
			for (int i = 0; i < rows; i++)
			{
				delete[] m[i];
			}
			delete[] m;
		}
	}



	Matrix operator+ (const Matrix&) const;
	Matrix operator*(const Matrix&) const;
    T* operator[](int a) const;
	int kolstrok() const;
	int kolstolb() const;
};


//конструктор случайной матрицы
template <typename T>
Matrix<T>::Matrix(int _rows, int _columns, int time)
{
	rows = _rows;
	columns = _columns;
	m = new T *[rows];
	for (int i = 0; i < rows; i++)
	{
		m[i] = new T[columns];
	}
	srand(time);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			m[i][j] = rand() % 10;
		}
	}
	
};

template <typename T>
int Matrix<T>::kolstrok() const
{
	return rows;
}

template <typename T>
int Matrix<T>::kolstolb() const
{
	return columns;
}

template <typename T>
Matrix<T> Matrix<T>::operator+(const Matrix &a) const
{

	Matrix res(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			res.m[i][j] = m[i][j] + a.m[i][j];
		}
	}
	return res;
}


template <typename T>
Matrix<T> Matrix<T>::operator*(const Matrix &a) const
{
	int value=0;
	Matrix res(rows, a.columns);
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < a.columns; col++)
		{
			for (int inner = 0; inner < a.rows; inner++)
			{
				value += m[row][inner] * a.m[inner][col];
			}
			res.m[row][col] = value;
			value = 0;
		}
	}

	return res;
}


template <typename T>
T* Matrix<T>::operator[](int a) const
{
	T *newrow;
	newrow = new T[columns];
	for (int i = 0; i < columns; i++)
	{
		newrow[i] = m[a][i];
	}
	
	return newrow;
}


//template <typename T>
/*void input(Matrix& object)
{
	for (int i = 0; i < object.rows; i++)
	{
		for (int j = 0; j < object.columns; j++)
		{
			cin >> object.m[i][j];
		}
	}
}

template <typename T>
void output(Matrix<T>& object)
{
	for (int i = 0; i < object.rows; i++)
	{
		for (int j = 0; j < object.columns; j++)
		{
			cout << object.m[i][j] << " ";
		}
		cout << endl;
	}
}*/