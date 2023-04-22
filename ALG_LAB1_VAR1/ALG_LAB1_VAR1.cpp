// ALG_LAB1_VAR1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <random> 
#include <chrono>
#include <fstream>
#include <numeric>



void bubbleSort(std::vector<double>& v, int n) 
{
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (v[j] > v[j + 1]) {
                std::swap(v[j], v[j + 1]);
            }
        }
    }
}

std::vector<double> vectorGenerate(std::vector<double>& v)
{
    std::mt19937 engine(time(0));
    std::uniform_real_distribution<double> gen(-1.0, 1.0);
    for (auto& el : v)
        el = gen(engine);

    return v;
}

double getAverage(std::vector<double> const& v) {
    if (v.empty()) {
        return 0;
    }

    return std::reduce(v.begin(), v.end(), 0.0) / v.size();
}

int main()
{
    std::ofstream fout("result.txt");
    std::vector<int> N = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 };
    std::vector<double> min_time;
    std::vector<double> max_time;
    std::vector<double> avg_time;
    std::vector<double> time;

        for (auto it : N) 
        {
            std::vector<double> timing;
            for (int i = 0; i < 20; i++) 
            {
                std::vector<double> v(it);
                v = vectorGenerate(v);
                std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
                bubbleSort(v, it);
                std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
                std::chrono::duration<double> sec_diff = end - start;
                time.push_back(sec_diff.count());
                timing.push_back(sec_diff.count());
                std::cout << "Length: " << it <<"  SIZE: " << size(v) << "  Time: " << sec_diff.count() << " sec." << std::endl;
                fout << "Length: " << it << "  SIZE: " << size(v) << "  Time: " << sec_diff.count() << " sec." << std::endl;
            }      
            auto it = std::minmax_element(timing.begin(), timing.end());
            double min = *it.first;
            double max = *it.second;
            min_time.push_back(min);
            max_time.push_back(max);
            avg_time.push_back(getAverage(timing));
        }
        

        fout << "min time : ";
        std::cout << "min time : ";
        for (auto it : min_time) 
        {
            fout << it << " ";
            std::cout << it << " ";
        }

        fout << "max time : ";
        std::cout << "max time : ";
        for (auto it : max_time)
        {
            fout << it << " ";
            std::cout << it << " ";
        }

        fout << "avg time : ";
        std::cout << "avg time : ";
        for (auto it : avg_time)
        {
            fout << it << " ";
            std::cout << it << " ";
        }
        
        fout << "time : ";
        std::cout << "time : ";
        for (auto it : time)
        {
            fout << it << " ";
            std::cout << it << " ";
        }


        fout.close();
       
}

