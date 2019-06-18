#include <fstream>
#include <vector>

int main() {
    std::ifstream fin("p3.in");
    std::ofstream fout("p3.out");
    int64_t n;
    int64_t maxSum = 0;
    fin >> n;
    std::vector<int64_t> numbers(n);
    std::vector<std::vector<int64_t>> dpTable(n);

    // Se citesc datele si se pun in vector si, totodata, se redimensioneaza
    // matricea ca sa fie de dimensiune n si se initializeaza cu 0. Se tine
    // si suma numereleor pentru rezultatul final.
    for (int64_t i = 0; i < n; ++i) {
        fin >> numbers[i];
        maxSum += numbers[i];
        dpTable[i].resize(n, 0);
    }

    // Matricea se construieste pe diagonala. Se folosesc intervale de
    // dimensiune crescatoare. Cu al doilea for se parcurg acele intervale
    // care sunt din ce in ce mai mici.
    // Se folosesc 3 variabile auxiliare care reprezinta diferite pozitii
    // din matrice. Daca se respecta conditia de pozitie se salveaza valoarea
    // din acel punct. La final, pe pozitia actuala se aseaza maximul dintre
    // prima suma (numarul de la pozitia i si minimul dintre prima si a doua
    // pozitie, deoarece se vrea ca primul jucator sa aiba maxim la final).
    for (int64_t interval = 0; interval < n; ++interval) {
        int64_t j = interval;
        for (int64_t i = 0; j < n; ++i, ++j) {
            int64_t position1 = 0, position2 = 0, position3 = 0;
            if (i + 2 <= j) {
                position1 = dpTable[i + 2][j];
            }
            if (i + 1 <= j - 1) {
                position2 = dpTable[i + 1][j - 1];
            }
            if (i <= j - 2) {
                position3 = dpTable[i][j - 2];
            }
            dpTable[i][j] = std::max(
                                numbers[i] + std::min(position1, position2), 
                                numbers[j] + std::min(position2, position3));
        }
    }

    // Deoarece recurenta este pentru a afla suma maxima facuta de Tuzgu,
    // se face o scadere pentru a se obtine diferenta dintre cei doi,
    // adica: 2 * T - (T + R) -> T - R
    fout << 2 * dpTable[0][n - 1] - maxSum << std::endl;
    fin.close();
    fout.close();
    return 0;
}
