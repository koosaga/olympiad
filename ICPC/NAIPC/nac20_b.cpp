#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 200005;

int k, a[7];
int should_cover = 0;
vector<int> hits[6];

lint dfs(int x, int msk){
	if(x == k){
		return (should_cover & msk) == should_cover;
	}
	lint ret = 0;
	for(auto &i : hits[a[x]]){
		if(i & msk) continue;
		ret += dfs(x + 1, i | msk);
	}
	return ret;
}

int main(){
	int n;
	cin >> n >> k;
	int already = 0;
	for(int i=0; i<n; i++){
		string s; cin >> s;
		for(int j=0; j<n; j++){
			if(s[j] == 'O') should_cover |= (1<<(i*n+j));
			if(s[j] == 'X') already |= (1<<(i*n+j));
		}
	}
	for(int i=0; i<k; i++) cin >> a[i];
	for(int i=1; i<=n; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				if(j + i - 1 < n){
					int msk = 0;
					for(int x=0; x<i; x++){
						msk |= (1<<((j+x)*n+k));
					}
					hits[i].push_back(msk);
				}
				if(i != 1 && k + i - 1 < n){
					int msk = 0;
					for(int x=0; x<i; x++){
						msk |= (1<<(j*n+k+x));
					}
					hits[i].push_back(msk);
				}
			}
		}
	}
	cout << dfs(0, already) << endl;
}
