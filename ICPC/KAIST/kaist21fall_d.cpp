#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
const int MAXN = 1000005;

vector<int> operator*(vector<int> a, vector<int> b){
	vector<int> c(sz(a));
	for(int i = 0; i < sz(c); i++) c[i] = b[a[i]];
	return c;
}

vector<int> pwr(vector<int> a, int t){
	if(t == 0){
		iota(all(a), 0); return a;
	}
	if(t == 1) return a;
	if(t & 1) return pwr(a, t - 1) * a;
	return pwr(a * a, t / 2);
}

int n, m, dn, dm, d;

int get(int x, int y){
	x %= n; if(x < 0) x += n;
	y %= m; if(y < 0) y += m;
	return x*m+y;
}

char buf[MAXN], ret[MAXN];

int main(){
	scanf("%d %d %d %d %d",&n,&m,&dn,&dm,&d);
	vector<int> rot(n*m);
	vector<int> mvl(n*m);
	vector<int> mvr(n*m);
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			rot[i*m+j] = (i < d && j < d ? get(j, d-1-i) : get(i, j));
			mvl[i*m+j] = get(i, j - dm);
			mvr[i*m+j] = get(i - dn, j + (m - d));
		}
	}
	vector<int> comp = (pwr(rot * mvl, (m - d) / dm) * rot) * mvr;
	int it = (n - d) / dn + 1;
	comp = pwr(comp, it);
	for(int i = 0; i < n; i++){
		scanf("%s", buf);
		for(int j = 0; j < m; j++){
			int nxtpos = comp[i*m+j];
			int x = nxtpos / m + it * dn;
			int y = nxtpos % m;
			ret[get(x, y)] = buf[j];
		}
	}
	for(int i = 0; i < n; i++){
		for(int j = 0; j < m; j++){
			putchar(ret[i*m+j]);
		}
		puts("");
	}
}
