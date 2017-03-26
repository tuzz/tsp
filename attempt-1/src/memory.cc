extern int nextLiteral();
extern int *commanders;

int *cities;
int *cityDays;
int *variables;
int *flightPrices;
static char cityCodes[MAX_CITIES + 1][3];

int cityIndex = 0;

// Allocate memory on the heap. All zeroes.
void initializeHeap() {
  cities = (int *)calloc(ALPHA3, sizeof(int));
  cityDays = (int *)calloc(MAX_CITIES * MAX_DAYS, sizeof(int));
  variables = (int *)calloc(MAX_DAYS, sizeof(int));
  commanders = (int *)calloc(MAX_DAYS, sizeof(int));
  flightPrices = (int *)calloc(MAX_DAYS * MAX_DAYS * MAX_DAYS, sizeof(int));
};

// Return a unique index for the city.
int city(char s1, char s2, char s3) {
  int address = (s1 - A) * ALPHA2 + (s2 - A) * ALPHA + (s3 - A);

  if (!cities[address]) {
    cityIndex++;
    cities[address] = cityIndex;

    cityCodes[cityIndex][0] = s1;
    cityCodes[cityIndex][1] = s2;
    cityCodes[cityIndex][2] = s3;
  }

  return cities[address];
}

// Return a unique literal for the city/day combination.
int cityDay(int city, int day) {
  int address = day * MAX_CITIES + city - 1;

  if (!cityDays[address]) {
    cityDays[address] = nextLiteral();
  }

  return cityDays[address];
}

void rememberPrice(int from, int to, int day, int price) {
  int address = from * MAX_DAYS * MAX_DAYS
              + to * MAX_DAYS
              + day;

  flightPrices[address] = price;
}

int getPrice(int from, int to, int day) {
  int address = from * MAX_DAYS * MAX_DAYS
              + to * MAX_DAYS
              + day;

  return flightPrices[address];
}
