/*
Zadanie zaliczeniowe 4
Wstep do programowania imperatywnego - laboratorium
Maciej Dragun <m.dragun2@student.uw.edu.pl> <md406129@students.mimuw.edu.pl>
Wersja 1.0
Data: 22.01.2019

(zapewne) Kompilacja poleceniem: gcc -std=c11 -pedantic -Wall -Wextra -Werror -fstack-protector-strong -g RzeczPrawdziwieWazna.c -o RzeczPrawdziwieWazna

Program na wejściu otrzymuje reprezentację obiegu prefiksowego lewo-prawo pewnego drzewa gdzie 0 oznacza NULL
Dla zadanego drzewa wyszukuje powtarzające się weń poddrzewa i powiązuje je ze sobą w następujący sposób
Do wartości znajdującej się w węźle drzewa późniejszego w obiegu prefiksowym lewo-prawo zapisuje odległość między nimi * (-1)
Program na wyjściu wypisuje przekształcone poddrzewo dla obiegu prefiksowego lewo - prawo

Zalozenia:
1) Kazdy wiersz konczy sie znakiem '\n'
2) Wprowadzone dane będą poprawne
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct wezel
{
int w;
struct wezel *lsyn;
struct wezel *psyn;
};
typedef struct wezel Twezel;

Twezel *Buduj_Drzewo()//funkcja buduje drzewo dla wprowadzonych danych
{
int c;//zmienna na której zapisywane będą pojedyncze znaki sprawdzające czy nie doszliśmy do EOF
int przekaz;//zmienna na której zapisywane będą dane z wejścia i przekazywane do drzewa
scanf("%d", &przekaz);//czytamy wprowadzoną wartość. Na mocy (1) wiemy, że zawsze mamy co wczytać
if(przekaz == 0)
    {
    return NULL;
    }
else
    {
    Twezel *d = malloc(sizeof *d);
    d -> w = przekaz;//odczytaną wartość wpisujemy do węzła
    c = getchar();//sprawdzamy czy nie koniec danych
    if(c != EOF) //(1)
        {
        ungetc(c, stdin);
        d -> lsyn = Buduj_Drzewo();//węzeł uzupełniamy o lewego i prawego syna
        d -> psyn = Buduj_Drzewo();
        }
    return d;
    }
}

bool Czy_Takie_Same(Twezel *a, Twezel *b)//funkcja sprawdz czy dane dwa drzewa są takie same
{
if(a==b)
    {
    return true;
    }
else if(a == NULL || b == NULL)//a == NULL albo b == NULL
    {
    return false;
    }
else
    {
    return(a -> w == b -> w && Czy_Takie_Same(a -> lsyn, b -> lsyn) && Czy_Takie_Same(a -> psyn, b -> psyn));
    }
}

void Zeruj(Twezel *d)//funkcja zeruje wartości (poza tą w korzeniu) w danym poddrzewie. Przyda nam się to podczas wypisywania drzewa.
{
if(d != NULL)
    {
    d -> w = 0;
    Zeruj(d -> lsyn);
    Zeruj(d -> psyn);
    }
}

void odlegloscc(Twezel *d, Twezel *pamietaj, Twezel *do_obliczen, int *odleglosc, bool *przycisk)
//odległością nazwiemy liczbę węzłów między dwoma danymi węzłami + 1 gdyby wypisać je prefiksowo prawo-lewo 
//funkcja odlegloscc oblicza odległość dla pewnych dwóch węzłów
//przycisk opsuje kiedy należy inkrementować zmienną *odleglosc
//domyślnie *odleglosc == 0 i przycisk == false
{
if(do_obliczen != NULL)
    {
    if(do_obliczen == pamietaj)//gdy znajdziesz pierwszy węzeł zacznij liczyć
        {
        (*przycisk) = true;
        }
    if(do_obliczen == d)//gdy znajdziesz drugi węzeł przestań liczyć
        {
        (*przycisk) = false;
        }
    if(*przycisk)
        {
        ++(*odleglosc);
        }
    odlegloscc(d, pamietaj, do_obliczen -> lsyn, odleglosc, przycisk);
    odlegloscc(d, pamietaj, do_obliczen -> psyn, odleglosc, przycisk);
    }
else
    {
    if(*przycisk)//NULLe też liczymy o ile przycisk jest włączony
        {
        ++(*odleglosc);
        }
    }
}

void Sprawdzaj(Twezel *d, Twezel *pamietaj, bool *kontynuuj, Twezel *do_obliczen)
//funkcja przechodzi prefiksowo lewo-prawo po drzewie i szuka węzłów o taich samych wartościach co przekazany węzeł (ten co go odnajdujemy obiegiem prefiksowym prawo-lewo)
//jeżeli dwa węzły mają w sobie te same wartości to są dobrymi kandydatami do sprawdzenia czy nie są takimi samymi drzewami
//Zajmuje się tym funkcja Czy_Takie_Same
//Jeżeli dwa drzewa są takie same oblicza się dla nich odległość (definicja odległości została podana parę linijek wyżej)
//odległość zapisujemy w węźle i zerujemy poddrzewo, którego korzeń jest tymże węzłem (będzie to przydatne przy wypisywaniu drzewa)
{
if(pamietaj != NULL && pamietaj -> w > 0 && pamietaj != d && (*kontynuuj))//d != NULL
//Nie chcemy sprawdzać pustego węzła && Nie chcemy sprawdzać poddrzew zawartych w już podczepionym poddrzewie && 
//Nie chcemy by pamiętaj "minęło" d && Po znalezieniu najwcześniejszego poddrzewa równego rozpatrywanemu poddrzewu chcielibyśmy zaniechać dalszych poszukiwań skoro poddrzewo chcemy powiązać z poddrzewem o najmniejszej odległości względem korzenia
//kontynuuj == true -- domyślnie
    {
    if(pamietaj -> w == d -> w)//sprawdzanie czy dane poddrzewo jest dobrym kandydatem na sprawdzanie
        {
        (*kontynuuj) = !Czy_Takie_Same(d, pamietaj);
        if(!(*kontynuuj))
            {
            bool przycisk = false;
            int odleglosc = 0;
            odlegloscc(d, pamietaj, do_obliczen, &odleglosc, &przycisk);
            odleglosc = odleglosc * (-1);//wedle specyfikacji ma być to liczba ujemna
            d -> w = odleglosc;
            Zeruj(d -> lsyn);
            Zeruj(d -> psyn);
            }
        }
    Sprawdzaj(d, pamietaj -> lsyn, kontynuuj, do_obliczen);
    Sprawdzaj(d, pamietaj -> psyn, kontynuuj, do_obliczen);
    }
}

void Branie_PrePL(Twezel *d, Twezel *pamietaj, Twezel *do_obliczen)
//Funkcja bierze kolejne poddrzewa w obiegu prefiksowym prawo-lewo i sprawdza dla kolejnych poddrzew w obiegu prefiksowym lewo-prawo czy są one równe
{
if(d != NULL && d -> w > 0)//Nie chcemy powiązywać ze sobą NULLi && Poddrzew będących częścią innego już podpiętego drzewa
    {
    bool kontynuuj = true;
    Sprawdzaj(d, pamietaj, &kontynuuj, do_obliczen);
    Branie_PrePL(d -> psyn, pamietaj, do_obliczen);
    Branie_PrePL(d -> lsyn, pamietaj, do_obliczen);
    }
}

void Drukuj_Drzewo(Twezel *d)//Funkcja wypisuje drzewo w obiegu prefiksowym lewo-prawo
{
if(d != NULL)
    {
    if(d -> w != 0)
        {
        printf("%d\n", d -> w);
        }
    if(d -> w > 0)
        {
        Drukuj_Drzewo(d -> lsyn);
        Drukuj_Drzewo(d -> psyn);
        }
    }
else//dla NULLi chcemy drukować zera
//Nie będą to NULLe z podczepianych poddrzew ponieważ nimi zajmuje się if
    {
    printf("0\n");
    }
}

void usun(Twezel *x)//funkcja zwalnia alokowaną uprzenio pamięć
{
if(x != NULL)
    {
    usun(x -> lsyn);
    usun(x -> psyn);
    free(x);
    }
}

int main(void)
{
Twezel *d;
int c;
c = getchar();
if(c != EOF)
    {
    ungetc(c, stdin);
    d = Buduj_Drzewo();
    }
else
    {
    return 0;
    }
Twezel *pamietaj = d;//dwa korzenie drzewa przydatne podczas pracy algorytmu
Twezel *do_obliczen = d;
Branie_PrePL(d, pamietaj, do_obliczen);
Drukuj_Drzewo(d);
usun(d);
return 0;
}