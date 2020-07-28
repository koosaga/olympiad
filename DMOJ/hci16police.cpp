// Ivan Carvalho
// Solution to https://dmoj.ca/problem/hci16police
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
vector<ll> M,B;
int ptr;
ll V[100010],N,H;
double intersect(int l1,int l2){
	return -double(B[l1] - B[l2])/double(M[l1] - M[l2]);
}
bool useless(int l1,int l2,int l3){
	double x = intersect(l1,l3);
	double y = M[l2]*x + B[l2];
	double ly = M[l3]*x + B[l3];
	return y > ly;
}
void add(ll m,ll b){
	M.push_back(m);
	B.push_back(b);
	while(M.size() >= 3 && useless(M.size() - 3, M.size() - 2, M.size() - 1)){
		M.erase(M.end() - 2);
		B.erase(B.end() - 2);
	}
}
ll query(ll x){
	if(ptr >= M.size()) ptr = M.size() - 1;
	while(ptr + 1 < M.size() && M[ptr+1]*x + B[ptr+1] < M[ptr]*x + B[ptr]){
		ptr++;
	}
	return M[ptr]*x + B[ptr];
}
int main(){
	scanf("%lld %lld",&N,&H);
	for(ll i=1;i<=N;i++) scanf("%lld",&V[i]);
	add(-2*V[1],V[1]*V[1]);
	for(ll i=1;i<N;i++){
		ll posx = V[i];
		ll best = query(posx) + posx*posx + H;
		add(-2*V[i+1],V[i+1]*V[i+1] + best);
	}
	printf("%lld\n",query(V[N]) + V[N]*V[N] + H);
	return 0;
}