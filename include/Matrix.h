#include "stdafx.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>

using namespace std;






int _tmain(int argc, _TCHAR* argv[])
{
	int kolstr, kolstl, time;
	char sogl[2],path[256];
	cout << "enter 'n' to create manually" << endl;
	cin >> sogl;
	if (strcmp("n", sogl) == 0)
	{
	cout << "enter number of lines" << endl;
	cin >> kolstr;
	cout << "enter number of columns" << endl;
	cin >> kolstl;
	if ((kolstr > 0) && (kolstl > 0))
	{

		Matrix<char> mat(kolstr, kolstl);
		cout << "enter path to the source of numbers" << endl;
		_flushall();
		cin.getline(path, 255);
		mat.Zapoln(path);
		mat.Show(kolstr, kolstl);
		cout << "enter 'p' to add new matrix to current" << endl;
		cin >> sogl;
		if (strcmp("p", sogl) == 0)
		{

			cout << "new matrix" << endl;
			cin >> time;
			Matrix<char> mat2(kolstr, kolstl, time);
			mat2.Show(kolstr, kolstl);
			Matrix<char> res(kolstr, kolstl);
			res = mat2 + mat;
			cout << "result";
			res.Show(kolstr, kolstl);
		}
		cout << "enter 'u' to multiply new matrix to current" << endl;
		cin >> sogl;
		if (strcmp("u", sogl) == 0)
		{
			cout << "enter number to create new values" << endl;
			cin >> time;
			Matrix<char> mat3(kolstr, kolstl, time);
			mat3.Show(kolstr, kolstl);
			Matrix<char> res3(kolstr, kolstl);
			res3 = mat * mat3;
			cout << "result";
			res3.Show(kolstr, kolstl);

		}
		cout << "enter number to take a raw from the matrix" << endl;
		cin >> sogl;
		int ch = atoi(sogl) - 1;
		if (ch >= 0)
		{
			char *res4;
			res4 = mat[ch];
			int r = mat.kolstolb();
			for (int i = 0; i < r; i++)
			{
				cout << res4[i] << " ";
			}
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
	}
	cout << "enter 'i' to create matrix manually by friend fucntion" << endl;
	cin >> sogl;
	if (strcmp("i", sogl) == 0)
	{
		cout << "enter number of lines" << endl;
		cin >> kolstr;
		cout << "enter number of columns" << endl;
		cin >> kolstl;
		Matrix<char> matr(kolstr, kolstl);
		cout << "enter matrix" << endl;
		cin >> matr;
		cout << "enter 'o' to display  matrix  by friend fucntion" << endl;
		cin >> sogl;
		if (strcmp("o", sogl) == 0)
		{
			cout << matr;
		}
	}
	system("pause");
	return 0;
}

