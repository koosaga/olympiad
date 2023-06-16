#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<int, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const string BLACK = "C";
const string WHITE = "B";
const string TIED = "R";

struct block {
	int d, n, l, owner;
};

bool white_stuck(vector<block> a) {
	for (auto &x : a) {
		if (x.owner == 1 && x.l > 0)
			return false;
		if (x.owner == 0 && x.d > x.n)
			return false;
		if (x.owner == 0 && x.l > 0)
			return false;
	}
	return true;
}

bool black_stuck(vector<block> a) {
	int salvation = 0;
	for (int i = 0; i < sz(a); i++) {
		if (a[i].owner == 1) {
			if (a[i].d > a[i].n)
				return false;
			if (a[i].l > 0) {
				if (a[(i + 1) % sz(a)].n == 1)
					return false;
				salvation++; // killable spaces
			}
		}
		if (a[i].owner == 0) {
			if (a[i].l > 0) {
				if (a[i].n == 1)
					return false;
				salvation++;
			}
		}
	}
	if (salvation >= 2)
		return false;
	// corner case: if white has nothing but to retreat
	bool else_retreat = 0;
	for (auto &x : a) {
		if (x.owner == 1 && x.l > 0)
			else_retreat = 1;
		if (x.owner == 0 && x.d > x.n)
			return false;
		if (x.owner == 0 && x.l > 0)
			else_retreat = 1;
	}
	if (!else_retreat)
		return false;
	return true;
}

string recurse(vector<block> blocks) {
	if (white_stuck(blocks))
		return BLACK;
	if (black_stuck(blocks))
		return WHITE;

	for (int i = 0; i < sz(blocks); i++)
		assert(blocks[i].owner != blocks[(i + 1) % sz(blocks)].owner);
	auto count_moves = [&](int owner) {
		int moves = 0;
		for (int i = 0; i < sz(blocks); i++) {
			if (blocks[i].owner == owner) {
				if (blocks[i].n >= 3 && blocks[i].d > blocks[i].n)
					return int(1e9);
				if (blocks[i].n >= 3 && blocks[i].l > 0)
					moves++;
			} else {
				if (blocks[(i + 1) % sz(blocks)].n >= 3 && blocks[i].l > 0)
					moves++;
			}
		}
		return moves;
	};
	int moves = count_moves(1);
	/*
	cout << "cm " << moves << endl;
	for (auto &x : blocks)
		cout << x.d << " " << x.l << " " << x.n << " " << x.owner << endl;
	cout << endl;*/

	if (moves >= 2) {
		return count_moves(0) >= 1 ? TIED : BLACK;
	}
	if (moves == 0) {
		if (count_moves(0) >= 1)
			return WHITE;
		int nimsum = 0;
		for (auto &z : blocks)
			nimsum ^= z.l;
		return nimsum == 0 ? BLACK : WHITE;
	}
	if (moves == 1) {
		if (count_moves(0) >= 1e8)
			return WHITE;
		if (count_moves(0) == 0) {
			// Block it and see what happens..
			for (int i = 0; i < sz(blocks); i++) {
				if (blocks[i].owner == 1) {
					if (blocks[i].n >= 3 && blocks[i].l > 0) {
						blocks[(i + 1) % sz(blocks)].d += blocks[i].l;
						blocks[i].l = 0;
					}
				} else {
					if (blocks[(i + 1) % sz(blocks)].n >= 3 && blocks[i].l > 0) {
						blocks[i].d += blocks[i].l;
						blocks[i].l = 0;
					}
				}
			}
			assert(count_moves(1) == 0);
			for (auto &x : blocks)
				x.owner ^= 1;
			auto ans = recurse(blocks);
			if (ans == WHITE)
				return BLACK;
			if (ans == TIED)
				return TIED;
			return WHITE;
		} else {
			// If I fuck with remaining moves, then I can assure tie, but they will too
			// Take offensive action to fuck opp
			for (int i = 0; i < sz(blocks); i++) {
				if (blocks[i].owner == 1) {
					if (blocks[i].n >= 3 && blocks[i].l > 0) {
						blocks[(i + 1) % sz(blocks)].d += blocks[i].l;
						blocks[i].l = 0;
					}
				} else {
					if (blocks[(i + 1) % sz(blocks)].n >= 3 && blocks[i].l > 0) {
						blocks[i].d += blocks[i].l;
						blocks[i].l = 0;
					}
				}
			}
			assert(count_moves(1) == 0);
			for (auto &x : blocks)
				x.owner ^= 1;
			auto ans = recurse(blocks);
			if (ans == BLACK)
				return WHITE;
			return TIED;
		}
	}
}

