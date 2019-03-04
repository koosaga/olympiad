#include <bits/stdc++.h>
using namespace std;
const int MAXN = 200005;
using lint = long long;
using pi = pair<int, int>;

int n;
int cnt[2][MAXN];

int main(){
	scanf("%d",&n);
	lint dap = 0;
	for(int i=0; i<n*2; i++){
		int x, y; scanf("%d %d",&x,&y);
		if(x < 1){
			dap += 1 - x;
			x = 1;
		}
		if(x > n){
			dap += x - n;
			x = n;
		}
		if(y < 1){
			dap += 1 - y;
			y = 1;
		}
		if(y > 2){
			dap += y - 2;
			y = 2;
		}
		cnt[y-1][x]++;
	}
	for(int i=1; i<=n; i++){
		// free flow
		cnt[0][i]--;
		cnt[1][i]--;
		// cost 1 flow which I never have to negate
		if(1ll * cnt[0][i] * cnt[1][i] < 0){
			if(cnt[0][i] < 0){
				int delt = min(-cnt[0][i], cnt[1][i]);
				dap += delt;
				cnt[0][i] += delt; cnt[1][i] -= delt;
			}
			else{
				int delt = min(-cnt[1][i], cnt[0][i]);
				dap += delt;
				cnt[0][i] -= delt; cnt[1][i] += delt;
			}
		}
		// abandon center edge, and proceed recursively
		dap += abs(cnt[0][i]) + abs(cnt[1][i]);
		cnt[0][i+1] += cnt[0][i];
		cnt[1][i+1] += cnt[1][i];
	}
	cout << dap << endl;
}
