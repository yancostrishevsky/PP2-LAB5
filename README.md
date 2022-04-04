Klasa-wrapper ma zaimplementowac metody, ktore zawiera klasa abstrakcyjna IContainerWrapper.
Implementujac kazda z metod nalezy zmieniac odpowiadajace im stale preprocesora z 0 na 1.
Dzieki temu kolejne testy beda przechodzic.
Zaleznie od uzywanego pod spodem kontenera bedziemy mieli dostepne rozne metody,
czesc metod do zaimplementowania mozna w sposob przezroczysty przekazac do wykonania
uzywanemu kontenerowi, ktory dana metode juz ma zaimplementowana.
Jednakze czesc metod nie jest zaimplementowana, do tego trzeba juz uzyc internetu.
Odsylam do [dokumentacji standardowych kontenerow](https://en.cppreference.com/w/cpp/container),
oraz do [artykulu robiacego benchmark](https://baptiste-wicht.com/posts/2017/05/cpp-containers-benchmark-vector-list-deque-plf-colony.html).
____________________________________________________________________________________
## Do rozwazenia dla zaawansowanych:
1. Gdzie by sie przydal std::optional?
2. Co by nam dala pula pamieci?
3. Zachecam do poeksperymentowania z typem `value_type` i z rozmiarem elementow - czy cos to zmienia?
4. Dlaczego `pop_front` z biblioteki standardowej zwraca `void`?
____________________________________________________________________________________
## Uwaga:
1. Zachecam do uzywania czego sie da z biblioteki standardowej.
2. Metody większe niż 1-linijkowe powinny być zadeklarowane w klasie,
   zdefiniowane poza klasą w pliku zrodlowym.
3. Obiekty typów klasowych powinny być w miarę możliwości przekazywane
   w argumentach funkcji przez referencję do stalej,
4. Proszę stosować słówko "const" w odpowiednich miejscach.
5. W pliku naglowkowym prosze nie wlaczac dodatkowych naglowkow typu:
   <iostream>, <algorithm> - takie rzeczy powinny byc w pliku zrodlowym
6. Prosze aby w pliku naglowkowym nie bylo `using namespace std;`, w zrodlowym moze.
7. Testy nie testuja przypadkow wyjatkowych, ale jak ktos umie warto zabezpieczyc metody
   na dziwne uzycie.
8. W kodzie sa fragmenty -niespodzianki.
   Powiem o tym na zajeciach (a w razie czego prosze o przypomnienie)
Mozna tworzyc dowolna ilosc metod pomocniczych, jednakze aby byly one prywatne.
