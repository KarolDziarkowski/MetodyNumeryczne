import copy

temp = []
macierz_A = []
macierz_B = []
wektor_X = []

with open("A2.txt", "r") as plik:
    temp = plik.readlines()
for linia in temp:
    macierz_A.append([float(element) for element in linia.split()])

with open("B2.txt", "r") as plik:
    temp = plik.read()
macierz_B = [float(element) for element in temp.split()]

with open("X2.txt", "r") as plik:
    temp = plik.read()
wektor_X = [float(element) for element in temp.split()]

for i in range(len(macierz_B)):
    macierz_A[i].append(macierz_B[i])

stare_dane = [
    [2, 4, 2, 1, 10],
    [2, 2, 3, 3, 6],
    [4, 2, 2, 1, 6],
    [0, 2, 1, 1, 4],
]

nowe_dane = [
    [2, 4, 2, 1, 10],
    [1, 2, 3, 3, 6],
    [4, 5, 2, 1, 6],
    [0, 1, 2, 9, 1],
]

dane = stare_dane

print("Początkowe dane:")
for linia in dane:
    for element in linia:
        print(round(element, 2), "\t", end="")
    print()
print()


def etap_jeden(dane, x, y):
    max_wartosc = min(len(dane), len(dane[0])) - 1
    if x >= max_wartosc or y >= max_wartosc:
        return dane

    pierwsze_wartosci = [linia[y] for linia in dane[y:]]
    max_wartosc = max(pierwsze_wartosci)
    indeks = pierwsze_wartosci.index(max_wartosc) + y

    dane[x], dane[indeks] = dane[indeks], dane[x]

    temp = copy.deepcopy(dane)

    a_xy = dane[x][y]
    for i in range(x + 1, len(dane)):
        a_ix = dane[i][y]
        m = a_ix / a_xy
        for j in range(y, len(dane[0])):
            temp[i][j] = temp[i][j] - dane[x][j] * m

    return etap_jeden(temp, x + 1, y + 1)


wynik_etap_jeden = etap_jeden(dane, 0, 0)
print("Wynik etapu pierwszego:")
for linia in wynik_etap_jeden:
    for element in linia:
        print(round(element, 2), "\t", end="")
    print()
print()


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


wynik_etap_dwa = etap_dwa(wynik_etap_jeden)

print("Ostateczny wynik:")
for element in wynik_etap_dwa:
    print(round(element, 5), "\t", end="")
print()
