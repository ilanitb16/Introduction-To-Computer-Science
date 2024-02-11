/******************************************
*Student name: Ilanit Berditchevski
*Student ID: 322453200
*Exercise name: ex5
******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// declare commonly used values to avoid repetition in the code

// letters in the ABC for phonebook
#define LETTER_COUNT 26

// maximum word length (given in the exercise)
#define MAX_WORD_LENGTH 10

#define PLACE_HOLDER_LENGTH 11

// check if variables exist or not
#define NOT_EXISTS 0
#define NAME_EXISTS 1
#define PHONE_EXISTS 2

// determine what to do next in the code
#define EQUAL 0
#define DELETE_NEXT 1
#define DO_NOTHING 0
#define NEWLINE '\n'
#define YES_ANSWER 'y'
#define CONTACT_FOUND 1
#define CONTACT_NOT_FOUND 0

#define LETTER_A_VALUE 65

#define SHOW_MENU 1
#define HIDE_MENU 0

#define ALLOCATION_SUCCESS 1
#define ALLOCATION_FAILED 0

#define BIG_TO_SMALL_RANGE 32

#define BIG_LETTERS_START 65
#define BIG_LETTERS_END 90

#define MENU_NOT_SELECTED 0
#define MENU_ADD_CONTACT 1
#define MENU_DELETE_CONTACT 2
#define MENU_SEARCH_BY_NUMBER 3
#define MENU_SEARCH_BY_NAME 4
#define MENU_UPDATE_PHONE 5
#define MENU_PRINT_PHONE_BOOK 6
#define MENU_EXIT 7

#define STRING_10 "%10s"

#define DELETION_FAILED_MESSAGE "The deletion of the contact has failed!\n"

typedef struct Contact {
    char* firstName;
    char* lastName;
    char* phoneNum;
    struct Contact* next;
} Contact;

/******************************************************************************
 * Function name: toLower()
 * The input: -
 * The output: char
 * The function operation: converts capital letters to small letters and returns
    the converted character
 * ***************************************************************************/
int toLower(int c){
    if(c >= BIG_LETTERS_START && c <= BIG_LETTERS_END){
        return c + BIG_TO_SMALL_RANGE;
    }
    else {
        return c;
    }
}

/******************************************************************************
 * Function name: cleanBuffer()
 * The input: -
 * The output: clears out every value waiting in the buffer
 * The function operation: empties out the values inside the buffer to avoid
    problems for next output
 * ***************************************************************************/
void cleanBuffer(){
    while(getchar() != NEWLINE);
    // end of while loop
}

/******************************************************************************
 * Function name: getFirstLetterIndex()
 * The input: cont pointer to the first character of a given word
 * The output: integer value
 * The function operation: returns the integer value of the first letter
    in the word - 65 in order to calculate the correct index for the array
 * ***************************************************************************/
int getFirstLetterIndex(char const*word) {
    return *word - LETTER_A_VALUE;
}

/******************************************************************************
 * Function name: isNameExists()
 * The input: Contact *phonebook, Contact *contact
 * The output: 1 or 0
 * The function operation: checks for a match between an inputted name and
    an existing contact in the list
 * ***************************************************************************/
int isNameExists(Contact *phonebook, char *firstName, char *lastName){
    if(phonebook == NULL || phonebook->firstName == NULL || phonebook->lastName == NULL){
        return NOT_EXISTS;
    }

    // compare first and last names
    if(EQUAL == strcmp(phonebook->firstName, firstName) &&
        EQUAL == strcmp(phonebook->lastName, lastName)){
        return NAME_EXISTS;
    }

    // if this is not the right contact, check next one if it exists
    return isNameExists(phonebook->next, firstName, lastName);
}

/******************************************************************************
 * Function name: isPhoneExists()
 * The input: Contact *phonebook, char *phoneNum
 * The output: 1 or 0
 * The function operation: checks for a match between an inputted phone number
    and an existing number in the contact list
 * ***************************************************************************/
int isPhoneExists(Contact *phonebook, char *phoneNum){
    // last contact in the list
    if(phonebook == NULL){
        return NOT_EXISTS;
    }

    // found a matching phone number
    if(EQUAL == strcmp(phonebook->phoneNum, phoneNum)){
        return PHONE_EXISTS;
    }

    // if there are more contacts in the list, and we haven't found a match
    if(phonebook->next != NULL){
        return isPhoneExists(phonebook->next, phoneNum);
    }
    else {
        return NOT_EXISTS;
    }
}

