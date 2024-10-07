#include <iostream>
#include <2knighs.hpp>

using namespace TwoKnights;

void print_solution(std::ostream& out, const Solution& solution) {
   
    out << "Out:" ;
    out << std::endl << "G: ";
    for(const auto& el : *solution.getXAxiPath()) {
        out << el;
    }
    out << std::endl << "L: ";
    for(const auto& el : *solution.getYAxiPath()) {
        out << el;
    }
    out << std::endl;
}

int main() {

    auto solution = Solution(3, 2, 11, 7);
    
    solution.Get();

    print_solution(std::cout, solution);

    return 0;
}