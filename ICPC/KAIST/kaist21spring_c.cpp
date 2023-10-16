#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;

int main(){
	int n, m;
	scanf("%d %d",&n,&m);
	vector<int> min_card(n, 1e9);
	for(int i = 0; i < m; i++){
		int sz; scanf("%d",&sz);
		for(int j = 0; j < sz; j++){
			int v; scanf("%d",&v); v--;
			min_card[v] = min(min_card[v], sz);
		}
	}
	double ret = 0;
	for(int i = 0; i < n; i++){
		if(min_card[i] < 1e8) ret = max(ret, 1 - 1.0 / min_card[i]);
	}
	printf("%.10f\n", ret);
}