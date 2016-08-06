#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, k, a[1000005];
pi s[1000005];

int p, q, x[1000005], y[1000005], rx[1000005], ry[1000005];
int nxtl[1000005], nxtr[1000005];

int l[1000005], r[1000005];

bool trial(int p){
	bool chk[1000005] = {};
	for(int i=1; i<l[p]; i++){
		chk[a[i]] = 1;
	}
	for(int i=r[p]+1; i<=n; i++){
		if(chk[a[i]]) return 1;
	}
	return 0;
}

int chkl[1000005], chkr[1000005];

vector<int> solve(){
	int tried = 0, cnt = 0;
	int lp = 0, rp = 0;
	vector<int> dap;
	for(int i=1; i<=n; i++){
		if(rx[a[i]] == p){
			if(l[i] <= 0 || r[i] > n) continue;
			if(!tried){
				for(int j=1; j<l[i]; j++){
					chkl[a[j]]++;
				}
				for(int j=r[i]+1; j<=n; j++){
					chkr[a[j]]++;
					if(chkl[a[j]] && chkr[a[j]]) cnt++;
				}
				lp = l[i] - 1, rp = r[i] + 1;
				tried = 1;
			}
			else{
				while(lp < l[i]-1){
					chkl[a[++lp]]++;
					if(chkl[a[lp]] == 1 && chkr[a[lp]]) cnt++;
				}
				while(rp <= r[i]){
					chkr[a[rp]]--;
					if(chkl[a[rp]] && !chkr[a[rp]]) cnt--;
					rp++;
				}
			}
			if(cnt) dap.push_back(i);
		}
	}
	return dap;
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		s[i] = pi(a[i], i);
	}
	sort(s+1, s+n+1);
	scanf("%d %d",&p,&q);
	for(int i=1; i<=p; i++){
		scanf("%d",&x[i]);
		rx[x[i]] = i;
	}
	for(int i=1; i<=q; i++){
		scanf("%d",&y[i]);
		ry[y[i]] = i;
	}
	memset(nxtl, -1, sizeof(nxtl));
	memset(nxtr, -1, sizeof(nxtr));
	for(int i=1; i<=n; i++){
		if(rx[a[i]] == 1){
			nxtl[i] = i;
		}
		if(rx[a[i]] > 1){
			int nc = x[rx[a[i]] - 1];
			auto t = lower_bound(s+1, s+n+1, pi(nc, i));
			t--;
			if(t->first == nc){
				nxtl[i] = t->second;
			}
		}
		if(ry[a[i]] == 1){
			nxtr[i] = i;
		}
		if(ry[a[i]] > 1){
			int nc = y[ry[a[i]] - 1];
			auto t = upper_bound(s+1, s+n+1, pi(nc, i));
			if(t->first == nc){
				nxtr[i] = t->second;
			}
		}
	}
	for(int i=1; i<=n; i++){
		if(nxtl[i] == -1) l[i] = -1e9;
		else if(nxtl[i] == i) l[i] = i;
		else l[i] = l[nxtl[i]];
	}
	for(int i=n; i; i--){
		if(nxtr[i] == -1) r[i] = 1e9;
		else if(nxtr[i] == i) r[i] = i;
		else r[i] = r[nxtr[i]];
	}
	vector<int> dap = solve();
	printf("%d\n", dap.size());
	for(auto &i : dap) printf("%d ", i);
}

