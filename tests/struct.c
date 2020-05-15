
struct foo {
  int a, b, c;
  float d;
  struct {
    char t;
  } s;
} f;

int geta() {
  f.a += 3;
  f.s.t = 'c'; 
  return f.a;
}