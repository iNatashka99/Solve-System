#pragma once



class Vector
{
public:
	int size;
	double *mas;
	Vector() {};
	Vector(int n);
	void SetVector(int start_row, int end_row, Vector &b);
	void SetVector(int n);
	void out();
	~Vector();
};