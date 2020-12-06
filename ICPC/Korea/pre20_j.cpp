#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

int n, k;
lint a[250005];
priority_queue<pi> pq;
int cnt[250005];

struct node{
	int sum;
	node *ls, *rs;
	node(){
		ls = rs = NULL;
		sum = 0;
	}
}*root[250005];

void init(int s, int e, node *p){
	if(s == e) return;
	p->ls = new node();
	p->rs = new node();
	int m = (s+e)/2;
	init(s, m, p->ls);
	init(m+1, e, p->rs);
}

void add(int pos, int s, int e, node *prev, node *cur){
	if(s == e){
		cur->sum = prev->sum + 1;
		return;
	}
	int m = (s+e)/2;
	if(pos <= m){
		cur->ls = new node();
		cur->rs = prev->rs;
		add(pos, s, m, prev->ls, cur->ls);
	}
	else{
		cur->ls = prev->ls;
		cur->rs = new node();
		add(pos, m+1, e, prev->rs, cur->rs);
	}
	cur->sum = cur->ls->sum + cur->rs->sum;
}

int search(node *prev, node *cur, int s, int e, int x){
	if(s == e) return s;
	int m = (s+e)/2;
	int tmp = cur->ls->sum - prev->ls->sum;
	if(x <= tmp){
		return search(prev->ls, cur->ls, s, m, x);
	}
	return search(prev->rs, cur->rs, m+1, e, x - tmp);
}

vector<lint> v;

lint getkth(int s, int e, int x){
	if(e - s + 1 <= x) return 1e17;
	return v[search(root[s], root[e+1], 0, n, x+1)];
}

int main(){
	scanf("%d %d",&n,&k);
	v.push_back(0);
	for(int i=1; i<=n; i++){
		scanf("%lld",&a[i]);
		a[i] += a[i-1];
		v.push_back(a[i]);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	for(int i=0; i<=n; i++){
		a[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();
	}
	root[0] = new node();
	init(0, n, root[0]);
	for(int i=0; i<=n; i++){
		root[i+1] = new node();
		add(a[i], 0, n, root[i], root[i+1]);  
	}
	for(int i=1; i<=n; i++){
		lint t = getkth(0, i - 1, cnt[i]);
		pq.push(pi(v[a[i]] - t, i));
	}
	while(k-- && !pq.empty()){
		pi t = pq.top();
		pq.pop();
		printf("%lld ", t.first);
		int pos = t.second;
		cnt[pos]++;
		pq.push(pi(v[a[pos]] - getkth(0, pos - 1, cnt[pos]), pos));
	}
}
