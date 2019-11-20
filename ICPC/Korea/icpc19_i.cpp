#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;
const int MAXT = 270000;

int n;
pi a[MAXN];

bool trial(lint x){
	lint cur = -1;
	for(int i=0; i<n; i++){
		if(cur > a[i].second) return 0;
		cur = max(cur, 1ll * a[i].first) + x;
	}
	return 1;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x, y; scanf("%d %d",&x,&y);
		a[i] = pi(x, x + y);
	}
	sort(a, a + n);
	lint s = 0, e = 2e9;
	while(s != e){
		lint m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	cout << s << endl;
}
