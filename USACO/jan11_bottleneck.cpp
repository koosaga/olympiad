#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

vector<int> gph[100005];
int c[100005], m[100005], p[100005];
int n, k;

struct cmp{
	bool operator()(const pi &a, const pi &b){
		return a.first * b.second > b.first * a.second;
	}
};

bool cmp2(const pi &a, const pi &b){
	return a.first * b.second > b.first * a.second;
}

struct node{
	priority_queue<pi, vector<pi>, cmp> pq;
	lint sum;
	int size(){
		return pq.size();
	}
	void merge(node &n){
		if(pq.size() < n.pq.size()){
			swap(pq, n.pq);
		}
		sum += n.sum;
		while(!n.pq.empty()){
			pq.push(n.pq.top());
			n.pq.pop();
		}
	}
}val[100005];

void solve(int x){
	for(auto &i : gph[x]){
		solve(i);
		val[x].merge(val[i]);
	}
	lint resi = c[x];
	while(x != 1 && val[x].sum > m[x]){
		pi t = val[x].pq.top();
		val[x].pq.pop();
		val[x].sum -= t.second;
		resi += t.first;
	}
	while(resi > 0){
		pi t = pi(resi, m[x] - val[x].sum);
		if(val[x].pq.empty() || cmp2(val[x].pq.top(), t)){
			val[x].pq.push(t);
			val[x].sum = m[x];
			break;
		}
		else{
			resi += val[x].pq.top().first;
			val[x].sum -= val[x].pq.top().second;
			val[x].pq.pop();
		}
	}
}

pi t[10005];
lint ret[10005];

int main(){
	cin >> n >> k;
	for(int i=2; i<=n; i++){
		scanf("%d %d %d",&p[i], &c[i], &m[i]);
		gph[p[i]].push_back(i);
	}
	solve(1);
	for(int i=0; i<k; i++){
		scanf("%d",&t[i].first);
		t[i].second = i;
	}
	sort(t, t+k);
	lint cur = 0, sum = val[1].sum;
	for(int i=0; i<k; i++){
		while(!val[1].pq.empty()){
			pi tmp = val[1].pq.top();
			if(tmp.first <= tmp.second * t[i].first){
				cur += tmp.first;
				sum -= tmp.second;
				val[1].pq.pop();
			}
			else break;
		}
		ret[t[i].second] = sum * t[i].first + cur;
	}
	for(int i=0; i<k; i++) printf("%lld\n", ret[i]);
}
