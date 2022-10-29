#include <iostream>
#include <vector>

//          dzięki temu nie trzeba przed np cout, endl dodatać std::
using namespace std;


// 1.       Wprowadzam dane wejściowe - dowolne liczby całkowite
// 2.       Podaję dane wejściowe do funkcji która będzie po kolei przechodziła przez wszystkie podane liczby
// 3.       Przechodzę po kolei przez wszystkie podane liczby
// 4.       Sprawdzam czy następna liczba jest mniejsza od aktualnej
// 4.1          Jeśli tak jest to zwiększam licznik który będzie pokazywał jak długi był ciąg zmniejszających liczb
// 4.2          Jeśli nie to mogę zacząć wypisywać te liczby np:
//                  jeśli licznik(counter) wynosi 5 to wiem że dla 5 ostatnich liczb każda następna była mniejsza od aktualnej np: {5, 4, 2, 1, 0, 3, 2, 1}
//                  do funkcji getDescendingSeriesInRange() podaję index pierwszej liczby i zakres ile tych liczb w serii jest
//                  dla powyższej tabeli na zdjęciu poniżej masz rozpisane jak wyglądają indexy i countery dla każdego wywołania



bool checkIfNextNumberIsLower(int index, vector<int> &inputData) {
//      sprawdzam czy aktualna liczba nie jest ostatnią liczbą z inputData
//      jeśli jest ostatnią, to nie ma sensu sprawdzać czy następna jest większa
//      daję -1 ponieważ poróznujemu index do liczby indeksów a nie rozmiaru tablicy
//      (indeksuje się od 0, a rozmiar tablicy liczy się od 1, stąd rozbieżność)
    if (index != inputData.size() - 1) {
//      jeśli następna jest większa zwracam true,
//      w innym wypadku false
        return (inputData[index]) > (inputData[index + 1]);
    }

//      zwracam false jeśli aktualna liczba jest ostatnią (pomijam warunek if)
    return false;
}

//      4.2 biorę index i counter i od danego indexu np: 0 dodaje do tablicy tyle liczb ile pokazuje counter np: 4
//          dla {5, 4, 2, 1, 0, 3, 2, 1} przy index: 0 i counter: 4, dodam do tablicy zwracającej liczby: {5, 4, 2, 1, 0}
vector<int> getDescendingSequenceInRangeFromIndex(int index, int counter, vector<int> &inputData) {
    vector<int> returnData;
//    cout<<"index: "<<index<<endl;
//    cout<<"counter: "<<counter<<endl;
//    cout<<"----------------"<<endl;
    for (counter; counter >= 0; counter--) {
        returnData.push_back(inputData[index]);
        index++;
    }
    return returnData;
}


//  w tej funkcji dostaję informację o maksymalnie długim ciągu w danym zakresie liczb
//  później po dodaniu tego maksymalnie długiego podciągu znajduję podciągi
//  np. {5, 4, 2, 1, 0} maksymalnym ciągiem malejącym w tym zakresie jest {5, 4, 2, 1, 0}
//  później podciągami są {5, 4, 2, 1} oraz {4, 2, 1, 0}
//  później podciągami są {5, 4, 2}, {4, 2, 1} oraz {2, 1, 0}
//  ...
//  aż dojdziemy do podciągów o długości 2, mniejszych podciągów już nie może być
void getAllDescendingSequencesInRangeFromIndex(int counter, int index, vector<int> &inputData, vector<vector<int>> &returnData){

    int maxCounter = counter;
    while (counter > 0) {
        int numberOfSubSequences = maxCounter - counter + 1;
        while (numberOfSubSequences > 0) {
            int firstIndex = index - counter - numberOfSubSequences + 1;
            returnData.push_back(getDescendingSequenceInRangeFromIndex(firstIndex, counter, inputData));
            numberOfSubSequences--;
        }
        counter--;
    }

}


// ad. 2.2 zadeklarowana funkcja, do której podaję zmienne wprowadzone na początku,
//         w której będę przechodził po kolei przez wszystkie podane liczby
//         i patrzył czy występuje ciąg: a(n)>a(n+1)
vector<vector<int>> findDescendingSequences(vector<int> &inputData) {
//         na początku deklaruję tablicę do której będę dodawał malejace ciągi

//         wiem że vector<vector<int>> może się wydawać straszne, sam vector<int> to tablica zawierająca liczby
//         a vector<vector<int>> to tablica takich tablic które zawierają liczby
//         np. jeśli miałabyś kartkę na której zapisałabyś liczby to byłoby to vector<int>
//         a cały zeszyt z takimi kartkami to vector<vector<int>>
    vector<vector<int>> returnData;

//         tworzę licznik, które będzie wzrastał jeśli będzie ciąg malejących po sobie liczb
//         jeśli np będą liczby {5, 3, 2} to licznik wyniesie 2, ponieważ 2 razy następna liczba
//         była mniejsza od poprzedniej, w przypadku {4, 3, 2, 1, -1, -4} licznik (counter) wyniesie 5
    int counter = 0;
// ad. 3
    for (int i = 0; i < inputData.size(); i++) {
//         jeśli następna liczba jest mniejsza od aktualnej to zwiększam counter
        if (checkIfNextNumberIsLower(i, inputData)) {
            counter++;
        }
//         jeśli następa liczba nie jest mniejsza to znaczy że ciąg się kończy
//         w takim przypadku mogę zacząć znalezione ciągi wypisywać
        else {
            getAllDescendingSequencesInRangeFromIndex(counter, i, inputData, returnData);
            counter = 0;
        }
    }

//    zwracam ciągi
    return returnData;
}

int main() {
// ad. 1
    vector<int> inputData = {5, 4, 2, 2, 1};

// ad. 2.1 podaję dane do wyżej zadeklarowanej funkcji
    vector<vector<int>> allDescendingSequences = findDescendingSequences(inputData);

//    pokazuje w konsoli wszystkie znalezione ciągi
    for (auto descendingSequences: allDescendingSequences) {
        for (const auto &item: descendingSequences) {
            cout << item <<", ";
        }
        cout << endl;
        cout << "----------------" << endl;
    }

    cout<<"Liczba ciągów malejących to: "<<allDescendingSequences.size();

    return 0;
}
