// Ivan Carvalho
// Solution to https://dmoj.ca/problem/lkp18c1p6
#include <bits/stdc++.h>
#define LSOne(S) (S & (-S))
using namespace std;

knuth_b gen(1000000007);

typedef long long ll;
typedef pair<int,int> ii;
typedef tuple<ll,ll,ll,int> quadra;

const int MAXN = 1e5 + 10;
const int MAXK = 33;

quadra sweep[2*MAXN];
vector<ii> ordenado;
vector<int> compy;
int bit[MAXK][MAXN],resultado[MAXN],N,M,ordPtr,iteracao;
ll 
X_p[MAXN],Y_p[MAXN],ini[MAXN],meio[MAXN],fim[MAXN],resp[MAXN],somatorio;
int X_b[MAXN],Y_b[MAXN];

void update(int k,int pos){
	for(int i = pos;i<MAXN;i+=LSOne(i)) bit[k][i]++;
}

int read(int k,int pos){
	int ans = 0;
	for(int i = pos;i>0;i-=LSOne(i)){
		ans += bit[k][i];
	}
	return ans;
}

int query(int k,int a,int b){
	if(a > b) return 0;
	return read(k,b) - read(k,a-1);
}

void processa(){

	//printf("Processando\n");

	// Limpando variaveis	
	ordPtr = 0;
	int T = 0;
	iteracao++;

	// Construindo o sweep
	for(int i = 1;i<=N;i++){
		if(meio[i] == -1) continue;
		resultado[i] = 0;
		ll y0 = Y_p[i] - meio[i];
		ll y1 = Y_p[i] + meio[i];
		ll x0 = X_p[i] - meio[i];
		ll x1 = X_p[i] + meio[i];
		y0 = lower_bound(compy.begin(),compy.end(),y0) - 
compy.begin() + 1;
		y1 = prev(upper_bound(compy.begin(),compy.end(),y1)) - 
compy.begin() + 1;
		sweep[T++] = make_tuple(x0-1,y0,y1,-i);
		sweep[T++] = make_tuple(x1,y0,y1,i);
	}
	sort(sweep,sweep+T);

	// Varrendo
	for(int i = 0;i<T;i++){
		ll x = get<0>(sweep[i]),y0 = get<1>(sweep[i]),y1 = 
get<2>(sweep[i]);
		int id = get<3>(sweep[i]);
		while(ordPtr < M && ordenado[ordPtr].first <= x){
			update(iteracao,Y_b[ordenado[ordPtr].second]);
			ordPtr++;
		}
		int delta = query(iteracao,y0,y1);
		//printf("Id %d com %d\n",id,delta);
		if(id > 0) resultado[id] += delta;
		else resultado[-id] -= delta;
	}

	//printf("###########\n");
	//for(int i = 1;i<=N;i++) printf("%d ",resultado[i]);
	//printf("\n###########\n");

}

int has_valid(){
	for(int i = 1;i<=N;i++) if(ini[i] <= fim[i]) return 1;
	return 0;
}

int main(){

	scanf("%d",&N);
	for(int i = 1;i<=N;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		X_p[i] = x + y;
		Y_p[i] = x - y;
	}

	scanf("%d",&M);
	for(int i = 1;i<=M;i++){
		int x,y;
		scanf("%d %d",&x,&y);
		X_b[i] = x + y;
		Y_b[i] = x - y;
		compy.push_back(Y_b[i]);
	}
	for(int i = 1;i<=N;i++){
		ini[i] = 0;
		int j = (gen() % M) + 1;
		fim[i] = max(abs(X_b[j] - X_p[i]),abs(Y_b[j] - Y_p[i]));
	}
	sort(compy.begin(),compy.end());
	compy.erase(unique(compy.begin(),compy.end()),compy.end());
	for(int i = 1;i<=M;i++){
		Y_b[i] = lower_bound(compy.begin(),compy.end(),Y_b[i]) - 
compy.begin() + 1;
		ordenado.push_back(ii(X_b[i],i));
	}
	sort(ordenado.begin(),ordenado.end());

	while(has_valid()){
		for(int i = 1;i<=N;i++){
			if(ini[i] > fim[i]) meio[i] = -1;
			else meio[i] = ini[i] + (fim[i] - ini[i])/2;
			//printf("I %d intervalo %lld %lld com meio 
%lld\n",i,ini[i],fim[i],meio[i]);
		}
		processa();
		for(int i = 1;i<=N;i++){
			if(meio[i] == -1) continue;
			if(resultado[i] > 0){
				resp[i] = meio[i];
				fim[i] = meio[i] - 1;
			}
			else{
				ini[i] = meio[i] + 1;
			}
		}
	}

	for(int i = 1;i<=N;i++) somatorio += resp[i]; 
	printf("%lld\n",somatorio);

	return 0;

}
