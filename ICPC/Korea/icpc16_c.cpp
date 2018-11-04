#include <cstdio>
#include <algorithm>
#include <bitset>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int k, n;
pi a[1000005];
int cnt[1000005], cur;

void add(int x){
	if (!cnt[x]) cur++;
	cnt[x]++;
}

void del(int x){
	cnt[x]--;
	if (!cnt[x]) cur--;
}

int half(int x){
	if (x < 0) return (x - 1) / 2;
	return x / 2;
}

int main(){
	scanf("%d %d", &k, &n);
	for (int i = 0; i < n; i++){
		scanf("%d %d", &a[i].first, &a[i].second);
	}
	sort(a, a + n);
	int e = 0;
	int dap = 1e9, pos = -1;
	for (int i = 0; i < n; i++){
		while (e < n && cur < k){
			add(a[e++].second);
		}
		if (cur == k){
			int p = half(a[i].first + a[e-1].first);
			int rad = max(a[e - 1].first - p, p - a[i].first);
			if (dap > rad){
				dap = rad;
				pos = p;
			}
		}
		del(a[i].second);
	}
	printf("%d", pos);
}