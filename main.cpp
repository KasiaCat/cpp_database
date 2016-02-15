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
void menu_wyszukiwania();
void Menu_woman_or_man();
void chodzenie_po_danych();
void modyfikacje();


class Artysci {
private:
    bool yes, znacznik;
    int i, j, wybor;
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
    void sortowanie_po_imieniu();
    void sortowanie_cenowe_rosnace();
    void sortowanie_rosnace_po_singlu();
    void sortowanie_rosnace_po_wieku();
    void sortowanie_rosnace_po_numerze();
    void sortowanie_po_ilosci_plyt();
    void sortowanie_malejace_po_numerze();
    void sortowanie_malejace_po_wieku();
    void dodaj_rekord();
    int usuwanie_rekordu(int do_usuniecia);
    void usun_jeden();
    int usuwanie_wielu(int pierwszy, int drugi, int trzeci);
    void usun_wiele();
    void edycja_albumu();
    void wyszukaj_imie();
    void wyszukaj_singiel();
    void wyszukaj_po_cenie();
    void wyszukaj_po_imieniu_i_nazwisku();
    int ile_plyt_kupic( unsigned long int d );
};

Artysci wykonawcy[MAX], pom;

int Artysci::ile_plyt_kupic( unsigned long int d )
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

void Artysci::zarobki()
{
    unsigned long long int suma = 0;

    suma =  wykonawcy[rekord].ile_sprzedanych_plyt * wykonawcy[rekord].cena;

    cout << "Dochod artysty: " << suma << "$";
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
    //bool znacznik;
    //int i;
    int nr = 1;
        do {
            znacznik = false;
            for (i = 0; i <= licznik - nr; i++)
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


void Artysci::sortowanie_rosnace_po_wieku()
{
    //bool znacznik;
    //int i;
    int nr = 1;
        do {
            znacznik = false;
            for (i = 0; i <= licznik - nr; i++)
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

void Artysci::sortowanie_malejace_po_wieku()
{
    //bool znacznik;
    //int i;
    int nr = 1;
        do {
            znacznik = false;
            for (i = 0; i <= licznik - nr; i++)
                if ( wykonawcy[i].wiek < wykonawcy[i + 1].wiek )
                    {
                        pom = wykonawcy[i];
                        wykonawcy[i] = wykonawcy[i + 1];
                        wykonawcy[i + 1] = pom;
                        znacznik = true;
                    }
                nr++;
        } while (znacznik);

}

void Artysci::sortowanie_rosnace_po_numerze()
{
    //bool znacznik;
    //int i;
    int nr = 1;
        do {
            znacznik = false;
            for (i = 0; i <= licznik - nr; i++)
                if ( wykonawcy[i].numerNaLisciePrzebojow > wykonawcy[i + 1].numerNaLisciePrzebojow )
                    {
                        pom = wykonawcy[i];
                        wykonawcy[i] = wykonawcy[i + 1];
                        wykonawcy[i + 1] = pom;
                        znacznik = true;
                    }
                nr++;
        } while (znacznik);

}

void Artysci::sortowanie_malejace_po_numerze()
{
    //bool znacznik;
    //int i;
    int nr = 1;
        do {
            znacznik = false;
            for (i = 0; i <= licznik - nr; i++)
                if ( wykonawcy[i].numerNaLisciePrzebojow < wykonawcy[i + 1].numerNaLisciePrzebojow )
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
    //bool znacznik;
    //int i;
    int nr = 1;
        do {
            znacznik = false;
            for (i = 0; i <= licznik - nr; i++)
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
        //int wybor;

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

        gotoxy(26, 1);
        cout << "Edytuj wiek [1 - edytuj, 0 - nie]: "; /*wybor = getch();*/ cin >> wybor;
                if ( wybor == 1 )
                   {
                        gotoxy( 20, 7 );
                        cout << " > ";
                        cin >> wiek;

                   }
        gotoxy(26, 1);
        cout << "Edytuj imie [1 - edytuj, 0 - nie]: "; cin >> wybor;
                if ( wybor == 1 )
                   {
                        gotoxy( 28, 9 );
                        cout << " > ";
                        cin >> imie;

                   }
        gotoxy(26, 1);
        cout << "Edytuj nazwisko [1 - edytuj, 0 - nie]: "; cin >> wybor;
                if ( wybor == 1 )
                   {
                        gotoxy( 26, 11 );
                        cout << " > ";
                        cin >> nazwisko;

                   }
        gotoxy(26, 1);
        cout << "Edytuj singiel [1 - edytuj, 0 - nie]: "; cin >> wybor;
                if ( wybor == 1 )
                   {
                        gotoxy( 26, 13 );
                        cout << " > ";
                        cin >> singiel;

                   }

        gotoxy(26, 1);
        cout << "Edytuj ilosc plyt [1 - edytuj, 0 - nie]:   "; cin >> wybor;
                if ( wybor == 1 )
                   {
                        gotoxy( 49, 15 );
                        cout << " > ";
                        cin >> ile_sprzedanych_plyt;

                   }

        gotoxy(26, 1);
        cout << "Edytuj cene [1 - edytuj, 0 - nie]:        "; cin >> wybor;
                if ( wybor == 1 )
                   {
                        gotoxy( 30, 17 );
                        cout << " > ";
                        cin >> cena;

                   }

        gotoxy(26, 1);
        cout << "Edytuj date urodzenia [1 - edytuj, 0 - nie]:     "; cin >> wybor;
                if ( wybor == 1 )
                   {
                        gotoxy( 36, 19 );
                        cout << " > ";
                        cin >> dataUrodzin;

                   }

        gotoxy(26, 1);
        cout << "Edytuj nazwe miasta [1 - edytuj, 0 - nie]:    "; cin >> wybor;
                if ( wybor == 1 )
                   {
                        gotoxy( 36, 21 );
                        cout << " > ";
                        cin >> miasto;

                   }

}


int Artysci::usuwanie_rekordu(int do_usuniecia)
{
    //int i, j;
    //bool yes;
    for (i = 0; i < licznik; i++)
    {
        if (wykonawcy[i].numerNaLisciePrzebojow == do_usuniecia)
        {
            for (j = i + 1; j < licznik; j++)
            {
                wykonawcy[j - 1] = wykonawcy[j];
                yes = true;
                if (yes == false)
                {
                     wykonawcy[j - 1] = wykonawcy[j - 2];
                }
            }
            --licznik;
            return do_usuniecia;
        }
    }
}

void Artysci::usun_jeden()
{
    int ktory;
    gotoxy(22, 11);
    cout << "Ktory indeks usunac: "; cin >> ktory;
    getchar();

    cout << usuwanie_rekordu(ktory);
}

int Artysci::usuwanie_wielu(int jeden, int dwa, int trzy)
{
    int i, j;
    for (i = 0; i < licznik; i++)
    {
        if ( ( wykonawcy[i].numerNaLisciePrzebojow == jeden ) || ( wykonawcy[i].numerNaLisciePrzebojow == dwa )
            || ( wykonawcy[i].numerNaLisciePrzebojow == trzy ))
                {

                    for (j = i + 1; j < licznik; j++)
                    {
                        wykonawcy[j - 1] = wykonawcy[j];
                        wykonawcy[j] = wykonawcy[j + 1];
                        wykonawcy[j + 1] = wykonawcy[j + 2];

                    }
                        j++;
                        --licznik;
                }

    }
    return 0;
}


void Artysci::usun_wiele()
{
    int pierwszy, drugi, trzeci;
    gotoxy(15, 13);
    cout << "Ktore 3 elementy usunac(wybierz numer na liscie przebojow): " << endl;
    gotoxy(15, 15);
    cout << " > ";
    cin >> pierwszy;
    getchar();
    gotoxy(15, 16);
    cout << " > ";
    cin >> drugi;
    getchar();
    gotoxy(15, 17);
    cout << " > ";
    cin >> trzeci;
    getchar();

    cout << usuwanie_wielu(pierwszy, drugi, trzeci);
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
            ustaw = 1;
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

        } while ( i <= licznik );

    if (i > licznik && ustaw != 1)
        cout << "Brak artysty o tym imieniu w bazie!";
}


void Artysci::wyszukaj_po_imieniu_i_nazwisku()
{
    string szukaneImie, szukaneNazwisko;
    bool print_man_or_woman, ustaw;
    int i = 0;

    gotoxy(2, 2);
    cout << "*************************************************************************" << endl;
    gotoxy(16, 24);
    cout << "Wpisz Imie: " << endl;
    gotoxy (17, 26);
    cout << " > ";
    cin >> szukaneImie;

    gotoxy(16, 28);
    cout << "Wpisz nazwisko: " << endl;
    gotoxy (17, 30);
    cout << " > ";
    cin >> szukaneNazwisko;
    czyszczenie();

    do {
        if( ( szukaneImie == wykonawcy[i].imie ) && ( szukaneNazwisko == wykonawcy[i].nazwisko ) )
        {
            ustaw = 1;
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

    } while (ustaw !=1 && i <= licznik );

    if (i > licznik)
        cout << "Brak wykonawcy w bazie!";

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
            ustaw = 1;
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

     } while ( i <= licznik );

    if (i > licznik && ustaw != 1)
        cout << "Brak artysty o tym imieniu w bazie!";
}


void Artysci::wyszukaj_po_cenie()
{
    double cenaOd, cenaDo;
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
            ustaw = 1;
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

    } while ( i <= licznik );

    if (i > licznik && ustaw != 1)
        cout << "Brak albumu w tej cenie w bazie!";

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

    int znak;

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
        }
        wykonawcy[rekord].listing_danych(k);
        chodzenie_po_danych(k);

        break;


    case '5':
        {
        czyszczenie();
        wykonawcy[rekord].edycja_albumu();
        chodzenie_po_danych(k);
        }
        break;

    case '6':
        czyszczenie();
        rekord++;
        if ( (rekord >= licznik) || (rekord < 0) )
        {
            rekord = licznik - 1;
        }
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
    int wybor;
    czyszczenie();

        gotoxy(15, 4); cout << "|"; gotoxy(15, 5); cout << "|"; gotoxy(15, 6); cout << "|";
        gotoxy(15, 7); cout << "|"; gotoxy(15, 8); cout << "|"; gotoxy(15, 9); cout << "|";
        gotoxy(15, 10); cout << "|"; gotoxy(15, 11); cout << "|";
        gotoxy(15, 12); cout << "|"; gotoxy(15, 13); cout << "|"; gotoxy(15, 14); cout << "|";
        gotoxy(15, 15); cout << "|"; gotoxy(15, 16); cout << "|"; gotoxy(15, 17); cout << "|";
        gotoxy(15, 18); cout << "|"; gotoxy(15, 19); cout << "|"; gotoxy(15, 20); cout << "|";

        gotoxy(59, 4); cout << "|"; gotoxy(59, 5); cout << "|"; gotoxy(59, 6); cout << "|";
        gotoxy(59, 7); cout << "|"; gotoxy(59, 8); cout << "|"; gotoxy(59, 9); cout << "|";
        gotoxy(59, 10); cout << "|"; gotoxy(59, 11); cout << "|"; gotoxy(59, 12); cout << "|";
        gotoxy(59, 13); cout << "|"; gotoxy(59, 14); cout << "|"; gotoxy(59, 15); cout << "|";
        gotoxy(59, 16); cout << "|"; gotoxy(59, 17); cout << "|"; gotoxy(59, 18); cout << "|";
        gotoxy(59, 19); cout << "|"; gotoxy(59, 20); cout << "|";

    gotoxy(15, 4);
    cout << "---------------------------------------------";
    gotoxy(24, 8);
    cout << "0. Powrot do menu glownego" << endl;
    gotoxy(24, 11);
    cout << "1. Dodaj pozycje do bazy" << endl;
    gotoxy(24, 14);
    cout << "2. Usun pozycje z bazy" << endl;
    gotoxy(24, 17);
    cout << "3. Usun 3 pozycje z bazy" << endl;
    gotoxy(15, 20);
    cout << "---------------------------------------------";


    gotoxy (30, 23);
    cout << "Twoj wybor to: ";
    gotoxy (30, 25);
    cout << " > ";
    wybor = getch();

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
                wykonawcy[licznik].usun_jeden();
                gotoxy(26, 27);
                zapisDoPliku();
                rekord++;
                Sleep(1000);
                modyfikacje();

            }

        case '3':
            {
                czyszczenie();
                wykonawcy[licznik].usun_wiele();
                gotoxy(26, 27);
                zapisDoPliku();
                rekord++;
                Sleep(1000);
                modyfikacje();

            }


        default:
            {
                gotoxy(30, 23);
                cout << "Blad! Wybierz cyfre sposrod podanych!";
                Sleep(1000);
                modyfikacje();
            }
    }


}

void menu()
{
    int wybor;
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
    wybor = getch();

    switch(wybor)
    {
        case '1':
            czyszczenie();
            Menu_woman_or_man();

        case '2':
            menu_sortowania();

        case '3':
            czyszczenie();
            menu_wyszukiwania();

        case '6':
            gotoxy(0, 24);
            zapisDoPliku();
            koniec();

        default:
            {
                gotoxy(30, 20);
                cout << "Wybierz jeszcze raz!" << endl;
                Sleep(1000);
                menu();

            }
    }

}

void Menu_woman_or_man()
{
    int deal;
    czyszczenie();

    gotoxy(15, 3); cout << "|"; gotoxy(15, 4); cout << "|"; gotoxy(15, 5); cout << "|";
    gotoxy(15, 6); cout << "|"; gotoxy(15, 7); cout << "|"; gotoxy(15, 8); cout << "|";
    gotoxy(15, 15); cout << "|"; gotoxy(15, 16); cout << "|"; gotoxy(15, 17); cout << "|";
    gotoxy(15, 18); cout << "|"; gotoxy(15, 19); cout << "|"; gotoxy(15, 20); cout << "|";

    gotoxy(59, 3); cout << "|"; gotoxy(59, 4); cout << "|"; gotoxy(59, 5); cout << "|";
    gotoxy(59, 6); cout << "|"; gotoxy(59, 7); cout << "|"; gotoxy(59, 8); cout << "|";
    gotoxy(59, 15); cout << "|"; gotoxy(59, 16); cout << "|"; gotoxy(59, 17); cout << "|";
    gotoxy(59, 18); cout << "|"; gotoxy(59, 19); cout << "|"; gotoxy(59, 20); cout << "|";

    gotoxy(15, 3);
    cout << "---------------------------------------------";
    gotoxy(20, 5);
    cout << "Wyswietlic artystki czy artystow ? ";
    gotoxy(15, 8);
    cout << "---------------------------------------------";

    gotoxy(28, 11);
    cout <<"0. Wyswietl arystow";
    gotoxy(28, 13);
    cout <<"1. Wyswietl arystki";

    gotoxy(15, 15);
    cout << "---------------------------------------------";
    gotoxy(28, 18);
    cout << "8. Powrot do menu";
    gotoxy(15, 20);
    cout << "---------------------------------------------";

    gotoxy(22, 25);
    cout <<" > ";
    deal = getch();

    switch(deal)
    {

    case '0':
        chodzenie_po_danych(0);

    case '1':
        chodzenie_po_danych(1);

    case '8':
        menu();

    default:
            {
                gotoxy(30, 25);
                cout << "Wybierz jeszcze raz!" << endl;
                Sleep(1000);
                Menu_woman_or_man();
            }

    }

}

void menu_wyszukiwania()
{
    int wybor;
    czyszczenie();

    gotoxy(23, 2);
    cout << "Wybierz metode wyszukiwania" << endl;
    gotoxy(3, 3);
    cout << "*************************************************************************" << endl;
    gotoxy(22, 6);
    cout << "1. Wyszukaj wedlug imienia" << endl;
    gotoxy(22, 9);
    cout << "2. Wyszukaj wedlug imienia i nazwisko" << endl;
    gotoxy(22, 12);
    cout << "3. Wyszukaj wedlug singla/nazwy plyty" << endl;
    gotoxy(22, 15);
    cout << "4. Wyszukaj wedlug ceny albumu" << endl;
    gotoxy(22, 18);
    cout << "5. Wroc do menu glownego" << endl;

    gotoxy (32, 21);
    cout << "Twoj wybor to: ";
    gotoxy (32, 23);
    cout << " > ";
    wybor = getch();

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
                wykonawcy[rekord].wyszukaj_po_imieniu_i_nazwisku();

                getchar();
                getchar();
                menu_wyszukiwania();

        case '3':
                czyszczenie();
                wykonawcy[rekord].wyszukaj_singiel();
                getchar();
                getchar();
                menu_wyszukiwania();

        case '4':
                czyszczenie();
                wykonawcy[rekord].wyszukaj_po_cenie();
                getchar();
                getchar();
                menu_wyszukiwania();

        case '5':
            menu();

        default:
            {
                gotoxy(30, 21);
                cout<< "Wybierz jeszcze raz!" << endl;
                Sleep(1000);
                menu_wyszukiwania();

            }
    }
}


