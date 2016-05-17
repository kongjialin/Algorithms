// greatest common divisor
// recursion
int GCD1(int a, int b) {
  if (b == 0) return a;
  return GCD1(b, a % b);
}

// iteration
int GCD2(int a, int b) {
  while (b != 0) {
    int t = b;
    b = a % b;
    a = t;
  }
  return a;
}
