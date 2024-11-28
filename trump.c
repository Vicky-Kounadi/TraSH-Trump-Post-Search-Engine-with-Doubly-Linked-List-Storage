/*Vasiliki Kounadi
AM: 2022202000102
dit20102@uop.gr*/


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void newpost (char *str);
void print (int num);
void printr (int num);
void count(char *what);
void typecount(char *what);
void printa(char *when);
void printb(char *when);
void findt(char *what);
void findi(char *what);
void findl(char *what);
void deleten (void);
void deleteo (void);
void load (char *name, FILE *fp);
void save (char *name, FILE *fp);

typedef struct 
{
   int month;
   int day;
   int year;
   int hour;
   int minutes;
   int seconds; 
}datetime;

typedef struct 
{
   int sumofreactions;
   int comments;
   int shares;
   int likes;
   int loves;
   int wows;
   int hahas;
   int sads;
   int angrys; 
}reactions;

typedef struct trumppost
{
    char *text; //would be string tables but I dont know how long
    char *info;
    char *type;
    char *link;
    datetime posted;
    reactions feelings;
    char learnedfrom[5]; //5 because either FILE or KBRD
    struct trumppost *next;
    struct trumppost *prev;
}post;

post *head=NULL, *tail = NULL;//for the start

int main (void)
{
    FILE *fp;
    //meatablhtes
    char *command,*str; 
    char *arr[3],*sentence;
    int i,check=1,until;
    FILE *fpointer;
    char *file;

    printf("\n\n--WELCOME TO TR.A.S.H--\nEnter 'Exit' if you want to stop (your file won't be saved automatically)\nEnter Trump's posts below\n");
    

    while(check==1)
    {
        printf("\n$> ");

        sentence = (char*)malloc(32000 * sizeof(char));
        if(sentence==NULL)
        {
            printf("**MEMORY ERROR**\n\n");
            exit(1);
        }
        str = (char*)malloc(32000 * sizeof(char));
        if(str==NULL)
        {
            printf("**MEMORY ERROR**\n\n");
            exit(1);
        }
        command = (char*)malloc(20 * sizeof(char));
        if(command==NULL)
        {
            printf("**MEMORY ERROR**\n\n");
            exit(1);
        }

        fgets(sentence, 32000, stdin);

        arr[0]= strtok(sentence, " "); //splits sentence and perhaps new string
        arr[1]= strtok(NULL, "\n");
        if(arr[1]==NULL) //the previous strtok points at null if no str then at the end and return null, else at the old _ and erases \n
            arr[0]= strtok(sentence, "\n");//cut the \n at the end
        else
            strcpy(str,arr[1]); //if it found _ have the str

        strcpy(command,arr[0]);
        

        //make everything lower case
        for (i=0; command[i] ; i++)
            command[i]= tolower(command[i]);

        if (strcmp(command,"newpost") == 0) 
            newpost(str);

        else if (strcmp(command,"typecount") == 0) //ORDER IMPORTANT DONT CONFUSE WITH COUNT
            typecount(str);

        else if (strcmp(command,"count") == 0) 
            count(str);

        else if (strcmp(command,"findt") == 0) 
            findt(str);

        else if (strcmp(command,"findi") == 0) 
            findi(str);

        else if (strcmp(command,"findl") == 0) 
            findl(str);
        
        else if (strcmp(command,"printa") == 0) //ORDER IMPORTANT DONT CONFUSE WITH PRINT
            printa(str);
        
        else if (strcmp(command,"printb") == 0) //ORDER IMPORTANT DONT CONFUSE WITH PRINT
            printb(str);

        else if (strcmp(command,"printr") == 0) //ORDER IMPORTANT DONT CONFUSE WITH PRINT
        {
            until=atoi(str);
            printr(until); 
        }            
        else if (strcmp(command,"print") == 0) 
        {
            until=atoi(str);
            print(until); 
        } 

        else if (strcmp(command,"deleten") == 0) 
            deleten();
        
        else if (strcmp(command,"deleteo") == 0) 
            deleteo();

        else if (strcmp(command,"save") == 0) 
            save(str,fp);

        else if (strcmp(command,"load") == 0) 
            load(str,fp);
                
        else if (strcmp(command,"exit") == 0) 
            check=0;

        else
            printf("\nINVALID INPUT...\n");


        free(str);
        free(command);
        free(sentence);
    }
    printf("\nThank you for using TraSH! We want to guarantee that the ex-president's maxims will remain in history...\n\n");

    return 0;
}



