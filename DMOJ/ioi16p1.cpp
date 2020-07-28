// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ioi16p1
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
ll n,a,b,tot;
vector<ii> entrada;
deque<ii> guloso;
int find_subset(int L, int U, int w[], int N, int result[]){
	n = (ll)N;
	a = (ll)L;
	b = (ll)U;
	for(ll i = 0;i<n;i++){
		ll x = (ll)w[i];
		entrada.push_back(ii(x,i));
	}
	sort(entrada.begin(),entrada.end());
	for(ll i = 0;i<n;i++){
		guloso.push_back(entrada[i]);
		tot += entrada[i].first;
		while(!guloso.empty() && tot > b){
			tot -= guloso.front().first;
			guloso.pop_front();
		}
		if(!(a <= tot && tot <= b)) continue;
		vector<int> resp;
		for(ii davez : guloso){
			resp.push_back((int)davez.second);
		}
		for(ll j = 0;j<resp.size();j++) result[j] = resp[j];
		return (int)resp.size();
	}
	return 0;
}
int main(){
	return 0;
}