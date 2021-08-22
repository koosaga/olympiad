#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 4005;

int n, a[MAXN], b[MAXN];
void one(){
	for(int i = 0; i < n; i++) swap(a[2*i], a[2*i+1]);
}

void two(){
	for(int i = 0; i < n; i++) swap(a[i], a[i+n]);
}

int main(){
	scanf("%d",&n);
	for(int i = 0; i < 2*n; i++) scanf("%d",&a[i]);
	int ret = 1e9;
	for(int i = 0; i < 2; i++){
		memcpy(b, a, sizeof(b));
		int ans = 1e9;
		for(int j = 0; j < 2*n; j++){
			if(is_sorted(a, a + 2*n)){
				ans = 2*j;
				break;
			}
			if(i) one();
			else two();
			if(is_sorted(a, a + 2*n)){
				ans = 2*j+1;
				break;
			}
			if(i) two();
			else one();
		}
		memcpy(a, b, sizeof(a));
		ret = min(ret, ans);
	}
	if(ret > 1e7) ret = -1;
	cout << ret << endl;
}
