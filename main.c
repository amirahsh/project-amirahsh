#include <stdio.h>
#include<conio.h>
#include<process.h>
#include<stdlib.h>
#include<dir.h>
void inputcommand(char string[15]){
    scanf("%s",string);
}
void create_folder(char *dirname) {
    int check;
    check = mkdir(dirname);
    //checking if directory is created
    if (!check)
        printf("Directories created\n");
    else {
        printf("Unable to create directory\nthey may have already been created\n");
    }
//    getch();
//    system("dir/p");
//    getch();
}
void createwithoutcot(){
    char file[70],ourroot[70],ourfile[30];
    char dirname[60] = "C:\\Users\\Amirhosein\\";
    scanf("%s",file);
    //printf("%s",file);
    char *e;
    e = strrchr(file, '\\');
    for (int i = 0, j=0; i < (int)(e-file); i++,j++) {
        ourroot[j]=file[i];
        if(file[i]=='\\')
            ourroot[++j]='\\';
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
        printf("File could not be created");
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
        if(file[i]=='\\')
            ourroot[++j]='\\';
    }
    ourfile[0]='\\';
    for (int i = (int)(e-file)+1, j=1; i<strlen(file)-1 ; i++,j++) {
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
        printf("File could not be created");
    fclose(ptr);
}
int main() {
    char com[15],com2[15],c;
    printf("User Guide:\n A:for creating file or folder:\n   1-createfile --file <file name and address>\n   2-createfile –file <\"file name and address\">"
           "(if your folder or your filenames have space\n   *Note:if you are willing to create folders only type '\\' at the end\n");
    inputcommand(com);
    while(strcmp(com,"exit")!=0){
        if(strcmp(com,"createfile")==0){
            inputcommand(com2);
            getchar();
            if(strcmp(com2,"--file")==0){
                c=getchar();
                if(c=='\\')
                    createwithoutcot();
                else  if(c=='"')
                    createwithcot();
                else
                    printf("Invalid Input");
            }
        }
        else
            printf("Invalid Input%s",com);
        inputcommand(com);
    }
    return 0;
}