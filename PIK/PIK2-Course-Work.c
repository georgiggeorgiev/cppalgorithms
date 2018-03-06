#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STRING_LEN 30
#define FILE_NAME "Data.bin"
#define CLEAR system("cls");printf("0.Exit\n1.Read file\n2.Print list\n3.Write list to file\n4.Append structure to file\n5.Add to end of list\n6.Add to start of list\n7.Add to middle of list\n");

// Структура, съдържаща данните, записани в двоичния файл.
typedef struct S_Data{
    char file_name[STRING_LEN];
    char artist_name[STRING_LEN];
    char song_name[STRING_LEN];
    char album_name[STRING_LEN];
    short year;
    char genre[STRING_LEN];
    short rating;
}Data;

// Структура, съдържаща обект от структурата Data и указател към следващия обект Node в свързания списък. При последния елемент от списъка стойността на този указател е задължително NULL.
typedef struct S_Node{
    Data data;
    struct S_Node* next;
}Node;

void read_file(Node** head,Node** last); // Приема аргументи адресите на указателите към първия и последния елемент от списъка. Променя стойностите на указателите в извикващата функция, като ги насочва към съответната памет, отговаряща на обект от структура Node, съдържащ информация, прочетена от двоичния файл. Осигурява генерирането на списъчната структура.
void get_string(char* input); // Приема аргумент указател към низ от char-ове и позволява на потребителя да въведе данни в низа.
short get_short(); // Връща стойност от тип short, въведена от потребителя.
Node* new_data_object(); // Позволява на потребителя да въведе данните в съответните полета на обект от структура Node и връша указател към обекта.
FILE* open_file(char* mode); // Приема аргумент указател към низ от char-ове, чието съдържание отговаря на режим на четене на файл. Отваря файлът в съответния режим и връща указател към него.
void append_struct_to_binary_file(Node* node,FILE* fp); // Приема аргументи указател към обект от структура Node и указател към отворен файл. Записва данните от подадения обект в края на файла в двоичен вид.
Node* read_data_from_file(FILE* fp); // Приема аргумент указател към отворен файл. Заделя памет за обект от структура Node, попълва съответните му данни посредством прочитане на файлът и връща указател към заделената памет. При липса на данни във файла или достигане на неговия край връща NULL.
Node* node_alloc(); // Заделя памет за обект от структура Node и връща указател към нея.
void print_list(Node* head); // Приема аргумент указател към обект от структура Node и извежда информацията в обектите от списъка, като започва от подадения обект и свършва в края на списъка.
void free_list(Node** head); // Приема аргумент адреса на указател към първия обект в свързания списък. Преминава през списъка и освобождава заделената памет за неговите елементи, след което променя стойността на указателя към първия елемент на NULL в извикващата функция.
void write_list_to_binary_file(Node* head); // Приема аргумент указател към обект от структура Node, отваря файл в режим за двоично записване, и записва в него информацията в обектите от списъка, като започва от подадения обект и свършва в края на списъка.
Node* get_struct_by_index(Node* head,short index); // Приема аргумент указател към обект от структура Node и стойност от тип short, отговаряща на индекса на търсения елемент в списъка. Преминава през списъка и при съвпадение на индекса на обект с подадения индекс връща указател към съответния обект. В противен случай връща NULL.
void add_struct_to_middle(Node* index); // Приема аргумент указател към обект от структура Node и позволява добавяне на нов обект след него в списъка.

int main() // Съдържа указателите към първия и последния обект в свързания списък и позволява на потребителя да манипулира данните в списъка чрез извикване на съответните функции от меню.
{
    Node* head=NULL,*last=NULL,*temp=NULL;

    CLEAR
    char c;
    while(1){
        c=getchar();
        fflush(stdin);
        if(c=='0'){
            break;
        }
        else if(c=='1'){
            free_list(&head);
            read_file(&head,&last);
            printf("Data successfully read from file\n");
        }
        else if(c=='2'){
            print_list(head);
        }
        else if(c=='3'){
            write_list_to_binary_file(head);
        }
        else if(c=='4'){
            append_struct_to_binary_file(new_data_object(),open_file("ab"));
        }
        else if(c=='5'){
            CLEAR
            if(head==NULL){
                head=new_data_object();
                last=head;
            }
            else{
                last->next=new_data_object();
                last=last->next;
            }
        }
        else if(c=='6'){
            CLEAR
            if(head==NULL){
                head=new_data_object();
                last=head;
            }
            else{
                temp=new_data_object();
                temp->next=head;
                head=temp;
                temp=NULL;
            }
        }
        else if(c=='7'){
            CLEAR
            if((head!=NULL)&&(head!=last)){
                printf("Enter index to add after:\n");
                add_struct_to_middle(get_struct_by_index(head,get_short()));
            }
            else{printf("Can not add to middle\n");}
        }
        else{CLEAR}
    }

    free_list(&head);
    return 0;
}

