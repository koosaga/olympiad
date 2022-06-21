namespace ds{
    vector<int> sfx, rev, lcp;
    int spt[19][MAXN], lg[MAXN], n;

    int get_lcp(int s, int e){
        if(s == 2 * n + 1 || e == 2 * n + 1) return 0;
        s = rev[s]; e = rev[e];
        if(s > e) swap(s, e);
        int l = lg[e - s];
        return min(spt[l][e - 1], spt[l][s + (1<<l) - 1]);
    }

    int get_lcp_rev(int s, int e){
        return get_lcp(2*n+1-s, 2*n+1-e);
    }

    void prep(string str){
        n = sz(str);
        string s = str;
        string r = s; reverse(all(r));
        s = s + "#" + r;
        sfx = yosupo::suffix_array(s);
        lcp = yosupo::lcp_array(s, sfx);
        rev.resize(sz(sfx));
        for(int i=0; i<sz(sfx); i++) rev[sfx[i]] = i;
        for(int i=1; i<MAXN; i++){
            lg[i] = lg[i-1];
            while((2 << lg[i]) <= i) lg[i]++;
        }
        for(int i=0; i<sz(sfx)-1; i++) spt[0][i] = lcp[i];
        for(int i=1; i<19; i++){
            for(int j=0; j<sz(sfx); j++){
                spt[i][j] = spt[i-1][j];
                if(j >= (1<<(i-1))) spt[i][j] = min(spt[i][j], spt[i-1][j-(1<<(i-1))]);
            }
        }
    }
}

struct runs{
    int t, l, r;
    bool operator<(const runs &x)const{
        return make_tuple(t, l, r) < make_tuple(x.t, x.l, x.r);
    }
    bool operator==(const runs &x)const{
        return make_tuple(t, l, r) == make_tuple(x.t, x.l, x.r);
    }
};

vector<runs> run_enumerate(string s){
    int n = sz(s);
    vector<pi> v;
    auto get_interval = [&](string t){
        auto sfx = yosupo::suffix_array(t);
        vector<int> rev(n + 1);
        for(int i = 0; i < n; i++) rev[sfx[i]] = i;
        rev[n] = -1;
        vector<int> stk = {n}, ans(n);
        for(int i = n - 1; i >= 0; i--){
            while(sz(stk) && rev[stk.back()] > rev[i]) stk.pop_back();
            v.emplace_back(i, stk.back());
            stk.push_back(i);
        }
    };
    ds::prep(s);
    get_interval(s);
    for(auto &i : s) i = 'a' + 'z' - i;
    get_interval(s);
    vector<runs> ans;
    for(auto &[x, y] : v){
        int s = x - ds::get_lcp_rev(x, y);
        int e = y + ds::get_lcp(x, y);
        int p = y - x;
        if(e - s >= 2 * p){
            ans.push_back({p, s, e});
        }
    }
    sort(all(ans));
    ans.resize(unique(all(ans)) - ans.begin());
    return ans;
}