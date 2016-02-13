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
void menu_sortowania();
void chodzenie_po_danych();
void modyfikacje();
void menu_wyszukiwania();

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
    void sortowanie_po_wieku();
    void dodaj_rekord();
    void usuwanie_rekordu();
    int usuwanie_rekordu(int do_usuniecia);
    void usun();
    void edycja_albumu();
    void sortowanie_po_imieniu();
    void wyszukaj_imie();
    void wyszukaj_singiel();
    void wyszukaj_po_cenie();
};

Artysci wykonawcy[MAX], pom;

int ile_plyt_kupic( unsigned long int d )
{
    unsigned long int suma = 0;

    suma = d*wykonawcy[rekord].cena;

    return suma;
}

void Artysci::kupno()
{
    unsigned long int ile;

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
/*
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
*/


void Artysci::sortowanie_rosnace_po_singlu()
{
    bool znacznik;;
    int i;
    int nr = 1;
        do {
            znacznik = false;
            for (i = 1; i <= licznik - nr; i++)
                if ( wykonawcy[i].singiel > wykonawcy[i + 1].singiel )
                    {
                        pom = wykonawcy[i];
                        wykonawcy[i] = wykonawcy[i + 1];
                        wykonawcy[i + 1] = pom;
                        znacznik = true;
                    }
                nr++;
        } while (znacznik);
}




void Artysci::sortowanie_po_wieku()
{
    bool znacznik;;
    int i;
    int nr = 1;
        do {
            znacznik = false;
            for (i = 1; i <= licznik - nr; i++)
                if ( wykonawcy[i].wiek > wykonawcy[i + 1].wiek )
                    {
                        pom = wykonawcy[i];
                        wykonawcy[i] = wykonawcy[i + 1];
                        wykonawcy[i + 1] = pom;
                        znacznik = true;
                    }
                nr++;
        } while (znacznik);

}

void Artysci::sortowanie_po_imieniu()
{
    bool znacznik;;
    int i;
    int nr = 1;
        do {
            znacznik = false;
            for (i = 1; i <= licznik - nr; i++)
                if ( wykonawcy[i].imie > wykonawcy[i + 1].imie )
                    {
                        pom = wykonawcy[i];
                        wykonawcy[i] = wykonawcy[i + 1];
                        wykonawcy[i + 1] = pom;
                        znacznik = true;
                    }
                nr++;
        } while (znacznik);

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

void Artysci::dodaj_rekord()
{
    if ( licznik >= MAX )
            {
                cout << " Niestety, baza jest juz pelna!" << endl;
                Sleep(1000);
            } else {

                gotoxy(30, 1);
                cout << " Dodaj album do kolekcji ";
                gotoxy (2, 2);
                cout << "*************************************************************************" << endl;

                gotoxy (26, 5);
                numerNaLisciePrzebojow = licznik + 1;
                cout << "Numer na liscie przebojow: " << numerNaLisciePrzebojow;

                gotoxy(26, 7);
                cout << "Wokalistka/Wokalista: ";
                gotoxy(26, 9);
                cout << "Wpisz 0 - artysta, 1 - artystka";

                gotoxy(48, 7);
                cin >> kobieta_czy_mezczyzna;

                gotoxy (26, 11);
                cout << "Wiek: "; cin >> wiek;
                gotoxy (26, 13);
                cout << "Imie artysty: "; cin >> imie;
                gotoxy (26, 15);
                cout << "Nazwisko artysty: "; cin >> nazwisko;
                gotoxy (26, 17);
                cout << "Nazwa albumu: "; cin >> singiel;
                gotoxy (26, 19);
                cout << "Ilosc sprzedanych plyt w 1szym tygodniu: "; cin >> ile_sprzedanych_plyt;
                gotoxy (26, 21);
                cout << "Cena albumu: "; cin >> cena;
                gotoxy (26, 23);
                cout <<  "Data urodzenia: "; cin >> dataUrodzin;
                gotoxy (26, 25);
                cout << "Miasto: "; cin >> miasto;

                licznik++;
                znacznik = 0;
            }

}

void Artysci::edycja_albumu()
{
        char edit;

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

        gotoxy(48, 1);
        cout << "Edytowac numer [1/0]: "; cin >> edit;
                if ( edit == '1' )
                   {
                        gotoxy( 32, 5 );
                        cin >> numerNaLisciePrzebojow;

                   }

}


int Artysci::usuwanie_rekordu(int do_usuniecia)
{
    int i, j;
    for (i = 0; i < licznik; i++)
    {
        if (wykonawcy[i].numerNaLisciePrzebojow == do_usuniecia)
        {
            for (j = i + 1; j < licznik; j++)
            {
                wykonawcy[j - 1] = wykonawcy[j];
            }
            --licznik;
            return do_usuniecia;
        }
    }
}

void Artysci::usun()
{
    int ktory;
    gotoxy(22, 11);
    cout << "Ktory indeks usunac: "; cin >> ktory;
    getchar();

    cout << usuwanie_rekordu(ktory);
}


void Artysci::wyszukaj_imie()
{
    string szukane_imie;
    bool print_man_or_woman, ustaw;
    int i = 0;

    gotoxy(2, 2);
    cout << "*************************************************************************" << endl;
    gotoxy(16, 24);
    cout << "Wpisz imie wykonawcy, ktorego chcesz wyszukac: " << endl;
    gotoxy (17, 26);
    cout << " > ";
    cin >> szukane_imie;
    czyszczenie();

    do {
        if(szukane_imie == wykonawcy[i].imie)
        {
            ustaw = true;
            if (wykonawcy[i].kobieta_czy_mezczyzna == true)
                        {
                            print_man_or_woman = true;
                        } else {
                            print_man_or_woman = false;
                        }

            gotoxy(5, 13);
            wykonawcy[i].listing_danych(print_man_or_woman);
        }
        i++;

    } while (ustaw == false && i <= licznik );

    if (false)
        cout << "Brak artysty w bazie!";

}


void Artysci::wyszukaj_singiel()
{
    string szukany_singiel;
    bool print_man_or_woman, ustaw;
    int i = 0;

    gotoxy(2, 2);
    cout << "*************************************************************************" << endl;
    gotoxy(16, 24);
    cout << "Wpisz nazwe singla/plyty, ktory chcesz wyszukac: " << endl;
    gotoxy (17, 26);
    cout << " > ";
    cin >> szukany_singiel;
    czyszczenie();

    do {
        if(szukany_singiel == wykonawcy[i].singiel)
        {
            ustaw = true;
            if (wykonawcy[i].kobieta_czy_mezczyzna == true)
                        {
                            print_man_or_woman = true;
                        } else {
                            print_man_or_woman = false;
                        }

            gotoxy(5, 13);
            wykonawcy[i].listing_danych(print_man_or_woman);
        }
        i++;

    } while (ustaw == false && i <= licznik );

    if (false)
        cout << "Brak artysty w bazie!";

}


void Artysci::wyszukaj_po_cenie()
{
    double cenaOd, cenaDo;
    int min, max;
    bool print_man_or_woman, ustaw;
    int i = 0;

    gotoxy(2, 2);
    cout << "*************************************************************************" << endl;
    gotoxy(16, 24);
    cout << "Wpisz cene, od ktorej chcesz wyszukac albumy: " << endl;
    gotoxy (17, 26);
    cout << " > ";
    cin >> cenaOd;

    gotoxy(16, 28);
    cout << "Wpisz cene, do ktorej chcesz wyszukac albumy: " << endl;
    gotoxy (17, 30);
    cout << " > ";
    cin >> cenaDo;
    czyszczenie();

    do {
        if( ( wykonawcy[i].cena >= cenaOd ) && ( wykonawcy[i].cena <= cenaDo ) )
        {
            ustaw = true;
            if (wykonawcy[i].kobieta_czy_mezczyzna == true)
                        {
                            print_man_or_woman = true;
                        } else {
                            print_man_or_woman = false;
                        }


            gotoxy(5, 13);
            wykonawcy[i].listing_danych(print_man_or_woman);
            getch();
        }
        i++;
        czyszczenie();

        min = cenaOd;
        max = cenaDo;

        if ( wykonawcy[i].cena <= cenaDo )
            {
             if (wykonawcy[i].kobieta_czy_mezczyzna == true)
                        {
                            print_man_or_woman = true;
                        } else {
                            print_man_or_woman = false;
                        }


            gotoxy(5, 13);
            wykonawcy[i].listing_danych(print_man_or_woman);
            getch();
            i++;
            }

    } while (ustaw == false && i <= licznik );

    if (false)
        cout << "Brak albumow w tej cenie w bazie!";

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
        cout << "Baza nie zostala zaladowana!" << endl;
        znacznik = 1;
    } else {
        wykonawcy[rekord].listing_danych(k);
    }

    char znak;

    gotoxy(5, 22);
    cout << "*************************************************************************" << endl;
    gotoxy(5, 23);
    cout << "4. Poprzedni wykonawca" << endl;
    gotoxy(52, 23);
    cout << "6. Nastepny wykonawca" << endl;
    gotoxy(34 ,24);
    cout << "2. Sprzedaz" << endl;
    gotoxy(5, 26);
    cout << "3. Podlicz dochod artysty" << endl;
    gotoxy(52, 26);
    cout << "9. Dokonaj modyfikacji bazy" << endl;
    gotoxy(34 ,28);
    cout << "5. Edytuj album" << endl;
    gotoxy(32, 1);
    cout << "8. Menu glowne";
    cout << endl << " > ";

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
            //rekord = licznik + 1;
        };

        wykonawcy[rekord].listing_danych(k);
        chodzenie_po_danych(k);

        break;


    case '5':
        {
        wykonawcy[licznik].edycja_albumu();
        chodzenie_po_danych(k);
        }
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

    case '9':
        modyfikacje();

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

void modyfikacje()
{
    char wybor;
    czyszczenie();

    gotoxy(24, 8);
    cout << "0. Powrot do menu glownego" << endl;
    gotoxy(24, 10);
    cout << "1. Dodaj pozycje do bazy" << endl;
    gotoxy(24, 12);
    cout << "2. Usun pozycje do bazy" << endl;


    gotoxy (30, 18);
    cout << "Twoj wybor to: ";
    gotoxy (30, 20);
    cout << " > ";
    cin >> wybor;
    getchar();

    switch(wybor)
    {
        case '0':
            menu();

        case '1':
            {
                czyszczenie();
                wykonawcy[licznik].dodaj_rekord();
                gotoxy(26, 27);
                zapisDoPliku();
                rekord++;
                Sleep(1000);
                modyfikacje();
            }

        case '2':
            {
                czyszczenie();
                wykonawcy[licznik].usun();
                gotoxy(26, 27);
                zapisDoPliku();
                rekord++;
                Sleep(1000);
                modyfikacje();

            }

        default:
            {
                cout << "Blad! Wybierz cyfre sposrod podanych!";
                Sleep(1000);
                modyfikacje();
            }
    }


}

void menu()
{
    char wybor;
    int deal;
    czyszczenie();

    gotoxy(26, 2);
    cout << "Baza plyt wydanych w latach 2000-2015" << endl;
    gotoxy(3, 3);
    cout << "*************************************************************************" << endl;
    gotoxy(24, 7);
    cout << "1. Spis plyt - wyswietlanie " << endl;
    gotoxy(24, 10);
    cout << "2. Metody sortowania danych" << endl;
    gotoxy(24, 13);
    cout << "3. Metody wyszukiwania danych" << endl;
    gotoxy(24, 16);
    cout << "6. Wyjdz z programu " << endl;

    gotoxy (32, 20);
    cout << "Twoj wybor to: ";
    gotoxy (32, 22);
    cout << " > ";
    cin >> wybor;
    getchar();

    switch(wybor)
    {
        case '1':
            {
            czyszczenie();

            gotoxy(19, 2);
            cout << "|";
            gotoxy(19, 3);
            cout << "|";
            gotoxy(19, 4);
            cout << "|";
            gotoxy(19, 14);
            cout << "|";
            gotoxy(19, 15);
            cout << "|";
            gotoxy(19, 16);
            cout << "|";

            gotoxy(60, 2);
            cout << "|";
            gotoxy(60, 3);
            cout << "|";
            gotoxy(60, 4);
            cout << "|";
            gotoxy(60, 14);
            cout << "|";
            gotoxy(60, 15);
            cout << "|";
            gotoxy(60, 16);
            cout << "|";

            gotoxy(20, 2);
            cout << "----------------------------------------";
            gotoxy(22, 3);
            cout << "Wyswietlic artystki czy artystow ? ";
            gotoxy(20, 4);
            cout << "----------------------------------------";

            gotoxy(22, 7);
            cout << "Wybierz 1, by wyswietlic arystki, ";
            gotoxy(22, 10);
            cout <<"Wybierz 0, by wyswietlic arystow.";


            gotoxy(20, 14);
            cout << "----------------------------------------";
            gotoxy(22, 15);
            cout << "wcisnij 8, by powrocic do menu";
            gotoxy(20, 16);
            cout << "----------------------------------------";

            do {

            gotoxy(22, 22);
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
                gotoxy(22, 18);
                cout << "Wybierz 1 lub 0!" << endl;
            }

            } while ( deal >=2 );

            }


        break;

        case '2':
            menu_sortowania();

        case '3':
            czyszczenie();
            menu_wyszukiwania();

        case '6':
            gotoxy(0, 24);
            zapisDoPliku();
            koniec();
        break;

        default:
            {
                gotoxy(30, 20);
                cout<< "Wybierz jeszcze raz!" << endl;
                Sleep(1000);
                menu();

            }
    }

}

