from fractions import Fraction
from typing import List, Tuple

class SimplexMethod:
    def __init__(self, filename: str):
        self.A: List[List[Fraction]] = []
        self.b: List[Fraction] = []
        self.c: List[Fraction] = []
        self.c_copy: List[Fraction] = []
        self.current_basis: List[int] = []
        self.F = Fraction(0)
        
        with open(filename, 'r') as file:
            # Читаем размеры матрицы
            first_line = file.readline().strip()
            while not first_line:
                first_line = file.readline().strip()
            file_row, file_col = map(int, first_line.split())
            
            # Читаем матрицу A
            for i in range(file_row):
                line = file.readline().strip()
                while not line:
                    line = file.readline().strip()
                row = list(map(Fraction, line.split()))
                self.A.append(row)
            
            # Читаем вектор c
            line = file.readline().strip()
            while not line:
                line = file.readline().strip()
            c_line = list(map(Fraction, line.split()))
            self.c = c_line[:file_col]
            
            # Читаем вектор b
            line = file.readline().strip()
            while not line:
                line = file.readline().strip()
            b_line = list(map(Fraction, line.split()))
            self.b = b_line[:file_row]
            
        self.c_copy = self.c.copy()

    def add_artificial_basis(self) -> None:
        row_A = len(self.A)
        col_A = len(self.A[0])
        
        self.c = [Fraction(0)] * col_A
        
        for row in self.A:
            row.extend([Fraction(0)] * row_A)
            
        for i in range(row_A):
            self.c.append(Fraction(1))
            self.A[i][col_A + i] = Fraction(1)

    def first_iterations(self) -> None:
        for i in range(len(self.b)):
            self.F -= self.b[i]
            for j in range(len(self.c)):
                self.c[j] -= self.A[i][j]
                
        start_col = len(self.A[0]) - len(self.A)
        self.current_basis = list(range(start_col, len(self.A[0])))

    def find_reference_element(self) -> Tuple[int, int]:
        for col in range(len(self.A[0])):
            if self.c[col] < Fraction(0):
                max_ratio = Fraction(0)
                find_row = -1
                
                for row in range(len(self.A)):
                    if self.b[row] != 0 and self.A[row][col] / self.b[row] > max_ratio:
                        max_ratio = self.A[row][col] / self.b[row]
                        find_row = row
                        
                if find_row != -1:
                    return find_row, col
                    
        return -1, -1

    def iteration_phase1(self, coordinate: Tuple[int, int]) -> None:
        row_idx, col_idx = coordinate
        current = self.A[row_idx][col_idx]
        
        for j in range(len(self.c)):
            self.A[row_idx][j] /= current
            
        self.b[row_idx] /= current
        
        for i in range(len(self.A)):
            if i != row_idx:
                multiplier = self.A[i][col_idx]
                for j in range(len(self.A[0])):
                    self.A[i][j] -= self.A[row_idx][j] * multiplier
                self.b[i] -= self.b[row_idx] * multiplier
                
        current_c = self.c[col_idx]
        for j in range(len(self.c)):
            self.c[j] -= self.A[row_idx][j] * current_c
        self.F -= self.b[row_idx] * current_c
        
        self.current_basis[row_idx] = col_idx

    def iteration_phase2(self, coordinate: Tuple[int, int]) -> None:
        row_idx, col_idx = coordinate
        current = self.c[col_idx]
        for j in range(len(self.c)):
            self.c[j] -= self.A[row_idx][j] * current
        self.F -= self.b[row_idx] * current
        print(self)

    def first_phase(self) -> None:
        print("---------------Phase 1----------------")
        self.add_artificial_basis()
        print(self)
        self.first_iterations()
        print(self)
        
        ref_element = self.find_reference_element()
        
        while ref_element != (-1, -1):
            self.iteration_phase1(ref_element)
            print(self)
            print(f"Control element: row - {ref_element[0]}, column - {ref_element[1]}\n")
            ref_element = self.find_reference_element()

    def second_phase(self) -> None:
        print("---------------Phase 2----------------")
        self.c = self.c_copy.copy()
        
        # Удаляем искусственные переменные
        for row in self.A:
            del row[-len(self.A):]
            
        print(self)
        
        for col in self.current_basis:
            for row_idx in range(len(self.A)):
                if self.A[row_idx][col] == Fraction(1):
                    self.iteration_phase2((row_idx, col))
                    break
                    
        self.F *= -1
        print(f"Maximum of function: {self.F}\n")

    def __str__(self) -> str:
        result = "------------------------------------------------------------------------+-----------\n"
        
        for val in self.c:
            result += f"\t{val}"
        result += f"\t|{self.F}\n"
        
        result += "------------------------------------------------------------------------+-----------\n"
        
        for i in range(len(self.A)):
            result += "\t"
            for val in self.A[i]:
                result += f"{val}\t"
            result += f"|{self.b[i]}\n"
            
        if self.current_basis:
            result += "current basis: ["
            result += "; ".join(map(str, self.current_basis))
            result += "]\n"
            
        result += "------------------------------------------------------------------------+-----------\n"
        return result