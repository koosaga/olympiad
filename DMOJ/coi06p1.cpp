// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coi06p1
#include <cstdio>
#include <stack>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> ii;
stack<ii> pilha;
int main(){
	ll n;
	scanf("%lld",&n);
	ll resp = 0,davez;
	for(ll i=1;i<=n;i++){
		scanf("%lld",&davez);
		ii atual = ii(davez,1);
		while(!pilha.empty() && pilha.top().first <= davez){
			resp += pilha.top().second;
			if(pilha.top().first == davez) atual.second += pilha.top().second;
			pilha.pop();
		}
		if(!pilha.empty()) resp++;
		pilha.push(atual);
	}
	printf("%lld\n",resp);
	return 0;
}