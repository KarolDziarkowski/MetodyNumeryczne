#include <iostream>
#include <fstream>
#include <cmath>

const int MAKS_ROZMIAR = 100; // maksymalny rozmiar tablicy, można dostosować według potrzeb

// Funkcja do obliczania wartości wielomianu interpolacyjnego Lagrange'a w punkcie
double interpolacjaLagrange(double x[], double y[], int n, double punkt) {
    double wynik = 0.0;

    for (int i = 0; i < n; ++i) {
        double iloczyn = y[i];
        for (int j = 0; j < n; ++j) {
            if (j != i) {
                iloczyn *= (punkt - x[j]) / (x[i] - x[j]);
            }
        }
        wynik += iloczyn;
    }

    return wynik;
}

int main() {
    std::ifstream plik("input.txt");
    if (!plik) {
        std::cerr << "Błąd otwierania pliku." << std::endl;
        return 1;
    }

    int liczbaWezlow;
    plik >> liczbaWezlow;

    double wezly[MAKS_ROZMIAR], wartosci[MAKS_ROZMIAR];
    for (int i = 0; i < liczbaWezlow; ++i) {
        plik >> wezly[i] >> wartosci[i];
    }
    plik.close();

    double punkt;
    std::cout << "Podaj punkt, w którym chcesz obliczyć wartość wielomianu interpolacyjnego Lagrange'a: ";
    std::cin >> punkt;

    double wartosc = interpolacjaLagrange(wezly, wartosci, liczbaWezlow, punkt);

    // Wyświetlenie wyników
    std::cout << "Liczba węzłów: " << liczbaWezlow << std::endl;
    std::cout << "Węzły i ich wartości funkcji:" << std::endl;
    for (int i = 0; i < liczbaWezlow; ++i) {
        std::cout << "x[" << i << "] = " << wezly[i] << ", f(x[" << i << "]) = " << wartosci[i] << std::endl;
    }
    std::cout << "Punkt: " << punkt << std::endl;
    std::cout << "Wartość wielomianu interpolacyjnego Lagrange'a w punkcie " << punkt << " wynosi " << wartosc << std::endl;

    return 0;
}
