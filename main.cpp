/*

Dla zadanej tablicy liczb calkowitych przesun wszystkie elementy mniejsze od 0 na jej koniec (nalezy zachowac kolejnosc wystepowania!).

 Przyklad:
 Wejscie: A[] = [-10,5,8,-4,1,3,0,-7]
 Wyjscie [5,8,1,3,0,-10,-4,-7]

*/

#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <sstream>
#include <bits/stdc++.h>

using namespace std;

//algorytm 1 -realizacja poprzez nowa tablice
vector<int> algorithm_v1(vector<int> arr){
    vector<int> arr_sorted; //tablica wyjsciowa

    for (int i : arr) { //dodawanie elementów nieujemnych do tablicy
        if (i >= 0) {
            arr_sorted.push_back(i);
        }
    }
    for (int i : arr) { //dodawanie elementów ujemnych do tablicy
        if (i < 0) {
            arr_sorted.push_back(i);
        }
    }
    return arr_sorted; //zwracanie tablicy wyjsciowej
}

//algorytm 1 - realizacja poprzez swap()
vector<int> algorithm_v2(vector<int> arr){
    int count = 1; // ilosc wykonan funkcji swap()
    for ( int i = 0; i < arr.size()-1; i++ ){
        if ( arr[i] < 0 ){
            if ( arr[i+1] < 0 ) {
                count += 1;
            }
            else{
                for ( int j = 0; j < count; j++ ){
                    swap( arr[i-j],arr[i+1-j] );
                }
            }
        }
    }
    return arr;
}

//funkcja obliczajaca czas wykonania algorytmu
long double timer(const vector<int>& arr,const function<vector<int>(vector<int>)> algorithm,int count){
    long double sum = 0; //zmienna dla sumy czasow wykonania algorytmu

    for( int i = 0; i <= count; i++ ){
        auto startA = chrono::steady_clock::now(); //start zegara
        algorithm(arr); // wybrany wczesniej algorytm
        auto stopA = chrono::steady_clock::now(); //stop zegara
        auto durationA = stopA - startA; //roznica czasow
        sum += chrono::duration<long double, nano> (durationA).count(); //zmiennoprzecinkowe zapisanie do zmiennej
    }
    return sum/count; //zwracanie sredniej czasow
}

//funkcja generujaca tablice z losowymi liczbami calkowitymi
vector<int> array_generator(int count, int min, int max){
    vector<int> arr;
    random_device generator; //obiekt klasy random_device
    uniform_int_distribution<int> myUnifIntDist(min,max); //nadanie przedzialu liczb
    for(int i = 0; i <= count-1; i++){ //dodawanie losowych elementow z przedzialu
        arr.push_back(myUnifIntDist(generator));
    }
    return arr; //zwrocenie tablicy
}

//funkcja wyswietlajaca podana tablice
void array_display(const vector<int>& arr){
    cout << "[";
    for(int i = 0; i < arr.size(); i++){
        cout << arr[i];
        if(i != arr.size()-1){
            cout << ", ";
        }
    }
    cout << "]"<<endl;
}

//funkcja tworzaca tablice przez uzytkownika
vector<int> array_by_user(){
    int count; //zmienna rozmiaru tablicy
    int element;//zmienna elementu
    vector<int> arr_user;
    cout << "Podaj ilosc liczb do stworzenia tablicy: ";
    cin >> count;

    for(int i = 1; i <= count; i++){ // dodawanie elementu
        cout << "Podaj "<<i<<" liczbe: ";
        cin >> element;
        arr_user.push_back(element);
    }
    return arr_user;//zwracanie tablicy

}

//funkcja wyswietlajaca wyniki
void result_display(const vector<int>&arr) {
    cout << "Przed podzialem: " <<endl;
    array_display(arr);
    cout << endl;
    cout << "ALGORYTM 1"<<endl;
    cout << endl;
    cout <<"Po podziale poprzez algorytm 1: "<<endl;
    array_display(algorithm_v1(arr));
    cout << "Sredni czas wykonania algorytmu 1: "<< timer(arr, algorithm_v1,100) <<" nanosekund."<<endl;
    cout << endl;
    cout << "ALGORYTM 2"<<endl;
    cout << endl;
    cout <<"Po podziale poprzez algorytm 2: "<<endl;
    array_display(algorithm_v2(arr));
    cout << "Sredni czas wykonania algorytmu 2: "<< timer(arr, algorithm_v2,100) <<" nanosekund."<<endl;
    cout << endl;
}

