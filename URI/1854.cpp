// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1854
#include <iostream>
#include <string>
#include <sstream>
#define endl '\n'
#define LSOne(S) (S & (-S))
using namespace std;
typedef long long ll;
const ll MAXN = 1e3 +1;
const ll MAXP = 1e7 + 1;
const ll MODULO = 1e9 + 7;
ll mat[MAXN][MAXN],v[8],fatorial[MAXP],n,m,bit[MAXN][MAXN],dia,contador;
ll fast_expo(ll base,ll expo){
	if(expo == 0) return 1;
	if(expo == 1) return base % MODULO;
	if(expo % 2 == 0){
		ll temp = fast_expo(base,expo/2);
		return (temp*temp) % MODULO;
	}
	return (base*fast_expo(base,expo-1))%MODULO;
}
ll inv(ll val){
	return fast_expo(val,MODULO-2);
}
void update(ll posx,ll posy, ll val){
	for(ll i=posx;i<=n;i+=LSOne(i)){
		for(ll j=posy;j<=m;j+=LSOne(j)){
			bit[i][j] += val;
		}
	}
}
ll sum(ll posx,ll posy){
	ll ans = 0;
	while(posx > 0){
		ll tposy = posy;
		while(tposy > 0){
			ans += bit[posx][tposy];
			tposy -= LSOne(tposy);
		}
		posx -= LSOne(posx);
	}
	return ans;
}
ll query(ll x1,ll y1,ll x2,ll y2){
	return sum(x2,y2) + sum(x1-1,y1-1) - sum(x2,y1-1) - sum(x1-1,y2);
}
ll binomial(ll a,ll b){
	ll supeior = fatorial[a];
	ll denominador = inv((fatorial[a-b]*fatorial[b])%MODULO);
	return (supeior*denominador) % MODULO;
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> n >> m;
	string entrada;
	stringstream ss;
	fatorial[0] = 1;
	for(ll i=1;i<MAXP;i++){
		fatorial[i] = (fatorial[i-1]*i) % MODULO;
	}
	while(getline(cin,entrada)){
		ss.clear();
		contador = 0;
		ss << entrada;
		while(ss >> v[contador]) contador++;
		if(contador == 3){
			update(v[0],v[1],v[2]);
			mat[v[0]][v[1]] += v[2];
		}
		else if(contador == 2){
			update(v[0],v[1],-mat[v[0]][v[1]]);
			mat[v[0]][v[1]] = 0;
		}
		else if(contador == 5){
			dia++;
			ll a = query(v[0],v[1],v[2],v[3]);
			cout << "Day #" << dia << ": " << binomial(a+v[4]-1,v[4]) << endl;
		}
	}
	return 0;
}
