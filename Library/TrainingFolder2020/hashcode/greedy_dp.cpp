#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <bitset>
#include <map>
#include <set>
#include <tuple>
#include <string.h>
#include <math.h>
#include <random>
#include <functional>
#include <assert.h>
#include <math.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

int B, L, D;
int score[MAXN];

struct output_buffer {
    vector<vector<int>> v;
    void print(vector<int> w) {
        v.push_back(w);
    }
    void flush() {
        cout << sz(v) / 2 << endl;
        for (auto &i : v) {
            for (auto &j : i) {
                printf("%d ", j);
            }
            puts("");
        }
    }
}buf;

struct library {
    int signup, speed, id;
    vector<int> books;
}a[MAXN];

int dp[703][1<<17];
int cost_func[703][20];

void REORDER(vector<int> idx){
	for(int i=0; i<D; i++){
		for(int j=0; j<sz(idx); j++){
			sort(all(a[idx[j]].books), [&](const int &a, const int &b){
				return score[a] > score[b];
			});
			int sum = (D - i) * a[idx[j]].speed;
			sum = min(sum, sz(a[idx[j]].books));
			for(int k=0; k<sum; k++){
				cost_func[i][j] += score[a[idx[j]].books[k]];
			}
		}
	}
	for(int i=0; i<703; i++){
		for(int j=0; j<(1<<17); j++) dp[i][j] = -1e9;
	}
	dp[0][0] = 0;
	for(int i=0; i<D; i++){
		for(int j=0; j<(1<<sz(idx)); j++){
			if(dp[i][j] < 0) continue;
			for(int k=0; k<sz(idx); k++){
				if((j >> k) & 1) continue;
				int T = a[idx[k]].signup;
				if(i + T > D) continue;
				dp[i + T][j | (1<<k)] = max(
				dp[i + T][j | (1<<k)], dp[i][j] + cost_func[i + T][k]);
			}
		}
	}
	pi pos(0, 0);
	bool upd = 1;
	vector<int> ord;
	while(upd){
		upd = 0;
		for(int j=0; j<sz(idx); j++){
			if((pos.second >> j) & 1) continue;
			int T = a[idx[j]].signup;
			if(pos.first + T > D) continue;
			if(dp[pos.first + T][pos.second | (1<<j)] == dp[pos.first][pos.second] + cost_func[pos.first + T][j]){
				ord.push_back(idx[j]);
				pos.first += T;
				pos.second |= (1<<j);
				upd = 1;
				break;
			}
		}
	}
	for(auto &i : ord){
		buf.print({a[i].id, sz(a[i].books)});
		buf.print(a[i].books);
	}
	buf.flush();
}

bool vis[MAXN];
bool procing[MAXN];

int extract_idx(int dates) {
    pair<double, int> ret(-1, -1);
    for (int i = 0; i<L; i++) {
        if (vis[i] || dates <= a[i].signup) continue;
        sort(all(a[i].books), [&](const int &a, const int &b) {
            return score[a] > score[b];
        });
        int siz = (int)min(1ll * (dates - a[i].signup) * a[i].speed, 1ll * sz(a[i].books));
        lint accm = 0;
        for (int j = 0; j < siz; j++)
            accm += score[a[i].books[j]];
        ret = max(ret, make_pair(1.0 * accm / pow(a[i].signup, 0.85), i));
    }
    return ret.second;
}
int main() {
	int orig_score[MAXN] = {};
    cin >> B >> L >> D;
    for (int i = 0; i<B; i++) cin >> score[i];
    memcpy(orig_score, score, sizeof(score));
    for (int i = 0; i<L; i++) {
        int siz;
        cin >> siz >> a[i].signup >> a[i].speed;
        a[i].id = i;
        a[i].books.resize(siz);
        for (auto &j : a[i].books) {
            scanf("%d", &j);
        }
    }
    vector<int> ord;
    int tick = 0;
    while (tick < D) {
        int i = extract_idx(D - tick);
        if (i == -1) break;
        vis[i] = 1;
        tick += a[i].signup;
        int siz = (int)min(1ll * (D - tick) * a[i].speed, 1ll * sz(a[i].books));
        assert(siz > 0);
        ord.push_back(i);
        a[i].books.resize(siz);
        for(int j=0; j<siz; j++){
        	score[a[i].books[j]] = 0;
		}
	}
	memcpy(score, orig_score, sizeof(score));
	REORDER(ord);
}