void newpost (char* string)
{
    char **array;
    int i,j=0;
    int check=0;

    for(i=0;i<32000;i++)
    {
        if(string[i]==';')
            check++;
        if(string[i]=='\0')
            break;
    }
    
    if(check!=13)
    {
        printf("--INVALID POST\n");
        return;
    }
    
    array = (char**)malloc(20 * sizeof(char*));
    if(array==NULL)
    {
        printf("**MEMORY ERROR**\n\n");
        exit(1);
    }

    array[0]=strtok(string,";");
    for(i=1;i<20;i++) 
    {
       if (i==5)
            i=10;
      
        array[i]=strtok(NULL,";");

        if(array[i]==NULL) 
            break;

        

        if(*(array[i]-1)==';')//blank spot
        {
            *(array[i]-1)='\0';//makes the extra ; null
            array[i]=array[i]-1;//makes the pointer point to this null eg. empty spot is info=null
            array[i+1]=array[i]+1;//points to the start of the new spot as before
            i++;//moves for the next spot
        }  
    }
    
    array[5]=strtok(array[4],"/");
    array[5]=strtok(NULL,"/");
    
    array[6]=strtok(NULL," ");
    array[7]=strtok(NULL,":");
    array[8]=strtok(NULL,":");

    array[9]=strtok(NULL,":");
    if(array[9]==NULL)
      array[9]=array[8]+2;//seconds dont exist

    //create a new node  
    post *newnode = (post*)malloc(sizeof(post));
    if(newnode==NULL)
    {
        printf("**MEMORY ERROR**\n\n");
        exit(1);
    }

    //fill
    strcpy(newnode->learnedfrom,"kbrd");
    newnode->text = strdup(array[0]);
    newnode->info = strdup(array[1]); 
    newnode->type = strdup(array[2]); 
    newnode->link = strdup(array[3]);        
    newnode->posted.month = atoi(array[4]); 
    newnode->posted.day = atoi(array[5]); 
    newnode->posted.year = atoi(array[6]);
    newnode->posted.hour = atoi(array[7]); 
    newnode->posted.minutes = atoi(array[8]); 
    newnode->posted.seconds = atoi(array[9]); 
    newnode->feelings.sumofreactions = atoi(array[10]); 
    newnode->feelings.comments = atoi(array[11]);
    newnode->feelings.shares = atoi(array[12]);
    newnode->feelings.likes = atoi(array[13]);
    newnode->feelings.loves = atoi(array[14]);
    newnode->feelings.wows = atoi(array[15]);
    newnode->feelings.hahas = atoi(array[16]);
    newnode->feelings.sads = atoi(array[17]);
    newnode->feelings.angrys = atoi(array[18]); 
   
      
    if(head == NULL) //If list is empty
    {    
        head = newnode; 
        tail = newnode;  
        head->prev = NULL;   
        tail->next = NULL;  
    }  
    else //Add newnode as new tail of the list  
    {   
        tail->next = newnode;  
        newnode->prev = tail;   
        tail = newnode;   
        tail->next = NULL; 
    } 

    printf("--LIST UPDATED\n"); 

   free(array);
}

void print (int num)
{
    post *current = head;
    int i=1;

    if(head == NULL) 
        printf("--LIST IS EMPTY\n");  

    while(current != NULL)
    {
        printf("%.30s;", current->text);//text
        if(*(current->info)=='\0')
            printf(";");//info
        else
            printf("%s;", current->info); 
        printf("%s;", current->type);//type
        if(*(current->link)=='\0')//link
            printf(";");
        else
            printf("%.30s;", current->link);

        printf("%d/", current->posted.month);
        printf("%d/", current->posted.day);
        printf("%d ", current->posted.year); 

        printf("%d:", current->posted.hour);

        if(current->posted.seconds=='\0')
        {
            if(current->posted.minutes<10)
                printf("0%d;", current->posted.minutes);
            else
                printf("%d;", current->posted.minutes);     
        }
        else
        {
            if(current->posted.minutes<10)
                printf("0%d:", current->posted.minutes);
            else
                printf("%d:", current->posted.minutes);

            if(current->posted.seconds<10)
                printf("0%d;", current->posted.seconds);
            else
                printf("%d;", current->posted.seconds);
        }

        printf("%d;", current->feelings.sumofreactions); 
        printf("%d;", current->feelings.comments); 
        printf("%d;", current->feelings.shares); 
        printf("%d;", current->feelings.likes); 
        printf("%d;", current->feelings.loves); 
        printf("%d;", current->feelings.wows);
        printf("%d;", current->feelings.hahas); 
        printf("%d;", current->feelings.sads); 
        printf("%d;", current->feelings.angrys);
        printf("%s\n", current->learnedfrom);
        printf("\n");

        current= current->next;
        i++; 
        if(i>num)
            break;
    }

}

void printr (int num)
{
    post *current = tail;
    int i=1;

    if(head == NULL) 
        printf("--LIST IS EMPTY\n");  

    while(current != NULL)
    {
        printf("%.30s;", current->text);//text
        if(*(current->info)=='\0')
            printf(";");//info
        else
            printf("%s;", current->info); 
        printf("%s;", current->type);//type
        if(*(current->link)=='\0')//link
            printf(";");
        else
            printf("%.30s;", current->link);

        printf("%d/", current->posted.month);
        printf("%d/", current->posted.day);
        printf("%d ", current->posted.year); 

        printf("%d:", current->posted.hour);

        if(current->posted.seconds=='\0')
        {
            if(current->posted.minutes<10)
                printf("0%d;", current->posted.minutes);
            else
                printf("%d;", current->posted.minutes);     
        }
        else
        {
            if(current->posted.minutes<10)
                printf("0%d:", current->posted.minutes);
            else
                printf("%d:", current->posted.minutes);

            if(current->posted.seconds<10)
                printf("0%d;", current->posted.seconds);
            else
                printf("%d;", current->posted.seconds);
        }

        printf("%d;", current->feelings.sumofreactions); 
        printf("%d;", current->feelings.comments); 
        printf("%d;", current->feelings.shares); 
        printf("%d;", current->feelings.likes); 
        printf("%d;", current->feelings.loves); 
        printf("%d;", current->feelings.wows);
        printf("%d;", current->feelings.hahas); 
        printf("%d;", current->feelings.sads); 
        printf("%d;", current->feelings.angrys);
        printf("%s\n", current->learnedfrom);
        printf("\n");

        current= current->prev;
        i++; 
        if(i>num)
            break;
    }

}

