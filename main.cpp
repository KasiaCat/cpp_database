#include <iostream>
#include <fstream> // obsluga plikow
#include <string> // obsluga string
#include <cstdlib> // konwersje string na int
#include <conio.h> // getch();
#include <windows.h> //gotoxy

#define MAX 20
#define DB_FILENAME "plik.txt"

using namespace std;

void gotoxy(int x, int y)
{
    COORD cord;
    cord.X = x;
    cord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cord);
}

int licznik = 0; // ilosc wczytanych rekordow
int rekord = 0;
int znacznik = 0;
void start();
void koniec();
void odczytPliku();
void zapisDoPliku();
void czyszczenie();
void menu();
void chodzenie_po_danych();

class Artysci {
public:
    int numerNaLisciePrzebojow;
    bool kobieta_czy_mezczyzna;
    int wiek;
    string imie;
    string nazwisko;
    string singiel;
    unsigned long int ile_sprzedanych_plyt;
    double  cena;
    string dataUrodzin;
    string miasto;
    void listing_danych(int k);
    void kupno();
    void zarobki();
    void sortowanie_cenowe_rosnace();
    void sortowanie_rosnace_po_singlu();
    void sortowanie_po_ilosci_plyt();
};

Artysci wykonawcy[MAX];

int ile_plyt_kupic( int d )
{
    unsigned long int suma = 0;

    suma = d*wykonawcy[rekord].cena;

    return suma;
}

void Artysci::kupno()
{
    int ile;

    cout << "Ile plyt kupic?" << endl;
    cout << " > ";
    cin >> ile;
    cout << "Rachunek wynosi:  " << ile_plyt_kupic(ile) << "$";
}

int zarobki_artysty()
{
    unsigned long long int suma = 0;

    suma =  wykonawcy[rekord].ile_sprzedanych_plyt * wykonawcy[rekord].cena;

    return suma;
}

void Artysci::zarobki()
{
    cout << "Dochod artysty: " << zarobki_artysty() << "$";
}

void Artysci::sortowanie_cenowe_rosnace()
{
    for (int nr = 2; nr <= licznik; nr++)
      {
          wykonawcy[0] = wykonawcy[nr];
          int previous = nr - 1;

          while ( wykonawcy[previous].cena > wykonawcy[0].cena )
            {
              wykonawcy[previous + 1] = wykonawcy[previous];
              previous--;
            }
          wykonawcy[previous + 1] = wykonawcy[0];
      }

}


void Artysci::sortowanie_po_ilosci_plyt()
{
    for (int nr = 2; nr <= licznik; nr++)
      {
          wykonawcy[0] = wykonawcy[nr];
          int previous = nr - 1;

          while ( wykonawcy[previous].ile_sprzedanych_plyt > wykonawcy[0].ile_sprzedanych_plyt )
            {
              wykonawcy[previous + 1] = wykonawcy[previous];
              previous--;
            }
          wykonawcy[previous + 1] = wykonawcy[0];
      }

}

void Artysci::sortowanie_rosnace_po_singlu()
{
    for (int nr = 2; nr <= licznik; nr++)
      {
          wykonawcy[0] = wykonawcy[nr];
          int previous = nr - 1;

          while ( wykonawcy[previous].singiel > wykonawcy[0].singiel )
            {
              wykonawcy[previous + 1] = wykonawcy[previous];
              previous--;
            }
          wykonawcy[previous + 1] = wykonawcy[0];
      }

}


