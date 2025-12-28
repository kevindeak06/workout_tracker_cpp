#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

// Adatszerkezet az edzesekhez
struct Edzes {
    std::string datum;
    std::string gyakorlat;
    int suly;
    int ismetles;
    int szeria;
};

// Adatok betoltese CSV-bol
// A sorokat vesszonkent daraboljuk fel stringstream-mel
void betoltes(std::vector<Edzes>& lista, std::string fajlnev) {
    std::ifstream file(fajlnev);
    if (!file.is_open()) {
        return; // Ha nincs fajl, nem baj, majd letrejon
    }

    std::string sor;
    while (getline(file, sor)) {
        if (sor.empty()) continue;

        std::stringstream ss(sor);
        std::string adat;
        std::vector<std::string> adatok;

        // Vesszonkent szedjuk szet a sort
        while (getline(ss, adat, ',')) {
            adatok.push_back(adat);
        }

        // Csak akkor dolgozzuk fel, ha megvan mind az 5 adat
        if (adatok.size() == 5) {
            Edzes e;
            e.datum = adatok[0];
            e.gyakorlat = adatok[1];
            try {
                e.suly = std::stoi(adatok[2]);
                e.ismetles = std::stoi(adatok[3]);
                e.szeria = std::stoi(adatok[4]);
                lista.push_back(e);
            }
            catch (...) {
                // Ha hibas a szam, atugorjuk a sort
                continue;
            }
        }
    }
    file.close();
}

// Mentes fajlba
void mentes(const std::vector<Edzes>& lista, std::string fajlnev) {
    std::ofstream file(fajlnev);
    if (!file.is_open()) {
        std::cout << "Hiba a fajl megnyitasakor!\n";
        return;
    }

    for (const auto& e : lista) {
        file << e.datum << ","
            << e.gyakorlat << ","
            << e.suly << ","
            << e.ismetles << ","
            << e.szeria << "\n";
    }
    file.close();
}

int main() {
    std::vector<Edzes> edzesek;
    std::string fajlnev = "edzesek.csv";

    // Program inditasakor betoltjuk az adatokat
    betoltes(edzesek, fajlnev);

    int valasztas = 0;

    while (valasztas != 4) {
        std::cout << "\n--- EDZO NAPLO ---\n";
        std::cout << "1. Uj edzes felvetele\n";
        std::cout << "2. Korabbi edzesek listazasa\n";
        std::cout << "3. Utolso edzes torlese\n";
        std::cout << "4. Kilepes\n";
        std::cout << "Valasztas: ";

        std::cin >> valasztas;

        // Hibakezeles, ha nem szamot irnak be
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            std::cout << "Hibas bemenet!\n";
            continue;
        }

        if (valasztas == 1) {
            Edzes uj;
            std::cout << "Datum (YYYY-MM-DD): ";
            std::cin >> uj.datum; // Feltetelezzuk, hogy nincs benne szokoz

            std::cout << "Gyakorlat neve: ";
            std::cin.ignore(); // Buffer ürítése getline elõtt
            std::getline(std::cin, uj.gyakorlat);

            std::cout << "Suly (kg): ";
            std::cin >> uj.suly;

            std::cout << "Ismetles: ";
            std::cin >> uj.ismetles;

            std::cout << "Szeria: ";
            std::cin >> uj.szeria;

            edzesek.push_back(uj);
            mentes(edzesek, fajlnev); // Minden felvétel után mentünk
            std::cout << "Sikeresen rogzitve!\n";

        }
        else if (valasztas == 2) {
            std::cout << "\nRogzitett edzesek:\n";
            if (edzesek.empty()) {
                std::cout << "Nincs adat.\n";
            }
            else {
                for (int i = 0; i < edzesek.size(); i++) {
                    std::cout << i + 1 << ". "
                        << edzesek[i].datum << " - "
                        << edzesek[i].gyakorlat << ": "
                        << edzesek[i].suly << "kg "
                        << edzesek[i].szeria << "x" << edzesek[i].ismetles << "\n";
                }
            }

        }
        else if (valasztas == 3) {
            // Egyszerusites: csak az utolsot toroljuk vagy index alapjan
            if (!edzesek.empty()) {
                int index;
                std::cout << "Hanyas sorszamut toroljem? ";
                std::cin >> index;

                if (index > 0 && index <= edzesek.size()) {
                    edzesek.erase(edzesek.begin() + index - 1);
                    mentes(edzesek, fajlnev);
                    std::cout << "Torolve.\n";
                }
                else {
                    std::cout << "Nincs ilyen sorszam.\n";
                }
            }
            else {
                std::cout << "Nincs mit torolni.\n";
            }
        }
    }

    return 0;
}