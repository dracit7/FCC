
int main() {
  int foo = 0;

  if (2 > 1) {
    foo = 1;
  }

  if (2 > 1) {
    foo = 3*2-1;
  } else {
    foo = 1;
  }
  while (1) {
    foo -= 1;
    if (!foo) break;
    continue;
  }
  for (int i = 0; i < 10; i++) {
    foo += i;
  }
  return foo;
}