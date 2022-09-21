// find det(xI - A)
// https://tistory.joonhyung.xyz/19
// https://rkm0959.tistory.com/141?category=743276
vector<mint> hessenberg(vector<vector<mint>> a){
    int n = sz(a);
    for(int i = 0; i+1 < n; i++){
        int j = i+1;
        while(j < n && a[j][i] == mint(0)) j++;
        if(j == n) continue;
        for(int k = 0; k < n; k++){
            swap(a[i+1][k], a[j][k]);
        }
        for(int k = 0; k < n; k++){
            swap(a[k][j], a[k][i+1]);
        }
        assert(a[i+1][i] != mint(0));
        for(int k = i+2; k < n; k++){
            mint gyesu = a[k][i] / a[i+1][i];
            for(int l = 0; l < n; l++){
                a[k][l] -= gyesu * a[i+1][l];
            }
            for(int l = 0; l < n; l++){
                a[l][i+1] += a[l][k] * gyesu;
            }
        }
    }
    vector<vector<mint>> dp(n + 1);
    dp[0] = {mint(1)};
    for(int i = 1; i <= n; i++){
        dp[i].resize(i + 1);
        for(int j = 1; j <= i; j++){
            dp[i][j] = dp[i-1][j-1];
        }
        for(int j = 0; j < i; j++){
            dp[i][j] -= a[i-1][i-1] * dp[i-1][j];
        }
        mint mul = 1;
        for(int j = i - 2; j >= 0; j--){
            mul *= a[j + 1][j];
            for(int k = 0; k <= j; k++){
                dp[i][k] -= a[j][i - 1] * mul * dp[j][k];
            }
        }
    }
    return dp[n];
}

vector<mint> det_axplusb(vector<vector<mint>> A, vector<vector<mint>> B){
    int n = sz(A);
    int a = 0, b = 0;
    mint det = mint(1);
    auto rswap = [&](int x, int y){
        if(x == y) return;
        det = -det;
        for(int i = 0; i < n; i++){
            swap(A[x][i], A[y][i]);
            swap(B[x][i], B[y][i]);
        }
    };
    auto cswap = [&](int x, int y){
        if(x == y) return;
        det = -det;
        for(int i = 0; i < n; i++){
            swap(A[i][x], A[i][y]);
            swap(B[i][x], B[i][y]);
        }
    };
    while(a + b < n){
        for(int i = 0; i < a; i++){
            mint val = -A[i][a];
            for(int j = 0; j < n; j++){
                A[j][a] += A[j][i] * val;
                B[j][a] += B[j][i] * val;
            }
        }
        for(int i = a; i < n - b; i++){
            if(A[i][a] != mint(0)){
                rswap(a, i);
                break;
            }
        }
        if(A[a][a] != mint(0)){
            det *= A[a][a];
            mint mul = mint(1) / A[a][a];
            for(int i = 0; i < n; i++){
                A[a][i] *= mul;
                B[a][i] *= mul;
            }
            for(int i = a + 1; i < n; i++){
                mint mul = -A[i][a];
                for(int j = 0; j < n; j++){
                    A[i][j] += A[a][j] * mul;
                    B[i][j] += B[a][j] * mul;
                }
            }
            a++;
        }
        else{
            int r = n - 1 - b;
            cswap(a, r);
            int pos = r;
            while(pos >= 0 && B[pos][r] == mint(0)) pos--;
            if(pos == -1){
                // zero polynomial
                return vector<mint>(n + 1);
            }
            if(pos < a){
                rswap(pos, a - 1);
                cswap(pos, a - 1);
                rswap(a - 1, r);
                a--;
            }
            else{
                rswap(pos, r);
            }
            det *= B[r][r];
            mint mul = mint(1) / B[r][r];
            for(int i = 0; i < n; i++){
                A[r][i] *= mul;
                B[r][i] *= mul;
            }
            for(int i = 0; i < r; i++){
                mint mul = -B[i][r];
                for(int j = 0; j < n; j++){
                    A[i][j] += A[r][j] * mul;
                    B[i][j] += B[r][j] * mul;
                }
            }
            b++;
        }
    }
    vector<vector<mint>> C(a, vector<mint>(a));
    for(int i = 0; i < a; i++){
        for(int j = 0; j < a; j++){
            C[i][j] = -B[i][j];
        }
    }
    vector<mint> ans = hessenberg(C);
    for(auto &x : ans) x *= det;
    ans.resize(n + 1);
    return ans;
}

vector<mint> hessenberg_anymod(vector<vector<mint>> a){
    int n = sz(a);
    for(int i = 0; i+1 < n; i++){
        int j = i+1;
        while(j < n && a[j][i] == mint(0)) j++;
        if(j == n) continue;
        for(int k = 0; k < n; k++){
            swap(a[i+1][k], a[j][k]);
        }
        for(int k = 0; k < n; k++){
            swap(a[k][j], a[k][i+1]);
        }
        assert(a[i+1][i] != mint(0));
        for(int k = i+2; k < n; k++){
            while(a[k][i] != mint(0)){
                for(int l = 0; l < n; l++){
                    swap(a[k][l], a[i + 1][l]);
                }
                for(int l = 0; l < n; l++){
                    swap(a[l][k], a[l][i + 1]);
                }
                mint gyesu = mint(a[k][i].val / a[i + 1][i].val);
                for(int l = 0; l < n; l++){
                    a[k][l] -= gyesu * a[i+1][l];
                }
                for(int l = 0; l < n; l++){
                    a[l][i+1] += a[l][k] * gyesu;
                }
            }
        }
    }
    vector<vector<mint>> dp(n + 1);
    dp[0] = {mint(1)};
    for(int i = 1; i <= n; i++){
        dp[i].resize(i + 1);
        for(int j = 1; j <= i; j++){
            dp[i][j] = dp[i-1][j-1];
        }
        for(int j = 0; j < i; j++){
            dp[i][j] -= a[i-1][i-1] * dp[i-1][j];
        }
        mint mul = 1;
        for(int j = i - 2; j >= 0; j--){
            mul *= a[j + 1][j];
            for(int k = 0; k <= j; k++){
                dp[i][k] -= a[j][i - 1] * mul * dp[j][k];
            }
        }
    }
    return dp[n];
}