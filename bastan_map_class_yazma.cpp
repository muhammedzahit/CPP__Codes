#include <iostream>
#include <list>
using namespace std;

template <class T,class Z>
class Map{
private:
    list<T> keys;
    list<Z> values;
    int b_search(T key){
        int low = 0,end = keys.size()-1;
        while (low <= end){
            int mid = low + (end-low)/2;
            auto it = keys.begin();
            advance(it,mid);
            if (*it > key) end = mid-1;
            else if (*it < key) low = mid+1;
            else return mid;
        }
        return low;
    }
public:
    void insert(T key, Z value){
        auto it = keys.begin();
        if (keys.size() == 1){
            if (*it > key){
                keys.push_front(key);
                values.push_front(value);
            }
            else{
                keys.push_back(key);
                values.push_back(value);
            }
            return;
        }
        auto it2 = values.begin();
        int i = b_search(key);
        advance(it,i);
        advance(it2,i);
        if (*it == key){
            *it2 = value;
        }
        else {
            keys.insert(it, key);
            values.insert(it2, value);
        }
    }
    Z get(T key){
        int i = b_search(key);
        auto cmp = keys.begin();
        advance(cmp,i);
        if (*cmp != key) {
            cout << "Key bulunamadi\n";
            return NULL;
        }
        else {
            auto it = values.begin();
            advance(it,i);
            return *it;
        }
    }
    void remove(T key){
        int i=0;
        for (auto it = keys.begin(); it != keys.end(); it++,i++){
            if (*it == key){
                values.erase(values.begin() + i);
                keys.erase(it);
            }
        }
    }
    void print(){
        auto it2 = values.begin();
        for (auto it = keys.begin(); it != keys.end(); it++,it2++){
            cout << *it << " " << *it2 << endl;
        }
        cout << endl;
    }
    string enYakinBilet(T zaman,Z rota){
        int i = b_search(zaman);
        string a;
        auto it = keys.begin();
        auto it2 = keys.begin();
        auto it3 = values.begin();
        auto it4 = values.begin();
        advance(it,i);
        advance(it2,i);
        advance(it3,i);
        advance(it4,i);
        if (*it == zaman and *it3 == rota){
            a += *it + "  " + *it3 + "\n";
        }
        else{
            while (it != keys.begin()){
                --it;
                --it3;
                if (*it3 == rota){
                    a += *it + "  " + *it3 + "\n";
                    break;
                }
            }
            it2--;
            it4--;
            while (++it2 != keys.end()){
                ++it4;
                if (*it4 == rota){
                    a += *it2 + "  " + *it4 + "\n";
                    break;
                }
            }
        }
        if (a.empty()) a += "Gun icerisinde tarife uygun bilet bulunamadi.";
        a += "En yakin biletler bulundu.";
        return a;
    }
};

int main(){

    Map<string,string> mp;
    mp.insert("09.00","samsun");
    mp.insert("12.00","istanbul");
    mp.insert("11.00","samsun");
    mp.insert("13.00","istanbul");
    mp.insert("15.00","samsun");
    mp.print();
    string zaman;
    string rota;
    int tip;
    cout << "Gitmek istediginiz rotayi girin (ilk harf kucuk yazin) : ";
    cin >> rota;
    cout << "Gitmek istediginiz zamani secin (09.00 formatinda) : ";
    cin >> zaman;
    cout << mp.enYakinBilet(zaman,rota);
    return 0;
}