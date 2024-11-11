import copy


def etap_jeden(dane, x, y, kolumny):
    dane_ = copy.deepcopy(dane)
    max_wartosc = min(len(dane_), len(dane_[0])) - 1
    if x >= max_wartosc or y >= max_wartosc:
        print("kolumny: " + " ".join(str(item) for item in kolumny))
        return dane_

    if not kolumny:
        kolumny = list(range(len(dane_)))

    # Znajdź maksymalny element do podziału, zaczynając od y-tej kolumny
    indeks_max = None
    max_wartosc = float('-inf')  # Użyj minus nieskończoności jako wartości początkowej
    for i in range(y, len(dane_)):
        if abs(dane_[i][y]) > max_wartosc:
            max_wartosc = abs(dane_[i][y])
            indeks_max = i

    # Zamień wiersze, aby umieścić maksymalny element na diagonali
    dane_[x], dane_[indeks_max] = dane_[indeks_max], dane_[x]

    # Zamień kolumny, aby przechowywać kolejność zmian
    kolumny[x], kolumny[indeks_max] = kolumny[indeks_max], kolumny[x]

    a_xy = dane_[x][y]

    for i in range(x + 1, len(dane_)):
        a_ix = dane_[i][y]
        if a_xy != 0:  # Sprawdzenie, czy a_xy nie jest zerem, aby uniknąć dzielenia przez zero
            m = a_ix / a_xy
            for j in range(y, len(dane_[0])):
                dane_[i][j] = dane_[i][j] - dane_[x][j] * m

    return etap_jeden(dane_, x + 1, y + 1, kolumny)


def suma(dane, i, wektor_x):
    wynik = 0
    n = len(dane) - 1
    for k in range(i + 1, n + 1):
        a_ik = dane[i][k]
        x_k = wektor_x[k]
        wynik += a_ik * x_k
    return wynik


def etap_dwa(dane):
    n = len(dane) - 1
    wektor_x = [0 for i in range(n + 1)]
    wektor_x[n] = dane[n][-1] / dane[n][n]
    for i in range(len(dane) - 2, -1, -1):
        b_i = dane[i][-1]
        suma_nk = suma(dane, i, wektor_x)
        a_ii = dane[i][i]
        wynik = (b_i - suma_nk) / a_ii
        wektor_x[i] = wynik
    return wektor_x


def main():
    stara_dane = [
        [2, 4, 2, 1, 10],
        [2, 2, 3, 3, 6],
        [4, 2, 2, 1, 6],
        [0, 2, 1, 1, 4],
    ]
    dane = stara_dane

    print("początkowe dane:")
    for linia in dane:
        for element in linia:
            print(round(element, 2), "\t", end="")
        print()
    print()

    wynik_etapu_jeden = etap_jeden(dane, 0, 0, [])
    print("\nwynik etapu pierwszego:")
    for linia in wynik_etapu_jeden:
        for element in linia:
            print(round(element, 2), "\t", end="")
        print()
    print()

    wynik_etapu_dwa = etap_dwa(wynik_etapu_jeden)

    print("końcowy wynik:")
    for element in wynik_etapu_dwa:
        print(round(element, 5), "\t", end="")
    print()


if __name__ == "__main__":
    main()
