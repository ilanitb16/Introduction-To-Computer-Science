/******************************************
*Student name: Ilanit Berditchevski
*Student ID: 322453200
*Exercise name: ex3
******************************************/

#include <stdio.h>

// declare commonly used values to avoid repetition in the code
#define X_DIMENSION 4
#define Y_DIMENSION 4
#define Z_DIMENSION 4
#define NEWLINE '\n'
#define EMPTY_CELL '*'
#define PLAYER_X 'X'
#define PLAYER_O 'O'
#define TRUE 1
#define FALSE 0
#define NO_ANSWER 'n'

// declare 3-dimensional array
char arena [X_DIMENSION][Y_DIMENSION][Z_DIMENSION];

/******************************************************************************
 * Function name:initArena()
 * The input: -
 * The output: -
 * The function operation: initializes the array by going through each cell
    and setting its value to ' '
 * ***************************************************************************/
void initArena(){
    // initialize 3-dimensional array
    for(int x = 0; x < X_DIMENSION; x++){
        for(int y = 0; y < Y_DIMENSION; y++){
            for(int z = 0; z < Z_DIMENSION; z++){
                arena[x][y][z] = EMPTY_CELL;
            }
        }
    }
}

/******************************************************************************
 * Function name: getCord()
 * The input: -
 * The output: return the first character after the space
 * The function operation: return the first character after the space
 * ***************************************************************************/
char getCord(){
    // reads char from buffer
    char c = (char)getchar();

    // skip spaces
    if(c == ' '){
        // call until get not a space char
        return getCord();
    }

    return c;
}

/******************************************************************************
 * Function name: printInputIncorrect()
 * The input: -
 * The output: prints out a string to the screen
 * The function operation: prints "Input incorrect."
 * -I did it to avoid errors with the automatic check. If I insert a wrong
    string and something is missing- I can simply fix it in one place
 * ***************************************************************************/
void printInputIncorrect(){
    printf("Input incorrect.\n");
}

/******************************************************************************
 * Function name: printYeet()
 * The input: -
 * The output: prints out a string to the screen
 * The function operation: prints "YEET"
 * -I did it to avoid errors with the automatic check. If I insert a wrong
    string and something is missing- I can simply fix it in one place
 * ***************************************************************************/
void printYeet(){
    printf("YEET");
}

/******************************************************************************
 * Function name: printSpace()
 * The input: -
 * The output: prints out a char to the screen
 * The function operation: prints ' '
 -I did it to avoid errors with the automatic check. Helps keep up with the
    spaces for the automatic check
 * ***************************************************************************/
void printSpace(int pos){
    if(pos != 0){
        printf(" ");
    }
}

/******************************************************************************
 * Function name: gameOver()
 * The input: -
 * The output: prints out chars
 * The function operation: prints the indexes of X and O, also prints them in
   order so we can visually see the victory/ loss
 * ***************************************************************************/
void gameOver(){
    for(int x = 0; x < X_DIMENSION; x++){
        for(int y = 0; y < Y_DIMENSION; y++){
            char values[Z_DIMENSION];

            // for each z, print the indexes
            for(int z = 0; z < Z_DIMENSION; z++){
                printSpace(z);
                printf("(%d %d %d)", x, y, z);
                values[z] = arena[x][y][z];
            }

            // print the values of each cell mentioned above
            for(int z = 0; z < Z_DIMENSION; z++){
                printf(" %c", values[z]);
            }

            printf("\n");
        }

        printf("\n");
    }
}

/******************************************************************************
 * Function name: hasFilledRow1
 * The input: the sign of the player (X or O)
 * The output: returns 1 if true and 0 if false
 * The function operation: checks for each sign if it forms a whole row:
 important note: it scans for rows for the Z dimension
 * ***************************************************************************/
int hasFilledRow1(char sign){
    for(int x = 0; x < X_DIMENSION; x++){
        for(int y = 0; y < Y_DIMENSION; y++){
            // determine if all the cells have the same sign in them
            int hasWrongCell = FALSE;

            // if the sign in that cell doesn't equal to the given sign
            for(int z = 0; z < Z_DIMENSION; z++){
                if(arena[x][y][z] != sign){
                    // change flag to match the result
                    hasWrongCell = TRUE;
                    break;
                }
            }

            // if there is no wrong cell => there is a column
            if(hasWrongCell == FALSE){
                return TRUE;
            }
        }
    }

    return FALSE;
}

/******************************************************************************
 * Function name: hasFilledRow2
 * The input: the sign of the player (X or O)
 * The output: returns 1 if true and 0 if false
 * The function operation: checks for each sign if it forms a whole row:
 important note: it scans for rows for the X dimension
 * ***************************************************************************/
