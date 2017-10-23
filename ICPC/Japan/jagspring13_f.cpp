#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;
const int MAXN = 2048;
typedef complex<double> base;

void fft(vector<base> &a, bool inv){
    int n = a.size(), j = 0;
    vector<base> roots(n/2);
    for(int i=1; i<n; i++){
        int bit = (n >> 1);
        while(j >= bit){
            j -= bit;
            bit >>= 1;
        }
        j += bit;
        if(i < j) swap(a[i], a[j]);
    }
    double ang = 2 * acos(-1) / n * (inv ? -1 : 1);
    for(int i=0; i<n/2; i++){
        roots[i] = base(cos(ang * i), sin(ang * i));
    }
    for(int i=2; i<=n; i<<=1){
        int step = n / i;
        for(int j=0; j<n; j+=i){
            for(int k=0; k<i/2; k++){
                base u = a[j+k], v = a[j+k+i/2] * roots[step * k];
                a[j+k] = u+v;
                a[j+k+i/2] = u-v;
            }
        }
    }
    if(inv) for(int i=0; i<n; i++) a[i] /= n;
}

int n, m;
base a[MAXN][MAXN], b[MAXN][MAXN];
lint chk[2200000];

int main(){
    scanf("%d",&n);
    int k = 0, l = 0;;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            int x;
            scanf("%d",&x);
            k += x * (x - 1) / 2;
            l += x;
            b[n-1-i][n-j-1] = a[i][j] = base(x, 0);
        }
    }
    m = 1;
    while(m < n) m <<= 1;
    m <<= 1;
    for(int i=0; i<m; i++){
        vector<base> v(m);
        for(int j=0; j<m; j++){
            v[j] = a[i][j];
        }
        fft(v, false);
        for(int j=0; j<m; j++){
            a[i][j] = v[j];
            v[j] = b[i][j];
        }
        fft(v, false);
        for(int j=0; j<m; j++){
            b[i][j] = v[j];
        }
    }
    for(int i=0; i<m; i++){
        vector<base> v(m);
        for(int j=0; j<m; j++){
            v[j] = a[j][i];
        }
        fft(v, false);
        for(int j=0; j<m; j++){
            a[j][i] = v[j];
            v[j] = b[j][i];
        }
        fft(v, false);
        for(int j=0; j<m; j++){
            b[j][i] = v[j];
        }
    }
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            a[i][j] = a[i][j] * b[i][j];
        }
    }
    for(int i=0; i<m; i++){
        vector<base> v(m);
        for(int j=0; j<m; j++){
            v[j] = a[j][i];
        }
        fft(v, true);
        for(int j=0; j<m; j++){
            a[j][i] = v[j];
        }
    }
    for(int i=0; i<m; i++){
        vector<base> v(m);
        for(int j=0; j<m; j++){
            v[j] = a[i][j];
        }
        fft(v, true);
        for(int j=0; j<m; j++){
            a[i][j] = v[j];
        }
    }
    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            int r = (int)round(a[i][j].real());
            int dx = i - (n - 1), dy = j - (n - 1);
            chk[dx * dx + dy * dy] += r;
        }
    }
    chk[0] = k * 2;
    long double ret = 0;
    for(int i=0; i<2200000; i++){
        chk[i] /= 2;
        ret += 1.0 * sqrt(i) * chk[i];
    }
    ret /= 1ll * l * (l - 1) / 2;
    printf("%.11Lf\n", ret);
    int cnt = 0;
    for(int i=0; i<2200000; i++){
        if(chk[i] && cnt < 10000){
            printf("%d %lld\n", i, chk[i]);
            cnt++;
        }
    }
}
