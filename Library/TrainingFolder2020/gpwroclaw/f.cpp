#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1000005;

int ret[MAXN];
pi a[MAXN];

int main(){
	int tc; scanf("%d",&tc);
	while(tc--){
		memset(ret, 0, sizeof(ret));
		int n;
		scanf("%d",&n);
		for(int i=0; i<n; i++){
			scanf("%d",&a[i].first);
			a[i].second = i + 1;
		}
		sort(a, a + n);
		int k = a[n-1].first;
		bool good = 1;
		for(int i=0; i<n; ){
			int e = i;
			while(e < n && a[e].first == a[i].first) e++;
			vector<int> v;
			for(int j=0; j<a[i].first; j++){
				if(!ret[j]){
					v.push_back(j);
				}
			}
			if(sz(v) < e - i){
				good = 0;
				break;
			}
			for(int j=i; j<e; j++){
				for(int x=v[j-i]; x<k; x+=a[j].first) ret[x] = a[j].second;
			}
			i = e;
		}
		if(!good) puts("NIE");
		else{
			puts("TAK");
			printf("%d ", k);
			for(int i=0; i<k; i++) printf("%d ", max(ret[i], 1));
			puts("");
		}
	}
}

