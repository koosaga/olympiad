#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int MAXN = 5005;

int n;
pi a[MAXN];
int pfx[MAXN], sfx[MAXN];

int dist(pi a, pi b){
	int x = b.first - a.first, y = b.second - a.second;
	return x * x + y * y;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%d %d",&a[i].first,&a[i].second);
	int st = 0, cur = -1;
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			int nxt = dist(a[i], a[j]);
			if(nxt > cur){
				cur = nxt;
				st = i;
			}
		}
	}
	swap(a[0], a[st]);
	sort(a + 1, a + n, [&](const pi &p, const pi &q){
		return dist(a[0], p) < dist(a[0], q);
	});
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++) pfx[i] = max(pfx[i], dist(a[i], a[j]));
		for(int j=i+1; j<n; j++) sfx[i] = max(sfx[i], dist(a[i], a[j]));
	}
	for(int i=1; i<n; i++){
		pfx[i] = max(pfx[i], pfx[i-1]);
		sfx[n-1-i] = max(sfx[n-1-i], sfx[n-i]);
	}
	double ans = 1e9;
	for(int i=0; i<n-1; i++) ans = min(ans, sqrt(pfx[i]) + sqrt(sfx[i + 1]));
	printf("%.10f\n", ans);
}
