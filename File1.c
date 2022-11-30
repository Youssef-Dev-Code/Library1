#include <Structs.h>
#include <File3.h>

int main(int argc, char const *argv[])
{
    system("mkdir /usr/Import"); // creating directory to save data
    Book *Head_Book = NULL;
    Theme *Head_Theme[MAX_THEMES];
    Author *Head_Author = NULL;
    __uint8_t x;
    Bool Test = True;
    while (Test == True)
    {
        Menu();
        scanf("%c", &x);
        switch (x)
        {
        case 1:
        
            break;
        case 2:
            
            break;
        default:
            printf("Invalid Value!!\n");
            break;
        }
    }
    
    return 0;
}
