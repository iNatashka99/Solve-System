#include "Matrix.h"
#include <iostream>
using namespace std;


Matrix::Matrix(int n)
{
	h = 1 / (n - 1);
	size = n;
	a.SetVector(n);
	b.SetVector(n);
	c.SetVector(n);
	for (int i = 0; i < n; i++)
	{
		a.mas[i] = 0;
		b.mas[i] = 0;
		c.mas[i] = 0;
	}
}

void Matrix::SetMatrix(int n)
{
	h = 1 / (n - 1);
	size = n;
	a.SetVector(n);
	b.SetVector(n);
	c.SetVector(n);
	for (int i = 0; i < n; i++)
	{
		a.mas[i] = 0;
		b.mas[i] = 0;
		c.mas[i] = 0;
	}
}

void Matrix::SetMatrix(int start_row, int end_row, Matrix &A)
{
	int n = end_row - start_row;
	h = 1 / (n - 1);
	size = n;
	a.SetVector(n);
	b.SetVector(n);
	c.SetVector(n);
	for (int i = 0; i < n; i++)
	{
		a.mas[i] = A.a.mas[start_row + i];
		b.mas[i] = A.b.mas[start_row + i];
		c.mas[i] = A.c.mas[start_row + i];
	}
}

Matrix::~Matrix()
{
	a.~Vector();
	b.~Vector();
	c.~Vector();
}


void Matrix::out()
{
	cout << "a: ";
	a.out();
	cout << "b: ";
	b.out();
	cout << "c: ";
	c.out();
}