#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 5005;

int n, a[MAXN];
vector<int> b;
int cnt[2 * MAXN];
int fuck;

int match(){
	memset(cnt, 0, sizeof(cnt));
	for(int i=fuck; i<n; i++) cnt[a[i]]++;
	int ptr = 0;
	int cur = 0;
	int dap = 0;
	for(auto &j : b){
		while(ptr < j){
			cur += cnt[ptr++];
		}
		if(cur){
			cur--;
			dap++;
		}
	}
	return dap;
}

int main(){
	cin >> n;
	b.resize(n);
	for(int i=0; i<n; i++) cin >> a[i];
	for(int i=0; i<n; i++) cin >> b[i];
	sort(b.begin(), b.end());
	int x = match();
	int cur_done = 0;
	for(int i=0; i<n; i++){
		fuck = i + 1;
		auto winThres = lower_bound(b.begin(), b.end(), a[i] + 1) - b.begin();
		auto erase_and_try = [&](int p){
			int val = b[p];
			b.erase(b.begin() + p);
			int ret = match();
			if(val > a[i]) ret++;
			b.insert(b.begin() + p, val);
			return ret;
		};
		int dap = -1;
		if(winThres != b.size() && erase_and_try(winThres) + cur_done == x){
			int l = winThres, r = b.size() - 1;
			while(l != r){
				int m = (l + r + 1) / 2;
				if(erase_and_try(m) + cur_done == x) l = m;
				else r = m - 1;
			}
			dap = l;
		}
		else{
			int l = 0, r = winThres - 1;
			assert(winThres > 0);
			while(l != r){
				int m = (l + r + 1) / 2;
				if(erase_and_try(m) + cur_done == x) l = m;
				else r = m - 1;
			}
			dap = l;
		}
		printf("%d ", b[dap]);
		if(b[dap] > a[i]) cur_done++;
		b.erase(b.begin() + dap);
	}
}
