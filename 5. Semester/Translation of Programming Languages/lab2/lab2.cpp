#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void program();
void lista_naredbi();
void lista_naredbi_epsilon();
void naredba();
void naredba_pridruzivanja();
void za_petlja();
void E();
void E_lista();
void E_lista_epsilon();
void T();
void T_lista();
void T_lista_epsilon();
void P();

bool in_array(string needle, vector<string> haystack);
void indentation(int depth);
void Error(bool inputEmpty);

string type, output;
vector<string> input, haystack;
int i, depth = 0;

int main() 
{
    string line;

    while (getline(cin, line) && !cin.eof())
        input.push_back(line);

    if (input.empty())
        Error(true);

    input.push_back("EOF");

    for (i = 0; i < input.size(); i++)
    {
        type = input[i].substr(0, input[i].find(' '));

        haystack = {"IDN", "KR_ZA", "EOF"};

        if (in_array(type, haystack))
            program();
        else
            Error(false);
    }
    cout << output;
    return 0;
}

void program()
{
    output += "<program>\n";
    haystack = {"IDN", "KR_ZA", "KR_AZ", "EOF"};
    if (in_array(type, haystack))
        lista_naredbi();
    else
        Error(false);

    return;
}

void lista_naredbi()
{
    indentation(++depth);
    output += "<lista_naredbi>\n";
    haystack = {"IDN", "KR_ZA"};
    if (in_array(type, haystack))
    {
        naredba();
        depth--;
        lista_naredbi();
    }
    else if (type == "KR_AZ" || type == "EOF") 
        lista_naredbi_epsilon();

    depth--;
    return;
}

void lista_naredbi_epsilon()
{
    indentation(++depth);
    output += "$\n";
    depth--;
    return;
}

void naredba()
{
    indentation(++depth);
    output += "<naredba>\n";
    if (type == "IDN")
        naredba_pridruzivanja();
    else if (type == "KR_ZA")
        za_petlja();
    else
        Error(false);

    depth--;
    return;
}

void naredba_pridruzivanja()
{
    indentation(++depth);
    output += "<naredba_pridruzivanja>\n";
    if (type == "IDN")
    {
        indentation(++depth);
        output += input[i] + "\n";
        type = input[++i].substr(0, input[i].find(' '));
        if (type == "OP_PRIDRUZI")
        {
            indentation(depth);
            output += input[i] + "\n";
            type = input[++i].substr(0, input[i].find(' '));
            E();
        }
        else
            Error(false);
    }
    else
        Error(false);

    depth--;
    return;
}

void za_petlja()
{
    indentation(++depth);
    output += "<za_petlja>\n";
    if (type == "KR_ZA")
    {
        indentation(++depth);
        output += input[i] + "\n";
        type = input[++i].substr(0, input[i].find(' '));
        if (type == "IDN")
        {
            indentation(depth);
            output += input[i] + "\n";
            type = input[++i].substr(0, input[i].find(' '));
            if (type == "KR_OD")
            {
                indentation(depth);
                output += input[i] + "\n";
                type = input[++i].substr(0, input[i].find(' '));
                haystack = {"IDN", "BROJ", "OP_PLUS", "OP_MINUS", "L_ZAGRADA"};
                if (in_array(type, haystack))
                   E();
                else
                    Error(false);

                if (type == "KR_DO")
                {
                    indentation(depth);
                    output += input[i] + "\n";
                    type = input[++i].substr(0, input[i].find(' '));
                    haystack = {"IDN", "BROJ", "OP_PLUS", "OP_MINUS", "L_ZAGRADA"};
                    if (in_array(type, haystack))
                        E();
                    else
                        Error(false);

                    haystack = {"IDN", "KR_ZA", "KR_AZ", "EOF"};
                    if (in_array(type, haystack))
                    {
                        depth--;
                        lista_naredbi();
                        if (type == "KR_AZ")
                        {
                            indentation(++depth);
                            output += input[i] + "\n";
                            type = input[++i].substr(0, input[i].find(' '));
                        }
                        else
                            Error(true);
                    }
                    else
                        Error(false);
                }
                else
                    Error(false);
            }
            else
                Error(false);
        }
        else
            Error(false);
    }
    else
        Error(false);

    depth--;
    return;
}

