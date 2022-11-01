#include <iostream>
#include <string>

using namespace std;

class lexicon {
  public:
    lexicon() {
      root = nullptr;
    }
    ~lexicon() {
      empty(root);
    }

    void insert(const string &s) {
      root = insert(s, root);
    }
    int lookup(const string &s) const {
      return lookup(s, root);
    }
    int depth(const string &s) const;
    void replace(const string &s1, const string &s2) {
      if(!root) {
        return;
      }
      node *p = find(s1, root);
      if(!p) {
        return;
      }
      else {
        int k = p->fr;
        root = deletenode(s1, root);
        p = find(s2, root);
        if(!p) {
          root = insert(s2, root);
          find(s2, root)->fr += (k-1);
        }
        else {
          p->fr += k;
        }
    }
    }

    friend ostream& operator<<(ostream &out, const lexicon &l) {
      if(l.root) {
        return l.inorder(out, l.root);
      }
      return out;
    }

  private:
    struct node {
      string data;
      int fr;
      node* left;
      node* right;
    };

    node* root;

    node* insert(const string &s, node* t);
    int lookup(const string &s, node* t) const;
    int depth(const string &s, node* t) const;
    void replace(const string &s1, const string &s2, node* t);

    node* deletenode(const string &s, node* t);
    node* findmax(node* t);
    void empty(node* t);
    node* find(const string &s, node* t) const;
    ostream& inorder(ostream &out, node* t) const;
};

lexicon::node* lexicon::insert(const string &s, node* t) {
  if(!t) {
    node* temp = new node;
    temp->data = s;
    temp->left = temp->right = nullptr;
    temp->fr = 1;
    return temp;
  }
  if(s < t->data) {
    t->left = insert(s, t->left);
  }
  else if(s > t->data) {
    t->right = insert(s, t->right);
  }
  else if(s == t->data) {
    (t->fr)++;
  }
  return t;
}

int lexicon::lookup(const string &s, node* t) const {
  if(!find(s, t)) {
    return 0;
  }
  return (find(s,t)->fr);
}

int lexicon::depth(const string &s) const {
  if(!find(s, root)) {
    return 0;
  }
  int cnt = 1;
  node* p = root;
  while(p->data != s) {
    if(s < p->data) {
      cnt++;
      p = p->left;
    }
    else {
      cnt++;
      p = p->right;
    }
  }
    return cnt;
}


lexicon::node* lexicon::deletenode(const string &s, node* t) {
  if(!t) {
    return t;
  }
  else if(s < t->data) {
    t->left = deletenode(s, t->left);
  }
  else if(s > t->data) {
    t->right = deletenode(s, t->right);
  }
  else {
    if(!t->left && !t->right) {
      delete t;
      t = nullptr;
    }
    else if(!t->left) {
      node* temp = t;
      t = t->right;
      delete temp;
    }
    else if(!t->right) {
      node* temp = t;
      t = t->left;
      delete temp;
    }
    else {
      node* temp = findmax(t->left);
      t->data = temp->data;
      t->fr = temp->fr;
      t->left = deletenode(temp->data, t->left);
    }
  }
  return t;
}

lexicon::node* lexicon::findmax(node* t) {
  while(t->right) {
    t = t->right;
  }
  return t;
}

void lexicon::empty(node* t) {
  if(t) {
    empty(t->left);
    empty(t->right);
    delete t;
  }
}

lexicon::node* lexicon::find(const string &s, node* t) const {
  if(!t || t->data == s) {
    return t;
  }
  if(s < t->data) {
    return find(s, t->left);
  }
  return find(s, t->right);
}

ostream& lexicon::inorder(ostream &out, node* t) const {
  if(t) {
    inorder(out, t->left);
    out << t->data << " " << t->fr << endl;
    inorder(out, t->right);
  }
  return out;
}

#ifndef CONTEST
int main() {
  lexicon l;
  l.insert("the");
  l.insert("boy");
  l.insert("and");
  l.insert("the");
  l.insert("wolf");
  cout << l.lookup("the") << endl;
  cout << l.depth("and") << endl;
  cout << l;
  l.replace("boy", "wolf");
  cout << l;
  cout << l.depth("and") << endl;
}
#endif