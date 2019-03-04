#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using llf = long double;
using lint = long long;
const int MAXN = 2505;

llf func[MAXN];
pi a[MAXN];
int n, k;

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll *dx1 * dy2 - 1ll * dy1 * dx2;
}

int main(){
	cin >> n >> k;
	for(int i=0; i<n; i++){
		llf x, y; 
		cin >> x >> y;
		int px = (int)round(x * 1000000L);
		int py = (int)round(y * 1000000L);
		a[i] = pi(px, py);
	}
	reverse(a, a + n);
	for(int i=k-2; i<=n; i++){
		func[i] = 1;
		for(int j=1; j<=k-2; j++){
			func[i] *= (llf)(i + 1 - j) / (n + 1 - j);
		}
		func[i] *= k * (k - 1);
		func[i] /= (n - k + 2) * (n - k + 1);
	}
	llf ret = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i == j) continue;
			int in_left = 0;
			if(i < j) in_left = n - (j - i + 1);
			else in_left = i - j - 1;
			ret += func[in_left] * ccw(pi(0, 0), a[i], a[j]);
		}
	}
	ret /= 1e12L;
	if(ret < 0) ret = -ret;
	printf("%.20Lf\n", ret / 2);
}
