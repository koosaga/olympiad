#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
typedef long long lint;

int n, p, a[MAXN], ptr[MAXN];
bitset<1000001> bs[205];
vector<int> gph[205], arr, orig;

int dfs(int x){
	int k = arr.size();
	arr.push_back(a[x]);
	orig.push_back(x);
	ptr[k] = 1;
	for(auto &i : gph[x]){
		ptr[k] += dfs(i);
	}
	return ptr[k];
}

vector<int> ans;

void trk(int x, int d){
	if(x == 0) return;
	if(d >= arr[x-1] && bs[x-1][d - arr[x-1]]){
		ans.push_back(orig[x-1]);
		trk(x-1, d - arr[x-1]);
		return;
	}
	for(int j=x-1; j>=0; j--){
		if(j + ptr[j] == x && bs[j][d]){
			trk(j, d);
			return;
		}
	}
}

int main(){
	cin >> n >> p;
	for(int i=1; i<=n; i++){
		int x;
		cin >> x >> a[i];
		gph[x].push_back(i);
	}
	dfs(0);
	bs[0][0] = 1;
	for(int i=0; i<=n; i++){
		bs[i+1] |= (bs[i] << arr[i]);
		bs[i + ptr[i]] |= bs[i];
	}
	for(int i=p; i>=0; i--){
		if(bs[n+1][i]){
			cout << i << endl;
			trk(n+1, i);
			sort(ans.begin(), ans.end());
			if(ans.size() && ans[0] == 0) ans.erase(ans.begin());
			cout << ans.size() << " ";
			for(auto &j : ans) cout << j << " ";
			return 0;
		}
	}
}
