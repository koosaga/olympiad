/*
Randomized Fixed-Dimension Near-Linear LP which
 *  Maximize c^T x
 *  Subject to Ax <= b
 *  Returns empty vector if infeasible

Runtime is expected
 *  O(d n log n + d^{O(d)} log n)                  | one phase (can use if 0 <= b)
 *  O(d^2 n + d^4 sqrt{n} log n + d^{O(d)} log(n)) | two phase (else)

Does exact calculations.

How to use:
 * using bigint_t = Bigint_Fixedsize_Fast<8 ~ 32>; works well in general
 * Every coefficient needs to be an integer
 * Solver returns d + 1 variable, where answers are x_i = a[i] / a[d]
 * Solver returns values in form of Lp_Clarkson_Barrierless<bigint_t>::Solution_Int to support infinity.
 * Lp_Clarkson_Barrierless<bigint_t>::Solution_Int supports casting to long double.

All due to dacin21 (https://github.com/dacin21/dacin21_codebook/tree/master/lp)
*/

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
lint randint(lint lb, lint ub) { return uniform_int_distribution<lint>(lb, ub)(rng); }
#define lp_debug(x) 0

template <size_t len> struct Bigint_Fixedsize_Fast {
	unsigned int data[len];
	uint16_t siz;
	bool sign;
	static constexpr unsigned int bits = 32;
	Bigint_Fixedsize_Fast() {
		data[0] = 0;
		siz = 1;
		sign = false;
	}
	Bigint_Fixedsize_Fast(long long a) {
		sign = false;
		if (a < 0) {
			sign = true;
			a = -a;
		}
		siz = 0;
		do {
			long long b = a >> bits;
			data[siz] = a - (b << bits);
			a = b;
			++siz;
		} while (a);
	}
	void trim() {
		while (siz > 1 && !data[siz - 1])
			--siz;
		if (siz == 1 && data[0] == 0)
			sign = false;
	}
	int comp_unsigned(Bigint_Fixedsize_Fast const &o) const {
		uint16_t lim = min(siz, o.siz);
		for (unsigned int i = lim; i < siz; ++i) {
			if (data[i]) {
				return 1;
			}
		}
		for (unsigned int i = lim; i < o.siz; ++i) {
			if (o.data[i]) {
				return -1;
			}
		}
		for (unsigned int i = lim - 1; i + 1; --i) {
			if (data[i] != o.data[i]) {
				return data[i] < o.data[i] ? -1 : 1;
			}
		}
		return 0;
	}
	int comp(Bigint_Fixedsize_Fast const &o) const {
		int sign_mul = 1 - 2 * sign;
		if (sign != o.sign) {
			return sign_mul;
		}
		return sign_mul * comp_unsigned(o);
	}
	bool operator<(Bigint_Fixedsize_Fast const &o) const { return comp(o) < 0; }
	bool operator>(Bigint_Fixedsize_Fast const &o) const { return comp(o) > 0; }
	bool operator<=(Bigint_Fixedsize_Fast const &o) const { return comp(o) <= 0; }
	bool operator>=(Bigint_Fixedsize_Fast const &o) const { return comp(o) >= 0; }
	bool operator==(Bigint_Fixedsize_Fast const &o) const { return comp(o) == 0; }
	bool operator!=(Bigint_Fixedsize_Fast const &o) const { return comp(o) != 0; }
	bool operator!() const { return operator==(ZERO); }
	Bigint_Fixedsize_Fast operator-() const {
		Bigint_Fixedsize_Fast ret(*this);
		if (!!ret) {
			ret.sign ^= 1;
		}
		return ret;
	}
	Bigint_Fixedsize_Fast operator*(Bigint_Fixedsize_Fast const &o) const {
		Bigint_Fixedsize_Fast ret;
		ret.siz = min(siz + o.siz, (int)len);
		ret.sign = (sign != o.sign);
		fill(ret.data, ret.data + ret.siz, 0);
		for (unsigned int i = 0; i < siz; ++i) {
			unsigned long long carry = 0, carry_2;
			for (unsigned int j = 0; j < o.siz; ++j) {
				carry += data[i] * (unsigned long long)o.data[j] + ret.data[i + j];
				carry_2 = carry >> bits;
				ret.data[i + j] = carry - (carry_2 << bits);
				carry = carry_2;
			}
			for (unsigned int j = i + o.siz; carry; ++j) {
				carry += ret.data[j];
				carry_2 = carry >> bits;
				ret.data[j] = carry - (carry_2 << bits);
				carry = carry_2;
			}
		}
		ret.trim();
		return ret;
	}
	Bigint_Fixedsize_Fast &operator*=(Bigint_Fixedsize_Fast const &o) {
		*this = operator*(o);
		return *this;
	}
	static void unsigned_add(Bigint_Fixedsize_Fast &ret, Bigint_Fixedsize_Fast const &A, Bigint_Fixedsize_Fast const &B) {
		const Bigint_Fixedsize_Fast *a = &A, *b = &B;
		if (a->siz < b->siz)
			swap(a, b);
		ret.sign = A.sign;
		unsigned long long carry = 0, carry_2;
		unsigned int j;
		for (j = 0; j < b->siz; ++j) {
			carry += (unsigned long long)a->data[j] + (unsigned long long)b->data[j];
			carry_2 = carry >> bits;
			ret.data[j] = carry - (carry_2 << bits);
			carry = carry_2;
		}
		for (; j < a->siz; ++j) {
			carry += a->data[j];
			carry_2 = carry >> bits;
			ret.data[j] = carry - (carry_2 << bits);
			carry = carry_2;
		}
		if (carry) {
			ret.data[j++] = carry;
		}
		ret.siz = j;
		ret.trim();
	}
	static void unsigned_subtract(Bigint_Fixedsize_Fast &ret, Bigint_Fixedsize_Fast const &A, Bigint_Fixedsize_Fast const &B) {
		int com = A.comp_unsigned(B);
		if (com == 0) {
			ret.sign = false;
			ret.siz = 1;
			ret.data[0] = 0;
			return;
		}
		ret.sign = A.sign;
		const Bigint_Fixedsize_Fast *a = &A, *b = &B;
		if (com < 0) {
			ret.sign ^= true;
			swap(a, b);
		}
		// deal with case then o is not trimed.
		unsigned int min_siz = min(A.siz, B.siz);
		unsigned long long carry = 0, carry_2;
		unsigned int j;
		for (j = 0; j < min_siz; ++j) {
			carry += (unsigned long long)a->data[j] - (unsigned long long)b->data[j];
			carry_2 = carry >> bits;
			ret.data[j] = carry - (carry_2 << bits);
			carry = -(carry_2 & 1u);
		}
		for (; carry; ++j) {
			assert(j < a->siz);
			carry += a->data[j];
			carry_2 = carry >> bits;
			ret.data[j] = carry - (carry_2 << bits);
			carry = -(carry_2 & 1u);
		}
		copy(a->data + j, a->data + a->siz, ret.data + j);
		ret.siz = a->siz;
		ret.trim();
	}
	static void add(Bigint_Fixedsize_Fast &ret, Bigint_Fixedsize_Fast const &A, Bigint_Fixedsize_Fast const &B) {
		if (A.sign == B.sign) {
			unsigned_add(ret, A, B);
		} else {
			unsigned_subtract(ret, A, B);
		}
	}
	static void sub(Bigint_Fixedsize_Fast &ret, Bigint_Fixedsize_Fast const &A, Bigint_Fixedsize_Fast const &B) {
		if (A.sign != B.sign) {
			unsigned_add(ret, A, B);
		} else {
			unsigned_subtract(ret, A, B);
		}
	}
	Bigint_Fixedsize_Fast operator+(Bigint_Fixedsize_Fast const &o) const {
		Bigint_Fixedsize_Fast ret;
		add(ret, *this, o);
		return ret;
	}
	Bigint_Fixedsize_Fast &operator+=(Bigint_Fixedsize_Fast const &o) {
		add(*this, *this, o);
		return *this;
	}
	Bigint_Fixedsize_Fast operator-(Bigint_Fixedsize_Fast const &o) const {
		Bigint_Fixedsize_Fast ret;
		sub(ret, *this, o);
		return ret;
	}
	Bigint_Fixedsize_Fast operator-=(Bigint_Fixedsize_Fast const &o) {
		sub(*this, *this, o);
		return *this;
	}
	explicit operator long double() const {
		long double ret = 0.0;
		long double base = 1ll << bits;
		for (int i = siz - 1; i >= 0; --i) {
			ret = ret * base + data[i];
		}
		if (sign)
			ret *= -1; // huh?
		return ret;
	}
	static const Bigint_Fixedsize_Fast ZERO;
};
template <size_t len> const Bigint_Fixedsize_Fast<len> Bigint_Fixedsize_Fast<len>::ZERO(0);

