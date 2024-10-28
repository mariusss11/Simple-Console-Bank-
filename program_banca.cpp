#include <iostream>
#include <fstream>
#include <cstring>

using namespace std; 

ifstream fin("clienti");
ofstream fout("iesire");  
 
struct client {
    char pin[20];
    long long ID;
    char nume[20];
    char prenume[20];
    float sold;
    

} a[99];

void readData(client a[], int& n) {
    ifstream fin("clienti");
    n = 0;

    while (fin >> a[n].ID >> a[n].pin >> a[n].nume >> a[n].prenume >> a[n].sold) {
        n++;
    }

    fin.close();
}

void writeData(client a[], int& n) {
    ofstream fout("clienti");

    for (int i = 0; i < n; ++i) {
        fout << a[i].ID << " " << a[i].pin << " " << a[i].nume << " " << a[i].prenume 
        << " " << a[i].sold << "\n";
    }

    fout.close();
} 

void alimentare(client a[], int j, int k) {
    int x;
    cout << "Datele sunt : \n";
    cout << "Nume : " << a[j].nume << "\n";
    cout << "Prenume : " << a[j].prenume << "\n";
    cout << "Sold : " << a[j].sold << "\n";
    cout << "Introduceti suma care doriti sa fie introdusa : ";
    cin >> x;
    a[j].sold += x;
    writeData(a, k);
    system ("cls");
    cout << "Datele noi sunt : \n";
    cout << "Nume : " << a[j].nume << "\n";
    cout << "Prenume : " << a[j].prenume << "\n";
    cout << "Sold : " << a[j].sold << "\n";
    cout << "\nSe revine la meniul principal\n\n";
}

void extragere(client a[], int j, int k) {
    int x;
    cout << "Datele sunt : \n";
    cout << "Nume : " << a[j].nume << "\n";
    cout << "Prenume : " << a[j].prenume << "\n";
    cout << "Sold : " << a[j].sold << "\n";
    cout << "Introduceti suma care doriti sa fie extrasa : ";
    cin >> x;
    if (a[j].sold > x){
        a[j].sold -= x;
    } else if (a[j].sold < x){
        do {
            cout << "Nu exista suficiente credite, va rugma introduceti alt numar : ";
            cin >> x;
        }while (a[j].sold < x);
        a[j].sold -= x;
    }
    writeData(a, k);
    system ("cls");
    cout << "\nDatele noi sunt : \n";
    cout << "Nume : " << a[j].nume << "\n";
    cout << "Prenume : " << a[j].prenume << "\n";
    cout << "Sold : " << a[j].sold << "\n";
    cout << "\nSe revine la meniul principal\n";
}

long long VerificarePIN(int k, int op) {

    long long id;
    int x;
    cout << "Introduceti ID-ul persoanei : ";
    cin >> id;
    int j;
    bool found = false;
    do {
        for (x = 0; x < k; x++) {
            if (a[x].ID == id) {
                j = x;
                found = true;
                break;
            }
        }

        if (!found) {
            cout << "Client cu acest ID nu exista. Reintroduceti ID-ul : ";
            cin >> id;
        }
        

    } while (!found);


    bool gasit = false;
    
    do {
        for ( j = 0; j < k; j++){
            if (a[j].ID == id ){
                gasit = true;
                system ("cls");
                cout << "Persoana a fost gasita" << "\n";
                char pin[20];
                cout << "Introduceti PIN-ul : ";
                cin >> pin;

                while (strcmp(pin, a[j].pin) != 0) {
                    cout << "PIN-ul nu este corect, introduceti din nou PIN-ul : ";
                    cin >> pin;
                }
                break;
            } else if (a[j].ID != id){}
        }

        if (op == 3){
            alimentare(a, j, k);
            break;
        } else if (op == 4){
            extragere(a, j, k );
            break;
        } 
    } while (!gasit);
}

