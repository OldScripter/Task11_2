#include <iostream>

bool checkSymbols(char c, bool isLeftPartOfEmail)
{
    if (c >= '0' && c <= '9' ||
        c >= 'a' && c <='z' ||
        c >= 'A' && c <='Z' ||
        c == '-' ||
        c == '.' ||
        c == '@')
    {
        return true;
    }
    else if (isLeftPartOfEmail)
    {
        std::string symbols = "!#$%&'*+-/=?^_`{|}~";
        for (int i = 0; i < symbols.length(); i++)
        {
            if (c == symbols[i]) return true;
        }
        return false;
    }
    else
    {
        return false;
    }
}

bool checkEmailCorrectness(std::string email)
{
    //@ detecting:
    bool dogIsFound = false;
    int leftPartLength = 0;
    int rightPartLength = 0;
    for (int i = 0; i < email.length(); i++)
    {
        if (email[i] == '.')
        {
            if (i == 0) return false;                                           // first dot detected
            else if (email[i] == email[email.length()-1]) return false;         // last dot detected
            else if (email[i-1] == '.') return false;                           // two dots in a row detected
        }
        else if (email[i] == '@')
        {
            if (dogIsFound) return false;                                       // second '@' detected;
            else dogIsFound = true;
        }
        else if (!checkSymbols(email[i], !dogIsFound)) return false;            // bad symbols found
        else if (dogIsFound)
        {
            rightPartLength++;
            if (rightPartLength > 63) return false;                             // right part symbols limit reached
        }
        else if (!dogIsFound)
        {
            leftPartLength++;
            if (leftPartLength < 1 || leftPartLength > 64) return false;        // left part symbols limit reached
        }
    }
    if (!dogIsFound) return false;                                              // no '@' is found

    return true;                                                                // no deviation is found
}


int main() {

    std::string input;
    while (true)
    {
        std::cout << "Please enter the email or 'q' to exit: ";
        std::getline(std::cin, input);
        //std::cin >> input;
        if (input == "q")
        {
            break;
        }
        else
        {
            if (checkEmailCorrectness(input)) std::cout << "Email is correct\n";
            else std::cout << "Email is NOT correct\n";
        }
    }
    std::cout << "Exit program.\n";

    return 0;
}
