// THREAD YONETİMİ ÖRNEK
#include <iostream>
#include <vector>
#include <thread>
#include <numeric>
#include <algorithm>
#include <future>
#include <chrono>
using namespace std;
using namespace std::chrono;
promise<void> p2,p3; // sözleri verdik
shared_future<void> f1(p2.get_future()); // P2 e göre devam eder veya bekletir
shared_future<void> f2(p3.get_future()); // p3 e göre devam eder veya bekletir
void bir(){
    cout << "bir" << endl;
    p2.set_value();
}
void iki(){
    f1.wait();
    cout << "iki" << endl;
    p3.set_value();
}
void uc(){
    f2.wait();
    cout << "uc" << endl;
}

int main(){
    // fonksiyonlari uc -> iki -> bir siralamasi ile cağırdığımız halde
    // bir -> iki -> uc sıralaması ile yazılacaklardır.
    thread t1(uc);
    thread t2(iki);
    thread t3(bir);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}