#include <iostream>
#include <stdexcept>
using namespace std;

class Game {
  public:
    Game(int heaps, int players);
    ~Game();

    void addHeap(int coins) throw(logic_error);
    void addPlayer(Player *player) throw(logic_error);
    void play(ostream &out) throw(logic_error);

  private:
    int numh;
    int nump;
    int *h;
    Player **p;
    int hc;
    int pc;
};

Game::Game(int heaps, int players) {
  numh = heaps;
  nump = players;
  h = new int[numh];
  p = new Player*[nump];
  hc = pc = 0;
}

Game::~Game() {
  delete [] h;
  delete [] p;
}

void Game::addHeap(int coins) throw(logic_error) {
  if(hc > numh - 1) {
    throw logic_error("out of heap space");
  }
  else {
    h[hc++] = coins;
  }
}

void Game::addPlayer(Player *player) throw(logic_error) {
  if(pc > nump - 1) {
    throw logic_error("out of player space");
  }
  else {
    p[pc++] = player;
  }
}

void Game::play(ostream &out) throw(logic_error) {
  State state1(numh, h);
  hc = pc = 0;
  while(!state1.winning()) {
    out << "State: " << state1 << endl;
    out << *p[pc] << " " << p[pc]->play(state1) << endl;
    state1.next(p[pc]->play(state1));
    pc++;
    if(pc == nump) {
      pc = 0;
    }
  }
  out << "State: " << state1 << endl;
  if(pc == 0) {
    out << *p[nump-1] << " wins" << endl;
  }
  else {
    out << *p[pc-1] << " wins" << endl;
  }
}