int hasFilledRow2(char sign){
    for(int z = 0; z < Z_DIMENSION; z++){
        for(int y = 0; y < Y_DIMENSION; y++){
            // determine if all the cells have the same sign in them
            int hasWrongCell = FALSE;

            // if the sign in that cell doesn't equal to the given sign
            for(int x = 0; x < X_DIMENSION; x++){
                if(arena[x][y][z] != sign){
                    // change flag to match the result
                    hasWrongCell = TRUE;
                    break;
                }
            }

            // if there is no wrong cell => there is a column
            if(hasWrongCell == FALSE){
                return TRUE;
            }
        }
    }

    return FALSE;
}

/******************************************************************************
 * Function name: hasFilledColumn
 * The input: the sign of the player (X or O)
 * The output: returns 1 if true and 0 if false
 * The function operation: checks for each sign if it forms a whole column
 * ***************************************************************************/
int hasFilledColumn(char sign){
    for(int x = 0; x < X_DIMENSION; x++){
        for(int z = 0; z < Z_DIMENSION; z++){
            // determine if all the cells have the same sign in them
            int hasWrongCell = FALSE;

            // if the sign in that cell doesn't equal to the given sign
            for(int y = 0; y < Y_DIMENSION; y++){
                if(arena[x][y][z] != sign){
                    // change flag => sign doesn't form a whole column
                    hasWrongCell = TRUE;
                    break;
                }
            }

            // if there is no wrong cell => there is a column
            if(hasWrongCell == FALSE){
                return TRUE;
            }
        }
    }

    return FALSE;
}

/******************************************************************************
 * Function name: int hasCrossDiagonal
 * The input: the sign of the player (X or O)
 * The output: returns 1 if true and 0 if false
 * The function operation: checks for 3 dimensional diagonal victory:
 meaning, the diagonal inside of the cube
 * ***************************************************************************/
int hasCrossDiagonal(char sign){
    // determine if all the cells have the same sign in them
    int hasWrongCell = FALSE;

    // check from 0,0,0 to 3,3,3
    for(int pos = 0; pos < X_DIMENSION; pos++){
        if(arena[pos][pos][pos] != sign){
            hasWrongCell = TRUE;
            break;
        }
    }

    // if all the cells have the same sign in them
    if(hasWrongCell == FALSE){
        return TRUE;
    }

    // check from 3,0,0
    hasWrongCell = FALSE;
    for(int pos = 0; pos < X_DIMENSION; pos++){
        if(arena[X_DIMENSION - pos][pos][pos] != sign){
            hasWrongCell = TRUE;
            break;
        }
    }

    // if all the cells have the same sign in them
    if(hasWrongCell == FALSE){
        return TRUE;
    }

    // check from 0,3,0
    hasWrongCell = FALSE;
    for(int pos = 0; pos < X_DIMENSION; pos++){
        if(arena[pos][Y_DIMENSION - pos][pos] != sign){
            hasWrongCell = TRUE;
            break;
        }
    }

    // if all the cells have the same sign in them
    if(hasWrongCell == FALSE){
        return TRUE;
    }

    // check from 0,3,3
    hasWrongCell = FALSE;
    for(int pos = 0; pos < X_DIMENSION; pos++){
        if(arena[pos][Y_DIMENSION - pos][Z_DIMENSION - pos] != sign){
            hasWrongCell = TRUE;
            break;
        }
    }

    // if all the cells have the same sign in them
    if(hasWrongCell == FALSE){
        return TRUE;
    }

    // check from 3,0,3
    hasWrongCell = FALSE;
    for(int pos = 0; pos < X_DIMENSION; pos++){
        if(arena[X_DIMENSION - pos][pos][Z_DIMENSION - pos] != sign){
            hasWrongCell = TRUE;
            break;
        }
    }

    if(hasWrongCell == FALSE){
        return TRUE;
    }

    return FALSE;
}

/******************************************************************************
 * Function name: hasSimpleDiagonal
 * The input: the sign of the player (X or O)
 * The output: returns 1 if true and 0 if false
 * The function operation: checks for 2 dimensional diagonal victory
 * ***************************************************************************/
