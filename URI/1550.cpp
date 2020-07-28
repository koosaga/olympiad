// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1550
#include <cstdio>
#include <queue>
#include <unordered_set>
#define MP make_pair
using namespace std;
typedef pair<int,int> pi;
inline int reverso(int x){
	int novo = 0;
	while(x>0){
		novo = novo*10 + (x%10);
		x = x/10;
	}
	return novo;
}
int main(){
	int casos;
	scanf("%d",&casos);
	while(casos--){
		 unordered_set<int> jafoi;
		queue< pi > fila;
		int a,b;
		scanf("%d %d",&a,&b);
		fila.push(MP(a,0));
		while(!fila.empty()){
			pi davez = fila.front();
			fila.pop();
			if (davez.first==b){
				printf("%d\n",davez.second);
				break;
			}
			if (jafoi.count(davez.first)) continue;
			jafoi.insert(davez.first);
			int primeiro = reverso(davez.first),segundo = davez.first +1;
			fila.push(MP(primeiro,davez.second+1));
			fila.push(MP(segundo,davez.second+1));
		}
	}
	return 0;
}
