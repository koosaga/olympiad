#include"communication.h"
#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 200005;

struct node{
	vector<pi> v;
	node operator+(const node &a)const{
		node ret;
		for(auto &x : v) ret.v.push_back(x);
		for(auto &x : a.v) ret.v.push_back(x);
		sort(all(ret.v));
		return ret;
	}
	lint getSize(){
		lint ret = 0;
		for(auto &[x, y] : v) ret += y - x + 1;
		return ret;
	}
	node spliceLower(lint l){
		node ret;
		for(auto &[x, y] : v){
			lint d = min(l, y - x + 1);
			if(d > 0){
				ret.v.emplace_back(x, x + d - 1);
				l -= d;
			}
		}
		return ret;
	}
	node spliceUpper(lint l){
		node tmp = *this;
		reverse(all(tmp.v));
		for(auto &[x, y] : tmp.v) tie(x, y) = pi(-y, -x);
		tmp = tmp.spliceLower(l);
		reverse(all(tmp.v));
		for(auto &[x, y] : tmp.v) tie(x, y) = pi(-y, -x);
		return tmp;
	}
	bool contains(int p){
		for(auto &[x, y] : v){
			if(x <= p && p <= y) return true;
		}
		return false;
	}
	vector<lint> getSet(){
		vector<lint> ret;
		for(auto &[x, y] : v){
			for(lint i = x; i <= y; i++) ret.push_back(i);
		}
		return ret;
	}
};

void encode(int N, int X) {
	node C, D;
	C.v.emplace_back(1, N);
	while(C.getSize() + D.getSize() > 3){
		node CU = C.spliceLower((1 + C.getSize()) / 2);
		node CN = C.spliceUpper((C.getSize()) / 2);
		node DU = D.spliceLower((D.getSize()) / 2);
		node DN = D.spliceUpper((1 + D.getSize()) / 2);
		bool toSend = (CU.contains(X) || DU.contains(X));
		bool received = send(toSend);
		if(received == 1){
			D = CN;
			C = CU + DU;
		}
		else{
			D = CU;
			C = CN + DN;
		}
	}
	auto ans = (C + D).getSet();
	assert(sz(ans) <= 3);
	while(sz(ans) < 3){
		lint b = ans.back();
		ans.push_back(b);
	}
	for(int i = 0; i < sz(ans); i++){
		if(ans[i] == X){
			if(i == 0){
				send(0); send(0); send(0); send(0);
			}
			if(i == 1){
				send(0); send(1); send(1); send(0);
			}
			if(i == 2){
				send(1); send(1); send(1); send(1);
			}
			return;
		}
	}
	assert(0);
}

std::pair<int, int> decode(int N) {
	node C, D;
	C.v.emplace_back(1, N);
	while(C.getSize() + D.getSize() > 3){
		node CU = C.spliceLower((1 + C.getSize()) / 2);
		node CN = C.spliceUpper((C.getSize()) / 2);
		node DU = D.spliceLower((D.getSize()) / 2);
		node DN = D.spliceUpper((1 + D.getSize()) / 2);
		if(receive() == 1){
			D = CN;
			C = CU + DU;
		}
		else{
			D = CU;
			C = CN + DN;
		}
	}
	auto ans = (C + D).getSet();
	assert(sz(ans) <= 3);
	while(sz(ans) < 3){
		lint b = ans.back();
		ans.push_back(b);
	}
	vector<int> t(4);
	for(int i = 0; i < 4; i++) t[i] = receive();
	bool nocon = 1;
	int msk = 7;
	for(int i = 0; i < 3; i++){
		if(t[i] && t[i + 1]) msk &= 6;
		if(!t[i] && !t[i+1]) msk &= 3;
		if(t[i] == t[i + 1]) nocon = 0;
	}
	if(nocon) msk &= 5;
	pi ret(-1, 1);
	for(int i = 0; i < 3; i++){
		if((msk >> i) & 1){
			if(ret.first == -1) ret.first = ans[i];
			else ret.second = ans[i];
		}
	}
	return ret;
}
