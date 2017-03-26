// Extract a number from a line that starts at the index.
int extractNumber(char *line, int index) {
  int number = 0;

  while(line[index] >= ZERO && line[index] <= NINE) {
    number *= 10;
    number += line[index] - ZERO;

    index++;
  }

  return number;
}

// Return the index of the next term on the line.
int scanRight(char *line, int index) {
  while (line[index] != ' ') index++;
  return index + 1;
}
