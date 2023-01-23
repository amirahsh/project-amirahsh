#include <stdio.h>
#include<conio.h>
#include<process.h>
#include<stdlib.h>
#include<dir.h>
void inputcommand(char string[]){
    scanf("%s",string);
}

char getcharx(){
    char c=getchar();
    return c;
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
            else if((d=getcharx())=='\n'){
                    
            }
        }
        else string[counter]=c;
        counter++;
    }
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
    gets(file);
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


void fileinserterspace(){
    char root[70]={0},ourpath[70]={0},c;
    char dir[30]="C:\\Users\\Amirhosein";
    getcot(root);
    //printf("%s",root);
    for (int i = 0 ,j=0; i<strlen(root) ; ++i,j++) {
        ourpath[j]=root[i];
//        if(root[i]=='\\' && root[i+1]!='"')
//            ourpath[++j]='\\';
    }
    char *ourroot;
    ourroot = strcat(dir,ourpath);
    //printf("%s",ourroot);
    FILE *ptr=fopen(ourroot,"w");
    if(ptr==NULL)
        printf("File could not be created or be opened\n");
    char com[8];
    char text[200];
    inputcommand(com);
    if((c=getcharx())=='"')
        getcot(text);
    fclose(ptr);
}

 void fileinserternonspace(){
    char root[70]={0},ourpath[70]={0};
    char dir[30]="C:\\Users\\Amirhosein\\";
    inputcommand(root);
    for (int i = 0 ,j=0; i<strlen(root) ; ++i,j++) {
        ourpath[j]=root[i];
       // if(root[i]=='\\' && root[i+1]!='"')
           // ourpath[++j]='\\';
    }
    char * ourroot;
    ourroot= strcat(dir,ourpath);
   // printf("%s",ourroot);
    FILE *ptr=fopen(ourroot,"w");
     if(ptr==NULL)
         printf("File could not be created or be opened\n");
     char com[8];
     inputcommand(com);
     fclose(ptr);

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