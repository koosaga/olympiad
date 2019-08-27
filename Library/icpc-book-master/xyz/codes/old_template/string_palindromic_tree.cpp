///////////////////////////
//
// ext_kmp
//
///////////////////////////
#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int MAXN = 300005 ;  
const int N = 26 ;  
  
struct Palindromic_Tree {  
  int next[MAXN][N] ;//next指针，next指针和字典树类似，指向的串为当前串两端加上同一个字符构成  
  int fail[MAXN] ;//fail指针，失配后跳转到fail指针指向的节点  
  int cnt[MAXN] ;  // 节点i表示的本质不同的串的个数（建树时求出的不是完全的，最后count()函数跑一遍以后才是正确的）
  int num[MAXN] ;  // 节点i表示的最长回文串的最右端点为回文串结尾的回文串个数。
  int len[MAXN] ;//len[i]表示节点i表示的回文串的长度  
  int rep[MAXN] ; // 字符串中第i个字符对应的节点标号

  // For 100500
  int diff[MAXN];
  int fail_fast[MAXN];
  int dp[MAXN][2];

  int S[MAXN] ;//存放添加的字符  
  int last ;//指向上一个字符所在的节点，方便下一次add  
  int n ;//字符数组指针  
  int p ;//节点指针  
  
  int newnode ( int l ) {//新建节点  
    for ( int i = 0 ; i < N ; ++ i ) next[p][i] = 0 ;  
    cnt[p] = 0 ;  
    num[p] = 0 ;  
    len[p] = l ;  
    return p ++ ;  
  }  
  
  void init () {//初始化  
    p = 0 ;  
    newnode (  0 ) ;  
    newnode ( -1 ) ;  
    last = 0 ;  
    n = 0 ;  
    S[n] = -1 ;//开头放一个字符集中没有的字符，减少特判  
    fail[0] = 1 ;  
  }  
  
  int get_fail ( int x ) {//和KMP一样，失配后找一个尽量最长的  
    while ( S[n - len[x] - 1] != S[n] ) x = fail[x] ;  
    return x ;  
  }  
  
  void add ( int c ) {  
    c -= 'a' ;  
    S[++ n] = c ;  
    int cur = get_fail ( last ) ;//通过上一个回文串找这个回文串的匹配位置  
    if ( !next[cur][c] ) {//如果这个回文串没有出现过，说明出现了一个新的本质不同的回文串  
      int now = newnode ( len[cur] + 2 ) ;//新建节点  
      fail[now] = next[get_fail ( fail[cur] )][c] ;//和AC自动机一样建立fail指针，以便失配后跳转  
      next[cur][c] = now ;  
      num[now] = num[fail[now]] + 1 ;  
    }  
    rep[n] = last = next[cur][c] ;  
    cnt[last] ++ ;  
  }  
  
  void count () {  
    for ( int i = p - 1 ; i >= 0 ; -- i ) cnt[fail[i]] += cnt[i] ;  
    //父亲累加儿子的cnt，因为如果fail[v]=u，则u一定是v的子回文串！  
  }  
} T;  

char S[MAXN];
int ans[MAXN][2];

int getMin(int n, int k, int t) {
  // printf("?? %d %d\n", n, n - ((T.fail_fast[k] == 0 ? 0 : T.len[T.fail_fast[k]]) + T.diff[k]));
  // T.dp[k][1 - t] = MAXN + 1;
  // if (T.fail_fast[k] != 0)
  T.dp[k][1 - t] = ans[n - ((T.fail_fast[k] == 0 ? 0 : T.len[T.fail_fast[k]]) + T.diff[k])][1 - t];
  // printf("!! %d\n", T.dp[k][1 - t]);
  if (T.diff[k] == T.diff[T.fail[k]])
    T.dp[k][1 - t] = min(T.dp[k][1 - t], T.dp[T.fail[k]][1 - t]);
  return T.dp[k][1 - t] + 1;
}

int main() {
  scanf("%s", S + 1);
  int n = strlen(S + 1);
  T.init();
  for (int i = 1; i <= n; i++)
    T.add(S[i]);
  T.diff[0] = -1;
  for (int i = 1; i < T.p; i++) {
    if (T.fail[i] != 0) {
      T.diff[i] = T.len[i] - T.len[T.fail[i]];
      if (T.diff[i] == T.diff[T.fail[i]])
        T.fail_fast[i] = T.fail_fast[T.fail[i]];
      else
        T.fail_fast[i] = T.fail[i];
    }else {
      T.diff[i] = T.len[i];
      T.fail_fast[i] = 0;
    }
  }
  ans[0][0] = 0;
  ans[0][1] = n + 1;
  // for (int i = 1; i <= n; i++)
  //  dp[i][0] = dp[i][1] = n + 1;

  for (int i = 1; i <= n; i++) {
    int k = T.rep[i];
    ans[i][0] = ans[i][1] = n + 1;
    while (k) {
      ans[i][0] = min(ans[i][0], getMin(i, k, 0));
      ans[i][1] = min(ans[i][1], getMin(i, k, 1));
      k = T.fail_fast[k];
    }
    printf("%d %d\n", ans[i][1] > n ? -1 : ans[i][1], ans[i][0] > n ? -2 : ans[i][0]);
  }
}