void read_file(Node** head,Node** last)
{
    FILE* fp=open_file("rb");
    if(fp==NULL){
        perror(NULL);
        exit(2);
    }

    (*head)=read_data_from_file(fp);
    if((*head)==NULL){
        printf("No data in file\n");
        free((*head));
        fclose(fp);
        exit(3);
    }

    (*last)=(*head);
    while(1){
        (*last)->next=read_data_from_file(fp);
        if(((*last)->next)==NULL){
            fclose(fp);
            break;
        }
        (*last)=(*last)->next;
    }
}

Node* read_data_from_file(FILE* fp)
{
    Node* current=node_alloc();

    if(fread(&current->data,sizeof(Data),1,fp)==1){
        return current;
    }
    else{
        free(current);
        fclose(fp);
        return NULL;
    }
}

void get_string(char* input)
{
    fgets(input,STRING_LEN-1,stdin);
    fflush(stdin);
}

short get_short()
{
    unsigned short input;
    scanf("%hd",&input);
    fflush(stdin);

    return input;
}

Node* new_data_object()
{
    Node* node=(Node*)malloc(sizeof(Node));

    printf("Enter file path/name:\n");
    get_string(node->data.file_name);

    printf("Enter artist name:\n");
    get_string(node->data.artist_name);

    printf("Enter song name:\n");
    get_string(node->data.song_name);

    printf("Enter album name:\n");
    get_string(node->data.album_name);

    printf("Enter year:\n");
    node->data.year=get_short();
    while(node->data.year<=0){
        printf("Invalid year entered, try again:\n");
        node->data.year=get_short();
    }

    printf("Enter genre:\n");
    get_string(node->data.genre);

    printf("Enter rating(value must be between 0 and 5):\n");
    node->data.rating=get_short();
    while((node->data.rating<0)||(node->data.rating>5)){
        printf("Invalid rating entered, try again:\n");
        node->data.rating=get_short();
    }
    node->next=NULL;

    return node;
}

FILE* open_file(char* mode)
{
    FILE* fp=fopen(FILE_NAME,mode);
    return fp;
}

void append_struct_to_binary_file(Node* node,FILE* fp)
{
    if(fp==NULL){
        perror(NULL);
        free(node);
        exit(1);
    }
    fwrite(&node->data,sizeof(Data),1,fp);
    free(node);
    fclose(fp);
}

Node* node_alloc()
{
    Node* node=(Node*)malloc(sizeof(Node));

    return node;
}

void print_list(Node* head)
{
    int counter=0;
    if(head==NULL){
        printf("Nothing in list, read file first\n");
        return;
    }
	Node *current=head;

	while(current!=NULL){
		printf("Index: %d\nFile name: %sArtist name: %sSong name: %sAlbum name: %sYear: %hd\nGenre: %sRating: %hd\n",
         counter,current->data.file_name,current->data.artist_name,current->data.song_name,current->data.album_name,
         current->data.year,current->data.genre,current->data.rating);

        printf("Node address: %p\tNext address: %p\n\n",current,current->next);
		current=current->next;
		++counter;
	}
}

void free_list(Node** head)
{
    Node* current=(*head);
    Node* next=NULL;

    while(current!=NULL){
        next=current->next;
        free(current);
        current=next;
    }
    (*head)=NULL;
}

void write_list_to_binary_file(Node* head)
{
    if(head==NULL){
        printf("Nothing in list, read file first\n");
        return;
    }
    FILE* fp=open_file("wb");
    if(fp==NULL){
        perror(NULL);
        free_list(&head);
        exit(4);
    }
    Node* current=head;
    while(current!=NULL){
        fwrite(&current->data,sizeof(Data),1,fp);
        current=current->next;
    }
    fclose(fp);
}

Node* get_struct_by_index(Node* head,short index)
{
    Node* current=head;
    short count=0;

    for(;;){
        if(count==index){
            return current;
        }
        else{
            current=current->next;
            ++count;
        }
        if(current==NULL){
            printf("No such index\n");
            return NULL;
        }
    }
}

void add_struct_to_middle(Node* index)
{
    if(index==NULL){
        return;
    }
    Node* temp=new_data_object();
    temp->next=index->next;
    index->next=temp;
}
