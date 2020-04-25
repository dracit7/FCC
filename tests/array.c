
int foo[3][4];
int foo_no_capacity[9][];

int test() {
  int a = 1, b = 2;
  return foo[a][b];
}