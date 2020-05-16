
int fibo(int a, int b) {
  if (a == 1) return 1;
  return fibo(b, a + b);
}

int main() {
  printf("%d%c", fibo(1, 1), 10);
  return 0;
}