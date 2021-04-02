#include <bits/stdc++.h>

std::vector<int> digit (int n) {
  std::vector<int> res(1, 0);
  for (; n; n /= 10) res.push_back(n % 10);
  return res;
}

int get (int n) {
  std::vector<int> a = digit(n);
  int m = a.size();
  int f[m][91][2];
  memset(f, -1, sizeof(f));

  f[m - 1][0][1] = 1;
  for (int pos = m - 1; pos > 0; pos--) {
    for (int sum = 0; sum <= 81; sum++) {
      for (int flag = 0; flag <= 1; flag++) {
        if (f[pos][sum][flag] == -1) continue;

        int bound = flag ? a[pos] : 9;
        for (int k = 0; k <= bound; k++) {
          int newFlag = flag & (k == a[pos]);
          if (f[pos - 1][sum + k][newFlag] == -1)
            f[pos - 1][sum + k][newFlag] = f[pos][sum][flag];
          else f[pos - 1][sum + k][newFlag] += f[pos][sum][flag];
        }
      }
    }
  }

  long long res = 0;
  for (int sum = 0; sum <= 81; sum++)
  for (int flag = 0; flag <= 1; flag++) {
    //std::cerr << sum << ' ' << flag << ' ' << f[0][sum][flag] << '\n';
    if (f[0][sum][flag] != -1) res += (f[0][sum][flag] * (long long)sum);
  }
  return res;
}

int main () {
  std::ios_base::sync_with_stdio(0);
  std::cin.tie(nullptr);
  freopen("A.inp", "r", stdin);
  freopen("A.out", "w", stdout);

  int a, b;
  while (std::cin >> a >> b) {
    if (a == -1 && b == -1) break;

    std::cerr << get(b) - get(a - 1) << '\n';
  }
}
