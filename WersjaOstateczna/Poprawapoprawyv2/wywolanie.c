#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//zadeklarowanie wywołania
extern int dodaj(int a, int b);

//funkcja na sprawdzenie czy string zawiera tylko znaki uzywane w hex
int check_Hex(const char *str) {
  for (int i = 0; str[i] != '\0'; i++) {
    if (!isxdigit(str[i])) {
      return 0;
    }
  }
  return 1;
}
//inicjalizacja programu, liczba argumentów, argumenty terminala w tablicy
int main(int argc, char *argv[]) {
  if (argc != 4) {
    printf("Podano nieprawidlowa liczbe argumentow.\n");
    return 1;
  }

  //argv [1] to pierwszy parametr (adres stringa)
  //argv [2] to znak jako string
  //argv [3] to 2. string
  char *num1 = argv[1];
  char *znak = argv[2];
  char *num2 = argv[3];
  int pom1, pom2;

  //Obliczenie dlugosci stringów
  int strlen1 = strlen(num1);
  int strlen2 = strlen(num2);

  if (!check_Hex(num1)) {
    printf("Podano nieprawidlowa liczbe nr 1\n");
    return 1;
  }
  if (!check_Hex(num2)) {
    printf("Podano nieprawidlowa liczbe nr 2\n");
    return 1;
  }
  if (*znak != '+') {
    printf("Przepraszam nie wykonuje takiej operacji. Moge tylko dodawac 2 liczby.\n");
    return 1;
  }

  //przygotowanie tabel dla liczb pod konwersje oraz tablic do przeslania do pliku z funkcja dodaj
  int *wynik;
  int *przepisana;
  int *Num1;
  int *Num2;
  int *Final;

  // Alokacja pamięci dla tablic z uwzględnieniem większego stringa
  size_t maxlen = (strlen1 >= strlen2) ? strlen1 + 1 : strlen2 + 1;
  wynik = (int *)malloc(maxlen * sizeof(int));
  przepisana = (int *)malloc(maxlen * sizeof(int));
  Num1 = (int *)malloc(maxlen * sizeof(int));
  Num2 = (int *)malloc(maxlen * sizeof(int));
  Final = (int *)malloc(maxlen * sizeof(int));

  // Sprawdzenie poprawności alokacji pamięci
  if (wynik == NULL || przepisana == NULL || Num1 == NULL || Num2 == NULL || Final == NULL) {
    printf("Blad alokacji pamieci.\n");
    free(wynik);
    free(przepisana);
    free(Num1);
    free(Num2);
    free(Final);
    return 1;
  }

  // Wypełnienie tablic zerami w hex
  for (int i = 0; i < maxlen; i++) {
    wynik[i] = 0x00;
    przepisana[i] = 0x00;
    Num1[i] = 0x00;
    Num2[i] = 0x00;
    Final[i] = 0x00;
  }
  // konwersja pierwszej liczby
  for (int i = 0; i < strlen1; i++) {
    char c = num1[i];
    if (c <= '9') {
      Num1[i + 1] = c - '0';
    } else if (c <= 'F') {
      Num1[i + 1] = c - 'A' + 10;
    } else if (c <= 'f') {
      Num1[i + 1] = c - 'a' + 10;
    }
  }

  // konwersja drugiej liczby
  for (int i = 0; i < strlen2; i++) {
    char c = num2[i];
    if (c <= '9') {
      Num2[i + 1] = c - '0';
    } else if (c <= 'F') {
      Num2[i + 1] = c - 'A' + 10;
    } else if (c <= 'f') {
      Num2[i + 1] = c - 'a' + 10;
    }
  }
  //przepisanie liczb do tablic wynik i przepisana z uwzględnieniem długości
  // Wypełnienie tablic wynik i przepisana, wyrównując krótszą liczbę zerami na początku
  if (strlen1 >= strlen2) {
    for (int i = 0; i < strlen1 + 1; i++) {
      wynik[i] = Num1[i];
    }
    for (int i = 0; i < strlen2 + 1; i++) {
      int prop = strlen1 - strlen2;
      przepisana[i + prop] = Num2[i];
    }
  } else {
    for (int i = 0; i < strlen1 + 1; i++) {
      int prop = strlen2 - strlen1;
      wynik[i + prop] = Num1[i];
    }
    for (int i = 0; i < strlen2 + 1; i++) {
      przepisana[i] = Num2[i];
    }
  }
  // Wywołanie funkcji dodaj, pętla przekazuje liczby z tablic
  if (strlen1 >= strlen2){
    for (int i = strlen1; i > 0; i--){
    pom1 = wynik[i];
    pom2 = przepisana[i];
    Final[i] = dodaj(pom1, pom2);
    }
  }
  if (strlen1 < strlen2){
    for (int i = strlen2; i > 0; i--){
    pom1 = wynik[i];
    pom2 = przepisana[i];
    Final[i] = dodaj(pom1, pom2);
    }
  }
  //obsługa przeniesienia
  if (strlen1 >= strlen2){
    for (int i = strlen1; i > 0; i--){
    if (Final[i] >= 0x10){
      Final[i] = Final[i] - 0x10;
      Final[i-1] = Final[i-1] + 0x01;
    }
    }
  }
  if (strlen1 < strlen2){
    for (int i = strlen2; i > 0; i--){
    if (Final[i] >= 0x10){
      Final[i] = Final[i] - 0x10;
      Final[i-1] = Final[i-1] + 0x01;
    }
    }
  }
  //drukowanie liczb
  printf("%s\n", num1);
  printf("%s\n", znak);
  printf("%s\n", num2);
  for (int i = 0; i < maxlen; i++) {
    printf("%x", Final[i]);
  }
  printf("\n");
  //zwolnienie alokowanych dynamicznie tablic z pamieci
  free(wynik);
  free(przepisana);
  free(Num1);
  free(Num2);
  free(Final);
  return 0;
}
