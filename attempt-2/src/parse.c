#include "cityIndex.c"
#include "cityCode.c"

extern int cityCount;

// Parse a number from a line that starts at the index.
int parseNumber(char *line, int index) {
  int number = 0;

  while(line[index] >= '0' && line[index] <= '9') {
    number *= 10;
    number += line[index] - '0';

    index += 1;
  }

  return number;
}

// Return the index of the next term on the line.
int scanRight(char *line, int index) {
  while (line[index] != ' ') index++;
  return index + 1;
}

void parse(int prices[300][300][300]) {
  const int lineLength = 20;
  char line[lineLength];

  // Remember the start city.
  fgets(line, lineLength, stdin);
  cityIndex(line[0], line[1], line[2]);

  // For each flight:
  int prev = -1;
  cityCount = 0;
  while (fgets(line, lineLength, stdin)) {
    int from = cityIndex(line[0], line[1], line[2]);
    int to = cityIndex(line[4], line[5], line[6]);
    int day = parseNumber(line, 8);
    int price = parseNumber(line, scanRight(line, 9));

    prices[day][from][to] = price;

    if (from != prev) {
      setCityCode(from, line[0], line[1], line[2]);
    }

    if (day >= cityCount) {
      cityCount = day + 1;
    }
  }
}
