#include <stdio.h>
#include <math.h>

char GetHexValue(int remainder)
{
    switch (remainder)
    {
        case 10:
            return 'A';

        case 11:
            return 'B';

        case 12:
            return 'C';

        case 13:
            return 'D';

        case 14:
            return 'E';

        case 15:
            return 'F';
    }
    return ' ';
}

void OctalToHex()
{
    printf("Please enter number in octal base: \n");
    int octal = 0;
    scanf("%d",&octal);

    int length = 0;

    int octal2 = octal;
    while(octal2!=0){
        length++;
        octal2= octal2/10;
    }

    int decimal = 0;
    int digit = 0;
    int numlength = length;
    for(int i =0; i<numlength; i++)
    {
        digit = octal/(pow(10,length-1));
        decimal+= digit * pow(8,i);
        length--;
        octal=octal-(digit*(pow(10,length)));
    }

    int num =decimal;
    int counter = 0;

    while(num !=0)
    {
        num = num/16;
        counter++;
    }

    int quotient = decimal/16;
    int remainder = decimal%16;
    decimal = quotient;

    char hex [counter];
    counter--;
    if(remainder<10)
        hex[counter] = remainder;
    else
    {
        hex[counter] = GetHexValue(remainder);
    }
    counter--;

    while (quotient!=0)
    {
        quotient = decimal/16;
        remainder = decimal%16;
        decimal = quotient;

        if(remainder<10)
            hex[counter] = remainder + '0';
        else{
            switch (remainder)
            {
                case 10:
                    hex[counter] = 'A';

                case 11:
                    hex[counter] = 'B';

                case 12:
                    hex[counter] = 'C';

                case 13:
                    hex[counter] = 'D';

                case 14:
                    hex[counter] = 'E';

                case 15:
                    hex[counter] = 'F';
            }
        }
        counter--;
    }
    for ( int i =0; i<sizeof(hex)/sizeof (hex[0]); i++)
    {
        if(hex[i] == 'A' || hex[i] == 'B' || hex[i] == 'C' || hex[i] == 'D' || hex[i] == 'E' || hex[i] == 'F')
            printf("%c", hex[i]);
        else
            printf("%d", hex[i]);
    }
} //שאלה 1

void FromDecimalToBinary()
{
    int decimal =0;
    int num = 0;
    printf("Enter a non negative decimal number: ");
    scanf("%d", &decimal);

    num =decimal;
    int counter = 0;

    while(num !=0)
    {
        num = num/2;
        counter++;
    }
    num = decimal;

    int quotient = decimal/2;
    int remainder = decimal%2;
    decimal = quotient;

    char newNum [counter];
    counter--;
    if(remainder>=10)
        newNum[counter] = GetHexValue(remainder);
    else
        newNum[counter] = remainder;

    counter--;

    while (quotient!=0)
    {
        quotient = decimal/2;
        remainder = decimal%2;
        decimal = quotient;

        if(remainder>=10)
            newNum[counter] = GetHexValue(remainder);
        else
            newNum[counter] = remainder;

        counter--;
    }

    int result = 0;
    int count = 1;
    int check = 0;
    for ( int i =0; i<(sizeof(newNum)/sizeof (newNum[0])); i++)
    {
        result  +=(int)newNum[i]*count;
        count*=10;
        if(i==(sizeof(newNum)/sizeof (newNum[0]))-1 && (int)newNum[i]*count == 0)
            check = 1;
    }

    int reverse = 0, remainder2;

    while (result != 0)
    {
        remainder2 = result % 10;
        reverse = reverse * 10 + remainder2;
        result /= 10;
    }
    // printf("Reversed number = %d", reverse);
    if(check ==1)
        reverse*=10;

    printf("%d", decimal);
    printf("=>");
    printf("%d", reverse);
} // שאלה 5

