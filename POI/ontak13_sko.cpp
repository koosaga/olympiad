#include "sko.h"
#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

int n;

void my_assert(bool p){
	if(p == 0){
		answer(0, 0, 0, 0);
		exit(0);
	}
}

void solve1(int p1, int p2){ // 2n
	int p3 = -1, cnt = 0;
	for(int i=1; i<=n; i++){
		if(i != p1 && edge(p2, i)){
			p3 = i;
			cnt++;
		}
	}
	my_assert(cnt == 1);
	my_assert(!edge(p1, p3));
	for(int i=1; i<=n; i++){
		if(i == p1 || i == p3) continue;
		my_assert(edge(i, p3));
	}
	answer(1, p1, p2, p3);
}

void solve2(int p3){ // 3n
	int p1 = -1, cnt = 0;
	for(int i=1; i<=n; i++){
		if(i != p3 && !edge(p3, i)){
			p1 = i;
			cnt++;
		}
	}
	my_assert(cnt == 1);
	cnt = 0;
	int p2 = -1;
	for(int i=1; i<=n; i++){
		if(edge(p1, i)){
			p2 = i;
			cnt++;
		}
	}
	my_assert(cnt == 1);
	cnt = 0;
	for(int i=1; i<=n; i++){
		if(edge(p2, i)){
			cnt++;
		}
	}
	my_assert(cnt == 2);
	answer(1, p1, p2, p3);
}

int main(){
	n = init();
	vector<int> a, b;
	for(int i=2; i<=n; i++){
		if(edge(1, i)){
			a.push_back(i);
		}
		else{
			b.push_back(i);
		}
	}
	my_assert(1 <= a.size() && a.size() <= n-2);
	if(a.size() == n-2){
		solve2(1);
	}
	else if(a.size() == 1){
		int deg = 0;
		for(int i=1; i<=n; i++){
			if(edge(a[0], i)) deg++;
		}
		if(deg == 2) solve1(1, a[0]);
		else if(deg == n-2)	solve2(a[0]);
		else my_assert(0);
	}
	else if(a.size() == 2){
		int deg = 0;
		for(int i=1; i<=n; i++){
			if(edge(a[0], i)) deg++;
		}
		if(deg == n-2) solve2(a[0]);
		else solve2(a[1]);
	}
	else{
		while(a.size() >= 1 && b.size() >= 1){
			if(edge(a.back(), b.back())) b.pop_back();
			else a.pop_back();
		}
		my_assert(a.empty() && !b.empty());
		int cnt = 0, p2 = -1;
		for(int i=1; i<=n; i++){
			if(edge(b.back(), i)){
				cnt++;
				p2 = i;
			}
		}
		my_assert(cnt == 1);
		solve1(b.back(), p2);
	}
}