/******************************************************************************
 * Function name: freeContact()
 * The input: Contact *contact
 * The output: -
 * The function operation: frees space for all the variables in the contact
 * ***************************************************************************/
void freeContact(Contact *contact){
    free(contact->firstName);
    free(contact->lastName);
    free(contact->phoneNum);
    free(contact);
}

/******************************************************************************
 * Function name: addContact()
 * The input: Contact* contact
 * The output: -
 * The function operation: add a new contact to the end of the phonebook list
 * ***************************************************************************/
void addContact(Contact *phonebook, Contact *contact){
    // if this is the last contact
    if(phonebook->next == NULL){
        phonebook->next = contact;
    }
    else {
        // do the same function with the next contact in the list
        addContact(phonebook->next, contact);
    }
}

/******************************************************************************
 * Function name: allocateMemoryForContact()
 * The input: Contact* contact
 * The output: -
 * The function operation: allocates memory for each pointer inside of contact
 * ***************************************************************************/
int allocateMemoryForContact(Contact* contact){
    contact->firstName = (char*) malloc(sizeof(char) * MAX_WORD_LENGTH);
    contact->lastName = (char*) malloc(sizeof(char) * MAX_WORD_LENGTH);
    contact->phoneNum = (char*) malloc(sizeof(char) * MAX_WORD_LENGTH);

    if(contact->firstName == NULL || contact->lastName == NULL
        || contact->phoneNum == NULL){
        return ALLOCATION_FAILED;
    }
    // set pointer to a next contact
    contact->next = NULL;

    return ALLOCATION_SUCCESS;
}

/******************************************************************************
 * Function name: readContactData()
 * The input: Contact* contact
 * The output: -
 * The function operation: scan details and place them in the contact
 * ***************************************************************************/
void readContactData(Contact* contact){
    printf("Enter a contact details (<first name> <last name> "
           "<phone number>): ");

    scanf(STRING_10, contact->firstName);
    scanf(STRING_10, contact->lastName);
    scanf(STRING_10, contact->phoneNum);

    cleanBuffer();
}

/******************************************************************************
 * Function name: addNewContact()
 * The input: Contact *phonebook[]
 * The output: -
 * The function operation: adds a new contact to phonebook
 * ***************************************************************************/
void addNewContact(Contact *phonebook[]){
    // allocate memory for a new contact
    Contact* contact = (Contact*) malloc(sizeof(Contact));

    if(contact == NULL){
        printf("The addition of the contact has failed!\n");
        return;
    }

    // allocate memory for contact data
    int result = allocateMemoryForContact(contact);

    if(result == ALLOCATION_FAILED){
        printf("The addition of the contact has failed!\n");
        return;
    }

    // read contact data
    readContactData(contact);

    int firstLetterIndex = getFirstLetterIndex(contact->lastName);

    // check if contact exists
    int nameExists = isNameExists(phonebook[firstLetterIndex],
         contact->firstName, contact->lastName);

    // if the name exists print error message
    if(nameExists == NAME_EXISTS){
        printf("The addition of the contact has failed,"
         " since the contact %s %s already exists!\n",
         contact->firstName, contact->lastName);

        // free space dedicated for the contact
        freeContact(contact);
        return;
    }

    // check if phone exists
    for(int i = 0; i < LETTER_COUNT; i++) {
        int phoneExists = isPhoneExists(phonebook[i],
                                        contact->phoneNum);

        if (phoneExists == PHONE_EXISTS) {
            printf("The addition of the contact has failed,"
             " since the phone number %s already exists!\n", contact->phoneNum);
            freeContact(contact);
            return;
        }
    }

    // the contact does not exist. add the contact.
    if(phonebook[firstLetterIndex] == NULL){
        phonebook[firstLetterIndex] = contact;
    }
    else{
        addContact(phonebook[firstLetterIndex], contact);
    }

    printf("The contact has been added successfully!\n");
}

/******************************************************************************
 * Function name: printContactDeletedMessage()
 * The input: -
 * The output: -
 * The function operation: prints message
 * ***************************************************************************/
void printContactDeletedMessage(){
    printf("The contact has been deleted successfully!\n");
}

/******************************************************************************
 * Function name: findAndDelete()
 * The input: Contact pointer, 2 char pointers
 * The output: 1 or 0
 * The function operation: searches for the necessary contact and deletes it
 * ***************************************************************************/
