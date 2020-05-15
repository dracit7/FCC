
int foo[3][4];

int test(int a, int b) {
  foo[a][b] = 1;
  return foo[a][b];
}