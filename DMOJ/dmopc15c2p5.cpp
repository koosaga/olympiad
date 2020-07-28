// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc15c2p5
#include <cstdio>
#include <vector>
#include <algorithm>
#define MP make_pair
#define A first
#define B second.first
#define ID second.second
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
typedef pair<ll,ii> iii;
vector<iii> E,H;
vector<ii> Q;
vector<ll> respostas;
double meet(iii l1,iii l2){
	return 1.0*(l2.B - l1.B)/(l1.A - l2.A);
}
bool useless(iii l1,iii l2,iii l3){
	double x = meet(l1,l3);
	double y = l2.A*x + l2.B;
	double ly = l3.A*x + l3.B;
	if(y == ly){
		return l2.ID > l3.ID;
	}
	return y < ly;
}
int main(){
	ll n,q;
	scanf("%lld %lld",&n,&q);
	respostas.assign(q+1,0);
	for(ll i=1;i<=n;i++){
		ll a,b;
		scanf("%lld %lld",&b,&a);
		E.push_back(MP(a,MP(b,i)));
	}
	sort(E.begin(),E.end());
	for(ll i=0;i<E.size();i++){
		iii davez = E[i];
		while(!H.empty() && H.back().A == davez.A) H.pop_back();
		while(H.size() >= 2 && useless(H[H.size()-2],H[H.size()-1],davez)) H.pop_back();
		H.push_back(davez);
	}
	for(ll i=1;i<=q;i++){
		ll t;
		scanf("%lld",&t);
		Q.push_back(MP(t,i));
	}
	sort(Q.begin(),Q.end());
	ll ptr = 0;
	for(ll i=0;i<Q.size();i++){
		ll t = Q[i].first;
		while(ptr + 1 < H.size()){
			if(H[ptr+1].A*t + H[ptr+1].B > H[ptr].A*t + H[ptr].B){
				ptr++;
			}	
			else if(H[ptr+1].A*t + H[ptr+1].B == H[ptr].A*t + H[ptr].B){
				if(H[ptr+1].ID < H[ptr].ID){
					ptr++;
				}
				else{
					break;
				}
			}
			else{
				break;
			}
		}
		respostas[Q[i].second] = H[ptr].ID - 1;
	}
	for(ll i=1;i<=q;i++) printf("%lld\n",respostas[i]);
	return 0;
}
}