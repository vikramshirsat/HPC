#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <omp.h>
#include <time.h>
#include <vector>
#include <chrono>
using namespace std;
using namespace std::chrono;

int main()
{
    vector<int> a;
    for (int i = 0; i < 10000; i++)
        a.push_back(rand());
    auto start = high_resolution_clock::now();
    for(int i=0;i<a.size();i++)
    {
        for(int j=0;j<a.size()-1;j++)
        {
            if(a[j]>a[j+1])
            {
                swap(a[j],a[j+1]);
            }
        }
    }
     auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    // double time_taken=2;
    cout <<"Serial: "<< duration.count() << endl;

auto start1 = high_resolution_clock::now();
    for(int i=0;i<a.size();i++)
    {
        int first = i%2;
        #pragma omp parallel for shared(a,first)
        for(int j=first;j<a.size()-1;j++)
        {
            if(a[j]>a[j+1])
            {
                swap(a[j],a[j+1]);
            }
        }
    }
    auto stop1 = high_resolution_clock::now();
    auto duration1 = duration_cast<microseconds>(stop1 - start1);
    // double time_taken=2;
    cout <<"Parllel: "<< duration1.count() << endl;
    //cout<<"sorted"<<  << endl;
    return 0;
}