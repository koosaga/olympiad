const int MAXA = 26;

struct SuffixAutomaton {
	struct node {
		int nxt[MAXA], len, slink;
		node() {
			memset(nxt, -1, sizeof(nxt));
			len = slink = 0;
		}
		node(int _len, int _slink) {
			memset(nxt, -1, sizeof(nxt));
			len = _len;
			slink = _slink;
		}
	};
	vector<node> sa;
	int total;
	SuffixAutomaton() {
		total = 0;
		// sa.reserve(2000005);
		sa.push_back(node(0, -1));
	}
	void addChar(int c) {
		assert(0 <= c && c < MAXA);
		sa.push_back(node(sa[total].len + 1, 0));
		int p = total;
		total = sz(sa) - 1;
		while (p != -1 && sa[p].nxt[c] == -1) {
			sa[p].nxt[c] = total;
			p = sa[p].slink;
		}
		if (p != -1) {
			int prv = sa[p].nxt[c];
			int upd = sa[p].nxt[c];
			if (sa[p].len + 1 < sa[prv].len) {
				upd = sz(sa);
				node nd = sa[prv];
				nd.len = sa[p].len + 1;
				sa.push_back(nd);
				sa[prv].slink = upd;
				for (int j = p; j != -1 && sa[j].nxt[c] == prv; j = sa[j].slink) {
					sa[j].nxt[c] = upd;
				}
			}
			sa[total].slink = upd;
		}
	}
};
