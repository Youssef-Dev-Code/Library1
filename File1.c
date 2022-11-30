#include <Structs.h>
#include <File3.h>

int main(int argc, char const *argv[])
{
    system("mkdir /usr/Import"); // creating directory to save data
    Book *Head_Book = NULL;
    Theme *Theme_List[MAX_THEMES];
    Author *Head_Author = NULL;
    __uint8_t x;
    Bool Test = True;
    while (Test == True)
    {
        Menu();
        scanf("%c", &x);
        switch (x)
        {
        case 0:
            Test = False;
            break;
        case 1:
            Add_Book(&Head_Book, &Head_Author);
            break;
        case 2:
            Theme_Add(Theme_List);
            break;
        case 3:
            Author_Create(&Head_Author);
            break;
        case 4:
            
            break;
        default:
            printf("Invalid Value!!\n");
            break;
        }
    }
    
    return 0;
}
