// Ivan Carvalho
// Solution to https://dmoj.ca/problem/ccoprep3p2
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
vector<ll> M,B;
int ptr;
long double meet(ll x,ll y){
	return 1.0 * (B[y] - B[x])/(M[x]-M[y]);
}
bool useless(ll left,ll mid,ll right){
		long double x = meet(left,right);
		long double y = x*M[mid] + B[mid];
		long double ly = M[left]*x + B[left];
		return y > ly;
	}
void add(ll m,ll b){
	M.push_back(m);
	B.push_back(b);
	while(M.size() >= 3 && useless(M.size() - 3,M.size()-2,M.size() - 1)){
		M.erase(M.end()-2);
		B.erase(B.end()-2);
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
	int N;
	ll L;
	scanf("%d %lld",&N,&L);
	add(0,0);
	ll total = 0,davez,best;
	for(int i=1;i <= N;i++){
		scanf("%lld",&davez);
		total += davez;
		if(i != 1) total++;
		best = query(total) + total*total - 2*total*L + L*L;
		add(-2*(total+1),(total+1)*(total + 1) + 2*L*(total+1) + best);
	}
	printf("%lld\n",best);
	return 0;
}