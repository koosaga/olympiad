// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1464
#include <cstdio>
#include <algorithm>
#include <vector>
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
struct point{
	int x,y;
};
bool comp(point A,point B){
	if (A.x < B.x) return true;
	if (A.x > B.x) return false;
	return A.y < B.y;
}
int ccw(point A,point B,point C){
	int val = A.x*(B.y - C.y) - A.y*(B.x-C.x) + B.x * C.y - B.y * C.x;
	if (val == 0) return 0;
	if (val > 0) return 1;
	return -1;
}
vector<point> CH(vector<point> P){
	int  n = P.size(),k=0;
	vector<point> H(2*n);
	sort(P.begin(),P.end(),comp);
	for(int i=0;i<n;i++){
		while(k >= 2 && ccw(H[k-2],H[k-1],P[i]) <= 0) k--;
		H[k++] = P[i];
	}
	for(int i=n-2,t=k+1;i>=0;i--){
		while(k >= t && ccw(H[k-2],H[k-1],P[i]) <= 0) k--;
		H[k++] = P[i];
	}
	H.resize(k-1);
	return H;
}
int main(){
	int quantidade;
	while(1){
		getint(quantidade);
		if (quantidade == 0) break;
		int camadas = 0;
		vector<point> entrada;
		for(int i=0;i<quantidade;i++){
			point temp;
			getint(temp.x);
			getint(temp.y);
			entrada.push_back(temp);
		}
		while(entrada.size() > 2){
			vector<point> remocao = CH(entrada),substituto;
			if (remocao.size() > 2) camadas++;
			for(int i=0;i<entrada.size();i++){
				int marcado = 0;
				for(int j=0;j<remocao.size();j++){
					if (entrada[i].x == remocao[j].x && entrada[i].y == remocao[j].y){
						marcado = 1;
						break;
					}
					if (j != 0 && ccw(remocao[j-1],remocao[j],entrada[i]) == 0){
						marcado = 1;
						break;
					}
				}
				if (marcado) continue;
				substituto.push_back(entrada[i]);
			}
			swap(entrada,substituto);
		}
		if (camadas % 2 == 1) printf("Take this onion to the lab!\n");
		else printf("Do not take this onion to the lab!\n");
	}
	return 0;
}
