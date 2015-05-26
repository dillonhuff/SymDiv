int test_1(int argc) {
  return argc;
}

int test_2(int a, int b) {
  return a / b;
}

int test_3(int a, int b) {
  int c = a + b;
  return 1 / c;
}

int test_4(int a, int b, int c) {
  int x = a + b * c;
  return x;
}

int test_5(int a, int b, int c) {
  int x = a - b;
  int y = x*a*b;
  int l = c + a*y;
  return l / y;
}
