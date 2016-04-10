
#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

template <typename T>
class Matrix
{
private:
	T **m;
	int columns, rows;
	friend istream& operator>>(istream& os, Matrix& object)
	{
		for (int i = 0; i < object.rows; i++)
		{
			for (int j = 0; j < object.columns; j++)
			{
				os >> object.m[i][j];
			}
		}
		return os;
	}
	friend ostream& operator<<(ostream& os, Matrix& object)
	{
		for (int i = 0; i < object.rows; i++)
		{
			for (int j = 0; j < object.columns; j++)
			{
				os << object.m[i][j] << " ";
			}
			os << endl;
		}
		return os;
	}
public:
	bool testmarker;
	class Badindex //класс исключений
	{
	public:
		int badindex;
		Badindex(int i) : badindex(i) {}
		void Report() 
		{
			cout << "This value can not be negative" << badindex << endl;
			testmarker=true;
		}
		void Reportrow() 
		{
			cout << "This row does not exist" << endl;
			testmarker=true;
		}
	};
		
	Matrix() :rows(0), columns(0), m(nullptr)
	{}
	Matrix(int kolstr, int kolstl) :
		columns(kolstl), rows(kolstr) 
	{
	   testmarker=false;	
		try
		{
			if ((kolstr < 0) || (kolstl < 0))
			{
				if (kolstl < 0)
					throw Badindex(kolstl);
				else
					throw Badindex(kolstr);
			}

			m = new T *[rows];
			for (int i = 0; i < rows; i++)
			{
				m[i] = new T[columns];
				for (int j = 0; j < columns; j++)
				{
					m[i][j] = 0;
				}
			}
		}
		catch (Badindex & bi)
		{
			bi.Report();
			m=nullptr;
		}
	}

	Matrix(int _rows, int _columns, int time);
        void Zapoln(string name)
	{
		//char fulpath[256] = "path";
		string full_name;
		full_name = name;
		int  i,a,j;
		fstream fin;
		//strcat_s(fulpath, path);
		fin.open(full_name, ios::in);//îòêðûòèå ôàéëà
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
		else
		 {
		    cout << "Îøèáêà, ïîïðîáóéòå åùå ðàç";
	            exit(100);
	}
		fin.close();
	}
	
	bool Show(int kolstr, int kolstl) const
	{
		bool mark=false;
		try
		{
			if ((kolstr < 0) || (kolstl < 0))
			{
				if (kolstl < 0)
					throw Badindex(kolstl);
				else
					throw Badindex(kolstr);
			}
			for (int i = 0; i < kolstr; i++)
			{
				cout << endl;
				for (int j = 0; j < kolstl; j++)
				{
                                        mark=true;
					cout << " " << m[i][j];
				}
			}
			cout << endl;
		}
		catch (Badindex & bi)
		{ 
			bi.Report();
		}
		
		return mark;
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


        bool operator==(const Matrix &right) const// оператор сравнения
       {
          	if (rows != right.rows || columns != right.columns)
    		return false; // матрицы с разным количеством элементов

	for (int i = 0; i < rows; i++)
		for (int j = 0; j < columns; j++)
			if (m[i][j] != right.m[i][j])
				return false; // матрицы не равны

	return true; // матрицы равны
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
    T* operator[](int a);
	int kolstrok() const;
	int kolstolb() const;
};


//конструктор случайной матрицы
template <typename T>
Matrix<T>::Matrix(int _rows, int _columns, int time)
{
	try
	{
		if ((_rows < 0) || (_columns < 0))
		{
			if (_rows < 0)
				throw Badindex(_rows);
			else
				throw Badindex(_columns);
		}
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
	}
	catch (Badindex & bi)
	{
		bi.Report();
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
T* Matrix<T>::operator[](int a) 
{
	testmarker=false;
	T *newrow;
	newrow = new T[columns];
	try
	{
		if ((a > rows) || (a < 0))
		{
			throw Badindex(a);
		}
		for (int i = 0; i < columns; i++)
		{
			newrow[i] = m[a][i];
		}
	}
	catch (Badindex & bi)
	{
		bi.Reportrow();
	}
	return newrow;
}
