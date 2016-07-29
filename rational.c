typedef struct {
  int enu;
  int den;
} rational;

rational mult(rational* left, rational* right) {
  rational ret;
  ret.enu = left->enu * right->enu;
  ret.den = left->den * right->den;
  if (ret.den < 0) {
    ret.den*=-1;
    ret.enu*=-1;
  }
  return ret;
};

rational inverse(rational* value) {
  rational ret;
  ret.enu = value->den;
  ret.den = value->enu;
  return ret;
};

rational sub(rational* left, rational*right) {
  rational ret;
  ret.den = left->den * right->den;
  ret.enu = left->enu * right->den - right->enu*left->den;
  if (ret.den < 0) {
    ret.den*=-1;
    ret.enu*=-1;
  }
  return ret;
};

rational divide(rational* left, rational* right) {
  rational ret = inverse(right);
  return mult(left, &ret);
};

int compare(rational* left, rational* right) {
  int lh, rh;
  lh = left->enu * right->den;
  rh = right->enu * left->den;
  return lh<rh;
};

int compare_int(rational* left, int right) {
  return left->enu < right*left->den;
};

int equal_int(rational* left, int right) {
  return (!compare_int(left, right) && !(left->enu > right*left->den));
};
