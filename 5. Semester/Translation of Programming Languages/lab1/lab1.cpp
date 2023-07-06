#include <iostream>
#include <memory>

using namespace std;

void write(string &output,string &type, int lineNo, string &token)  //zapisi novi token
{
    output += type + ' ' + to_string(lineNo) + ' ' + token + '\n';
    type.clear();
    token.clear();
}

string checkKR(string type, string token)   //provjeri jel IDN zapravo KLJUCNA RIJEC
{
    if (token == "za")
        type = "KR_ZA";
    else if (token == "od")
        type = "KR_OD";
    else if (token == "do")
        type = "KR_DO";
    else if (token == "az")
        type = "KR_AZ";

    return type;
}

int main() {
    string line, token, type, output;
    int lineNo = 0;

    while (getline(cin, line) && !cin.eof())    //ucitavaj liniju po liniju sve dok ne dodes do kraja inputa
    {
        lineNo++;
        for (long unsigned int i = 0; i <= line.length(); i++)    //iteriraj po svim znakovima u liniji
        {
            if (line[i] == '/' && line[i+1] != '\n')    //provjera za komentar
            {
                if (line[i+1] == '/')
                {
                    type.clear();
                    token.clear();
                    break;
                }
            }
            
            if (isalpha(line[i]))   //provjera jel znak slovo
            {
                if (!type.empty() && type != "IDN")     //provjera jel novi znak spada u trenutni ili novi token
                    write(output, type, lineNo, token);
                
                token += line[i];
                type = "IDN";
            }
            else if (isdigit(line[i]))  //provjera jel znak broj
            {
                if (type != "IDN")   //ako je type == IDN onda se broj nadovezuje na trenutni token i type ostaje IDN, inace se mijenja u BROJ
                    type = "BROJ";
                
                token += line[i];
            }
            else    //provjera jel znak jednak nekome od operatora
            {
                if (!type.empty())  //ako type nije prazan, ispisi trenutni token, ali prije toga provjeri jel mozda KR
                {
                    if (type == "IDN")
                        type = checkKR(type, token);
                    
                    write(output, type, lineNo, token);
                }

                bool match = true;
                switch (line[i])
                {
                case '=':
                    type = "OP_PRIDRUZI";
                    break;
                case '+':
                    type = "OP_PLUS";
                    break;
                case '-':
                    type = "OP_MINUS";
                    break;
                case '*':
                    type = "OP_PUTA";
                    break;
                case '/':
                    type = "OP_DIJELI";
                    break;
                case '(':
                    type = "L_ZAGRADA";
                    break;
                case ')':
                    type = "D_ZAGRADA";
                    break;
                default:
                    match = false;
                    break;
                }

                if (match)  //ako je token jedan od operatora, zapisi ga
                {
                    token = line[i];
                    write(output, type, lineNo, token);
                }
            }

            if (line[i] == ' ' || line[i] == '\t' || line[i] == '\n')   //provjera jel znak razmak, tabulator ili kraj reda, ako je zapisi trenutni token
            {
                if (!type.empty())
                {
                    if (type == "IDN")
                        type = checkKR(type, token);

                    write(output, type, lineNo, token);
                }
            }
        }

        if (!type.empty())  //provjera jel ostao zadnji token nespremljen
            write(output, type, lineNo, token);
    }

    cout << output << endl;
    return 0;
}