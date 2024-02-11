
/******************************************
*Student name: Ilanit Berditchevski
*Student ID: 322453200
*Exercise name: ex3
******************************************/

#include <stdio.h>
#include <math.h>

// use global variable to keep an operator
char nextChar;

/*****************************************************************************
 * Function name:readVariable
 * The input: variable of type char
 * The output: returns char
 * The function operation: validates the variable, changes it to the
 right value and changes the value of the operation accordingly in the code
 * **************************************************************************/
int readVariable(){
    // get next char
    int c = getchar();

    // verifying if the given variable is a letter by checking the ascii value of the char
    if(c >= 65 && c <= 90) {
        // increase the value to match the small letters ascii code.
        c += 32;
        // read next char into global variable
        nextChar = (char)getchar();
        return c;
    }

    // checking if the char is a small letter.
    if(c >= 97 && c <= 122){
        // read next char into global variable
        nextChar = (char)getchar();
        return c;
    }

    int count = 1; // to correctly place the digit in its position
    double multiplier = 0.1; //
    double number = 0;

    // checking if the char is  a number
    if(c >= 48 && c <= 57) {
        // while the chars are numbers
        while (c >= 48 && c <= 57) {
            // get the real value of the number (not ascii), multiply
            // accordingly to get the number in the correct order
            number += (c - 48) * multiplier;
            multiplier /= 10;
            count *= 10;

            // read next char into referenced variable
            c = getchar();
        }

        // read next char into global variable
        // if the numbers are over, the next char should be an operator
        nextChar = (char)c;

        // convert double number to integer
        return (int)(number * count);
    }

    return -1;
}

/******************************************************************************
 * Function name:calculate
 * The input: 3 variables of type char
 * The output: returns int
 * The function operation: returns 1 if the statement is true and 0 if false
 * ***************************************************************************/

int calculate(char compareOperation, int var1, int var2) {
    switch (compareOperation) {
        case '=':
            // if true return 1, else 0
            return (var1 == var2) ? 1 : 0;

        case '>':
            // if true return 1, else 0
            return (var1 > var2) ? 1 : 0;

        case '<':
            // if true return 1, else 0
            return (var1 < var2) ? 1 : 0;

        default:
            return -1;
    }
}

/*****************************************************************************
 * Function name:LogicalStatementCalculator
 * The input: none
 * The output: printf
 * The function operation: determines if a given statement is true or false
 * ***************************************************************************/

int LogicalStatementCalculator(){
    // (variable, operation, variable), operation2: & or |
    // The reason for using these global operators: initialization within the
    // while will change their value, which should be stored in order to put it to use
    // in the calculation process
    char compareOperation, logicalOperator = ' ';
    char c = ' ';
    int var1, var2, statementValue = -1; // -1 = not initialized, 0 = false, 1 = true

    printf("\n%s", "Please write your logical statement: ");
    scanf("%c", &c);

    // read next char into referenced variable
    c = (char)getchar();

    while(c != '\n' && c != ' '){
        nextChar = ' ';

        if(c == '&' || c == '|') {
            logicalOperator = c;
            // read next char into referenced variable
            c = (char)getchar();
        }

        // doesn't include operator not ~
        int includeNot = 0;

        if(c =='~'){
            includeNot = 1;
            // read next char into referenced variable
            c = (char)getchar();
        }

        if(c != '(') {
            printf("You have a syntax error in your statement.\n");
            return 0;
        }

        // get the variable value
        var1 = readVariable();

        if(var1 == -1){
            printf("You have a syntax error in your statement.\n");
            return 0;
        }

        // get the operation after the character
        compareOperation = nextChar;

        // compare operator verification
        if(compareOperation != '=' && compareOperation != '>' && compareOperation != '<'){
            printf("You have a syntax error in your statement.\n");
            statementValue = -1;
            return 0;
        }

        //get the next character
        var2 = readVariable();

        if(var2 == -1){
            printf("You have a syntax error in your statement.\n");
            return 0;
        }

        if(nextChar != ')') {
            printf("You have a syntax error in your statement.\n");
            return 0;
        }

        // get the result of the statement
        int result = calculate(compareOperation, var1, var2);

        // if the statement includes a NOT, change result
        if(includeNot) {
            result = !result;
        }

        // if it is the first statement, set value to result
        if(statementValue == -1){
            statementValue = result;
        }
        else {
            // calculate the final value of the statements and insert it into statementValue
            switch(logicalOperator) {
                case '&':
                    statementValue = statementValue & result;
                    break;

                case '|':
                    statementValue = statementValue | result;
                    break;

                // if not both cases
                default:
                    printf("You have a syntax error in your statement.\n");
                    return 0;
            }
        }

        // read next char into referenced variable
        c = (char)getchar();
    }  // end of while loop

    // print out the statement
    switch(statementValue) {
        case 0:
            printf("%s", "The statement is false.\n");
            break;
        case 1:
            printf("%s", "The statement is true.\n");
            break;
        default:
            // do nothing
            break;
    }

    return 1;
}