int hasSimpleDiagonal(char sign){
    int hasWrongCell = FALSE;

    for(int z = 0; z < Z_DIMENSION; z++) {
        // determine if the cells have the same sign
        hasWrongCell = FALSE;

        // check from 0,0,z to 3,3,z: x,y diagonal
        for (int pos = 0; pos < X_DIMENSION; pos++) {
            if (arena[pos][pos][z] != sign) {
                hasWrongCell = TRUE;
                break;
            }
        }

        // if all the cells have the same size
        if(hasWrongCell == FALSE){
            return TRUE;
        }
    }

    for(int z = 0; z < Z_DIMENSION; z++) {
        hasWrongCell = FALSE;

        // check from 3,0,z to 0,3,z: y,x diagonal
        for (int pos = 0; pos < X_DIMENSION; pos++) {
            if (arena[X_DIMENSION - pos][pos][z] != sign) {
                hasWrongCell = TRUE;
                break;
            }
        }

        if(hasWrongCell == FALSE){
            return TRUE;
        }
    }

    for(int y = 0; y < Y_DIMENSION; y++) {
        hasWrongCell = FALSE;

        // check from 0,y,0 to 3,y,3: x,z diagonal
        for (int pos = 0; pos < X_DIMENSION; pos++) {
            if (arena[pos][y][pos] != sign) {
                hasWrongCell = TRUE;
                break;
            }
        }

        if(hasWrongCell == FALSE){
            return TRUE;
        }
    }

    for(int y = 0; y < Y_DIMENSION; y++) {
        hasWrongCell = FALSE;

        // check from 0,y,3 to 3,y,0: z,x diagonal
        for (int pos = 0; pos < X_DIMENSION; pos++) {
            if (arena[pos][y][Z_DIMENSION - pos] != sign) {
                hasWrongCell = TRUE;
                break;
            }
        }

        if (hasWrongCell == FALSE) {
            return TRUE;
        }
    }

    for(int x = 0; x < X_DIMENSION; x++) {
        hasWrongCell = FALSE;

        // check from x,0,0 to x,3,3: y,z diagonal
        for (int pos = 0; pos < X_DIMENSION; pos++) {
            if (arena[x][pos][pos] != sign) {
                hasWrongCell = TRUE;
                break;
            }
        }

        if (hasWrongCell == FALSE) {
            return TRUE;
        }
    }

    for(int x = 0; x < X_DIMENSION; x++) {
        hasWrongCell = FALSE;

        // check from x,0,3 to x,3,0: z,y diagonal

        for (int pos = 0; pos < X_DIMENSION; pos++) {
            if (arena[x][pos][X_DIMENSION - pos] != sign) {
                hasWrongCell = TRUE;
                break;
            }
        }

        if (hasWrongCell == FALSE) {
            return TRUE;
        }
    }

    return FALSE;
}

/******************************************************************************
 * Function name: winnerExists()
 * The input: -
 * The output: prints out the correct string for each given case
 * The function operation: The function calls the functions responsible
    for scanning the rows, columns and diagonals, and prints out the correct
    output if there is a victor.
 * ***************************************************************************/
int winnerExists(){
    // check columns for X
    if(TRUE == hasFilledColumn(PLAYER_X)){
        printf("X is the winner.\n");
        return TRUE;
    }

    // check columns for O
    if(TRUE == hasFilledColumn(PLAYER_O)){
        printf("O is the winner.\n");
        return TRUE;
    }

    // check rows for X
    if(TRUE == hasFilledRow1(PLAYER_X)){
        printf("X is the winner.\n");
        return TRUE;
    }

    // check rows for O
    if(TRUE == hasFilledRow1(PLAYER_O)){
        printf("O is the winner.\n");
        return TRUE;
    }

    if(TRUE == hasFilledRow2(PLAYER_X)){
        printf("X is the winner.\n");
        return TRUE;
    }

    if(TRUE == hasFilledRow2(PLAYER_O)){
        printf("O is the winner.\n");
        return TRUE;
    }

    // check internal diagonal for x
    if(TRUE == hasCrossDiagonal(PLAYER_X)){
        printf("X is the winner.\n");
        return TRUE;
    }

    // check internal diagonal for x
    if(TRUE == hasCrossDiagonal(PLAYER_O)){
        printf("O is the winner.\n");
        return TRUE;
    }

    // check external diagonal for x
    if(TRUE == hasSimpleDiagonal(PLAYER_X)){
        printf("X is the winner.\n");
        return TRUE;
    }

    // check external diagonal for x
    if(TRUE == hasSimpleDiagonal(PLAYER_O)){
        printf("O is the winner.\n");
        return TRUE;
    }

    return FALSE;
}

/******************************************************************************
 * Function name: emptyCellsExist()
 * The input: -
 * The output: 1 if true, 0 if false
 * The function operation: checks if there are empty cells. If there aren't
 the function will print tie.
 * ***************************************************************************/
int emptyCellsExist(){
    // goes over the cells in the arena
    for(int x = 0; x < X_DIMENSION; x++){
        for(int y = 0; y < Y_DIMENSION; y++){
            for(int z = 0; z < Z_DIMENSION; z++){
                if(arena[x][y][z] == EMPTY_CELL){
                    // there are empty cells
                    return TRUE;
                }
            }
        }
    }

    // there aren't empty cells
    printf("Tie.\n");
    return FALSE;
}

