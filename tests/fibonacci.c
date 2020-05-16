
int fibo(int n) {
  if (n == 1 || n == 2) return 1;
  return fibo(n - 1) + fibo(n - 2);
}

int main() {
  printf("%d%c", fibo(6), 10);
  return 0;
}