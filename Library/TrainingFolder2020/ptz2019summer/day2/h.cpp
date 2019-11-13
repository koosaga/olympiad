#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
typedef long long lint;
typedef pair<lint, int> pi;
const int MAXN = 35005;
const int MAXT = 132000;
 
int n, q, a[MAXN];
 
struct node{
	vector<lint> v[2][2];
	int len;
}tree[MAXT];
 
node newnode(int x){
	node ret;
	ret.len = 1;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			ret.v[i][j].resize(2);
			ret.v[i][j][0] = 0;
			ret.v[i][j][1] = x;
			if(i + j > 0) ret.v[i][j][0] = -1e18;
		}
	}
	return ret;
}
 
node merge(node x, node y){
	node ret;
	ret.len = x.len + y.len;
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			ret.v[i][j].resize(ret.len + 1);
			fill(ret.v[i][j].begin(), ret.v[i][j].end(), -1e18);
		}
	}
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			for(int k=0; k<2; k++){
				vector<lint> L, R;
				for(int a=1; a<sz(x.v[i][j]); a++){
					L.push_back(x.v[i][j][a-1] - x.v[i][j][a]);
				}
				for(int a=1; a<sz(y.v[j][k]); a++){
					R.push_back(y.v[j][k][a-1] - y.v[j][k][a]);
				}
				vector<lint> z(sz(L) + sz(R) + 1);
				z[0] = x.v[i][j][0] + y.v[j][k][0];
				merge(L.begin(), L.end(), R.begin(), R.end(), z.begin() + 1);
				for(int a=1; a<sz(z); a++){
					z[a] = z[a-1] - z[a];
				}
				if(j) z.erase(z.begin());
				for(int a=0; a<sz(z); a++){
					ret.v[i][k][a] = max(ret.v[i][k][a], z[a]);
				}
			}
		}
	}
	return ret;
}
 
void init(int s, int e, int p){
	if(s == e){
		tree[p] = newnode(a[s]);
		return;
	}
	int m = (s+e)/2;
	init(s, m, 2*p);
	init(m + 1, e, 2*p+1);
	tree[p] = merge(tree[2*p], tree[2*p+1]);
}
 
struct result{
	pi ans[2][2];
}dap[MAXN];
 
result merge(result x, result y, int v){
	result ret;
	ret.ans[0][0] = ret.ans[0][1] = ret.ans[1][0] = ret.ans[1][1] = pi(-1e18, 0);
	for(int i=0; i<2; i++){
		for(int j=0; j<2; j++){
			for(int k=0; k<2; k++){
				pi x1 = x.ans[i][j];
				pi x2 = y.ans[j][k];
				ret.ans[i][k] = max(ret.ans[i][k], pi(x1.first + x2.first - j * v, x1.second + x2.second - j));
			}
		}
	}
	return ret;
}
 
struct query{ int s, e, x; lint l, m, r; }qr[MAXN];
vector<int> seq[MAXN];
int ptr[MAXT][2][2];
 
void add_seq(int s, int e, int ps, int pe, int p, int i){
	if(e < ps || pe < s) return;
	if(s <= ps && pe <= e){
		seq[i].push_back(p);
		return;
	}
	int pm = (ps+pe)/2;
	add_seq(s, e, ps, pm, 2*p, i);
	add_seq(s, e, pm+1, pe, 2*p+1, i);
}
 
int main(){
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	init(1, n, 1);
	for(int i=0; i<q; i++){
		scanf("%d %d %d",&qr[i].s, &qr[i].e, &qr[i].x);
		add_seq(qr[i].s, qr[i].e, 1, n, 1, i);
		qr[i].l = -2e9;
		qr[i].r = 2e9;
	}
	for(int iter = 0; iter < 35; iter++){
		memset(ptr, 0, sizeof(ptr));
		for(int i=0; i<q; i++) qr[i].m = (qr[i].r - qr[i].l) / 2 + qr[i].l;
		vector<int> ord(q); iota(ord.begin(), ord.end(), 0);
		sort(ord.begin(), ord.end(), [&](const int &x, const int &y){
			return qr[x].m < qr[y].m;
		});
		for(auto &i : ord){
			bool is_empty = 1;
			for(auto &j : seq[i]){
				result ret;
				for(int k=0; k<2; k++){
					for(int l=0; l<2; l++){
						vector<lint> &drz = tree[j].v[k][l];
						while(ptr[j][k][l] + 1 < sz(drz) && drz[ptr[j][k][l]] <= drz[ptr[j][k][l] + 1] + qr[i].m){
							ptr[j][k][l]++;
						}
						ret.ans[k][l] = pi(drz[ptr[j][k][l]] + 1ll * ptr[j][k][l] * qr[i].m, ptr[j][k][l]);
					}
				}
				if(is_empty) dap[i] = ret;
				else dap[i] = merge(dap[i], ret, qr[i].m);
				is_empty = 0;
			}
			if(dap[i].ans[0][0].second < qr[i].x) qr[i].l = qr[i].m + 1;
			else qr[i].r = qr[i].m;
		}
	}
	for(int i=0; i<q; i++){
		printf("%lld\n", dap[i].ans[0][0].first - qr[i].x * qr[i].l);
	}
}
