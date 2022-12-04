#include "Solve.h"
#include <iostream>
using namespace std;


Solve::Solve(int n)
{
	size = n;
	h = 1.0 / (n - 1);
	A.SetMatrix(n);
	f.SetVector(n);
	y.SetVector(n);
	alfa.SetVector(n);
	betta.SetVector(n);
	epsilon.SetVector(n);
	etta.SetVector(n);
	SetParameters();
}

Solve::Solve(int start_row, int end_row, Solve &S)
{
	int n = end_row - start_row;
	size = n;
	h = 1 / (n - 1);
	A.SetMatrix(start_row, end_row, S.A);
	f.SetVector(start_row, end_row, S.f);
	y.SetVector(start_row, end_row, S.y);
	alfa.SetVector(n);
	betta.SetVector(n);
	epsilon.SetVector(n);
	etta.SetVector(n);
}

Solve::~Solve()
{
	A.~Matrix();
	f.~Vector();
	y.~Vector();
	alfa.~Vector();
	betta.~Vector();
	epsilon.~Vector();
	etta.~Vector();
}

double Solve::f_a(int i)
{
	if (i == size - 1)
		return 0;
	else
		return 1 - 3 * h;
}

double Solve::f_b(int i)
{
	if (i == 0)
		return 0;
	else
		return 1 + 3 * h;
}

double Solve::f_c(int i)
{
	if ((i == 0) || (i == size - 1))
		return 1;
	else
		return -2;
}

double Solve::f_f(int i)
{
	if (i == 0)
		return -2;
	else if (i == size - 1)
		return 8;
	else
		return 0;
}

void Solve::SetParameters()
{
	for (int i = 0; i < size; i++)
	{
		A.a.mas[i] = f_a(i);
		A.b.mas[i] = f_b(i);
		A.c.mas[i] = f_c(i);
		f.mas[i] = f_f(i);
	}
}

void Solve::Posled_alg(bool fl)
{
	if (fl)
	{
		Right_alg1();
		double xp = (f.mas[size - 1] - A.a.mas[size - 1] * betta.mas[size - 1]) / (A.a.mas[size - 1] * alfa.mas[size - 1] + A.c.mas[size - 1]);
		Right_alg2(xp);
	}
	else
	{
		Left_alg1();
		double xp = (f.mas[0] - A.b.mas[0] * etta.mas[1]) / (A.b.mas[0] * epsilon.mas[1] + A.c.mas[0]);
		Left_alg2(xp);
	}
}

void Solve::Left_alg1()
{
	epsilon.mas[size - 1] = -A.a.mas[size - 1] / A.c.mas[size - 1];
	etta.mas[size - 1] = f.mas[size - 1] / A.c.mas[size - 1];
	for (int i = size - 2; i >= 1; i--)
	{
		epsilon.mas[i] = -A.a.mas[i] / (A.c.mas[i] + A.b.mas[i] * epsilon.mas[i + 1]);
		etta.mas[i] = (f.mas[i] - A.b.mas[i] * etta.mas[i + 1]) / (A.c.mas[i] + A.b.mas[i] * epsilon.mas[i + 1]);
	}
}

void Solve::Left_alg2(double xp)
{
	y.mas[0] = xp;
	for (int i = 0; i < size - 1; i++)
	{
		y.mas[i + 1] = epsilon.mas[i + 1] * y.mas[i] + etta.mas[i + 1];
	}
}

void Solve::Right_alg1()
{
	alfa.mas[1] = - A.b.mas[0] / A.c.mas[0];
	betta.mas[1] = f.mas[0] / A.c.mas[0];
	for (int i = 1; i < size - 1; i++)
	{
		alfa.mas[i + 1] = - A.b.mas[i] / (A.a.mas[i] * alfa.mas[i] + A.c.mas[i]);
		betta.mas[i + 1] = (f.mas[i] - A.a.mas[i] * betta.mas[i]) / (A.a.mas[i] * alfa.mas[i] + A.c.mas[i]);
	}
}

void Solve::Right_alg2(double xp)
{
	y.mas[size - 1] = xp;
	for (int i = size - 2; i >= 0; i--)
	{
		y.mas[i] = alfa.mas[i + 1] * y.mas[i + 1] + betta.mas[i + 1];
	}
}

double Solve::getYp(double alfa1, double betta1, double epsilon1, double etta1)
{
	double xp1 = (betta1 * epsilon1 + etta1) / (1 - alfa1 * epsilon1);
	double xp = betta1 + alfa1 * xp1;
	return xp;
}

void Solve::CollectHalfs(Vector &H1, Vector &H2)
{
	for (int i = 0; i < H1.size; i++)
	{
		y.mas[i] = H1.mas[i];
	}
	for (int i = 1; i < H2.size; i++)
	{
		y.mas[H1.size - 1 + i] = H2.mas[i];
	}
}

void Solve::out(bool fl)
{
	if (fl)
	{
		A.out();
		cout << "f: ";
		f.out();
		cout << "alfa: ";
		alfa.out();
		cout << "betta: ";
		betta.out();
		cout << "epsilon: ";
		epsilon.out();
		cout << "etta: ";
		etta.out();
	}
	cout << "y: ";
	y.out();
	cout << endl;
}