template <typename INT> class Barrier_Int {
  private:
	Barrier_Int(INT const &_val, INT const &_inf_part) : val(_val), inf_part(_inf_part) {}

  public:
	Barrier_Int() : val(0), inf_part(0) {}
	explicit Barrier_Int(INT const &_val) : val(_val), inf_part(0) {}
	static Barrier_Int infinity() { return Barrier_Int(0, 1); }
	static Barrier_Int negative_infinity() { return Barrier_Int(0, -1); }

	Barrier_Int operator-() const { return Barrier_Int(-val, -inf_part); }
	Barrier_Int &operator+=(Barrier_Int const &o) {
		val += o.val;
		inf_part += o.inf_part;
		return *this;
	}
	Barrier_Int operator+(Barrier_Int const &o) const { return Barrier_Int(val + o.val, inf_part + o.inf_part); }
	Barrier_Int &operator-=(Barrier_Int const &o) {
		val -= o.val;
		inf_part -= o.inf_part;
		return *this;
	}
	Barrier_Int operator-(Barrier_Int const &o) const { return Barrier_Int(val - o.val, inf_part - o.inf_part); }
	Barrier_Int &operator*=(INT const &o) {
		val *= o;
		inf_part *= o;
		return *this;
	}
	Barrier_Int operator*(INT const &o) const { return Barrier_Int(val * o, inf_part * o); }
	bool operator<(Barrier_Int const &o) const {
		if (inf_part != o.inf_part)
			return inf_part < o.inf_part;
		return val < o.val;
	}
	bool operator>(Barrier_Int const &o) const { return o < *this; }
	bool operator>=(Barrier_Int const &o) const { return !operator<(o); }
	bool operator<=(Barrier_Int const &o) const { return !operator>(o); }
	bool operator==(Barrier_Int const &o) const { return val == o.val && inf_part == o.inf_part; }
	bool operator!=(Barrier_Int const &o) const { return val != o.val || inf_part != o.inf_part; }
	friend ostream &operator<<(ostream &o, Barrier_Int const &b) {
		if (!b.inf_part) {
			return o << b.val;
		}
		o << b.inf_part << numeric_limits<double>::infinity() << "+" << b.val;
		return o;
	}
	explicit operator long double() const {
		if (inf_part != INT(0)) {
			return inf_part < INT(0) ? -numeric_limits<long double>::infinity() : numeric_limits<long double>::infinity();
		}
		return (long double)val;
	}

  public:
	INT val;
	INT inf_part;
};

