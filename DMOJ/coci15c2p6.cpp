// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci15c2p6
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;
typedef tuple<int,int,int> trinca;
const int MAXN = 50010;
const int MAXK = 32;
int pai[MAXN],possivel[MAXN][MAXK],X[MAXN],Y[MAXN],Z[MAXN],N,K;
vector<trinca> ordenado;

int find(int x){
	if(x == pai[x]) return x;
	return pai[x] = find(pai[x]);
}

void join(int x,int y){
	x = find(x);
	y = find(y);
	if(x == y) return;
	if(x > y) swap(x,y);
	int novo[MAXK];
	for(int i = 0;i<K;i++) novo[i] = possivel[x][i] | possivel[y][i];
	for(int i = 0;i<K;i++){
		for(int j = 0;j<K;j++){
			novo[(i+j) % K] |= (possivel[x][i] & possivel[y][j]);
		}
	}
	for(int i = 0;i<K;i++) possivel[x][i] |= novo[i];
	pai[y] = x;
}

inline ll dist(int a,int b){
	return 1LL*(X[a] - X[b])*(X[a] - X[b]) + 1LL*(Y[a] - Y[b])*(Y[a] - Y[b]);
}

int checa(ll maximo){
	int teto = (int)ceil(sqrt(maximo)) + 3;
	for(int i = 1;i<=N;i++){
		pai[i] = i;
		for(int j = 0;j<K;j++){
			possivel[i][j] = 0;
		}
		possivel[i][Z[i]] = 1;
	}
	set<ii> caixa;
	int ponteiro = 1;
	caixa.insert(ii(Y[1],1));
	for(int i = 2;i<=N;i++){
		while(X[i] - X[ponteiro] > teto){
			caixa.erase(ii(Y[ponteiro],ponteiro));
			ponteiro++;
		}
		for(set<ii>::iterator it = caixa.lower_bound(ii(Y[i] - teto,-1));it != caixa.end();it++){
			int j = (*it).second;
			if(abs(Y[j] - Y[i]) > teto) break;
			if(dist(i,j) <= maximo) join(i,j);
			if(possivel[find(i)][0]) return 1;
		}
		if(possivel[find(i)][0]) return 1;
		caixa.insert(ii(Y[i],i));
	}
	return 0;
}

int main(){
	scanf("%d %d",&N,&K);
	for(int i = 0;i<N;i++){
		int x,y,z;
		scanf("%d %d %d",&x,&y,&z);
		ordenado.push_back(make_tuple(x,y,z));
	}
	sort(ordenado.begin(),ordenado.end());
	for(int i = 1;i<=N;i++){
		X[i] = get<0>(ordenado[i-1]);
		Y[i] = get<1>(ordenado[i-1]);
		Z[i] = get<2>(ordenado[i-1]) % K;
	}
	ll ini = 0, fim = 2*1e18,meio,ans = 2*1e18;
	while(ini <= fim){
		meio = ini + (fim - ini)/2;
		if(checa(meio)){
			ans = meio;
			fim = meio - 1;
		}
		else{
			ini = meio + 1;
		}
	}
	printf("%.3lf\n",sqrt(ans));
	return 0;
}
