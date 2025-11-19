#include <iostream>
#include "Simplex.h"

int main() {
    SimplexMethod A("../SimplexApp/task.txt");
    A.FirstPhase();
    A.SecondPhase();
    return 0;
}