#include "Simplex.h"

SimplexMethod::SimplexMethod(const std::string &filename)
{
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::invalid_argument("File not found");
    }

    if (file.is_open()) {
        size_t file_row = 0, file_col = 0;
        int current = 0;
        file >> file_row >> file_col;
        for (size_t row = 0; row < file_row; row++) {
            A.push_back(std::vector<frac> ());
            for (size_t col = 0; col < file_col; col++) {
                file >> current;
                A[row].push_back(frac(current));
            }
        }
        
        for (size_t c_index = 0; c_index < file_col; c_index++) {
            file >> current;
            c.push_back(frac(current));
        }

        for (size_t b_index = 0; b_index < file_row; b_index++) {
            file >> current;
            b.push_back(frac(current));
        }
        
        c_copy = c;

        file.close();
    }
}

void SimplexMethod::AddArtisticBasis()
{
    size_t row_A = A.size();
    size_t col_A = A[0].size();

    c = std::vector<frac> (col_A, 0);

    for (size_t row = 0; row < row_A; row++) {
        for (size_t col = col_A; col < row_A + col_A; col++) {
            A[row].push_back(frac(0));
        }
    }

    for (size_t i = 0; i < row_A; i++) {
        c.push_back(frac(1));
        A[i][col_A + i] = frac(1);
    }
}

void SimplexMethod::FirstIterations()
{
    for (size_t row = 0; row < b.size(); row++) {
        F -= b[row];
        for (size_t col = 0; col < c.size(); col++) {
            c[col] -= A[row][col];
        }
    }

    for (size_t current = A[0].size() - A.size(); current < A[0].size(); current++) {
        current_basis.push_back(current);
    }
}

std::pair<int, int> SimplexMethod::FindReferenceElement()
{
    for(size_t col = 0; col < A[0].size(); col++) {
        if ( c[col] < frac(0) ) {
            frac max_ratio(0);
            int find_row = -1;

            for (size_t row = 0; row < A.size(); row++) {
                if (b[row] != 0 && A[row][col] / b[row] > max_ratio) {
                    max_ratio = A[row][col] / b[row];
                    find_row = row;
                }
            }
            if (find_row != -1) {
                return std::pair<int, int> (find_row, col);
            }
        }
    }

    return std::pair<int, int>(-1, -1);
}

void SimplexMethod::IterationPhase1(std::pair<int, int> coordinate)
{
    frac current = A[coordinate.first][coordinate.second];

    for (size_t col = 0; col < c.size(); col++) {
        A[coordinate.first][col] /= current;
    }

    b[coordinate.first] /= current;

    for (size_t row = 0; row < A.size(); row++) {
        frac multiplier = A[row][coordinate.second];
        if (row != coordinate.first) {
            for (size_t col = 0; col < A[0].size(); col++) {
                A[row][col] -= (A[coordinate.first][col] * multiplier);
            }
            b[row] -= b[coordinate.first] * multiplier;
        }
    }

    current = c[coordinate.second];
    for (size_t i = 0; i < c.size(); ++i)
        c[i] -= (A[coordinate.first][i] * current);
    F -= (b[coordinate.first] * current);
    
    current_basis[coordinate.first] = coordinate.second;
}

void SimplexMethod::IterationPhase2(std::pair<int, int> coordinate)
{
    frac current = c[coordinate.second];
    for (size_t i = 0; i < c.size(); ++i)
        c[i] -= (A[coordinate.first][i] * current);
    F -= (b[coordinate.first] * current);
    std::cout << *this;
}

void SimplexMethod::FirstPhase()
{
    std::cout << "---------------Phase 1----------------\n";
    AddArtisticBasis();
    std::cout << *this;
    FirstIterations();
    std::cout << *this;

    std::pair<int, int> pair = FindReferenceElement();

    while (pair != std::pair<int, int>(-1, -1))
    {
        IterationPhase1(pair);
        std::cout << *this;
        std::cout << "Control element: row - " << pair.first << ", column - " << pair.second << "]\n\n";
        pair = FindReferenceElement();
    }
}

void SimplexMethod::SecondPhase()
{
    std::cout << "---------------Phase 2----------------\n";
    c = c_copy;
    for (size_t row = 0; row < A.size(); row++) {
        for (size_t col = 0; col < A.size(); col++) {
            A[row].pop_back();
        }
    }
    std::cout << *this;

    for (size_t col : current_basis) {
        for (size_t row = 0; row < A.size(); row ++) {
            if ( A[row][col] == frac(1)) {
                IterationPhase2(std::pair<int, int>(row, col));
                break;
            } 
        }
    }

    F *= - 1;
    
    std::cout << "Maximum of function: " << F;
}

std::ostream& operator<<(std::ostream& out, SimplexMethod& other)
{
    out << "------------------------------------------------------------------------+-----------\n";
    for (size_t i = 0; i < other.c.size(); ++i) {
        out << "\t" << other.c[i];
    }
    out << "\t|" << other.F << "\n";

    out << "------------------------------------------------------------------------+-----------\n";

    for (size_t i = 0; i < other.A.size(); ++i) {
        out << "\t";
        for (size_t j = 0; j < other.A[i].size(); ++j) {
            out << other.A[i][j] << "\t";
        }
        out << "|" << other.b[i] << "\n";
    }
    if(!other.current_basis.empty()) {
        out << "current basis: [";
        for (size_t index = 0; index < other.current_basis.size() - 1; index++) {
            out << other.current_basis[index] << "; ";
        }
        out << other.current_basis[other.current_basis.size() - 1] << "]\n";
    }
    out << "------------------------------------------------------------------------+-----------\n";
    return out;
}