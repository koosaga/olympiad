// Karatsuba (can't compile locally..)
// Credit: qwerasdfzxcl 
// https://judge.yosupo.jp/submission/355995

#include <bits/stdc++.h>
#include <immintrin.h>

using namespace std;
using ll = long long;
using ull = unsigned long long;

constexpr int threshold = 32;

vector<ull> naive(const vector<ull> &A, const vector<ull> &B){
    int n = A.size();
    vector<ull> C(n*2);

    static __m128i a[threshold];
    static __m128i b[threshold];
    static __m128i c[threshold * 2];

    for (int i=0;i<n;i++) a[i] = _mm_set_epi64x(0, A[i]);
    for (int i=0;i<n;i++) b[i] = _mm_set_epi64x(0, B[i]);
    for (int i=0;i<n*2;i++) c[i] = _mm_set_epi64x(0, 0);

    for (int i=0;i<n;i++) for (int j=0;j<n;j++){
        c[i+j] = _mm_xor_si128(c[i+j], _mm_clmulepi64_si128(a[i], b[j], 0x00));
    }

    for (int i=0;i<n*2;i++){
        ull L = _mm_cvtsi128_si64(c[i]);
        ull H = _mm_extract_epi64(c[i], 1);

        ull H_low = (H << 4) ^ (H << 3) ^ (H << 1) ^ H;
        ull H_high = (H >> 60) ^ (H >> 61) ^ (H >> 63);
        H_high = (H_high << 4) ^ (H_high << 3) ^ (H_high << 1) ^ H_high;

        C[i] = L ^ H_low ^ H_high;
    }
    
    return C;
}

vector<ull> dnc(const vector<ull> &A, const vector<ull> &B){
    int n = A.size();
    if (n <= threshold) return naive(A, B);

    auto low = dnc(vector<ull>(A.begin(), A.begin() + n/2), vector<ull>(B.begin(), B.begin() + n/2));
    auto high = dnc(vector<ull>(A.begin() + n/2, A.end()), vector<ull>(B.begin() + n/2, B.end()));

    vector<ull> a(A.begin(), A.begin() + n/2);
    for (int i=0;i<n/2;i++) a[i] ^= A[i+n/2];

    vector<ull> b(B.begin(), B.begin() + n/2);
    for (int i=0;i<n/2;i++) b[i] ^= B[i+n/2];

    auto mid = dnc(a, b);
    for (int i=0;i<n;i++) mid[i] ^= low[i] ^ high[i];

    vector<ull> ret(n*2);
    for (int i=0;i<n;i++) ret[i] ^= low[i];
    for (int i=0;i<n;i++) ret[i+n/2] ^= mid[i];
    for (int i=0;i<n;i++) ret[i+n] ^= high[i];

    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int n, m;
    cin >> n >> m;

    int N = 1;
    while(N < max(n, m)) N *= 2;

    vector<ull> a(N), b(N);
    for (int i=0;i<n;i++) cin >> a[i];
    for (int i=0;i<m;i++) cin >> b[i];

    auto ans = dnc(a, b);
    for (int i=0;i<n+m-1;i++) cout << ans[i] << ' ';
    cout << '\n';
}