void count(char *what)
{
    post *current = head;
    int sum=0;

    if(head == NULL) 
    {
        printf("--LIST IS EMPTY\n");
        return;
    }
         
        
    while(current != NULL)
    {
        if(strcmp(what,"reactions") == 0)
            sum= sum + current->feelings.sumofreactions;
        else if(strcmp(what,"comments") == 0)
            sum= sum + current->feelings.comments;
        else if(strcmp(what,"shares") == 0)
            sum= sum + current->feelings.shares;
        else if(strcmp(what,"likes") == 0)
            sum= sum + current->feelings.likes;
        else if(strcmp(what,"loves") == 0)
            sum= sum + current->feelings.loves;
        else if(strcmp(what,"wows") == 0)
            sum= sum + current->feelings.wows;
        else if(strcmp(what,"hahas") == 0)
            sum= sum + current->feelings.hahas;
        else if(strcmp(what,"sads") == 0)
            sum= sum + current->feelings.sads;
        else if(strcmp(what,"angrys") == 0)
            sum= sum + current->feelings.angrys;
        else
        {
            printf("--INVALID SEARCH\n");
            return;
        }

        current= current->next;
    }
    printf("--There are %d %s in total\n", sum, what);
}

void typecount(char *what)
{
    post *current = head;
    int sum=0;

    if(head == NULL)
    {
        printf("--LIST IS EMPTY\n");
        return;
    } 
          
        
    while(current != NULL)
    {
        if(strcmp(what,"status") == 0)
        {
            if(strstr(current->type,"status") != NULL)
                sum++;
        }
        else if(strcmp(what,"photo") == 0)
        {
            if(strstr(current->type,"photo") != NULL)
                sum++;
        }
        else if(strcmp(what,"video") == 0)
        {
            if(strstr(current->type,"video") != NULL)
                sum++;
        }
        else if(strcmp(what,"link") == 0)
        {
            if(strstr(current->type,"link") != NULL)
                sum++;
        }
        else
        {
            printf("--INVALID SEARCH TYPE\n");
            return;
        }
            
        current= current->next;
    }
    printf("--There are %d posts using the type %s in total\n", sum, what);
}

void printa(char *when)
{
    post *current = head;
    int i,m,d,y,yearcheck,check=0;
    char **board;

    board = (char**)malloc(3 * sizeof(char*));
    if(board==NULL)
    {
        printf("**MEMORY ERROR**\n\n");
        exit(1);
    }

    for(i=0;i<32000;i++)
    {
        if(when[i]=='/')
            check++;
        if(when[i]=='\0')
            break;
    }
    
    if(check!=2)
    {
        printf("--INVALID DATE\n");
        return;
    }
    
    
    board[0]= strtok(when,"/"); //splits sentence and perhaps new string

    for(i=1;i<3;i++) 
    {
        board[i]=strtok(NULL,"/");
        if(board[i]==NULL) 
            break;
    }

    m=atoi(board[0]);
    d=atoi(board[1]);
    y=atoi(board[2]);

    if(m<=0 || m>12 || d<=0 || d>31)
    {
        printf("--INVALID DATE\n");
        return;
    }


    if(head == NULL) 
        printf("--LIST IS EMPTY\n");  
        
    while(current != NULL)
    {
        if(current->posted.year<2000)//if instead of 2016 is 16 i dont change current->posted.year but use a new variable
            yearcheck= current->posted.year+2000;
        else
            yearcheck= current->posted.year;


        if(yearcheck >y)//HERE
        {
            printf("%.30s;", current->text);
            if(*(current->info)=='\0')
                printf(";");
            else
                printf("%s;", current->info); 
            printf("%s;", current->type);
            if(*(current->link)=='\0')
                printf(";");
            else
                printf("%.30s;", current->link);

            printf("%d/", current->posted.month);
            printf("%d/", current->posted.day);
            printf("%d ", current->posted.year); 

            printf("%d:", current->posted.hour);

            if(current->posted.seconds=='\0')
            {
                if(current->posted.minutes<10)
                    printf("0%d;", current->posted.minutes);
                else
                    printf("%d;", current->posted.minutes);     
            }
            else
            {
                if(current->posted.minutes<10)
                    printf("0%d:", current->posted.minutes);
                else
                    printf("%d:", current->posted.minutes);

                if(current->posted.seconds<10)
                    printf("0%d;", current->posted.seconds);
                else
                    printf("%d;", current->posted.seconds);
            }

            printf("%d;", current->feelings.sumofreactions); 
            printf("%d;", current->feelings.comments); 
            printf("%d;", current->feelings.shares); 
            printf("%d;", current->feelings.likes); 
            printf("%d;", current->feelings.loves); 
            printf("%d;", current->feelings.wows);
            printf("%d;", current->feelings.hahas); 
            printf("%d;", current->feelings.sads); 
            printf("%d;", current->feelings.angrys);
            printf("%s\n", current->learnedfrom);
            printf("\n");    
        }
        else if (yearcheck ==y)//HERE
        {
            if(current->posted.month >m)//HERE
            {
                printf("%.30s;", current->text);
                if(*(current->info)=='\0')
                    printf(";");
                else
                    printf("%s;", current->info); 
                printf("%s;", current->type);
                if(*(current->link)=='\0')
                    printf(";");
                else
                    printf("%.30s;", current->link);

                printf("%d/", current->posted.month);
                printf("%d/", current->posted.day);
                printf("%d ", current->posted.year); 

                printf("%d:", current->posted.hour);

                if(current->posted.seconds=='\0')
                {
                    if(current->posted.minutes<10)
                        printf("0%d;", current->posted.minutes);
                    else
                        printf("%d;", current->posted.minutes);     
                }
                else
                {
                    if(current->posted.minutes<10)
                        printf("0%d:", current->posted.minutes);
                    else
                        printf("%d:", current->posted.minutes);

                    if(current->posted.seconds<10)
                        printf("0%d;", current->posted.seconds);
                    else
                        printf("%d;", current->posted.seconds);
                }

                printf("%d;", current->feelings.sumofreactions); 
                printf("%d;", current->feelings.comments); 
                printf("%d;", current->feelings.shares); 
                printf("%d;", current->feelings.likes); 
                printf("%d;", current->feelings.loves); 
                printf("%d;", current->feelings.wows);
                printf("%d;", current->feelings.hahas); 
                printf("%d;", current->feelings.sads); 
                printf("%d;", current->feelings.angrys);
                printf("%s\n", current->learnedfrom);
                printf("\n"); 
            }
            else if (current->posted.month ==m)//HERE
            {
                if(current->posted.day >=d)//HERE
                {
                    printf("%.30s;", current->text);
                    if(*(current->info)=='\0')
                        printf(";");
                    else
                        printf("%s;", current->info); 
                    printf("%s;", current->type);
                    if(*(current->link)=='\0')
                        printf(";");
                    else
                        printf("%.30s;", current->link);

                    printf("%d/", current->posted.month);
                    printf("%d/", current->posted.day);
                    printf("%d ", current->posted.year); 

                    printf("%d:", current->posted.hour);

                    if(current->posted.seconds=='\0')
                    {
                        if(current->posted.minutes<10)
                            printf("0%d;", current->posted.minutes);
                        else
                            printf("%d;", current->posted.minutes);     
                    }
                    else
                    {
                        if(current->posted.minutes<10)
                            printf("0%d:", current->posted.minutes);
                        else
                            printf("%d:", current->posted.minutes);

                        if(current->posted.seconds<10)
                            printf("0%d;", current->posted.seconds);
                        else
                            printf("%d;", current->posted.seconds);
                    }

                    printf("%d;", current->feelings.sumofreactions); 
                    printf("%d;", current->feelings.comments); 
                    printf("%d;", current->feelings.shares); 
                    printf("%d;", current->feelings.likes); 
                    printf("%d;", current->feelings.loves); 
                    printf("%d;", current->feelings.wows);
                    printf("%d;", current->feelings.hahas); 
                    printf("%d;", current->feelings.sads); 
                    printf("%d;", current->feelings.angrys);
                    printf("%s\n", current->learnedfrom);
                    printf("\n"); 
                }
            }
        }
            
        current= current->next;
    }
    free(board);

}

