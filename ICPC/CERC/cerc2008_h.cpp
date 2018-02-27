#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 100005;

struct intv{
	int s, e, idx;
	bool operator<(const intv &i)const{
		return e < i.e;
	}
}a[MAXN];

int n, c, col[MAXN];
vector<intv> v[MAXN];

bool insec(intv a, intv b){
	return max(a.s, b.s) < min(a.e, b.e);
}

bool find_kempe_chain(vector<intv> &l, vector<intv> &r, intv cur, intv obj){
	while(true){
		auto k = upper_bound(r.begin(), r.end(), (intv){-1, cur.e, -1});
		if(k == r.end() || !insec(*k, cur)) return true;
		cur = *k;
		if(insec(obj, cur)) return false;
		k = upper_bound(l.begin(), l.end(), (intv){-1, cur.e, -1});
		if(k == l.end() || !insec(*k, cur)) return true;
		cur = *k;
		if(cur.e >= obj.e) return false;
	}
}

int solve(){
	set<int> s;
	priority_queue<pi> pq;
	for(int i=n-1; i>=0; i--){
		while(!pq.empty() && pq.top().first >= a[i].e){
			s.insert(col[pq.top().second]);
			pq.pop();
		}
		if(s.size() == 0){
			s.insert(c++);
		}
		col[a[i].idx] = *s.begin();
		s.erase(s.begin());
		pq.push(pi(a[i].s, a[i].idx));
	}
	if(col[0] != col[1]) return c;
	intv st, ed;
	for(int i=0; i<n; i++){
		if(a[i].idx == 0) st = a[i];
		if(a[i].idx == 1) ed = a[i];
		v[col[a[i].idx]].push_back(a[i]);
	}
	for(int i=0; i<c; i++){
		if(i != col[0] && find_kempe_chain(v[col[0]], v[i], st, ed)) return c;
	}
	return c + 1;
}

int main(){
	int tc;
	scanf("%d",&tc);
	while(tc--){
		scanf("%d",&n);
		for(int i=0; i<n; i++) scanf("%d %d",&a[i].s,&a[i].e), a[i].idx = i;
		if(a[1].e <= a[0].s) swap(a[0].idx, a[1].idx);
		sort(a, a+n);
		printf("%d\n", solve());
		for(int i=0; i<c; i++) v[i].clear();
		c = 0;
	}
}
