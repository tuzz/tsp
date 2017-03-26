#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "parse.c"
#include "seed.c"
#include "cost.c"
#include "evolve.c"

int cityCount;

int main(int argc, char **argv) {
  srand(time(NULL));

  int prices[300][300][300];
  int chromosones[1024][299];
  parse(prices);
  seed(chromosones, prices);
  evolve(chromosones, prices, cityCount - 1);

  return 0;
}
