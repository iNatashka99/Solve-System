#include "Vector.h"
#include <iostream>
using namespace std;


Vector::Vector(int n)
{
	size = n;
	mas = new double [n];
	for (int i = 0; i < n; i++)
	{
		mas[i] = 0;
	}
}

void Vector::SetVector(int start_row, int end_row, Vector &b)
{
	int n = end_row - start_row;
	size = n;
	mas = new double[n];
	for (int i = 0; i < n; i++)
	{
		mas[i] = b.mas[start_row + i];;
	}
}

void Vector::SetVector(int n)
{
	size = n;
	mas = new double[n];
	for (int i = 0; i < n; i++)
	{
		mas[i] = 0;
	}
}

Vector::~Vector()
{
	if (mas != NULL)
	{
		delete[] mas;
		mas = NULL;
	}
}

void Vector::out()
{
	for (int i = 0; i < size; i++)
	{
		cout << mas[i] << " ";
	}
	cout << endl;
}