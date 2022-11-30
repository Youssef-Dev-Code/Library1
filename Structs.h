#include <stdio.h>
#include <string.h>  
#include <stdlib.h>
#include <unistd.h>

char *Theme_Path = "/usr/Import/Themes.bin";
char *Book_Path = "/usr/Import/Book.bin";
//#define MAX_THEMES 25;
size_t MAX_THEMES = 25;

typedef enum Bool {
    False,
    True
}Bool;

typedef struct Author
{
    char First[15];
    char Last[15];
    __uint16_t Number;
    struct Author *Link;
}Author;

typedef struct Book
{
    char Title[40];
    Author A;
    __uint64_t Number;
    float Price;
    struct Book *Link;
}Book;

typedef struct Theme
{
    char Theme_Name[20];
    __uint8_t Number;
    Book *B;
}Theme;

Author *Author_Create(Author **Head)
{
    Author *Temp1 = (Author*)malloc(sizeof(Author));
    printf("Give Author's First Name: ");
    scanf("%s", &(Temp1->First));
    printf("Give author's last name: ");
    scanf("%s", &(Temp1->Last));  
    printf("Give author's number: ");
    scanf("%hu", &(Temp1->Number));
    Temp1->Link = *Head;  // adding the author in the author list
    *Head = Temp1;
}

void Add_Book(Book **Head1, Author **Head2)
{
    __uint8_t x;
    __uint16_t y;
    Book *Temp = (Book*)malloc(sizeof(Book));
    Author *Temp0 = *Head2;
    printf("Give Book's Title: ");
    scanf("%s", &(Temp->Title));
    printf("Give Book's Number: ");
    scanf("%c", &(Temp->Number));
    printf("Give Book's Price: ");
    scanf("%f", &(Temp->Price));
    printf("Type 0 to show author list\nType 1 if this book is written by a new author\n__::");
    scanf("%c", &x);
    switch (x)
    {
    case 0:
        while (Temp0 != NULL)
        {
            printf("%s %s number: %hu\n", Temp0->First, Temp0->Last, Temp0->Number);
            Temp0 = Temp0->Link;
        }
        break;
        Temp0 = *Head2;  // resetting temp to first link
        printf("Type 0 if the author exists in this list\nType 1 if not\n__::");
        scanf("%c", &x);
    case 1:
        Temp->A = *Author_Create(Head2);    // assigning the newly created author to the book
        x = 2; // assigning x  --> 2 to avoid next switch statement
        break;
    default:
        printf("Invalid Option!\n");
        break;
    }
    switch (x)
    {
    case 0:
        printf("Give author's number: ");
        scanf("%hu", &(y));
        while (Temp0 != NULL)
        {
            if (Temp0->Number == y)
            {
                Temp->A = *Temp0;  // adding author to book struct
                break;
            }
            Temp0 = Temp0->Link;
        }
        break;
    case 1:
        Temp->A = *Author_Create(Head2);   // assigning the newly created author to the book
        break;
    case 2:
        break;
    default :
        printf("Invalid Value!!\n");
        break;
    }
    Temp->Link = *Head1;
    *Head1 = Temp;
}

Theme *Theme_Create(void)
{
    Theme *Temp;
    printf("Give theme's name: ");
    scanf("%s", &(Temp->Theme_Name));
    printf("Give theme's number: ");
    scanf("%c", &(Temp->Number));
    Temp->B = NULL;
    return Temp;
}

void Theme_Add(Theme **Theme_List)
{
    __uint8_t i = 0;
    while ((Theme_List[i] != NULL) && (i < MAX_THEMES)) // set number of empty slots in theme list to 0
    {i++;}
    Theme_List[i] = Theme_Create();
}

void Import_Themes(Theme **Theme_List)
{
    __uint8_t i = 0;
    FILE *pf = fopen(Theme_Path, "rb");
    if (pf == NULL)
    {
        printf("An Error occured while opening %s\n", Theme_Path);
        return;
    }
    while (fread(Theme_List[i], sizeof(Theme), 1, pf) != 0)
    {i++;}
    fclose(pf);
}

