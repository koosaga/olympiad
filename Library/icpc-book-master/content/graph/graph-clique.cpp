/**
 * Author: WishingBone's ACM/ICPC Routine Library
 * Description: Max clique N<64. Bit trick for speed.
 * clique solver calculates both size and consitution of maximum clique
 * uses bit operation to accelerate searching
 * graph size limit is 63, the graph should be undirected
 * can optimize to calculate on each component, and sort on vertex degrees
 *can be used to solve maximum independent set
 *
 */

class clique {
  public:
  static const long long ONE = 1;
  static const long long MASK = (1 << 21) - 1;
  char* bits;
  int n, size, cmax[63];
  long long mask[63], cons;
  // initiate lookup table
  clique() {
    bits = new char[1 << 21];
    bits[0] = 0;
    for (int i = 1; i < (1<<21); ++i) 
      bits[i] = bits[i >> 1] + (i & 1);
  }
  ~clique() {
    delete bits;
  }
  // search routine
  bool search(int step,int siz,LL mor,LL con);
  // solve maximum clique and return size
  int sizeClique(vector<vector<int> >& mat);
  // solve maximum clique and return set
  vector<int>getClq(vector<vector<int> >&mat);
};
// step is node id, size is current sol., more is available mask, cons is constitution mask
bool clique::search(int step, int size, 
                    LL more, LL cons) {
  if (step >= n) {
    if (size > this->size) {
      // a new solution reached
      this->size = size;
      this->cons = cons;
    }
    return true;
  }
  long long now = ONE << step;
  if ((now & more) > 0) {
    long long next = more & mask[step];
    if (size + bits[next & MASK] + 
        bits[(next >> 21) & MASK] + 
        bits[next >> 42] >= this->size 
     && size + cmax[step] > this->size) {
      // the current node is in the clique
      if (search(step+1,size+1,next,cons|now))      
        return true;
    }
  }
  long long next = more & ~now;
  if (size + bits[next & MASK] + 
      bits[(next >> 21) & MASK] + 
      bits[next >> 42] > this->size) {
    // the current node is not in the clique
    if (search(step + 1, size, next, cons))
      return true;
  }
  return false;
}
// solve maximum clique and return size
int clique::sizeClique(vector<vector<int> >& mat) {
  n = mat.size();
  // generate mask vectors
  for (int i = 0; i < n; ++i) {
    mask[i] = 0;
    for (int j = 0; j < n; ++j) 
      if (mat[i][j] > 0) mask[i] |= ONE << j;
  }
  size = 0;
  for (int i = n - 1; i >= 0; --i) {
    search(i + 1, 1, mask[i], ONE << i);
    cmax[i] = size;
  }
  return size;
}
// calls sizeClique and restore cons
vector<int> clique::getClq(
    vector<vector<int> >& mat) {
  sizeClique(mat);
  vector<int> ret;
  for (int i = 0; i < n; ++i) 
    if ((cons&(ONE<<i)) > 0) ret.push_back(i);
  return ret;
} 