void menu_wyszukiwania()
{
    char wybor;
    czyszczenie();

    gotoxy(23, 2);
    cout << "Wybierz metode wyszukiwania" << endl;
    gotoxy(3, 3);
    cout << "*************************************************************************" << endl;
    gotoxy(22, 6);
    cout << "1. Wyszukaj wedlug imienia" << endl;
    gotoxy(22, 9);
    cout << "2. Wyszukaj wedlug singla/nazwy plyty" << endl;
    gotoxy(22, 12);
    cout << "3. Wyszukaj wedlug ceny albumu" << endl;
    gotoxy(22, 15);
    cout << "4. Wroc do menu glownego" << endl;

    gotoxy (32, 19);
    cout << "Twoj wybor to: ";
    gotoxy (32, 21);
    cout << " > ";
    cin >> wybor;
    getchar();

    switch(wybor)
    {
        case '1':
                czyszczenie();
                wykonawcy[rekord].wyszukaj_imie();

                getchar();
                getchar();
                menu_wyszukiwania();

        case '2':
                czyszczenie();
                wykonawcy[rekord].wyszukaj_singiel();
                getchar();
                getchar();
                menu_wyszukiwania();

        case '3':
                czyszczenie();
                wykonawcy[rekord].wyszukaj_po_cenie();
                getchar();
                getchar();
                menu_wyszukiwania();

        case '4':
            menu();

        default:
            {
                gotoxy(30, 19);
                cout<< "Wybierz jeszcze raz!" << endl;
                Sleep(1000);
                menu_wyszukiwania();

            }
    }
}


