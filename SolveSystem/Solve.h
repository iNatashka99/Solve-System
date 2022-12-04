#pragma once

#include "Matrix.h"
#include "Vector.h"


class Solve
{
public:
	int size;
	double h;
	Vector alfa;
	Vector betta;
	Vector epsilon;
	Vector etta;
	Matrix A;
	Vector f;
	Vector y;
	Solve() {};
	Solve(int n);
	Solve(int start_row, int end_row, Solve &S);
	void Posled_alg(bool fl);
	void Left_alg1();
	void Left_alg2(double xp);
	void Right_alg1();
	void Right_alg2(double xp);
	double f_a(int i);
	double f_b(int i);
	double f_c(int i);
	double f_f(int i);
	void SetParameters();
	double getYp(double alfa1, double betta1, double epsilon1, double etta1);
	void out(bool fl);
	void CollectHalfs(Vector &H1, Vector &H2);
	~Solve();
};