/**
 *  Randomized LP in expected
 *  O(d! 4^d n)
 *  Does exact calculations.
 *  Does not need a barrier bound for dealing with unbounded parts
 */
template <typename FLOAT> class Lp_Seidel_Barierless {
  private:
	// orthogonal projection of 'vec' into 'plane'
	vector<FLOAT> proj_down(vector<FLOAT> const &vec, vector<FLOAT> const &plane, size_t j) {
		assert(vec.size() <= plane.size() && plane.size() <= vec.size() + 1);
		assert(j + 1 < plane.size());
		assert(!!plane[j]);
		vector<FLOAT> ret(vec.size() - 1);
		// FLOAT tmp;
		if (plane[j] < FLOAT(0)) {
			for (size_t i = 0; i + 1 < vec.size(); ++i) {
				ret[i] = vec[j] * plane[i + (i >= j)] - vec[i + (i >= j)] * plane[j];
			}
		} else {
			for (size_t i = 0; i + 1 < vec.size(); ++i) {
				ret[i] = vec[i + (i >= j)] * plane[j] - vec[j] * plane[i + (i >= j)];
			}
		}
		return ret;
	}

	// orthogonal projection of 'vec' out of 'plane'
	vector<Barrier_Int<FLOAT>> proj_up(vector<Barrier_Int<FLOAT>> const &vec, vector<FLOAT> const &plane, size_t j) {
		assert(vec.size() + 1 == plane.size());
		assert(j + 1 < plane.size());
		assert(!!plane[j]);
		vector<Barrier_Int<FLOAT>> ret(vec.size() + 1);
		copy(vec.begin(), vec.begin() + j, ret.begin());
		copy(vec.begin() + j, vec.end(), ret.begin() + j + 1);
		for (size_t i = 0; i < vec.size(); ++i) {
			ret[j] += vec[i] * plane[i + (i >= j)];
		}
		FLOAT denom = plane[j];
		if (denom < FLOAT(0)) {
			denom = -denom;
		}
		for (size_t i = 0; i < vec.size(); ++i) {
			ret[i + (i >= j)] *= denom;
		}
		if (plane[j] >= FLOAT(0)) {
			ret[j] = -ret[j];
		}
		return ret;
	}
	Barrier_Int<FLOAT> planescal(vector<Barrier_Int<FLOAT>> const &x, vector<FLOAT> const &a) {
		assert(x.size() == a.size());
		Barrier_Int<FLOAT> ret(0);
		for (size_t i = 0; i < x.size(); ++i) {
			ret += x[i] * a[i];
		}
		return ret;
	}

	// solve lp recursively
	vector<Barrier_Int<FLOAT>> solve(vector<vector<FLOAT>> const &A, vector<FLOAT> const &c, int d) {
		int n = A.size();
		if (d == 1) { // base case: single dimension
			vector<Barrier_Int<FLOAT>> ret(2);
			if (c[0] != FLOAT(0)) {
				ret[0] = (c[0] < FLOAT(0) ? Barrier_Int<FLOAT>::negative_infinity() : Barrier_Int<FLOAT>::infinity());
			}
			ret[1].val = FLOAT(1ull);
			for (int i = 0; i < n; ++i) {
				if (ret[0] * A[i][0] + ret[1] * A[i].back() > Barrier_Int<FLOAT>(0)) {
					if (!A[i][0]) {
						lp_debug("infeasible single\n");
						return vector<Barrier_Int<FLOAT>>();
					}
					ret[0] = Barrier_Int<FLOAT>(-A[i].back());
					ret[1] = Barrier_Int<FLOAT>(A[i][0]);
					if (ret[1] < Barrier_Int<FLOAT>(0)) {
						ret[1] = -ret[1];
						ret[0] = -ret[0];
					}
					lp_debug(" -> " << i << " " << ret[0] << " " << ret[1] << "\n");
				}
			}
			for (int i = 0; i < n; ++i) {
				if (ret[0] * A[i][0] + ret[1] * A[i].back() > Barrier_Int<FLOAT>(0)) {
					lp_debug("infeasible\n");
					return vector<Barrier_Int<FLOAT>>();
				}
			}
			return ret;
		}
		// initial solution
		vector<Barrier_Int<FLOAT>> x(d + 1);
		for (int i = 0; i < d; ++i) {
			if (c[i] != FLOAT(0)) {
				x[i] = (c[i] < FLOAT(0) ? Barrier_Int<FLOAT>::negative_infinity() : Barrier_Int<FLOAT>::infinity());
			}
		}
		x.back() = Barrier_Int<FLOAT>(1);
		for (size_t i = 0; i < A.size(); ++i) {
			if (planescal(x, A[i]) > Barrier_Int<FLOAT>(0)) {
				int k = 0;
				while (k < d && !A[i][k])
					++k;
				// recurse
				if (k == d) {
					lp_debug("what?\n");
					return vector<Barrier_Int<FLOAT>>();
				} // degenerate failing plane??????
				vector<vector<FLOAT>> A2(i);
				for (size_t j = 0; j < A2.size(); ++j) {
					A2[j] = proj_down(A[j], A[i], k);
				}
				shuffle(A2.begin(), A2.end(), rng);
				lp_debug(string(2 * d, ' ') << i << "\n");
				vector<FLOAT> c2 = proj_down(c, A[i], k);
				vector<Barrier_Int<FLOAT>> x2 = solve(A2, c2, d - 1);
				if (x2.empty())
					return x2; // infeasible
				x = proj_up(x2, A[i], k);
				lp_debug(string(2 * d, ' ') << ":");
				lp_debug(""; for (auto const &e : x) lp_debug(" " << e));
				lp_debug("\n");
			}
		}
		return x;
	}

  public:
	vector<Barrier_Int<FLOAT>> solve(vector<vector<FLOAT>> const &A, vector<FLOAT> const &c) {
		assert(A.empty() || A[0].size() == c.size() + 1);
		return solve(A, c, c.size());
	}
	/**
	 *  Maximize c^T x
	 *  subject to Ax <= b
	 *
	 *  Returns empty vector if infeasible
	 */
	vector<Barrier_Int<FLOAT>> solve(vector<vector<FLOAT>> A, vector<FLOAT> const &b, vector<FLOAT> const &c) {
		assert(A.size() == b.size());
		for (unsigned int i = 0; i < A.size(); ++i) {
			A[i].push_back(-b[i]);
		}
		return solve(A, c);
	}
};
/**
 *  Randomized LP, runtime is expected
 *  O(d^2 n + d^4 sqrt{n} log n + d^{O(d)} log(n)) | two phase
 *  O(d n log n + d^{O(d)} log n)                  | one phase
 *  Does exact calculations.
 */
