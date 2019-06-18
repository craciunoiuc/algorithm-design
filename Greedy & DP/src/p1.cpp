#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>

bool comparator(int64_t o1, int64_t o2) {
    return o2 > o1;
}

int main() {
    std::ifstream fin("p1.in");
    std::ofstream fout("p1.out");
    int64_t n;
    int64_t TScore = 0;
    int64_t RScore = 0;
    
    // Se citesc datele si se pun intr-un vector
    fin >> n;
    std::vector<int64_t> numbers(n);
    for (int64_t i = 0; i < n; ++i) {
        fin >> numbers[i];
    }

    // Se sorteaza numerele din vector descrescator pentru a se aplica greedy
    std::sort(numbers.begin(), numbers.end(), comparator);

    // Se parcurge vectorul sortat descrescator si se aduna la scorul fiecaruia
    // numarul de pe acea pozitie. Cei doi alterneaza luatul elementelor.
    for (int64_t i = 0; i < n; ++i) {
        if (i & 1) {
            RScore += numbers[i];
        } else {
            TScore += numbers[i];
        }
    }

    // La final se afiseaza diferenta pozitiva dintre cei doi
    fout << abs(TScore-RScore) << std::endl;
    fin.close();
    fout.close();
    return 0;
}
