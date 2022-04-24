#include <iostream>
#include <omp.h>
#include<cmath>
#include<list>
#include<cstdlib>

using namespace std;

double f(double x)
{
    return 1/(1+x*x);
}

double f_2(double x)
{
    return sin(x)*sin(x);
}

double integr(double (*f)(double), double A, double B)
{
    double sum[2]{0};
    int n = 1000000;

    #pragma omp parallel
    {
        #pragma omp single
        {
            #pragma omp task
            {
                for (int i = 1; i < n/2; ++i)
                {
                    sum[0] += f(A+((B-A)/n)*i);
                }
            }
            #pragma omp task
            {
                for (int i = n/2; i < n; ++i)
                {
                    sum[1] += f(A+((B-A)/n)*i);
                }
            }
            #pragma omp taskwait
        }

    }

    return (sum[0] + sum[1])*(B-A)/n + ((B-A)/n)*(f(A) + f(B))/2;
}

double integral_posl(double (*f)(double), double A, double B)
{
    double inter_full = integr(f, A, B);
    double inter_left_half = integr(f, A, (A+B)/2);
    double inter_right_half = integr(f, (A+B)/2, B);
    double val = inter_full - (inter_left_half + inter_right_half);

    if(-1e-10 < val && val < 1e-10)
    {
        return inter_full;
    }
    return integral_posl(f, A, (A+B)/2) + integral_posl(f, (A+B)/2, B);
}

double integral_par(double (*f)(double), double A, double B, bool is_external = true)
{
    double inter_full = integr(f, A, B);
    double inter_left_half = integr(f, A, (A+B)/2);
    double inter_right_half = integr(f, (A+B)/2, B);
    double val = inter_full - (inter_left_half + inter_right_half);

    if(-1e-10 < val && val < 1e-10)
    {
        return inter_full;
    }
    double a = 0;
    double b = 0;
    if(is_external)
    {
    #pragma omp parallel
    {
        #pragma omp single
            {
                #pragma omp task
                a = integral_par(f, A, (A+B)/2, false);

                #pragma omp task
                b = integral_par(f, (A+B)/2, B, false);
            }
    }
    }
    else
    {
        a = integral_posl(f, A, (A+B)/2);
        b = integral_posl(f,(A+B)/2, B);
    }
    return a + b;
}


int partition (int* a, int l, int r)
{
    int i = l-1, j = r;
    int v = a[r];
    while (true)
    {
        while (a[++i] < v);
        while (v < a[--j])
        {
            if (j == l)
            {
                break;
            }
        }
        if (i >= j)
        {
            break;
        }
        swap(a[i], a[j]);
    }
    swap(a[i], a[r]);
    return i;
}

void qsort (int* a, int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int i = partition(a, l, r);
    qsort(a, l, i - 1);
    qsort(a, i+1, r);
}

void qsort_par (int* a, int l, int r)
{
    if (l >= r)
    {
        return;
    }
    int i = partition(a, l, r);
      #pragma omp parallel
        {
        #pragma omp single
        {
            #pragma omp task
            qsort(a, l, i - 1);
            #pragma omp task
            qsort(a, i+1, r);
            #pragma omp taskwait
        }
        }
}

struct Pair
{
   int integer;
   bool logical;
};
bool is_prime(int n)
{
    if (n == 1)
    {
        return false;
    }
    if (n % 2 == 0 && n != 2)
    {
        return false;
    }
    for (int i = 3; i * i <= n; i += 2)
    {
        if (n % i == 0)
        {
            return false;
        }
    }
    return true;
}
void processNode(Pair& p)
{
    p.logical = is_prime(p.integer);
}
void processList(list<Pair>& l, void (*f)(Pair&))
{
    for (auto i = l.begin(); i != l.end(); ++i)
    {
        f(*i);
    }
}
void processList_par(list<Pair>& l, void (*f)(Pair&))
{
    int size = l.size();
    auto j = l.begin();
    advance(j, size/2);
    #pragma omp parallel
        {
        #pragma omp single
        {
            #pragma omp task
            for (auto i = l.begin(); i != j; ++i)
            {
                f(*i);
            }
            #pragma omp task
            for (auto i = j; i != l.end(); ++i)
            {
                f(*i);
            }
            #pragma omp taskwait
        }
        }
}
void feel_list(list<Pair>& l, int elements_count)
{
    Pair p;
    for (int i = 0; i < elements_count; ++i)
    {
        p.integer = rand()%10;
        p.logical = false;
        l.push_back(p);
    }
}



int main()
{
    /*double t = omp_get_wtime();
    cout << 4*integral_posl(f, 0, 1) << endl;
    cout << "Time posl:" << omp_get_wtime() - t <<endl;

    t = omp_get_wtime();
    cout << 4*integral_par(f, 0, 1) << endl;
    cout << "Time par:" << omp_get_wtime() - t <<endl;

    int* arr = new int[50000000]{0};
    t = omp_get_wtime();
    qsort(arr, 0, 50000000);
    cout << "qsort Time posl:" << omp_get_wtime() - t <<endl;
    t = omp_get_wtime();
    qsort_par(arr, 0, 50000000);
    cout << "qsort Time par:" << omp_get_wtime() - t <<endl;*/

    list<Pair> l;
    feel_list(l, 10);

    double t = omp_get_wtime();
    processList(l, processNode);
    cout << "Time posl:" << omp_get_wtime() - t <<endl;
    for(auto x: l)
    {
        cout << "number =" << x.integer << " prime - " << x.logical << endl;
    }
    cout << endl;

    list<Pair> l_2;
    feel_list(l_2, 10);

    t = omp_get_wtime();
    processList_par(l_2, processNode);
    cout << "Time par:" << omp_get_wtime() - t <<endl;
    for(auto x: l_2)
    {
        cout << "number =" << x.integer << " prime - " << x.logical << endl;
    }
    cout << endl;

    system("Pause");


    return 0;
}
