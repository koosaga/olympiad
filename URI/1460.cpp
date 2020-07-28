// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1460
#include <cstdio>
#include <vector>
#include <algorithm>
#include <deque>
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 500;
vector<int> matriz[MAXN];
int n,m,q,maior[MAXN],menor[MAXN];
int func(int k){
	deque<ii> janela_maior,janela_menor;
	for(int i=0;i<k;i++){
		ii davez_maior = MP(i,maior[i]);
		ii davez_menor = MP(i,menor[i]);
		while(!janela_maior.empty() && janela_maior.back().second <= davez_maior.second) janela_maior.pop_back();
		janela_maior.push_back(davez_maior);
		while(!janela_menor.empty() && janela_menor.back().second >= davez_menor.second) janela_menor.pop_back();
		janela_menor.push_back(davez_menor);
	}
	int delta = janela_menor.front().second - janela_maior.front().second + 1;
	if(delta >= k) return 1;
	for(int i=k;i<n;i++){
		ii davez_maior = MP(i,maior[i]);
		ii davez_menor = MP(i,menor[i]);
		while(!janela_maior.empty() && janela_maior.back().second <= davez_maior.second) janela_maior.pop_back();
		janela_maior.push_back(davez_maior);
		if(janela_maior.front().first <= i - k) janela_maior.pop_front();
		while(!janela_menor.empty() && janela_menor.back().second >= davez_menor.second) janela_menor.pop_back();
		janela_menor.push_back(davez_menor);
		if(janela_menor.front().first <= i - k) janela_menor.pop_front();
		delta = janela_menor.front().second - janela_maior.front().second + 1;
		if(delta >= k) return 1;
	}
	return 0;
}
int main(){
	while(scanf("%d %d",&n,&m) && (n || m)){
		for(int i=0;i<n;i++){
			matriz[i].assign(m,0);
		}
		for(int i=0;i<n;i++){
			for(int j=0;j<m;j++){
				scanf("%d",&matriz[i][j]);
			}
		}
		scanf("%d",&q);
		while(q--){
			int a,b;
			scanf("%d %d",&a,&b);
			for(int i=0;i<n;i++){
				if(matriz[i][m-1] < a){
					maior[i] = m+2;
				}
				else{
					vector<int>::iterator it1 = lower_bound(matriz[i].begin(),matriz[i].end(),a);
					maior[i] = it1 - matriz[i].begin() + 1; 
				}
				if(matriz[i][0] > b){
					menor[i] = -1;
				}
				else{
					vector<int>::iterator it2 = upper_bound(matriz[i].begin(),matriz[i].end(),b);
					it2--;
					menor[i] = it2 - matriz[i].begin() + 1; 
				}
				//printf("%d: [%d,%d]\n",i,maior[i],menor[i]);
			}
			int ini = 1, fim = min(n,m),meio,resp = 0;
			while(ini <= fim){
				meio = (ini + fim)/2;
				if(func(meio)){
					resp = meio;
					ini = meio + 1;
				}
				else fim = meio - 1;
			}
			printf("%d\n",resp);
		}
		printf("-\n");
	}
	return 0;
}