string solve() {
	int l, n, m;
	cin >> l >> n >> m;
	vector<pi> pos(n + m);
	for (int i = 0; i < n; i++) {
		cin >> pos[i][0];
		// white
	}
	for (int i = 0; i < m; i++) {
		cin >> pos[i + n][0];
		pos[i + n][1] = 1; // black
	}
	sort(all(pos));
	int z = 0;
	while (pos[z][1] == pos[(z + sz(pos) - 1) % sz(pos)][1])
		z++;
	rotate(pos.begin(), pos.begin() + z, pos.end());
	vector<block> blocks; // (d, n, l, o)
	for (int i = 0; i < sz(pos);) {
		int j = i;
		while (j < sz(pos) && pos[j][1] == pos[i][1])
			j++;
		int d = (pos[j - 1][0] - pos[i][0] + l) % l + 1;
		int z = (pos[j % sz(pos)][0] - pos[j - 1][0] + l - 1) % l;
		blocks.push_back({d, j - i, z, pos[i][1]});
		i = j;
	}
	if (white_stuck(blocks))
		return BLACK;
	if (black_stuck(blocks))
		return WHITE;
	int non_sing_pos = -1;
	for (int i = 0; i < sz(blocks); i++) {
		if (blocks[i].n > 1)
			non_sing_pos = i;
	}
	if (non_sing_pos == -1)
		return TIED;
	rotate(blocks.begin(), blocks.begin() + non_sing_pos, blocks.end()); /*
	 for (auto &x : blocks)
		 cout << x.d << " " << x.l << " " << x.n << " " << x.owner << endl;
	 cout << endl;*/
	{
		vector<block> nxt;
		for (int i = 0; i < sz(blocks);) {
			if (blocks[i].n > 1) {
				nxt.push_back(blocks[i++]);
			} else {
				int j = i;
				while (j < sz(blocks) && blocks[j].n == blocks[i].n)
					j++;
				auto s = nxt.back();
				auto e = (j < sz(blocks) ? blocks[j] : nxt[0]);
				if ((j - i) % 2) {
					block ret = e;
					for (int it = i; it < j; it++) {
						ret.d += blocks[it].d + blocks[it].l;
						ret.n += blocks[it].n;
					}
					ret.d += s.d + s.l;
					ret.n += s.n;
					nxt.back() = ret;
					if (j == sz(blocks)) {
						if (sz(nxt) > 1)
							nxt.erase(nxt.begin()), i = j;
						else {
							if (nxt[0].owner == 0)
								return WHITE;
							return BLACK;
						}
					} else
						i = j + 1;
				} else {
					for (int it = i; it < j; it++) {
						blocks[it].n = blocks[it].d = 2;
						if (it % 2 == i % 2) {
							blocks[it].l = 0;
						}
						nxt.push_back(blocks[it]);
					}
					i = j;
				}
			}
		}
		blocks = nxt;
	} /*
	  for (auto &x : blocks)
		  cout << x.d << " " << x.l << " " << x.n << " " << x.owner << endl;
	  cout << endl;*/
	for (auto &z : blocks) {
		if (z.n == 1)
			assert(0);
	}
	return recurse(blocks);
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	int t;
	cin >> t;
	while (t--) {
		cout << solve() << "\n";
	}
}