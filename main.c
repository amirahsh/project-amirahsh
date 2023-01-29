#include <stdio.h>
#include<conio.h>
#include<process.h>
#include<stdlib.h>
#include<dir.h>
#include<string.h>
void inputcommand(char string[]){
    scanf("%s",string);
}

char getcharx(){
    char c=getchar();
    return c;
}

void inputtext(char string[]){
    char c;
    int counter=1;
    while((c=getcharx())!=' '){
        string[counter]= c;
        counter++;
    }
}

void getsx(char string[]){
    gets(string);
}

void create_folder(char *dirname) {
    int check;
    check = mkdir(dirname);
    //checking if directory is created
    if (!check)
        printf("Directories created\n");
    else {
        printf("Unable to create directory they may have already been created\n");
    }
//    getch();
//    system("dir/p");
//    getch();
}

void createwithoutcot(){
    char file[70],ourroot[70],ourfile[30];
    char dirname[60] = "C:\\Users\\Amirhosein\\";
    inputcommand(file);
    //printf("%s",file);
    char *e;
    e = strrchr(file, '\\');
    for (int i = 0, j=0; i < (int)(e-file); i++,j++) {
        ourroot[j]=file[i];
//        if(file[i]=='\\')
//            ourroot[++j]='\\';
    }
    ourfile[0]='\\';
    for (int i = (int)(e-file)+1, j=1; file[i]!='\0' ; i++,j++) {
        ourfile[j]=file[i];
    }
    //printf("%s",ourfile);
    char *df;
    df = strcat(dirname, ourroot);
    create_folder(df);
    df = strcat(df,ourfile);
    //printf("%s",df);
    FILE *ptr=fopen(df,"w");
    if(ptr==NULL)
        printf("File could not be created \n");
    else
        printf("File created");
    fclose(ptr);
}

void createwithcot(){
    char file[70],ourroot[70],ourfile[30];
    char dirname[60] = "C:\\Users\\Amirhosein";
    getsx(file);
    //printf("%s",file);
    char *e;
    e = strrchr(file, '\\');
    for (int i = 0, j=0; i < (int)(e-file); i++,j++) {
            ourroot[j]=file[i];
//        if(file[i]=='\\' && file[i+1]!='"')
//            ourroot[++j]='\\';
    }
   // printf("%s",ourroot);
    ourfile[0]='\\';
    for (int i = (int)(e-file)+1, j=1; i<strlen(file)-1 ; i++,j++) {
        ourfile[j]=file[i];
    }

    char *df;
    df = strcat(dirname, ourroot);
    //printf("%s",df);
    create_folder(df);
    df = strcat(df,ourfile);
    //printf("%s",df);
    FILE *ptr=fopen(df,"w");
    if(ptr==NULL)
        printf("File could not be created\n");
    else
        printf("File created ");
    fclose(ptr);
}

void getcot(char string[]){
    int counter=0;
    char c,d,e;
    while(1){
        c=getcharx();
        if(c=='"' && string[counter-1]!='\\')
            break;
        else if(c=='\\'){
            if((d=getcharx())=='"')
                string[counter]=d;
            else if(d=='n')
                string[counter]='\n';
            else if(d=='\\'){
                if((e=getcharx())=='n'){
                    string[counter]='\\';
                    string[++counter]=e;
                }
            }

        }
        else
            string[counter]=c;
        counter++;
    }
}

