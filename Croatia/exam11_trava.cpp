#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;

lint st, ed, n, h;
deque<pi> dql, dqr;
lint lsum, rsum;

lint query(){
	return (ed - st) * n - lsum - rsum;
}

void popBL(){
	lint gap = dql.back().second;
	lint ht = dql.back().first - st;
	dql.pop_back();
	if (!dql.empty()) gap -= dql.back().second;
	lsum -= gap * ht;
}

void popBR(){
	lint gap = -dqr.back().second;
	lint ht = dqr.back().first - st;
	dqr.pop_back();
	if (!dqr.empty()) gap += dqr.back().second;
	else gap += n;
	rsum -= gap * ht;
}

void popFL(){
	lint gap = dql.front().second;
	lint ht = dql.front().first;
	dql.pop_front();
	if (dql.empty()) ht -= st;
	else ht -= dql.front().first;
	lsum -= gap * ht;
}

void popFR(){
	lint gap = n - dqr.front().second;
	lint ht = dqr.front().first;
	dqr.pop_front();
	if (dqr.empty()) ht -= st;
	else ht -= dqr.front().first;
	rsum -= gap * ht;
}

void up(lint x){
	while (!dql.empty() && dql.back().first <= x){
		popBL();
	}
	while (!dqr.empty() && dqr.back().first <= x){
		popBR();
	}
	if (!dql.empty()) lsum -= (x - st) * dql.back().second;
	if (!dqr.empty()) rsum -= (x - st) * (n - dqr.back().second);
	st = x;
}

long long fertilize (int x) {
	ed += x;
	if (st < ed - h){
		up(ed - h);
	}
	return query();
}

long long mow (int x) {
	if (st < ed - x){
		up(ed - x);
	}
	return query();
}

long long burn_front (int k) {
	while (!dql.empty() && dql.front().second <= k){
		popFL();
	}
	lsum += k * (ed - (dql.empty() ? st : dql.front().first));
	dql.push_front(pi(ed, k));
	lint x = st;
	while (!dqr.empty() && dqr.back().second <= k){
		x = dqr.back().first;
		popBR();
	}
	if (!dql.empty()) lsum -= (x - st) * dql.back().second;
	if (!dqr.empty()) rsum -= (x - st) * (n - dqr.back().second);
	st = x;
	return query();
}

long long burn_back (int k) {
	while (!dqr.empty() && dqr.front().second >= n - k){
		popFR();
	}
	rsum += k * (ed - (dqr.empty() ? st : dqr.front().first));
	dqr.push_front(pi(ed, n - k));
	lint x = st;
	while (!dql.empty() && dql.back().second >= n - k){
		x = dql.back().first;
		popBL();
	}
	if (!dql.empty()) lsum -= (x - st) * dql.back().second;
	if (!dqr.empty()) rsum -= (x - st) * (n - dqr.back().second);
	st = x;
	return query();
}

int main(){
	int q;
	char buf[5];
	scanf("%lld %lld %d", &n, &h, &q);
	while (q--){
		scanf("%s", buf);
		if (*buf == 'Z') printf("%lld\n", query());
		else{
			int x;
			scanf("%d", &x);
			if (*buf == 'N') fertilize(x);
			if (*buf == 'L') burn_front(x);
			if (*buf == 'D') burn_back(x);
			if (*buf == 'S') mow(x);
		}
	}
}