/******************************************************************************
 * Function name: isCellAlreadyFilled
 * The input: the coordinates the player used
 * The output: 1 if true, 0 if false
 * The function operation: checks if the move the player made is illegal:
    if the cell was already used, the function returns 1 (true) (yes, the cell
    is already filled), if the cell is empty, it is good for use and the
    function will return 0 (false)
 * ***************************************************************************/
int isCellAlreadyFilled(int x, int y, int z){
    // if cell is empty, it is not taken and good to use
    if(arena[x][y][z] == EMPTY_CELL)
        return FALSE;
    else{
        // print message saying the value was incorrect
        printInputIncorrect();
        return TRUE;
    }
}

/******************************************************************************
 * Function name: convertToDigit
 * The input: the character we scanned from the user
 * The output: the digit
 * The function operation: converts from chat to integer by decreasing the
    ascii value of 0
 * ***************************************************************************/
int convertToDigit(char value){
    return value - 48;
}

/******************************************************************************
 * Function name: isDigit
 * The input: the value we want to check
 * The output: 1 if true, 0 if false
 * The function operation: validates the digit range, checks if the coordinate
   is between 0-3
 * ***************************************************************************/
int isDigit(char value){
    int num = convertToDigit(value);

    if(num >= 0 && num <= 3)
        return TRUE;
    else
        return FALSE;
}

/******************************************************************************
 * Function name: isInputValid
 * The input: gets the coordinates of the X or O placement in the arena
 * The output: 1 if the input is valid, 0 if it isn't
 * The function operation: validates if one of the coordinates in missing,
   and if the coordinates are in the correct range between 0-3, if they aren't,
   we print out the needed message to the screen
 * ***************************************************************************/
int isInputValid(char x, char y, char z){
   // validates if one of the coordinates in missing
    if(x == NEWLINE || y == NEWLINE || z == NEWLINE){
        printInputIncorrect();
        return FALSE;
    }
    //check if the coordinates are in the correct range between 0-3
    if(TRUE == isDigit(x) && TRUE == isDigit(y) && TRUE == isDigit(z)){
        return TRUE;
    }
    else {
        //digits are not in the correct range, then we print Output incorrect.
        printInputIncorrect();
        return FALSE;
    }
}

/******************************************************************************
 * Function name: getNextSign
 * The input: gets the current player (X or O)
 * The output: new player (X or O)
 * The function operation: switches player, if X => O, if O => X to allow
   the game flow, each player gets one move each
 * ***************************************************************************/
char getNextSign(char current){
    // if current player is X, switch to O, else switch to X
    if(current == PLAYER_X)
        return PLAYER_O;
    else
        return PLAYER_X;
}

/******************************************************************************
 * Function name: cleanBuffer()
 * The input: -
 * The output: clears out every value waiting in the buffer
 * The function operation: empties out the values inside the buffer to avoid
    problems for next output
 * ***************************************************************************/
void cleanBuffer(){
    while(getchar() != NEWLINE); // end of while loop
}

int main() {
    setbuf(stdout, 0);
    int exit = FALSE;
    char answer;

    printf("Would you like to start? (y/n)\n");
    scanf("%c", &answer);

    // exit program if got no answer
    if(answer == NO_ANSWER){
        printYeet();
        return FALSE;
    }

    // skip '\n'
    getchar();

    while(exit == FALSE){
        //char c = ' ';
        char sign = PLAYER_X;

        initArena();
        printf("Please enter your game sequence.\n");

        while(1){
            // get the characters
            char cX = getCord();
            char cY = getCord();
            char cZ = getCord();

            if(FALSE == isInputValid(cX, cY, cZ)){
                break;
            }

            // converting from char do digit
            int x = convertToDigit(cX);
            int y = convertToDigit(cY);
            int z = convertToDigit(cZ);

            if(TRUE == isCellAlreadyFilled(x, y, z)){
                break;
            }

            // placing the correct sign in the cube
            arena[x][y][z] = sign;

            // if the winner exists we finish the game
            if(TRUE == winnerExists()){
                gameOver();
                break;
            }

            // if we ran out of cells
            if(FALSE == emptyCellsExist()){
                break;
            }

            // get next player's sign (X or O)
            sign = getNextSign(sign);
        }

        // clear the buffer
        cleanBuffer();
        printf("Would you like to continue? (y/n)\n");
        scanf("%c", &answer);
        getchar(); // skip last '/n'

        if(answer == NO_ANSWER){
            exit = TRUE;
            printYeet();
        }
    }// end of while loop

    return 0;

}

/******************************************************************************
 *                          WARNINGS IN THE CODE:
 * Clang-Tidy: Function 'getCord' is within a recursive call chain
 * Reason for appearance: notifying about the possibility of entering an
    endless loop, because if the termination condition doesn't exist, the code
    will fail. In our case, we have a clear working termination condition which
    insures the loop is not endless.
 * ***************************************************************************/