template <typename Big_Int, bool use_two_phase = true> class Lp_Clarkson_Barrierless {
  public:
	using Solution_Int = Barrier_Int<Big_Int>;

  private:
	/**
	 *  Returns a sub-multiset of size siz uniformly at random
	 *  out of the set where i is present weight[i] times.
	 *
	 *  Runs in O(|weight| + siz^2) expected time.
	 *  Could be optimized
	 */

	vector<int> sample_subset(vector<int64_t> const &weight, unsigned int siz) {
		int64_t total_weight = accumulate(weight.begin(), weight.end(), 0ll);
		vector<int64_t> samples;
		while (samples.size() < siz) {
			int64_t new_sample = randint(0, total_weight - 1);
			if (find(samples.begin(), samples.end(), new_sample) == samples.end()) {
				samples.push_back(new_sample);
			}
		}
		sort(samples.begin(), samples.end());
		vector<int> ret;
		int64_t left_weight = 0;
		for (unsigned int i = 0, j = 0; i < weight.size() && j < samples.size();) {
			if (samples[j] < left_weight + weight[i]) {
				ret.push_back(i);
				++j;
			} else {
				left_weight += weight[i];
				++i;
			}
		}
		return ret;
	}
	/// violation check
	bool is_satisfied(vector<Solution_Int> const &x, vector<Big_Int> const &a) {
		assert(x.size() == a.size());
		Solution_Int ret(0);
		for (size_t i = 0; i < x.size(); ++i) {
			ret += x[i] * a[i];
		}
		return ret <= Solution_Int(0);
	}
	vector<Solution_Int> solve_two(vector<vector<Big_Int>> const &A, vector<Big_Int> const &c) {
		const unsigned int sample_size = c.size() * c.size() * 4;
		Lp_Seidel_Barierless<Big_Int> sub_lp;
		// to few constrains -> use other solver
		if (A.size() < sample_size) {
			return sub_lp.solve(A, c);
		} else {
			int constraints = A.size();
			int variables = c.size();
			vector<int64_t> weight(constraints, 1);
			vector<Solution_Int> x;
			vector<vector<Big_Int>> subproblem_A;
			vector<char> is_violated(constraints, 0);
			for (unsigned int iteration = 1;; ++iteration) {
				subproblem_A.clear();
				vector<int> subspace = sample_subset(weight, sample_size);
				for (int const &e : subspace) {
					subproblem_A.push_back(A[e]);
				}

				x = sub_lp.solve(subproblem_A, c);
				// infeasible case
				if (x.empty()) {
					return x;
				}

				int64_t total_violated = 0;
				for (int i = 0; i < constraints; ++i) {
					is_violated[i] = !is_satisfied(x, A[i]);
					if (is_violated[i]) {
						total_violated += weight[i];
					}
				}
				if (total_violated == 0) {
					break;
				}
				if (total_violated * 3 * variables <= accumulate(weight.begin(), weight.end(), 0ll)) {
					for (int i = 0; i < constraints; ++i) {
						if (is_violated[i]) {
							weight[i] *= 2;
						}
					}
				}
			}
			return x;
		}
	}
	vector<Solution_Int> solve_one(vector<vector<Big_Int>> const &A, vector<Big_Int> const &c) {
		const unsigned int constraints = A.size(), variables = c.size();
		if (constraints <= variables * variables * 6) {
			return solve_two(A, c);
		} else {
			const unsigned int sqrt_constraints = sqrt(constraints);
			const unsigned int sample_size = variables * sqrt(constraints);
			vector<Solution_Int> x;
			vector<vector<Big_Int>> subproblem_A;
			vector<int> violations;
			for (unsigned int iteration = 1;; ++iteration) {
				vector<int> subspace = sample_subset(vector<int64_t>(constraints, 1), sample_size);
				for (int const &e : subspace) {
					subproblem_A.push_back(A[e]);
				}

				x = solve_two(subproblem_A, c);
				// infeasible case
				if (x.empty()) {
					return x;
				}
				violations.clear();
				for (unsigned int i = 0; i < constraints; ++i) {
					if (!is_satisfied(x, A[i])) {
						violations.push_back(i);
					}
				}
				if (violations.empty()) {
					break;
				}
				subproblem_A.erase(subproblem_A.end() - sample_size, subproblem_A.end());
				if (violations.size() <= 2 * sqrt_constraints) {
					for (int const &e : violations) {
						subproblem_A.push_back(A[e]);
					}
				}
			}
			return x;
		}
	}

  public:
	vector<Solution_Int> solve(vector<vector<Big_Int>> const &A, vector<Big_Int> const &c) {
		if (use_two_phase) {
			return solve_one(A, c);
		} else {
			return solve_two(A, c);
		}
	}

	/**
	 *  Maximize c^T x
	 *  Subject to Ax <= b
	 *
	 *  Returns empty vector if infeasible
	 */
	vector<Solution_Int> solve(vector<vector<Big_Int>> A, vector<Big_Int> const &b, vector<Big_Int> const &c) {
		assert(A.size() == b.size());
		for (unsigned int i = 0; i < A.size(); ++i) {
			A[i].push_back(-b[i]);
		}
		return solve(A, c);
	}
};