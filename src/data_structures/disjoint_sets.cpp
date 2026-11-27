// DS using union by size and path compression.
// alpha is the inverse Ackermann function.
struct DisjointSets {
  int elements_n;
  int components_n;
  vector<int> parent;  // Set representatives satisfy parent[u] == u.
  vector<int> size;  // Component size at representatives.

  // Creates n singleton sets.
  // Time complexity: O(n).
  DisjointSets(int n = -1) { if (n >= 0) Init(n); };
  void Init(int n) {
    parent.resize(n);
    iota(parent.begin(), parent.end(), 0);
    size.assign(n, 1);
    elements_n = n;
    components_n = n;
  }

  // Unites the dynamic sets that contain u and v.
  // Returns true if they were in differente sets.
  // Time complexity: O(alpha(n)) amortized.
  bool Union(int u, int v) {
    u = FindSet(u);
    v = FindSet(v);
    if (u == v) return false;
    if (size[u] > size[v]) swap(u, v);
    parent[u] = v;
    size[v] += size[u];
    components_n--;
    return true;
  }

  // Returns the representative of the set containing u.
  // Applies path compression.
  // Time complexity: O(alpha(n)) amortized.
  int FindSet(int u) {
    if (u != parent[u]) parent[u] = FindSet(parent[u]);
    return parent[u];
  }

  // Returns the number of elements in the set containing u.
  // Time complexity: O(alpha(n)) amortized.
  int SetSize(int u) {
    return size[FindSet(u)];
  }

  // Returns whether u and v belong to the same set.
  // Time complexity: O(alpha(n)) amortized.
  bool Connected(int u, int v) {
    return FindSet(u) == FindSet(v);
  }

  int ComponentsCount(void) const {
    return components_n;
  }
};