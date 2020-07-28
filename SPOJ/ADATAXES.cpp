// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADATAXES/
#include <cstdio>
#include <vector>
#include <algorithm>
#define LSOne(S) (S & (-S))
#define MP make_pair
#define gc getchar_unlocked
inline void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
inline void print(int n){
	char buf[11];
	buf[10] = '\n';
	int i = 9;
	while (n){
		buf[i--] = n % 10 + '0';
		n /= 10;
	}
	while (buf[i] != '\n') putchar_unlocked(buf[++i]);
}
using namespace std;
typedef pair<int,int> i2;
typedef pair<int,i2> i3;
typedef pair<int,i3> i4;
typedef long long ll;
const int MAXN = 3*1e5 + 10;
const ll MOD = 1e9 + 7;
ll bit[MAXN],exibir[MAXN];
vector<i2> atualizacoes;
vector<i4> perguntas;
int N,Q;
ll fast_expo(ll z,ll expo){
	if(expo == 0) return 1LL;
	if(expo == 1) return z;
	if(expo % 2 == 0){
		ll temp = fast_expo(z,expo/2);
		return (temp*temp) % MOD;
	}
	return (z*fast_expo(z,expo-1)) % MOD;
}
inline ll inv(ll z){
	if(z == 1) return z;
	return fast_expo(z,MOD-2);
}
inline void update(int pos,ll delta){
	while(pos <= N){
		bit[pos] = (bit[pos] * delta) % MOD;
		pos += LSOne(pos);
	}
}
inline ll read(int pos){
	ll ans = 1;
	while(pos > 0){
		ans = (ans*bit[pos]) % MOD;
		pos -= LSOne(pos);
	}
	return ans;
}
inline ll query(int a,int b){
	return (read(b)*inv(read(a-1))) % MOD;
}
int main(){
	getint(N);
	getint(Q);
	for(int i=1;i<=N;i++){
		int val;
		getint(val);
		atualizacoes.push_back(MP(val,i));
		bit[i] = 1;
	}
	sort(atualizacoes.begin(),atualizacoes.end());
	for(int i=1;i<=Q;i++){
		int l,r,h;
		getint(l);
		getint(r);
		getint(h);
		perguntas.push_back(MP(h,MP(i,MP(l+1,r+1))));
	}
	sort(perguntas.begin(),perguntas.end());
	int ptr = 0;
	for(int i =0;i<Q;i++){
		int h = perguntas[i].first;
		int idx = perguntas[i].second.first;
		int l = perguntas[i].second.second.first;
		int r = perguntas[i].second.second.second;
		while(ptr < N && atualizacoes[ptr].first <= h){
			update(atualizacoes[ptr].second, (ll)atualizacoes[ptr].first );
			ptr++;
		}
		exibir[idx] = query(l,r);
	}
	for(int i=1;i<=Q;i++) print((int)exibir[i]);
	return 0;
}