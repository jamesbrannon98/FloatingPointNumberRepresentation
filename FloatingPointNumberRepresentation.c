#include "FloatingPointNumberRepresentation.h"
/* Computes the bit level representation of an integer */
float_bits float_i2f(int i) {
  int sign, exp, frac, round, rounded, factor, remainder;
  int min = 0x80000000;
  int bias = 0x7f;
  exp = 0;
  
  /* Base case of 0 */
  if (i == 0){
    sign = 0;
    exp = 0;
    frac = 0;
    return sign << 31 | exp << 23 | frac;
  }

  /*Base case of INT_MIN */
  if (i == min){
    sign = 1;
    exp = bias + 31;
    frac = 0;
    return sign << 31 | exp << 23 | frac;
  }
  /* Converts the sign of the integer */
  sign = 0;
  if (i < 0){
    sign = 1;
    i = -i;
  }
  frac = i;
  /*Computes the exponent of the integer */
  while (i >>= 1){
    exp++;
  }
  
  /* Rounds the integer if it contains greater than 23 significant figures */
  round = exp - 23;
  if (round > 0){
    rounded = frac & (~(min >> (31 - round)));
    factor = 1 << (round - 1);
    if ((rounded == factor) && (frac >> round & 1)){
      remainder = 1;
      }
    else {
      remainder = rounded > factor;
    }
    frac = frac >> round;
    frac += remainder;
  
    if (frac & 16777216){
      exp++;
    }
  }

  else {
    frac = frac << (-round);
  }

  /* Sets the sign and exponent parts of the frac to 0,
   * adds the bias to the exponent,
   * and returns the bit level representation of the integer */
  frac = frac & 0x7fffff;
  exp += bias;
  return sign << 31 | exp << 23 | frac;
}