void menu_sortowania()
{
    int wybor;
    czyszczenie();

    gotoxy(27, 2);
    cout << "Wybierz metode sortowania" << endl;
    gotoxy(3, 3);
    cout << "*************************************************************************" << endl;
    gotoxy(5, 5);
    cout << "1. Posortuj rosnaco wedlug ceny" << endl;
    gotoxy(45, 5);
    cout << "2. Posortuj rosnaco wedlug singla" << endl;
    gotoxy(22, 8);
    cout << "3. Posortuj rosnaco wedlug ilosci sprzedanych plyt" << endl;
    gotoxy(5, 11);
    cout << "4. Posortuj rosnaca wedlug wieku" << endl;
    gotoxy(45, 11);
    cout << "5. Posortuj malejaco wedlug wieku" << endl;
    gotoxy(5, 14);
    cout << "6. Posortuj rosnaca wedlug imienia" << endl;
    gotoxy(5, 17);
    cout << "7. Posortuj malejaco wedlug numeru na lisce przebojow" << endl;
    gotoxy(5, 20);
    cout << "8. Posortuj rosnaca wedlug numeru na lisce przebojow" << endl;
    gotoxy(26, 23);
    cout << "9. Wroc do menu glownego" << endl;

    gotoxy (32, 27);
    cout << "Twoj wybor to: ";
    gotoxy (32, 29);
    cout << " > ";
    wybor = getch();

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
                    Menu_woman_or_man();

        case '2':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "wedlug nazwy singla, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_rosnace_po_singlu();
                    Menu_woman_or_man();

        case '3':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "wedlug ilosci sprzedanych krazkow, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_po_ilosci_plyt();
                    Menu_woman_or_man();

        case '4':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "rosnaco wedlug wieku, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_rosnace_po_wieku();
                    Menu_woman_or_man();

        case '5':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "malejaco wedlug wieku, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_malejace_po_wieku();
                    Menu_woman_or_man();


        case '6':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "wedlug imienia, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_po_imieniu();
                    Menu_woman_or_man();

        case '7':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "wedlug numeru malejaco, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_malejace_po_numerze();
                    Menu_woman_or_man();

        case '8':
                czyszczenie();
                gotoxy(22, 9);
                cout << "By posortowac wszystkich artystow i artystki ";
                gotoxy(22, 10);
                cout << "wedlug numeru rosnaco, wcisnij enter" << endl;
                gotoxy(22, 11);
                getchar();

                    wykonawcy[rekord].sortowanie_rosnace_po_numerze();
                    Menu_woman_or_man();

        case '9':
            menu();

        default:
            {
                gotoxy(30, 27);
                cout<< "Wybierz jeszcze raz!" << endl;
                Sleep(1000);
                menu_sortowania();

            }
    }
}

void start()
{
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),677); //910 //253 //233 - zolty //279 - niebieski //674 - zielen

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
