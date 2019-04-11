#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;
using pi = pair<int, int>;

int d, n;
pi dp1[MAXN], dp2[MAXN], a[MAXN];
int trk1[MAXN], trk2[MAXN];

int main(){
	cin >> d >> n;
	for(int i=1; i<=n; i++) cin >> a[i].first >> a[i].second;
	a[n+1].first = d;
	for(int i=1; i<=n+1; i++){
		dp1[i] = dp2[i] = pi(1e9, 1e9);
		for(int j=i-1; j>=0; j--){
			if(a[j].first < a[i].first - 800) break;
			if(dp1[i] > dp1[j]){
				dp1[i] = dp1[j];
				trk1[i] = j;
			}
			if(dp2[i] > dp2[j]){
				dp2[i] = dp2[j];
				trk2[i] = j;
			}
		}
		dp1[i].first += a[i].second;
		dp1[i].second += 1;
		dp2[i].first += 1;
		dp2[i].second += a[i].second;
	}
	vector<int> v1, v2;
	for(int i=n+1; i; i=trk1[i]) v1.push_back(a[i].first);
	for(int i=n+1; i; i=trk2[i]) v2.push_back(a[i].first);
	reverse(v1.begin(), v1.end()); v1.pop_back();
	reverse(v2.begin(), v2.end()); v2.pop_back();
	for(auto &i : v1) cout << i << " ";
	cout << endl;
	for(auto &i : v2) cout << i << " ";
}
