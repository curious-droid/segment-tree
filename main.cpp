#include <iostream>

int N;

int sm[4000000000], si[4000000000], tg[4000000000], a[10000000000];
int size = 0;

void addTag(int v, int z) {
  sm[v] += si[v] * z;
  tg[v] += z;
}

void pushDown(int v) {
  if (tg[v]) {
    addTag(v << 1, tg[v]);
    addTag(v << 1 | 1, tg[v]);
    tg[v] = 0;
  }
}

void pushUp(int v) { sm[v] = sm[v << 1] + sm[v << 1 | 1]; }

void build(int v, int l, int r) {
  si[v] = r - l + 1;
  if (si[v] == 1) {
    sm[v] = a[++size];
    return;
  }
  int mid = (l + r) >> 1;
  build(v << 1, l, mid);
  build(v << 1 | 1, mid + 1, r);
  pushUp(v);
}

void modify(int x, int y, int z, int v = 1, int l = 1, int r = N) {
  if (x > r || y < l) {
    return;
  }
  if (x <= l && r <= y) {
    addTag(v, z);
    return;
  }
  pushDown(v);
  int mid = (l + r) >> 1;
  modify(x, y, z, v << 1, l, mid);
  modify(x, y, z, v << 1 | 1, mid + 1, r);
  pushUp(v);
}
int query(int x, int y, int v = 1, int l = 1, int r = N) {
  if (x > r || y < l) {
    return 0;
  }
  if (x <= l && r <= y) {
    return sm[v];
  }
  pushDown(v);
  int mid = (l + r) >> 1;
  return query(x, y, v << 1, l, mid) + query(x, y, v << 1 | 1, mid + 1, r);
}

int main() {
  std::cin >> N;
  for (int i = 0; i < N; i++) {
    std::cin >> a[i + 1];
  }
  build(1, 1, N);
}