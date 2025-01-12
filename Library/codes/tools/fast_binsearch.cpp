// Fast binary search.
// Source: https://contest.ucup.ac/submission/855147

template <typename T, typename C> int fast_bs(const vector<T> &v, const T &x, const C &comp) {
	if (v.empty() or comp(x, v[0]))
		return 0;
	const T *p = v.data();
	int s = v.size();
	int t = 63 - __builtin_clzll(s);
	int b = s - (1 << t);
	int l = comp(x, p[b]) ? 0 : b;
	if (t == 0)
		return l + 1;
	for (int d = 1 << (t - 1); d; d /= 2) {
		l = comp(x, p[l + d]) ? l : l + d;
	}
	return l + 1;
}

template <typename T> int fast_lb(const vector<T> &v, const T &x) { return fast_bs(v, x, std::less_equal<T>{}); }

template <typename T> int fast_ub(const vector<T> &v, const T &x) { return fast_bs(v, x, std::less<T>{}); }
