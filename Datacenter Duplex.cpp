/**
 *    author:  tourist
 *    created: 08.06.2019 17:16:06       
**/
#include <bits/stdc++.h>

using namespace std;

class dsu {
 public:
  vector<int> p;
  int n;

  dsu(int _n) : n(_n) {
    p.resize(n);
    iota(p.begin(), p.end(), 0);
  }

  inline int get(int x) {
    return (x == p[x] ? x : (p[x] = get(p[x])));
  }

  inline bool unite(int x, int y) {
    x = get(x);
    y = get(y);
    if (x != y) {
      p[x] = y;
      return true;
    }
    return false;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int tt;
  cin >> tt;
  for (int qq = 1; qq <= tt; qq++) {
    cout << "Case #" << qq << ": ";
    int h, w;
    cin >> h >> w;
    vector<string> s(h);
    for (int i = 0; i < h; i++) {
      cin >> s[i];
    }
    vector<string> ans(h - 1, string(w - 1, '.'));
    dsu d(h * w);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w - 1; j++) {
        if (s[i][j] == s[i][j + 1]) {
          d.unite(i * w + j, i * w + (j + 1));
        }
      }
    }
    for (int i = 0; i < h - 1; i++) {
      for (int j = 0; j < w; j++) {
        if (s[i][j] == s[i + 1][j]) {
          d.unite(i * w + j, (i + 1) * w + j);
        }
      }
    }
    vector<vector<int>> comp(2);
    vector<int> cid(h * w, -1);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (d.get(i * w + j) == i * w + j) {
          comp[(int) (s[i][j] - 'A')].push_back(i * w + j);
          cid[i * w + j] = (int) comp[(int) (s[i][j] - 'A')].size() - 1;
        }
      }
    }
    dsu d0(comp[0].size());
    dsu d1(comp[1].size());
    for (int i = 0; i < h - 1; i++) {
      for (int j = 0; j < w - 1; j++) {
        if (s[i][j] == s[i + 1][j + 1] && s[i + 1][j] == s[i][j + 1] && s[i][j] != s[i][j + 1]) {
          int x0 = cid[d.get(i * w + j)];
          int y0 = cid[d.get((i + 1) * w + (j + 1))];
          int x1 = cid[d.get(i * w + (j + 1))];
          int y1 = cid[d.get((i + 1) * w + j)];
          if (s[i][j] == 'A') {
            if (d0.unite(x0, y0)) {
              ans[i][j] = '\\';
            } else {
              ans[i][j] = '/';
              d1.unite(x1, y1);
            }
          } else {
            if (d0.unite(x1, y1)) {
              ans[i][j] = '/';
            } else {
              ans[i][j] = '\\';
              d1.unite(x0, y0);
            }
          }
        }
      }
    }
    int ok = 1;
    for (int i = 0; i < (int) comp[0].size(); i++) {
      if (d0.get(i) != d0.get(0)) {
        ok = 0;
        break;
      }
    }
    for (int i = 0; i < (int) comp[1].size(); i++) {
      if (d1.get(i) != d1.get(0)) {
        ok = 0;
        break;
      }
    }
    if (!ok) {
      cout << "IMPOSSIBLE" << '\n';
    } else {
      cout << "POSSIBLE" << '\n';
      for (int i = 0; i < h - 1; i++) {
        cout << ans[i] << '\n';
      }
    }
  }
  return 0;
}
