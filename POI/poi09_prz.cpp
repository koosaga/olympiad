#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 200005;

struct kek{
	int foo, bar, baz, idx;
	bool operator==(const kek &k)const{
		return make_tuple(foo, bar, baz) == make_tuple(k.foo, k.bar, k.baz);
	}
}tp[MAXN], aux[MAXN];

int a[MAXN];
int sfx[MAXN];
int n, m;
int cnt[MAXN];

void sort_it(){
	for(int i=1; i<=n+m; i++) tp[i].idx = i;

	int msz = max(n + m + 3, 105);
	memset(cnt, 0, sizeof(cnt));
	for(int i=1; i<=n+m; i++) cnt[tp[i].baz + 1]++;
	for(int i=1; i<=msz; i++) cnt[i] += cnt[i-1];
	for(int i=n+m; i; i--) aux[--cnt[tp[i].baz + 1]] = tp[i];
	for(int i=1; i<=n+m; i++) tp[i] = aux[i-1];

	memset(cnt, 0, sizeof(cnt));
	for(int i=1; i<=n+m; i++) cnt[tp[i].bar + 1]++;
	for(int i=1; i<=msz; i++) cnt[i] += cnt[i-1];
	for(int i=n+m; i; i--) aux[--cnt[tp[i].bar + 1]] = tp[i];
	for(int i=1; i<=n+m; i++) tp[i] = aux[i-1];

	memset(cnt, 0, sizeof(cnt));
	for(int i=1; i<=n+m; i++) cnt[tp[i].foo + 1]++;
	for(int i=1; i<=msz; i++) cnt[i] += cnt[i-1];
	for(int i=n+m; i; i--) aux[--cnt[tp[i].foo + 1]] = tp[i];
	for(int i=1; i<=n+m; i++) tp[i] = aux[i-1];

	for(int i=1; i<=n+m; ){
		int j = i;
		while(j <= n+m && tp[i] == tp[j]) j++;
		for(int k=i; k<j; k++){
			sfx[tp[k].idx] = i;
		}
		i = j;
	}
}

int main(){
	int tc; scanf("%d",&tc);
	for(int i=0; i<tc; i++){
		scanf("%d %d",&n,&m);
		bitset<105> cnt;
		memset(sfx, -1, sizeof(sfx));
		for(int i=1; i<=n+m; i++){
			scanf("%d",&a[i]);
			cnt[a[i]] = 1;
		}
		m += 1;
		a[n+m] = 101;
		rotate(a + n + 1, a + n + m, a + n + m + 1);
		int tt = cnt.count();
		for(int i=1; i<=n+m; i++){
			sfx[i] = a[i];
		}
		for(int i=2; i<=tt; i++){
			int k = 0, occ = 0;
			int cnt[105] = {};
			memset(cnt, 0, sizeof(cnt));
			k = n + m + 1; occ = 0;
			vector<int> fuck(n + m + 1);
			for(int j=n+m; j; j--){
				cnt[a[j]]++;
				if(cnt[a[j]] == 1) occ++;
				while(occ > i){
					k--;
					cnt[a[k]]--;
					if(cnt[a[k]] == 0) occ--;
				}
				if(occ == i) tp[j].foo = sfx[j], fuck[j] = k - 1;
				else tp[j] = {-1, -1, -1};
			}
			memset(cnt, 0, sizeof(cnt));
			int p = 0, q = 0;
			occ = 0;
			for(int j=1; j<=n+m && fuck[j]; j++){
				while(q < fuck[j]){
					q++;
					if(cnt[a[q]] == 0) occ++;
					cnt[a[q]]++;
				}
				while(occ >= i){
					p++;
					cnt[a[p]]--;
					if(cnt[a[p]] == 0) occ--;
				}
				tp[j].bar = sfx[p + 1];
				tp[j].baz = a[p];
			}
			sort_it();
			if(sfx[1] != sfx[n + 2]) break;
		}
		printf("%d\n", sfx[1] >= 0 &&  sfx[1] == sfx[n + 2]);
	}
}

