
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <cctype>

using namespace std;

bool loadJokes(const string& filename, vector<string>& jokes) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Error: Cannot open jokes file!" << endl;
        return false;
    }

    string line;

    while (getline(file, line)) {
        if (!line.empty()) {
            jokes.push_back(line);
        }
    }

    file.close();
    return !jokes.empty();
}

void tellJoke(const vector<string>& jokes) {
    int randomIndex = rand() % jokes.size();

    string joke = jokes[randomIndex];

    size_t questionMark = joke.find('?');

    if (questionMark != string::npos) {
        cout << joke.substr(0, questionMark + 1) << endl;

        cout << "Press Enter for the answer...";
        string wait;
        getline(cin, wait);

        cout << joke.substr(questionMark + 1) << endl;
    }
    else {
        cout << joke << endl;
    }
}

int main() {
    srand(time(0));

    vector<string> jokes;

    if (!loadJokes("randomJokes.txt", jokes)) {
        return 1;
    }

    cout << "Welcome to Alexa Joke Generator!" << endl;
    cout << "Type 'Alexa, tell me a joke' or 'quit' to exit." << endl;

    string command;

    while (true) {
        cout << "\nYour command: ";
        getline(cin, command);

        for (char& c : command) {
            c = tolower(static_cast<unsigned char>(c));
        }

        if (command == "quit") {
            cout << "Goodbye!" << endl;
            break;
        }
        else if (command == "alexa, tell me a joke") {
            tellJoke(jokes);
        }
        else {
            cout << "Command not recognised. Please try again." << endl;
        }
    }

    return 0;
}
