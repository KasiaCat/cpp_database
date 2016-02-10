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
};

Artysci wykonawcy[MAX];

int ile_plyt_kupic( int d )
{
    return d*wykonawcy[rekord].cena;
}

void Artysci::kupno()
{
    int ile;

    cout << "Ile plyt kupic?" << endl;
    cout << " > ";
    cin >> ile;
    cout << "Rachunek wynosi:  " << ile_plyt_kupic(ile) << "$";
}

void zarobki_artysty()
{
    wykonawcy[rekord].ile_sprzedanych_plyt * wykonawcy[rekord].cena;
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
    cout << "6. Nastepny wykonawca" << endl;
    cout << "4. Poprzedni wykonawca" << endl;
    cout << "2. Sprzedaz" << endl;
    cout << "8. Menu glowne" << endl;
    cout << " > ";

    znak = getch();
    switch(znak)
    {

     case '2':
        czyszczenie();
        wykonawcy[rekord].kupno();
        system("PAUSE");

        rekord++;
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
        system("Pause");
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
    gotoxy (24, 8);
    cout << "3. Wyjdz z programu " << endl;

    gotoxy (30, 12);
    cout << "Twoj wybor to: ";
    gotoxy (30, 14);
    cout << " > ";
    cin >> wybor;

    switch(wybor)
    {
        case '1':
            {
            czyszczenie();
            cout << endl << "Wyswietlic artystki czy artystow ? " << endl << endl;
            cout << "Wybierz 1, by wyswietlic arystki, albo wybierz 0, by wyswietlic arystow.";
            cout << endl << " > ";

            cin >> deal;
            if( deal == 1)
                chodzenie_po_danych(1);
            else if( deal == 0 )
                chodzenie_po_danych(0);
            else
            {
                cout << "Musisz wybrac 0 albo 1!";
                menu();
            }

            }


        break;
        case '3':
            zapisDoPliku();
            koniec();
        break;

        default:
            {
                cout<< "Wybierz jeszcze raz!" << endl;
                system("Pause");
                menu();
            }
    }

}

void start()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),233); //910 //253

}

void koniec()
{
    cout << endl << "Do widzenia, nacisnij Enter by zamknac baze danych";
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