void excludere (int i, int &k){
    
    for (int j = i; j < k; j++) {
        if (j == k - 2){
            a[j] = a[j + 1];
            break;
        } else
            a[j] = a[j + 1];
    }
    cout << "Clientul a fost eliminat cu succes\n";
    k -= 1;
};

void VerificareID(int& k, long long id) {

    bool gasit = false;
    do {
        for (int i = 0; i < k; i++){
            if (a[i].ID == id) {
                    gasit = true;
                    system ("cls");
                    cout << "Clientul a fost gasit\n";
                    char pin_n[10];
                    cout << "Introduceti PIN-ul clientului : ";
                    cin >> pin_n;
                    if (strcmp(a[i].pin,pin_n) != 0){
                        do {
                            cout << "PIN-ul introdus este incorect. Reintroduceti : ";
                            cin >> pin_n;
                        } while (strcmp(a[i].pin,pin_n) != 0);
                    }

                    excludere(i, k);
                    break;
                }
        }
        if (!gasit){
                cout << "Client cu acest ID nu exista. Reintroduceti ID-ul : ";
                cin >> id;
        }
    } while (!gasit);

    writeData(a, k);
    readData(a, k);
};



int main() { //main---------------------------------------------------------------

    system ("cls");

    cout << " ------------------------------------------------ " << "\n";
    cout << "|                                                  |" << "\n";
    cout << "|                   MENIU                          |" << "\n";
    cout << "|                                                  |" << "\n";
    cout << " ------------------------------------------------ " << "\n";

    int i = 0;
    
    while (fin >> a[i].ID >> a[i].pin >> a[i].nume >> a[i].prenume >> a[i].sold) {
        i++;
    }
    int k = i;
    int op;

    do {

        for (int i = 0; i < k; i++){
            fin >> a[i].ID >> a[i].pin >> a[i].nume >> a[i].prenume >> a[i].sold;
        }

        cout << "1. Afisarea persoanelor din baza de date " << "\n";
        cout << "2. Informatii despre o persoana din baza de date " << "\n";
        cout << "3. Alimentare cont " << "\n";
        cout << "4. Retragere numerar " << "\n";
        cout << "5. Transfer de la o persoana la alta " << "\n";
        cout << "6. Adaugare client " << "\n";
        cout << "7. Excludere client " << "\n";
        cout << "8. Inchidere baza de date " << "\n";
        cout << "Introduceti optiunea: ";
        
        cin >> op;

        switch (op) {

            case 1: {

                system("cls");
                readData(a, k);

                for (int j = 0; j < k; j++) {
                    cout << "Numele si prenumele : " << a[j].nume << " " << a[j].prenume << "\n";
                }
                cout << "\n";
            }
            break;

            case 2: {

                readData(a, k);

                char s[20];
                cout << "Introduceti numele persoanei cautate : ";
                cin >> s;
                cin.get();
                char s2[20];
                cout << "Introduceti prenumele persoanei cautate : ";
                cin >> s2;
                int j;
                bool found = false;
                do {
                    found = false; 
                    for (j = 0; j < k; j++) {
                        if (strcmp(a[j].nume, s) == 0 && strcmp(a[j].prenume, s2) == 0) {
                            found = true;
                            break;
                        }
                    }

                    if (!found) {
                        cout << "Persoana nu a fost gasita, reintroduceti\n";
                        cout << "Introduceti numele : ";
                        cin >> s;
                        cout << "Introduceti prenumele : ";
                        cin >> s2;
                    }
                } while (!found && j < k);

                char pin_n[10];
                cout << "Introduceti PIN-ul clientului : ";
                cin >> pin_n;
                if (strcmp(a[j].pin,pin_n) != 0){
                    do {
                        cout << "PIN-ul introdus este incorect. Reintroduceti : ";
                        cin >> pin_n;
                    } while (strcmp(a[j].pin,pin_n) != 0);
                }

                system("cls");

                cout << "Datele acesteia sunt : " << "\n";
                cout << "Nume : " << a[j].nume << "\n";
                cout << "Prenume : " << a[j].prenume << "\n";
                cout << "Sold : " << a[j].sold << "\n";
                cout << "ID : " << a[j].ID << "\n";
                char r[5];
                cout << "Doriti sa faceti modificari contului : ";
                cin >> r;
                char r1[5] = "DA";
                char r2[5] = "Da";
                char r3[5] = "da";
                    
                if (strcmp(r,r1) == 0 || strcmp(r,r2) == 0 || strcmp(r,r3) == 0){

                    int op1;

                    do {

                        cout << "1. Schimbare PIN" << "\n";
                        cout << "2. Schimbare nume" << "\n";
                        cout << "3. Schimbare prenume" << "\n";
                        cout << "4. Revenire la meniul principal" << "\n";
                        cout << "Introduceti optiunea: ";
                                    
                        cin >> op1;

                        switch (op1){


                            case 1: {

                            system("cls");

                            cout << "Introduceti PIN-ul curent : ";
                            char pin[20];
                            cin >> pin;
                            if (strcmp(pin, a[j].pin) != 0){
                                do {
                                    cout << "PIN-ul introdus nu este corect, va rugam introduceti din nou : ";
                                    cin >> pin;
                                } while (strcmp(pin, a[j].pin) != 0);
                            }
                            char pin_n[20];
                            cout << "Introduceti noul PIN : ";
                            cin >> pin_n;
                            if (strcmp(pin_n, a[j].pin) == 0){
                                do {
                                    cout << "PIN-ul a fost deja folosit, va rugam introduceti alt PIN : ";
                                    cin >> pin_n;
                                } while (strcmp(pin_n, a[j].pin) == 0);
                            }
                            strcpy(a[j].pin, pin_n);
                            writeData(a, k);

                            cout << "Schimbarile au fost efectuate cu succes \n";
                            cout << "Se revine la meniul anterior\n";

                            cout << "\n";

                            }
                            break;

                            case 2 : {

                            system("cls");

                            char nume_n[20];
                            cout << "Introduceti numele nou : ";
                            cin >> nume_n;
                            if (strcmp(a[j].nume, nume_n) == 0){
                                 do {
                                    cout << "Introduceti alt nume : ";
                                    cin >> nume_n;
                                } while (strcmp(a[j].nume, nume_n) == 0);
                            }
                            strcpy(a[j].nume, nume_n);
                            writeData(a, k);
                            readData(a, k);

                            cout << "Schimbarile au fost efectuate cu succes \n";
                            cout << "Se revine la meniul anterior\n";

                            cout << "\n";

                            }
                            break;

                            case 3 : {

                            system("cls");

                            char prenume_n[20];
                            cout << "Introduceti numele nou : ";
                            cin >> prenume_n;
                            if (strcmp(a[j].prenume, prenume_n) == 0){
                            do {
                                cout << "Introduceti alt prenume : ";
                                cin >> prenume_n;
                                } while (strcmp(a[j].prenume, prenume_n) == 0);
                            }
                            strcpy(a[j].prenume, prenume_n);
                            writeData(a, k);
                            readData(a, k);

                            cout << "Schimbarile au fost efectuate cu succes \n";
                            cout << "Se revine la meniul anterior\n";

                            cout << "\n";
                            }
                            break;

                            case 4 : {
                                system("cls");
                            }
                            break;

                            default : {
                                cout << "A fost introdus o optiune invalida, va rugam introduceti un numar valid" << "\n";
                            }
                        }

                    } while (op1 != 4);
                } else if (strcmp(r,r1) != 0 || strcmp(r,r2) != 0 || strcmp(r,r3) != 0){
                        cout << "\nSe revine la meniul anterior\n";
                        break;
                    }
                writeData(a, k);
                readData(a, k);
            }


            break;

            case 3: {

                readData(a, k);

                system("cls");

                VerificarePIN(k, op);
                cout << "\n";
            }
            break;

            case 4 : {

                readData(a, k);
                
                system("cls");

                VerificarePIN(k, op);
                cout << "\n";
            }
            break;

            case 5: {

                system("cls");

                readData(a, k);

                long long id;
                cout << "Introduceti ID-ul persoanei : ";
                cin >> id;

                int i = 0;
                while (i < k && a[i].ID != id) {
                    cout << "ID-ul introdus nu corespunde cu nici o persoana, va rugam sa introduceti alt ID : ";
                    cin >> id;
                }

                char pin[20];
                cout << "Introduceti PIN-ul : ";
                cin >> pin;

                while (strcmp(pin, a[i].pin) != 0) {
                    cout << "PIN-ul nu este corect, introduceti din nou PIN-ul : ";
                    cin >> pin;
                }
                cout << "Persoana a fost gasita\n";
                cout << "Nume : " << a[i].nume << "\n";
                cout << "Prenume : " << a[i].prenume << "\n";
                cout << "Sold : " << a[i].sold << "\n";
                
                int suma;
                cout << "Introduceti suma care va fi transferata : ";
                cin >> suma;
                if (suma > a[i].sold){
                    do {
                        cout << "Nu exista suficiente credite, introduceti alta suma : ";
                        cin >> suma;
                    } while (suma > a[i].sold);
                }

                a[i].sold -= suma;

                char s[20];
                char s2[20];

                bool found = false;
                do {
                    cout << "Introduceti numele persoanei caruia ii vor fi transferati banii : ";
                    cin >> s;
                    cout << "Introduceti prenumele persoanei caruia ii vor fi transferati banii : ";
                    cin >> s2;

                    for (int j = 0; j < k; j++) {
                        if (strcmp(a[j].nume, s) == 0 && strcmp(a[j].prenume, s2) == 0 && (a[i].ID != a[j].ID )) {
                            found = true;
                            cout << "Persoana a fost gasita" << "\n";
                            a[j].sold += suma;
                        }
                    }

                    if (!found) {
                        cout << "Transfer imposibil. Mai introduceti datele inca odata." << "\n";
                    }
                } while (!found);
            }

            cout << "Transferul a fost efectuat cu succes \n";
            cout << "Se revine la meniul principal\n\n";
            writeData(a, k);

            break;
            
            case 6 : {

                readData(a, k);
                
                char nume[20];
                cout << "Introduceti numele persoanei : ";
                cin >> nume;
                strcpy(a[k].nume, nume); 

                char prenume[20];
                cout << "Introduceti prenumele persoanei : ";
                cin >> prenume;
                strcpy(a[i].prenume, prenume);

                long long id;
                cout << "Introduceti ID-ul persoanei : ";
                cin >> id;
                a[k].ID = id;

                char pin[10];
                cout << "Introduceti PIN-ul : ";
                cin >> pin;
                strcpy(a[k].pin, pin);

                int sold;
                cout << "Introduceti soldul disponibil la moment : ";
                cin >> sold;
                a[k].sold = sold;
                k += 1;
                cout << "\n";

                writeData(a, k);
                readData(a, k);
            }
            break;

            case 7 : {

                readData(a, k);

                system("cls");
                long long id;
                cout << "Introduceti ID-ul clientului pe care doriti sa il eliminati : ";
                cin >> id;
                VerificareID(k, id);
                writeData(a, k);
                readData(a, k);
                cout << "\n";
                
            }
            break;

            case 8 : {

                system ("cls");

                cout << "Baza de date s-a inchis " << "\n";
            }
            break;

            default: {

                cout << "A fost introdus o optiune invalida, va rugam introduceti un numar valid" << "\n";
            }
            break;
        }

    } while (op != 8);



    return 0;
}
