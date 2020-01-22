#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 505;

int n;
pi a[MAXN];
int sum[MAXN], suff[MAXN];

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> a[i].second >> a[i].first;
	sort(a, a + n);
	for(int i=0; i<n; i++){
		sum[i + 1] = sum[i] + a[i].second;
	}
	for(int i=n-1; i>=0; i--){
		suff[i] = sum[i + 1] - a[i].first;
		suff[i] = max(suff[i], suff[i + 1]);
	}
	int ret = 1e9;
	for(int i=0; i<n; i++){
		int over = 0;
		for(int j=0; j<i; j++){
			over = max(over, sum[j + 1] - a[j].first);
		}
		int new_over = 0;
		for(int j=i+1; j<=n; j++){
			int fst_over = max(0, sum[j] - a[i].first);
			int snd_over = max({over, new_over, suff[j]});
			if(fst_over >= snd_over) ret = min(ret, fst_over + snd_over);
			new_over = max(new_over, sum[j + 1] - a[i].second - a[j].first);
		}
	}
	cout << ret << endl;
}
