// Returns pair of two closest points
// Complexity: expected O(n) with big constant
// Credit: wery0 @ https://judge.yosupo.jp/submission/213872

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

template <typename T> struct closest_pair_of_points_2d {
	using ptt = pair<T, T>;
	uint64_t hash_pair(uint64_t x, uint64_t y) {
		static mt19937_64 rndll(std::chrono::steady_clock::now().time_since_epoch().count());
		static uint64_t kek = uniform_int_distribution<uint64_t>(0, numeric_limits<uint64_t>::max())(rndll);
		return x * kek + y;
	}

	T dist2(ptt p1, ptt p2) { return (p1.first - p2.first) * (p1.first - p2.first) + (p1.second - p2.second) * (p1.second - p2.second); }

	unordered_map<uint64_t, vector<ptt>> mp;
	vector<ptt> m;

	void rebuild(long double d, size_t pref) {
		mp.clear();
		for (size_t i = 0; i < pref; ++i) {
			mp[hash_pair(m[i].first / d, m[i].second / d)].push_back(m[i]);
		}
	}

  public:
	closest_pair_of_points_2d() = default;
	closest_pair_of_points_2d(size_t n) : m(n) {}
	closest_pair_of_points_2d(const vector<ptt> &m) : m(m) {}

	void add_point(T x, T y) { m.emplace_back(x, y); }

	pair<ptt, ptt> calc() {
		assert(m.size() >= 2);
		mp.reserve(m.size());
		shuffle(m.begin(), m.end(), rng);
		sort(all(m));
		ptt o1 = m[0], o2 = m[1];
		T sd = dist2(o1, o2);
		for (int q = 1; q + 1 < m.size(); ++q) {
			T cd = dist2(m[q], m[q + 1]);
			if (cd < sd)
				sd = cd, o1 = m[q], o2 = m[q + 1];
		}
		if (!sd)
			return {o1, o2};
		rebuild(sqrtl(sd), 2);
		for (size_t i = 2; i < m.size(); ++i) {
			uint64_t x = m[i].first / sqrtl(sd);
			uint64_t y = m[i].second / sqrtl(sd);
			bool fl = 0;
			for (int dx = -1; dx <= 1; ++dx) {
				uint64_t nx = x + dx;
				for (int dy = -1; dy <= 1; ++dy) {
					uint64_t ny = y + dy;
					uint64_t hs = hash_pair(nx, ny);
					if (mp.count(hs)) {
						for (const ptt &p : mp[hs]) {
							T tyt = dist2(m[i], p);
							if (tyt < sd) {
								sd = tyt;
								fl = 1;
								o1 = m[i], o2 = p;
								if (sd == 0)
									return {o1, o2};
							}
						}
					}
				}
			}
			if (fl)
				rebuild(sqrtl(sd), i + 1);
			else
				mp[hash_pair(x, y)].push_back(m[i]);
		}
		return {o1, o2};
	}
};
