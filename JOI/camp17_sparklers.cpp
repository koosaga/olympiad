#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<int, int>;

int n, k, a[MAXN];
int t;

bool solve(vector<lint> x, vector<lint> y){
	if(x[0] < y[0]) return 0;
	vector<int> sx = {0}, sy = {0};
	for(int i=1; i<x.size(); i++){
		if(x[sx.back()] <= x[i]) sx.push_back(i);
	}
	for(int i=1; i<y.size(); i++){
		if(y[sy.back()] >= y[i]) sy.push_back(i);
	}
	vector<lint> prec;
	for(int i=0; i+1<sy.size(); i++){
		prec.push_back(*max_element(y.begin() + sy[i] + 1, y.begin() + sy[i + 1] + 1));
	}
	int cs = 0, ce = 0;
	for(int i=0; i<sx.size(); i++){
		while(ce + 1 < sy.size()){
			lint nxtmax = prec[ce];
			if(nxtmax <= x[sx[i]]) ce++;
			else break;
		}
		if(i + 1 < sx.size()){
			lint nxtmin = *min_element(x.begin() + sx[i] + 1, x.begin() + sx[i + 1] + 1);
			while(cs <= ce && y[sy[cs]] > nxtmin) cs++;
			if(cs > ce) return 0;
		}
	}
	return ce + 1 == sy.size();
}

bool trial(int s){
	lint L = min(2ll * t * s, 2ll * a[n]);
	vector<lint> vu, vd;
	for(int i=1; i<=n; i++){
		if(i <= k) vu.push_back(a[i] - L * i);
		if(i >= k) vd.push_back(a[i] - L * i);
	}
	reverse(vu.begin(), vu.end());
	int mx1 = max_element(vu.begin(), vu.end()) - vu.begin();
	int mx2 = min_element(vd.begin(), vd.end()) - vd.begin();
	vector<lint> u1, u2, d1, d2;
	for(int i=0; i<=mx1; i++) u1.push_back(vu[i]);
	for(int i=0; i<=mx2; i++) d1.push_back(vd[i]);
	for(int i=mx1; i<vu.size(); i++) u2.push_back(vu[i]);
	for(int i=mx2; i<vd.size(); i++) d2.push_back(vd[i]);
	reverse(u2.begin(), u2.end());
	reverse(d2.begin(), d2.end());
	return solve(u1, d1) && solve(u2, d2);
}

int main(){
	scanf("%d %d %d",&n,&k,&t);
	for(int i=1; i<=n; i++) scanf("%d",&a[i]);
	int s = 0, e = 1e9;
	while(s != e){
		int m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m + 1;
	}
	cout << s << endl;
}
