
#include "GameAction.hpp"
#include <cassert>
#include <iostream>

using namespace std;


struct GameAction::GameActionImpl {
  Direction dir;

  GameActionImpl(Direction dir) : dir(dir) {}

  void apply(GameState &state) const {
    state.movePlayer(dir);
  }

  bool operator== (const GameActionImpl& obj) const {
    return dir == obj.dir;
  }

  size_t hashCode(void) const {
    return static_cast<size_t>(dir);
  }

  void output(std::ostream &out) const {
    out << "ga( " << dir << " )" << endl;
  }
};


GameAction::GameAction(Direction dir) :
    impl(new GameActionImpl(dir)) {}

GameAction::~GameAction() = default;

void GameAction::apply(GameState &state) const {
  impl->apply(state);
}

uptr<Action> GameAction::clone(void) const {
  return make_unique<GameAction>(impl->dir);
}

bool GameAction::operator== (const Action& obj) const {
  const GameAction *ga = dynamic_cast<const GameAction*>(&obj);
  if (ga == nullptr) {
    return false;
  }

  return *impl == *ga->impl;
}

size_t GameAction::hashCode(void) const {
  return impl->hashCode();
}

void GameAction::output(std::ostream &out) const {
  impl->output(out);
}
