#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, lint> pi;

struct disj{
	int pa[50005];
	void init(int n){
		for(int i=1; i<=n; i++) pa[i] = i;
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

int n, m, s[200005], e[200005];
unordered_set<unsigned> hack;

int chk[50005];

int main(){
	cin >> n >> m;
	for(int i=1; i<=n; i++){
		int k;
		scanf("%d",&k);
		for(int j=0; j<k; j++){
			int x;
			scanf("%d",&x);
			if(s[x]) e[x] = i;
			else s[x] = i;
		}
	}
	for(int i=1; i<=m; i++){
		if(s[i] > e[i]) swap(s[i], e[i]);
		unsigned t = (s[i] << 16) + e[i];
		hack.insert(t);
	}
	int q;
	cin >> q;
	while(q--){
		int k;
		scanf("%d",&k);
		vector<int> v(k);
		for(int i=0; i<k; i++){
			scanf("%d",&v[i]);
		}
		if(k >= 500){
			for(auto &i : v) chk[i] = 1;
			disj.init(n);
			int V = k, E = 0, C = k;
			for(int i=1; i<=m; i++){
				if(chk[s[i]] && chk[e[i]]){
					C -= disj.uni(s[i], e[i]);
					E++;
				}
			}
			printf("%d\n", C + E - V);
			for(auto &i : v) chk[i] = 0;
		}
		else{
			sort(v.begin(), v.end());
			disj.init(v.size());
			int V = k, E = 0, C = k;
			for(int i=0; i<k; i++){
				for(int j=0; j<i; j++){
					unsigned t = (v[j] << 16) + v[i];
					if(hack.find(t) != hack.end()){
						E++;
						C -= disj.uni(i+1, j+1);
					}
				}
			}
			printf("%d\n", C + E - V);
		}
	}
}

