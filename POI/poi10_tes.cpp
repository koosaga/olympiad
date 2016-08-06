#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
 
int n;
vector<int> pos[1000005];
 
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		pos[x].push_back(i);
	}
	int q;
	scanf("%d",&q);
	while(q--){
		scanf("%d",&n);
		int p = 0;
		bool bad = 0;
		for(int i=1; i<=n; i++){
			int x;
			scanf("%d",&x);
			auto t = upper_bound(pos[x].begin(), pos[x].end(), p);
			if(t == pos[x].end()){
				bad = 1;
				continue;
			}
			p = *t;
		}
		puts(bad ? "NIE" : "TAK");
	}
}