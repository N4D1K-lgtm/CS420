#include <math.h>
#include <stdio.h>

#define PI 3.14159
#define MAX_NAME_LENGTH 50
#define SEPARATOR_LENGTH 55

// type definition for a pointer to any function that takes two floats and
// returns a float. all of our formula implementations will match this signature
typedef float (*CircumferenceFunc)(float, float);

// a struct to hold the name of a formula and its associated function
// we will use this to dynamically call each formula from an initialized struct
// array
typedef struct {
  char name[MAX_NAME_LENGTH];
  CircumferenceFunc func;
} CircumferenceFormula;

// all our formula implementations
float firstRamunajan(float a, float b) {
  return PI * (3 * (a + b) - sqrt((3 * a + b) * (a + b * 3)));
}

float secondRamunajan(float a, float b) {
  const float h = pow((a - b), 2) / pow((a + b), 2);
  return PI * (a + b) * (1 + 3 * h / (10 + pow((4 - 3 * h), .5)));
}

float muir(float a, float b) {
  const float s = 1.5;
  return 2 * PI * pow((pow(a, s) / 2 + pow(b, s) / 2), (1 / s));
}

float hudson(float a, float b) {
  const float h = pow((a - b), 2) / pow((a + b), 2);
  return 0.25 * PI * ((a + b) * (3 * (1 + h / 4) + 1 / (1 - h / 4)));
}

float holder(float a, float b) {
  const float s = log(2) / log(PI / 2);
  return 4 * pow(pow(a, s) + pow(b, s), (1 / s));
}

float davidCantrell(float a, float b) {
  const float s = 0.825056;
  return 4 * (a + b) -
         2 * (4 - PI) * a * b / pow((pow(a, s) / 2 + pow(b, s) / 2), (1 / s));
}

// print a separator line of length SEPARATOR_LENGTH
void printSeparator() {
  for (int i = 0; i < SEPARATOR_LENGTH; i++) {
    if (i == 0 || i == SEPARATOR_LENGTH - 1) {
      printf("+");

    } else {
      printf("-");
    }
  }
  printf("\n");
}

// print results for each formula in the formulas array tabulated according to
// the desired output
void printResults(const float a, const float b,
                  const CircumferenceFormula formulas[],
                  const int formulaCount) {
  printf("Ellipse Circumference for Major Axis: %6.2f and Minor Axis: %6.2f\n",
         a, b);
  printSeparator();
  for (int i = 0; i < formulaCount; i++) {
    printf("|%36s |%15.6f|\n", formulas[i].name, formulas[i].func(a, b));
    printSeparator();
  }
}

int main(void) {
  // declare an array of CircumferenceFormula structs, each containing a name
  // and its associated function. this approach lets us add new formulas without
  // having to change printResults
  CircumferenceFormula formulas[] = {
      {"Ramanujan's First Approximation", firstRamunajan},
      {"Ramanujan's Second Approximation", secondRamunajan},
      {"Muir's Formula", muir},
      {"Hudson's Formula", hudson},
      {"Holder's Mean", holder},
      {"David Cantrell's Formula", davidCantrell}};

  // grab floats from stdin, assume they are valid
  float a, b;
  scanf("%f %f", &a, &b);

  // number of elements in our formulas array
  int formulaCount = sizeof(formulas) / sizeof(formulas[0]);

  printResults(a, b, formulas, formulaCount);

  return 0;
}
