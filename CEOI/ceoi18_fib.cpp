#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int mod = 1e9 + 7;
const int MAXN = 1000005;
 
struct mtrx{
	int a[2][2];
	mtrx operator*(const mtrx &m)const{
		mtrx ret;
		memset(ret.a, 0, sizeof(ret.a));
		for(int i=0; i<2; i++){
			for(int j=0; j<2; j++){
				for(int k=0; k<2; k++){
					ret.a[j][k] += 1ll * a[j][i] * m.a[i][k] % mod;
					if(ret.a[j][k] >= mod) ret.a[j][k] -= mod;
				}
			}
		}
		return ret;
	}
}E, pwr[MAXN];
 
mtrx num(int n){
	mtrx m;
	m.a[1][0] = m.a[1][1] = (n % 2 == 0);
	m.a[0][0] = (n + 1) / 2;
	m.a[0][1] = (n - 1) / 2;
	return m;
}
 
set<pi> s;
 
struct seg{
	vector<mtrx> tree;
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		tree.resize(2 * lim);
		fill(tree.begin(), tree.end(), E);
	}
	void add(int x, mtrx v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] * tree[2*x+1];
		}
	}
	mtrx query(){
		return tree[1];
	}
}seg;
 
struct seq{
	int type; 
	int pos;
	mtrx m;
};
 
vector<seq> instr;
vector<int> vect;
 
void batch(){
	sort(vect.begin(), vect.end());
	vect.resize(unique(vect.begin(), vect.end()) - vect.begin());
	seg.init(vect.size());
	for(auto &i : instr){
		if(i.type == 2){
			printf("%d\n", seg.query().a[0][0]);
		}
		else{
			int pos = lower_bound(vect.begin(), vect.end(), i.pos) - vect.begin();
			seg.add(pos, i.m);
		}
	}
}
 
void query(){
	instr.push_back({2, -1, E});
}
 
void add_query(int pos, mtrx m){
	vect.push_back(pos);
	instr.push_back({1, pos, m});
}
 
void rem_query(int pos){
	instr.push_back({1, pos, E});
}
 
void add(int x){ 
	if(x == 0) x = 1;
	if(x == -1) return;
	auto ins = [](pi x){
		auto itr = s.lower_bound(x);
		int pos = 0;
		if(itr != s.begin()) pos = prev(itr)->second;
		if(itr != s.end()) rem_query(pos);
		s.insert(x);
		add_query(pos, num(x.first - pos));
		if(x.first != x.second) add_query(x.first, pwr[(x.second - x.first) / 2]);
		itr = s.upper_bound(x);
		if(itr != s.end()){
			add_query(x.second, num(itr->first - x.second));
		}
	};
	auto rem = [](pi x){
		if(x.first != x.second) rem_query(x.first);
		auto itr = s.lower_bound(x);
        assert(itr != s.end());
		int pos = 0;
		if(itr != s.begin()) pos = prev(itr)->second;
		if(next(itr) != s.end()) rem_query(x.second);
		rem_query(pos);
		s.erase(x);
		itr = s.lower_bound(x);
		if(itr != s.end()){
			add_query(pos, num(itr->first - pos));
		}
	};
	auto it = s.upper_bound(pi(x + 1, -1));
	if(it != s.begin() && prev(it)->second >= x){
		auto intv = *--it;
		rem(intv);
		if(intv.first % 2 == x % 2){
			add(intv.second + 1);
			intv.second = x - 2;
			if(intv.first <= intv.second){
				auto l = s.lower_bound(pi(intv.second + 3, -1));
				auto nxt = pi(intv.first + 1, intv.second + 1);
				if(l != s.end() && l->first == intv.second + 3){
					nxt.second = l->second;
					rem(*l);
				}
				ins(nxt);
			}
			add(intv.first - 2);
		}
		else{
			ins(pi(intv.first, x - 1));
			add(intv.second + 1);
		}
	}
	else{
		auto nxt = it;
		if(nxt != s.begin()){
			nxt = prev(nxt);
			if(nxt->second == x - 1){
				auto prv = *nxt;
				rem(prv);
				if(prv.first != prv.second){
					prv.second -= 2;
					ins(prv);
				}
				add(x + 1);
				return;
			}
			if(nxt->second == x - 2){
				auto l = s.lower_bound(pi(x + 1, -1));
				if(l != s.end() && l->first == x + 1){
					int pos = l->second + 1;
					rem(*l);
					add(pos);
				}
				else if(l != s.end() && l->first == x + 2){
					auto it = *nxt;
					it.second = l->second;
                    auto Q = *nxt;
					rem(*l);
					rem(Q);
					ins(it);
				}
				else{
					auto it = *nxt;
					it.second += 2;
					rem(*nxt);
					ins(it);
				}
				return;
			}
		}
		auto l = s.lower_bound(pi(x + 1, -1));
		if(l->first == x + 1){
			int pos = l->second + 1;
			rem(*l);
			add(pos);
		}
		else if(l->first == x + 2){
			auto nxt = *l; nxt.first -= 2;
			rem(*l);
			ins(nxt);
		}
		else{
			ins(pi(x, x));
		}
	}
}
 
int main(){
	E.a[0][0] = E.a[1][1] = 1;
	pwr[0] = E;
	pwr[1] = num(2);
	for(int i=2; i<MAXN; i++) pwr[i] = pwr[i-1] * pwr[1];
	int n, x;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&x);
		add(x);
		query();
	}
	batch();
}
