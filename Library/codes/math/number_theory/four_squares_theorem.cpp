// Given an integer N
// Find all integer solution for the equation a^2 + b^2 = N.
// Requires factorization.
// Credit: maspy (https://maspypy.github.io/library/nt/two_square.hpp)

template <typename T> T floor(T a, T b) { return a / b - (a % b && (a ^ b) < 0); }

template <typename T> struct Gaussian_Integer {
    T x, y;
    using G = Gaussian_Integer;

    Gaussian_Integer(T x = 0, T y = 0) : x(x), y(y) {}
    Gaussian_Integer(pair<T, T> p) : x(p.fi), y(p.se) {}

    T norm() const { return x * x + y * y; }
    G conjugate() const { return G(x, -y); }

    G &operator+=(const G &g) {
        x += g.x, y += g.y;
        return *this;
    }
    G &operator-=(const G &g) {
        x -= g.x, y -= g.y;
        return *this;
    }
    G &operator*=(const G &g) {
        tie(x, y) = make_pair(x * g.x - y * g.y, x * g.y + y * g.x);
        return *this;
    }
    G &operator/=(const G &g) {
        *this *= g.conjugate();
        T n = g.norm();
        x = floor(x + n / 2, n);
        y = floor(y + n / 2, n);
        return *this;
    }
    G &operator%=(const G &g) {
        auto q = G(*this) / g;
        q *= g;
        (*this) -= q;
        return *this;
    }
    G operator-() { return G(-x, -y); }
    G operator+(const G &g) { return G(*this) += g; }
    G operator-(const G &g) { return G(*this) -= g; }
    G operator*(const G &g) { return G(*this) *= g; }
    G operator/(const G &g) { return G(*this) /= g; }
    G operator%(const G &g) { return G(*this) %= g; }
    bool operator==(const G &g) { return (x == g.x && y == g.y); }

    static G gcd(G a, G b) {
        while (b.x != 0 || b.y != 0) {
            a %= b;
            swap(a, b);
        }
        return a;
    }

    G pow(lint n) const {
        assert(n >= 0);
        G ret(1), mul(*this);
        while (n > 0) {
            if (n & 1)
                ret *= mul;
            mul *= mul;
            n >>= 1;
        }
        return ret;
    }

    // (g,x,y) s.t ax+by=g

    static tuple<G, G, G> extgcd(G a, G b) {
        if (b.x != 0 || b.y != 0) {
            G q = a / b;
            auto [g, x, y] = extgcd(b, a - q * b);
            return {g, y, x - q * y};
        }
        return {a, G{1, 0}, G{0, 0}};
    }
};

pair<lint, lint> solve_norm_equation_prime(lint p) {
    using G = Gaussian_Integer<__int128>;
    assert(p == 2 || p % 4 == 1);
    if (p == 2)
        return {1, 1};
    lint x = [&]() -> lint {
        lint x = 1;
        while (1) {
            ++x;
            lint pow_x = ipow(x, (p - 1) / 4, p);
            if (__int128(pow_x) * pow_x % p == p - 1)
                return pow_x;
        }
        return -1;
    }();
    G a(p, 0), b(x, 1);
    a = G::gcd(a, b);
    assert(a.norm() == p);
    return {a.x, a.y};
}

template <typename T> vector<Gaussian_Integer<T>> solve_norm_equation_factor(vector<pair<lint, int>> pfs) {
    using G = Gaussian_Integer<T>;
    vector<G> res;
    for (auto &&[p, e] : pfs) {
        if (p % 4 == 3 && e % 2 == 1)
            return {};
    }

    res.emplace_back(G(1, 0));
    for (auto &&[p, e] : pfs) {
        if (p % 4 == 3) {
            T pp = 1;
            for (int i = 0; i < e / 2; i++)
                pp *= p;
            for (auto &&g : res) {
                g.x *= pp;
                g.y *= pp;
            }
            continue;
        }
        auto [pix, piy] = solve_norm_equation_prime(p);
        G pi(pix, piy);
        vector<G> pows(e + 1);
        pows[0] = G(1, 0);
        for (int i = 0; i < e; i++)
            pows[i + 1] = pows[i] * pi;
        if (p == 2) {
            for (auto &&g : res)
                g *= pows[e];
            continue;
        }
        vector<G> pis(e + 1);
        for (int j = 0; j < e + 1; j++) {
            pis[j] = pows[j] * (pows[e - j].conjugate());
        }
        vector<G> new_res;
        new_res.reserve(sz(res) * (e + 1));
        for (auto &&g : res) {
            for (auto &&a : pis) {
                new_res.emplace_back(g * a);
            }
        }
        swap(res, new_res);
    }

    for (auto &&g : res) {
        while (g.x <= 0 || g.y < 0) {
            g = G(-g.y, g.x);
        }
    }
    return res;
}

template <typename T> vector<Gaussian_Integer<T>> solve_norm_equation(T N) {
    using G = Gaussian_Integer<T>;
    vector<G> res;
    if (N < 0)
        return {};
    if (N == 0) {
        res.emplace_back(G(0, 0));
        return res;
    }
    vector<pair<lint, int>> pfs;
    auto fct = factors::factorize(N);
    for (int i = 0; i < sz(fct);) {
        int j = i;
        while (j < sz(fct) && fct[j] == fct[i])
            j++;
        pfs.emplace_back(fct[i], j - i);
        i = j;
    }
    return solve_norm_equation_factor<T>(pfs);
}

vector<pair<lint, lint>> two_square(lint N, bool only_nonnegative) {
    vector<pair<lint, lint>> ANS;
    if (N == 0) {
        ANS.emplace_back(0, 0);
        return ANS;
    }
    if (only_nonnegative) {
        for (auto &g : solve_norm_equation<__int128>(N)) {
            ANS.emplace_back(g.x, g.y);
        }
        lint sqN = sqrtl(N);
        if (sqN * sqN == N)
            ANS.emplace_back(0, sqN);
        return ANS;
    }
    for (auto &g : solve_norm_equation<__int128>(N)) {
        for (int i = 0; i < 4; i++) {
            ANS.emplace_back(g.x, g.y);
            tie(g.x, g.y) = make_pair(g.y, g.x);
        }
    }
    return ANS;
}

// Given an integer N
// Find a list of integers with minimum size whose squares sums to N.
vector<lint> solve(lint n) {
    if (n % 4 == 0) {
        vector<lint> rec = solve(n / 4);
        for (auto &x : rec)
            x *= 2;
        return rec;
    }
    if (n % 8 == 7) {
        vector<lint> rec = solve(n - 1);
        rec.push_back(1);
        return rec;
    }
    for (lint i = 0;; i++) {
        auto v = two_square(n - i * i, true);
        if (sz(v)) {
            vector<lint> q;
            if (i)
                q.push_back(i);
            for (auto &[a, b] : v) {
                if (a == 0) {
                    q.push_back(b);
                    return q;
                }
            }
            q.push_back((lint)v[0].first);
            q.push_back((lint)v[0].second);
            return q;
        }
    }
}

