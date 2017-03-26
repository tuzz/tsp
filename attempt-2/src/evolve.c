typedef struct {
  int index;
  int fitness;
} tuple;

int compare(const void *a, const void *b) {
  tuple *x = (tuple *)a;
  tuple *y = (tuple *)b;

  return (x->fitness - y->fitness);
}

void evolve(int chromosones[1024][299], int prices[300][300][300], int population) {
  static tuple tuples[1024];

  for (int i = 0; i < population; i += 1) {
    tuples[i].index = i;
    tuples[i].fitness = 1000000 - cost(chromosones[i], prices, 0);
  }

  qsort(tuples, population, sizeof(tuple), compare);

  int sum = 0;
  for (int i = 0; i < population; i += 1) {
    sum += tuples[i].fitness;
  }


//  for (int i = 0; i < population; i += 1) {
//    int price = cost(chromosones[i], prices, cityCount, 0);
//    if (!best || price < best) {
//      best = price;
//      printf("%d\n", best);
//    }
//  }

}