void menu_sortowania()
{
    char wybor;
    czyszczenie();

    gotoxy(25, 2);
    cout << "Wybierz metode sortowania" << endl;
    gotoxy(3, 3);
    cout << "*************************************************************************" << endl;
    gotoxy(22, 5);
    cout << "1. Posortuj rosnaco wedlug ceny" << endl;
    gotoxy(22, 8);
    cout << "2. Posortuj rosnaco wedlug singla" << endl;
    gotoxy(22, 11);
    cout << "3. Posortuj rosnaco wedlug ilosci sprzedanych plyt" << endl;
    gotoxy(22, 14);
    cout << "4. Posortuj rosnaca wedlug wieku" << endl;
    gotoxy(22, 17);
    cout << "5. Posortuj rosnaca wedlug imienia" << endl;
    gotoxy(22, 20);
    cout << "6. Wroc do menu glownego" << endl;

    gotoxy (32, 24);
    cout << "Twoj wybor to: ";
    gotoxy (32, 26);
    cout << " > ";
    cin >> wybor;
    getchar();

    switch(wybor)
    {
        case '1':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "wedlug ceny albumu, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_cenowe_rosnace();
                    menu();

        case '2':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "wedlug nazwy singla, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_rosnace_po_singlu();
                    menu();

        case '3':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "wedlug ilosci sprzedanych krazkow, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_po_ilosci_plyt();
                    menu();

        case '4':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "wedlug wieku, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_po_wieku();
                    menu();

        case '5':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "wedlug imienia, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_po_imieniu();
                    menu();

        case '6':
            menu();

        default:
            {
                gotoxy(30, 24);
                cout<< "Wybierz jeszcze raz!" << endl;
                Sleep(1000);
                menu_sortowania();

            }
    }
}

void start()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),279); //910 //253 //233 - zolty

}

void koniec()
{
    gotoxy(20, 26);
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
