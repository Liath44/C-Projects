#include <stdio.h>
#include <stdbool.h>



bool Skos_1(int spr_x, int spr_y, char tablica[][8])
  {
  bool aa = true;
  int x = spr_x;
  int y = spr_y;
  int i = 1;
  int j = 1;
  while(x>0 && y<7 && i<5)
    {
    --x;
    ++y;
    ++i;
    }
  while(x+4<=7 && y-4>=0 && j<=5)
    {
    if(tablica[y][x]!='-' && tablica[y][x]==tablica[y - 4][x + 4])
      {
      if(tablica[y-1][x+1]!='-' && tablica[y-1][x+1]==tablica[y - 3][x + 3])
      {
    if(tablica[y-2][x+2]!='-')
      {
      aa = false;
      }
    }
      }
      ++x;
      --y;
      ++j;
    }
  return aa;
  }


bool Skos_2(int spr_x, int spr_y, char tablica[][8])
{
  bool bb = true;
  int x = spr_x;
  int y = spr_y;
  int i = 1;
  int j = 1;
  while(x<7 && y<7 && i<5)
    {
    ++x;
    ++y;
    ++i;
    }
  while(x-4>=0 && y-4>=0 && j<=5)
    {
    if(tablica[y][x]!='-' && tablica[y][x]==tablica[y - 4][x - 4])
      {
      if(tablica[y-1][x-1]!='-' && tablica[y-1][x-1]==tablica[y - 3][x - 3])
    {
    if(tablica[y-2][x-2]!='-')
      {
      bb = false;
      }
    }
      }
     --x;
     --y;
     ++j;
    }
  return bb;
  }


bool Pion(int spr_x, int spr_y, char tablica[][8])
{
  bool cc = true;
  int x = spr_x;
  int y = spr_y;
  int i = 1;
  int j = 1;
  while(y<7 && i<5)
    {
    ++y;
    ++i;
    }
  while(y-4>=0 && j<=5)
    {
    if(tablica[y][x]!='-' && tablica[y][x]==tablica[y - 4][x])
      {
      if(tablica[y-1][x]!='-' && tablica[y-1][x]==tablica[y - 3][x])
    {
    if(tablica[y-2][x]!='-')
      {
      cc = false;
      }
    }
      }
    --y;
    ++j;
    }
  return cc;
  }


bool Poziom(int spr_x, int spr_y, char tablica[][8])
  {
      bool dd = true;
  int x = spr_x;
  int y = spr_y;
  int i = 1;
  int j = 1;
  while(x>0 && i<5)
    {
    --x;
    ++i;
    }
  while(x+4<=7 && j<=5)
    {
    if(tablica[y][x]!='-' && tablica[y][x]==tablica[y][x + 4])
      {
      if(tablica[y][x+1]!='-' && tablica[y][x+1]==tablica[y][x + 3])
      {
    if(tablica[y][x+2]!='-')
      {
      dd = false;
      }
    }
      }
    ++x;
    ++j;
    }
  return dd;
  }


void Inicjalizacja_Tabeli(char tablica[][8])
{
int kolumny, wiersze;
for(wiersze = 0; wiersze < 8; wiersze++)
  {
  for(kolumny = 0; kolumny < 8; kolumny++)
    {
    tablica[wiersze][kolumny] = '-';
    }
  }
}

void Wypisz_Tabele(char tablica[][8])
{
int kolumniste = 0;    //tu cos zmieniono ale nie wiem czy na dobre
for(int wiersze_w = 0; wiersze_w < 8; wiersze_w++)
  {
  for(int kolumny_w = 0; kolumny_w < 8; kolumny_w++)
    {
    printf(" %c",tablica[wiersze_w][kolumny_w]);
    }
  printf("\n");
  }
for(char indeksy = 'a'; kolumniste < 8; ++indeksy, ++kolumniste)
  {
  printf(" ");
  putchar (indeksy);
  }
printf("\n");
}

void Gracz(int aktualny_gracz)
{
printf("%d:\n", aktualny_gracz);
}



