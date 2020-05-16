
struct foo {
  int a, b, c;
  float d;
  struct {
    char t;
  } s;
};

int geta(struct foo f) {
  f.a += 3;
  f.s.t = 'c'; 
  return f.a;
}

int main() {
  return 0;
}