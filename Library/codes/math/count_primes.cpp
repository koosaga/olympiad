vector<bool> prime;
vector<int> primes;
vector<int> prime_count;

void sieve(int maximum) {
    maximum = max(maximum, 2);
    prime.assign(maximum + 1, true);
    prime[0] = prime[1] = false;
    primes = {};

    for (long long p = 2; p <= maximum; p++)
        if (prime[p]) {
            primes.push_back(p);

            for (long long i = p * p; i <= maximum; i += p)
                prime[i] = false;
        }

    prime_count.assign(maximum + 1, 0);

    for (int i = 1; i <= maximum; i++)
        prime_count[i] = prime_count[i - 1] + prime[i];
}

const int K_MEMO = 50;
const int N_MEMO = 1e5;

// Warning: if N_MEMO >= 2^17, this must be changed to a 32-bit integer.
uint16_t memo[K_MEMO][N_MEMO];

// Returns the number of integers in `[1, n]` that are not a multiple of any of `primes[0]` through `primes[k]`.
long long count_non_multiples(long long n, int k) {
    if (n <= 1 || k < 0)
        return n;

    long long p = primes[k];

    if (n <= p)
        return 1;

    if (n < (int) prime.size() && n <= p * p)
        return prime_count[n] - k;

    bool save = k < K_MEMO && n < N_MEMO;

    if (save && memo[k][n])
        return memo[k][n];

    // Count non-multiples ignoring `p`, and then subtract the multiples of `p` that aren't already included.
    long long ret = count_non_multiples(n, k - 1) - count_non_multiples(n / p, k - 1);

    if (save)
        memo[k][n] = ret;

    return ret;
}

// Returns the count of primes <= n. Runs in O(n^(3/4) / log n).
long long count_primes(long long n) {
    if (n < (int) prime.size())
        return prime_count[n];

    int s = (int) sqrt(n) + 1;
    assert(s < (int) prime.size());
    int k = prime_count[s];
    return count_non_multiples(n, k) + k;
}

const int SIEVE = 15e6;

int main() {
    sieve(SIEVE);

    int tests;
    cin >> tests;

    while (tests-- > 0) {
        long long N;
        cin >> N;
        long long bad = count_primes(N) - count_primes(N / 2) + 1;
        long long pairs = (N - bad) / 2;
        cout << N - pairs << '\n';
    }
}