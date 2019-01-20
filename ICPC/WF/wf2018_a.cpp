#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
using real_t = long double;
const int MAXN = 1000005;

struct event{
	lint time;
	int type;
	int pos;
	int which;
	real_t prob;
	bool operator<(const event &e)const{
		return make_tuple(time, type, pos) < make_tuple(e.time, e.type, e.pos);
	}
};

vector<event> ev;
real_t dp[MAXN], cache[MAXN];

int main(){
	int m;
	scanf("%d %*d %*lld", &m);
	for(int i=0; i<m; i++){
		int a, b;
		lint s, t;
		real_t x;
		scanf("%d %d %lld %lld %Lf",&a,&b,&s,&t,&x);
		ev.push_back({s, 0, a, i, x});
		ev.push_back({t, 1, b, i, x});
	}
	sort(ev.rbegin(), ev.rend());
	dp[1] = 1;
	for(int i=0; i<ev.size(); ){
		if(ev[i].type == 1){
			cache[ev[i].which] = dp[ev[i].pos];
			i++;
			continue;
		}
		else{
			int e = i;
			while(e < ev.size() && make_tuple(ev[i].time, ev[i].pos) == make_tuple(ev[e].time, ev[e].pos)) e++;
			vector<pair<real_t, real_t>> cnds;
			real_t ans = dp[ev[i].pos];
			for(int j=i; j<e; j++){
				ans = max(ans, cache[ev[j].which] * ev[j].prob + dp[ev[i].pos] * (1 - ev[j].prob));
			}
			dp[ev[i].pos] = ans; 
			i = e;
		}
	}
	printf("%.20f\n", (double)dp[0]);
}
