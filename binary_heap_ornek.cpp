#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> a;
// Binary Heap algoritması girilen dizinin max veya min değerini LogN zamanında bulabilen bir algoritmadır.
void swim(int k){
    while (k > 1 && a[k] > a[(k/2)]){
        swap(a[k],a[(k/2)]);
        k = k/2;
    }
}
void sink(int k){
    while (2*k <= a.size()-1){
        int j = 2*k;
        if (j < a.size()  && a[j] < a[j+1] ) j++;
        if (a[k] > a[j]) break;
        swap(a[k],a[j]);
        k = j;
    }
}
void insert(int x){
    a.push_back(x);
    swim(a.size()-1);
}
int returnMax(){
    int max = a[1];
    swap(a[1],a[a.size()-1]);
    a.erase(a.begin()+a.size()-1);
    sink(1);
    return max;
}
int main()
{
    a.push_back(0);
    insert(3);
    insert(4);
    insert(5);
    insert(7);
    insert(10);
    insert(6);
    cout << returnMax() << " " << returnMax() << " " << returnMax() << endl;

}