void printb(char *when)
{
    post *current = head;
    int i,m,d,y,yearcheck,check=0;
    char **board;

    board = (char**)malloc(3 * sizeof(char*));
    if(board==NULL)
    {
        printf("**MEMORY ERROR**\n\n");
        exit(1);
    }

    for(i=0;i<32000;i++)
    {
        if(when[i]=='/')
            check++;
        if(when[i]=='\0')
            break;
    }
    
    if(check!=2)
    {
        printf("--INVALID DATE\n");
        return;
    }

    board[0]= strtok(when,"/"); //splits sentence and perhaps new string
    for(i=1;i<3;i++) 
    {
        board[i]=strtok(NULL,"/");
        if(board[i]==NULL) 
            break;
    }

    m=atoi(board[0]);
    d=atoi(board[1]);
    y=atoi(board[2]);

    if(m<=0 || m>12 || d<=0 || d>31)
    {
        printf("--INVALID DATE\n");
        return;
    }

    if(head == NULL) 
        printf("--LIST IS EMPTY\n");  
        
    while(current != NULL)
    {
        if(current->posted.year<2000)//if instead of 2016 is 16 i dont change current->posted.year but use a new variable
            yearcheck= current->posted.year+2000;
        else
            yearcheck= current->posted.year;

        if(yearcheck <y)//HERE
        {
            printf("%.30s;", current->text);
            if(*(current->info)=='\0')
                printf(";");
            else
                printf("%s;", current->info); 
            printf("%s;", current->type);
            if(*(current->link)=='\0')
                printf(";");
            else
                printf("%.30s;", current->link);

            printf("%d/", current->posted.month);
            printf("%d/", current->posted.day);
            printf("%d ", current->posted.year); 

            printf("%d:", current->posted.hour);

            if(current->posted.seconds=='\0')
            {
                if(current->posted.minutes<10)
                    printf("0%d;", current->posted.minutes);
                else
                    printf("%d;", current->posted.minutes);     
            }
            else
            {
                if(current->posted.minutes<10)
                    printf("0%d:", current->posted.minutes);
                else
                    printf("%d:", current->posted.minutes);

                if(current->posted.seconds<10)
                    printf("0%d;", current->posted.seconds);
                else
                    printf("%d;", current->posted.seconds);
            }

            printf("%d;", current->feelings.sumofreactions); 
            printf("%d;", current->feelings.comments); 
            printf("%d;", current->feelings.shares); 
            printf("%d;", current->feelings.likes); 
            printf("%d;", current->feelings.loves); 
            printf("%d;", current->feelings.wows);
            printf("%d;", current->feelings.hahas); 
            printf("%d;", current->feelings.sads); 
            printf("%d;", current->feelings.angrys);
            printf("%s\n", current->learnedfrom);
            printf("\n");    
        }
        else if (yearcheck ==y)//HERE
        {
            if(current->posted.month <m)//HERE
            {
                printf("%.30s;", current->text);
                if(*(current->info)=='\0')
                    printf(";");
                else
                    printf("%s;", current->info); 
                printf("%s;", current->type);
                if(*(current->link)=='\0')
                    printf(";");
                else
                    printf("%.30s;", current->link);

                printf("%d/", current->posted.month);
                printf("%d/", current->posted.day);
                printf("%d ", current->posted.year); 

                printf("%d:", current->posted.hour);

                if(current->posted.seconds=='\0')
                {
                    if(current->posted.minutes<10)
                        printf("0%d;", current->posted.minutes);
                    else
                        printf("%d;", current->posted.minutes);     
                }
                else
                {
                    if(current->posted.minutes<10)
                        printf("0%d:", current->posted.minutes);
                    else
                        printf("%d:", current->posted.minutes);

                    if(current->posted.seconds<10)
                        printf("0%d;", current->posted.seconds);
                    else
                        printf("%d;", current->posted.seconds);
                }

                printf("%d;", current->feelings.sumofreactions); 
                printf("%d;", current->feelings.comments); 
                printf("%d;", current->feelings.shares); 
                printf("%d;", current->feelings.likes); 
                printf("%d;", current->feelings.loves); 
                printf("%d;", current->feelings.wows);
                printf("%d;", current->feelings.hahas); 
                printf("%d;", current->feelings.sads); 
                printf("%d;", current->feelings.angrys);
                printf("%s\n", current->learnedfrom);
                printf("\n"); 
            }
            else if (current->posted.month ==m)//HERE
            {
                if(current->posted.day <=d)//HERE
                {
                    printf("%.30s;", current->text);
                    if(*(current->info)=='\0')
                        printf(";");
                    else
                        printf("%s;", current->info); 
                    printf("%s;", current->type);
                    if(*(current->link)=='\0')
                        printf(";");
                    else
                        printf("%.30s;", current->link);

                    printf("%d/", current->posted.month);
                    printf("%d/", current->posted.day);
                    printf("%d ", current->posted.year); 

                    printf("%d:", current->posted.hour);

                    if(current->posted.seconds=='\0')
                    {
                        if(current->posted.minutes<10)
                            printf("0%d;", current->posted.minutes);
                        else
                            printf("%d;", current->posted.minutes);     
                    }
                    else
                    {
                        if(current->posted.minutes<10)
                            printf("0%d:", current->posted.minutes);
                        else
                            printf("%d:", current->posted.minutes);

                        if(current->posted.seconds<10)
                            printf("0%d;", current->posted.seconds);
                        else
                            printf("%d;", current->posted.seconds);
                    }

                    printf("%d;", current->feelings.sumofreactions); 
                    printf("%d;", current->feelings.comments); 
                    printf("%d;", current->feelings.shares); 
                    printf("%d;", current->feelings.likes); 
                    printf("%d;", current->feelings.loves); 
                    printf("%d;", current->feelings.wows);
                    printf("%d;", current->feelings.hahas); 
                    printf("%d;", current->feelings.sads); 
                    printf("%d;", current->feelings.angrys);
                    printf("%s\n", current->learnedfrom);
                    printf("\n"); 
                }
            }
        }
            
        current= current->next;
    }
    free(board);

}

