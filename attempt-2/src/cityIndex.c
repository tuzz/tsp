// Store a unique index for each city code.
int cityIndex(char c1, char c2, char c3) {
  static int cities[26][26][26];
  static int counter = 1;

  int index = cities[c1 - 'A'][c2 - 'A'][c3 - 'A'];

  if (!index) {
    index = counter;
    cities[c1 - 'A'][c2 - 'A'][c3 - 'A'] = index;
    counter += 1;
  }

  return index - 1;
}
