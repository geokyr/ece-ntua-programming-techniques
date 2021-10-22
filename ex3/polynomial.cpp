#include <iostream>
#include <cmath>

using namespace std;

class Polynomial {
  public:
    class Term {
      public:
        int exponent;
        int coefficient;
        Term *next;

        Term(int exp, int coeff, Term *n) {
          exponent = exp;
          coefficient = coeff;
          next = n;
        }

        friend class Polynomial;
    };
    Term *head;

  public:
    Polynomial();
    Polynomial(const Polynomial &p);
    ~Polynomial();

    Polynomial& operator=(const Polynomial &p);

    void addTerm(int expon, int coeff);
    double evaluate(double x);

    friend Polynomial operator+(const Polynomial &p, const Polynomial &q);
    friend Polynomial operator*(const Polynomial &p, const Polynomial &q);
    friend ostream& operator<<(const Polynomial &p, const Polynomial &q);
};

Polynomial::Polynomial() {
  head = NULL;
}

Polynomial::Polynomial(const Polynomial &p) {
  head = NULL;
  Term *temp = p.head;
  while(temp != NULL) {
    addTerm(temp->exponent, temp->coefficient);
    temp = temp->next;
  }
}

Polynomial::~Polynomial() {
  Term *temp = head;
  Term *del;
  head = NULL;
  while(temp != NULL) {
    del = temp->next;
    delete temp;
    temp = del;
  }
}

Polynomial& Polynomial::operator=(const Polynomial &p) {
  Polynomial temp(p);
  swap(temp.head, head);
  return *this;
}

void Polynomial::addTerm(int expon, int coeff) {
  if(coeff == 0) {
    return;
  }

  if(head == NULL) {
    head = new Term(expon, coeff, NULL);
    return;
  }

  if(head->exponent < expon) {
    Term *temp = new Term(expon, coeff, head);
    head = temp;
    return;
  }

  if(head->exponent == expon) {
    head->coefficient += coeff;
    if(head->coefficient == 0) {
      Term *temp = head;
      head = head->next;
      delete temp;
    }
    return;
  }

  Term *temp = head;
  Term *prev = head;
  while((temp != NULL) && (temp->exponent > expon)) {
    prev = temp;
    temp = temp->next;
  }

  if(temp == NULL) {
    Term *temp2 = new Term(expon, coeff, NULL);
    prev->next = temp2;
    return;
  }

  if(temp->exponent == expon) {
    temp->coefficient += coeff;
    if(temp->coefficient == 0) {
      prev->next = temp->next;
      delete temp;
      temp = NULL;
    }
    return;
  }
  else {
    Term *temp3 = new Term(expon, coeff, temp);
    prev->next = temp3;
    return;
  }
}

double Polynomial::evaluate(double x) {
  double ans = 0.0;
  Term *temp = head;
  if(head == NULL) {
    return ans;
  }
  while(temp != NULL) {
    ans += (temp->coefficient * pow(x, temp->exponent));
    temp = temp->next;
  }
  return ans;
}

Polynomial operator+(const Polynomial &p, const Polynomial &q) {
  Polynomial ans;
  Polynomial::Term *temp;
  temp = p.head;
  while(temp != NULL) {
    ans.addTerm(temp->exponent, temp->coefficient);
    temp = temp->next;
  }
  temp = q.head;
  while(temp != NULL) {
    ans.addTerm(temp->exponent, temp->coefficient);
    temp = temp->next;
  }
  return ans;
}

Polynomial operator*(const Polynomial &p, const Polynomial &q) {
  Polynomial ans;
  Polynomial::Term *temp;
  Polynomial::Term *temp2;
  temp = p.head;
  temp2 = q.head;
  while(temp != NULL) {
    while(temp2 != NULL) {
      ans.addTerm(temp->exponent+temp2->exponent, temp->coefficient*temp2->coefficient);
      temp2 = temp2->next;
    }
    temp2 = q.head;
    temp = temp->next;
  }
  return ans;
}

ostream& operator<<(ostream &out, const Polynomial &p) {
  Polynomial::Term *print = p.head;
  if(print == NULL) {
    out << "0";
    return out;
  }
  if(print->exponent > 1 || print->exponent < 0) {
    if(print->coefficient > 1) {
      out << print->coefficient << "x^" << print->exponent;
    }
    else if(print->coefficient == 1) {
      out << "x^" << print->exponent;
    }
    else if(print->coefficient == -1) {
      out << "- x^" << print->exponent;
    }
    else if(print->coefficient < -1) {
      out << "- " << abs(print->coefficient) << "x^" << print->exponent;
    }
  }
  else if(print->exponent == 1) {
    if(print->coefficient > 1) {
      out << print->coefficient << "x";
    }
    else if(print->coefficient == 1) {
      out << "x";
    }
    else if(print->coefficient == -1) {
      out << "- x";
    }
    else if(print->coefficient < -1) {
      out << "- " << abs(print->coefficient) << "x";
    }
  }
  else if(print->exponent == 0) {
    if(print->coefficient >= 0) {
      out << print->coefficient;
    }
    else if(print->coefficient < 0) {
      out << "- " << abs(print->coefficient);
    }
  }
  print = print->next;
  while(print != NULL) {
    if(print->exponent > 1 || print->exponent < 0) {
      if(print->coefficient > 1) {
        out << " + " << print->coefficient << "x^" << print->exponent;
      }
      else if(print->coefficient == 1) {
        out << " + x^" << print->exponent;
      }
      else if(print->coefficient == -1) {
        out << " - x^" << print->exponent;
      }
      else if(print->coefficient < -1) {
        out << " - " << abs(print->coefficient) << "x^" << print->exponent;
      }
    }
    else if(print->exponent == 1) {
      if(print->coefficient > 1) {
        out << " + " << print->coefficient << "x";
      }
      else if(print->coefficient == 1) {
        out << " + x";
      }
      else if(print->coefficient == -1) {
        out << " - x";
      }
      else if(print->coefficient < -1) {
        out << " - " << abs(print->coefficient) << "x";
      }
    }
    else if(print->exponent == 0) {
      if(print->coefficient >= 0) {
        out << " + " << print->coefficient;
      }
      else if(print->coefficient < 0) {
        out << " - " << abs(print->coefficient);
      }
    }
    print = print->next;
  }
  return out;
}

#ifndef CONTEST
int main() {}
#endif