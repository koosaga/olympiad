#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400005;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

struct bit{
	int tree[MAXN];
	void clear(){
		memset(tree, 0, sizeof(tree));
	}
	void add(int x, int v){
		for(int i=x+1; i<MAXN; i+=i&-i){
			tree[i] += v;
		}
	}
	int query(int x){
		int ret = 0;
		for(int i=x+1; i; i-=i&-i) ret += tree[i];
		return ret;
	}
}bit;

struct fuck{
	int type, where, how;
};

int main(){
	int tc; cin >> tc;
	while(tc--){
		bit.clear();
		int n, q; scanf("%d %d",&n,&q);
		vector<int> a(n + 1);
		vector<fuck> fuk;
		fuk.push_back({1, 0, n});
		while(q--){
			static char buf[5];
			scanf("%s", buf);
			if(*buf == 'Q'){
				int x; scanf("%d",&x);
				fuk.push_back({0, a[x], -1});
			}
			else{
				int x, y; scanf("%d %d",&x,&y);
				fuk.push_back({1, a[x], -1});
				a[x] += y;
				fuk.push_back({1, a[x], +1});
			}
		}
		vector<int> crd;
		for(auto &i : fuk) crd.push_back(i.where);
		sort(crd.begin(), crd.end());
		crd.resize(unique(crd.begin(), crd.end()) - crd.begin());
		for(auto &i : fuk){
			if(i.type == 0){
				auto l = lower_bound(crd.begin(), crd.end(), i.where) - crd.begin();
				printf("%d\n", -bit.query(l) + n + 1);
			}
			else{
				auto l = lower_bound(crd.begin(), crd.end(), i.where) - crd.begin();
				bit.add(l, i.how);
			}
		}
		bit.clear();
	}
}
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())

int n, m;
pi a[MAXN], b[MAXN];

int main(){
	int t; scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		for(int i=0; i<n; i++) scanf("%d %d",&a[i].second,&a[i].first);
		scanf("%d",&m);
		for(int i=0; i<m; i++) scanf("%d %d",&b[i].second,&b[i].first);
		sort(a, a + n);
		sort(b, b + m);
		int ans = 1e9;
		for(int i=0; i<2; i++){
			int ptr = 0, foo = 1e9;
			for(int i=0; i<n; i++){
				while(ptr < m && b[ptr].first <= a[i].first){
					foo = min(foo, -b[ptr].first + b[ptr].second);
					ptr++;
				}
				ans = min(ans, foo + a[i].first - a[i].second);
			}
			reverse(a,a+n); reverse(b,b+m);
			for(int i=0; i<n; i++) a[i].first *= -1;
			for(int i=0; i<m; i++) b[i].first *= -1;
		}
		cout << ans << endl;
	}
}
