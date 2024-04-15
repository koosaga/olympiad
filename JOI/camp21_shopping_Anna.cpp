#include "Anna.h"
#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);

namespace FUCKING1 {
const int MAXT = 2100000;
int cnt, n, setAnswer, queryCnt;
pi query, recv, binsearch, lastInterval, ilow, ihigh;
int mode, offset;
int foo;
int recNeedy;
vector<int> partial;
vector<int> received;
/*
0: just receive cartesian tree
1: do binary search
3: receive answer (from 1)
*/

void Sends(int x, int b) {
	for (int i = b - 1; i >= 0; i--) {
		SendA((x >> i) & 1);
		queryCnt++;
	}
}

int mtch[MAXT];
vector<int> seq;

int wordsize(pi bsint) {
	int z = 1;
	while ((1 << z) < bsint[1] - bsint[0] + 1)
		z++;
	return z;
}

void constr(int l, int r, int d = 1) {
	if (l == r)
		return;
	constr(l + 1, mtch[l], d + 1);
	seq.push_back(d);
	constr(mtch[l] + 1, r, d + 1);
}

vector<int> recover(string bits) {
	vector<int> stk;
	for (int i = 0; i < sz(bits); i++) {
		if (bits[i] == '0') {
			stk.push_back(i);
		} else {
			mtch[stk.back()] = i;
			stk.pop_back();
		}
	}
	constr(0, sz(bits));
	return seq;
}

pi bsint;

void doSeg(int s, int e, int ps, int pe, int p, int d) {
	if (d == 13) {
		Sends(15, 4);
		Sends(p - (1 << d), d);
		// cout << p << " " << ps << " " << pe << " " << (ps + pe) / 2 << endl;

		lastInterval = pi{ps, pe};
		mode = 0;
		return;
	} else {
		int pm = (ps + pe) / 2;
		if (ps <= s && e <= pm) {
			doSeg(s, e, ps, pm, 2 * p, d + 1);
		} else if (pm + 1 <= s && e <= pe) {
			doSeg(s, e, pm + 1, pe, 2 * p + 1, d + 1);
		} else {
			if (d <= 1)
				Sends(d, 3);
			else
				Sends(d + 2, 4);
			Sends(p - (1 << d), d);
			//	cout << p - (1 << d) << " " << ps << " " << pe << " " << (ps + pe) / 2 << endl;
			lastInterval = pi{ps, pe};
			bsint = pi{ps, pm};
			mode = 1;
			return;
		}
	}
}

void InitA(int N, int L, int R) {
	if (L == R) {
		setAnswer = L;
		return;
	}
	query = pi{L, R};
	recv = pi{0, 0};
	n = N;
	doSeg(L, R, 0, N - 1, 1, 0);
	binsearch[1] = lastInterval[1] - lastInterval[0];
}

string bits;

void ReceiveA(bool x) {
	// cout << "mode" << mode << endl;
	if (mode == 0) {
		bits.push_back('0' + x);
		if (sz(bits) == 2 * (lastInterval[1] - lastInterval[0]) + 2) {
			auto partial = recover(bits);
			pi ans{int(1e9), -1};
			for (int i = 0; i < sz(partial); i++) {
				if (query[0] <= i + lastInterval[0] && i + lastInterval[0] <= query[1]) {
					ans = min(ans, pi{partial[i], i + lastInterval[0]});
				}
			}
			setAnswer = ans[1];
			//	cout << "!!" << setAnswer << " " << lastInterval[0] << " " << lastInterval[1] << endl;
			return;
		}
	}

	if (mode == 1) {
		recv[0] += (x << cnt);
		++cnt;
		if (cnt == wordsize(bsint)) {
			//	cout << "recv by" << bsint[0] << " " << bsint[1] << " " << wordsize(bsint) << endl;

			recv[0] += bsint[0];
			recv[1] = recv[0] + (binsearch[0] + binsearch[1]) / 2;
			if (recv[0] <= query[0] && query[1] <= recv[1]) {
				binsearch[1] = (binsearch[0] + binsearch[1]) / 2;
				bsint = pi{recv[0], bsint[1]};
				SendA(true);
				queryCnt++;
			} else {
				binsearch[0] = 1 + (binsearch[0] + binsearch[1]) / 2;
				bsint = pi{bsint[0], recv[0]};
				SendA(false);
				queryCnt++;
			}
			cnt = 0;
			recv[0] = recv[1] = 0;
			if (binsearch[0] == binsearch[1]) {
				mode = 2;
				cnt = 0;
				return;
			}
			if (queryCnt == 18) {
				mode = 3;
				cnt = 0;
				return;
			}
		}
	}
	if (mode == 2) {
		//	cout << "rcv" << cnt;
		setAnswer += (x << cnt);
		cnt++;
		return;
	}
	if (mode == 3) {
		recv[0] += (x << cnt);
		++cnt;
		// cout << cnt << " " << sz(received) << " " << width << endl;
		if (cnt == wordsize(bsint) && sz(received) == 0) {
			//	cout << "recv by" << bsint[0] << " " << bsint[1] << " " << wordsize(bsint) << endl;
			received.push_back(recv[0]);
			cnt = 0;
			recv[0] = 0;
			return;
		}
		if (cnt == wordsize(bsint) && sz(received) == 1) {
			//	cout << "recv by" << bsint[0] << " " << bsint[1] << " " << wordsize(bsint) << endl;
			received.push_back(recv[0]);
			cnt = 0;
			recv[0] = 0;
			return;
		}
		if (cnt == 20 && sz(received) == 2) {
			received[0] += bsint[0];
			received[1] += bsint[0];
			received.push_back(recv[0]);
			cnt = 0;
			recv[0] = 0;
			// cout << received[0] << " " << received[1] << endl;
			ilow = pi{received[0], received[0] + binsearch[0]};
			ihigh = pi{received[1], received[1] + binsearch[1]};
			mode = 4;
			for (int j = ihigh[0]; j < ilow[0]; j++) {
				recNeedy++;
			}
			recNeedy++;
			for (int j = ilow[1] + 1; j <= ihigh[1]; j++) {
				recNeedy++;
			}
			return;
		}
	}
	if (mode == 4) {
		bits.push_back('0' + x);
		recv[0] = 0;
		if (sz(bits) == 2 * recNeedy) {
			int minPosActual = received[2];
			pi minval = {int(1e9), -1};
			recNeedy = 0;
			auto recv = recover(bits);
			for (int j = ihigh[0]; j < ilow[0]; j++) {
				if (j >= query[0] && j <= query[1])
					minval = min(minval, pi{recv[recNeedy], j});
				recNeedy++;
			}
			if (minPosActual >= query[0] && minPosActual <= query[1]) {
				minval = min(minval, pi{recv[recNeedy], minPosActual});
			}
			recNeedy++;
			for (int j = ilow[1] + 1; j <= ihigh[1]; j++) {
				if (j >= query[0] && j <= query[1])
					minval = min(minval, pi{recv[recNeedy], j});
				recNeedy++;
			}
			assert(minval[0] <= 8e9);
			setAnswer = minval[1];
			assert(setAnswer >= query[0] && setAnswer <= query[1]);
		}
	}
}
int Answer() { return setAnswer; }

} // namespace FUCKING1
void InitA(int N, int L, int R) { FUCKING1::InitA(N, L, R); }

void ReceiveA(bool x) { FUCKING1::ReceiveA(x); }

int Answer() { return FUCKING1::Answer(); }