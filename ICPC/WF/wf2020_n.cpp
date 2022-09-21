#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

vector<vector<double>> trans(vector<vector<double>> A){
    int n = sz(A), m = sz(A[0]);
    vector<vector<double>> B(m, vector<double>(n));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            B[j][i] = A[i][j];
        }
    }
    return B;
}

double dot(vector<double> &a, vector<double> &b){
    assert(sz(a) == sz(b));
    double ret = 0;
    for(int i = 0; i < sz(a); i++) ret += a[i] * b[i];
    return ret;
}

pair<vector<vector<double>>, vector<double>> getLeastNorm(vector<vector<double>> A, vector<double> b){
    int m = sz(A), n = sz(A[0]); // dont ask why
    assert(m <= n);
    vector<vector<double>> U = A;
    for(int i = 0; i < m; i++){
        double coeff = sqrt(dot(U[i], U[i]));
        vector<double> q(n);
        for(int j = 0; j < n; j++) q[j] = U[i][j] / coeff;
        for(int j = i + 1; j < m; j++){
            double coeff = dot(q, U[j]);
            for(int k = 0; k < n; k++) U[j][k] -= coeff * q[k];
        }
    }
    vector<vector<double>> Q(m, vector<double>(n));
    vector<vector<double>> R(m, vector<double>(m));
    for(int i = 0; i < m; i++){
        double norm = sqrt(dot(U[i], U[i]));
        for(int j = 0; j < n; j++){
            Q[i][j] = U[i][j] / norm;
        }
    }
    for(int i = 0; i < m; i++){
        for(int j = i; j < m; j++){
            R[i][j] = dot(Q[i], A[j]);
        }
    }
    Q = trans(Q);
    A = trans(A);
    vector<vector<double>> inv(m, vector<double>(m));
    for(int i = m - 1; i >= 0; i--){
        for(int j = i; j < m; j++){
            inv[i][j] = (i == j);
            for(int k = i; k < j; k++){
                inv[i][j] -= inv[i][k] * R[k][j];
            }
            inv[i][j] /= R[j][j];
        }
    }
    inv = trans(inv);
    vector<double> ans(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            double qrij = 0;
            for(int k = 0; k < m; k++){
                qrij += Q[i][k] * inv[k][j];
            }
            ans[i] += qrij * b[j];
        }
    }
    Q = trans(Q);
    return make_pair(Q, ans);
}

mt19937 rng(694201557);
int randint(int lb, int ub){ return uniform_int_distribution<int>(lb, ub)(rng); }

vector<double> getVectorFromKernel(vector<vector<double>> Q){
    int n = sz(Q), m = sz(Q[0]);
    vector<double> b(m);
    for(int i = 0; i < m; i++) b[i] = randint(-696969, 696969);
    for(auto &x : Q){
        auto d = dot(b, x);
        for(int j = 0; j < m; j++) b[j] -= d * x[j];
    }
    double sz = sqrt(dot(b, b));
    for(int j = 0; j < m; j++) b[j] /= sz;
    return b;
}

int main(){ 
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    int d, n; cin >> d >> n;
    n = min(n, d + 1); // inputs are independent, anyway
    vector<vector<double>> v(n, vector<double>(d));
    vector<double> e(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < d; j++) cin >> v[i][j];
        cin >> e[i];
    }
    if(n == 1){
        v[0][0] += e[0];
        for(int i = 0; i < d; i++) cout << setprecision(69) << v[0][i] << " ";
        return 0;
    }
    vector<vector<double>> A(n - 1, vector<double>(d));
    vector<double> b(n - 1);
    for(int i = 0; i < n - 1; i++){
        for(int j = 0; j < d; j++){
            A[i][j] = 2 * v[i][j] - 2 * v[n - 1][j];
        }
        b[i] = dot(A[i], A[i]) / 4 + e[n - 1] * e[n - 1] - e[i] * e[i];
    }
    auto [Q, sln] = getLeastNorm(A, b);
    double toAdd = sqrt(e[n - 1] * e[n - 1] - dot(sln, sln));
    if(n != d + 1){
        vector<double> vec = getVectorFromKernel(Q);
        for(int j = 0; j < d; j++) sln[j] += vec[j] * toAdd;
    }
    for(int j = 0; j < d; j++) sln[j] += v[n - 1][j];
    for(int i = 0; i < d; i++) cout << setprecision(69) << sln[i] << " ";
}
