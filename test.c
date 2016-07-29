#include <stdio.h>

#include "rational.c"

int main() {
  rational x, y, z;
  x.enu = 10;
  x.den = 1;

  y.enu = 5;
  y.den = 1;

  printf("x = %d / %d \ny = %d / %d \n", x.enu, x.den, y.enu, y.den);

  z = mult(&x, &y);
  printf("After multiplication x*y:\n");
  printf("x = %d / %d\n", x.enu, x.den);
  printf("y = %d / %d\n", y.enu, y.den);
  printf("z = %d / %d\n", z.enu, z.den);

  z = divide(&x, &y);
  printf("After division x/y:\n x = %d / %d \n y = %d / %d \n, z = %d / %d \n", x.enu, x.den, y.enu, y.den, z.enu, z.den);
  printf("Dividing again:\n");
  z = divide(&x, &y);
  printf("x = %d / %d \ny = %d / %d \nz = %d / %d\n", x.enu, x.den, y.enu, y.den, z.enu, z.den);

  if (compare(&x, &y)) {
    printf("x < y\n");
  } else {
    printf("x > y\n");
  }

  z = sub(&x, &y);
  printf("After subtraction x-y: \n x = %d / %d \n y = %d / %d \n res = %d / %d \n", x.enu, x.den, y.enu, y.den, z.enu, z.den);
}