void findt(char *what)//text 
{
    post *current = head;
    int i;
    char *checktext;

    //make everything lower case
    for (i=0; what[i] ; i++)
        what[i]= tolower(what[i]);

    if(head == NULL) 
        printf("--LIST IS EMPTY\n");

    if(strcmp(what,"*")==0)//prints all
    {
        while(current != NULL)
        {
            printf("%s;", current->text);
            if(*(current->info)=='\0')
                printf(";");
            else
                printf("%s;", current->info); 
            printf("%s;", current->type);
            if(*(current->link)=='\0')
                printf(";");
            else
                printf("%.30s;", current->link);

            printf("%d/", current->posted.month);
            printf("%d/", current->posted.day);
            printf("%d ", current->posted.year); 

            printf("%d:", current->posted.hour);

            if(current->posted.seconds=='\0')
            {
                if(current->posted.minutes<10)
                    printf("0%d;", current->posted.minutes);
                else
                    printf("%d;", current->posted.minutes);     
            }
            else
            {
                if(current->posted.minutes<10)
                    printf("0%d:", current->posted.minutes);
                else
                    printf("%d:", current->posted.minutes);

                if(current->posted.seconds<10)
                    printf("0%d;", current->posted.seconds);
                else
                    printf("%d;", current->posted.seconds);
            }

            printf("%d;", current->feelings.sumofreactions); 
            printf("%d;", current->feelings.comments); 
            printf("%d;", current->feelings.shares); 
            printf("%d;", current->feelings.likes); 
            printf("%d;", current->feelings.loves); 
            printf("%d;", current->feelings.wows);
            printf("%d;", current->feelings.hahas); 
            printf("%d;", current->feelings.sads); 
            printf("%d;", current->feelings.angrys);
            printf("%s\n", current->learnedfrom);
            printf("\n");   

            current= current->next;
        }  

    } 
    else
    {
        while(current != NULL)
        {
            checktext=strdup(current->text);//it doesnt recognise LETS in post because I insert lets
            for (i=0; checktext[i]; i++)
                checktext[i]= tolower(checktext[i]);

            if(strstr(checktext, what) !=NULL)
            {
                printf("%s;", current->text);
                if(*(current->info)=='\0')
                    printf(";");
                else
                    printf("%s;", current->info); 
                printf("%s;", current->type);
                if(*(current->link)=='\0')
                    printf(";");
                else
                    printf("%.30s;", current->link);

                printf("%d/", current->posted.month);
                printf("%d/", current->posted.day);
                printf("%d ", current->posted.year); 

                printf("%d:", current->posted.hour);

                if(current->posted.seconds=='\0')
                {
                    if(current->posted.minutes<10)
                        printf("0%d;", current->posted.minutes);
                    else
                        printf("%d;", current->posted.minutes);     
                }
                else
                {
                    if(current->posted.minutes<10)
                        printf("0%d:", current->posted.minutes);
                    else
                        printf("%d:", current->posted.minutes);

                    if(current->posted.seconds<10)
                        printf("0%d;", current->posted.seconds);
                    else
                        printf("%d;", current->posted.seconds);
                }

                printf("%d;", current->feelings.sumofreactions); 
                printf("%d;", current->feelings.comments); 
                printf("%d;", current->feelings.shares); 
                printf("%d;", current->feelings.likes); 
                printf("%d;", current->feelings.loves); 
                printf("%d;", current->feelings.wows);
                printf("%d;", current->feelings.hahas); 
                printf("%d;", current->feelings.sads); 
                printf("%d;", current->feelings.angrys);
                printf("%s\n", current->learnedfrom);
                printf("\n");
            }   

            current= current->next;
        }
    }  

}

