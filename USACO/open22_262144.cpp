#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 270000;

int n, a[MAXN];
vector<vector<int>> Linc, Rinc;
struct number{
	int s, e;
	int pivot;
	int lp, rp;
};

lint ret;

void promote(number &n, int newPivot){
	int Q = (newPivot - n.pivot);
	if(Q == 0) return;
	n.pivot = newPivot;
	if(Q > 20){
		if(sz(Linc[n.lp]) > 1) Linc[n.lp].resize(1);
		if(sz(Rinc[n.rp]) > 1) Rinc[n.rp].resize(1);
		return;
	}
	int K = (1 << Q);
	if(sz(Linc[n.lp]) > 1){
		vector<int> nb;
		for(int i = 0; i < sz(Linc[n.lp]); i += K) nb.push_back(Linc[n.lp][i]);
		Linc[n.lp] = nb;
	}
	if(sz(Rinc[n.rp]) > 1){
		vector<int> nb;
		for(int i = 0; i < sz(Rinc[n.rp]); i += K) nb.push_back(Rinc[n.rp][i]);
		Rinc[n.rp] = nb;
	}
}

int pa[MAXN];

int find(int x){
	return pa[x] = (pa[x] == x ? x : find(pa[x]));
}

int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int n; cin >> n;
	for(int i = 0; i < n; i++) cin >> a[i];
	Linc.resize(n + 10);
	Rinc.resize(n + 10);
	vector<number> ds(n + 1);
	for(int i = 0; i <= n; i++){
		ds[i].pivot = -1557;
		ds[i].lp = ds[i].rp = i;
		ds[i].s = i;
		ds[i].e = i - 1;
	}
	vector<int> idx(n); iota(all(idx), 0);
	shuffle(all(idx), mt19937(0x69420));
	stable_sort(all(idx), [&](const int &p, const int &q){
		return a[p] < a[q];
	});
	iota(pa, pa + n + 1, 0);
	for(auto &pos : idx){
		auto p = find(pos), q = find(pos + 1);
		auto L = ds[p], R = ds[q];
		int s = ds[p].s, e = ds[q].e;
		promote(L, a[pos]);
		promote(R, a[pos]);
		auto up = [&](int x){
			int y = 0;
			while((1 << y) < x) y++;
			return y;
		};
		auto powerOfTwoGreaterThan = [&](int p){
			return (1 << up(p)) + 1;
		};
		if(sz(Rinc[L.rp]) < sz(Linc[R.lp])){
			for(int i = 0; i <= sz(Rinc[L.rp]); i++){
				int s1 = (i < sz(Rinc[L.rp]) ? Rinc[L.rp][i] : s);
				int e1 = (i > 0 ? Rinc[L.rp][i - 1] : pos + 1) - 1;
				auto access = [&](int j){
					if(j < 0) return pos;
					if(j >= sz(Linc[R.lp])) return e + 1;
					return Linc[R.lp][j];
				};
				int ptr = a[pos] + up(i + 1);
				for(int j = 0; j <= sz(Linc[R.lp]); j++){
					int k = powerOfTwoGreaterThan(i + j + 1) - 2 - i;
					ret += 1ll * (e1 - s1 + 1) * (access(k) - access(j - 1)) * ptr;
					j = k;
					ptr++;
				}
			}
		} else {
			for(int j = 0; j <= sz(Linc[R.lp]); j++){
				int s2 = (j > 0 ? Linc[R.lp][j - 1] : pos);
				int e2 = (j < sz(Linc[R.lp]) ? Linc[R.lp][j] : (e+1)) - 1;
				auto access = [&](int i){
					if(i < 0) return pos + 1;
					if(i >= sz(Rinc[L.rp])) return s;
					return Rinc[L.rp][i];
				};
				int ptr = a[pos] + up(j + 1);
				for(int i = 0; i <= sz(Rinc[L.rp]); i++){
					int k = powerOfTwoGreaterThan(i + j + 1) - 2 - j;
					ret += 1ll * (e2 - s2 + 1) * (access(i - 1) - access(k)) * ptr;
					i = k;
					ptr++;
				}
			}
		}

		number ret;
		ret.pivot = a[pos];
		ret.lp = L.lp;
		ret.rp = R.rp;

		if(sz(Linc[ret.lp]) == 0 || Linc[ret.lp].back() < pos) Linc[ret.lp].push_back(pos);
		for(auto &i : Linc[R.lp]) Linc[ret.lp].push_back(i);

		if(sz(Rinc[ret.rp]) == 0 || Rinc[ret.rp].back() > pos + 1) Rinc[ret.rp].push_back(pos + 1);
		for(auto &i : Rinc[L.rp]) Rinc[ret.rp].push_back(i);

		pa[q] = p;
		ds[p] = ret;
		ds[p].s = s;
		ds[p].e = e;
	}
	cout << ret << endl;
}
