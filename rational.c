typedef struct {
  int enu;
  int den;
} rational;

void mult(rational* left, rational* right) {
  left->enu = left->enu * right->enu;
  left->den = left->den * right->den;
  if (left->den < 0) {
    left->den*=-1;
    left->enu*=-1;
  }
};

void inverse(rational* value) {
  int k = value->enu;
  value->enu = value->den;
  value->den = k;
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

void divide(rational* left, rational* right) {
  inverse(right);
  mult(left, right);
  inverse(right);
};

bool compare(rational* left, rational* right) {
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
