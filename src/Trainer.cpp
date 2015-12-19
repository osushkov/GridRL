
#include "Trainer.hpp"
#include "common/Common.hpp"
#include "LearningAgent.hpp"
#include "util/Util.hpp"
#include "gridworld/GameState.hpp"
#include "gridworld/GameRules.hpp"
#include <cassert>
#include <cmath>


struct Trainer::TrainerImpl {

  const unsigned numRounds = 10000;

  const double startLearnRate = 0.1;
  const double endLearnRate = 0.0001;

  GameRules rules;

  TrainerImpl() : rules(100, -100, 0) {}

  unique_ptr<Agent> trainAgent(void) {
    auto trainedAgent = make_unique<LearningAgent>(0.9);

    for (unsigned round = 0; round < numRounds; round++) {
      double roundFrac = (double) round / (double) numRounds;
      double learnRate = startLearnRate + roundFrac * (endLearnRate - startLearnRate);

      trainedAgent->setLearnRate(learnRate);
      trainedAgent->setPRandom(0.2); // * (1.0 - roundFrac));

      trainingRound(trainedAgent.get());
    }

    return move(trainedAgent);
  }

private:

  void trainingRound(Agent* agent) {
    uptr<State> gameState(GameState::NewInitialGameState());

    // cout << endl;
    for (unsigned i = 0; i < 100; i++) {
      uptr<Action> action = agent->chooseAction(gameState.get());
      uptr<State> successor = gameState->successorState(*action);
      double reward = rules.getReward(*successor.get());

      agent->actionOutcome(make_pair(gameState.get(), action.get()), make_pair(successor.get(), reward));

      if (rules.isTerminalState(*successor.get())) {
        break;
      }

      gameState = move(successor);
    }
  }
};


Trainer::Trainer() : impl(new TrainerImpl()) {}

Trainer::~Trainer() = default;

unique_ptr<Agent> Trainer::trainAgent(void) {
  return impl->trainAgent();
}
