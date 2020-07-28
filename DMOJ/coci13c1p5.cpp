// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci13c1p5
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 2*1e6 + 1;
int qtd[MAXN],n;
int maior[MAXN];
map<int,int> primos;
vector<int> divisores,temp;
ll resp;
int main(){
	cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
	cin >> n;
	for(int i = 2;i<MAXN;i++){
		if(maior[i] == 0){
			maior[i] = i;
			for(int j = 2*i;j<MAXN;j+=i) maior[j] = i;
		}
	}
	for(int numero = 1;numero<=n;numero++){
		divisores.clear();
		primos.clear();
		divisores.push_back(1);
		int x;
		cin >> x;
		if(x == 1){
			qtd[1]++;
			continue;
		}
		int y = x;
		while(y != 1){
			primos[maior[y]]++;
			y /= maior[y];
		}
		for(auto it : primos){
			temp.clear();
			int fator = it.first;
			int aparece = it.second;
			int produtorio = 1;
			for(int contador = 1;contador<=aparece;contador++){
				produtorio *= fator;
				for(int i : divisores) temp.push_back(i*produtorio);
			}
			for(int i : temp) divisores.push_back(i);
		}
		for(int i : divisores){
			qtd[i]++;
		}
	}
	for(int i = 1;i<MAXN;i++){
		if(qtd[i] >= 2){
			resp = max(resp, 1LL*i*qtd[i] );
		}
	}
	cout << resp << endl;
	return 0;
}