#include <cstdio>
#include <cmath>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
typedef pair<double, double> pi;

int n, w, u, v, s, e;

map<double, int> mp;

int main(){
	scanf("%d %d %d %d %d %d",&n,&w,&u,&v,&s,&e);
	for(int i=0; i<n; i++){
		char str[5];
		scanf("%s",str);
		int t;
		scanf("%d",&t);
		while(t--){
			double a, b;
			scanf("%lf %lf",&a,&b);
			if(str[0] == 'E') b = -b;
			double st = b / u, ed = (a + b) / u;
			st -= (i+1) * 1.0 * w / v;
			ed -= i * 1.0 * w / v;
			if(st > e || ed < s) continue;
			st = max(st,1.0 * s);
			ed = min(ed,1.0 * e);
			mp[st]++;
			mp[ed]--;
		}
	}
	mp[s-1e-8]++;
	mp[s]--;
	mp[e]++;
	mp[e+1e-8]--;
	auto nxt = ++mp.begin();
	int cnt = 0;
	double ret = 0;
	for(auto &i : mp){
		cnt += i.second;
		if(cnt == 0){
			ret = max(ret, nxt->first - i.first);
		}
		nxt++;
		if(nxt == mp.end()) break;
	}
	printf("%f\n",ret);
}