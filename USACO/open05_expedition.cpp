#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, l, p;
pi a[10005];
priority_queue<int> pq;

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
	}
	cin >> a[n].first >> p;
	for(int i=0; i<n; i++){
		a[i].first = a[n].first - a[i].first;
	}
	sort(a, a+n+1);
	int cnt = 0, curp = 0;
	for(int i=0; i<=n; i++){
		p -= (a[i].first - curp);
		curp = a[i].first;
		while(p < 0){
			if(pq.empty()) return !puts("-1");
			p += pq.top();
			pq.pop();
			cnt++;
		}
		pq.push(a[i].second);
	}
	cout << cnt;
}