void Artysci::listing_danych(int k)
{
    if (kobieta_czy_mezczyzna == k )
    {
        gotoxy (5, 3);
        cout << "*************************************************************************" << endl;
        gotoxy (5, 5);
        cout << "Numer na liscie przebojow: " << numerNaLisciePrzebojow << endl;
        gotoxy (5, 7);
        cout << "Wiek: " << wiek << endl;
        gotoxy (5, 9);
        cout << "Imie artysty: " << imie << endl;
        gotoxy (5, 11);
        cout << "Nazwisko artysty: " << nazwisko << endl;
        gotoxy (5, 13);
        cout << "Nazwa albumu: " << singiel << endl;
        gotoxy (5, 15);
        cout << "Ilosc sprzedanych plyt w 1szym tygodniu: " << ile_sprzedanych_plyt << endl;
        gotoxy (5, 17);
        cout << "Cena albumu: " << cena << endl;
        gotoxy (5, 19);
        cout <<  "Data urodzenia: " << dataUrodzin << endl;
        gotoxy (5, 21);
        cout << "Miasto: " << miasto << endl;

    } else {
        gotoxy (58, 35);
        cout << "Nastepny artysta --> " << endl;
    }
}

void odczytPliku()
{
    string linia;
    int znak = 0;
    ifstream plik;

    plik.open("plik.txt");

    while (plik.good())
    {

        getline(plik, linia);
        wykonawcy[znak].numerNaLisciePrzebojow = atoi(linia.c_str());

        getline(plik, linia);
        wykonawcy[znak].kobieta_czy_mezczyzna = atoi(linia.c_str());

        getline(plik, linia);
        wykonawcy[znak].wiek = atoi(linia.c_str()); //zamiana na string

        getline(plik, wykonawcy[znak].imie);
        getline(plik, wykonawcy[znak].nazwisko);
        getline(plik, wykonawcy[znak].singiel);

        getline(plik, linia);
        wykonawcy[znak].ile_sprzedanych_plyt = atoi(linia.c_str());
        //getline(plik, wykonawcy[znak].ile_sprzedanych_plyt);

        getline(plik, linia);
        wykonawcy[znak].cena = atoi(linia.c_str());

        getline(plik, wykonawcy[znak].dataUrodzin);
        getline(plik, wykonawcy[znak].miasto);
        znak++;
        licznik = znak - 1;

    }
        plik.close();

}

void zapisDoPliku()
{
    fstream plik;

    plik.open("plik.txt", ios::out);  //ios::app
    cout << "Zapis w trakcie" << endl;

    for (int i = 0; i <= licznik; i++)
    {
        if (wykonawcy[i].numerNaLisciePrzebojow != 0)
        {
            plik << wykonawcy[i].numerNaLisciePrzebojow << endl;
            plik << wykonawcy[i].kobieta_czy_mezczyzna << endl;
            plik << wykonawcy[i].wiek << endl;
            plik << wykonawcy[i].imie << endl;
            plik << wykonawcy[i].nazwisko << endl;
            plik << wykonawcy[i].singiel << endl;
            plik << wykonawcy[i].ile_sprzedanych_plyt << endl;
            plik << wykonawcy[i].cena << endl;
            plik << wykonawcy[i].dataUrodzin << endl;
            plik << wykonawcy[i].miasto << endl;
        }
    }

    plik.close();

}

