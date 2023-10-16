#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 200005;

struct solver{
	set<int> s;
	void add(int x, int v){
		if(v == 1) s.insert(x);
		else s.erase(x);
	}
	lint query(){
		return *s.rbegin() - sz(s) + 1;
	}
	void init(int n, char *str){
		for (int i = 0; i < n; i++) if(str[i] == 'O') add(i, +1);
	}
}s1, s2;

char str[MAXN];
int main(){
	int n; scanf("%d",&n);
	scanf("%s", str);
	s1.init(n, str);
	reverse(str, str + n);
	s2.init(n, str);
	reverse(str, str + n);
	int q; scanf("%d",&q);
	while(q--){
		int k; scanf("%d",&k);
		k--;
		if(str[k] == 'O'){
			s1.add(k, -1);
			s2.add(n-1-k, -1);
		}
		else{
			s1.add(k, +1);
			s2.add(n-1-k, +1);
		}
		str[k] = 'O' + 'X' - str[k];
		printf("%lld\n", min(s1.query(), s2.query()));
	}
}