//funkcja zapisujaca do pliku
void write_to_file(vector<int>arr){
    vector<int> alg1 = algorithm_v1(arr); //zmienna algorytmu 1
    vector<int> alg2 = algorithm_v2(arr); //zmienna algorytmu 2
    stringstream ss; //obiekt klasy stringstream do dodawania ciagow znakow
    ofstream output; //obiekt klasy ofstream do zapisu do pliku

    ss << "Przed podzialem: " << endl << "[";
    for(int i  = 0; i < arr.size(); i++){
        ss << arr[i];
        if(i != arr.size()-1){
            ss << ", ";
        }
    }
    ss << "]" << endl << "ALGORYTM 1"<< endl << "[";
    for(int i = 0; i < alg1.size(); i++){
        ss << alg1[i];
        if(i != arr.size()-1){
            ss << ", ";
        }
    }
    ss <<"]" << endl;
    ss << "Sredni czas wykonania algorytmu 1 (srednia wartosc 100 prob): "<< timer(arr, algorithm_v1,100) <<" nanosekund."<<endl;
    ss << "ALGORYTM 2"<< endl << "[";
    for(int i = 0; i < alg2.size(); i++){
        ss << alg2[i];
        if(i != arr.size()-1){
            ss << ", ";
        }
    }
    ss << "]" << endl;
    ss << "Sredni czas wykonania algorytmu 2 (srednia wartosc 100 prob): "<< timer(arr, algorithm_v2,100) <<" nanosekund."<<endl;
    string s = ss.str(); // stringstream -> string
    output.open("output.txt");
    output << s;
    output.close();
    cout << "Wynik zapisal sie w pliku output.txt w folderze cmake-build-debug"; //informacja o polozeniu pliku w projekcie
}

int main() {
    static vector<int> A = {-10, 5, 8, -4, 1, 3, 0, -7}; // Przyklad 1
    static vector<int> B = {92, -32, 8, -121, 55, 32, 34, -23, 0}; //Przyklad 2
    static vector<int> C = {-29, -30, 20, 10, 60, -38, -489, 892, 829, -894, 2516, 72637, -9400};//Przyklad 3
    vector<int> user;
    vector<int> random_arr;
    int choice;
    int count;
    int min;
    int max;
    bool min_max_test = false;
    bool menu_loop = false;

    //proste "menu"
    cout << "Witaj w programie wykonujacym algorytm przesuwania elementow ujemnych tablicy na koniec." << endl;
    cout << endl;
    cout << "Wybierz co chcesz zrobic:" << endl;
    cout << "1. Przyklady" << endl;
    cout << "2. Wlasna tablica" << endl;
    cout << "3. Tablica losowa" << endl;
    cin >> choice;

    while (!menu_loop) {
        switch (choice) {
            case 1:
                result_display(A);
                result_display(B);
                result_display(C);
                menu_loop = true;
                break;
            case 2:
                user = array_by_user();
                result_display(user);
                write_to_file(user);
                menu_loop = true;
                break;
            case 3:
                cout << "Podaj rozmiar tablicy do wygenerowania: ";
                cin >> count;
                while (!min_max_test) {
                    cout << endl << "Podaj dolna granice zakresu (min): ";
                    cin >> min;
                    cout << endl << "Podaj gorna granice zakresu (max): ";
                    cin >> max;
                    if (min < max) {
                        random_arr = array_generator(count, min, max);
                        result_display(random_arr);
                        write_to_file(random_arr);
                        min_max_test = true;
                        menu_loop = true;
                    } else {
                        cout << "Dolna granica musi byc nizsza od gornej. Podaj zakres jeszcze raz." << endl;
                    }
                }
                break;
            default:
                break;

        }


    }
}