const int mxn = 1000;
int grid[mxn + 1][mxn + 1];
int bit[mxn + 1][mxn + 1];
void update(int row, int col, int d) {
  grid[row][col] += d;
  for (int i = row; i <= mxn; i += (i & -i))
    for (int j = col; j <= mxn; j += (j & -j))
      bit[i][j] += d;
}
int sum(int row, int col) {
  // calculates sum from [1,1] till [row,col]
  int res = 0;
  for (int i = row; i > 0; i -= (i & -i))
    for (int j = col; j > 0; j -= (j & -j))
      res += bit[i][j];
  return res;
}