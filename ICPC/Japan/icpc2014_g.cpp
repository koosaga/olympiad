#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 300005;
const int MAXT = 1050000;
const int inf = 1e9;

int n, q;
char str[MAXN];
int h[MAXN];
set<int> s;

struct seg{
	struct node{
		int minOdd, minEven;
		int minOddPos, minEvenPos;
		int lazy;
	}tree[MAXT];
	void push(int p){
		tree[2*p].lazy += tree[p].lazy;
		tree[2*p].minOdd += tree[p].lazy;
		tree[2*p].minEven += tree[p].lazy;
		tree[2*p+1].lazy += tree[p].lazy;
		tree[2*p+1].minOdd += tree[p].lazy;
		tree[2*p+1].minEven += tree[p].lazy;
		tree[p].lazy = 0;
	}
	void pull(int p){
		tree[p].minOdd = min(tree[2*p].minOdd, tree[2*p+1].minOdd);
		tree[p].minEven = min(tree[2*p].minEven, tree[2*p+1].minEven);
		if(tree[p].minOdd != tree[2*p+1].minOdd){
			tree[p].minOddPos = tree[2*p].minOddPos;
		}
		else{
			tree[p].minOddPos = tree[2*p+1].minOddPos;
		}
		if(tree[p].minEven != tree[2*p+1].minEven){
			tree[p].minEvenPos = tree[2*p].minEvenPos;
		}
		else{
			tree[p].minEvenPos = tree[2*p+1].minEvenPos;
		}
	}
	void init(int s, int e, int p, int *a){
		if(s == e){
			tree[p] = {inf, inf, inf, inf, 0};
			if(a[s] & 1){
				tree[p].minOdd = a[s];
				tree[p].minOddPos = s;
			}
			else{
				tree[p].minEven = a[s];
				tree[p].minEvenPos = s;
			}
			return;
		}
		int m = (s+e)/2;
		init(s, m, 2*p, a);
		init(m+1, e, 2*p+1, a);
		pull(p);
	}
	void add(int s, int e, int ps, int pe, int p, int v){
		if(e < ps || pe < s) return;
		if(s <= ps && pe <= e){
			tree[p].lazy += v;
			tree[p].minOdd += v;
			tree[p].minEven += v;
			return;
		}
		int pm = (ps + pe) / 2;
		push(p);
		add(s, e, ps, pm, 2*p, v);
		add(s, e, pm+1, pe, 2*p+1, v);
		pull(p);
	}
	int query(int s, int e, int ps, int pe, int p){
		if(e < ps || pe < s) return 0;
		if(s <= ps && pe <= e){
			int ret = 0;
			if(tree[p].minOdd == 1) ret = max(ret, tree[p].minOddPos);
			if(tree[p].minEven == 0) ret = max(ret, tree[p].minEvenPos);
			return ret;
		}
		push(p);
		int pm = (ps + pe) / 2;
		return max(query(s, e, ps, pm, 2*p),
		query(s, e, pm+1, pe, 2*p+1));
	}


}seg;

void update(int pos, char val){
	if(val == '(') s.erase(pos);
	if(val == ')') s.insert(pos);
	str[pos] = val;
	seg.add(pos + 1, n, 0, n, 1, (val == '(' ? 2 : -2));
}

int main(){
	scanf("%d %d",&n,&q);
	scanf("%s", str);
	for(int i=0; i<n; i++){
		if(str[i] == ')'){
			s.insert(i);
			h[i+1] = h[i] - 1;
		}
		else h[i+1] = h[i] + 1;
	}
	seg.init(0, n, 1, h);
	while(q--){
		int x; scanf("%d",&x); x--;
		if(str[x] == ')'){
			update(x, '(');
			int pos = seg.query(0, x, 0, n, 1);
			update(pos, ')');
			printf("%d\n", pos + 1);
		}
		else{
			update(x, ')');
			int w = *s.begin();
			update(w, '(');
			printf("%d\n", w + 1);
		}
	}
}