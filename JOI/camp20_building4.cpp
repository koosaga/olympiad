#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1000005;

struct foo{
	int s, e, suml, sumr;
};

void my_ass(bool p){
	if(!p){
		puts("-1");
		exit(0);
	}
}

int n;
pi a[MAXN][2];
int ass[MAXN];

int main(){
	scanf("%d",&n);
	for(int j=0; j<2; j++){
		for(int i=1; i<=n*2; i++){
			scanf("%d",&a[i][j].first);
			a[i][j].second = j;
		}
	}
	for(int i=1; i<=2*n; i++) sort(a[i], a[i] + 2);
	for(int i=2; i<=2*n; i++){
		int j = i;
		while(j > 1 && a[j-1][1].first > a[j][1].first){
			a[j-1][1] = a[j-1][0];
			my_ass(a[j-1][1].first <= a[j][1].first);
			j--;
		}
	}
	for(int i=2*n-1; i>=1; i--){
		int j = i;
		while(j <= 2*n-1 && a[j][0].first > a[j+1][0].first){
			a[j+1][0] = a[j+1][1];
			my_ass(a[j][0].first <= a[j+1][0].first);
			j++;
		}
	}
	vector<foo> dap;
	for(int i=1; i<=2*n; ){
		int e = i;
		while(e+1 <= 2*n && a[e+1][0].first < a[e][1].first) e++;
		int cnt = 0;
		for(int j=i; j<=e; j++) cnt += a[j][1].second;
		int smin = cnt, smax = cnt;
		for(int j=i; j<=e; j++){
			cnt -= a[j][1].second;
			cnt += a[j][0].second;
			smax = max(smax, cnt);
			smin = min(smin, cnt);
		}
		dap.push_back({i, e, smin, smax});
		i = e + 1;
	}
	int dmin = 0, dmax = 0;
	for(auto &i : dap){
		dmin += i.suml;
		dmax += i.sumr;
	}
	my_ass(dmin <= n && n <= dmax);
	for(auto &i : dap){
		dmin -= i.suml;
		i.suml = min(n - dmin, i.sumr);
		dmin += i.suml;
	}
	for(auto &i : dap){
		int l = i.s, r = i.e;
		int cnt = 0;
		for(int j=l; j<=r; j++){
			cnt += a[j][1].second;
			ass[j] = a[j][1].second;
		}
		for(int j=l; j<=r; j++){
			if(i.suml == cnt) break;
			cnt -= a[j][1].second;
			cnt += a[j][0].second;
			ass[j] = a[j][0].second;
		}
	}
	for(int i=1; i<=2*n; i++) putchar(ass[i] + 'A');
}
