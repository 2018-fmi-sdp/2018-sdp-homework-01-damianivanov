#include <iostream>

#include <cstring>
#include <cstdlib>

using namespace std;

// The code works
// The code is ugly
//  - there is repetition
//  - if you want to add a new command you need to touch the code in several places
//  - all is in one function and is hard to read
//  - your homework is to fix all that!

int main()
{
    char line[1000];
    char prompt[100] = ">";
    int registers[10] = {};

    while(true)
    {
        cout << prompt << " ";
        cin.getline(line, 1000);
        if (strcmp(line, "quit") == 0) {
            break;
        } else if (strcmp(line, "help") == 0) {
            cout << "Supported commands:" << endl
                 << "quit" << endl
                 << "cmd.prompt" << endl
                 << "asm.reg.set" << endl
                 << "asm.reg.add" << endl
                 << "asm.reg.dbg" << endl
                 << "help" << endl;
        } else if (strncmp(line, "cmd.prompt ", strlen("cmd.prompt ")) == 0) {
            char* argument = line + strlen("cmd.prompt ");
            // "cmd.prompt %asd" => argument="%asd"
            // "cmd.prompt ?1" => argument="?1"
            if (strlen(argument) < 100 && *argument != '\0')
                strcpy(prompt, argument);
        } else if (strncmp(line, "asm.reg.set ", strlen("asm.reg.set ")) == 0) {
            char* arguments = line + strlen("asm.reg.set ");
            // "asm.reg.set 0 +15" => arguments="0 +15"
            // "asm.reg.set 9 -115" => arguments="9 -115"
            if (*arguments < '0' || *arguments > '9' || arguments[1] != ' ') {
                // invalid register - must be just one digit
                cout << "ERROR" << endl;
                continue; // next loop of the repl
            }
            int reg = *arguments - '0';
            arguments += 2;
            // "0 +15" => "+15"
            // "9 -115" => "-115"
            char* endOfNumber = NULL;
            long number = strtol(arguments, &endOfNumber, 0);
            if (!endOfNumber || *endOfNumber != '\0' //should point to the '\0' after the number in arguments
                || number < -100 || number > 100) { 
                cout << "ERROR" << endl;
                continue;
            }
            registers[reg] = number;
            cout << "OK" << endl;
        } else if (strncmp(line, "asm.reg.add ", strlen("asm.reg.add ")) == 0) {
            char* arguments = line + strlen("asm.reg.set ");
            // "asm.reg.add 0 1 2" => arguments="0 1 2"
            if (*arguments < '0' || *arguments > '9' || arguments[1] != ' ') {
                // invalid register - must be just one digit
                cout << "ERROR" << endl;
                continue; // next loop of the repl
            }
            int reg1 = *arguments - '0';
            arguments += 2;
            // "0 1 2" => "1 2"
            if (*arguments < '0' || *arguments > '9' || arguments[1] != ' ') {
                // invalid register - must be just one digit
                cout << "ERROR" << endl;
                continue; // next loop of the repl
            }
            int reg2 = *arguments - '0';
            arguments += 2;
            
            // "1 2" => "2"
            if (*arguments < '0' || *arguments > '9' || arguments[1] != '\0') {
                // invalid register - must be just one digit at end of string
                cout << "ERROR" << endl;
                continue; // next loop of the repl
            }
            int reg3 = *arguments - '0';
            
            int sum = registers[reg2] + registers[reg3];
            if (sum > 100 || sum < -100) {
                cout << "ERROR: overflow" << endl;
                continue; // next loop of the repl
            }
            
            registers[reg1] = sum;
            cout << "OK" << endl;
            
        } else if (strncmp(line, "asm.reg.dbg", strlen("asm.reg.dbg")) == 0) {
            for (int i=0; i < 10; i++) {
                cout << "REG_" << i << " = " << registers[i] << endl;
            }
            
        } else {
            cout << "Unknown command " << line << endl; 
         }
    }
    return 0;
}
//promqna na red 92 
