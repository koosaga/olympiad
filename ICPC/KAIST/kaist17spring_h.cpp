#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
const int MAXN = 100005;

int n, a[MAXN];
lint b[MAXN];

bool in(int n, lint x){ return binary_search(b, b + n - 1, x); }
bool in(int n, lint s, lint e){ 
	int idx = lower_bound(b, b + n - 1, s) - b;
	if(idx < n - 1 && b[idx] <= e) return 1;
	return 0;
}

struct bit{
	lint tree[MAXN];
	void add(int x, int v){
		for(int i=x; i<MAXN; i+=i&-i){
			tree[i] += v;
		}
	}
	lint query(int x){
		lint ret = 0;
		for(int i=x; i; i-=i&-i){
			ret += tree[i];
		}
		return ret;
	}
	int kth(lint x){
		int pos = 0;
		for(int i=16; i>=0; i--){
			if(pos + (1<<i) < MAXN && tree[pos|(1<<i)] < x){
				pos |= (1<<i);
				x -= tree[pos];
			}
		}
		return pos + 1;
	}
}bit;

vector<int> ans;

void PUSH(int x){
	ans.push_back(x);
	bit.add(sz(ans), a[x]);
}

void SWAP(int x, int y){
	bit.add(x + 1, -a[ans[x]]);
	bit.add(y + 1, -a[ans[y]]);
	swap(ans[x], ans[y]);
	bit.add(x + 1, +a[ans[x]]);
	bit.add(y + 1, +a[ans[y]]);
}

void solve(int n, lint S, set<int> &idx){
	if(n == 0) return;
	if(n == 1){
		PUSH(*idx.begin());
		return;
	}
	int l = *idx.rbegin();
	idx.erase(l);
	if(!in(n, S - a[l])){
		if(in(n, S - a[l] + 1, S - 1)){
			solve(n - 1, S - a[l], idx);
			PUSH(l);
		}
		else{
			lint lst = b[n - 2];
			b[n - 2] = 1e18;
			solve(n - 1, S - a[l], idx);
			PUSH(l);
			b[n - 2] = lst;
			int kth = bit.kth(lst);
			if(bit.query(kth) == lst){
				SWAP(kth - 1, n - 1);
			}
		}
	}
	else{
		if(in(n, S - a[l] + 1, S - 1)){
			int rec = -1;
			for(auto &i : idx){
				if(!in(n, S - a[i]) && !in(n, S - a[i] - a[l])){
					rec = i;
					break;
				}
			}
			assert(rec != -1);
			idx.erase(rec);
			solve(n - 2, S - a[rec] - a[l], idx);
			PUSH(l); PUSH(rec);
		}
		else{
			solve(n - 1, S - a[l], idx);
			PUSH(l);
			SWAP(sz(ans) - 2, sz(ans) - 1);
		}
	}
}

int main(){
	map<int, int> mp;
	int m;
	scanf("%d %d",&n,&m);
	set<int> s;
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
		s.insert(i);
		mp[a[i]] = i + 1;
	}
	for(int i=0; i<m; i++) scanf("%lld",&b[i]);
	sort(a, a + n); sort(b, b + m);
	b[n-1] = 1e18;
	for(int j=n-2; j>=m; j--) b[j] = b[j+1] - 1;
	lint S = accumulate(a, a + n, 0ll);
	if(in(n, S)){
		puts("-1");
		return 0;
	}
	solve(n, S, s);
	for(auto &i : ans) printf("%d ", mp[a[i]]);
}
