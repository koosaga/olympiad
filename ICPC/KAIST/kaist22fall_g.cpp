#include <bits/stdc++.h>
#define va first
#define vb second
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
using pii = pair<int, int>;
#define sz(a) ((int)(a).size())
#define all(a) (a).begin(), (a).end()
const int mod = 998244353;
const int MN = 2e5 + 5;
int A[MN], ans[MN], unk;
vector<int> vec, blank;
pii query[MN];
set<int> S;

bool calc0(int x)
{
    if (x == blank.size())
        return 1;
    int pos = blank[x];
    int prev = 0;
    while (1)
    {
        auto it = S.upper_bound(prev);
        if (it == S.end())
            break;
        int target = *it;
        prev = target;

        if (pos && abs(target - ans[pos - 1]) == 1 || abs(target - ans[pos + 1]) == 1)
        {
            continue;
        }
        ans[pos] = target;
        S.erase(target);

        if (calc0(x + 1))
        {
            return 1;
        }
        else
        {
            ans[pos] = -1;
            S.insert(target);
            continue;
        }
    }
    return 0;
}

int main()
{
    int N;
    cin >> N;
    int cnt = 0, Q = 0;
    for (int i = 0; i < MN; i++)
        ans[i] = -1;
    for (int i = 0; i < N; i++)
    {
        cin >> ans[i];
        if (ans[i] == -1)
        {
            cnt++;
            unk++;
        }
        else
        {
            A[ans[i]] = 1;
            if (cnt)
                query[Q++] = pii(cnt, i - cnt);
            cnt = 0;
        }
    }
    if (cnt)
    {
        query[Q++] = pii(cnt, N - cnt);
    }
    for (int i = 1; i <= N; i++)
    {
        if (A[i])
            continue;
        S.insert(i);
    }
    for (int i = 0; i < Q; i++)
    {
        if (unk - query[i].va <= 7)
        {
            blank.clear();
            for (int j = query[i].vb; j < N; j++)
            {
                if (ans[j] != -1)
                    continue;
                blank.push_back(j);
            }

            bool succ = calc0(0);
            if (!succ)
            {
                cout << -1 << '\n';
                return 0;
            }
            break;
        }
        else
        {
            blank.clear();
            for (int j = query[i].vb; j < query[i].vb + query[i].va; j++)
            {
                blank.push_back(j);
            }
            bool succ = calc0(0);
            if (!succ)
            {
                cout << -1 << '\n';
                return 0;
            }
            unk -= query[i].va;
        }
    }
    for (int i = 0; i < N; i++)
    {
        assert(ans[i] != -1);
    }
    for (int i = 0; i < N; i++)
    {
        cout << ans[i] << ' ';
    }
}