#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

void recepti(string& a){
// ISPISUJE DOSTUPNE RECEPTE
    ifstream unos;

    cout << "Dostupni recepti: \n";
    unos.open("Recepti\\init.txt");

    while(unos>>a){
        cout << a << endl;
    }
    unos.close();
}

void odaberi(){
// IZBOR RECEPTA
    ifstream unos;
    unos.open("init.txt");
    cout << "Izaberite recept: \n";
    string x,korisnik;
    cin >> korisnik;
    int duzina=0;
// DUZINA LISTE RECEPATA
    while(unos>>x){
        duzina++;
    }
// PROVJERA UNOSA
    int r=1;
    while(unos>>x){
        if(korisnik!=x){
            r++;
        }
    }
    unos.close();

    if(r==duzina){
        cout << "\nRecept se ne nalazi u bazi.";
    }

    else{
// AKO JE DOBAR UNOS ISPISUJE SE RECEPT U KONZOLI
        string recept;
        int sastojak;
        ofstream ispis1;
        ofstream ispis2;
        ispis1.open("Recepti\\" + korisnik + "_sastojci.txt", ios_base::app);
        ispis2.open("Recepti\\" + korisnik + "_kolicina.txt", ios_base::app);
        ispis1.close();
        ispis2.close();
        ifstream unos1;
        ifstream unos2;

        unos1.open("Recepti\\" + korisnik + "_sastojci.txt");
        unos2.open("Recepti\\" + korisnik + "_kolicina.txt");
        while(true){
            unos1 >> recept;
            cout << recept << " ";
            unos2>>sastojak;
            cout << sastojak << endl;
            break;
        }

        unos1.close();
        unos2.close();
    }
}

void noviRecept(){
// DODAJE NOVI RECEPT U INIT
    string recept;
    cout << "Unijeti naziv recepta: ";
    cin >> recept;

    ofstream ispis;
    ispis.open("Recepti\\init.txt", ios_base::app);;
    ispis << "\n" + recept;
    ispis.close();

    string sastojak;
    int kolicina;

    ofstream unos1;
    ofstream unos2;
    unos1.open("Recepti\\" + recept + "_sastojci.txt");
    unos2.open("Recepti\\" + recept + "_kolicina.txt");
    char kraj;
// UNOS SASTOJAKA I KOLICINE
    cout << "\nUnijeti sastojak(space), zatim kolicinu(enter)\n\n";
    while(true){
        getline(cin, sastojak, ' ');
        unos1 << sastojak << endl;
        cin >> kolicina;
        unos2 << kolicina << endl;
        cout << "\nDa li je kraj unosa sastojaka? (Y/N)\n";
// PROVJERA DA LI JE VALIDAN UNOS
        cin >> kraj;
        while(kraj!='Y' && kraj!='y' && kraj!='n' && kraj!='N'){
        cout << "\nGreska unosa, ponoviti unos.";
        cin >> kraj;
            }
        if(kraj == 'Y' || kraj == 'y'){
            break;
        }
    }

    unos1.close();
    unos2.close();
}
int main(){
    string a;
    recepti(a);
    cout << "Da li se nalazi recept koji zelite u datom nizu: (y/n)\n";
    char izbor;
    cin >> izbor;
    while(izbor!='Y' && izbor!='y' && izbor!='n' && izbor!='N'){
        cout << "\nGreska unosa, ponoviti unos.";
        cin >> izbor;
    }
    if(izbor == 'Y' || izbor == 'y'){
    odaberi();
    }
    else if(izbor == 'N' || izbor == 'n')
    {
        noviRecept();
        recepti(a);
        odaberi();
    }
    return 0;
}
