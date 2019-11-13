#include <bits/stdc++.h>
using namespace std;
using lint = __int128;
using pi = pair<int, int>;
const int MAXN = 100005;
#define sz(v) ((int)(v).size())

void print(lint x){
	lint pw18 = 1;
	for(int i=0; i<18; i++) pw18 *= 10;
	if(x < pw18){
		cout << (long long)x << endl;
	}
	else{
		long long div = (x / pw18);
		cout << div;
		x %= pw18;
		printf("%018lld", (long long)x);
	}
}

struct kek{
	lint sqsum, sum, cnt;
	kek up(lint l){
		kek nxt;
		nxt.sqsum = sqsum + l * l * cnt + sum * 2 * l;
		nxt.sum = sum + cnt * l;
		nxt.cnt = cnt;
		return nxt;
	}
};

lint tot;
vector<pi> gph[MAXN];

kek dfs(int x, int p){
	if(sz(gph[x]) == 1){
		return (kek){0, 0, 1};
	}
	vector<kek> v;
	for(auto &i : gph[x]){
		if(i.second == p) continue;
		v.push_back(dfs(i.second, x).up(i.first));
	}
	kek ret = {0, 0, 0};
	lint summ = 0;
	lint tmp = 0;
	for(auto &i : v) tmp += i.cnt;
	for(auto &i : v){
		ret.sqsum += i.sqsum;
		ret.sum += i.sum;
		ret.cnt += i.cnt;
		tot += (tmp - i.cnt) * i.sqsum - i.sum * i.sum;
		summ += i.sum;
	}
	tot += summ * summ;
	return ret;
}

int main(){
	int n; scanf("%d",&n);
	for(int i=0; i<n-1; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		gph[s].emplace_back(x, e);
		gph[e].emplace_back(x, s);
	}
	for(int i=1; i<=n; i++){
		if(gph[i].size() > 1){
			dfs(i, -1);
			print(tot);
			return 0;
		}
	}
	assert(0);
}
