#include <algorithm>
#include <iostream>
#include <queue>
#include <cassert>
#include <cstring>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int B = 1000;

#include "grader.h"
/*
namespace ggwp{
	int n, k, ds[5500];
	int a[1010101];
	int ptr, pass;
	int ptr2;
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	void stream(int x){
		if(ptr2 == 0){
			for(int i=0; i<k; i++) pq.emplace(a[i], i);
		}
		else{
			assert(ptr2 + k  - 1< n);
			pq.emplace(a[ptr2 + k - 1], ptr2 + k - 1);
		}
		while(!pq.empty() && pq.top().second < ptr2) pq.pop();
		ptr2++;
		int minv = pq.top().first;
		if(minv != x){
			cout << ptr2 << endl;
			assert(0);
		}
	}
int cntG, cntS;
}

int get(int index){ ggwp::cntG++; return ggwp::ds[index]; }
void set(int index, int value){ ggwp::cntS++; ggwp::ds[index] = value; }
void shoutMinimum(int output){ ggwp::stream(output); }
int getTrainLength(){ return ggwp::n; }
int getWindowLength(){ return ggwp::k; }
int getCurrentCarIndex(){ return ggwp::ptr; }
int getCurrentPassIndex(){ return ggwp::pass; }*/

void setPtr(int x){ set(5499, x); }
void setRs(int x){ set(5498, x); }
void setRe(int x){ set(5497, x); }
void setRenew(int x){ set(5496, x); }
int getPtr(){ return get(5499); }
int getRs(){ return get(5498); }
int getRe(){ return get(5497); }
int getRenew(){ return get(5496); }

pi interval(int i){
	i = max(i, 0);
	int st = (max(i - getWindowLength() + 1, 0) + B - 1) / B;
	int ed = min(i, getTrainLength() - getWindowLength()) / B;
	return pi(st, ed);
}

void make_ds(){
	int n = getTrainLength();
	int k = getWindowLength();
	int x = getPtr() + 1;
	assert(x < 2001);
	setPtr(0);
	pi ans[2005];
	pi vect[2005];
	fill(vect, vect + 2005, pi(0, -1));
	fill(ans, ans + 2005, pi(2e9, 2e9));
	for(int i=0; i<n; i++){
		auto pIntv = interval(i - 1);
		auto cIntv = interval(i);
		if(cIntv.first > cIntv.second) continue;
		if(pIntv != cIntv){
			setPtr(getPtr() + 1);
		}
		vect[getPtr()] = cIntv;
	}
	for(int i=0; i<x; i++) ans[i] = pi(get(2 * i), get(2 * i + 1));
	for(int i=0; i<5400; i++) set(i, (1<<31) - 1);
	pi upload[1005];
	fill(upload, upload + 1005, pi(2e9, 2e9));
	for(int i=0; i<x; i++){
		for(int j=vect[i].first; j<=vect[i].second; j++){
			upload[j] = min(upload[j], ans[i]);
		}
	}
	for(int i=0; i<=(n-k)/B; i++){
		set(i, upload[i].second);
	}
}

void upload(int grs, int rs, int re, int x, int y){
	if(grs == rs){
		if(get(1019 + re - grs) >= x){
			set(1019 + re - grs, x);
		}
	}
	else{
		if(get(2040 + rs - grs) >= x){
			set(2040 + rs - grs, x);
		}
	}
}

void empty_buffer(){
	int k = getWindowLength();
	int rs = getRs();
	int re = getRe();
	int ans[1111];
	memset(ans, 0x3f, sizeof(ans));
	for(int i=rs; i<=re; i++){
		int w = get(1019 + i - rs);
		ans[i - rs] = min(ans[i - rs], w);
	}
	for(int i=1109; i>=0; i--) ans[i] = min(ans[i], ans[i + 1]);
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i=rs+1; i<=re; i++){
		int w = get(2040 + i - rs);
		pq.emplace(w, min(i + k - 1, re));
		while(!pq.empty() && pq.top().second < i) pq.pop();
		if(pq.size()) ans[i - rs] = min(ans[i - rs], pq.top().first);
	}
	for(int i=rs; i<=re; i++) shoutMinimum(ans[i - rs]);
}

void remake(int x){
	int n = getTrainLength();
	int k = getWindowLength();
	setRs(B * getPtr());
	setRe(min(n - k, B * getPtr() + B - 1));
	if(getRs() > getRe()){
		setRenew(1e9);
		return;
	}
	setRenew(n - 1);
	if(B * getPtr() + B + k - 1 < n){
		setRenew(get(getPtr() + 1));
	}
	int rs = getRs();
	int re = getRe();
	for(int i=1010; i<3100; i++) set(i, (1 << 31) - 1);
	rs = max(rs, getCurrentCarIndex() - k + 1);
	re = min(re, getCurrentCarIndex());
	upload(getRs(), rs, re, x, getCurrentCarIndex());
}


void helpBessie(int x){
	int n = getTrainLength();
	int k = getWindowLength();
	if(getCurrentPassIndex() == 0){
		int i = getCurrentCarIndex();
		if(i == 0){
			for(int i=0; i<5500; i++){
				set(i, (1 << 31) - 1);
			}
			setPtr(0);
		}
		auto pIntv = interval(i - 1);
		auto cIntv = interval(i);
		if(cIntv.first > cIntv.second) return;
		if(pIntv != cIntv){
			setPtr(getPtr() + 1);
		}
		int v = getPtr();
		if(get(2 * v) >= x){
			set(2 * v, x);
			set(2 * v + 1, i);
		}
	}
	else{
		if(getCurrentCarIndex() == 0){
			make_ds();
			setRs(0);
			setRe(0);
			setPtr(0);
			setRenew(0);
			remake(x);
		}
		int rs = getRs();
		int re = getRe();
		rs = max(rs, getCurrentCarIndex() - k + 1);
		re = min(re, getCurrentCarIndex());
		upload(getRs(), rs, re, x, getCurrentCarIndex());
		while(getRenew() <= getCurrentCarIndex()){
			empty_buffer();
			setPtr(getPtr() + 1);
			remake(x);
		}
	}
}

/*
int main(){
	cin >> ggwp::n >> ggwp::k;
	for(int i=0; i<ggwp::n; i++){
		ggwp::a[i] = rand() % 10000;
	//	scanf("%d",&ggwp::a[i]);
	}
	for(int j=0; j<2; j++){
		for(int i=0; i<ggwp::n; i++){
			ggwp::ptr = i, ggwp::pass = j;
			helpBessie(ggwp::a[i]);
		}
	}
	if(ggwp::ptr2 != ggwp::n - ggwp::k + 1){
		puts("WRONG LENGTH!!");
	}
	else puts("CORRECT LENGTH");
	printf("%d %d %d\n", ggwp::cntG, ggwp::cntS, ggwp::cntG + ggwp::cntS);
}*/
