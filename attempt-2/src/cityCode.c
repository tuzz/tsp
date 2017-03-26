static char cityCodes[300][4];

void setCityCode(int index, char c1, char c2, char c3) {
  cityCodes[index][0] = c1;
  cityCodes[index][1] = c2;
  cityCodes[index][2] = c3;
}

char* cityCode(int index) {
  return cityCodes[index];
}
