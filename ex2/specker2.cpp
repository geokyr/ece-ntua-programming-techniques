#include <iostream>
#include <string>
using namespace std;

class Player {
  public:
    Player(const string &n);
    virtual ~Player();

    virtual const string &getType() const = 0;
    virtual Move play(const State &s) = 0;

    friend ostream& operator<<(ostream &out, const Player &player);

  private:
    string *name;
};

Player::Player(const string &n) {
  name = new string;
  *name = n;
}

Player::~Player() {
  delete name;
}

ostream& operator<<(ostream &out, const Player &player) {
  out << player.getType() << " player " << *player.name;
  return out;
}

class GreedyPlayer : public Player {
  public:
    GreedyPlayer(const string &n) : Player(n) {
      type = new string;
      *type = "Greedy";
    }

    const string &getType() const {
      return *type;
    }

    Move play(const State &s) {
      int max, maxi;
      max = maxi = 0;
      for(int i=0; i<s.getHeaps(); i++) {
        if(s.getCoins(i) > max) {
          max = s.getCoins(i);
          maxi = i;
        }
      }
      return Move(maxi, max, 0, 0);
    }

  private:
    string *type;
};

class SpartanPlayer : public Player {
  public:
    SpartanPlayer(const string &n) : Player(n) {
      type = new string;
      *type = "Spartan";
    }

    const string &getType() const {
      return *type;
    }

    Move play(const State &s) {
      int max, maxi;
      max = maxi = 0;
      for(int i=0; i<s.getHeaps(); i++) {
        if(s.getCoins(i) > max) {
          max = s.getCoins(i);
          maxi = i;
        }
      }
      return Move(maxi, 1, 0, 0);
    }

  private:
    string *type;
};

class SneakyPlayer : public Player {
  public:
    SneakyPlayer(const string &n) : Player(n) {
      type = new string;
      *type = "Sneaky";
    }

    const string &getType() const {
      return *type;
    }

    Move play(const State &s) {
      int min, mini;
      min = 1000000000;
      mini = 0;
      for(int i=0; i<s.getHeaps(); i++) {
        if(s.getCoins(i) < min && s.getCoins(i) != 0) {
          min = s.getCoins(i);
          mini = i;
        }
      }
      return Move(mini, min, 0, 0);
    }

  private:
    string *type;
};

class RighteousPlayer : public Player {
  public:
    RighteousPlayer(const string &n) : Player(n) {
      type = new string;
      *type = "Righteous";
    }

    const string &getType() const {
      return *type;
    }

    Move play(const State &s) {
      int max, maxi, min, mini;
      max = maxi = mini = 0;
      min = 1000000000;
      for(int i=0; i<s.getHeaps(); i++) {
        if(s.getCoins(i) > max) {
          max = s.getCoins(i);
          maxi = i;
        }
        if(s.getCoins(i) < min) {
          min = s.getCoins(i);
          mini = i;
        }
      }
      return Move(maxi, (max+1)/2, mini, (max+1)/2-1);
    }

  private:
    string *type;
};