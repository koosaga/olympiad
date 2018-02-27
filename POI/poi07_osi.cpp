#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 600005;

struct obj{
	bool type;
	long long arg1;
	long double arg2;
	bool operator==(const obj &t)const{
		if(t.type != type) return 0;
		if(t.type == 0) return t.arg1 == arg1;
		else return fabs(arg2 - t.arg2) < 1e-13;
	}
}b[MAXN];

obj dist(pi a, pi b){
	int dx = b.first - a.first;
	int dy = b.second - a.second;
	return (obj){false, 1ll * dx * dx + 1ll * dy * dy, -1};
}

const long double rad = 2 * acos(-1);

obj angle(pi a, pi b, pi c){
	long double v = atan2(c.second - a.second, c.first - a.first) 
		- atan2(b.second - a.second, b.first - a.first);
	while(v < 0) v += rad;
	while(v >= rad) v -= rad;
	return (obj){true, -1, v};
}

int n;
pi a[MAXN];
int ret[MAXN];

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		memset(ret, 0, sizeof(ret));
		scanf("%d",&n);
		for(int i=0; i<n; i++){
			scanf("%d %d",&a[i].first,&a[i].second);
			a[i+n+n] = a[i+n] = a[i];
		}
		a[3*n] = a[0];
		a[3*n+1] = a[1];
		for(int i=0; i<3*n; i++){
			b[2*i] = dist(a[i], a[i + 1]);
			b[2*i + 1] = angle(a[i + 1], a[i + 2], a[i]);
		}
		int p = 0, c = 0;
		for(int i=0; i<6*n; i++){
			int cur = 0;
			if(i <= p) cur = min(ret[2 * c - i], p - i);
			while(i - cur - 1 >= 0 && i + cur + 1 < 6*n && b[i-cur-1] == b[i+cur+1]){
				cur++;
			}
			ret[i] = cur;
			if(i + ret[i] > p){
				p = i + ret[i];
				c = i;
			}
		}
		int ans = 0;
		for(int i=2*n; i<4*n; i++){
			if(ret[i] >= n) ans++;
		}
		printf("%d\n", ans / 2);
	}
}

