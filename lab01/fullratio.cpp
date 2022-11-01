#include <iostream>
#ifndef CONTEST
#include "fullratio.hpp"
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

rational operator + (const rational &x, const rational &y) {
  rational re(0, 1);
  re.nom = x.nom * y.den + x.den * y.nom;
  re.den = x.den * y.den;
  int a = rational::gcd(re.nom, re.den);
  re.nom /= a;
  re.den /= a;
  if(re.den < 0) {
    re.nom = -re.nom;
    re.den = -re.den;
  }
  return re;
}

rational operator - (const rational &x, const rational &y) {
  rational re(0, 1);
  re.nom = x.nom * y.den - x.den * y.nom;
  re.den = x.den * y.den;
  int s = rational::gcd(re.nom, re.den);
  re.nom /= s;
  re.den /= s;
  if(re.den < 0) {
    re.nom = -re.nom;
    re.den = -re.den;
  }
  return re;
}

rational operator * (const rational &x, const rational &y) {
  rational re(0, 1);
  re.nom = x.nom * y.nom;
  re.den = x.den * y.den;
  int m = rational::gcd(re.nom, re.den);
  re.nom /= m;
  re.den /= m;
  if(re.den < 0) {
    re.nom = -re.nom;
    re.den = -re.den;
  }
  return re;
}

rational operator / (const rational &x, const rational &y) {
  rational re(0, 1);
  re.nom = x.nom * y.den;
  re.den = x.den * y.nom;
  int d = rational::gcd(re.nom, re.den);
  re.nom /= d;
  re.den /= d;
  if(re.den < 0) {
    re.nom = -re.nom;
    re.den = -re.den;
  }
  return re;
}

std::ostream & operator << (std::ostream &out, const rational &x) {
  out << x.nom << "/" << x.den;
  return out;
}

int rational::gcd(int a, int b) {
  a = abs(a);
  b = abs(b);
  while(a > 0 && b > 0) {
    if(a > b) {
      a = a % b;
    }
    else {
      b = b % a;
    }
  }
  return (a + b);
}