void fileinserterspace() {
    char root[70] = {0}, c;
    char dir[30] = "C:\\Users\\Amirhosein";
    getcot(root);
    //printf("%s",root);
//    for (int i = 0 ,j=0; i<strlen(root) ; ++i,j++) {
//        ourpath[j]=root[i];
//        if(root[i]=='\\' && root[i+1]!='"')
//            ourpath[++j]='\\';
//    }
    char *ourroot;
    ourroot = strcat(dir, root);
    //printf("%s",ourroot);
    FILE *ptr = fopen(ourroot, "r+");
    char com[8];
    char text[500],saver[200],saver2[200];
    long int line=0,pos=0,entercounter=1,entercounter2=0,entercounter3=1,size=0,size2=0;
    char *whole;
    if (ptr == NULL) {
        printf("File could not be created or be opened try again\n");
    }
    else {
        inputcommand(com);
        if (strcmp(com, "--str") == 0) {
            getchar();
            if ((c = getcharx()) == '"')
                getcot(text);
            else
                inputtext(text);
            inputcommand(com);
            if (strcmp(com, "--pos") == 0) {
                scanf("%ld%c%ld", &line, &c, &pos);
                while (fgets(saver, 200, ptr) != NULL) {
                    if(entercounter<line)
                        entercounter2+= strlen(saver);
                    entercounter++;
                }
                //printf("%ld %d",entercounter2,entercounter);
                if(line<=entercounter){
                    rewind(ptr);
                    //printf("%ld %s %ld %ld ", ftell(ptr),text,line,pos);
                    while (fgets(saver, 200, ptr) != NULL) {
                        if(entercounter3==line) {
                            size = strlen(saver);
                            //printf("%d", size);
                            if (size >= pos) {
                                size2 = strlen(text);
                                fseek(ptr, entercounter2 + pos, SEEK_SET);
                                long int j = 0;
                                for (long int i = entercounter2 + pos+1; (c = fgetc(ptr)) != EOF; ++i) {
                                    saver2[j++] = c;
                                }
                                saver2[j] = '\0';
                                whole = strcat(text, saver2);
                                //printf("%s", whole);
                                // printf("%d %d", ftell(ptr), pos);
                                fseek(ptr, entercounter2 + pos+1, SEEK_SET);
                                fputs(text, ptr);

                                fclose(ptr);
                                break;
                            } else if (size < pos) {
                                printf("You cant write in that position\n");
                                fclose(ptr);
                                break;
                            }
                        }
                        else
                            entercounter3++;

                    }

                }
                else {
                    printf("you cant write in that line\n");
                    fclose(ptr);
                }
            }
            else {
                printf("Invalid input try again\n");
                fclose(ptr);
            }
        }
        else {
            printf("Invalid input try again\n");
            fclose(ptr);
        }

    }
}

 void fileinserternonspace(){
    char root[70]={0};
    char dir[30]="C:\\Users\\Amirhosein\\";
    inputcommand(root);
//    for (int i = 0 ,j=0; i<strlen(root) ; ++i,j++) {
//        ourpath[j]=root[i];
//       // if(root[i]=='\\' && root[i+1]!='"')
//           // ourpath[++j]='\\';
//    }
    char * ourroot;
    ourroot= strcat(dir,root);
   // printf("%s",ourroot);
    FILE *ptr=fopen(ourroot,"w");
     char com[8],c;
     char text[200];
     int line=0,pos=0;
     if (ptr == NULL) {
         printf("File could not be created or be opened try again\n");
     }
     else {
         inputcommand(com);
         if (strcmp(com, "--str" )== 0) {
             if ((c = getcharx()) == '"')
                 getcot(text);
             else
                 inputcommand(text);
             inputcommand(com);
             scanf("%d%c%d",&line,&c,&pos);
             fclose(ptr);
         }
         else {
             printf("Invalid input try again\n");
             fclose(ptr);
         }

     }

}
int main() {
    char com[15],com2[8],c;
    printf("User Guide:\n A:for creating file or folder:\n   1-createfile --file <file name and address>\n   2-createfile –file <\"file name and address\">"
           "(if your folder or your filenames have space\n   *Note:if you are willing to create folders only type '\\' at the end\n");
    inputcommand(com);
    while(strcmp(com,"exit")!=0){
        if(strcmp(com,"createfile")==0){
            inputcommand(com2);
            getchar();
            if(strcmp(com2,"--file")==0){
                c=getcharx();
                if(c=='\\')
                    createwithoutcot();
                else  if(c=='"')
                    createwithcot();
                else
                    printf("Invalid Input\n");
            }
        }
        else if(strcmp(com,"insertstr")==0) {
            inputcommand(com2);
            getchar();
            if (strcmp(com2, "--file") == 0) {
                c=getcharx();
                if(c=='\\') {
                    fileinserternonspace();
                }
                else  if(c=='"') {
                    fileinserterspace();
                }
                else
                    printf("Invalid Input");
            }
        }
        else {
            if(getcharx()=='\n')
                printf("Invalid Input\n");
        }
        inputcommand(com);
    }
    return 0;
}