int findAndDelete(Contact* contact, char *firstName, char *lastName){
    // checked all contacts
    if(contact == NULL){
        printf(DELETION_FAILED_MESSAGE);
        return DO_NOTHING;
    }

    // comparing the strings
    if(EQUAL == strcmp(contact->firstName, firstName) && EQUAL == strcmp
        (contact->lastName, lastName)){
        return DELETE_NEXT;
    }

    int result = findAndDelete(contact->next, firstName, lastName);

    // if the contact was found, and it's not the first one
    if(result == DELETE_NEXT){
        // if the contact after the one we must delete is null
        if(contact->next->next == NULL){
            // free the memory allocated for the contact we want to delete
            freeContact(contact->next);
            // set the previous contact's next value to null
            contact->next = NULL;
        }
        else{
            // variable to store the contact after the one we want to delete
            Contact *next = contact->next->next;
            // free the memory allocated for the contact we want to delete
            freeContact(contact->next);
            // set the previous contact's next value to the "next->next" contact
            contact->next = next;
        }

        printContactDeletedMessage();
    }

    return DO_NOTHING;
}

/******************************************************************************
 * Function name: deleteContact()
 * The input: Array of contact pointers
 * The output: -
 * The function operation: checks for each contact in the list if it matches
    the name and the last name
 * ***************************************************************************/
void deleteContact(Contact *phonebook[]){
    printf("Enter a contact name (<first name> <last name>): ");

    // allocates the requested memory and returns pointer
    char *firstName = malloc(sizeof(char) * MAX_WORD_LENGTH);
    char *lastName = malloc(sizeof(char) * MAX_WORD_LENGTH);

    if(firstName == NULL || lastName == NULL){
        printf(DELETION_FAILED_MESSAGE);
        return;
    }

    // scan variables from user
    scanf(STRING_10, firstName);
    scanf(STRING_10, lastName);

    // get the index of the first letter to place in the array
    int firstLetterIndex = getFirstLetterIndex(lastName);

    int nameExists = isNameExists(phonebook[firstLetterIndex],
                                  firstName, lastName);

    // if the name does not exist print error message
    if(nameExists == NOT_EXISTS){
        printf(DELETION_FAILED_MESSAGE);
        // free space dedicated for the data
        free(firstName);
        free(lastName);
        return;
    }

    printf("Are you sure? (y/n) ");
    cleanBuffer();

    char answer;
    scanf("%c", &answer);

    if(toLower(answer) != YES_ANSWER){
        printf("The deletion of the contact has been canceled.\n");
        // memory won't be used so it must be freed
        free(firstName);
        free(lastName);
        return;
    }

    int result = findAndDelete(phonebook[firstLetterIndex],
                               firstName, lastName);

    // For first element DELETE_NEXT means delete the first element
    if(result == DELETE_NEXT){
        Contact *contact = phonebook[firstLetterIndex];

        // if it is the only contact
        if(contact->next == NULL){
            // free memory
            freeContact(contact);
            // no contacts in that index
            phonebook[firstLetterIndex] = NULL;
        }
        // there is more than one contact
        else{
            // stores address of the next contact
            Contact *next = contact->next;
            // free space. hence, delete current contact
            freeContact(contact);
            //set first contact address to next
            phonebook[firstLetterIndex] = next;
        }

        printContactDeletedMessage();
    }

    // free memory that won't be required anymore
    free(firstName);
    free(lastName);
}

/******************************************************************************
 * Function name: findByNumberAndPrint()
 * The input: contact pointers and char pointer
 * The output: pointer of type contact
 * The function operation: checks for each contact in the list if it matches
    the name and the last name
 * ***************************************************************************/
int findByNumberAndPrint(Contact* contact, char *phoneNum) {
    // reached the end of the list, the contact doesn't exist
    if(contact == NULL){
        return CONTACT_NOT_FOUND;
    }

    // comparing between the phone numbers
    if(EQUAL == strcmp(contact->phoneNum, phoneNum)){
        printf("The following contact was found: %s %s %s \n",
               contact->firstName,  contact->lastName, phoneNum);
        return CONTACT_FOUND;
    }

    // keep looking for the contact by passing this function the next contact
    return findByNumberAndPrint(contact->next, phoneNum);
}

/******************************************************************************
 * Function name: searchByNumber()
 * The input: Array of contact pointers
 * The output: -
 * The function operation: checks for each contact in the phonebook if it
    matches the name and the last name
 * ***************************************************************************/
