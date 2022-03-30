#include <iostream>
#include <omp.h>


using namespace std;

double f(double x)
{
    return 1/(1+x*x);
}

double integral(double (*f)(double), double A, double B)
{
    double sum[2]{0};
    int n = 100000000;
    double t = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            {
                for (int i = 0; i < n/2; ++i)
                {
                    sum[0] += (f(A+((B-A)*i)/n) + f(A+((B-A)*(i + 1)/n)))*(1.0/n)/2;
                }
            }
            #pragma omp task
            {
                for (int i = n/2; i < n; ++i)
                {
                    sum[1] += (f(A+((B-A)*i)/n) + f(A+((B-A)*(i + 1)/n)))*(1.0/n)/2;
                }
            }
            #pragma omp taskwait
        }

    }
    cout << "Time:" << omp_get_wtime() - t <<endl;
    return sum[0] + sum[1];
}

int main()
{
    cout << 4*integral(f, 0, 1);
    system("Pause");
    return 0;
}
