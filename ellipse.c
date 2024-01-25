#include <math.h>
#include <stdio.h>
#include <string.h>

#define PI 3.14159
#define MAX_FORMULAS 6
#define MAX_NAME_LENGTH 50
#define SEPARATOR_LENGTH 55

typedef float (*CircumferenceFunc)(float, float);

typedef struct {
    char name[MAX_NAME_LENGTH];
    CircumferenceFunc func;
} CircumferenceFormula;


float first_ramunajan(float a, float b) {
    return PI * (3 * (a + b) - sqrt((3 * a + b) * (a + b * 3)));
}

float second_ramunajan(float a, float b) {
  float h = pow((a - b), 2) / pow((a + b), 2);
  return PI * (a + b) * ( 1 + 3 * h / (10 + pow((4 - 3 * h), .5)));
}

float muir(float a, float b) {
  float s = 1.5;
  return 2 * PI * pow((pow(a, s) / 2 + pow(b, s) / 2), (1 / s));
}

float hudson(float a, float b) {
  float h = pow((a - b), 2) / pow((a + b), 2);
  return 0.25 * PI * ((a + b) * (3 * (1 + h / 4) + 1 / (1 - h / 4)));
}

float holder(float a, float b) {
  float s = log(2) / log(PI / 2);
  return 4 * pow(pow(a, s) + pow(b, s), (1 / s));
}

float david_cantrell(float a, float b) {
  float s = 0.825056;
  return 4 * (a + b) - 2 * (4 - PI) * a * b / pow((pow(a, s) / 2 + pow(b, s) / 2), (1 / s));
}

void printSeparator() {
    for (int i = 0; i < SEPARATOR_LENGTH; i++) {
        if (i == 0 || i == SEPARATOR_LENGTH - 1) {
            printf("+");

        }
        else {
            printf("-");
        }
    }
    printf("\n");
}

float promptForFloat(const char *prompt) {
    float value;
    printf("%s", prompt);
    scanf("%f", &value);
    return value;
}

void printResults(const float a, const float b, const CircumferenceFormula formulas[], const int formulaCount) {
    printf("Ellipse Circumference for Major Axis: %6.2f and Minor Axis: %6.2f\n", a, b);
    printSeparator();
    for (int i = 0; i < formulaCount; i++) {
        printf("|%36s |%15.6f|\n", formulas[i].name, formulas[i].func(a, b));
        printSeparator();
    }
}

int main(void) {
    CircumferenceFormula formulas[MAX_FORMULAS] = {
        {"Ramanujan's First Approximation", first_ramunajan},
        {"Ramanujan's Second Approximation", second_ramunajan},
        {"Muir's Approximation", muir},
        {"Hudson's Approximation", hudson},
        {"Holder's Approximation", holder},
        {"David Cantrell's Approximation", david_cantrell}
    };

    float a = promptForFloat("Enter a value for the Major Axis (a): ");
    float b = promptForFloat("Enter a value for the Minor Axis (b): ");

    printResults(a, b, formulas, MAX_FORMULAS);

    return 0;
}
