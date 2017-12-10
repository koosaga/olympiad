#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef pair<llf, llf> pj;
const double eps = 1e-11;
const int MAXN = 200005;

int t[MAXN], r[MAXN];

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	iota(r + 1, r + n + 1, 1);
	for(int i=1; i<=m; i++){
		int x; scanf("%d",&x);
		t[x] = i;
	}
	sort(r + 1, r + n + 1, [&](const int &a, const int &b){
		return pi(t[a], -a) > pi(t[b], -b);
	});
	for(int i=1; i<=n; i++) printf("%d\n", r[i]);
}
