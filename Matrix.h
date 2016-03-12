#include <iostream>
#include <fstream>


using namespace std;

class Matrix
{
public:
	int **m;
	int columns, rows;

	Matrix()
	{
		columns = 2;
		rows = 2;
		m = new int *[rows];
		for (int j = 0; j<rows; j++)
		{
			m[j] = new int[columns];
			for (int i = 0; i<columns; i++)
				m[j][i] = 0;
		}
	}
	Matrix(int kolstr, int kolstl)
	{
		columns = kolstl;
		rows = kolstr;
		m = new int *[rows];
		for (int j = 0; j<rows; j++)
		{
			m[j] = new int[columns];
			for (int i = 0; i < columns; i++)
			{
				m[j][i] = 0;
			}

		}

	}

	void Zapoln(char path[256])
	{
		char fulpath[256] = "D:\\labiu8\\2 сем\\lab3\\Debug\\";
		int a, k, i, j;
		k = 1;
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
	void Show(int kolstr, int kolstl)
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
		//columns = M.columns;
		//rows = M.rows;
		m = new int*[rows];
	    for (int i = 0; i < rows; i++)
		{
			m[i] = new int[columns];
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
			m = new int *[rows];
			for (int j = 0; j<rows; j++)
			{
				m[j] = new int[columns];
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



	Matrix operator+ (const Matrix&);
	Matrix operator*(const Matrix&);
    int* operator[](int a);
	int kolstrok();
	int kolstolb();
};

int Matrix::kolstrok()
{
	return rows;
}


int Matrix::kolstolb()
{
	return columns;
}

Matrix Matrix::operator+(const Matrix &a)
{

	Matrix res(rows, columns);
	for (int i = 0; i < rows; i++)
	for (int j = 0; j<columns; j++)

		res.m[i][j] = m[i][j] + a.m[i][j];
	return res;
}

Matrix Matrix::operator*(const Matrix &a)
{
	Matrix res(rows, a.columns);
	Matrix temp(rows, a.columns);
	for (int row = 0; row < rows; row++)
	for (int col = 0; col < a.columns; col++)
	{
		for (int inner = 0; inner < a.rows; inner++)
		{
			temp.m[row][col] += m[row][inner] * a.m[inner][col];
		}
		cout << endl;
	}
	res = temp;
	return res;
}

int* Matrix::operator[](int a)
{
	int *newrow;
	newrow = new int[columns];
	for (int i = 0; i < columns; i++)
	{
		newrow[i] = m[a][i];
	}
	return newrow;
}