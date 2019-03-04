#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100069;

struct sfx{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void solve(int n, char *str, int *sfx, int *rev){
		int p = 1;
		memset(ord, 0, sizeof(int) * (max(255, n) + 5));
		for(int i=0; i<n; i++){
			sfx[i] = i;
			ord[i] = str[i];
		}
		int pnt = 1;
		while(true){
			memset(cnt, 0, sizeof(int) * (max(255, n) + 5));
			for(int i=0; i<n; i++){
				cnt[ord[min(i + p, n)]]++;
			}
			for(int i=1; i<=n||i<=255; i++){
				cnt[i] += cnt[i-1];
			}
			for(int i=n-1; i>=0; i--){
				aux[--cnt[ord[min(i + p, n)]]] = i;
			}
			memset(cnt, 0, sizeof(int) * (max(255, n) + 5));
			for(int i=0; i<n; i++) cnt[ord[i]]++;
			for(int i=1; i<=n||i<=255; i++){
				cnt[i] += cnt[i-1];
			}
			for(int i=n-1; i>=0; i--){
				sfx[--cnt[ord[aux[i]]]] = aux[i];
			}
			if(pnt == n) break;
			pnt = 1;
			nord[sfx[0]] = 1;
			for(int i=1; i<n; i++){
				if(ord[sfx[i-1]] != ord[sfx[i]] || ord[sfx[i-1] + p] != ord[sfx[i] + p]){
					pnt++;
				}
				nord[sfx[i]] = pnt;
			}
			memcpy(ord, nord, sizeof(int) * n);
			p <<= 1;
		}
		for(int i=0; i<n; i++) rev[sfx[i]] = i;
	}
}sfxarray;

int n, k;
char str[MAXN];
int sfx[MAXN], rev[MAXN];

void solve(){
	scanf("%d %s",&k, str);
	n = strlen(str);
	sfxarray.solve(n, str, sfx, rev);
	rev[n] = -1;
	string ret;
	for(int i='z'; i>='a' && n > 0 && k > 0; i--){
		if(count(str, str + n, i) == 0) continue;
		int ptr = 0;
		while(ptr < n && str[ptr] == i) ptr++;
		for(int j=0; j<ptr; j++) ret.push_back(str[j]);
		vector<pi> block;
		for(int j=ptr; j<n; j++){
			if(str[j] == i){
				int e = j;
				while(e < n && str[e] == str[j]) e++;
				block.emplace_back(j, e);
				j = e;
			}
		}
		sort(block.begin(), block.end(), [&](const pi &a, const pi &b){
			return a.second - a.first > b.second - b.first;
		});
		if(block.size() <= k){
			k -= block.size();
			int cur_last = ptr;
			for(auto &j : block){
				for(int x = j.first; x < j.second; x++){
					ret.push_back(i);
				}
				cur_last = max(cur_last, j.second);
			}
			for(int j=cur_last; j<=n; j++){
				str[j - cur_last] = str[j];
				rev[j - cur_last] = rev[j];
			}
			n -= cur_last;
			if(k == 0 || i == 'a'){
				for(int j=0; j<n; j++) ret.push_back(str[j]);
				break;
			}
		}
		else{
			// last chance
			int kth_length = block[k - 1].second - block[k - 1].first;
			int shouldpick = 0;
			int cur_last = ptr;
			for(int j=0; j<k; j++){
				if(block[j].second - block[j].first != kth_length){
					cur_last = max(cur_last, block[j].second);
					for(int x = block[j].first; x < block[j].second; x++){
						ret.push_back(i);
					}
				}
				else{
					shouldpick++;
				}
			}
			vector<pi> nxt;
			for(auto &j : block){
				if(j.second - j.first == kth_length) nxt.push_back(j);
			}
			block = nxt;
			sort(block.begin(), block.end());
			for(int j=0; j<shouldpick * (kth_length); j++){
				ret.push_back(i);
			}
			pi max_suffix = pi(-1e9, -1e9);
			for(int j=shouldpick - 1; j < block.size(); j++){
				int cur_comparison = max(cur_last, block[j].second);
				max_suffix = max(max_suffix, pi(rev[cur_comparison], cur_comparison));
			}
			for(int j=max_suffix.second; j<n; j++){
				ret.push_back(str[j]);
			}
			break;
		}
	}
	puts(ret.c_str());
}


int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--) solve();
}
