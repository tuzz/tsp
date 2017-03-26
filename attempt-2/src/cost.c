int cost(int chromosone[299], int prices[300][300][300], int print) {
  static int current[299];
  int used[299] = {0};

  for (int x = 0; x < cityCount; x += 1) {
    int c = chromosone[x];
    for (int i = 0; i < cityCount; i += 1) {
      if (!used[i]) {
        c -= 1;
      } else {
      }
      if (c == 0) {
        current[x] = i + 1;
        used[i] = 1;
        break;
      }
    }
  }

  int cur, prev = 0, sum = 0;
  for (int i = 0; i < cityCount; i += 1) {
    cur = current[i];
    sum += prices[i][prev][cur];
    prev = cur;
  }
  sum += prices[cityCount - 1][prev][0];

  if (print) {
    printf("%d\n", sum);
    prev = 0;
    int price;
    for (int i = 0; i < cityCount; i += 1) {
      cur = current[i];
      price = prices[i][prev][cur];
      printf("%s %s %d %d\n", cityCode(prev), cityCode(cur), i, price);
      prev = cur;
    }
    price = prices[cityCount - 1][prev][0];
    printf("%s %s %d %d\n", cityCode(prev), cityCode(0), cityCount - 1, price);
  }

  return sum;
}
