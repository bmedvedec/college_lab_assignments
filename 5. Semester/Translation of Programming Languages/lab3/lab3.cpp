#include <iostream>
#include <vector>
#include <map>
#include <sstream>
#include <algorithm>

using namespace std;

vector<string> split(string line, char delimiter);
void write(string usageLine, string defineLine, string idn);
void error(string errorLine, string idn);
void zaPetlja();

string output;
vector<string> input, grammars, operators, lineTokens, nextTokens;
map<string, int> vars;           // defined tokens
vector<map<string, int>> scopes; // vector of maps for for loops
int i;
auto it = vars.begin();

int main()
{
    string line;
    while (getline(cin, line) && !cin.eof())
        input.push_back(line);

    if (input.empty())
    {
        cout << "Error: empty input" << endl;
        exit(0);
    }
    else
        input.push_back("EOF");

    grammars = {"<program>", "<lista_naredbi>", "<naredba>", "<naredba_pridruzivanja>", "<za_petlja>", "<E>", "<E_lista>", "<T>", "<T_lista>", "<P>", "$"};

    for (i = 0; i < input.size(); i++)
    {
        lineTokens = split(input[i], ' ');
        if (lineTokens[0] == "EOF")
            break;

        bool inGrammar = find(grammars.begin(), grammars.end(), lineTokens[0]) != grammars.end();
        if (inGrammar)
            continue;

        if (lineTokens[0] == "IDN")
        {
            nextTokens = split(input[i + 1], ' ');
            it = vars.find(lineTokens[2]);
            if (nextTokens.size() == 3 && nextTokens[2] == "=") // idn se nalazi s lijeve strane operatora =
            {
                if (it == vars.end())
                    vars.insert({lineTokens[2], stoi(lineTokens[1])});
                i++;
            }
            else
            {
                if (it == vars.end())
                {
                    error(lineTokens[1], lineTokens[2]);
                }
                else
                {
                    write(lineTokens[1], to_string(it->second), it->first);
                }
            }
        }
        else if (lineTokens[0] == "KR_ZA")
        {
            zaPetlja();
        }
    }

    cout << output;
    return 0;
}

vector<string> split(string line, char delimiter)
{
    vector<string> tokens;
    string token;
    stringstream ss(line);

    // remove leading spaces
    while (ss.peek() == delimiter)
        ss.ignore();

    while (getline(ss, token, delimiter))
        tokens.push_back(token);

    return tokens;
}

void write(string usageLine, string defineLine, string idn)
{
    output += usageLine + " " + defineLine + " " + idn + "\n";
    return;
}

void error(string errorLine, string idn)
{
    cout << output;
    cout << "err " + errorLine + " " + idn + "\n";
    exit(0);
}

void zaPetlja()
{
    map<string, int> forScope;
    auto itVars = vars.begin(), itFor = forScope.begin();
    lineTokens = split(input[++i], ' ');
    itVars = vars.find(lineTokens[2]);
    // bool hidden = itVars == vars.end() ? false : true;
    bool nested = scopes.size() == 0 ? false : true;

    forScope.insert({lineTokens[2], stoi(lineTokens[1])}); // definiraj idn poslije kr_za i prije kr_od
    lineTokens = split(input[++i], ' ');

    while (lineTokens[0] != "KR_AZ")
    {
        if (lineTokens[0] == "IDN")
        {
            itVars = vars.find(lineTokens[2]);
            itFor = forScope.find(lineTokens[2]);
            nextTokens = split(input[i + 1], ' ');
            if (nextTokens.size() == 3 && nextTokens[2] == "=")
            {
                if (itVars == vars.end() && itFor == forScope.end())
                    forScope.insert({lineTokens[2], stoi(lineTokens[1])});
                i++;
            }
            else
            {
                if (itVars == vars.end() && itFor == forScope.end())
                {
                    error(lineTokens[1], lineTokens[2]);
                }
                else
                {
                    if (itFor != forScope.end())
                        write(lineTokens[1], to_string(itFor->second), itFor->first);
                    else
                        write(lineTokens[1], to_string(itVars->second), itVars->first);
                }
            }
        }
        else if (lineTokens[0] == "KR_OD" || lineTokens[0] == "KR_DO")
        {
            do
            {
                lineTokens = split(input[++i], ' ');
            } while (find(grammars.begin(), grammars.end(), lineTokens[0]) != grammars.end());

            if (lineTokens[0] == "IDN")
            {
                itVars = vars.find(lineTokens[2]);
                itFor = forScope.find(lineTokens[2]);
                if (itVars == vars.end() && itFor == forScope.end())
                {
                    error(lineTokens[1], lineTokens[2]);
                }
                else
                {
                    if (itFor != forScope.end()) // neki idn je jednak pocetnom definiranom u za petlji ili nije definiran uopce
                    {
                        error(lineTokens[1], lineTokens[2]);
                    }
                    else
                    {
                        write(lineTokens[1], to_string(itVars->second), itVars->first);
                    }
                }
            }
        }
        else if (lineTokens[0] == "KR_ZA")
        {
            scopes.push_back(forScope);
            zaPetlja();
        }

        lineTokens = split(input[++i], ' ');
    }

    if (nested)
        scopes.pop_back();
    return;
}