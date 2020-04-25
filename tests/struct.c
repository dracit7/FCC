
struct foo {
  int a;
  float b, c;
  struct {
    char t;
  } s;
};

int geta(struct foo f) {
  return f.a;
}