#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = array<lint, 2>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
#define cr(v, n) (v).clear(), (v).resize(n);
const int MAXN = 1005;
bool localtest = true;

double beg[MAXN];
double probFirst[MAXN]; // p where first j of i contains something alive
double dp[MAXN][MAXN];  // when we know we have one in first i
double pwr[MAXN];

int opt[MAXN], opt2[MAXN][MAXN];

double f(int i, int k, int j) { return probFirst[k] / probFirst[j]; }
string dap, qstring;

int qcnt = 0;
bool query(string &s) {
    if (localtest) {
        qcnt++;
        for (int i = 0; i < sz(s); i++) {
            if (s[i] == '1' && qstring[i] == '1')
                return true;
        }
        return false;
    }
    cout << "Q " << s << endl;
    string t;
    cin >> t;
    return t == "P";
}

void ans() {
    if (localtest) {
        assert(dap == qstring);
        cerr << qcnt << endl;
        qcnt = 0;
        return;
    }
    cout << "A " << dap << endl;
    string q;
    cin >> q;
    assert(q == "C");
}

void go(int n, int k, vector<int> nondet, double p) {
    if (!sz(nondet)) {
        return;
    }
    int m = sz(nondet);

    if (k == 0) {
        k = opt[m];
        //  if (localtest)
        //      cout << m << " " << opt[m] << endl;
        string s(n, '0');
        for (int i = 0; i < k; i++)
            s[nondet[i]] = '1';
        if (query(s) == 0) {
            nondet.erase(nondet.begin(), nondet.begin() + k);
            go(n, 0, nondet, p);
            return;
        }
    }
    while (k > 1) {
        int k2 = opt2[m][k];
        string s(n, '0');
        for (int i = 0; i < k2; i++)
            s[nondet[i]] = '1';
        if (query(s) == 0) {
            nondet.erase(nondet.begin(), nondet.begin() + k2);
            go(n, k - k2, nondet, p);
            return;
        }
        k = k2;
    }
    dap[nondet[0]] = '1';
    nondet.erase(nondet.begin(), nondet.begin() + 1);
    go(n, 0, nondet, p);
}

int main() {
    int n;
    double p;
    cin >> n >> p;
    double cpwr = 1;
    for (int i = 1; i <= n; i++) {
        probFirst[i] = probFirst[i - 1] + p * cpwr;
        cpwr *= 1 - p;
    }
    for (int i = 1; i <= n; i++) {
        beg[i] = 1e18;
        for (int j = 1; j <= i; j++) {
            dp[i][j] = 1e18;
            if (j == 1) {
                dp[i][j] = beg[i - 1];
            }
            for (int k = 1; k < j; k++) {
                double nxt = 1 + f(i, k, j) * dp[i][k] + dp[i - k][j - k] * (1 - f(i, k, j));
                if (dp[i][j] > nxt) {
                    dp[i][j] = nxt;
                    opt2[i][j] = k;
                }
            }
            double nxt = 1 + probFirst[j] * dp[i][j] + (1 - probFirst[j]) * beg[i - j];
            if (beg[i] > nxt) {
                beg[i] = nxt;
                opt[i] = j;
            }
        }
        //  cout << endl;
        //  cout << i << " " << beg[i] << endl;
    }
    if (localtest)
        cout << beg[n] << "\n";
    int t;
    cin >> t;
    while (t--) {
        if (localtest) {
            qstring.clear();
            for (int i = 0; i < n; i++) {
                if (rand() % 1000000 < 1000000 * p)
                    qstring.push_back('1');
                else
                    qstring.push_back('0');
            }
        }
        dap = string(n, '0');
        vector<int> nondet(n);
        iota(all(nondet), 0);
        go(n, 0, nondet, p);
        ans();
    }
}