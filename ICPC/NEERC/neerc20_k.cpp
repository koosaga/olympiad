#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 100005;
 
int n;
 
char buf[MAXN];
 
int main(){
	scanf("%d",&n);
	vector<pi> cnd;
	for(int i=1; i<=n; i++){
		int m; scanf("%d",&m);
		scanf("%s", buf);
		int cnt[3] = {};
		for(int j=0; buf[j]; j++){
			if(buf[j] <= '2') cnt[buf[j] - '0']++;
		}
		if(cnt[0] >= 1 && cnt[1] >= 1 && cnt[2] >= 2){
			cnd.emplace_back(m, i);
		}
	}
	if(sz(cnd)){
		sort(all(cnd));
		cout << cnd[0].second << endl;
	}
	else cout << 0 << endl;
}
 
