#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 1000005;
using lint = long long;
using pi = pair<lint, lint>;

int n;
lint l, r, a[MAXN];
lint cover[MAXN];
lint uniUntil[MAXN];
lint nxtPos[MAXN];
int validInterval[MAXN];
lint pmin[MAXN];

lint solve(lint x, int cnt = -1){
	x = max(x, 0ll);
	if(cnt == -1){
		cnt = upper_bound(a, a + n, x) - a;
	}
	if(cover[cnt] < 0 || min(x + r, 2 * cnt * r) < cover[cnt]) return 1e18;
	if(!validInterval[cnt]) return x;
	return min(2 * uniUntil[cnt], x + pmin[validInterval[cnt] - 1]) + x;
}

void precalc(){
	fill(cover, cover + n + 1, -1e18);
	cover[n] = l;
	for(int i=n-1; i>=0; i--){
		if(cover[i + 1] <= a[i] + r){
			cover[i] = max(0ll, a[i] - r);
		}
		else break;
	}
	lint cmax = 0;
	nxtPos[0] = r;
	pmin[0] = -r;
	for(int i=1; i<=n; i++){
		uniUntil[i] = uniUntil[i-1];
		nxtPos[i] = (2*i+1)*r;
		validInterval[i] = validInterval[i - 1];
		pi intv((2*i-1)*r, a[i-1]);
		if(intv.first < intv.second){
			validInterval[i] = i;
			intv.first = max(intv.first, cmax);
			uniUntil[i] += intv.second - intv.first;
			cmax = max(cmax, intv.second);
		}
		pmin[i] = min(pmin[i-1], 2 * uniUntil[i] - nxtPos[i]);
	}
}

int main(){
	scanf("%d %lld %lld",&n,&l,&r);
	for(int i=0; i<n; i++){
		scanf("%lld",&a[i]);
	}
	precalc();
	lint ret = min(solve(l), solve(l-r));
	int j = 0;
	for(int i=0; i<n; i++){
		ret = min(ret, solve(a[i], i+1));
		while(j < n && a[j] <= a[i] - 2 * r) j++;
		ret = min(ret, solve(a[i]-2*r, j));
	}
	if(ret > 1e17) ret = -1;
	cout << ret << endl;
}
