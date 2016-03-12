// lab3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Matrix.h"
#include <iostream>
#include <fstream>

using namespace std;






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
	mat.Show(kolstr,kolstl);
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
			res.Show(kolstr, kolstl);
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
				res3.Show(kolstr, kolstl3);
			}
		}
		cout << "enter number to take a raw from the matrix" << endl;
		cin >> sogl;
		int ch = atoi(sogl)-1;
		if ((ch>=0) & (ch < mat.rows))
		{
			int *res4;
			res4 = new int[mat.columns];
			res4 = mat[ch];
			for (int i = 0; i < mat.columns; i++)
				cout << res4[i] << " ";
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

