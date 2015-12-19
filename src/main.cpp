
#include <iostream>
#include <vector>
#include <unordered_map>
#include <random>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "common/Common.hpp"
#include "gridworld/GameState.hpp"
#include "gridworld/GameAction.hpp"
#include "gridworld/GameRules.hpp"
#include "LearningAgent.hpp"
#include "Agent.hpp"
#include "Trainer.hpp"

using namespace std;

void playGame(Agent *agent) {
  GameRules rules;

  uptr<State> gameState(move(GameState::NewInitialGameState()));

  for (int i = 0; i < 10; i++) {
    gameState->output(cout);
    // static_cast<LearningAgent*>(agent)->outputMaxQ(gameState.get());
    // static_cast<LearningAgent*>(agent)->outputQValues(gameState.get());
    cout << endl;

    uptr<Action> action = agent->chooseAction(gameState.get());
    gameState = move(gameState->successorState(*action));

    action->output(cout);
    if (rules.isTerminalState(*gameState.get())) {
      break;
    }
  }
}

int main() {
  // srand(time(NULL));

  cout << "starting" << endl;

  Trainer trainer;
  unique_ptr<Agent> trainedAgent(trainer.trainAgent());

  trainedAgent->setPRandom(0.0);
  playGame(trainedAgent.get());

  cout << "finished" << endl;

  return 0;
}
