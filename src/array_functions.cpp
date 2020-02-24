/*
 * functionstocomplete.cpp
 *
 *  Created on: Sep 10, 2017
 *      Author: keith
 */

//============================================================================
#include "array_functions.h"
#include "utilities.h"
//============================================================================

//============================================================================
//	stuff you will need
//============================================================================
//TODO define a structure to track words and number of times they occur

//TODO add a global array of entry structs (global to this file)

//TODO add variable to keep track of next available slot in array

//TODO define all functions in header file

//TODO look in utilities.h for useful functions, particularly strip_unwanted_chars!

struct woco {
    std::string word;
    int count{};
    std::string upper;
};

struct woco myarr[constants::MAX_WORDS];
int size = 0;

void clearArray() {
    size = 0;
}

int getArraySize() {
    return size;
}

std::string getArrayWordAt(int i) {
    return myarr[i].word;
}

int getArrayWord_NumbOccur_At(int i) {
    return myarr[i].count;
}

bool processFile(std::fstream &myfstream) {
    if (myfstream.peek() == std::ifstream::traits_type::eof()) {
        return false;
    }

    while (myfstream) {
        std::string line;
        myfstream >> line;
        processLine(line);
    }

    return true;
}

void processLine(std::string &myString) {
    std::istringstream ss(myString);
    while (ss) {
        std::string token;
        ss >> token;
        processToken(token);
    }
}

void processToken(std::string &token) {
    strip_unwanted_chars(token);


    std::string upperToken = token;
    toUpper(upperToken);

//    std::transform(token.begin(), token.end(), token.begin(), ::tolower);
    if (!upperToken.empty()) {
        for (int i = 0; i < size; i++) {
            if (myarr[i].upper == upperToken) {
                myarr[i].count++;
                return;
            }
        }

        myarr[size].upper = upperToken;
        myarr[size].count = 1;
        myarr[size].word = token;
        size++;
    }
}

bool openFile(std::fstream &myfile, const std::string &myFileName, std::ios_base::openmode mode) {
    if (!myfile.is_open()) {
        myfile.open(myFileName, mode);
        return myfile.good();
    }

    return false;
}

void closeFile(std::fstream &myfile) {
    if (myfile.is_open()) {
        myfile.close();
    }
}

int writeArraytoFile(const std::string &outputfilename) {
    std::fstream myfile;
    openFile(myfile, outputfilename, std::ios::out);

    for (int i = 0; i < size; i++) {
        myfile << myarr[i].word;
        myfile << " ";
        myfile << myarr[i].count;
        myfile << "\n";
    }

    closeFile(myfile);
    return constants::SUCCESS;
}

bool woco_sorter(woco const &lw, woco const &rw, constants::sortOrder so) {
    switch (so) {
        case constants::NONE:
            return false;
        case constants::ASCENDING:
            return lw.upper > rw.upper;
        case constants::DESCENDING:
            return lw.upper < rw.upper;
        case constants::NUMBER_OCCURRENCES:
            return lw.count < rw.count;
    }

}

void sortArray(constants::sortOrder so) {
    if (so == constants::NONE) {
        return;
    }

    struct woco tmp;
    for (int i = size - 1; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (woco_sorter(myarr[j], myarr[j + 1], so)) {
                tmp = myarr[j];
                myarr[j] = myarr[j + 1];
                myarr[j + 1] = tmp;
            }
        }
    }

}
