#include<bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;

set<int> gph[10005];
int n, m;

void rem(int s, int e){
	gph[s].erase(e);
	gph[e].erase(s);
}

int main(){
	int t; cin >> t;
	while(t--){
		for(int i=0; i<=10000; i++) gph[i].clear();
	cin >> n >> m;
	m += n;
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].insert(e);
		gph[e].insert(s);
	}
	int l = -1, r = -1;
	vector<int> a, b;
	for(int i=1; i<=n; i++){
		if(gph[i].size() == 2){
			a.push_back(i);
			l = *gph[i].begin();
			r = *gph[i].rbegin();
			a.push_back(l);
			b.push_back(r);
			rem(i, l);
			rem(i, r);
			break;
		}
	}
	while(a.size() + b.size() < n){
		if(gph[l].size() == 1){
			int nxtl = *gph[l].begin();
			rem(l, nxtl);
			a.push_back(nxtl);
			l = nxtl;
		}
		else if(gph[r].size() == 1){
			int nxtr = *gph[r].begin();
			rem(r, nxtr);
			b.push_back(nxtr);
			r = nxtr;
		}
		else{
			rem(l, r);
		}
	}
	while(b.size()){
		a.push_back(b.back());
		b.pop_back();
	}
	rotate(a.begin(), find(a.begin(), a.end(), 1), a.end());
	if(a[1] > a.back()){
		reverse(a.begin(), a.end());
		rotate(a.begin(), find(a.begin(), a.end(), 1), a.end());
	}
	for(auto &i : a) printf("%d ", i);
		puts("");
	}
}
