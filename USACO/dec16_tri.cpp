#include <bits/stdc++.h>
using namespace std;
typedef long long lint;

struct pi{ 
	int first, second, num, idx;
	bool operator<(const pi &p)const{
		if(first == p.first) return second < p.second;
		return first < p.first;
	}
	bool operator>(const pi &p)const{
		if(first == p.first) return second > p.second;
		return first > p.first;
	}
};

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

int n, cnt[305];
pi a[305];

struct bit{
	int tree[305];
	void clear(){ memset(tree, 0, sizeof(tree)); }
	void add(int x, int v){
		while(x <= n){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

vector<pi> ang[305];
int rnum[305][305];

void solve(int s, int e){
	vector<pi> v;
	for(int j=1; j<n; j++){
		int k = rnum[e][s] + n - j;
		k %= n-1;
		if(ccw(a[e], ang[e][k], a[s]) > 0){
			v.push_back(ang[e][k]);
		}
	}
	for(int i=0; i<v.size(); i++){
		v[i].idx = rnum[s][v[i].num] - rnum[s][e] + n - 1;
		v[i].idx %= n-1;
		v[i].idx++;
	}
	bit.clear();
	for(int i=0; i<v.size(); i++){
		cnt[bit.query(v[i].idx)]++;
		bit.add(v[i].idx, 1);
	}
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> a[i].second;
		a[i].num = i;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i != j) ang[i].push_back(a[j]);
		}
		sort(ang[i].begin(), ang[i].end(), [&](const pi &p, const pi &q){
			if(p > a[i] && q > a[i]){
				return ccw(a[i], p, q) > 0;
			}
			else if(p < a[i] && q < a[i]){
				return ccw(a[i], p, q) > 0;
			}
			else{
				return (p > a[i]) > (q > a[i]);
			}
		});
		for(int j=0; j<n-1; j++){
			rnum[i][ang[i][j].num] = j;
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<i; j++){
			solve(i, j);
			solve(j, i);
		}
	}
	for(int i=0; i<n-2; i++) cout << cnt[i]/3 << endl;
}

