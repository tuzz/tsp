#ifndef _SOLVER
#define _SOLVER

#include "MaxSat.h"
#include "Alg_WBO.h"

using namespace NSPACE;

extern int maxDay;
static int bestWeight = MAX_WEIGHT;
static char c1, c2, c3;
static int lastCity;
static int curPrice;
static int totalPrice;
static bool firstCallback = true;

class SATSolver : public WBO {
  public:
    SATSolver(int verb, int weight, bool symm) : WBO(verb, weight, symm) {}

    void callback() {
      if (firstCallback) {
        stdout = fopen("/dev/tty","w");
        firstCallback = false;
      }

      if (currentWeight >= bestWeight) {
        return;
      }
      bestWeight = currentWeight;

      c1 = cityCodes[1][0];
      c2 = cityCodes[1][1];
      c3 = cityCodes[1][2];

      lastCity = 1;
      totalPrice = 0;

      for (int day = 1; day <= maxDay; day++) {
        for (int city = 1; city <= maxDay; city++) {
          if (model[cityDay(city, day) - 1] == l_False) {
            //printf("%c%c%c ", c1, c2, c3);

            c1 = cityCodes[city][0];
            c2 = cityCodes[city][1];
            c3 = cityCodes[city][2];

            curPrice = getPrice(lastCity, city, day - 1);
            //printf("%c%c%c %d %d\n", c1, c2, c3, day - 1, curPrice);

            lastCity = city;
            totalPrice += curPrice;

            break;
          }
        }
      }

      //printf("Total: %d\n\n\n", totalPrice);
    }
};

static SATSolver *solver;
static vec<Lit> lits;
static int literals = 0;

void initializeSolver() {
  solver = new SATSolver(_VERBOSITY_MINIMAL_, _WEIGHT_DIVERSIFY_, false);
  solver->setProblemType(_WEIGHTED_);
  solver->setHardWeight(MAX_WEIGHT);

  // Disable stdout until the first solve.
//  fclose(stdout);
};

int nextLiteral() {
  literals++;
  solver->newVar();
  return literals;
};

void literal(int n, bool b) {
  lits.push(mkLit(n - 1, b));
}

void hardClause() {
  solver->addHardClause(lits);
  lits.clear();
}

void softClause(int weight) {
	solver->setCurrentWeight(weight);
	solver->updateSumWeights(weight);
	solver->addSoftClause(weight, lits);
  lits.clear();
}

#endif
