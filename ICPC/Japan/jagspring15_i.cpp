#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<lint, lint> pi;
const int MAXN = 100005;

namespace fft{
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

    vector<lint> multiply(vector<lint> &v, vector<lint> &w){
        vector<base> fv(v.begin(), v.end()), fw(w.begin(), w.end());
        int n = 1;
        while(n < max(v.size(), w.size())) n <<= 1;
        n <<= 1;
        fv.resize(n);
        fw.resize(n);
        fft(fv, 0);
        fft(fw, 0);
        for(int i=0; i<n; i++) fv[i] *= fw[i];
        fft(fv, 1);
        vector<lint> ret(n);
        for(int i=0; i<n; i++) ret[i] = (lint)round(fv[i].real());
        return ret;
    }
    vector<lint> multiply(vector<lint> &v, vector<lint> &w, lint mod){
        int n = 1;
        while(n < max(v.size(), w.size())) n <<= 1;
        n <<= 1;
        vector<base> v1(n), v2(n);
        vector<base> r1(n), r2(n);
        for(int i=0; i<v.size(); i++){
            v1[i] = base(v[i] >> 15, v[i] & 32767);
        }
        for(int i=0; i<w.size(); i++){
            v2[i] = base(w[i] >> 15, w[i] & 32767);
        }
        fft(v1, 0);
        fft(v2, 0);
        for(int i=0; i<n; i++){
            int j = (i ? (n - i) : i);
            base ans1 = (v1[i] + conj(v1[j])) * base(0.5, 0);
            base ans2 = (v1[i] - conj(v1[j])) * base(0, -0.5);
            base ans3 = (v2[i] + conj(v2[j])) * base(0.5, 0);
            base ans4 = (v2[i] - conj(v2[j])) * base(0, -0.5);
            r1[i] = (ans1 * ans3) + (ans1 * ans4) * base(0, 1);
            r2[i] = (ans2 * ans3) + (ans2 * ans4) * base(0, 1);
        }
        fft(r1, 1);
        fft(r2, 1);
        vector<lint> ret(n);
        for(int i=0; i<n; i++){
            lint av = (lint)round(r1[i].real());
            lint bv = (lint)round(r1[i].imag()) + (lint)round(r2[i].real());
            lint cv = (lint)round(r2[i].imag());
            av %= mod, bv %= mod, cv %= mod;
            ret[i] = (av << 30) + (bv << 15) + cv;
            ret[i] %= mod;
            ret[i] += mod;
            ret[i] %= mod;
        }
        return ret;
    }
}


lint ccw(pi a, pi b, pi c){
    lint dx1 = b.first - a.first;
    lint dy1 = b.second - a.second;
    lint dx2 = c.first - a.first;
    lint dy2 = c.second - a.second;
    return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}

lint ccw(pi a, pi b){ return ccw(pi(0, 0), a, b); }
int gcd(int x, int y){ return y ? gcd(y, x%y) : x; }

int n, m, k;
pi sa, sb, sc, da, db, dc;
int cnt1[2 * MAXN], cnt2[2 * MAXN], cnt3[2 * MAXN];

pi p[MAXN];

void input(int *a, pi &pos, pi &dir, int n){
    for(int i=0; i<n; i++){
        int x, y;
        scanf("%d %d",&x,&y);
        p[i] = pi(x, y);
    }
    sort(p, p + n);
    if(p[0] == p[n-1]){
        pos = p[0];
        dir = pi(0, 1);
        a[0] = n;
    }
    else{
        pos = p[0];
        dir = pi(p[n-1].first - p[0].first, p[n-1].second - p[0].second);
        int g = gcd(abs(dir.first), abs(dir.second));
        dir.first /= g;
        dir.second /= g;
        for(int i=0; i<n; i++){
            int x = abs(p[i].first - p[0].first) + abs(p[i].second - p[0].second);
            int y = abs(dir.first) + abs(dir.second);
            a[x / y]++;
        }
    }
}

