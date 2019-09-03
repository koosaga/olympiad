#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int main(){
	int n, k; scanf("%d %d",&n,&k);
	vector<pi> v(n + 1);
	for(int i=0; i<n; i++) scanf("%d %d",&v[i].first,&v[i].second);
	v[n].first = k;
	int sum = 0, cnt = 0;
	for(int i=0; i<n; i++){
		if(!v[i].second && sum + v[i].first < v[i+1].first){
			sum += v[i].first;
			cnt++;
		}
	}
	if(sum == 0) sum = 1;
	cout << cnt << endl << k - sum << endl;
}
