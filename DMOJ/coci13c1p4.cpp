// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci13c1p4
#include <cstdio>
#include <set>
#define gc getchar_unlocked
inline void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
typedef pair<int,int> ii;
multiset<ii> itens;
multiset<int> bolsas;
int N,K;
long long resp;
int main(){
	getint(N);
	getint(K);
	for(int i=1;i<=N;i++){
		int mi,vi;
		getint(mi);
		getint(vi);
		itens.insert(ii(-vi,mi));
	}
	for(int i=1;i<=K;i++){
		int aguenta;
		getint(aguenta);
		bolsas.insert(aguenta);
	}
	for(multiset<ii>::iterator it = itens.begin();it != itens.end();it++){
		ii davez = (*it);
		int vi = -davez.first;
		int mi = davez.second;
		if(bolsas.empty()) break;
		multiset<int>::iterator ptr = bolsas.lower_bound(mi);
		if(ptr == bolsas.end()) continue;
		resp += 1LL*vi;
		bolsas.erase(ptr);
	}
	printf("%lld\n",resp);
	return 0;
}