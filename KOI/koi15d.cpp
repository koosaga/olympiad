#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 705;

struct kek{
	int a, b, c, cnt, ra, rb, rc;
	kek(){}
	kek(int a, int b, int c, int cnt): a(a), b(b), c(c), cnt(cnt), ra(a), rb(b), rc(c) {}
};

int aux[2 * MAXN][2 * MAXN];

vector<kek> compress(vector<kek> &v){
	for(auto &i : v){
		aux[i.a][i.b] += i.cnt;
	}
	vector<kek> w;
	for(auto &i : v){
		if(aux[i.a][i.b]){
			w.emplace_back(i.a, i.b, i.c, aux[i.a][i.b]);
			aux[i.a][i.b] = 0;
		}
	}
	return w;
}

void write(vector<kek> &write_pos, vector<kek> &v, vector<kek> &w){
	int tot = w[0].a + w[0].b + w[0].c;
	for(auto &i : w) aux[i.a][i.b] = (i.ra << 12) + i.rb;
	for(int itr = 0; itr < sz(write_pos); itr++){
		auto i = v[itr];
		int nxta = (aux[i.a][i.b] >> 12);
		int nxtb = (aux[i.a][i.b] & 4095);
		int nxtc = tot - nxta - nxtb;
		write_pos[itr].ra += nxta - i.a;
		write_pos[itr].rb += nxtb - i.b;
		write_pos[itr].rc += nxtc - i.c;
	}
	for(auto &i : w) aux[i.a][i.b] = 0;
}

char str[MAXN][MAXN][30];
int n, a[MAXN][MAXN];

vector<pi> get_border(int sx, int ex, int sy, int ey){
	vector<pi> v;
	for(int i=ex; i>=sx; i--) v.emplace_back(i, sy);
	for(int i=sy+1; i<=ey; i++) v.emplace_back(sx, i);
	return v;
}

kek splice(kek i, int l, int r){
	auto reduce = [&](int &x, int &y){
		int minv = min(x, y);
		x -= minv; y -= minv;
	};
	int nl = l, nr = i.ra + i.rb + i.rc - r - 1;
	reduce(nl, i.ra); reduce(nl, i.rb); reduce(nl, i.rc);
	reduce(nr, i.rc); reduce(nr, i.rb); reduce(nr, i.ra); 
	return kek(i.ra, i.rb, i.rc, i.cnt);
}

void solve(int sx, int ex, int sy, int ey, vector<kek> &v){
	if(ex - sx <= 4 || ey - sy <= 4){
		auto B = get_border(0, ex - sx, 0, ey - sy);
		for(auto &i : v){
			for(int j=i.a; j<i.a + i.b; j++){
				aux[B[j].first][B[j].second] = 1;
			}
			for(int j=i.a+i.b; j<sz(B); j++){
				aux[B[j].first][B[j].second] = 2;
			}
			int cc = i.cnt;
			for(int i=1; i<=ex-sx; i++){
				for(int j=1; j<=ey-sy; j++){
					int val = aux[i-1][j] + aux[i-1][j-1] * 3 + aux[i][j-1] * 9;
					char choice = str[i + sx][j + sy][val];
					if(choice == 'L') aux[i][j] = aux[i][j-1];
					if(choice == 'D') aux[i][j] = aux[i-1][j-1];
					if(choice == 'U') aux[i][j] = aux[i-1][j];
					a[sx + i][sy + j] += aux[i][j] * cc;
				}
			}
			int c[3] = {};
			for(int i=sy; i<=ey; i++) c[aux[ex-sx][i-sy]]++;
			for(int i=sx; i<ex; i++) c[aux[i-sx][ey-sy]]++;
			i.ra = c[0];
			i.rb = c[1];
			i.rc = c[2]; 
			for(int i=0; i<=ex-sx; i++){
				for(int j=0; j<=ey-sy; j++){
					aux[i][j] = 0;
				}
			}
		}
		return;
	}
	int mx = (sx + ex) / 2;
	int my = (sy + ey) / 2;
	int vec[5] = {0, ex - mx, my - sy + ex - mx, my - sy + ex - sx, ey - sy + ex - sx};
	vector<kek> split(sz(v));
	{
		for(int i=0; i<sz(v); i++) split[i] = splice(v[i], vec[1], vec[3]);
		vector<kek> comp = compress(split);
		solve(sx, mx, sy, my, comp);
		write(v, split, comp);
	}
	{
		for(int i=0; i<sz(v); i++) split[i] = splice(v[i], vec[2], vec[4]);
		vector<kek> comp = compress(split);
		solve(sx, mx, my, ey, comp);
		write(v, split, comp);
	}
	{
		for(int i=0; i<sz(v); i++) split[i] = splice(v[i], vec[0], vec[2]);
		vector<kek> comp = compress(split);
		solve(mx, ex, sy, my, comp);
		write(v, split, comp);
	}
	{
		for(int i=0; i<sz(v); i++) split[i] = splice(v[i], vec[2] - vec[1], vec[2] + vec[4] - vec[3]);
		vector<kek> comp = compress(split);
		solve(mx, ex, my, ey, comp);
		write(v, split, comp);
	}
}

int main(){
	int dx[2 * MAXN] = {};
	int q;
	scanf("%d %d",&n,&q);
	for(int i=1; i<n; i++){
		for(int j=1; j<n; j++){
			scanf("%s", str[i][j]);
		}
	}
	vector<kek> v(q);
	for(auto &i : v){
		scanf("%d %d %d",&i.a,&i.b,&i.c);
		i.cnt = 1;
		dx[i.a] += 1;
		dx[i.a + i.b] += 1;
	}
	v = compress(v);
	for(int i=1; i<=2*n+2; i++) dx[i] += dx[i-1];
	auto vect = get_border(0, n-1, 0, n-1);
	for(int i=0; i<sz(vect); i++) a[vect[i].first][vect[i].second] += dx[i];
	solve(0, n - 1, 0, n - 1, v);
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			printf("%d ", a[i][j] + 1);
		}
		puts("");
	}
}
