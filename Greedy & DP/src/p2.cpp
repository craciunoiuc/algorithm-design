#include <fstream>
#include <deque>
#include <algorithm>

bool comparator(int64_t o1, int64_t o2) {
    return o2 < o1;
}

int main() {
    std::ifstream fin("p2.in");
    std::ofstream fout("p2.out");
    int64_t n, k;
    fin >> n >> k;
    int64_t TScore = 0, RScore = 0;

    // Daca vor sa se elimine k elemente inseamna ca jocul se termina direct.
    if (n == k) {
        fout << 0 << std::endl;
        fin.close();
        fout.close();
        return 0;
    }

    // Se citesc datele si se pun intr-un deque
    std::deque<int64_t> numbers;
    for (int64_t i = 0; i < n; ++i) {
        int64_t aux;
        fin >> aux;
        numbers.push_back(aux);
    }

    // Se sorteaza descrescator, se salveaza primul element si apoi se
    // elimina urmatoarele k elemente.
    std::sort(numbers.begin(), numbers.end(), comparator);
    TScore += numbers.front();
    while (k--) {
        numbers.pop_front();
        n--;
    }

    // Se joaca jocul ca la prima problema
    for (int64_t i = 1; i < n; ++i) {
        if (i & 1) {
            RScore += numbers[i];
        } else {
            TScore += numbers[i];
        }
    }

    fout << TScore-RScore << std::endl;
    fin.close();
    fout.close();
    return 0;
}
