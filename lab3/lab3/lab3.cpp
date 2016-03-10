// lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>

using namespace std;



class Matrix
{
  public:
	int **m;
	int nstl, nstr;
	
	Matrix()
	{
		nstl = 2;
		nstr = 2;
		m = new int *[nstr];
		for (int j = 0; j<nstr; j++)
		{
			m[j] = new int[nstl];
			for (int i = 0; i<nstl; i++)
				m[j][i] = 0;
		}
	}
	Matrix(int kolstr, int kolstl)
	{
		int ch;
		nstl = kolstl;
		nstr = kolstr;
		m = new int *[nstr];
		for (int j = 0; j<nstr; j++)
		{
			m[j] = new int[nstl];
			for (int i = 0; i < nstl; i++)
			{
				//cin >> ch;
				m[j][i] = 0;
			}
			
		}

	}

	void Zapoln(char path[256])
	{
		char fulpath[256]="D:\\labiu8\\2 сем\\lab3\\Debug\\";
		int a,k,i,j;
		k = 1;
		fstream fin;
		strcat_s(fulpath, path);
		fin.open(fulpath, ios::in);//открытие файла
		if (fin)
		{
			for (int j = 0; j<nstr; j++)
			{
				//m[j] = new int[nstl];
				for (int i = 0; i < nstl; i++)
				{
					fin >> a;
					m[j][i] = a;
				}

			}
		}
		fin.close();
	}
	void Pokaz(int kolstr, int kolstl)
	{
		for (int i = 0; i < kolstr; i++)
		{
			cout << endl;
			for (int j = 0; j < kolstl; j++)
				cout << " " << m[i][j];
		}
		cout << endl;
	}
	Matrix(const Matrix &M)
	{
		nstl = M.nstl;
		nstr = M.nstr;
		m = new int*[nstr];
		for (int i = 0; i < nstr; i++)
			m[i] = new int[nstl];
		for (int i = 0; i < nstr; i++){
			for (int j = 0; j < nstl; j++)
				m[i][j] = M.m[i][j];
		}
	}
	
	
	
	Matrix & operator=(const Matrix & matrix) {
		if (this != &matrix) { //перегруженный оператор присваивания
			for (int i = 0; i < nstr;i++)
			 delete[] m[i];
			delete[] m;
			nstl = matrix.nstl;
			nstr = matrix.nstr;
			m = new int *[nstr];
			for (int j = 0; j<nstr; j++)
			{
				m[j] = new int[nstl];
				for (int i = 0; i < nstl; i++)
				{
					m[j][i] = matrix.m[j][i];
				}

			}
		}
		else {
			//самоприсваивание
		}
		return *this;
	}
	
	
	
	
	
	
	
	~Matrix()
	{
		if (m != nullptr)
		{
			for (int i = 0; i < nstr; i++)
			{
				delete[] m[i];
			}
			delete[] m;
		}
	}
     


	Matrix operator+ (const Matrix&);
	Matrix operator*(const Matrix&);
	Matrix operator[](int a);
	int kolstrok();
	int kolstolb();
};

int Matrix::kolstrok()
{
	return nstr;
}


int Matrix::kolstolb()
{
	return nstl;
}

Matrix Matrix::operator+(const Matrix &a)
{
	
	Matrix res(nstr, nstl);
	for (int i = 0; i < nstr; i++)
	for (int j = 0; j<nstl; j++)

		res.m[i][j] =m[i][j]+ a.m[i][j];
	return res;
}

Matrix Matrix::operator*(const Matrix &a)
{
	Matrix res(nstr, a.nstl);
	for (int row = 0; row < nstr; row++)
	for (int col = 0; col < a.nstl; col++)
	{
		for (int inner = 0; inner < a.nstr; inner++)
		{
			res.m[row][col] += m[row][inner] * a.m[inner][col];
			//cout << " " << m[row][inner] << "*" << a.m[inner][col]<<"+";
		}
		cout << endl;
	}
	return res;
}

Matrix Matrix::operator[](int a)
{
	Matrix res(1, nstl);
	for (int i = 0; i < nstl; i++)
	{
		res.m[0][i] = m[a][i];
	}
	return res;
}


int _tmain(int argc, _TCHAR* argv[])
{
	int kolstr, kolstl,kolstr3,kolstl3;
	char sogl[2],path[256];
	cout << "enter 'y' to create matrix automatically or 'n' to create manually" << endl;
	cin >> sogl;
	if (strcmp("n", sogl) == 0)
	{
	cout << "enter number of lines" << endl;
	cin >> kolstr;
	cout << "enter number of columns" << endl;
	cin >> kolstl;
	Matrix mat(kolstr,kolstl);
	cout << "enter path to the source of numbers" << endl;
	_flushall();
	cin.getline(path, 255);
	mat.Zapoln(path);
	mat.Pokaz(kolstr,kolstl);
	cout << "enter 'p' to add new matrix to current" << endl;
		cin >> sogl;
		if (strcmp("p", sogl) == 0)
		{
			cout << "add new matrix" << endl;
			Matrix mat2(kolstr, kolstl);
			Matrix res(kolstr, kolstl);
			for (int i = 0; i < kolstr; i++)
			for (int j = 0; j < kolstl; j++)
				cin >> mat2.m[i][j];
			res = mat2 + mat;
			cout << "result";
			res.Pokaz(kolstr, kolstl);
		}
		cout << "enter 'u' to multiply new matrix to current" << endl;
		cin >> sogl;
		if (strcmp("u", sogl) == 0)
		{
			cout << "add new matrix" << endl;
			cout << "enter number of lines" << endl;
			cin >> kolstr3;
			cout << "enter number of columns" << endl;
			cin >> kolstl3;
			Matrix mat3(kolstr3, kolstl3);
			if (kolstr3 == kolstl)
			{
				Matrix res3(kolstr, kolstl3);
				for (int i = 0; i < kolstr3; i++)
				for (int j = 0; j < kolstl3; j++)
					cin >> mat3.m[i][j];
				res3 = mat * mat3;
				cout << "result";
				res3.Pokaz(kolstr, kolstl3);
			}
		}
		cout << "enter number to take a raw from the matrix" << endl;
		cin >> sogl;
		int ch = atoi(sogl)-1;
		if ((ch>=0) & (ch < mat.nstr))
		{
			Matrix res4(1, kolstl);
			res4 = mat[ch];
			res4.Pokaz(1,kolstl);
		}
		cout << "enter 'r' to take a number of rows from the matrix" << endl;
		cin >> sogl;
		if (strcmp("r", sogl) == 0)
		{
			int r = mat.kolstrok();
			cout << r << endl;
		}
		cout << "enter 's' to take a number of columns from the matrix" << endl;
		cin >> sogl;
		if (strcmp("s", sogl) == 0)
		{
			int r = mat.kolstolb();
			cout << r << endl;
		}
	}
	system("pause");
	return 0;
}

