#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

struct disj{
	int pa[1000005];
	void init(int n){
		for(int i=1; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n, a[1000005];
vector<pi> v;
stack<pi> stk;

int main(){
	scanf("%d",&n);
	disj.init(n);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		int lst = a[i];
		while(!stk.empty() && stk.top().second >= a[i]){
			lst = max(lst, stk.top().second);
			disj.uni(stk.top().first, i);
			stk.pop();
		}
		stk.push(pi(i, lst));
	}
	int cnt = 0;
	for(int i=1; i<=n; i++){
		v.push_back(pi(disj.find(i), i));
	}
	sort(v.begin(), v.end());
	for(int i=0; i<v.size(); ){
		cnt++;
		int e = i;
		while(e < v.size() && v[e].first == v[i].first) e++;
		for(int j=i; j<e; j++) v[j].first = v[i].second;
		i = e;
	}
	sort(v.begin(), v.end());
	printf("%d\n", cnt);
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && v[e].first == v[i].first) e++;
		printf("%d ", e-i);
		for(int j=i; j<e; j++) printf("%d ", v[j].second);
		puts("");
		i = e;
	}
}