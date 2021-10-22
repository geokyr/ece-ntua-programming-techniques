#include <iostream>
#include <stdexcept>
using namespace std;

class Move {
  public:
    Move(int sh, int sc, int th, int tc);

    int getSource() const;
    int getSourceCoins() const;
    int getTarget() const;
    int getTargetCoins() const;

    friend ostream& operator<<(ostream &out, const Move &move);

  private:
    int ph;
    int pc;
    int dh;
    int dc;
};

Move::Move(int sh, int sc, int th, int tc) {
  ph = sh;
  pc = sc;
  dh = th;
  dc = tc;
}

int Move::getSource() const {
  return ph;
}

int Move::getSourceCoins() const {
  return pc;
}

int Move::getTarget() const {
  return dh;
}

int Move::getTargetCoins() const {
  return dc;
}

ostream& operator<<(ostream &out, const Move &move) {
  if(move.dc > 0) {
    out << "takes " << move.pc << " coins from heap " << move.ph << " and puts " << move.dc << " coins to heap " << move.dh;
  }
  else {
    out << "takes " << move.pc << " coins from heap " << move.ph << " and puts nothing";
  }
  return out;
}

class State {
  public:
    State(int h, const int c[]);
    ~State();

    void next(const Move &move) throw(logic_error);
    bool winning() const;

    int getHeaps() const;
    int getCoins(int h) const throw (logic_error);

    friend ostream& operator<<(ostream &out, const State &state);

  private:
    int nh;
    int *coins;
};

State::State(int h, const int c[]) {
  nh = h;
  coins = new int[h];
  for(int i=0; i<h; i++) {
    coins[i] = c[i];
  }
}

State::~State() {
  nh = 0;
  delete [] coins;
}

void State::next(const Move &move) throw(logic_error) {
  if(move.getSource() > nh - 1 || move.getTarget() > nh - 1) {
    throw logic_error("invalid heap");
  }
  else {
    if(coins[move.getSource()] < move.getSourceCoins()) {
      throw logic_error("not enough coins available");
    }
    else if(move.getSourceCoins()-1 < move.getTargetCoins()) {
      throw logic_error("not enough coins picked up");
    }
    else {
      coins[move.getSource()] -= move.getSourceCoins();
      coins[move.getTarget()] += move.getTargetCoins();
    }
  }
}

bool State::winning() const {
  for(int i=0; i<nh; i++) {
    if(coins[i] != 0) {
      return false;
    }
  }
  return true;
}

int State::getHeaps() const {
  return nh;
}

int State::getCoins(int h) const throw(logic_error) {
  if(h > nh - 1 || h < 0) {
    throw logic_error("invalid heap");
  }
  else {
    return coins[h];
  }
}

ostream& operator<<(ostream &out, const State &state) {
  for(int i=0; i<state.getHeaps()-1; i++) {
    out << state.getCoins(i) << ", ";
  }
  out << state.getCoins(state.getHeaps()-1);
  return out;
}