//kuroni
#include <bits/stdc++.h>
#include <bit>
using namespace std;

const int INF = 100;
const int DX[4] = {-1, 0, 1, 0}, DY[4] = {0, -1, 0, 1};

int pw[10];
int dp[19683], move_1_trans[19683], move_2_trans[19683][512], move_3_trans[19683][512][2];
int transition[512], make_state[512][512];

void solve() {
    pw[0] = 1;
    for (int i = 1; i <= 9; i++) {
        pw[i] = pw[i - 1] * 3;
    }
    auto get_bit = [&](int state, int bit) {
        return state / pw[bit] % 3;
    };
    auto change_bit = [&](int state, int bit, int to) {
        state -= get_bit(state, bit) * pw[bit];
        state += to * pw[bit];
        return state;
    };
    auto valid = [&](int x, int y) {
        return x >= 0 && x < 3 && y >= 0 && y < 3;
    };
    auto to_cell = [&](int u) -> pair<int, int> { return {u / 3, u % 3}; };
    auto to_bit = [&](int x, int y) { return x * 3 + y; };
    fill(dp, dp + 19683, -1);

    // initialize transition and make_state
    for (int msk = 0; msk < (1 << 9); msk++) {
        int new_msk = 0;
        for (int i = 0; i < 9; i++) {
            if (msk >> i & 1) {
                auto [x, y] = to_cell(i);
                for (int d = 0; d < 4; d++) {
                    int nx = x + DX[d], ny = y + DY[d];
                    if (valid(nx, ny)) {
                        new_msk |= (1 << to_bit(nx, ny));
                    }
                }
            }
        }
        transition[msk] = new_msk;
    }
    for (int u = 0; u < (1 << 9); u++) {
        for (int p = 0; p < (1 << 9); p++) {
            if ((u & p) > 0) {
                continue;
            }
            int ans = 0;
            for (int i = 0; i < 9; i++) {
                if (u >> i & 1) {
                    ans = change_bit(ans, i, 1);
                } else if (p >> i & 1) {
                    ans = change_bit(ans, i, 2);
                }
            }
            make_state[u][p] = ans;
        }
    }

    function<int(int)> do_dp = [&](int state) -> int {
        if (dp[state] != -1) {
            return dp[state];
        }
        int unavailable = 0, current_possible = 0;
        {
            for (int i = 0; i < 9; i++) {
                int x = get_bit(state, i);
                if (x == 1) {
                    unavailable |= (1 << i);
                } else if (x == 2) {
                    current_possible |= (1 << i);
                }
            }
        }
        int& best_1 = dp[state];
        int& move_1 = move_1_trans[state];
        if (current_possible == 0) {
            return best_1 = 0;
        }
        best_1 = INF; move_1 = -1;
        for (int sub = 0; sub < (1 << 9); sub++) {
            if ((sub & unavailable) > 0) {
                continue;
            }
            int best_2 = -INF;
            int& move_2 = move_2_trans[state][sub];
            {
                // outside
                int tmp_possible = current_possible & (~sub);
                int best_3 = INF;
                int& move_3 = move_3_trans[state][sub][0];
                for (int i = 0; i < 9; i++) {
                    if (!(unavailable >> i & 1)) {
                        int new_unavail = unavailable | (1 << i);
                        int new_possible = transition[tmp_possible] & (~new_unavail);
                        int new_state = make_state[new_unavail][new_possible];
                        if (int best_4 = do_dp(new_state); best_4 < best_3) {
                            best_3 = best_4;
                            move_3 = i;
                        }
                    }
                }
                if (best_3 > best_2) {
                    best_2 = best_3;
                    move_2 = 0;
                }
            }
            {
                // inside
                int tmp_possible = current_possible & sub;
                int best_3 = INF;
                int& move_3 = move_3_trans[state][sub][1];
                for (int i = 0; i < 9; i++) {
                    if (!(unavailable >> i & 1)) {
                        int new_unavail = unavailable | (1 << i);
                        int new_possible = transition[tmp_possible] & (~new_unavail);
                        int new_state = make_state[new_unavail][new_possible];
                        if (int best_4 = do_dp(new_state); best_4 < best_3) {
                            best_3 = best_4;
                            move_3 = i;
                        }
                    }
                }
                if (best_3 > best_2) {
                    best_2 = best_3;
                    move_2 = 1;
                }
            }
            if (best_2 < best_1) {
                best_1 = best_2;
                move_1 = sub;
            }
        }
        return ++best_1;
    };

    int r, u; cin >> r >> u;
    int unavailable = 0, current_possible = (1 << 9) - 1;
    for (int i = 0; i < u; i++) {
        int k; cin >> k; k--;
        unavailable |= (1 << k);
    }
    current_possible &= (~unavailable);
    int state = make_state[unavailable][current_possible];
    auto print_state = [&](int unavailable, int current_possible, int state) {
        for (int x : {unavailable, current_possible}) {
            cerr << "[";
            for (int i = 0; i < 9; i++) {
                if (x >> i & 1) {
                    cerr << i + 1 << "";
                }
            }
            cerr << "] ";
        }
        cerr << dp[state] << endl;
    };
    if (do_dp(state) <= r) {
        // solve as trapper
        cout << "Trapper" << endl;
        for (int st = 0; st < r; st++) {
            // // print_state();
            int sub = move_1_trans[state];
            cout << popcount((unsigned)sub) << endl;
            if (sub != 0) {
                for (int i = 0; i < 9; i++) {
                    if (sub >> i & 1) {
                        cout << i + 1 << " ";
                    }
                }
                cout << endl;
            }
            string s; cin >> s;
            if (s == "Yes") {
                int tmp_possible = current_possible & sub;
                int i = move_3_trans[state][sub][1];
                cout << i + 1 << endl;
                int new_unavail = unavailable | (1 << i);
                int new_possible = transition[tmp_possible] & (~new_unavail);
                int new_state = make_state[new_unavail][new_possible];
                cin >> s;
                if (s == "Free") {
                    unavailable = new_unavail;
                    current_possible = new_possible;
                    state = new_state;
                    assert(current_possible > 0);
                } else {
                    return;
                }
            } else {
                int tmp_possible = current_possible & (~sub);
                int i = move_3_trans[state][sub][0];
                cout << i + 1 << endl;
                int new_unavail = unavailable | (1 << i);
                int new_possible = transition[tmp_possible] & (~new_unavail);
                int new_state = make_state[new_unavail][new_possible];
                cin >> s;
                if (s == "Free") {
                    unavailable = new_unavail;
                    current_possible = new_possible;
                    state = new_state;
                    assert(current_possible > 0);
                } else {
                    return;
                }
            }
        }
    } else {
        // solve as runner
        cout << "Runner" << endl;
        vector<int> all_possible;
        for (int st = 0; st < r; st++) {
            // // print_state();
            int sub = 0;
            {
                int k; cin >> k;
                for (int i = 0; i < k; i++) {
                    int x; cin >> x; x--;
                    sub |= (1 << x);
                }
            }
            int answer = move_2_trans[state][sub];
            int tmp_possible;
            if (answer == 1) {
                cout << "Yes" << endl;
                tmp_possible = current_possible & sub;
            } else {
                cout << "No" << endl;
                tmp_possible = current_possible & (~sub);
            }
            // print_state(unavailable, tmp_possible, dp[state]);
            all_possible.push_back(tmp_possible);
            int i; cin >> i; i--;
            int new_unavail = unavailable | (1 << i);
            int new_possible = transition[tmp_possible] & (~new_unavail);
            int new_state = make_state[new_unavail][new_possible];
            assert(new_possible > 0);
            cout << "Free" << endl;
            unavailable = new_unavail;
            current_possible = new_possible;
            state = new_state;
        }
        all_possible.push_back(current_possible);
        assert(current_possible > 0);
        // print_state(unavailable, current_possible, state);
        vector<int> movs;
        int i = countr_zero((unsigned)current_possible);
        movs.push_back(i);
        for (int st = r - 1; st >= 0; st--) {
            int back_possible = all_possible[st];
            auto [x, y] = to_cell(i);
            // print_state(0, back_possible, 0);
            // cerr << i + 1 << " " << x << " " << y << '\n';
            bool ok = false;
            for (int d = 0; d < 4; d++) {
                int nx = x + DX[d], ny = y + DY[d];
                if (valid(nx, ny)) {
                    int ni = to_bit(nx, ny);
                    // cerr << ni << '\n';
                    if (back_possible >> ni & 1) {
                        i = ni;
                        movs.push_back(i);
                        ok = true;
                        break;
                    }
                }
            }
            assert(ok);
        }
        reverse(movs.begin(), movs.end());
        for (int i = 0; i <= r; i++) {
            cout << movs[i] + 1 << " ";
        }
        cout << endl;
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1; // cin >> t;
    while (t--) {
        solve();
    }
}