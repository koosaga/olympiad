#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
const int MAXN = 2005;

int dist(pi a, pi b){
	int dx = b.first - a.first;
	int dy = b.second - a.second;
	return dx * dx + dy * dy;
}

int n, q;
pi a[MAXN];

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	for(int i=0; i<q; i++){
		pi p; scanf("%d %d",&p.first,&p.second);
		vector<int> v;
		int curmin = 1e9;
		for(int j=0; j<n; j++){
			if(curmin > dist(p, a[j])){
			    curmin = dist(p, a[j]);
				v.clear();
			}
			if(curmin == dist(p, a[j])){
				v.push_back(j + 1);
			}
		}
		if(v.size() >= 3) printf("POINT");
		else if(v.size() == 2) printf("LINE");
		else printf("REGION");
		if(v.size() <= 2){
			for(auto &i : v) printf(" %d", i);
		}
		puts("");
	}
}

