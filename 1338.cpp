// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1338
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 1e6 + 10;
bool crivo[MAXN];
vector<ll> squares;
ll SQ_SIZE,restam,davez;
void brute(ll pos,ll product,ll parity){
	if(pos == SQ_SIZE) return;
	if(squares[pos] > davez/product) return;
	brute(pos+1,product,parity);
	parity ^= 1;
	product *= squares[pos];
	if(parity % 2 == 1) restam -= davez/product;
	else restam += davez/product;
	brute(pos+1,product,parity);
}
ll bs(ll kth){
	ll ini = 1,fim = 1e12,meio,resp = -1;
	if(kth <= 10000000LL ) fim = 16449369;
	while(ini <= fim){
		meio = (ini+fim)/2;
		restam = meio;
		davez = meio;
		brute(0,1LL,0);
		if(restam >= kth){
			resp = meio;
			fim = meio - 1;
		}
		else{
			ini = meio + 1;
		}
	}
	return resp;
}
int main(){
	cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
	for(ll i = 2;i<MAXN;i++){
		if(crivo[i]) continue;
		squares.push_back(i*i);
		for(ll j = i*i;j<MAXN;j+=i) crivo[j] = true;
	}
	SQ_SIZE = squares.size();
	ll q;
	cin >> q;
	while(q--){
		ll kth;
		cin >> kth;
		cout << bs(kth) << '\n';
	}
	return 0;
}