void searchByNumber(Contact *phonebook[]){
    printf("Enter a phone number: ");

    // allocates the requested memory and returns pointer
    char *phoneNum = malloc(sizeof(char) * MAX_WORD_LENGTH);
    scanf(STRING_10, phoneNum);

    // scans each letter and searches for phone number
    for(int i = 0; i < LETTER_COUNT; i++){
        int result = findByNumberAndPrint(phonebook[i], phoneNum);

        // if the contact was found the allocated memory must be freed
        if(result == CONTACT_FOUND){
            free(phoneNum);
            return;
        }
    }

    printf("No contact with a phone number %s was found in the phone"
           " book\n", phoneNum);

    // if the contact was not found the allocated memory must be freed
    free(phoneNum);
}

/******************************************************************************
 * Function name: findByFullName()
 * The input: Contact pointer, 2 char pointers
 * The output: pointer of type Contact
 * The function operation: checks for each contact in the list if it matches
    the name and the last name
 * ***************************************************************************/
Contact* findByFullName(Contact* contact, char *firstName, char *lastName) {
    // if no contact (function scanned all the contacts)
    if(contact == NULL){
        return NULL;
    }

    //if first names and last names are equal, the matching contact was located
    if(EQUAL == strcmp(contact->firstName, firstName) && EQUAL == strcmp
    (contact->lastName, lastName)){
        return contact;
    }

    // return the same function but check for next contact in line
    return findByFullName(contact->next, firstName, lastName);
}

/******************************************************************************
 * Function name: searchByFullName()
 * The input: Array of contact pointers
 * The output: -
 * The function operation: scans the array of contact pointers, if a contact
    with the matching first and last name exists, the function prints out the
    details.
 * ***************************************************************************/
void searchByFullName(Contact *phonebook[]){
    printf("Enter a contact name (<first name> <last name>): ");

    // allocate the requested memory and return pointer
    char *firstName = malloc(sizeof(char) * MAX_WORD_LENGTH);
    char *lastName = malloc(sizeof(char) * MAX_WORD_LENGTH);

    scanf(STRING_10, firstName);
    scanf(STRING_10, lastName);

    // get the index of the first letter in order to place it in the array
    int firstLetterIndex = getFirstLetterIndex(lastName);

    // search for the contact by going over all contacts with same index letter
    Contact *contact = findByFullName
            (phonebook[firstLetterIndex], firstName, lastName);

    // The function returned NULL => no such contact
    if(contact == NULL) {
        printf("No contact with a name %s %s was found in the phone book\n",
               firstName, lastName);
    }
    else{
        printf("The following contact was found: %s %s %s \n",
               contact->firstName, contact->lastName, contact->phoneNum);
    }
    // freeing the space allocated for the variables
    free(firstName);
    free(lastName);
}

/******************************************************************************
 * Function name: updatePhoneNumber()
 * The input: Array of contact pointers
 * The output: -
 * The function operation: scans the array of contact pointers, if a contact
    with the matching first and last name exists, and this phone number is not
    taken, the phone number is updated.
 * ***************************************************************************/
void updatePhoneNumber(Contact *phonebook[]){
    printf("Enter a contact name (<first name> <last name>): ");

    // allocates the requested memory and returns pointer
    char *firstName = malloc(sizeof(char) * MAX_WORD_LENGTH);
    char *lastName = malloc(sizeof(char) * MAX_WORD_LENGTH);

    if(firstName == NULL || lastName == NULL){
        printf("The update of the contact has failed!\n");
        return;
    }

    scanf(STRING_10, firstName);
    scanf(STRING_10, lastName);

    // get the index of the first letter in order to place it in the array
    int firstLetterIndex = getFirstLetterIndex(lastName);

    // search for the contact in the phonebook
    Contact *contact = findByFullName(phonebook[firstLetterIndex],
                                      firstName, lastName);

    // The function returned NULL => no such contact
    if(contact == NULL) {
        printf("No contact with a name %s %s was found in the phone book\n",
               firstName, lastName);
    }
    else {
        printf("The following contact was found: %s %s %s\n", contact->firstName, contact->lastName, contact->phoneNum);
    }

    // free the space we dedicated for the variables
    free(firstName);
    free(lastName);

    if(contact == NULL) {
        return;
    }

    cleanBuffer();
    printf("Enter the new phone number: ");

    // allocate the requested memory and return pointer
    char *phoneNum = malloc(sizeof(char) * MAX_WORD_LENGTH);

    if(phoneNum == NULL){
        printf("The update of the contact has failed!\n");
        return;
    }

    scanf(STRING_10, phoneNum);

    // check if phone exists
    for(int i = 0; i < LETTER_COUNT; i++) {
        int phoneExists = isPhoneExists(phonebook[i], phoneNum);

        if (phoneExists == PHONE_EXISTS) {
            printf("The update of the contact has failed, since the phone"
                   " number %s already exists!\n",
                   phoneNum);
            // free the space we dedicated for the variable
            free(phoneNum);
            return;
        }
    }

    // freeing the memory of the previous phone number
    free(contact->phoneNum);

    // setting new phone number
    contact->phoneNum = phoneNum;
    printf("The contact has been updated successfully!\n");
    cleanBuffer();
}