void findi(char *what)//info 
{
    post *current = head;
    int i;
    char *checkinfo;

    //make everything lower case
    for (i=0; what[i] ; i++)
        what[i]= tolower(what[i]);

    if(head == NULL) 
        printf("--LIST IS EMPTY\n");

    if(strcmp(what,"*")==0)//prints all
    {
        while(current != NULL)
        {
                printf("%.30s;", current->text);
                if(*(current->info)=='\0')
                    printf(";");
                else
                    printf("%s;", current->info); 
                printf("%s;", current->type);
                if(*(current->link)=='\0')
                    printf(";");
                else
                    printf("%.30s;", current->link);

                printf("%d/", current->posted.month);
                printf("%d/", current->posted.day);
                printf("%d ", current->posted.year); 

                printf("%d:", current->posted.hour);

                if(current->posted.seconds=='\0')
                {
                    if(current->posted.minutes<10)
                        printf("0%d;", current->posted.minutes);
                    else
                        printf("%d;", current->posted.minutes);     
                }
                else
                {
                    if(current->posted.minutes<10)
                        printf("0%d:", current->posted.minutes);
                    else
                        printf("%d:", current->posted.minutes);

                    if(current->posted.seconds<10)
                        printf("0%d;", current->posted.seconds);
                    else
                        printf("%d;", current->posted.seconds);
                }

                printf("%d;", current->feelings.sumofreactions); 
                printf("%d;", current->feelings.comments); 
                printf("%d;", current->feelings.shares); 
                printf("%d;", current->feelings.likes); 
                printf("%d;", current->feelings.loves); 
                printf("%d;", current->feelings.wows);
                printf("%d;", current->feelings.hahas); 
                printf("%d;", current->feelings.sads); 
                printf("%d;", current->feelings.angrys);
                printf("%s\n", current->learnedfrom);
                printf("\n");   

                current= current->next;
        }  

    } 
    else
    {
        while(current != NULL)
        {
            checkinfo=strdup(current->info);//it doesnt recognise LETS in post because I insert lets
            for (i=0; checkinfo[i]; i++)
                checkinfo[i]= tolower(checkinfo[i]);

            if(strstr(checkinfo, what) !=NULL)
            {
                printf("%.30s;", current->text);
                if(*(current->info)=='\0')
                    printf(";");
                else
                    printf("%s;", current->info); 
                printf("%s;", current->type);
                if(*(current->link)=='\0')
                    printf(";");
                else
                    printf("%.30s;", current->link);

                printf("%d/", current->posted.month);
                printf("%d/", current->posted.day);
                printf("%d ", current->posted.year); 

                printf("%d:", current->posted.hour);

                if(current->posted.seconds=='\0')
                {
                    if(current->posted.minutes<10)
                        printf("0%d;", current->posted.minutes);
                    else
                        printf("%d;", current->posted.minutes);     
                }
                else
                {
                    if(current->posted.minutes<10)
                        printf("0%d:", current->posted.minutes);
                    else
                        printf("%d:", current->posted.minutes);

                    if(current->posted.seconds<10)
                        printf("0%d;", current->posted.seconds);
                    else
                        printf("%d;", current->posted.seconds);
                }

                printf("%d;", current->feelings.sumofreactions); 
                printf("%d;", current->feelings.comments); 
                printf("%d;", current->feelings.shares); 
                printf("%d;", current->feelings.likes); 
                printf("%d;", current->feelings.loves); 
                printf("%d;", current->feelings.wows);
                printf("%d;", current->feelings.hahas); 
                printf("%d;", current->feelings.sads); 
                printf("%d;", current->feelings.angrys);
                printf("%s\n", current->learnedfrom);
                printf("\n");
            }   

            current= current->next;
        }
    }  

}