void BinaryAddition()
{
    long long binary1 =0,binary2 =0;

    printf("Please enter two binary numbers: \n");

    scanf("%lld", &binary1);
    scanf("%lld", &binary2);

    long long decimal1 = 0;

    // code that turns a number from binary base to decimal base
    int length = 0;
    long long binary1_f = binary1;
    while(binary1_f!=0){
        length++;
        binary1_f= binary1_f/10;
    }
    binary1_f = binary1;
    int numlength = length;
    int digit = 0;
    long long decimal =0;

    for(int i =numlength-1; i>0; i--)
    {
        digit = binary1_f/(pow(10,length-1));
        decimal+= digit * pow(2,i);
        length--;
        binary1_f=binary1_f-(digit*(pow(10,length)));
    }
    decimal1= decimal;

    long long decimal2 = 0;
    // --------------------------------------------------------------------
    length = 0;
    long long binary2_f = binary2;
    while(binary2_f!=0){
        length++;
        binary2_f= binary2_f/10;
    }
    binary2_f = binary2;
    numlength = length;
    digit = 0; decimal =0;

    for(int i =numlength-1; i>0; i--)
    {
        digit = binary2_f/(pow(10,length-1));
        decimal+= digit * pow(2,i);
        length--;
        binary2_f=binary2_f-(digit*(pow(10,length)));
    }
    decimal2= decimal;

    long long sum = decimal1 + decimal2;
    long long binarySum = 0;

    int num =decimal1;
    int counter = 0;

    while(num !=0)
    {
        num = num/2;
        counter++;
    }

    num = decimal1;

    int quotient = num/2;
    int remainder = num%2;
    num = quotient;

    char newNum1 [counter];
    counter--;
    if(remainder>=10)
        newNum1[counter] = GetHexValue(remainder);
    else
        newNum1[counter] = remainder;

    counter--;

    while (quotient!=0)
    {
        quotient = num/2;
        remainder = num%2;
        num = quotient;

        if(remainder>=10)
            newNum1[counter] = GetHexValue(remainder);
        else
            newNum1[counter] = remainder;

        counter--;
    }

    int result = 0;
    int count = 1;
    int check = 0;
    for ( int i =0; i<(sizeof(newNum1)/sizeof (newNum1[0])); i++)
    {
        result  +=(int)newNum1[i]*count;
        count*=10;
        if(i==(sizeof(newNum1)/sizeof (newNum1[0]))-1 && (int)newNum1[i]*count == 0)
            check = 1;
    }

    int reverse = 0, remainder2;

    while (result != 0)
    {
        remainder2 = result % 10;
        reverse = reverse * 10 + remainder2;
        result /= 10;
    }
    if(check ==1)
        reverse*=10;

    binarySum+=reverse;
// -----------------------------------------------------------//

    num = decimal2; counter = 0; quotient = 0; remainder = 0;
    while(num !=0)
    {
        num = num/2;
        counter++;
    }
    num = decimal2;

    quotient = num/2;
    remainder = num%2;
    num = quotient;

    char newNum2 [counter];
    counter--;
    if(remainder>=10)
        newNum2[counter] = GetHexValue(remainder);
    else
        newNum2[counter] = remainder;

    counter--;

    while (quotient!=0)
    {
        quotient = num/2;
        remainder = num%2;
        num = quotient;

        if(remainder>=10)
            newNum2[counter] = GetHexValue(remainder);
        else
            newNum2[counter] = remainder;

        counter--;
    }

    result = 0; count = 1; check = 0;
    for ( int i =0; i<(sizeof(newNum2)/sizeof (newNum2[0])); i++)
    {
        result  +=(int)newNum2[i]*count;
        count*=10;
        if(i==(sizeof(newNum2)/sizeof (newNum2[0]))-1 && (int)newNum2[i]*count == 0)
            check = 1;
    }

    reverse = 0, remainder2 = 0;

    while (result != 0)
    {
        remainder2 = result % 10;
        reverse = reverse * 10 + remainder2;
        result /= 10;
    }
    if(check ==1)
        reverse*=10;

    binarySum+=reverse;

    int size1 = 0;
    int size2 = 0;
    long long binary1_s = binary1;
    long long binary2_s = binary2;

    while(binary1_s!=0){
        size1++;
        binary1_s= binary1_s/10;
    }

    while(binary2_s!=0){
        size2++;
        binary2_s = binary2_s/10;
    }

    if(size1 < size2)
    {
        for(int i = 0; i<size2-size1;i++)
        {
            printf("%d", 0);
        }
    }

    printf( "%lld",binary1);
    printf(" + ");

    if(size1>size2)
    {
        for(int i = 0; i<size1-size2;i++)
        {
            printf("%d", 0);
        }
    }

    printf("%lld", binary2);
    printf(" = ");

    printf("%lld", binarySum);
} // שאלה 2

