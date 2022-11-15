#include <iostream>
#include <vector>

using namespace std;

bool checkIfNextNumberIsLower(int index, vector<int> &inputData) {
    if (index != inputData.size() - 1) {
        return (inputData[index]) > (inputData[index + 1]);
    }
    return false;
}


void getAllDescendingSequencesInRangeFromIndex(int counter, int index, vector<int> &inputData,
                                               vector<vector<int>> &returnData) {

    int maxCounter = counter;
    while (counter > 0) {
        int numberOfSubSequences = maxCounter - counter + 1;
        while (numberOfSubSequences > 0) {
            int firstIndex = index - counter - numberOfSubSequences + 1;
            returnData.push_back(
                    vector<int>{
                            inputData.begin() + firstIndex,
                            inputData.begin() + firstIndex + counter + 1
                    });
            numberOfSubSequences--;
        }
        counter--;
    }

}


vector<vector<int>> findDescendingSequences(vector<int> &inputData) {
    vector<vector<int>> returnData;

    int counter = 0;
    for (int i = 0; i < inputData.size(); i++) {
        if (checkIfNextNumberIsLower(i, inputData)) {
            counter++;
        } else {
            getAllDescendingSequencesInRangeFromIndex(counter, i, inputData, returnData);
            counter = 0;
        }
    }

    return returnData;
}

int main() {
    vector<int> inputData = {17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    vector<vector<int>> allDescendingSequences = findDescendingSequences(inputData);

    for (auto descendingSequences: allDescendingSequences) {
        for (const auto &item: descendingSequences) {
            cout << item << ", ";
        }
        cout << endl;
        cout << "----------------" << endl;
    }
    cout << "Liczba podciagow malejacych: "<<allDescendingSequences.size();
    return 0;
}