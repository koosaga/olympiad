#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXT = 530000;
 
//const int _V = 0;
const int _VD = 1;
const int _VU = 2;
//const int _HR = 3;
const int _HUR = 4;
const int _HDL = 5;
//const int _HL = 6;
 
struct event{
	int arr, pos, x, y;
};
 
 
struct node{
	lint adj[3][3];
	void init(){
		memset(adj, 0x3f, sizeof(adj));
		adj[0][0] = adj[1][1] = adj[2][2] = 0;
	}
	node operator*(const node &n)const{
		node ret;
		memset(ret.adj, 0x3f, sizeof(ret));
		for(int i = 0; i < 3; i++){
			for(int j = 0; j < 3; j++){
				for(int k = 0; k < 3; k++){
					ret.adj[j][k] = min(ret.adj[j][k], adj[j][i] + n.adj[i][k]);
				}
			}
		}
		return ret;
	}
};
 
struct seg{
	node tree[MAXT];
	int lim;
	void init(vector<node> nd){
		for(lim = 1; lim < sz(nd); lim <<= 1);
		node big; big.init();
		fill(tree, tree + MAXT, big);
		for(int i = 0; i < sz(nd); i++) tree[i + lim] = nd[i];
		for(int i = lim-1; i; i--) tree[i] = tree[2*i] * tree[2*i+1];
	}
	void upd(int x, node v){
		x += lim;
		tree[x] = v;
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] * tree[2*x+1];
		}
	}
	lint query(){ return tree[1].adj[0][2]; };
}seg;
 
lint Do(int W, int H, vector<int> A, vector<int> X1,vector<int> Y1, vector<int> X2, vector<int> Y2){
	vector<lint> V(H + 1), VD(H + 1), VU(H + 1);
	vector<lint> HR(H + 1), HUR(H + 1), HDL(H + 1), HL(H + 1);
	vector<event> ev;
	for(int i = 0; i < sz(A); i++){
		if(pi(X1[i], Y1[i]) > pi(X2[i], Y2[i])){
			swap(X1[i], X2[i]);
			swap(Y1[i], Y2[i]);
		}
		if(X1[i] == X2[i]){
			HR[Y2[i]] += A[i];
			HL[Y1[i]] += A[i];
			HDL[Y1[i]] += A[i];
			ev.push_back({_HUR, X1[i] + 1, Y2[i], +A[i]});
			ev.push_back({_HDL, X1[i], Y1[i], -A[i]});
		}
		else{
			V[Y1[i]] += A[i];
			VU[Y1[i]] += A[i];
			ev.push_back({_VD, X2[i] + 1, Y1[i], +A[i]});
			ev.push_back({_VU, X1[i], Y1[i], -A[i]});
		}
	}
	auto makenode = [&](int p){
		node ret;
		ret.adj[0][0] = HR[p] + V[p];
		ret.adj[0][1] = HUR[p] + VD[p];
		ret.adj[0][2] = 0;
		ret.adj[1][1] = HUR[p] + HDL[p] + VD[p] + VU[p];
		ret.adj[1][2] = HDL[p] + VU[p];
		ret.adj[2][2] = HL[p] + V[p];
		ret.adj[1][0] = ret.adj[2][0] = ret.adj[2][1] = 1e18;
		return ret;
	};
	sort(all(ev), [&](const event &a, const event &b){
		return a.pos < b.pos;
	});
	lint ret = 1e18;
	int p = 0;
	vector<node> nd(H + 1);
	for(int i = 0; i < H+1; i++) nd[i] = makenode(i);
	seg.init(nd);
	for(int i = 0; i <= W; i++){
		while(p < sz(ev) && ev[p].pos == i){
			if(ev[p].arr == _VD) VD[ev[p].x] += ev[p].y;
			if(ev[p].arr == _VU) VU[ev[p].x] += ev[p].y;
			if(ev[p].arr == _HUR) HUR[ev[p].x] += ev[p].y;
			if(ev[p].arr == _HDL) HDL[ev[p].x] += ev[p].y;
			nd[ev[p].x] = makenode(ev[p].x);
			seg.upd(ev[p].x, nd[ev[p].x]);
			p++;
		}
		ret = min(ret, seg.query());
	}
	return accumulate(all(A), 0ll) - ret;
}
 
lint get_max_score(int W, int H, vector<int> A, vector<int> X1,vector<int> Y1, vector<int> X2, vector<int> Y2){
	W *= 2;
	H *= 2;
	for(auto &i : X1) i *= 2;
	for(auto &i : Y1) i *= 2;
	for(auto &i : X2) i *= 2;
	for(auto &i : Y2) i *= 2;
	lint ans = Do(W, H, A, X1, Y1, X2, Y2);
	for(int i = 0; i < sz(A); i++){
		Y1[i] = H - Y1[i];
		Y2[i] = H - Y2[i];
	}
	ans = max(ans, Do(W, H, A, X1, Y1, X2, Y2));
	return ans;
}

