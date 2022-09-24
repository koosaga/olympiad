#include <bits/stdc++.h>
using namespace std;
#define va first
#define vb second
typedef pair<int, int> pii;

int board[9], tri[10];
pii dp[20000];
bool reachable[20000];

pair<int, int> operator+(pair<int, int> a, pair<int, int> b)
{
    return pii(a.va + b.va, a.vb + b.vb);
};

bool subcheck(int i, int j, int k)
{
    return board[i] && board[i] == board[j] && board[i] == board[k];
}

bool isEnd()
{
    return subcheck(0, 1, 2) | subcheck(3, 4, 5) | subcheck(6, 7, 8) | subcheck(0, 3, 6) | subcheck(1, 4, 7) | subcheck(2, 5, 8) | subcheck(0, 4, 8) | subcheck(2, 4, 6);
}

int main()
{
    ios::sync_with_stdio(0), cin.tie(0);
    tri[0] = 1;
    for (int i = 1; i <= 9; i++)
    {
        tri[i] = tri[i - 1] * 3;
    }
    reachable[0] = true;
    for (int i = 0; i < tri[9]; i++)
    {
        if (!reachable[i])
            continue;
        int cnt = i;
        bool isFirst = true;
        for (int j = 0; j < 9; j++)
        {
            board[j] = cnt % 3;
            if (board[j])
                isFirst ^= 1;
            cnt /= 3;
        }
        if (isEnd())
            continue;
        for (int j = 0; j < 9; j++)
        {
            if (board[j])
                continue;
            if (isFirst)
                reachable[i + tri[j]] = true;
            else
                reachable[i + tri[j] * 2] = true;
        }
    }
    for (int i = tri[9] - 1; i >= 0; i--)
    {
        if (!reachable[i])
            continue;
        int cnt = i;
        bool isFirst = true;
        for (int j = 0; j < 9; j++)
        {
            board[j] = cnt % 3;
            if (board[j])
                isFirst ^= 1;
            cnt /= 3;
        }
        if (isEnd())
        {
            dp[i] = pii(!isFirst, isFirst);
            continue;
        }
        for (int j = 0; j < 9; j++)
        {
            if (board[j])
                continue;
            if (isFirst)
                dp[i] = dp[i] + dp[i + tri[j]];
            else
                dp[i] = dp[i] + dp[i + tri[j] * 2];
        }
    }

    int T;
    cin >> T;
    while (T--)
    {
        int sum = 0;
        for (int i = 0; i < 9; i++)
        {
            char c;
            cin >> c;
            if (c == 'X')
                sum += tri[i];
            if (c == 'O')
                sum += tri[i] * 2;
        }
        if (!reachable[sum])
        {
            cout << "-1 -1\n";
        }
        else
        {
            cout << dp[sum].va << ' ' << dp[sum].vb << '\n';
        }
    }
}