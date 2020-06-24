// Bir önceki algoritmamızda recursive kullandığımız için karmaşık çözümler yapamıyordu.
// Bu kodda A* Algoritması kullanılmıştır. Karmaşık çözümler yapabilir. Bir önceki algoritmadan hızlıdır.
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<vector<int>> istenen{{1,2,3},{4,5,6},{7,8,0}};
enum Onceki{yukari,asagi,sag,sol};
int puan(vector<vector<int>>& girdi,int x,int y){
    int a = 0;
    int index = girdi[x][y]-1;
    if (index == -1) return 0;
    int x2 = index/3;
    int y2 = (index-(3*x2))%3;
    while (x2 != x){
        if (x2 > x) x++;
        else x--;
        a++;
    }
    while(y2 != y){
        if (y2 > y) y++;
        else y--;
        a++;
    }
    return a;
}

int heuristicPuan(vector<vector<int>>& girdi){
    int h_puan = 0;
    for (int i=0; i<3; i++)
        for (int y=0; y<3; y++)
          h_puan += puan(girdi,i,y);
    return h_puan;
}

int manhattanPuan(vector<vector<int>>& girdi){
    int x = 0;
    for (int i=0; i<3; i++)
        for (int y=0; y<3; y++){
            if (girdi[i][y] != istenen[i][y]) x++;
        }
    return x;
}

void find_way(vector<vector<int>> girdi,string a,string& b,int onceki){
    if (girdi == istenen){
        b = a;
        return;
    }
    int x,y;
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            if (girdi[i][j] == 0){
                x = i; y = j;
            }
    int minM = INT_MAX,minH = INT_MAX,yon = 5;
    if (x-1 >= 0 && onceki != asagi){
        swap(girdi[x-1][y],girdi[x][y]);
        if (manhattanPuan(girdi) < minM){
            yon = yukari;
            minM = manhattanPuan(girdi);
            minH = heuristicPuan(girdi);
        }
        else if (manhattanPuan(girdi) == minM){
            if (heuristicPuan(girdi) < minH) {
                yon = yukari;
                minM = manhattanPuan(girdi);
                minH = heuristicPuan(girdi);
            }
        }
        swap(girdi[x-1][y],girdi[x][y]);
    }
    if (x+1 <= 2 && onceki != yukari){
        swap(girdi[x+1][y],girdi[x][y]);
        if (manhattanPuan(girdi) < minM){
            yon = asagi;
            minM = manhattanPuan(girdi);
            minH = heuristicPuan(girdi);
        }
        else if (manhattanPuan(girdi) == minM){
            if (heuristicPuan(girdi) < minH){
                yon = asagi;
                minM = manhattanPuan(girdi);
                minH = heuristicPuan(girdi);
            }
        }
        swap(girdi[x+1][y],girdi[x][y]);
    }
    if (y-1 >= 0 && onceki != sag){
        swap(girdi[x][y-1],girdi[x][y]);
        if (manhattanPuan(girdi) < minM){
            yon = sol;
            minM = manhattanPuan(girdi);
            minH = heuristicPuan(girdi);
        }
        else if (manhattanPuan(girdi) == minM){
            if (heuristicPuan(girdi) < minH){
                yon = sol;
                minM = manhattanPuan(girdi);
                minH = heuristicPuan(girdi);
            }
        }
        swap(girdi[x][y-1],girdi[x][y]);
    }
    if (y+1 <= 2 && onceki != sol){
        swap(girdi[x][y+1],girdi[x][y]);
        if (manhattanPuan(girdi) < minM){
            yon = sag;
            minM = manhattanPuan(girdi);
            minH = heuristicPuan(girdi);
        }
        else if (manhattanPuan(girdi) == minM){
            if (heuristicPuan(girdi) < minH){
                yon = sag;
                minM = manhattanPuan(girdi);
                minH = heuristicPuan(girdi);
            }
        }
        swap(girdi[x][y+1],girdi[x][y]);
    }
    switch (yon) {
        case yukari:
            swap(girdi[x-1][y],girdi[x][y]);
            a += girdi[x][y] + '0';
            a += " asagi\n";
            break;
        case asagi:
            swap(girdi[x+1][y],girdi[x][y]);
            a += girdi[x][y] + '0';
            a += " yukari\n";
            break;
        case sol:
            swap(girdi[x][y-1],girdi[x][y]);
            a += girdi[x][y] + '0';
            a += " saga\n";
            break;
        case sag:
            swap(girdi[x][y+1],girdi[x][y]);
            a += girdi[x][y] + '0';
            a += " sola\n";
            break;
    }
    find_way(girdi,a,b,yon);
}

int main(){

    vector<vector<int>> girdi{{4,7,1},{8,6,2},{5,3,0}};
    string a;
    find_way(girdi,"",a,5);
    cout << a;
    return 0;
}