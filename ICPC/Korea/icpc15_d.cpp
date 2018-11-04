#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct sweep{
    int s, e, x, dx;
    bool operator<(const sweep &s)const{
        return x < s.x;
    }
};

struct minseg{
    int tree[66000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        memset(tree, 0x3f, sizeof(tree));
    }
    void update(int s, int e, int x){
        s += lim;
        e += lim;
        while(s < e){
            if(s%2 == 1){
                tree[s] = min(tree[s], x);
                s++;
            }
            if(e%2 == 0){
                tree[e] = min(tree[e], x);
                e--;
            }
            s >>= 1;
            e >>= 1;
        }
        if(s == e) tree[s] = min(tree[s], x);
    }
    int query(int x){
        x += lim;
        int ret = 1e9;
        while(x){
            ret = min(ret, tree[x]);
            x >>= 1;
        }
        return ret;
    }
}minx, miny;

struct maxseg{
    int tree[66000], lim;
    void init(int n){
        for(lim = 1; lim <= n; lim <<= 1);
        memset(tree, 0, sizeof(tree));
    }
    void update(int s, int e, int x){
        s += lim;
        e += lim;
        while(s < e){
            if(s%2 == 1){
                tree[s] = max(tree[s], x);
                s++;
            }
            if(e%2 == 0){
                tree[e] = max(tree[e], x);
                e--;
            }
            s >>= 1;
            e >>= 1;
        }
        if(s == e) tree[s] = max(tree[s], x);
    }
    int query(int x){
        x += lim;
        int ret = 0;
        while(x){
            ret = max(ret, tree[x]);
            x >>= 1;
        }
        return ret;
    }

}maxx, maxy;

int n, sx[20005], ex[20005], sy[20005], ey[20005];
pi a[10005];

int dir(pi a, pi b){
    if(a.first == b.first){
        if(a.second < b.second) return 1;
        return 3;
    }
    if(a.first < b.first) return 0;
    return 2;
}

int main(){
    int tc;
    cin >> tc;
    while(tc--){
        scanf("%d",&n);
        vector<int> vx, vy;
        for(int i=0; i<n; i++){
            scanf("%d %d",&a[i].first, &a[i].second);
            vx.push_back(a[i].first);
            vy.push_back(a[i].second);
        }
        minx.init(2*n);
        miny.init(2*n);
        maxx.init(2*n);
        maxy.init(2*n);
        sort(vx.begin(), vx.end());
        sort(vy.begin(), vy.end());
        vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
        vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
        for(int i=0; i<n; i++){
            a[i].first = lower_bound(vx.begin(), vx.end(), a[i].first) - vx.begin();
            a[i].second = lower_bound(vy.begin(), vy.end(), a[i].second) - vy.begin();
        }
        a[n] = a[0];
        a[n+1] = a[1];
        vector<sweep> swp;
        for(int i=0; i<n; i++){
            int p1 = dir(a[i], a[i+1]);
            if(p1 == 0){
                swp.push_back({2*a[i].first, 2*a[i+1].first, 2*a[i].second, 1});
                maxy.update(2*a[i].first+1, 2*a[i+1].first-1, 2*a[i].second);
            }
            if(p1 == 1){
                minx.update(2*a[i].second+1, 2*a[i+1].second-1, 2*a[i].first);
            }
            if(p1 == 2){
                swp.push_back({2*a[i+1].first, 2*a[i].first, 2*a[i].second+1, -1});
                miny.update(2*a[i+1].first+1, 2*a[i].first-1, 2*a[i].second);
            }
            if(p1 == 3){
                maxx.update(2*a[i+1].second+1, 2*a[i].second-1, 2*a[i].first);
            }
        }
        for(int i=1; i<=n; i++){
            int p1 = dir(a[i-1], a[i]), p2 = dir(a[i], a[i+1]);
            if((p1 + 1) % 4 == p2){
                // fuck me
                if(p1 == 0){
                    maxy.update(2*a[i].first+1, 2*n, 2*a[i].second+1);
                    maxy.update(2*a[i].first,2*a[i].first,2*a[i].second);
                    minx.update(0, 2*a[i].second-1, 2*a[i].first-1);
                    minx.update(2*a[i].second, 2*a[i].second, 2*a[i].first);
                }
                if(p1 == 1){
                    miny.update(2*a[i].first,2*a[i].first,2*a[i].second);
                    minx.update(2*a[i].second, 2*a[i].second, 2*a[i].first);
                    minx.update(2*a[i].second+1, 2*n, 2*a[i].first-1);
                    miny.update(2*a[i].first+1, 2*n, 2*a[i].second-1);
                }
                if(p1 == 2){
                    miny.update(2*a[i].first,2*a[i].first,2*a[i].second);
                    maxx.update(2*a[i].second, 2*a[i].second, 2*a[i].first);
                    miny.update(0, 2*a[i].first-1, 2*a[i].second-1);
                    maxx.update(2*a[i].second+1, 2*n, 2*a[i].first+1);
                }
                if(p1 == 3){
                    maxx.update(0, 2*a[i].second-1, 2*a[i].first+1);
                    maxy.update(0, 2*a[i].first-1, 2*a[i].second+1);
                    maxx.update(2*a[i].second, 2*a[i].second, 2*a[i].first);
                    maxy.update(2*a[i].first,2*a[i].first,2*a[i].second);
                }
            }
        }
        for(int i=0; i<=2*n; i++){
            sx[i] = maxy.query(i);
            ex[i] = miny.query(i);
            sy[i] = maxx.query(i);
            ey[i] = minx.query(i);
            ex[i] = min(ex[i], 2 * (int)vy.size());
            ey[i] = min(ey[i], 2 * (int)vx.size());
        }
        int dx[20005] = {};
        sort(swp.begin(), swp.end());
        int e = 0;
        bool ok = 0;
        for(int i=0; i<=2*vy.size(); i++){
            while(e < swp.size() && swp[e].x <= i){
                for(int j=swp[e].s+1; j<=swp[e].e; j+=2){
                    dx[j] += swp[e].dx;
                }
                e++;
            }
            for(int j=sy[i]; j<=ey[i]; j++){
                if(dx[j] || dx[j+1] || (j > 0 && dx[j-1])){

                    if(sx[j] <= i && i <= ex[j]){
                        puts("YES");
                        ok = 1;
                        break;
                    }
                }
            }
            if(ok) break;
        }
        if(!ok) puts("NO");
    }
}
