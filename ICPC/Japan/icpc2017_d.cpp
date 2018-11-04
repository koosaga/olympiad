#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using pi = pair<int, int>;
using lint = long long;
using real_t = long double;

lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

lint dist(pi a, pi b){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	return 1ll * dx1 * dx1 + 1ll * dy1 * dy1;
}

real_t getPer(vector<pi> H){
	real_t ret = 0;
	for(int i=0; i<H.size(); i++) ret += sqrt(dist(H[i], H[(i+1)%H.size()]));
	return ret;
}

vector<pi> getCH(vector<pi> &pnt){
	swap(pnt[0], *min_element(pnt.begin(), pnt.end()));
	sort(pnt.begin() + 1, pnt.end(), [&](const pi &p, const pi &q){
		lint tmp = ccw(pnt[0], p, q);
		if(tmp != 0) return tmp > 0;
		return dist(pnt[0], p) < dist(pnt[0], q);
	});
	vector<pi> H;
	for(auto &i : pnt){
		while(H.size() >= 2 && ccw(H[H.size() - 2], H.back(), i) <= 0) H.pop_back();
		H.push_back(i);
	}
	return H;
}

const int INF = 420420420;

real_t rem_one(vector<pi> pnt, pi NO1 = pi(INF, INF), pi NO2 = pi(INF, INF)){ 
	// Running time = O(|pnt|)
	// Condition : Set is not fully collinear
	vector<pi> H = getCH(pnt);
	int ptr = 1;
	real_t total = getPer(H);
	real_t ans = total;
	if(H.size() <= 8){
		for(auto &i : H){
			if(i == NO1 || i == NO2) continue;
			vector<pi> punk;
			for(auto &j : pnt){
				if(i == j) continue;
				punk.push_back(j);
			}
			ans = min(ans, getPer(getCH(punk)));
		}
		return ans;
	}
	for(int i=1; i<H.size(); i++){
		if(H[i] == NO1 || H[i] == NO2) continue;
		while(ptr < pnt.size() && H[i] != pnt[ptr]) ptr++;
		assert(ptr != pnt.size());
		int st = ptr - 1, ed = ptr + 1;
		while(st > 0 && pnt[st] != H[i-1]) st--;
		while(ed < pnt.size() && pnt[ed] != H[(i+1)%H.size()]) ed++;
		pi L = H[i-1], M = H[i], R = H[(i+1)%H.size()];
		real_t delta = -sqrt(dist(L, M)) - sqrt(dist(M, R));
		vector<pi> TH;
		for(int j=st; j<=ed; j++){
			auto i = pnt[j % pnt.size()];
			if(i == M) continue;
			while(TH.size() >= 2 && ccw(TH[TH.size()-2], TH.back(), i) <= 0) TH.pop_back();
			TH.push_back(i);
		}
		for(int i=1; i<TH.size(); i++) delta += sqrt(dist(TH[i-1], TH[i]));
		ans = min(ans, total + delta);
	}
	if(NO1 != pnt[0] && NO2 != pnt[0]){
		pnt.erase(pnt.begin());
		ans = min(ans, getPer(getCH(pnt)));
	}
	return ans;
}