int Zmien_Gracza(int aktualny_gracz, int liczba_graczy, int gracz[])
{
if(aktualny_gracz == liczba_graczy)
  {
  aktualny_gracz = gracz[0];
  }
else
  {
  aktualny_gracz = gracz[aktualny_gracz];
  }
return aktualny_gracz;
}


void Wypisz_Zwyciezce(int aktualny_gracz)
{
printf("%d.\n", aktualny_gracz);
}



int Ruch(int spr_x, char tablica[][8], int aktualny_gracz)
{
int polecenie;
bool kontynuuj = true;
Wypisz_Tabele(tablica);
Gracz(aktualny_gracz);
while(kontynuuj && (polecenie=getchar())!=EOF)
    {
    if(polecenie == '\n')
      {
      kontynuuj = true;
      }
    else
    {
    if('a'<=polecenie&&polecenie<='h')
        {
        spr_x = polecenie - 'a';
        kontynuuj = tablica[0][spr_x]=='1'||tablica[0][spr_x]=='2';
        }
    else
        {
        if(polecenie == '=')
            {
            spr_x = -1;
            kontynuuj = false;
            }
        }
    polecenie = getchar();
    if(polecenie!='\n')
        {
        while(polecenie!='\n')
            {
            polecenie = getchar();
            }
        kontynuuj = true;
        }
    }
    if(kontynuuj)
        {
        Wypisz_Tabele(tablica);
        Gracz(aktualny_gracz);
        }
    }
return spr_x;
}

int Ruch2(int spr_y, int spr_x, char tablica[][8], int aktualny_gracz)
{
bool e = false;
for(int kolum = 7; kolum>-1 && e == false; --kolum)
  {
  if(tablica[kolum][spr_x]=='-')
    {
    spr_y = kolum;
    if(aktualny_gracz==1)    //UWAGA TURBO WATPLIWOSCI CO DO TABLICA[SPR_X][KOLUM] - JAK NADPISAĆ TAM 1 LUB 2    tablica[spr_x][kolum] = 'aktualny_gracz';
      {
      tablica[kolum][spr_x] = '1';
      }
    else
      {
      tablica[kolum][spr_x] = '2';
      }
    e = true;
    }
  }
return spr_y;
}


int Sprawdz_Wygrana(int spr_x, int spr_y, int aktualny_gracz, char tablica[][8])
  {
  bool a = Skos_1(spr_x, spr_y, tablica);
  bool b = Skos_2(spr_x, spr_y, tablica);
  bool c = Pion(spr_x, spr_y, tablica);
  bool d = Poziom(spr_x, spr_y, tablica);
  if(a==false||b==false||c==false||d==false)
    {
    return aktualny_gracz;
    }
  else
    {
    return 0;
    }
  }



int main(void)
{
char tablica[8][8];
int zwyciezca = 0;
int spr_x, spr_y;
int liczba_graczy = 2;
int gracz[liczba_graczy];
int aktualny_gracz = 1;
bool gra = true;
for(int i = 0; i<liczba_graczy; ++i)     //zamiast funkcji Inizjalizacja_Graczy()
  {                    //zwracanie tablic nigdy nie wychodzi mi na dobre
  gracz[i] = i + 1;
  }
Inicjalizacja_Tabeli(tablica);
while (gra==true)
  {
  spr_x = -1;
  spr_x = Ruch(spr_x, tablica, aktualny_gracz);
  if(spr_x == -1)
    {
    gra = false;
    }
  else
    {
    spr_y = Ruch2(spr_y, spr_x, tablica, aktualny_gracz);
    zwyciezca = Sprawdz_Wygrana(spr_x, spr_y, aktualny_gracz, tablica);
    if(zwyciezca!=0)
        {
        Wypisz_Tabele(tablica);
        Wypisz_Zwyciezce(aktualny_gracz);
        gra=false;
        }
    aktualny_gracz = Zmien_Gracza(aktualny_gracz, liczba_graczy, gracz);
    }
  }
return 0;
}