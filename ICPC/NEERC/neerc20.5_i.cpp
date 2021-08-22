#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;
using lint = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int randint(int lb, int ub){ return uniform_int_distribution<int>(lb, ub)(rng); }

char buf[MAXN], buf2[MAXN];
int a[MAXN];

int main(){
	int n, m; scanf("%d %d",&n,&m);
	for(int i = 0; i < m; i++){
		scanf("%s", buf);
		int min_val = *min_element(a, a + n);
		double prob[2] = {};
		vector<int> v;
		for(int j = 0; j < n; j++){
			double val = exp(-50.0 * (a[j] - min_val) / max(min_val, 1));
			prob[buf[j] - '0'] += val;
		}
		double winprob = prob[0] / (prob[0] + prob[1]);
		int x = randint(0, (1 << 30) - 1);
		char ans[5] = "";
		ans[0] = x < winprob * (1 << 30) ? '0' : '1';
		cout << ans << endl;
		cin >> ans;
		for(int j = 0; j < n; j++){
			if(buf[j] != *ans) a[j]++;
		}
	}
}