int main(){
	int n;
	scanf("%d",&n);
	vector<pi> A(n);
	for(int i=0; i<n; i++) scanf("%d %d",&A[i].first,&A[i].second);
	vector<pi> H = getCH(A);
	real_t P = getPer(H);
	real_t ret = P;
	if(H.size() <= 8){
		for(auto &i : H){
			vector<pi> punk;
			for(auto &j : A){
				if(i == j) continue;
				punk.push_back(j);
			}
			ret = min(ret, rem_one(punk));
		}
		printf("%.10Lf\n", P - ret);
		return 0;
	}
	// Case 1
	{
		vector<pi> no_one_punkty_set(A.begin() + 1, A.end());
		ret = min(ret, rem_one(no_one_punkty_set));
	}
	// Case 2
	{
		int ptr = 1;
		vector<real_t> ans(H.size());
		for(int i=1; i<H.size(); i++){
			while(ptr < A.size() && H[i] != A[ptr]) ptr++;
			assert(ptr != A.size());
			int st = ptr - 1, ed = ptr + 1;
			while(st > 0 && A[st] != H[i-1]) st--;
			while(ed < A.size() && A[ed] != H[(i+1)%H.size()]) ed++;
			real_t delta = -sqrt(dist(H[i-1], H[i])) - sqrt(dist(H[i], H[(i+1)%H.size()]));
			vector<pi> TH;
			for(int j=st; j<=ed; j++){
				if(j == ptr) continue;
				auto i = A[j % A.size()];
				while(TH.size() >= 2 && ccw(TH[TH.size()-2], TH.back(), i) <= 0) TH.pop_back();
				TH.push_back(i);
			}
			for(int i=1; i<TH.size(); i++) delta += sqrt(dist(TH[i-1], TH[i]));
			ans[i] = delta;
		}
		real_t pfx = 1e18;
		for(int i=1; i<H.size(); i++){
			if(i - 2 >= 1) pfx = min(pfx, ans[i-2]);
			ret = min(ret, P + pfx + ans[i]);
		}
	}
	// Case 3-1
	{
		int ptr = 1;
		for(int i=2; i<H.size(); i++){
			while(ptr < A.size() && H[i-1] != A[ptr]) ptr++;
			assert(ptr != A.size());
			int st = ptr - 1, ed = ptr + 1;
			while(st > 0 && A[st] != H[i-2]) st--;
			while(ed < A.size() && A[ed] != H[(i+1)%H.size()]) ed++;
			real_t delta =  -sqrt(dist(H[i-2], H[i-1]))
				-sqrt(dist(H[i-1], H[i])) 
				-sqrt(dist(H[i], H[(i+1)%H.size()]));
			vector<pi> TH;
			for(int j=st; j<=ed; j++){
				auto PUNKTY = A[j % A.size()];
				if(PUNKTY == H[i-1] || PUNKTY == H[i]) continue;
				while(TH.size() >= 2 && ccw(TH[TH.size()-2], TH.back(), PUNKTY) <= 0) TH.pop_back();
				TH.push_back(PUNKTY);
			}
			for(int i=1; i<TH.size(); i++) delta += sqrt(dist(TH[i-1], TH[i]));
			ret = min(ret, P + delta);
		}
	}
	// Case 3-2
	{
		int ptr = 1;
		for(int i=1; i<H.size(); i++){
			while(ptr < A.size() && H[i] != A[ptr]) ptr++;
			assert(ptr != A.size());
			int st = ptr - 1, ed = ptr + 1;
			while(st > 0 && A[st] != H[i-1]) st--;
			while(ed < A.size() && A[ed] != H[(i+1)%H.size()]) ed++;
			auto L = H[i-1];
			auto M = H[i];
			auto R = H[(i+1)%H.size()];
			vector<pi> TH = {L, R};
			for(int j=st; j<=ed; j++){
				if(j == ptr) continue;
				auto i = A[j % A.size()];
				if(ccw(L, R, i) >= 0 || i == M) continue;
				TH.push_back(i);
			}
			assert(TH.size() >= 2);
			if(TH.size() == 2){
				real_t delta = -sqrt(dist(L, M)) - sqrt(dist(M, R)) + sqrt(dist(L, R));
				ret = min(ret, P + delta); 
			}
			else{
				real_t delta = -sqrt(dist(L, M)) - sqrt(dist(M, R)) - sqrt(dist(L, R));
				// we send TH to rem_one : Is precondition satisfied??
				// size of TH is obviously geq than 3...
				delta += rem_one(TH, L, R);
				ret = min(ret, P + delta);
			}
		}
	}
	printf("%.10Lf\n", P - ret);
}