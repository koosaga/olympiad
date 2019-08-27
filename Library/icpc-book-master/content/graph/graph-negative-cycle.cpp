/**
 * Author: 
 * Description: negative cycle
 */
double b[N][N];

double dis[N];
int vis[N], pc[N];

bool dfs(int k) {
  vis[k] += 1; pc[k] = true;
  for (int i = 0; i < N; i++)
    if (dis[k] + b[k][i] < dis[i]) {
      dis[i] = dis[k] + b[k][i];
      if (!pc[i]) {
        if (dfs(i))
          return true;
      } else return true;
    }
  pc[k] = false;
  return false;
}

bool chk(double d) {
  for (int i = 0; i < N; i ++) 
    for (int j = 0; j < N; j ++) {
      b[i][j] = -a[i][j] + d;
    }
  for (int i = 0; i < N; i++)
    vis[i] = false, dis[i] = 0, pc[i] = false;
  for (int i = 0; i < N; i++)
    if (!vis[i] && dfs(i))
      return true;
  return false;
}