/******************************************************************************
 * Function name:printFormattedContact
 * The input: pointer of type contact
 * The output: -
 * The function operation: gets the details from the given contact and prints
    them out to the screen according to the necessary format
 * ***************************************************************************/
void printFormattedContact(Contact *contact){
    printf("%-*s", PLACE_HOLDER_LENGTH, contact->firstName);
    printf("%-*s", PLACE_HOLDER_LENGTH, contact->lastName);
    printf("%-*s\n", PLACE_HOLDER_LENGTH, contact->phoneNum);
}

/******************************************************************************
 * Function name:printContact()
 * The input: pointer of type contact
 * The output: -
 * The function operation: gets the details from the given contact and prints
    them out to the screen. Then prints the next contact's details
 * ***************************************************************************/
void printContact(Contact *contact){
    // this is the last contact
    if(contact->next == NULL){
        printFormattedContact(contact);
    }
    else{
        printContact(contact->next);
        printFormattedContact(contact);
    }
}

/******************************************************************************
 * Function name:printPhoneBook()
 * The input: Array of contact pointers
 * The output: -
 * The function operation: scans the array of contact pointers and prints out
    each contact for all alphabet letters
 * ***************************************************************************/
void printPhoneBook(Contact *phonebook[]){
    for(int i = 0; i < LETTER_COUNT; i++){

        if(phonebook[i] != NULL){
            printContact(phonebook[i]);
        }
    }
}

/******************************************************************************
 * Function name:printMenu()
 * The input: -
 * The output: prints to the console
 * The function operation: prints out all the options of the menu to the screen
 * ***************************************************************************/
void printMenu(){
    printf("Welcome to the phone book manager!\n");
    printf("Choose an option:\n");
    printf("1. Add a new contact to the phone book.\n");
    printf("2. Delete a contact from the phone book.\n");
    printf("3. Find a contact in the phone book by phone number.\n");
    printf("4. Find a contact in the phone book by name.\n");
    printf("5. Update phone number for a contact.\n");
    printf("6. Print phone book.\n");
    printf("7. Exit.\n");
}

/******************************************************************************
 * Function name:initContacts
 * The input: Array of contact pointers
 * The output: -
 * The function operation: initializes the array by going through each cell
    and setting its value to NULL
 * ***************************************************************************/
void initContacts(Contact *phonebook[]){
    for(int i = 0; i < LETTER_COUNT; i++){
        phonebook[i] = NULL;
    }
}

int main() {
//    setbuf(stdout, 0);

    // creating an array of pointers containing contacts in the order of the ABC
    Contact *phonebook[LETTER_COUNT];

    // initializing the contacts, setting default value to NULL
    initContacts(phonebook);

    // variable to contain the chosen option by the user in the menu
    int option = MENU_NOT_SELECTED;

    int menuStatus = SHOW_MENU;

    // while the user doesn't want to exit the program
    while(option != MENU_EXIT){
        // function to print the menu
        if(menuStatus == SHOW_MENU){
            printMenu();
        }

        menuStatus = SHOW_MENU;

        scanf("%d", &option);

        // menu implementation
        switch(option){
            case MENU_ADD_CONTACT:
                addNewContact(phonebook);
                break;

            case MENU_DELETE_CONTACT:
                deleteContact(phonebook);
                break;

            case MENU_SEARCH_BY_NUMBER:
                searchByNumber(phonebook);
                break;

            case MENU_SEARCH_BY_NAME:
                searchByFullName(phonebook);
                break;

            case MENU_UPDATE_PHONE:
                updatePhoneNumber(phonebook);
                break;

            case MENU_PRINT_PHONE_BOOK:
                printPhoneBook(phonebook);
                break;

            case MENU_EXIT:
                printf("Bye!");
                break;

            default:
                menuStatus = HIDE_MENU;
                printf("Wrong option, try again:\n");
        }
    }
}

/******************************************************************************
 *                          WARNINGS IN THE CODE:
 * Clang-Tidy:Function 'functionName' is within a recursive call chain (7 times)
 * Reason for appearance: notifying about the possibility of entering an
    endless loop, because if the termination condition doesn't exist, the code
    will fail. In our case, we have a clear working termination condition which
    insures the loop is not endless.
 *

 * ***************************************************************************/