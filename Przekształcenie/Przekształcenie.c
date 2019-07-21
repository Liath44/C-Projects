/*
Zadanie zaliczeniowe 2
Wstep do programowania imperatywnego - laboratorium
Maciej Dragun <m.dragun2@student.uw.edu.pl> <md406129@students.mimuw.edu.pl>
Wersja 1.0
Data: 03.12.2018

(zapewne) Kompilacja poleceniem: gcc -std=c11 -pedantic -Wall -Wextra -Werror -fstack-protector-strong -g potezny_protektor.c -o potezny_protektor

Program przeksztalca plansze znakow w nastepujacych krokach:
0) Wpisuje dane do planszy 20 x 80
1) Porzadkuje plansze
    a) Jezeli pod znakiem jest puste pole to przepisuje sie go na owe miejsce
    b) Idac z lewej do prawej jesli jakas kolumna jest pusta to nastepna  nie pusta kolumne przestawia sie w jej miejsce
2) Czyta znak z lewego dolnego rogu
3) Rozpoczynajac od przeczytanego znaku wymazuje grupe o ile ona istnieje
4) Porzadkuje plansze ponownie
5) Wypisuje wynik

Zalozenia:
1) Kazdy wiersz konczy sie znakiem '\n'
2) Wprowadzone dane nie przekraczaja rozmarow 20 wierszy i 80 kolumn
*/
#include <stdio.h>
#include <stdbool.h>

#define WIERSZE 20
#define KOLUMNY 80

void Zamien_Kolumne(char dane[WIERSZE][KOLUMNY], int j, int l) //Funkcja zamienia kolumny miejscami
{
for(int i = 0; i < WIERSZE; ++i)
  {
  dane[i][j] = dane[i][l];
  dane[i][l] = ' '; //zamiast przepisywac zamieniana kolumne pozwalamy sobie na wykorzystanie wiedzy, ze jest ona wypelniona spacjami
  }
}

void Uzupelnij_Poziom(int j, int i, char dane[WIERSZE][KOLUMNY]) //Funkcja uzupelnia dany wiersz spacjami gdy zaprzestano wprowadzania do niego znakow
{
for(int k = j; k < KOLUMNY; ++k)
  {
  dane[i][k] = ' ';
  }
}

void Uzupelnij_Reszte(int i, char dane[WIERSZE][KOLUMNY])//Chcac miec calkowicie wypelniona tablice dane uzupelniamy pozostale wiersze spacjami
{
for(int l = i; l < WIERSZE; ++l)
  {
  for(int k = 0; k < KOLUMNY; ++k)
    {
    dane[l][k] = ' ';
    }
  }
}

void Spadanie(char dane[WIERSZE][KOLUMNY]) //Dopoki jest choc jeden widoczny znak, bezposrednio ponizej ktorego, w tej samej kolumnie, jest pole puste, przesuwa ten znak o jeden wiersz w dol
{
for(int i = 0; i < KOLUMNY; ++i)//j - poszukiwacz pustych miejsc l - (lokatorzy) poszukiwacz kandydatow na ulokowanie w pustych miejscach
  {//i - spawdzamy kazda kolumne
  int j = WIERSZE - 1;
  while(j >= 0 && dane[j][i] != ' ')//nie interesuja nas juz uporzadkowane znaki
    {
    j--;
    }
  int l = j - 1; //wiemy ze na pozycji j elka nie bedzie miala czego szukac
  while(l >= 0) // w tym while'u l < j zawsze ergo zapisuje warunek tylko na elce
    {
    if(dane[l][i] == ' ')
      {
      --l;//brak lokatora = szukanie dalej
      }
    else
      {
      dane[j][i] = dane[l][i];
      dane[l][i] = ' ';//zamieniamy najwczesniejsze puste miejsce z pierwszym znalezionym znakiem
      --j;
      --l;
      }
    }
  }
}

void Na_Lewo(char dane[WIERSZE][KOLUMNY]) //idac od lewej do prawej jesli znajdziemy w pelni pusta kolumne zastepujemy ja pierwsza na prawo od tej pustej kolumny nie pusta kolumna
{
int j = 0;
while(j < KOLUMNY && dane[WIERSZE - 1][j] != ' ')//nie interesuja nas kolumny, ktore juz sa przesuniete na lewo. Sprawdzamy tylko pierwszy znak, bo po upadku znakow jest on gwarantem w pelni pustej kolumny
  {
  ++j;
  }
int l = j + 1;
while(l < KOLUMNY)
  {
  if(dane[WIERSZE - 1][l] == ' ')//szukamy niepustej kolumny. Sprawdzamy tylko pierwszy znak, bo po upadku znakow jest on gwarantem w pelni pustej kolumny
    {
    ++l;
    }
  else
    {
    Zamien_Kolumne(dane, j, l);
    ++l;
    ++j;
    }
  }
}

void Czytaj_Dane(char dane[WIERSZE][KOLUMNY])//Funkcja wczytuje dane
{
int znak;
int i = 0;
while((znak = getchar()) != EOF)//pobieramy znaki dopoki nie napotkamy konca pliku. Ten warunek wstawiamy tylko tutaj poniewaz korzystajac z zalozenia 1
  {
  int j = 0;
  while(znak != '\n')// wczytujemy linijke az do napotkania '\n'
    {
    dane[i][j] = znak;
    znak = getchar();//czytanie kolejnego znaku
    ++j;
    }
  Uzupelnij_Poziom(j, i, dane);//gdy doszlismy juz do '\n' uzupelniamy reszte kolumny spacjami
  ++i;
  }
Uzupelnij_Reszte(i, dane);// po skonczeniu wczytywania danych uzupelniamy reszte tabeli dane spacjami
}

