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

namespace MaxSAT{
	vector<int> solve(int N, vector<vector<int>> system){
		vector<int> solution(N);
		for(int i=0; i<N; i++) solution[i] = (i % 2);
		return solution;
	}
}

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

vector<int> btol[MAXN];
int ass[MAXN], clz;

int main() {
    cin >> B >> L >> D;
    for (int i = 0; i<B; i++) cin >> score[i];
    for (int i = 0; i<L; i++) {
        int siz;
        cin >> siz >> a[i].signup >> a[i].speed;
        a[i].id = i;
        a[i].books.resize(siz);
        for (auto &j : a[i].books) {
            scanf("%d", &j);
            btol[j].push_back(i);
        }
    }
    vector<int> ord(B);
    iota(all(ord), 0);
    sort(all(ord), [&](const int &a, const int &b){
    	return sz(btol[a]) < sz(btol[b]);
	});
	vector<vector<int>> sys;
	vector<pi> doWhich;
	for(auto &i : ord){
		if(sz(btol[i]) == 2){
			clz++;
			ass[btol[i][0]] = clz;
			ass[btol[i][1]] = -clz;
			doWhich.emplace_back(btol[i][0], btol[i][1]);
		}
		if(sz(btol[i]) == 3){
			vector<int> v;
			for(auto &j : btol[i]){
				v.push_back(ass[j]);
			}
			sys.push_back(v);
		}
	}
	auto solution = MaxSAT::solve(clz, sys);
	vector<int> libSet;
	for(int i=0; i<clz; i++){
		if(solution[i] == 1) libSet.push_back(doWhich[i].first);
		else libSet.push_back(doWhich[i].second);
	}
	cout << sz(libSet) << endl;
	for(auto &i : libSet){
		cout << i << " " << sz(a[i].books) << endl;
		for(auto &j : a[i].books){
			cout << j << " ";
		}
		cout << endl;
	}
}