void findl(char *what)//link 
{
    post *current = head;
    int i;
    char *checklink;

    //make everything lower case
    for (i=0; what[i] ; i++)
        what[i]= tolower(what[i]);

    if(head == NULL) 
        printf("--LIST IS EMPTY\n");

    if(strcmp(what,"*")==0)//prints all
    {
        while(current != NULL)
        {
                printf("%.30s;", current->text);
                if(*(current->info)=='\0')
                    printf(";");
                else
                    printf("%s;", current->info); 
                printf("%s;", current->type);
                if(*(current->link)=='\0')
                    printf(";");
                else
                    printf("%s;", current->link);

                printf("%d/", current->posted.month);
                printf("%d/", current->posted.day);
                printf("%d ", current->posted.year); 

                printf("%d:", current->posted.hour);

                if(current->posted.seconds=='\0')
                {
                    if(current->posted.minutes<10)
                        printf("0%d;", current->posted.minutes);
                    else
                        printf("%d;", current->posted.minutes);     
                }
                else
                {
                    if(current->posted.minutes<10)
                        printf("0%d:", current->posted.minutes);
                    else
                        printf("%d:", current->posted.minutes);

                    if(current->posted.seconds<10)
                        printf("0%d;", current->posted.seconds);
                    else
                        printf("%d;", current->posted.seconds);
                }

                printf("%d;", current->feelings.sumofreactions); 
                printf("%d;", current->feelings.comments); 
                printf("%d;", current->feelings.shares); 
                printf("%d;", current->feelings.likes); 
                printf("%d;", current->feelings.loves); 
                printf("%d;", current->feelings.wows);
                printf("%d;", current->feelings.hahas); 
                printf("%d;", current->feelings.sads); 
                printf("%d;", current->feelings.angrys);
                printf("%s\n", current->learnedfrom);
                printf("\n");   

                current= current->next;
        }  

    } 
    else
    {
        while(current != NULL)
        {
            checklink=strdup(current->link);//it doesnt recognise LETS in post because I insert lets
            for (i=0; checklink[i]; i++)
                checklink[i]= tolower(checklink[i]);

            if(strstr(checklink, what) !=NULL)
            {
                printf("%.30s;", current->text);
                if(*(current->info)=='\0')
                    printf(";");
                else
                    printf("%s;", current->info); 
                printf("%s;", current->type);
                if(*(current->link)=='\0')
                    printf(";");
                else
                    printf("%s;", current->link);

                printf("%d/", current->posted.month);
                printf("%d/", current->posted.day);
                printf("%d ", current->posted.year); 

                printf("%d:", current->posted.hour);

                if(current->posted.seconds=='\0')
                {
                    if(current->posted.minutes<10)
                        printf("0%d;", current->posted.minutes);
                    else
                        printf("%d;", current->posted.minutes);     
                }
                else
                {
                    if(current->posted.minutes<10)
                        printf("0%d:", current->posted.minutes);
                    else
                        printf("%d:", current->posted.minutes);

                    if(current->posted.seconds<10)
                        printf("0%d;", current->posted.seconds);
                    else
                        printf("%d;", current->posted.seconds);
                }

                printf("%d;", current->feelings.sumofreactions); 
                printf("%d;", current->feelings.comments); 
                printf("%d;", current->feelings.shares); 
                printf("%d;", current->feelings.likes); 
                printf("%d;", current->feelings.loves); 
                printf("%d;", current->feelings.wows);
                printf("%d;", current->feelings.hahas); 
                printf("%d;", current->feelings.sads); 
                printf("%d;", current->feelings.angrys);
                printf("%s\n", current->learnedfrom);
                printf("\n");
            }   

            current= current->next;
        }
    }  

}

void deleten (void)
{
    post *pointer=tail;

    if(head == NULL) 
        printf("--LIST IS EMPTY\n");
    else if((tail->prev==NULL) && (tail->next==NULL))//list has one post
    {
        tail=head=NULL;
        free(pointer); 
        printf("--LAST POST DELETED SUCCESSFULLY\n");
    }
    else
    {
        tail= tail->prev;
        tail->next=NULL;
        pointer->prev=NULL;
        free(pointer);
        printf("--LAST POST DELETED SUCCESSFULLY\n");
    }
}

void deleteo (void)
{
    post *pointer=head;

    if(head == NULL) 
        printf("--LIST IS EMPTY\n");
    else if((head->prev==NULL) && (head->next==NULL))
    {
        tail=head=NULL;
        free(pointer); 
        printf("--LAST POST DELETED SUCCESSFULLY\n");
    }
    else
    {
        head= head->next;
        head->prev=NULL;
        pointer->next=NULL;
        free(pointer);
        printf("--FIRST POST DELETED SUCCESSFULLY\n");
    }
}