void Porzadkuj_Dane(char dane[WIERSZE][KOLUMNY])//Funkcja porzadkuje dane w dwoch krokach
{
Spadanie(dane);
Na_Lewo(dane);
}

void Usuwaj(char dane[WIERSZE][KOLUMNY], int wiersz_ldrog, int kolumna_ldrog, char ldrog)//usuwa grupe rozpoczynajac od znaku w lewym dolnym rogu
{
dane[wiersz_ldrog][kolumna_ldrog] = ' ';
//kazdy z ponizszych if'ow szuka wczytanego znaku na lewo, prawo w gore i w dol. Jesli nie wychodzi poza rozmiar tablicy i znajduje taki sam co wczytany znak to wywoluje funkcje Usuwaj dla nowych argumentow
if(kolumna_ldrog + 1 < KOLUMNY && dane[wiersz_ldrog][kolumna_ldrog + 1] == ldrog)
    {
    Usuwaj(dane, wiersz_ldrog, kolumna_ldrog + 1, ldrog);
    }
if(kolumna_ldrog - 1 >= 0 && dane[wiersz_ldrog][kolumna_ldrog - 1] == ldrog)
    {
    Usuwaj(dane, wiersz_ldrog, kolumna_ldrog - 1, ldrog);
    }
if(wiersz_ldrog + 1 < WIERSZE && dane[wiersz_ldrog + 1][kolumna_ldrog] == ldrog)
    {
    Usuwaj(dane, wiersz_ldrog + 1, kolumna_ldrog, ldrog);
    }
if(wiersz_ldrog - 1 >= 0 && dane[wiersz_ldrog - 1][kolumna_ldrog] == ldrog)
    {
    Usuwaj(dane, wiersz_ldrog - 1, kolumna_ldrog, ldrog);
    }
}

int Biegun_Wschodni(char dane[WIERSZE][KOLUMNY])//Funkcja szuka najdalej wysunietego na prawo elementu nie bedacego spacja
{
int i = 0;
bool kontynuuj = true;
while(i < KOLUMNY && kontynuuj)//Porzadkowanie funkcji gwarantuje nam to, ze Biegun Wschodni znajduje sie w najnizszym wierszu tabeli dane
    {
    if(dane[WIERSZE - 1][i] != ' ')
        {
        ++i;
        }
    else
        {
        kontynuuj = false;
        }
    }
--i;
return i;
}

bool Czy_Nie_Wszystkie_Spacje(char dane[WIERSZE][KOLUMNY], int j)//Funkcja sprawdza czy istnieje znak w danym wierszu nie bedacy spacja
{
int i = 0;
bool kontynuuj_i = true;
while(i < WIERSZE && kontynuuj_i)
    {
    if(dane[j][i] == ' ')
        {
        ++i;
        }
    else
        {
        kontynuuj_i = false;
        }
    }
return !kontynuuj_i;
}

int Biegun_Polnocny(char dane[WIERSZE][KOLUMNY])//Funkcja szuka najdalej wysunietego w gore elementu nie bedacego spacja
{
int j = WIERSZE - 1;
bool kontynuuj_j = true;
while(j >= 0 && kontynuuj_j)
    {
    kontynuuj_j = Czy_Nie_Wszystkie_Spacje(dane, j);//sprawdzanie czy w danej kolumnie istnieje znak nie bedacy spacja - jesli tak to chcemy szkuac dalej by znalezc nasz upragniony pusty wiersz
    if(kontynuuj_j)
        {
        --j;
        }
    }
++j;//nie chcielibysmy przy wypisywaniu wyniku uwzgledniac pustego wiersza, wiec cofamy sie (do przodu)
return j;
}

bool Czy_jest_nie_spacja(char dane[WIERSZE][KOLUMNY], int wsch, int i, int j)
{
bool kontynuuj = true;
for(int a = j; a <= wsch && kontynuuj; ++a)
  {
  if(dane[i][a] != ' ')
    {
    kontynuuj = false;
    }
  }
return !kontynuuj;
}

void Wypisz_Co_Masz(char dane[WIERSZE][KOLUMNY], int pn, int wsch)//wypisuje tabele po przeksztalceniu o rozmiarze ograniczonym przez biegun wschodni i polnocny
{
for(int i = pn; i < WIERSZE; ++i)
    {
    bool kontynuuj = true;
    for(int j = 0; j <= wsch && kontynuuj; ++j)
        {
	kontynuuj = Czy_jest_nie_spacja(dane, wsch, i, j + 1);//to j + 1 musi zostac
        printf("%c", dane[i][j]);
        }
    printf("\n");
    }
}

void Wypisz_Wynik(char dane[WIERSZE][KOLUMNY])//wypisuje przeksztalcona tabele
{
int wsch = Biegun_Wschodni(dane);
int pn = Biegun_Polnocny(dane);
Wypisz_Co_Masz(dane, pn, wsch);
}

int main(void)
{
int wiersz_ldrog = WIERSZE - 1;
int kolumna_ldrog = 0;
//powyzej wspolrzedne lewego dolnego rogu tabeli
char dane[WIERSZE][KOLUMNY];
Czytaj_Dane(dane);
Porzadkuj_Dane(dane);
char ldrog = dane[WIERSZE - 1][0];
if (ldrog == ' ')//w takim przypadku wiedzac jak dziala funkcja Porzadkuj_Dane mmozemy wywnioskowac, ze wprowadzono dane puste lub skladajace sie z samych spacji
    {
    return 0;//czyli nie wypisujemy nic
    }
else
    {
    Usuwaj(dane, wiersz_ldrog, kolumna_ldrog, ldrog);
    Porzadkuj_Dane(dane);
    Wypisz_Wynik(dane);
    return 0;
    }
}