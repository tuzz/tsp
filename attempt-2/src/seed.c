// Seeds the chromosones by greedily visiting the next shortest path from each
// city that hasn't been visited. The second city of each tour is the same as
// the chromosone's index. Chromosones aren't simple tours and are instead based
// on a subtractive technique that aids mutation/crossover operations. e.g.
//
// 1 2 3 4 5  (canonical order)
// 1 4 5 2 3  (tour)
// 1 3 3 1 1  (chromosone)
void seed(int chromosones[1024][299], int prices[300][300][300]) {
  static int current[299];

  for (int x = 0; x < cityCount - 1; x += 1) {
    int prev = 0;
    current[0] = x + 1;
    for (int day = 1; day < cityCount - 1; day += 1) {
      int minPrice = 65536;
      int minIndex = -1;
      int price;
      for (int i = 1; i < cityCount; i += 1) {
        price = prices[day][prev][i];
        if (price && price < minPrice) {
          int visited = 0;
          for (int j = 0; j < day; j += 1) {
            if (current[j] == i) {
              visited = 1;
              break;
            }
          }
          if (!visited) {
            minPrice = price;
            minIndex = i;
          }
        }
      }
      current[day] = minIndex;
      prev = minIndex;
    }
    int lowerIndexes, c;
    for (int i = 0; i < cityCount - 1; i += 1) {
      c = current[i];
      lowerIndexes = 0;
      for (int j = 0; j < i; j += 1) {
        if (current[j] < c) {
          lowerIndexes += 1;
        }
      }
      chromosones[x][i] = c - lowerIndexes;
    }
  }
}
