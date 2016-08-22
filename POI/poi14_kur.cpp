#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, q, a[500005];
int cnt[500005];
int cnt2[500005];

int count_range(lint val, int s, int e){
	return upper_bound(cnt + cnt2[val-1], cnt + cnt2[val], e) - lower_bound(cnt + cnt2[val-1], cnt + cnt2[val], s);
}

int tree[1050000];

void init(int s, int e, int p){
	if(s == e){
		tree[p] = a[s];
		return;
	}
	int m = (s+e)/2;
	init(s, m, 2*p);
	init(m+1, e, 2*p+1);
	if(count_range(tree[2*p], s, e) > count_range(tree[2*p+1], s, e)){
		tree[p] = tree[2*p];
	}
	else{
		tree[p] = tree[2*p+1];
	}
}

int lis[40], sz;
void query(int s, int e, int ps, int pe, int p){
	if(e < ps || pe < s) return;
	if(s <= ps && pe <= e){
		lis[sz++] = tree[p];
		return;
	}
	int pm = (ps + pe) / 2;
	query(s, e, ps, pm, 2*p);
	query(s, e, pm+1, pe, 2*p+1);
}

int main(){
	vector<pi> v;
	scanf("%d %d",&n,&q);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		v.push_back(pi(a[i], i));
		cnt2[a[i]]++;
	}
	for(int i=1; i<=n; i++) cnt2[i] += cnt2[i-1];
	sort(v.begin(), v.end());
	int p = 0;
	for(auto &i : v){
		cnt[p++] = i.second;
	}
	init(1, n, 1);
	for(int i=1; i<=q; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		sz = 0;
		query(s, e, 1, n, 1);
		bool f = 0;
		sort(lis, lis + sz);
		for(int i=0; i<sz; i++){
			if(i && lis[i-1] == lis[i]) continue;
			if(e - s + 1 < 2 * count_range(lis[i], s, e)){
				printf("%d\n", lis[i]);
				f = 1;
				continue;
			}
		}
		if(!f) puts("0");
	}
}