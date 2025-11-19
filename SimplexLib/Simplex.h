#pragma once
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include "FractionalNumbers.h"

class SimplexMethod {
    private:
    std::vector<std::vector<frac>> A;
    std::vector<frac> b;
    std::vector<frac> c;
    std::vector<frac> c_copy;
    std::vector<size_t> current_basis;

    frac F;

    public:
    SimplexMethod(const std::string& filename);

    void AddArtisticBasis();
    void FirstIterations();
    std::pair<int, int> FindReferenceElement();
    void IterationPhase1(std::pair<int,int> coordinate);
    void IterationPhase2(std::pair<int, int> coordinate);

    void FirstPhase();
    void SecondPhase();

    friend std::ostream& operator<<(std::ostream& out,SimplexMethod& other);
};
