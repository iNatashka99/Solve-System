#pragma once

#include "Vector.h"


class Matrix
{
public:
	int size;
	double h;
	Vector a;
	Vector b;
	Vector c;
	Matrix() {};
	Matrix(int n);
	void SetMatrix(int n);
	void SetMatrix(int start_row, int end_row, Matrix &A);
	void out();
	~Matrix();
};

