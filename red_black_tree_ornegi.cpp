#include <iostream>
#include <queue>
using namespace std;
enum Color{BLACK = false,RED = true};
template<class T,class Z>
class Dugum{
public:
    T key;
    Z value;
    bool color;
    Dugum<T,Z>* right;
    Dugum<T,Z>* left;
    Dugum(T key, Z value,bool clr) : key(key) , value(value) , color(clr){
        right = nullptr;
        left = nullptr;
    }
    void yazdir(){
        cout << key << " " << value << " ";
        if (color) cout << "RED" << endl;
        else cout << "BLACK" << endl;
    }
};
template <class T,class Z>
class Map{
private:
    Dugum<T,Z>* kok;
    void yazdir(Dugum<T,Z>* main){
        queue<Dugum<T,Z>*> q;
        q.push(main);
        while (!q.empty()){
            Dugum<T,Z>* front = q.front();
            q.pop();
            front->yazdir();
            if (front->left) q.push(front->left);
            if (front->right) q.push(front->right);
        }
    }
    bool isRed(Dugum<T,Z>* main){
        if (!main) return BLACK;
        return main->color;
    }
    Dugum<T,Z>* solaDondur(Dugum<T,Z>* main){
        Dugum<T,Z>* temp = main->right;
        main->right = temp->left;
        temp->left = main;
        temp->color = main->color;
        main->color = RED;
        return temp;
    }
    Dugum<T,Z>* sagaDondur(Dugum<T,Z>* main){
        Dugum<T,Z>* temp = main->left;
        main->left = temp->right;
        temp->right = main;
        temp->color = main->color;
        main->color = RED;
        return temp;
    }
    void renkDegistir(Dugum<T,Z>* main){
        main->color = RED;
        main->left->color = BLACK;
        main->right->color = BLACK;
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
        else return new Dugum<T,Z>(key, value, RED);

        if (isRed(start->right) && !isRed(start->left)) start = solaDondur(start);
        if (isRed(start->left) && isRed(start->left->left)) start = sagaDondur(start);
        if (isRed(start->right) && isRed(start->left)) renkDegistir(start);

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
    int height(Dugum<T,Z>* main){
        if (!main) return 0;
        return 1 + max(height(main->left),height(main->right));
    }
public:
    //Dugum<T,Z>* kok;
    Map(){
        kok = nullptr;
    }
    void Yazdir(){
        if (kok == nullptr) cout << "Eleman bulunmamaktadir." << endl;
        yazdir(kok);
        cout << endl;
    }
    void Ekle(T key, Z value){
        if (kok == nullptr) kok = new Dugum<T,Z>(key,value,BLACK);
        else kok = Ekle(kok, key, value);
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
    int height(){
        return height(kok);
    }
};

int main(){
    Map<int,int> mp;
    mp.Ekle(11,11);
    mp.Ekle(1,1);
    mp.Ekle(14,14);
    mp.Ekle(2,2);
    mp.Ekle(7,7);
    mp.Ekle(15,15);
    mp.Yazdir();
    cout << mp.height();
    return 0;
}