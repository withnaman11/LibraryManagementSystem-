#include<stdio.h>
#include<string.h>

typedef struct book
{
    int book_id;
    char book_name[50];
    char author[50];

} b; // book information

//functions to the library 
void addbook();
void deletebook();
void searchbook();
void veiwallbook();
void issuebook();
void searchforissue();

int main()
{
    printf("=============================\n  LIBRARY MANAGEMENT SYSTEM\n=============================\n");
    b book1;
    int choice;
    
    do
    {
         printf("\n1.Add book\n2.view all books\n3.Search books\n4.Delete books\n6.view issued books \n7.issue books \n8.Logout\n\nenter your choice:");
         scanf("%d",&choice);
         switch (choice)
                {
                case 1:
                    printf("\nAdding a new book\n");
                    addbooks();
                    break;

                case 2:
                    printf("\nDisplayng all books...\n");
                    veiwallbooks();
                    break;

                case 3: 
                    printf("searching....");
                    searchbooks();
                    break;

                case 4:
                    printf("delete the book !");
                    deletebooks();
                    break;
                case 6:
                     printf("// before this search the book id is valid or not !\n");
                    searchforissue();
                    break;
                case 7:
                   issuebook();
                   break;
                
                case 8:
                     printf("program terminated !");
                    break;

                default:
                    printf("\n invalid option entered");
                    break;
                }
    } while (choice!=8);
    
}

//declaration of functions 

void searchbooks() // search books in library
{
    b search;
    FILE *books;
    int search_id, found = 0;
    printf("enter the book id you have to search :");
    scanf("%d", &search_id);
    books = fopen("book.dat", "rb");
    if (books == NULL)
    {
        printf("\nerror opening file\n");
        return;
    }
    if (books)
    {
        rewind(books);
        while (fread(&search, sizeof(search), 1, books) == 1)
        {
            if (search_id == search.book_id)
            {
                printf("\n...book is present...\n%-10d,%-10s,%-10s\n", search.book_id, search.book_name, search.author);
                found = 1;
                break;
            }
        }
    }
    fclose(books);
    if (found == 0)
    {
        printf("\nBook is not present :-(\n");
    }
}

void addbooks() // adding a new book
{   
    FILE *book1;
    b new;b temp;
    book1 = fopen("book.dat", "rb");
    if (book1 == NULL)
    {
        printf("error opening file!");
        return;
    }
    // taking book details
    int search_book, present = 0;
    printf("enter the book id:");
    scanf("%d", &new.book_id);
    getchar();
    printf("enter the book name:");
    fgets(new.book_name, 50, stdin);
    new.book_name[strcspn(new.book_name, "\n")];
    printf("enter the author name:");
    fgets(new.author, 50, stdin);
    new.author[strcspn(new.author, "\n")];
    // reading the books file
    while (fread(&temp, sizeof(temp), 1, book1))
    {
        if (temp.book_id == new.book_id)
        {
            printf("\nBook is present in the library !\n");
            present++;
            break;
        }
    }
    fclose(book1);
    if (present == 0)
    {
        book1 = fopen("book.dat", "ab");
        fwrite(&new, sizeof(new), 1, book1);
        printf("\nbook added successfully!\n");
        fclose(book1);
    }
}

void deletebooks() // deleting a book
{
    FILE *books,*temp;
    int deleting_id, found = 0;
    b deletebooks;
    printf("enter the book id :");
    scanf("%d", &deletebooks.book_id);
    deleting_id = deletebooks.book_id;

    books = fopen("book.dat", "rb");
    temp = fopen("temp.dat", "wb"); // opening a temporary file
    if (books == NULL)
    {
        printf("error opening file!");
        return;
    }
    if (temp == NULL)
    {
        printf("\nunable to create a temporary file!\n\n");
        return;
    }
    rewind(books);
    while (fread(&deletebooks, sizeof(deletebooks), 1, books))
    {
        if (deletebooks.book_id != deleting_id)
        {
            fwrite(&deletebooks, sizeof(deletebooks), 1, temp); // copy to the temporary file except the target
        }
        else
        {
            found++;
        }
    }
    fclose(books);
    fclose(temp);
    remove("book.dat");             // deletes the original file
    rename("temp.dat", "book.dat"); // renames the temporary file

    if (found == 1)
    {
        printf("\nbook deleted successflly !\n");
    }
    else
    {
        printf("\nUnable to find the book !\n");
    }
}
void veiwallbooks() // display all book function
{
    b view;
    FILE *books;
    books = fopen("book.dat", "rb");
    if (books == NULL)
    {
        printf("\nerror opening file\n");
        return;
    }
    if (books)
    {
        rewind(books);
        while (fread(&view, sizeof(view), 1, books) == 1)
        {
            printf("\nbook id - %10d  , book name - %10s ,  author -%10s\n ", view.book_id, view.book_name, view.author);
        }
    }
    fclose(books);
}

void issuebook() // issue book function
{
    b issue;
    int search_id,found=0;
    FILE *book;FILE *issued;
    book=fopen("book.dat","rb+");
    printf("Enter the book id to issue:");
    scanf("%d",&search_id);
     if (book == NULL)
    {
        printf("\nerror opening file\n");
        return;
    }
    rewind(book);
    while (fread(&issue,sizeof(book),1,book))
    {
        if(issue.book_id==search_id){
            printf("Book issued");
            issued=fopen("issued.txt","ab");
            fprintf(issued,"%d ",search_id);
            fclose(issued);
            found++;
            break;
        }
        else{
           continue;
        }
    }
    fclose(book);
    if(found==0){
        printf("book not found!");
    }
}

void searchforissue(){
   
    FILE *issued;
    int a,b,found=0;
    issued=fopen("issued.txt","r");
    printf("\nenter the  book id to search:");
    scanf("%d",&a);
    if (issued==NULL){
        printf("error openin file...");
        return;
    }
    if(issued){
        rewind(issued);
       fscanf(issued,"%d",&b);
        while(b!=EOF){
            if(b==a){
                printf("\nbook issued , not present in library\n ");
                found++;
                break;
            }
          
             fscanf(issued,"%d",&b);
        }
        
       
    }
    fclose(issued);
    if(found==0){
        printf("book is in library!\n");
    }
}