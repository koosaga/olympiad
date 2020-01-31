#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		int n;
		scanf("%d",&n);
		vector<int> v(n);
		for(auto &i : v) scanf("%d",&i);
		sort(all(v));
		if(n == 2){
			puts("1");
			continue;
		}
		int cnt = 0;
		while(cnt < n / 2 && v[cnt] + v[n - 1 - cnt] > 2) cnt++;
		printf("%d\n", cnt);
	}
}
