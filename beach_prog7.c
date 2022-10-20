/*
*
* William Beach, COP2220, October 12, 2022  - Program 7
* Ordering program that allows user to select
* their food order and add money to their balance. Reads balance from file. Utilizes pointers. Updates balance and writes to file. 
*
*/



#define _CRT_SECURE_NO_WARNINGS //for Visual studio compiler 
#include<stdio.h> //for printf and scanf 
#include<ctype.h> //for tolower and toupper
#include <stdbool.h> //for boolean functionality

// function prototypes
void greeting(void); // greets user
void viewBalance(double balance); // displays user balance
void optionListPtr(char *choicePtr); // displays options for user
double processOption(char choice, double balance); // display output respective of user input
void displayMenu(void); // display food menu from program 6
void orderPricePtr(double *pricePtr); // get the order number and pass its price to the pointer pricePtr
int checkForEnoughMoney(double balance, double price); // check if there's enough money in user balance to place order
double reload(double balance); // help user to reload their account balance

int main() {
    char choice; //variable declarations
    double balance;
    FILE *inPtr, *outPtr; // file pointer variable declarations
    bool quit = false;
    greeting(); //greet user
    printf("Getting your balance from the file...\n\n");
    inPtr = fopen("accountBalance.txt", "r"); // open text file and assign pointer to the address of the text file's data
    fscanf(inPtr, "%lf", &balance); // scans text file via pointer variable and assigns data in file to variable balance
    viewBalance(balance); // displays balance which is passed value from file via fscanf and inPtr pointer
    while ( quit != true) { //if user submits q, function optionListPtr which points to choice variable address sets choice equal to q and thus quit becomes true and we break the loop
        optionListPtr(&choice);
        if (choice == 'q') {
          quit = true;
          break;
        }
        balance = processOption(choice, balance); //otherwise, choice is processed and options are displayed
    }
    printf("Saving your balance to file...\n\n");
    outPtr = fopen("accountBalance.txt", "w"); // output ptr references address of open file with write capability
    fprintf(outPtr, "Updated Balance: %.2f\n", balance); // fprintf lets us write to the referenced file with data stored in the variable balance
    fclose(inPtr); // close input reference to file
    fclose(outPtr); // close output reference to file
    printf("Have a great day!"); //goodbye when quitting
    return 0;
};


void greeting(void) { //greet user
    printf(" _______________________________________________________________________________ \n");
    printf("|                                                                               |\n");
    printf("|-------------------------------------------------------------------------------|\n");
    printf("|.....................Welcome traveler, to the Coffee Shack.....................|\n");
    printf("|........................Delicious food if you have coin........................|\n");
    printf("|...I present to you a selection of our finest products from around the world...|\n");
    printf("|-------------------------------------------------------------------------------|\n");
    printf("|_______________________________________________________________________________|\n\n");
}

void viewBalance(double balance) { // displays user balance
        printf("Your current balance is %.2f", balance);
        printf("\n\n");
}

void optionListPtr(char *choicePtr) { //print user options and collect their choice
    printf("What would you like to do?\n\n"); 
    printf("Please select from the following options:\n\n");
    printf("'s' to view the snack and beverages available for purchase\n");
    printf("'o' to order coffee or a snack\n");
    printf("'b' to view your account balance\n");
    printf("'a' to add money to your account\n");
    printf("'q' to Quit\n\n");
    printf("Enter your selection: ");
    scanf(" %c", choicePtr); // passes user input to choice variable via choice pointer
    printf("\n\n");
    choicePtr = tolower(choicePtr); // lowercases user input
}

double processOption(char choice, double balance) { // takes user input and processes it depending on selection
    double price;
    switch (choice) {
        case 's':
            displayMenu();
            break;
        case 'o':
            printf("Order an item and complete the purchase\n\n");
            viewBalance(balance);
            orderPricePtr(&price); // passes price of item number to variable price
            if (checkForEnoughMoney(balance, price) == 1) { // checks balance before approving purchase
                printf("------------------------------Purchasing the item------------------------------\n\n");
                printf("Enjoy your purchase!\n\n");
                printf("***********************************************************************************\n\n");
                balance = balance - price;
                break;
            } else {
                printf("You do not have enough money in your account! Please select 'add money to your account' in menu options\n\n");
                printf("********************************************************************************************************\n\n");
                break;
            }
        case 'b':
            viewBalance(balance); // displays user balance
            printf("***********************************************************************************\n\n");
            break;
        case 'a':
            balance = reload(balance); // allows user to deposit money
            printf("***********************************************************************************\n\n");
            break;
        default:
            printf("That is not a valid option\n");
            printf("***********************************************************************************\n\n");
            break;
    }
    return balance;
}

void orderPricePtr(double *pricePtr) {
    displayMenu();
    int itemNumber;
    printf("Please enter your selection: ");
    scanf("%d", &itemNumber);
    printf("\n\n");
    switch (itemNumber) {
        case 1:
            printf("You selected 'Hot Coffee', the price is $2.35\n\n");
            *pricePtr = 2.35;
            break;
        case 2:
            printf("You selected 'Iced Coffee', the price is $5.00\n\n");
            *pricePtr = 5.00;
            break;
        case 3:
            printf("You selected 'Hot Latte', the price is $4.68\n\n");
            *pricePtr = 4.68;
            break;
        case 4: 
            printf("You selected 'Iced Latte', the price is $4.68\n\n");
            *pricePtr = 4.68;
            break;
        case 5: 
            printf("You selected 'Butter Croissant', the price is $3.50\n\n");
            *pricePtr = 3.50;
            break;
        case 6:
            printf("You selected 'Almond Croissant', the price is $4.50\n\n");
            *pricePtr = 4.50;
            break;
        case 7:
            printf("You selected 'Blueberry Muffin Top', the price is $5.00\n\n");
            *pricePtr = 5.00;
            break;
        default:
            printf("That is not a valid selection\n\n");
            break;
    }
}

int checkForEnoughMoney(double balance, double price) {
    if (balance - price >= 0) {
        return 1;
    } else {
        return 0;
    }
}

double reload(double balance) {
    double deposit;
    viewBalance(balance);
    printf("Please enter the deposit amount: ");
    scanf("%lf", &deposit);
    printf("\n\n");
    balance = balance + deposit;
    printf("Your new balance is: $%.2f\n\n", balance);
    return balance;
}

void displayMenu() { //show user the menu
        printf(" _______________________________________________________________________________\n");
        printf("|                                                                               |\n");
        printf("|                                      MENU                                     |\n");
        printf("|                                                                               |\n");
        printf("|                         (1)  Hot Coffee               $2.35                   |\n");
        printf("|                         (2)  Iced Coffee              $5.00                   |\n");
        printf("|                         (3)  Hot Latte                $4.68                   |\n");
        printf("|                         (4)  Iced Latte               $4.68                   |\n");
        printf("|                         (5)  Butter Croissant         $3.50                   |\n");
        printf("|                         (6)  Almond Croissant         $4.50                   |\n");
        printf("|                         (7)  Blueberry Muffin Top     $5.00                   |\n");
        printf("|_______________________________________________________________________________|\n\n");
        printf("***********************************************************************************\n");
}


