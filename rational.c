typedef struct {
  int enu;
  int den;
} rational;

void mult(rational* left, rational* right) {
  left->enu = left->enu * right->enu;
  left->den = left->den * right->den;
};

void inverse(rational* value) {
  int k = value->enu;
  value->enu = value->den;
  value->den = k;
}

void div(rational* left, rational* right) {
  inverse(right);
  mult(left, right);
  inverse(right);
};
