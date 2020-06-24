// Program girilen slide puzzle türünden bir bulmacayı çözmeyi amaçlar.
// Programda recursive çözüm kullanıldığı için kac_adim degerine 25 den
// yüksek değerler girildiğinde program yavaş çalışmaktadır.

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

vector<vector<int>> istenen{{1,2,3},{4,5,6},{7,8,0}};

int kac_adim;

bool cozulduMu;

enum Onceki{Yukari,Asagi,Sol,Sag};

void puzzle(vector<vector<int>> a,string c,string& d,int onceki,int num){
    if (a == istenen){
        d = c;
        return;
    }
	
    if (num == kac_adim || cozulduMu) {
        return;
    }
	
    int x,y;
	
    for (int i=0; i<3; i++)
        for (int j=0; j<3; j++)
            if (a[i][j] == 0){
                x = i;
                y = j;
            }
			
    if (x-1 >= 0 && onceki != Yukari){
        swap(a[x][y],a[x-1][y]);
		
        string k = c;
        k += (a[x][y]) + '0';
        k += " asagiya \n";
        puzzle(a,k,d,Asagi,num+1);
		
        swap(a[x][y],a[x-1][y]);
    }
	
    if (x+1 <= 2 && onceki != Asagi){
		
        swap(a[x][y],a[x+1][y]);
		
        string k = c;
        k += (a[x][y]) + '0';
        k += " yukariya \n";
        puzzle(a,k,d,Yukari,num+1);
		
        swap(a[x][y],a[x+1][y]);
    }
	
    if (y-1 >= 0 && onceki != Sol){
        swap(a[x][y],a[x][y-1]);
		
        string k = c;
        k += (a[x][y]) + '0';
        k += " saga \n";
        puzzle(a,k,d,Sag,num+1);
		
        swap(a[x][y],a[x][y-1]);
    }
    if (y+1 <= 2 && onceki != Sag){
        swap(a[x][y],a[x][y+1]);
		
        string k = c;
        k += (a[x][y]) + '0';
        k += " sola \n";
		
        puzzle(a,k,d,Sol,num+1);
    }
}
int main(){
    vector<vector<int>> girdi{{0,1,3},{4,2,5},{7,8,6}};
    cozulduMu = false;
    string adimlar;
    cout << "en fazla kac adimda cozulmesini istiyorsunuz ?\n";
    cin >> kac_adim;
    puzzle(girdi,"",adimlar,5,0);
    if (adimlar == "") cout << "Cozum bulunamadi. Adim sayisini arttirmayi deneyin.";
    else cout << "Cozum:\n" << adimlar;
    return 0;
}