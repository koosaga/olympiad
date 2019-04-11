#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 200005;

struct disj{
	int pa[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

int n;
char sex[MAXN];
int dead[MAXN];
int seq[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%s", sex + i);
	int m; scanf("%d",&m);
	disj.init(n + m);
	while(m--){
		int x, y;
		scanf("%d",&x);
		if(x < 0){
			dead[-x] = 1;
		}
		else{
			n++;
			scanf("%d %s",&y,sex + n);
			disj.uni(y, n);
		}
	}
//	puts(sex + 1);
	scanf("%d",&m);
	while(m--){
		int x; scanf("%d",&x); scanf("%d",&seq[disj.find(x)]);
	}
	vector<int> v;
	for(int i=1; i<=n; i++) if(!dead[i]) v.push_back(disj.find(i));
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	// case 1. all v indicates one DNA
	bool good = 1;
	for(int i=1; i<v.size(); i++){
		if(seq[v[i-1]] == seq[v[i]] && seq[v[i]]) good = 1;
		else{
			good = 0;
			break;
		}
	}
	if(good){
		puts("YES");
		return 0;
	}
	// case 2. there is bad guy
	set<int> s;
	for(int i=0; i<v.size(); i++){
		if(seq[v[i]]) s.insert(seq[v[i]]);
	}
	if(s.size() > 1){
		puts("NO");
		return 0;
	}
	puts("POSSIBLY");
}
