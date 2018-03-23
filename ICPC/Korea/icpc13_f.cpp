#include <cstdio>
#include <algorithm>
using namespace std;
typedef pair<int,int> pi;

int n, k;
pi a[10005];

int cnt(int x){
	int ret = 0;
	int nowfind = 0, st = 0, ed = 0;
	for(int i=0; i<n; i++){
		if(!nowfind){
			st = a[i].second - x;
			ed = a[i].second + x;
			nowfind = 1;
			ret++;
		}
		st = max(st, a[i].second - x);
		ed = min(ed, a[i].second + x);
		if(st > ed){
			i--;
			nowfind = 0;
		}
	}
	return ret;
}

void solve(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
		a[i].second *= 2;
	}
	sort(a,a+n);
	int s = 0, e = 5e8;
	while(s != e){
		int m = (s+e)/2;
		if(cnt(m) <= k) e = m;
		else s = m+1;
	}
	printf("%.1f\n",0.5 * s);
}

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		solve();
	}
}