void Import_Books(Book **Head)
{
    Book *Temp = (Book*)malloc(sizeof(Book));
    FILE *pf = fopen(Book_Path, "rb");
    if (pf == NULL)
    {
        printf("An Error occured while opening %s\n", Book_Path);
        return;
    }
    while (fread(Temp, sizeof(Book), 1, pf) != 0)
    {
        Temp->Link = *Head;
        *Head = Temp;
        Temp = (Book*)malloc(sizeof(Book));
    }
    fclose(pf);
}

void Save_Themes(Theme **Theme_List)
{
    __uint8_t i = 0;
    FILE *pf = fopen(Theme_Path, "ab");
    if (pf == NULL)
    {
        printf("An Error occured while opening %s\n", Theme_Path);
        return;
    }
    while (Theme_List[i] != NULL)
    {
        fwrite(Theme_List[i], sizeof(Theme), 1, pf);
        i++;
    }
    fclose(pf);
}

void Print_Themes(Theme *Th)
{
    printf("Theme's name: %d\n", Th->Number);
    printf("Theme's number: %s\n", Th->Theme_Name);
}

void Save_Theme(Theme **Theme_List) 
{
    __uint8_t i = 0, x;
    printf("----------------------------\n");
    while (Theme_List[i] != NULL)
    {
        Print_Themes(Theme_List[i]);
        i++;
    }
    i = 0;
    printf("----------------------------\n");
    printf("Give theme number to save: ");
    scanf("%c", &x);
    while (Theme_List[i]->Number != x)
    {i++;}
    FILE *Pf = fopen(Theme_Path, "ab");
    if (Pf == NULL)
    {
        printf("An Error occured while opening %s\n", Theme_Path);
        return;
    }
    fwrite(Theme_List[i], sizeof(Theme), 1, Pf);
    fclose(Pf);
}

void Save_Book(Book **Head)
{
    Book *Temp = *Head;
    __uint64_t n;
    __uint8_t x;
    printf("Type 1 to save a single book\nType 2 to save all books\nType 3 to reset progress and save all books\n__::");
    scanf("%c", &x);
    switch (x)
    {
    case 1:
        printf("Type 1 to print book list\nType 2 to enter book number to save\n__:");
        scanf("%c", &x);
        if (x == 1)
        {
            while (Temp != NULL)
            {
                printf("%s\n", Temp->Title);
                printf("%d\n", Temp->Number);
                Temp = Temp->Link;
            }
        }
        printf("Give Book number to save in data base:");
        scanf("%lu", &n);
        Temp = *Head;
        while (Temp->Number != n)
        {Temp = Temp->Link;}
        FILE *Pf = fopen(Book_Path, "ab");
        fwrite(Temp, sizeof(Book), 1, Pf);
        fclose(Pf);
        break;
    case 2:
        FILE *Pf = fopen(Book_Path, "ab");
        if (Pf == NULL)
        {
            printf("An Error occured while opening %s\n", Book_Path);
            return;
        }
        while (Temp != NULL)
        {
            fwrite(Temp, sizeof(Book), 1, Pf);
            Temp = Temp->Link;
        }
        fclose(Pf);
        break;
    case 3:
        FILE *Pf = fopen(Book_Path, "wb");
        if (Pf == NULL)
        {
            printf("An Error occured while opening %s\n", Book_Path);
            return;
        }
        while (Temp != NULL)
        {
            fwrite(Temp, sizeof(Book), 1, Pf);
            Temp = Temp->Link;
        }
        fclose(Pf);
        break;
    default:
        printf("Invalid Value!\n");
        break;
    }
}

void Menu(void)
{
    printf("Type 1 to add a book\n");
    printf("Type 2 to add a theme\n");
    printf("Type 3 to add an author\n");
    printf("Type 4 to save themes\n");
    printf("Type 5 to save books\n");
}