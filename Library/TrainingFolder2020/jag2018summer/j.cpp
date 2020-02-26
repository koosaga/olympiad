#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 200005;
const int MAXT = 530000;
const int mod = 1e9 + 7;

int n;
char str[MAXN];

struct node{
	int cnt[2];
	int flip;
	int opt[2];
	node(){
		cnt[0] = cnt[1] = flip = opt[0] = opt[1] = 0;
	}
	void rev(){
		flip ^= 1;
		swap(cnt[0], cnt[1]);
		swap(opt[0], opt[1]);
	}
	node(int x){
		cnt[x] = 1;
		cnt[1 - x] = 0;
		flip = 0;
		opt[0] = opt[1] = 1;
	}
	node operator+(const node &n)const{
		node ret;
		ret.cnt[0] = cnt[0] + n.cnt[0];
		ret.cnt[1] = cnt[1] + n.cnt[1];
		ret.flip = 0;
		ret.opt[0] = max({opt[0] + n.cnt[0], cnt[1] + n.opt[0], cnt[1] + n.cnt[0]});
		ret.opt[1] = max({opt[1] + n.cnt[1], cnt[0] + n.opt[1], cnt[0] + n.cnt[1]});
		return ret;
	}
}tree[MAXT];

void init(int s = 0, int e = n - 1, int p = 1){
	if(s == e) tree[p] = node(str[s] - 'A');
	else{
		int m = (s+e)/2;
		init(s, m, 2*p);
		init(m+1, e, 2*p+1);
		tree[p] = tree[2*p] + tree[2*p+1];
	}
}

void lazydown(int p){
	for(int j=2*p; j<2*p+2; j++){
		if(tree[p].flip){
			tree[j].rev();
		}
	}
	tree[p].flip = 0;
}

void upd(int s, int e, int ps = 0, int pe = n - 1, int p = 1){
	if(e < ps || pe < s) return;
	if(s <= ps && pe <= e){
		tree[p].rev();
		return;
	}
	lazydown(p);
	int m = (ps+pe)/2;
	upd(s, e, ps, m, 2*p);
	upd(s, e, m+1, pe, 2*p+1);
	tree[p] = tree[2*p] + tree[2*p+1];
}

int main(){
	scanf("%d",&n);
	scanf("%s", str + 1);
	str[0] = 'B'; str[n + 1] = 'A'; n += 2;
	init();
	int q; scanf("%d",&q);
	while(q--){
		int l, r; scanf("%d %d",&l,&r);
		l++; r++;
		upd(l, r);
		printf("%d\n", tree[1].opt[0] - 1);
	}
}
