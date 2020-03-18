#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 200005;

int n, p, q, s;
int a[MAXN], b[MAXN];

bool trial(int D){
	vector<pi> ev;
	for(int i=0; i<p; i++){
		int st, ed;
		st = max(0, a[i] - D);
		ed = min(s - a[i], a[i] + D);
		if(st <= ed) ev.emplace_back(st, ed);
	}
	sort(all(ev));
	int p = 0;
	priority_queue<int, vector<int>, greater<int> > pq;
	int mtch = 0;
	for(int i=0; i<q; i++){
		while(p < sz(ev) && ev[p].first <= b[i]){
			pq.push(ev[p].second);
			p++;
		}
		while(sz(pq) && pq.top() < b[i]) pq.pop();
		if(sz(pq)){
			mtch++;
			pq.pop();
		}
	}
	return mtch >= n;
}

int main(){
	scanf("%d %d %d %d",&n,&p,&q,&s);
	for(int i=0; i<p; i++) scanf("%d",&a[i]);
	for(int i=0; i<q; i++) scanf("%d",&b[i]);
	sort(a, a + p);
	sort(b, b + q);
	int s = 0, e = 1e9;
	if(!trial(e)){
		puts("-1");
		return 0;
	}
	while(s != e){
		int m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m + 1;
	}
	cout << s << endl;
}

