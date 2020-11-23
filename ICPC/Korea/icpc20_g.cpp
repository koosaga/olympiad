#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1000005;

lint solve(vector<lint> v, lint d){
	for(int i=0; i<sz(v); i++) v[i] -= i * d;
	return *max_element(all(v)) - *min_element(all(v));
}

int main(){
	int n;
	lint d;
	scanf("%d %lld",&n,&d);
	vector<lint> v(n);
	for(auto &i : v) scanf("%lld",&i);
	lint a = solve(v, d);
	reverse(all(v));
	a = min(a, solve(v, d));
	printf("%lld.%lld\n", (a / 2), 5 * (a % 2));
}
