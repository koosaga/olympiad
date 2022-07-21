#include <bits/stdc++.h>
using namespace std;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using lint = long long;
using pi = pair<lint, lint>;
 
typedef pair<int,int> pii;
typedef long double ld;
typedef long long ll;
typedef pair<ld,int> pdi;
typedef pair<ld,ld> pdd;
const int INF = 0x3f3f3f3f;
 
int N, Q;
vector<ll> C[50100];
vector<ll> P[50100];
 
struct SInfo {
	ld e, al, be;
};
vector<SInfo> gi[50100];
vector<SInfo> hi[50100];
 
vector<SInfo> g, h;
ld xcsum = 0;
 
int keys[50100];
vector<SInfo> merge(vector<SInfo> seg[]) {
	priority_queue<pdi, vector<pdi>, greater<>> pq;
	ld als = 0, bes = 0;
	for (int i=0;i<N;i++) {
		keys[i] = 0;
		if (!seg[i].empty()) {
			als += seg[i][0].al;
			bes += seg[i][0].be;
			pq.emplace(seg[i][0].e, i);
		}
	}
	vector<SInfo> res;
	while(!pq.empty()) {
		pdi tmp = pq.top(); pq.pop();
		ld e = tmp.first;
		int idx = tmp.second;
		res.push_back({e, als, bes});
		als -= seg[idx][keys[idx]].al;
		bes -= seg[idx][keys[idx]].be;
		keys[idx]++;
		if (keys[idx]<seg[idx].size()) {
			als += seg[idx][keys[idx]].al;
			bes += seg[idx][keys[idx]].be;
			pq.emplace(seg[idx][keys[idx]].e, idx);
		}
	}
	return res;
}
 
pdd eval(vector<SInfo> &f, ld x) {
	int s = 0, e = (int)f.size()-1;
	while(s<=e) {
		int m = (s+e)/2;
		if (f[m].e >= x) e = m-1;
		else s = m+1;
	}
	return {f[s].al, f[s].be};
}
 
const ld EPS = 1e-16;
 
int find_loc(vector<SInfo> &g, ll x) {
	int s = 0, e = (int)g.size()-1;
	while(s<=e) {
		int m = (s+e)/2;
		if (g[m].e > -EPS) e = m-1;
		else if (g[m].al / sqrt(max(-g[m].e, (ld)EPS)) + g[m].be <= x) s = m+1;
		else e = m-1;
	}
	return s;
}
 
ld query(ll x) {
	if (x>=xcsum-EPS) return 0;
	int idx = find_loc(g, x);
	if (idx==(int)g.size()-1) return 0;
	ld sans = -50;
//	printf("%lld! -> %d\n",x,idx);
	if (idx>0) {
		ld s = min(g[idx-1].e,-EPS), e = min(g[idx].e, -EPS);
		for (int bsc = 0; bsc < 60; bsc++) {
			ld m = (s + e) / 2;
			if (g[idx].al / sqrt(max(-m, (ld) EPS)) + g[idx].be <= x) s = m;
			else e = m;
		}
		sans = s;
	}
//	printf("%Lf\n",sans);
	pdd hc = eval(h, sans);
	return hc.first * sqrt(max(-sans,(ld)EPS)) + hc.second;
}
 
int main(){
	scanf("%d%d",&N,&Q);
	for (int i=0;i<N;i++) {
		int k;
		scanf("%d",&k);
		for (int j=0;j<k;j++) {
			int c;
			scanf("%d",&c);
			C[i].push_back(c);
		}
		for (int j=0;j<k;j++) {
			int p;
			scanf("%d",&p);
			P[i].push_back(p);
		}
	}
	for (int i=0;i<N;i++) {
		ll sumC = 0, sumP = 0;
		for (ll &c: C[i]) sumC+=c;
		for (ll &p: P[i]) sumP+=p;
		vector<int> ord(P[i].size(),0);
		iota(ord.begin(),ord.end(),0);
		sort(ord.begin(),ord.end(),[&i](int a, int b){
			return C[i][a]*P[i][b]<C[i][b]*P[i][a];
		});
		vector<ll> temp;
		for (int &j : ord) temp.push_back(C[i][j]);
		C[i] = temp;
		temp.clear();
		for (int &j : ord) temp.push_back(P[i][j]);
		P[i] = temp;
		int k = (int)P[i].size();
		for (int j=0;j<P[i].size();j++) {
			if (C[i][j]*sumP>=sumC*P[i][j]) {
				k=j;
				break;
			}
		}
		int n = (int)P[i].size();
		for (int r=0;r<n-k;r++) {
			ld a = 0, b = 0, c = 0, d = 0;
			for (int j=k;j<k+r;j++) a += (ld)P[i][j]/sumP;
			a -= 1;
			for (int j=k;j<k+r;j++) b += sumC*(ld)P[i][j]/sumP;
			for (int j=0;j<k+r;j++) b -= C[i][j];
			for (int j=k+r;j<n;j++) b += C[i][j];
			c = sumC;
			for (int j=0;j<k;j++) d += (ld)P[i][j]/sumP;
			for (int j=k+r;j<n;j++) d -= (ld)P[i][j]/sumP;
			auto f = [&a,&b,&c,&d](ld x) {
				return (a*x+b)/(x+c)+d;
			};
			auto fp = [&a,&b,&c](ld x) {
				return (a*c-b)/(x+c)/(x+c);
			};
			ld xp = 0, xc = 0;
			xp = (r==0?0:(ld)sumP*C[i][k+r-1]/P[i][k+r-1]-sumC);
			xc = (ld)sumP*C[i][k+r]/P[i][k+r]-sumC;
			if (r==0) {
				gi[i].push_back({fp(xp), 0, 0});
				hi[i].push_back({fp(xp), 0, f(0)});
			} else {
				gi[i].push_back({fp(xp),0,xp});
				hi[i].push_back({fp(xp), 0, f(xp)});
			}
			gi[i].push_back({fp(xc),sqrt(max(b-a*c,(ld)0.0)),-c});
			hi[i].push_back({fp(xc),sqrt(max(b-a*c,(ld)0.0)), a+d});
			if (r==n-k-1) {
//				printf("%Lf!!\n",xc);
				gi[i].push_back({0, 0, xc});
				hi[i].push_back({0,0,f(xc)});
				xcsum += xc;
			}
		}
	}
	g = merge(gi);
	h = merge(hi);
//	for (int i=0;i<g.size();i++) {
//		printf("%Lf, %Lf\n",g[i].e, g[i].al/sqrt(max(-g[i].e,(ld)EPS))+g[i].be);
//	}
	for (int i=0;i<Q;i++) {
		ll x;
		scanf("%lld",&x);
		printf("%.30Lf\n",query(x));
	}
 
	return 0;
}
