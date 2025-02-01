#include <iostream>
#include <string>

using namespace std;

class RegularGrammarParser {
private:
    char productions[26][2]; // Store production rules with two characters (e.g., S -> aS)
    char startSymbol;

public:
    RegularGrammarParser(char start) : startSymbol(start) {
        for (int i = 0; i < 26; ++i) {
            productions[i][0] = '\0'; // Initialize productions array
            productions[i][1] = '\0'; // Initialize second character of the production
        }
    }

    void addProduction(char variable, const string& production) {
        productions[variable - 'A'][0] = production[0]; // Store the first character of the production
        if (production.size() > 1) {
            productions[variable - 'A'][1] = production[1]; // Store the second character if it exists
        }
    }

    bool isTerminal(char symbol) {
        return !isupper(symbol); // Terminals are lowercase characters
    }
    bool parseString(const string& input) {
        int n = input.size();
        bool dp[n + 1][n + 1] = {false};

        for (int i = 0; i <= n; ++i) {
            for (int j = 0; j < n - i + 1; ++j) {
                int end = j + i;
                for (int k = j + 1; k <= end; ++k) {
                    char X = input[j];
                    char Y = input[k - 1];
                    char Z = input[k];
                    if (isupper(X) && productions[X - 'A'][0] != '\0' && (productions[X - 'A'][1] == '\0' || productions[X - 'A'][1] == Z)) {
                        dp[j][end] |= (dp[j][k - 1] && dp[k][end]);
                    } else if (isTerminal(X) && X == Y) {
                        dp[j][end] = true;
                    }
                }
            }
        }

        return dp[0][n];
    }
};

int main() {
    RegularGrammarParser parser('S'); // Start symbol is 'S'
    parser.addProduction('S', "aS"); // Example production: S -> aS
    parser.addProduction('S', "b");  // Example production: S -> b

    string input;
    cout << "Enter input string: ";
    cin >> input;

    if (parser.parseString(input)) {
        cout << "Input string belongs to the language generated by the regular grammar." << endl;
    } else {
        cout << "Input string does not belong to the language generated by the regular grammar." << endl;
    }

    return 0;
}

