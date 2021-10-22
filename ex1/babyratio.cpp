#include <iostream>
#ifndef CONTEST
#include "babyratio.hpp"
#endif

using namespace std;

rational::rational(int n, int d) {
  nom = n;
  den = d;
  int r = gcd(nom, den);
  nom /= r;
  den /= r;
  if(nom == 0) {
    den = 1;
  }
  if(den < 0) {
   nom = -nom;
   den = -den;
  }
}

rational rational::add(rational r) {
  rational re(0, 1);
  re.nom = nom * r.den + den * r.nom;
  re.den = r.den * den;
  int a = gcd(re.nom, re.den);
  re.nom /= a;
  re.den /= a;
  if(re.den < 0) {
    re.nom = -re.nom;
    re.den = -re.den;
  }
  return re;
}

rational rational::sub(rational r) {
  rational re(0, 1);
  re.nom = nom * r.den - den * r.nom;
  re.den = r.den * den;
  int s = gcd(re.nom, re.den);
  re.nom /= s;
  re.den /= s;
  if(re.den < 0) {
    re.nom = -re.nom;
    re.den = -re.den;
  }
  return re;
}

rational rational::mul(rational r) {
  rational re(0, 1);
  re.nom = r.nom * nom;
  re.den = r.den * den;
  int m = gcd(re.nom, re.den);
  re.nom /= m;
  re.den /= m;
  if(re.den < 0) {
    re.nom = -re.nom;
    re.den = -re.den;
  }
  return re;
}

rational rational::div(rational r) {
  rational re(0, 1);
  re.nom = r.den * nom;
  re.den = r.nom * den;
  int d = gcd(re.nom, re.den);
  re.nom /= d;
  re.den /= d;
  if(re.den < 0) {
    re.nom = -re.nom;
    re.den = -re.den;
  }
  return re;
}

void rational::print() {
  cout << nom << "/" << den;
}

int rational::gcd(int a, int b) {
  a = abs(a);
  b = abs(b);
  while (a > 0 && b > 0) {
    if (a > b) {
      a = a % b;
    }
    else {
      b = b % a;
    }
  }
  return (a + b);
}