/******************************************************************************
 * Function name:CountDigit
 * The input: 2 integer variables
 * The output: returns int
 * The function operation: counts the appearance of a digit in a given number
 * ***************************************************************************/

int CountDigit(int number, int digit){
    if(number == 0)
        return 0;

    // if we found the digit
    if(number%10 == digit) {
        return 1 + CountDigit(number/10, digit) ;
    }

    // if the digit wasn't found
    return CountDigit(number/10, digit);
}

/******************************************************************************
 * Function name:printMenu
 * The input: none
 * The output: prints out 5 strings
 * The function operation: prints out to the screen the menu of the program
 * **************************************************************************/

void printMenu(){
    printf("%s\n","Choose an option:");
    printf("\t%s\n","1: Logical Statement Calculator");
    printf("\t%s\n","2: Count digit in a number");
    printf("\t%s\n","3: GCD Calculator");
    printf("\t%s\n","4: Exit");
}

/******************************************************************************
 * Function name:GCD
 * The input: 2 integers
 * The output: returns int
 * The function operation:finds the greatest common divisor, shows the steps
 * ***************************************************************************/

int GCD(int num1, int num2){

   if(num2 == 0)
       return num1;

   int d = (num1 / num2); // get the maximum amount of times num2 fits in num1

   // solving problem: 201/200 = 0 => num2*0 +1 = num1
   if(d == 0 && num1 - num2 > 0){
       d = 1;
   }

   // printout the steps
   printf("%d%c%d%c%d %c %d ", num2, '*', d,
          '+', num1-d*num2, '=', num1);

   printf("(%s%d, %s%d)\n", "num1=", num1, "num2=", num2);

   return GCD( num2,num1-d*num2);
}

int main() {
    setbuf(stdout, 0);

    // Variable for: the selected option
    int option = 0;
    int num1 = 0, num2 = 0;

    // Variables for: number and digit to count the appearances
    int number, digit;
    int result;
    int exit = 0;

    // while the user doesn't press exit
    while(exit == 0){
        printMenu();
        scanf("%d", &option);

        switch (option){
            case 1:
                result = LogicalStatementCalculator();

                if(result == 0){
                    int c = getchar();
                    while(c != 32){
                        c = getchar();
                    }
                }
                break;

            case 2:
                printf("\n%s", "Enter a number and a digit: ");
                scanf("%d %d", &number, &digit);

                if(number < 0 || digit < 0 || digit > 9){
                    printf("%s\n","You should stay positive,"
                                " and so should your input.");
                    break;
                }

                if(number == 0 && digit == 0)
                    printf("%s %d %s %d %s %d\n","The digit", digit, "appears",
                           1, "times in the number", number);
                else
                    printf("%s %d %s %d %s %d\n","The digit", digit, "appears",
                           CountDigit(number, digit), "times in the number", number);
                break;

            case 3:
                printf("\n%s", "Enter two positive numbers: ");
                scanf("%d %d", &num1, &num2);

                if(num1 < 0 || num2 < 0){
                    printf("%s\n","You should stay positive,"
                                " and so should your input.");
                    break;
                }
                if(num1==0 && num2 != 0){
                    printf("%s%d", "GCD = ", num2);
                }
                if(num1 != 0 && num2 == 0){
                    printf("%s%d\n", "GCD = ", num1);
                }
                else{
                    printf("%s %d\n","GCD =", GCD((int)fmax(num1, num2), (int)fmin(num1, num2)));
                }
                break;
            case 4:
                printf("%s", "So Long, and Thanks for All the Fish!\n");
                exit = 1;
                break;

            default:
                printf("Fool of a Took!\n");
                printf("This is a serious journey, not a hobbit walking-party.\n");
                printf("Throw yourself in next time, and then you will be no further nuisance.\n");
                getchar();
                break;
        }
    }

    return 0;
}

/******************************************************************************
 *                          WARNINGS IN THE CODE:
 * Clang-Tidy: Function 'CountDigit' is within a recursive call chain
 * Reason:Remind about the recursive function and avoid a never ending loop

 * Clang-Tidy: Function 'GCD' is within a recursive call chain
 * Reason:Remind about the recursive function and avoid a never ending loop

 * Clang-Tidy: 'scanf' used to convert a string to an integer value, but
 function will not report conversion errors; consider using 'strtol'
 instead
 * Reason: worry about the user inserting the wrong value.Solution: validate
 each value after its converted to integer.
 * ***************************************************************************/