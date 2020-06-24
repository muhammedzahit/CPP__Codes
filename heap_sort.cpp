#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void print(vector<int>& a){
    for (int i : a)
        cout << i << " ";
    cout << endl;
}
void swim(vector<int>& a,int k){
    while (k > 1 && a[k] > a[(k/2)]){
        swap(a[k],a[(k/2)]);
        k = k/2;
    }
}
void sink(vector<int>& a,int k){
    while (2*k <= a.size()-1){
        int j = 2*k;
        if (j < a.size()-1  && a[j] < a[j+1] ) j++;
        if (a[k] > a[j]) break;
        swap(a[k],a[j]);
        k = j;
    }
}
void insert(vector<int>& a,int x){
    a.push_back(x);
    swim(a,a.size()-1);
}
int returnMax(vector<int>& a){
    int max = a[1];
    swap(a[1],a[a.size()-1]);
    a.erase(a.begin()+a.size()-1);
    sink(a,1);
    return max;
}
vector<int> heapSort(vector<int> dizi){
    // önce listeyi heap max' a göre sıralamamız lazım.
    for (int i = dizi.size()/2 ; i>=1 ; i--){
        sink(dizi,i);
    }
    vector<int> siraliDizi;
    while (dizi.size() != 1){
        siraliDizi.push_back(returnMax(dizi));
    }
    return siraliDizi;
}

int main()
{
    // ilk elemana işlem kolaylığı için 0 atanmıştır. Bu eleman kullanılmayacaktır.
    vector<int> dizi{0,5,7,2,3,9,0,6,1,10};
    vector<int> sirali = heapSort(dizi);
    print(sirali);
}