void load (char *name, FILE *fp)
{
    char *file;
    
    char **array;
    char *string;
    int i,j=0;
    int count, mistake;

    
    string = (char *)malloc(32000 * sizeof(char));
    if(string==NULL)
    {
        printf("**MEMORY ERROR**\n\n");
        exit(1);
    }
    

    file = strdup(name); //no need when doing malloc just put it a san argument
	fp = fopen(file, "r");
	if (fp == NULL)
    {
		printf("--ERROR OPENING FILE \"%s\"\n\n", file);
		return;
	}
	

    while ( !feof(fp) )  
    {
        mistake=0;
        count++;
        fgets(string,32000,fp);

        int check=0;

        for(i=0;i<32000;i++)
        {
            if(string[i]==';')
                check++;
            if(string[i]=='\0')
                break;
        }
        
        if(check!=13)
        {
            printf("--INVALID POST ON LINE %d\n", count);
            mistake=1;
            break;
        }

        array = (char**)malloc(20 * sizeof(char*));
        if(array==NULL)
        {
            printf("**MEMORY ERROR**\n\n");
            exit(1);
        }
    
        array[0]=strtok(string,";");

        for(i=1;i<20;i++) 
        {
            if (i==5)
                i=10;
        
            array[i]=strtok(NULL,";");

            if(array[i]==NULL) 
                break;

            if(*(array[i]-1)==';')//blank spot
            {
                *(array[i]-1)='\0';//makes the extra ; null
                array[i]=array[i]-1;//makes the pointer point to this null eg. empty spot is info=null
                array[i+1]=array[i]+1;//points to the start of the new spot as before
                i++;//moves for the next spot
            }  
        }

        
        array[5]=strtok(array[4],"/");
        array[5]=strtok(NULL,"/");
        
        array[6]=strtok(NULL," ");
        array[7]=strtok(NULL,":");
        array[8]=strtok(NULL,":");

        array[9]=strtok(NULL,":");
        if(array[9]==NULL)
            array[9]=array[8]+2;//seconds dont exist

        //create a new node  
        post *newnode = (post*)malloc(sizeof(post));

        //fill
        strcpy(newnode->learnedfrom,"file");
        newnode->text = strdup(array[0]);
        newnode->info = strdup(array[1]); 
        newnode->type = strdup(array[2]); 
        newnode->link = strdup(array[3]); 
        newnode->posted.month = atoi(array[4]); 
        newnode->posted.day = atoi(array[5]); 
        newnode->posted.year = atoi(array[6]);
        newnode->posted.hour = atoi(array[7]); 
        newnode->posted.minutes = atoi(array[8]); 
        newnode->posted.seconds = atoi(array[9]); 
        newnode->feelings.sumofreactions = atoi(array[10]); 
        newnode->feelings.comments = atoi(array[11]);
        newnode->feelings.shares = atoi(array[12]);
        newnode->feelings.likes = atoi(array[13]);
        newnode->feelings.loves = atoi(array[14]);
        newnode->feelings.wows = atoi(array[15]);
        newnode->feelings.hahas = atoi(array[16]);
        newnode->feelings.sads = atoi(array[17]);
        newnode->feelings.angrys = atoi(array[18]);

        if(head == NULL) //If list is empty
        {    
            head = newnode; 
            tail = newnode;  
            head->prev = NULL;   
            tail->next = NULL;  
        }  
        else //Add newnode as new tail of the list  
        {   
            tail->next = newnode;  
            newnode->prev = tail;   
            tail = newnode;   
            tail->next = NULL; 
        }  
        free(array);
     
    }

    if (mistake==0)
        printf("--LIST UPDATED, %d POSTS LOADED\n", count);
    else if (mistake==1)
	    printf("--LIST UPDATED, %d POSTS LOADED\n", count-1);//read all posts before mistake

    fclose(fp);
    free(string);

}

void save (char *name, FILE *fp)
{
    char *file;

    file = strdup(name); //no need when doing malloc just put it a san argument
	fp = fopen(file, "w");
	if (fp == NULL)
    {
		printf("--ERROR MAKING FILE \"%s\"\n", file);
		exit(0);
	}

    post *current = head;
    int i=1;

    if(head == NULL) 
        printf("--LIST IS EMPTY\n");
    else  
    {
        while(current != NULL)
        {
            fprintf(fp,"%s;", current->text);//text
            if(*(current->info)=='\0')
                fprintf(fp,";");//info
            else
                fprintf(fp,"%s;", current->info); 
            fprintf(fp,"%s;", current->type);//type
            if(*(current->link)=='\0')//link
                fprintf(fp,";");
            else
                fprintf(fp,"%s;", current->link);

            fprintf(fp,"%d/", current->posted.month);
            fprintf(fp,"%d/", current->posted.day);
            fprintf(fp,"%d ", current->posted.year); 

            fprintf(fp,"%d:", current->posted.hour);

            if(current->posted.seconds=='\0')
            {
                if(current->posted.minutes<10)
                    fprintf(fp,"0%d;", current->posted.minutes);
                else
                    fprintf(fp,"%d;", current->posted.minutes);     
            }
            else
            {
                if(current->posted.minutes<10)
                    fprintf(fp,"0%d:", current->posted.minutes);
                else
                    fprintf(fp,"%d:", current->posted.minutes);

                if(current->posted.seconds<10)
                    fprintf(fp,"0%d;", current->posted.seconds);
                else
                    fprintf(fp,"%d;", current->posted.seconds);
            }

            fprintf(fp,"%d;", current->feelings.sumofreactions); 
            fprintf(fp,"%d;", current->feelings.comments); 
            fprintf(fp,"%d;", current->feelings.shares); 
            fprintf(fp,"%d;", current->feelings.likes); 
            fprintf(fp,"%d;", current->feelings.loves); 
            fprintf(fp,"%d;", current->feelings.wows);
            fprintf(fp,"%d;", current->feelings.hahas); 
            fprintf(fp,"%d;", current->feelings.sads); 
            fprintf(fp,"%d;", current->feelings.angrys);
            fprintf(fp,"%s\n", current->learnedfrom);

            current= current->next;
        }
        fclose(fp);
        printf("--FILE SAVED SUCCESSFULLY\n");
    }

}