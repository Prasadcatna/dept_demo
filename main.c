[09:29] Hema Prasad C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define USERNAME "admin"
#define PASSWORD "admin123"
#define MAX 20
typedef struct items
{
    char product_code[MAX];
    char product_name[MAX];
    int rate;
    int quantity;
    float weight;
    char description[30];
} ITEM;
ITEM item;
int isCodeAvailable(char code[])
{
    FILE *file;
    file = fopen("Record.txt", "r");
    while (!feof(file))
    {
        fread(&item, sizeof(item), 1, file);
        if (strcmp(code, item.product_code) == 0)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
int isProductAvailable(int quantity)
{
    FILE *file;
    file = fopen("Record.txt", "r");
    while (!feof(file))
    {
        fread(&item, sizeof(item), 1, file);
        if (item.quantity >= quantity)
        {
            fclose(file);
            return 1;
        }
    }
    fclose(file);
    return 0;
}
int get_int(int input)
{
    char ch;
    while (scanf("%d", &input) != 1)
    {
        while ((ch = getchar()) != '\n')
        {
       }
        printf("\n\t\tMust be positive integer.\n");
        printf("\t\tEnter Positive integer value, such as 1,2,3,4: ");
    }
    return input;
}
int check_rate()
{
    int input;
    char ch;
    while (scanf("%d", &input) != 1)
    {
        while ((ch = getchar()) != '\n')
        {
       }
        printf("\n\t\tRate be positive Integer.\n");
        printf("\t\tEnter rate of the product in positive integer: ");
    }
    return input;
}
void addProduct()
{
    printf("\t\tAdd Product\n");
    FILE *file;
    char code[MAX];
    char x[4] = {0};
    int a;
    file = fopen("Record.txt", "ab");
    printf("\n\t\tEnter the \" end \" to exit for here");
    printf("\n\t\tEnter Product code: ");
    scanf("%s", code);
    if (strcmp(code, "end") == 0)
    {
        system("clear");
        options();
    }
    int available;
    available = isCodeAvailable(code); 
    if (available == 1)
    {
        system("clear");
        printf("\n\t\t* Product is already there.\n");
        options();
    }
    strcpy(item.product_code, code); 
    printf("\t\tEnter Product Name: ");
    scanf("%s", item.product_name);
    printf("\n\t\tEnter Product Rate: ");
    a = check_rate();
    item.rate = a;
    printf("\n\t\tEnter Quantity: ");
    scanf("%d", &item.quantity);
    printf("\n\t\tEnter product Weight(in gram): ");
    scanf("%f", &item.weight);
    printf("\n\t\tEnter product descriptions: ");
    scanf(" %s", item.description);
    fwrite(&item, sizeof(item), 1, file);
    fclose(file);
} 
void display()
{
    printf("\t\tAvailable Products\n");
    FILE *file;
    int count = 0;
    file = fopen("Record.txt", "rb");
    printf("\t\t\tCODE\t||\tNAME\t||\tRATE\t||\tQUANTITY\t||\tWEIGHT\t||\tDESCRIPTION\n");
    if (file == NULL)
    {
        printf("\t\t\t\tNo Product is inserted.");
        options();
    }
    while (fread(&item, sizeof(item), 1, file))
    {
        printf("\t\t\t%s\t||\t%s\t||\t%d\t||\t %d\t\t||\t%.2f\t||\t%s \n", item.product_code, item.product_name, item.rate, item.quantity, item.weight, item.description);
        count++;
    }
    if (count == 0)
    {
        system("clear");
        printf("\n\t\t* Product is not available.\n");
        printf("\033[0m");
    }
    fclose(file);
} 
void close_app()
{
    char choice;
    printf("\n Do you want to close the applications?(Y/y)");
    scanf("%s", &choice);
    if (choice == 'Y' || choice == 'y')
    {
        exit(0);
    }
}
void search()
{
    FILE *file;
    char code[MAX], product[MAX];
    int available;
    printf("\t\tEnter \"end\" for back to menu.\n");
    printf(\t\tEnter the Product code to search: ");
    scanf("%s", code);
    if (strcmp(code, "end") == 0)
    {
        system("clear");
        options();
    }
    system("clear");
    printf("\t\tProduct information\n");
    printf("\t\t**********************\n");
    available = isCodeAvailable(code);
    if (available == 0)
    {
        system("clear");
        printf("\n\t\tProduct code is not found.\n");
    }
    else
    {
        file = fopen("Record.txt", "rb");
        while (fread(&item, sizeof(item), 1, file))
        {
            strcpy(product, item.product_code);
            if (strcmp(product, code) == 0)
            {
                printf("\n\t\tProduct Code:        %s", item.product_code);
                printf("\n\t\tName of Product:     %s", item.product_name);
                printf("\nt\t\tRate of Product(RS): %d", item.rate);
                printf("\n\t\tProduct Weight:      %.2f", item.weight);
                printf("\n\t\tProduct Description: %s\n", item.description);
            }
        }
        fclose(file);
    }
} 
void deleteRecord()
{
    FILE *file1, *file2;
    char code[MAX], product[MAX];
    int available;
    file1 = fopen("Record.txt", "rb");
    display();
    printf("\n\t\t\t\t\t\tEnter the Product code to delete: ");
    scanf("%s", code);
    system("clear");
    available = isCodeAvailable(code);
    if (available == 0)
    {
        system("clear");
        printf("\n\t\t* Product is not available.\n");
    }
    else
    {
        file2 = fopen("tempfile.txt", "wb");
        while (fread(&item, sizeof(item), 1, file1))
        {
            strcpy(product, item.product_code);
            if (strcmp(product, code) != 0)
            {
                fwrite(&item, sizeof(item), 1, file2);
            }
        }
        fclose(file1);
        fclose(file2);
        file1 = fopen("Record.txt", "wb");
        file2 = fopen("tempfile.txt", "rb");
        while (fread(&item, sizeof(item), 1, file2))
        {
            fwrite(&item, sizeof(item), 1, file1);
        }
        printf("\n\t\tProduct deleted sucessfully!!\n\n");
        fclose(file1);
        fclose(file2);
    }
} 
void updateProduct()
{
    printf("\t\tUpdate Product\n");
    printf("\t\t************************\n");
    FILE *file1, *file2;
    char code[MAX], product[MAX];
    int available;
    printf("enter the Product code to update the record:");
    scanf("%s", code);
    available = isCodeAvailable(code);
    if (available == 0)
    {
        system("clear");
        printf("\n\t\t* no Product is found for update.\n");
    }
    else
    {
        file1 = fopen("Record.txt", "rb");
        file2 = fopen("tempfile.txt", "wb");
        while (fread(&item, sizeof(item), 1, file1))
        {
            strcpy(product, item.product_code);
            if (strcmp(product, code) != 0)
            {
                fwrite(&item, sizeof(item), 1, file2);
            }
            else
            {
                printf("\n Updating data for the privious product %s\n", code);
                printf("enter Product Name: ");
                scanf("%s", item.product_name);
                printf("Enter Product Rate: ");
                scanf("%d", &item.rate);
                printf("Enter Quantity: ");
                scanf("%d", &item.quantity);
                printf("Enter weight: ");
                scanf("%f", item.weight);
                printf("enter product descriptions: ");
                scanf("%s", item.description);
                printf("\n\n");
                fwrite(&item, sizeof(item), 1, file2);
            }
        }
        fclose(file1);
        fclose(file2);
        file1 = fopen("Record.txt", "wb");
        file2 = fopen("tempfile.txt", "rb");
        while (fread(&item, sizeof(item), 1, file2))
        {
            fwrite(&item, sizeof(item), 1, file1);
        }
        fclose(file1);
        fclose(file2);
    }
} 
void login()
{
    printf("\t\tLogin \n");
    char username[15], password[10];
    printf("\t\tEnter username: ");
    scanf("%s", username);
    printf("\t\tEnter password: ");
    scanf("%s", password);
    while (1)
    {
        if ((strcmp(USERNAME, username)) == 0 && (strcmp(PASSWORD, password)) == 0)
        {
            system("clear");
            printf("\t\tLogin successfully!!");
            options();
        }
        else
        {
            system("clear");
            printf("\n\t\tsorry you enter the worng information.\n");
            printf("\n\t\tPlease try again.\n");
            login();
            break;
        }
    }
} 
int main()
{
    login();
    system("clear");
    return 0;
} 
void saleProduct()
{
    printf("\t\tSale Product\n");
    char x[4] = {0}; // for item code
    int q = 0, size = 0, i = 1;
    int total = 0, gtotal = 0;
    FILE *file;
    file = fopen("Record.txt", "r+b");
    rewind(file);
    int availableC, availableQ;
    printf("\t\tEnter  \" end \" to finish input");
    int qty = item.quantity;
    while (1)
    {
        printf("\n\t\tEnter Item Code:");
        scanf("%s", x);
        if (strcmp(x, "end") == 0)
        {
            system("clear");
            break;
        }
        availableC = isCodeAvailable(x);
        if (availableC == 0)
        {
            system("clear");
            printf("\n\t\t* no Product is found.\n");
            options();
        }
        printf("\t\tEnter Quantity:");
        scanf("%d", &q);
        qty = qty - q;
        if (qty < 0)
        {
            system("clear");
            printf("\n\t\t* Out of stock.\n");
            break;
       }
        rewind(file);
        while (fread(&item, sizeof(item), 1, file))
        {
            if ((strcmp(item.product_code, x) == 0))
            {
                total = item.rate * q;
                printf("\n\t\t%d ", i);
                printf("\t\t%s ", item.product_name);
                printf("\t\t%d ", q);
                printf("\t\t%d ", item.rate);
                printf("\t\t%d ", total);
                gtotal = gtotal + total;
                size = sizeof(item);
                item.quantity = item.quantity - q;
                i++;
                fseek(file, -size, SEEK_CUR);
                fwrite(&item, sizeof(item), 1, file);
                break;
            }
        }
    }
    if (gtotal != 0)
    {
        printf("\t\tTOTAL AMOUNT = NRs. %d", gtotal);
    }
    fclose(file);
}
void options()
{
    int num, choice;
    while (1)
    {
        printf("\n\t\t\t1. Insert\n\t\t\t2. Display");
        printf("\n\t\t\t3. Search\n\t\t\t4. Delete\n\t\t\t5. Update");
        printf("\n\t\t\t6. close\n\t\t7. Sale product\n\n");
        printf("\t\tEnter your choice: ");
        choice = get_int(num);
        switch (choice)
        {
        case 1:
            system("clear");
            addProduct();
            system("clear");
            break;
        case 2:
            system("clear");
            display();
            break;
        case 3:
            system("clear");
            search();
            break;
        case 4:
            system("clear");
            deleteRecord();
            break;
        case 5:
            system("clear");
            updateProduct();
            break;
        case 6:
            system("clear");
            close_app();
            break;
        case 7:
            system("clear");
            saleProduct();
            break;

}
}