void PrintHi(){
    printf("Pick a number: \n" );
    unsigned int x = 0;
    scanf("%u", &x);
    if(x<0){
        printf("Invalid Input!");
        return;
    }
    int rowCount = 3*x+4;
    int colCount = 4*x+7;

    int row0start0 = 0;
    int row0end0 = row0start0 + x + 2;

    int row0start1 = x + 2 + x;
    int row0end1 = row0start1 + x + 2 - 1;

    int row0start2 = row0end1 + 1;
    int row0end2 = row0start2 + x + 2;

   // char * space = " ";

    for(int row = 0; row < rowCount; row++){
        for(int col = 0; col < colCount; col++){
            if(row == 0 || row == rowCount - 1){ // first && last rows
                if((col >= row0start0 && col < row0end0) || (col >= row0start1 && col <= row0end1) || (col > row0start2 && col <= row0end2)){
                    printf("#");
                }
                else {
                    printf(" ");
                }
            }

            if((row > 0 && row <= x) || (row >= 2 * x + 3 && row < 3 * x + 3)){
                if((col >= row0start0 && col < row0end0) || (col >= row0start1 && col <= row0end1) || (col > row0start2 && col <= row0end2)){
                    if(col == 0 || col == row0end0 -1 || col == row0start1 || col == row0end1 || col == row0start2 + 1 || col == row0end2){
                        printf("#");
                    }
                    else {
                        printf("*");
                    }

                }
                else {
                    printf(" ");
                }
            }

            if(row == x + 1|| row == 2 * x + 2){
                if((col >= row0start0 && col <= row0end1) || (col > row0start2 && col <= row0end2)) {
                    if (col == row0start0 || (col >= row0end0 - 1 && col <= row0start1) || col == row0start2 - 1 || col == row0start2 + 1 || col == row0end2) {
                        printf("#");
                    } else {
                        printf("*");
                    }
                }
                else {
                    printf(" ");
                }

            }

            if(row >= x + 2 && row < x + 2 + x) {
                if((col >= row0start0 && col <= row0end1) || (col > row0start2 && col <= row0end2)) {
                    if (col == row0start0 || col == row0end1 || col == row0start2 + 1 || col == row0end2) {
                        printf("#");
                    } else {
                        printf("*");
                    }
                }
                else {
                    printf(" ");
                }
            }
        }
        printf("\n");
    }
} // שאלה 3

void countDigitOne()
{
    int binary = 0;
    printf("Please enter binary number: ");
    scanf("%d", &binary);

    int digit = 0;
    int counter = 0;

    while(binary!=0)
    {
        digit = binary%10;
        if(digit==1)
            counter++;
        binary/=10;
    }
    printf("%d", counter);
   // return counter;
} // שאלה 4

void ZigZag(){
    printf("Enter a non negative decimal number ");
    int decimal = 0;
    scanf("%d", &decimal);

    int binary = 0;
    int digit = 0;

    int num =decimal;
    int counter = 0;

    while(num !=0)
    {
        num = num/2;
        counter++;
    }
    num = decimal;

    int quotient = num/2;
    int remainder = num%2;
    num = quotient;

    char newNum [counter];
    counter--;
    if(remainder>=10)
        newNum[counter] = GetHexValue(remainder);
    else
        newNum[counter] = remainder;

    counter--;

    while (quotient!=0)
    {
        quotient = num/2;
        remainder = num%2;
        num = quotient;

        if(remainder>=10)
            newNum[counter] = GetHexValue(remainder);
        else
            newNum[counter] = remainder;

        counter--;
    }

    int result = 0;
    int count = 1;
    int check = 0;
    for ( int i =0; i<(sizeof(newNum)/sizeof (newNum[0])); i++)
    {
        result  +=(int)newNum[i]*count;
        count*=10;
        if(i==(sizeof(newNum)/sizeof (newNum[0]))-1 && (int)newNum[i]*count == 0)
            check = 1;

    }

    int reverse = 0, remainder2;

    while (result != 0)
    {
        remainder2 = result % 10;
        reverse = reverse * 10 + remainder2;
        result /= 10;
    }
    // printf("Reversed number = %d", reverse);
    if(check ==1)
        reverse*=10;

    binary = reverse;

    int checkZigZag = 1; // משתנה עזר

    while(binary/10!=0)
    {
        digit = binary%10;
        binary/=10;
        if(digit ==1)
            if(binary%10 !=0){
                checkZigZag =0; // אם המספר הבא לא שווה ל-0 התנאי לא מתקיים
                break;
            }
        if(digit ==0){
            if(binary%10 !=1){
                checkZigZag = 0; // אם המספר הבא לא שווה ל-0 התנאי לא מתקיים
                break;
            }
        }
    }
    if(checkZigZag == 0)
        printf("false");
    else
        printf("true");
} // שאלה 6

int main() {

    setbuf(stdout,0);
    // menu
    printf("Choose an option:\n");
    printf("1. octal to hex\n");
    printf("2. binary addition\n");
    printf("3. print HI\n");
    printf("4. count bits\n");
    printf("5. decimal to binary\n");
    printf("6. zig-zag bits\n");
    printf("7. exit\n");

    int option = 0; // משתנה שמקבל את האופציה שנבחרה

    scanf("%d", &option);

    if(option <1 || option > 7) // בדיקת תחום ערכים
    {
        printf("Invalid Option!");
    }

    switch (option) // התאמת האפשרות שנבחרה לפעולה
    {
        case 1:
            OctalToHex();
           break;
        case 2:
            BinaryAddition();
            break;
        case 3:
            PrintHi();
            break;
        case 4:
            countDigitOne();
            break;
        case 5:
            FromDecimalToBinary();
            break;
        case 6:
            ZigZag();
            break;
        case 7:
            printf("Bye!");
            break;
    }

}


