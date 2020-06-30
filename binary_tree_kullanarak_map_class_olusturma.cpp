#include <iostream>
using namespace std;
template<class T,class Z>
class Dugum{
public:
    T key;
    Z value;
    Dugum<T,Z>* right;
    Dugum<T,Z>* left;
    Dugum(T key, Z value) : key(key) , value(value){
        right = nullptr;
        left = nullptr;
    }
    void yazdir(){
        cout << key << " " << value << endl;
    }
};
template <class T,class Z>
class Map{
private:
    Dugum<T,Z>* kok;
    void yazdir(Dugum<T,Z>* main){
        if (main != nullptr){
            yazdir(main->left);
            main->yazdir();
            yazdir(main->right);
        }
    }
    Dugum<T,Z>* KucukBul(Dugum<T,Z>* main){
        Dugum<T,Z>* temp = main;
        while (temp && temp->left) temp = temp->left;
        return temp;
    }
    Dugum<T,Z>* Ekle(Dugum<T,Z>* start, T key, Z value){
        if (start){
            if (start->key < key)
                start->right = Ekle(start->right, key, value);
            else if(key < start->key)
                start->left = Ekle(start->left, key, value);
            else
                start->value = value;
        }
        else return new Dugum<T,Z>(key, value);
        return start;
    }
    Dugum<T,Z>* Bul(Dugum<T,Z>* start, T key){
        if (start){
            if (key > start->key) return Bul(start->right, key);
            else if (start->key > key) return Bul(start->left, key);
        }
        return start;
    }
    Dugum<T,Z>* Sil(Dugum<T,Z>* start, Dugum<T,Z>* deleted){
        if (start){
            if (start->key > deleted->key)
                start->left = Sil(start->left, deleted);
            else if (deleted->key > start->key)
                start->right = Sil(start->right, deleted);
            else if (deleted->key == start->key){
                Dugum<T,Z>* node = nullptr;
                if (start->right and start->left){
                    node = KucukBul(start->right);
                    Sil(start, node);
                    node->left = start->left;
                    node->right = start->right;
                }
                else if (start->right)
                    node = start->right;
                else if (start->left)
                    node =  start->left;
                return node;
            }
        }
        return start;
    }
public:
    Map(){
        kok = nullptr;
    }
    void Yazdir(){
        if (kok == nullptr) cout << "Eleman bulunmamaktadir." << endl;
        yazdir(kok);
        cout << endl;
    }
    void Ekle(T key, Z value){
        kok = Ekle(kok, key, value);
    }
    void Sil(T key){
        Dugum<T,Z>* temp = Bul(kok, key);
        if (!temp){
            cout << "Bu anahtarda bir eleman bulunamadi." << endl;
            return;
        }
        kok = Sil(kok, temp);
        delete temp;
    }
};

int main(){
    Map<int,int> mp;
    mp.Ekle(5, 5);
    mp.Ekle(3, 3);
    mp.Ekle(10, 10);
    mp.Ekle(1, 1);
    mp.Ekle(15, 15);
    mp.Ekle(4, 4);
    mp.Yazdir();
    return 0;
}