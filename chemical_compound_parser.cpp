#include <iostream>
#include <unordered_map>
#include <stack>
#include <cctype>
using namespace std;

// Atomic weights (simplified for demo)
unordered_map<string, double> atomic_weights = {
    {"H", 1.008}, {"O", 15.999}, {"C", 12.011}, {"N", 14.007},
    {"Fe", 55.845}, {"Na", 22.990}, {"Cl", 35.453}, {"Mg", 24.305},
    {"S", 32.06}, {"P", 30.974}, {"K", 39.098}
};

double parseChemicalFormula(const string& formula) {
    stack<unordered_map<string, int>> stk;
    unordered_map<string, int> current;
    int i = 0;
    while (i < formula.size()) {
        if (formula[i] == '(') {
            stk.push(current);
            current.clear();
            i++;
        } else if (formula[i] == ')') {
            i++;
            int multiplier = 0;
            while (i < formula.size() && isdigit(formula[i])) {
                multiplier = multiplier * 10 + (formula[i++] - '0');
            }
            for (auto& pair : current) {
                pair.second *= (multiplier == 0 ? 1 : multiplier);
            }
            auto top = stk.top(); stk.pop();
            for (auto& pair : current) {
                top[pair.first] += pair.second;
            }
            current = top;
        } else {
            string element;
            element += formula[i++];
            if (i < formula.size() && islower(formula[i])) {
                element += formula[i++];
            }
            int count = 0;
            while (i < formula.size() && isdigit(formula[i])) {
                count = count * 10 + (formula[i++] - '0');
            }
            current[element] += (count == 0 ? 1 : count);
        }
    }

    double total_weight = 0;
    for (auto& pair : current) {
        total_weight += atomic_weights[pair.first] * pair.second;
    }
    return total_weight;
}

int main() {
    string formula;
    cout << "Enter chemical formula (e.g., H2O, Fe(NO3)3): ";
    cin >> formula;

    try {
        double result = parseChemicalFormula(formula);
        cout << "Molecular weight of " << formula << " is: " << result << " g/mol" << endl;
    } catch (...) {
        cout << "Error: Invalid formula or unknown element!" << endl;
    }

    return 0;
}