int main(){
    scanf("%d %d %d",&n,&m,&k);
    input(cnt1, sa, da, n);
    input(cnt2, sb, db, m);
    input(cnt3, sc, dc, k);
    if(da == db){
        vector<lint> p1(MAXN * 2), p2(MAXN * 2);
        for(int i=0; i<2*MAXN; i++) p1[i] = cnt1[i];
        for(int i=0; i<2*MAXN; i++) p2[i] = cnt2[i];
        auto ans = fft::multiply(p1, p2);
        map<pi, lint> mp;
        for(int i=0; i<4*MAXN; i++){
            int cx = sa.first + sb.first + i * da.first;
            int cy = sa.second + sb.second + i * da.second;
            mp[pi(cx, cy)] = ans[i];
        }
        lint dap = 0;
        for(int i=0; i<2*MAXN; i++){
            auto l = mp.find(pi(2 * sc.first + 2 * dc.first * i, 2 * sc.second + 2 * dc.second * i));
            if(l != mp.end()) dap += l->second * cnt3[i];
        }
        cout << dap << endl;
        return 0;
    }
    else{
        pi dx = pi(db.first - da.first, db.second - da.second);
        pi is = sc;
        pi ie = pi(sc.first + dc.first, sc.second + dc.second);
        is.first *= 2;
        is.second *= 2;
        ie.first *= 2;
        ie.second *= 2;
        if(ccw(pi(0, 0), dx, dc) == 0){
            lint ret = 0;
            for(int i=0; i<4*MAXN; i++){
                pi cur = pi(sa.first + sb.first + i * da.first, sa.second + sb.second + i * da.second);
                if(ccw(is, ie, cur) == 0){
                    for(int j=max(0, i-2*MAXN+1); j<=i && j<2*MAXN; j++){
                        lint k = 1ll * cnt1[i-j] * cnt2[j];
                        pi x = pi(cur.first + j * dx.first, cur.second + j * dx.second);
                        if(x.first % 2 || x.second % 2) continue;
                        x.first /= 2;
                        x.second /= 2;
                        if(dc.first){
                            lint arg = (x.first - sc.first) / dc.first;
                            if(arg < 2 * MAXN && arg >= 0) ret += k * cnt3[arg];
                        }
                        else{
                            lint arg = (x.second - sc.second) / dc.second;
                            if(arg < 2 * MAXN && arg >= 0) ret += k * cnt3[arg];
                        }
                    }
                }
            }
            cout << ret << endl;
        }
        else{
            lint ret = 0;
            for(int i=0; i<4*MAXN; i++){
                pi cur = pi(sa.first + sb.first + i * da.first, sa.second + sb.second + i * da.second);
                int s = 0, e = i;
                while(s != e){
                    int m = (s+e)/2;
                    pi x = pi(cur.first + m * dx.first, cur.second + m * dx.second);
                    pi y = pi(cur.first + (m+1) * dx.first, cur.second + (m+1) * dx.second);
                    if(abs(ccw(is, ie, x)) < abs(ccw(is, ie, y))) e = m;
                    else s = m+1;
                }
                pi x = pi(cur.first + s * dx.first, cur.second + s * dx.second);
                if(ccw(is, ie, x) == 0 && s < 2 * MAXN && i-s < 2 * MAXN){
                    lint k = 1ll * cnt1[i-s] * cnt2[s];
                    if(x.first % 2 || x.second % 2) continue;
                    x.first /= 2;
                    x.second /= 2;
                    if(dc.first){
                        lint arg = (x.first - sc.first) / dc.first;
                        if(arg < 2 * MAXN && arg >= 0) ret += k * cnt3[arg];
                    }
                    else{
                        lint arg = (x.second - sc.second) / dc.second;
                        if(arg < 2 * MAXN && arg >= 0) ret += k * cnt3[arg];    
                    }
                }
            }
            cout << ret << endl;
        }
    }
}
