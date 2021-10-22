#include <iostream>
using namespace std;

template <typename T>
class stack {
  public:
    stack(int size) {
      cap = 0;
      top = -1;
      ssize = size;
      a = new T[size];
    }

    stack(const stack &s) {
      cap = s.cap;
      top = s.top;
      ssize = s.ssize;
      a = new T[ssize];
      for(int i=0; i<cap; i++) {
        a[i] = s.a[i];
      }
    }

    ~stack() {
      delete [] a;
    }

    const stack& operator=(const stack &s) {
      delete [] a;
      cap = s.cap;
      top = s.top;
      ssize = s.ssize;
      a = new T[ssize];
      for(int i=0; i<cap; i++) {
        a[i] = s.a[i];
      }
      return *this;
    }

    bool empty() {
      return (cap == 0);
    }

    void push(const T &x) {
      a[++top] = x;
      cap++;
    }

    T pop() {
      cap--;
      return a[top--];
    }

    int size() {
      return cap;
    }

    friend ostream& operator<<(ostream &out, const stack &s) {
      out << "[";
      for(int i=0; i<=s.top; i++) {
        out << s.a[i];
        if (i != s.top) {
          out << ", ";
        }
      }
      out << "]";
      return out;
    }

  private:
    T *a;
    int top;
    int cap;
    int ssize;
};

#ifndef CONTEST
int main () {
  stack<int> s(10);
  cout << "s is empty: " << s << endl;
  s.push(42);
  cout << "s has one element: " << s << endl;
  s.push(17);
  s.push(34);
  cout << "s has more elements: " << s << endl;
  cout << "How many?  " << s.size() << endl;
  stack<int> t(5);
  t.push(7);
  cout << "t: " << t << endl;
  t = s;
  cout << "popping from s: " << s.pop() << endl;
  s.push(8);
  stack<int> a(s);
  t.push(99);
  a.push(77);
  cout << "s: " << s << endl;
  cout << "t: " << t << endl;
  cout << "a: " << a << endl;
  stack<double> c(4);
  c.push(3.14);
  c.push(1.414);
  cout << "c contains doubles " << c << endl;
  stack<char> k(4);
  k.push('$');
  cout << "k contains a character " << k << endl;
}
#endif