#include "solver.cc"

extern const int MAX_WEIGHT;
extern int nextLiteral();
extern void hardClause();
extern void literal(int, bool);

int group[3];
int groupIndex;
int commanderIndex;
int commander;
int *commanders;

// Enforces an 'exactly one' constraint using O(n) clauses and O(n) variables.
// https://www.cs.cmu.edu/~wklieber/papers/2007_efficient-cnf-encoding-for-selecting-1.pdf
void commanderVariable(int *array, int groupSize) {
  groupIndex = 0;
  commanderIndex = 0;

  // Base cases:
  if (groupSize == 1) {
    // The one-and-only variable must be true.
    literal(array[0], T);
    hardClause();
  }

  if (groupSize == 2) {
    // One or the other must be true.
    literal(array[0], F);
    literal(array[1], F);
    hardClause();

    literal(array[0], T);
    literal(array[1], T);
    hardClause();
  }

  if (groupSize == 3) {
    // At most one variable can be true.
    literal(array[0], F);
    literal(array[1], F);
    hardClause();

    literal(array[0], F);
    literal(array[2], F);
    hardClause();

    literal(array[1], F);
    literal(array[2], F);
    hardClause();

    // At least one variable must be true.
    literal(array[0], T);
    literal(array[1], T);
    literal(array[2], T);
    hardClause();
  }

  if (groupSize <= 3) {
    return;
  }

  // Recursive case.
  for (int i = 0; i < groupSize; i++) {
    group[groupIndex] = array[i];

    groupIndex++;
    groupIndex %= 3;

    if (!groupIndex) {
      // Make a commander for the group.
      commander = nextLiteral();
      commanders[commanderIndex] = commander;
      commanderIndex++;

      // At most one variable in a group can be true.
      literal(group[0], F);
      literal(group[1], F);
      hardClause();

      literal(group[0], F);
      literal(group[2], F);
      hardClause();

      literal(group[1], F);
      literal(group[2], F);
      hardClause();

      // If the commander is true, at least one of the variables must be true.
      literal(commander, F);
      literal(group[0], T);
      literal(group[1], T);
      literal(group[2], T);
      hardClause();

      // If the commander is false, none of the variables can be true.
      literal(commander, T);
      literal(group[0], F);
      hardClause();

      literal(commander, T);
      literal(group[1], F);
      hardClause();

      literal(commander, T);
      literal(group[2], F);
      hardClause();
    }
  }

  // Promote remaining variables to commanders.
  for (int i = 0; i < groupIndex; i++) {
    commanders[commanderIndex] = group[i];
    commanderIndex++;
  }

  // Exactly one of the commander variables is true.
  commanderVariable(commanders, commanderIndex);
}