void chodzenie_po_danych(int k)
{
    czyszczenie();

    if (wykonawcy[rekord].numerNaLisciePrzebojow == 0)
    {
        cout << "Brak numeru zerowego, baza nie zostala zaladowana!" << endl;
        znacznik = 1;
    } else {
        wykonawcy[rekord].listing_danych(k);
    }

    char znak;
    gotoxy(5, 23);
    cout << "4. Poprzedni wykonawca" << endl;
    gotoxy(52, 23);
    cout << "6. Nastepny wykonawca" << endl;
    gotoxy(34 ,24);
    cout << "2. Sprzedaz" << endl;
    gotoxy(5, 26);
    cout << "3. Podlicz dochod artysty" << endl;
    gotoxy(32, 1);
    cout << "8. Menu glowne" << endl;
    cout << " > ";

    znak = getch();
    switch(znak)
    {

     case '2':
        czyszczenie();
        cout << "--------------------------------------------------------------------------------" << endl;
        wykonawcy[rekord].kupno();
        cout << endl << "--------------------------------------------------------------------------------";
        Sleep(2000);

        wykonawcy[rekord].listing_danych(k);
        chodzenie_po_danych(k);

     case '3':
        czyszczenie();
        cout << "--------------------------------------------------------------------------------" << endl;
        wykonawcy[rekord].zarobki();
        cout << endl << "--------------------------------------------------------------------------------";

        Sleep(2000);

        wykonawcy[rekord].listing_danych(k);
        chodzenie_po_danych(k);


     case '4':
        czyszczenie();
        rekord--;
        if ( (rekord >= licznik) || (rekord < 0) )
        {
            rekord = 0;
        };

        wykonawcy[rekord].listing_danych(k);
        chodzenie_po_danych(k);

        break;


    case '6':
        czyszczenie();
        rekord++;
        if ( (rekord >= licznik) || (rekord < 0) )
        {
            rekord = licznik - 1;
        };
        wykonawcy[rekord].listing_danych(k);
        chodzenie_po_danych(k);

        break;

    case '8':
        menu();

    default:
        {
        cout << "Blad! Wybierz cyfre sposrod podanych!";
        Sleep(1000);
        chodzenie_po_danych(k);
        }

    }

}

void czyszczenie()
{
    system("cls");
}

void menu()
{
    char wybor;
    int deal;
    czyszczenie();

    gotoxy (24, 2);
    cout << "Menu" << endl;
    gotoxy (24, 4);
    cout << "Baza plyt wydanych w latach 2000-2015" << endl;
    gotoxy (24, 6);
    cout << "1. Spis plyt - wyswietlanie " << endl;
    gotoxy(24, 8);
    cout << "2. Posortuj rosnaco wedlug ceny" << endl;
    gotoxy(24, 10);
    cout << "3. Posortuj rosnaco wedlug singla" << endl;
    gotoxy(24, 12);
    cout << "4. Posortuj rosnaco wedlug ilosci sprzedanych plyt" << endl;
    gotoxy (24, 14);
    cout << "5. Wyjdz z programu " << endl;

    gotoxy (30, 16);
    cout << "Twoj wybor to: ";
    gotoxy (30, 18);
    cout << " > ";
    cin >> wybor;
    getchar();

    switch(wybor)
    {
        case '1':
            {
            czyszczenie();
            gotoxy(22, 5);
            cout << "Wyswietlic artystki czy artystow ? " << endl << endl;
            gotoxy(22, 7);
            cout << "Wybierz 1, by wyswietlic arystki, ";
            gotoxy(22, 9);
            cout <<"Wybierz 0, by wyswietlic arystow.";
            gotoxy(22, 11);
            cout << "wcisnij 8, by powrocic do menu";

            do {

            gotoxy(22, 18);
            cout <<" > ";
            cin >> deal;
            getchar();

            if( deal == 1)
                chodzenie_po_danych(1);
            else if( deal == 0 )
                chodzenie_po_danych(0);
            else if (deal == 8)
                menu();

            else {
                gotoxy(22, 16);
                cout << "Wybierz 1 lub 0!" << endl;
            }

            } while ( deal >=2 );

            }


        break;

        case '2':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "wedlug ceny albumu, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_cenowe_rosnace();
                    menu();

        case '3':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "wedlug nazwy singla, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_rosnace_po_singlu();
                    menu();

        case '4':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "wedlug ilosci sprzedanych krazkow, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_po_ilosci_plyt();
                    menu();

        case '5':
            zapisDoPliku();
            koniec();
        break;

        default:
            {
                gotoxy(30, 18);
                cout<< "Wybierz jeszcze raz!" << endl;
                Sleep(1000);
                menu();

            }
    }

}

void start()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),279); //910 //253 //233 - zolty

}

void koniec()
{
    cout << endl << "Do widzenia, nacisnij Enter by zamknac baze danych" << endl;
    exit(0);
    cin.ignore();
    cin.get();
}


int main()
{
    start();

    odczytPliku();
    menu();
    zapisDoPliku();
    koniec();

    return 0;
}
