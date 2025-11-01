#include <cmath>
#include <iomanip>
#include <iostream>
#include <ctime>

double f(double t)
{
	return sin(sin(t));
}

struct intresult
{
	double area;
	unsigned long iterations;
};

intresult integrate(double t0, double t, double dt)
{
	unsigned long itrs = (t - t0) / dt;
	double area = 0;

	for (unsigned long i = 0; i <= itrs; ++i)
	{
		area += dt * f(t0 + i * dt);
	}

	intresult y;
	y.area = area;
	y.iterations = itrs + 1; // add one because we go from 0 until i == itrs, so it's itrs + 1

	return y;
}

int main()
{
	double t0 = 0;
	double dt = .00001;
	double t = 10;
	unsigned long itrs = 10;

	timespec start, end;

	intresult result = integrate(t0, t, dt);

	clock_gettime(CLOCK_MONOTONIC, &start);

	for (int i = 0; i < itrs; ++i)
	{
		integrate(t0, t, dt);
	}

	clock_gettime(CLOCK_MONOTONIC, &end);

	std::cout << std::setprecision(100);

	std::cout << "Iterations of Function Over [" << t0 << ", " << (t0 + result.iterations * dt) << "]: " << result.iterations << std::endl;
	std::cout << "Area: " << result.area << std::endl;
	std::cout << "Error: ~" << 1.62960311845949599833215279526380750441030805528490007161244326911918585159 - result.area << std::endl;

	unsigned long ns = (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec);

	std::cout << std::endl;
	std::cout << "BENCHMARK" << std::endl;
	std::cout << "Total Time for " << result.iterations << " Iterations: " << ns << " ns" << std::endl;
	std::cout << "Average Time " << ns / itrs << " ns" << std::endl;

	return 0;
}
