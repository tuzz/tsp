#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>

#include "constants.cc"
#include "memory.cc"
#include "parse.cc"
#include "commander.cc"
#include "solver.cc"

int maxDay = 0;

int main(int argc, char **argv) {
  initializeHeap();
  initializeSolver();

  // Remember the start city.
  char line[LINE_MAX];
  if(fgets(line, LINE_MAX, stdin)){}
  int startCity = city(line[0], line[1], line[2]);

  // For each flight:
  while (fgets(line, LINE_MAX, stdin) != NULL) {
    int day = extractNumber(line, 8);
    int fromIndex = city(line[0], line[1], line[2]);
    int toIndex = city(line[4], line[5], line[6]);
    int from = cityDay(fromIndex, day);
    int to = cityDay(toIndex, day + 1);
    int price = extractNumber(line, scanRight(line, 9));
    int flight = nextLiteral();

    rememberPrice(fromIndex, toIndex, day, price);

    // If took this flight, must have started at 'from'.
    literal(flight, F);
    literal(from, T);
    hardClause();

    // If took this flight, must have ended at 'to'.
    literal(flight, F);
    literal(to, T);
    hardClause();

    // If started at 'from' and ended at 'to', must have taken this flight.
    literal(from, F);
    literal(to, F);
    literal(flight, T);
    hardClause();

    // Add a soft clause that is true if this flight is taken. We want to
    // maximise the prices of flights we didn't take, meaning we took the
    // cheapest. This isn't very intuitive, but it's how Weighted Partial-MaxSat
    // solvers work.
    literal(flight, T);
    softClause(MAX_PRICE - price);

    // Remember the highest day seen.
    if (day > maxDay) {
      maxDay = day;
    }
  }

  // There's an extra day because it's a round trip.
  maxDay++;

  // Must be in exactly one city each day.
  for (int i = 0; i <= maxDay; i++) {
    for (int j = 0; j < cityIndex; j++) {
      variables[j] = cityDay(j + 1, i);
    }

    commanderVariable(variables, cityIndex);
  }

  // Must visit every city (except the first one) exactly once.
  for (int i = 1; i < cityIndex; i++) {
    for (int j = 0; j <= maxDay; j++) {
      variables[j] = cityDay(i + 1, j);
    }

    commanderVariable(variables, maxDay + 1);
  }

  // Must start in the start city.
  int start = cityDay(startCity, 0);
  literal(start, T);
	hardClause();

  // Must end in the start city.
  int end = cityDay(startCity, maxDay);
  literal(end, T);
	hardClause();

  solver->search();

  return 0;
}
