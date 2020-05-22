// THREAD YONETİMİ ORNEK 2
#include <iostream>
#include <thread>
using namespace std;
bool bir = false,iki = false;
void birYaz(){
    cout << "bir" << endl;
    bir = true;
}
void ikiYaz(){
    while(!bir){
        // bir koşulu true oluncaya kadar dön
    }
    cout << "iki" << endl;
    iki = true;
}
void ucYaz(){
    while (!iki){

    }
    cout << "uc" << endl;
}
int main(){
    /* fonksiyonlari ucYaz -> ikiYaz -> birYaz diye çağırdığımız halde
     * birYaz -> ikiYaz -> ucYaz şeklinde çalışacaktır.
     */
    thread t1(ucYaz);
    thread t2(ikiYaz);
    thread t3(birYaz);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}