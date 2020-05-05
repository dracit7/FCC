
struct foo {
  int a;
  float b, c;
  struct {
    char t;
  } s;
};

int geta(struct foo f) {
  f.b += 3.14;
  f.s.t = 'c'; 
  return f.a;
}