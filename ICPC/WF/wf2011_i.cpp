#include <cstdio>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;
typedef pair<int,int> pi;

int n;
pi a[100005];

vector<pi> ladd, ldel, hadd, hdel;
multiset<int> low, high;

bool trial(int x){
	low.clear();
	high.clear();
	ladd.clear();
	ldel.clear();
	hadd.clear();
	hdel.clear();
	for(int i=0; i<n; i++){
		if(a[i].first < 0 && a[i].second < 0){
			hadd.push_back(pi(a[i].first - x, a[i].second + x));
			hdel.push_back(pi(a[i].first + x + 1, a[i].second + x));
		}
		if(a[i].first < 0 && a[i].second >= 0){
			ladd.push_back(pi(a[i].first - x, a[i].second - x));
			ldel.push_back(pi(a[i].first + x + 1, a[i].second - x));
		}
		if(a[i].first >= 0 && a[i].second < 0){
			hadd.push_back(pi(a[i].first - x, a[i].second + x));
			hdel.push_back(pi(a[i].first + x + 1, a[i].second + x));
		}
		if(a[i].first >= 0 && a[i].second >= 0){
			ladd.push_back(pi(a[i].first - x, a[i].second - x));
			ldel.push_back(pi(a[i].first + x + 1, a[i].second - x));
		}
	}
	low.insert(x + 1);
	high.insert(-x - 1);
	int p1 = 0, p2 = 0, p3 = 0, p4 = 0;
	for(int i=-x; i<=x; i++){
		while(p1 < ladd.size() && ladd[p1].first <= i){
			low.insert(ladd[p1++].second);
		}
		while(p2 < hadd.size() && hadd[p2].first <= i){
			high.insert(hadd[p2++].second);
		}
		while(p3 < ldel.size() && ldel[p3].first <= i){
			low.erase(low.find(ldel[p3++].second));
		}
		while(p4 < hdel.size() && hdel[p4].first <= i){
			high.erase(high.find(hdel[p4++].second));
		}
		if(*low.begin() > *high.rbegin() + 1) return 1;
	}
	return 0;
}

void solve(){
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	sort(a,a+n);
	int s = 0, e = 1e6+1;
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	if(s > 1e6) puts("never");
	else printf("%d\n",s+1);
}

int main(){
	int t = 1;
	while(1){
		scanf("%d",&n);
		if(n == -1) break;
		printf("Case %d: ",t++);
		solve();
	}
}