void E()
{
    indentation(depth);
    output += "<E>\n";
    haystack = {"IDN", "BROJ", "OP_PLUS", "OP_MINUS", "L_ZAGRADA"};
    if (in_array(type, haystack))
    {        
        T();
        haystack = {"OP_PLUS", "OP_MINUS", "IDN", "KR_ZA", "KR_DO", "KR_AZ", "D_ZAGRADA", "EOF"};
        if (in_array(type, haystack))
            E_lista();
        else 
            Error(false);
    }
    else
        Error(false);
}

void E_lista()
{
    indentation(++depth);
    output += "<E_lista>\n";
    haystack = {"IDN", "KR_ZA", "KR_DO", "KR_AZ", "D_ZAGRADA", "EOF"};
    if (type == "OP_PLUS" || type == "OP_MINUS")
    {
        indentation(++depth);
        output += input[i] + "\n";
        type = input[++i].substr(0, input[i].find(' '));
        haystack = {"IDN", "BROJ", "OP_PLUS", "OP_MINUS", "L_ZAGRADA"};
        if (in_array(type, haystack))
            E();
        else
            Error(false);
            
        depth--;
    }
    else if (in_array(type, haystack))
        E_lista_epsilon();
    else
        Error(false);
 
    depth--;
    return;
}

void E_lista_epsilon()
{
    indentation(++depth);
    output += "$\n";
    depth--;
    return;
}

void T()
{
    indentation(++depth);
    output += "<T>\n";
    haystack = {"IDN", "BROJ", "OP_PLUS", "OP_MINUS", "L_ZAGRADA"};
    if (in_array(type, haystack))
    {
        P();
        haystack = {"OP_PUTA", "OP_DIJELI", "OP_PLUS", "OP_MINUS", "IDN", "KR_ZA", "KR_DO", "KR_AZ", "D_ZAGRADA", "EOF"};
        if (in_array(type, haystack))
            T_lista();
        else
            Error(false);
    }
    else
        Error(false);

    depth--;
    return;
}

void T_lista()
{
    indentation(++depth);
    output += "<T_lista>\n";
    haystack = {"OP_PLUS", "OP_MINUS", "IDN", "KR_ZA", "KR_DO", "KR_AZ", "D_ZAGRADA", "EOF"};
    if (type == "OP_PUTA" || type == "OP_DIJELI")
    {
        indentation(++depth);
        output += input[i] + "\n";
        type = input[++i].substr(0, input[i].find(' '));
        haystack = {"IDN", "BROJ", "OP_PLUS", "OP_MINUS", "L_ZAGRADA"};
        if (in_array(type, haystack))
        {
            depth--;
            T();
            depth++;
        }
        else
            Error(false);
        depth--;
    }
    else if (in_array(type, haystack))
        T_lista_epsilon();
    else
        Error(false);

    depth--;
    return;
}

void T_lista_epsilon()
{
    indentation(++depth);
    output += "$\n";
    depth--;
    return;
}

void P()
{
    indentation(++depth);
    output += "<P>\n";
    if (type == "OP_PLUS" || type == "OP_MINUS")
    {
        indentation(++depth);
        output += input[i] + "\n";
        type = input[++i].substr(0, input[i].find(' '));
        haystack = {"IDN", "BROJ", "OP_PLUS", "OP_MINUS", "L_ZAGRADA"};
        if (in_array(type, haystack))
        {
            depth--;
            P();
        }
        else
            Error(false);
    }
    else if (type == "L_ZAGRADA")
    {
        indentation(++depth);
        output += input[i] + "\n";
        type = input[++i].substr(0, input[i].find(' '));
        haystack = {"IDN", "BROJ", "OP_PLUS", "OP_MINUS", "L_ZAGRADA"};
        if (in_array(type, haystack))
            E();
        else
            Error(false);

        if (type == "D_ZAGRADA")
        {
            indentation(depth);
            output += input[i] + "\n";
            type = input[++i].substr(0, input[i].find(' '));
        }
        else
            Error(false);
        depth--;
    }
    else if (type == "IDN" || type == "BROJ")
    {
        indentation(++depth);
        output += input[i] + "\n";
        type = input[++i].substr(0, input[i].find(' '));
        depth--;
    }
    else
        Error(false);

    depth--;
    return;
}

bool in_array(string needle, vector<string> haystack)
{
    return find(haystack.begin(), haystack.end(), needle) != haystack.end();
}

void indentation(int depth)
{
    string temp;
    for (int i = 0; i < depth; i++)
        temp += " ";

    output += temp;  
    return;
}

void Error(bool inputEmpty)
{
    if (inputEmpty || type == "EOF")
        cout << "err kraj" << endl;
    else
        cout << "err " + input[i] << endl;

    exit(0);
}