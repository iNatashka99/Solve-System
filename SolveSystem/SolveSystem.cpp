
#include <iostream>
#include "time.h"
#include <omp.h>
#include "Solve.h"

using namespace std;

#define THREADS 1


double Posled(int n, double &time)
{
	Solve S0(n + 1);
	double start = clock();
	S0.Posled_alg(0);
	time = (clock() - start) / 1000.0;
	return time;
}


// OpenMP
double OMP1(int n, double &time)
{
	omp_set_num_threads(THREADS);
	double start = clock();
	Solve S0(n + 1);
	int p = ceil((n + 1) / 2);
	Solve S1(0, p + 1, S0);
	Solve S2(p, n + 1, S0);
#pragma omp parallel
	{
		int thread = omp_get_thread_num(); // 0 или 1
		int amount = omp_get_num_threads();  //2

		if (thread == 0)
		{
			// тут прямой ход правой
			S1.Right_alg1();
		}
		if ((thread == 1) || (amount == 1))
		{
			// тут прямой ход левой
			S2.Left_alg1();
		}
#pragma omp barrier
		// тут обмен
		double alfa1, betta1, epsilon1, etta1;
		alfa1 = -S1.A.b.mas[p] / (S1.A.a.mas[p] * S1.alfa.mas[p] + S1.A.c.mas[p]);
		betta1 = (S1.f.mas[p] - S1.A.a.mas[p] * S1.betta.mas[p]) / (S1.A.a.mas[p] * S1.alfa.mas[p] + S1.A.c.mas[p]);
		epsilon1 = S2.epsilon.mas[1];
		etta1 = S2.etta.mas[1];
		double xp = S0.getYp(alfa1, betta1, epsilon1, etta1);
#pragma omp barrier
		if (thread == 0)
		{
			// тут обратный ход правой
			S1.Right_alg2(xp);
		}
		if ((thread == 1) || (amount == 1))
		{
			// тут обратный ход левой
			S2.Left_alg2(xp);
		}
#pragma omp barrier
		S0.CollectHalfs(S1.y, S2.y);
		if ((n <= 10) && (thread == 0))
		{
			S0.out(0);
		}
	}
	time = (clock() - start) / 1000.0;
	return time;
}


int main()
{
	int n = 10;
	double rez = 0;
	double time;
	time = OMP1(n, time);
	rez = rez + time;
	cout << rez << endl;
	return 1;
}
