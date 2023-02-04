#include <stdio.h>
#include<conio.h>
#include<process.h>
#include<stdlib.h>
#include<dir.h>
#include<string.h>
#include <dirent.h>

struct files{
    char *file;
    char *name;
};
struct files fileundo[10*100];
int howmanyeachfile[100]={0};
int howmanyeachwas[100]={0};
int howmanyfiles=0;
char cutstr[300];
void inputcommand(char string[]){
    scanf("%s",string);
}

char getcharx(){
    char c=getchar();
    return c;
}

void getsx(char string[]){
    gets(string);
}

void undotosave(char ourroot[],int wheretowrite) {
    char saver[400], *whole = {0}, *whole2 = {0};
    FILE *ptr;
    int i = 0;
    int which;
     //printf("sssssssss%d  %d",wheretowrite,howmanyfiles);
    if (wheretowrite == -2) {
        for (i = 0; i < howmanyfiles * 10+1; i += 10) {
            printf("%s %s",ourroot,fileundo[i].name);
            if (strcmp(ourroot, fileundo[i].name) == 0) {
                //  printf("ssss");
                which = howmanyeachfile[i / 10];
                wheretowrite = which + i;
            }
        }
    }
    //printf("aaaaa%d",wheretowrite);
    i = 0;
    if (wheretowrite == -2)
        printf("Invalid file the file may have been existed before\n");
    else {
        ptr = fopen(ourroot, "r+");
//        while (fgets(saver, 400, ptr) != NULL) {
//            for (int j = 0; saver[j] != '\0'; ++j, ++i) {
//                fileundo[wheretowrite].file[i] = saver[j];
//            }
//            printf("%s ", saver);
//        }
        fseek(ptr, 0, SEEK_END);
        long int size = ftell(ptr);
        rewind(ptr);

        fileundo[wheretowrite].file = calloc(size + 1, 1);

        fread(fileundo[wheretowrite].file,1,size,ptr);
        printf("%s ",fileundo[wheretowrite].file);
        fclose(ptr);
        howmanyeachfile[howmanyfiles]++;
        howmanyeachwas[howmanyfiles]++;

        //printf("%s",whole2);
//    for (int i = 0; i < 1500; i+=10) {
//        if(strcmp(ourroot,fileundo[i].name)==0)
//    }
        //printf("%s",whole);
    }
}

int undo(char ourroot[]){
    char c, e, com[15], saver[400], *wherefind = "";
    char wholefile[8000], *whole, *token;
    FILE *ptr;
    int which,i;
    for ( i = 0; i < howmanyfiles*10; i+=10) {
        if(strcmp(ourroot,fileundo[i].name)==0) {
            if(howmanyeachwas[i/10]-1==0){
                printf("File just been created you cannot  do undo\n");
                return -1;
            }
            which = --howmanyeachfile[i /10] ;
            printf("%d",which);
            if(which<0){
                which=howmanyeachwas[i/10];
                howmanyeachfile[i /10]=howmanyeachwas[i /10];
            }
            ptr = fopen(ourroot, "w");
            printf("%d %d",howmanyeachfile[i/10],howmanyeachwas[i/10]);
            if (ptr == NULL) {
                printf("File could not be created or be opened\n");
                return -1;
            }
            if(!fputs(fileundo[which].file,ptr))
                printf("Successful\n");
            else printf("Unssuccseful\n");
            fclose(ptr);
            return 1;
        }
    }
        printf("File not found\n");
        return -1;
}

void tree(const char *path,int indent,int indent1,int sign){
    if(indent1==-1)
        indent1=11;
    struct dirent *dp;
    DIR *dir = opendir(path);
    if (!dir) {
        printf("Unable to open directory\n");
        return;
    }
    char *whole;
    char indentto[10]={0};
    for(int i=0;i<indent ;i++){
        indentto[i]=' ';
    }
    char *tosend;
    while ((dp = readdir(dir)) != NULL){
        if(strcmp(dp->d_name,".")!=0 && strcmp(dp->d_name,"..")!=0){
            if(sign==0)
                printf("%s-%s\n",indentto, dp->d_name);
            if(sign==1 && strlen(dp->d_name)-(int) (strstr(dp->d_name,".txt") - dp->d_name)==4){
                //strstr(dp->d_name,".txt")!=NULL
                // printf("%s %s",path,dp->d_name);
                char *new_path2 = (char *)malloc(strlen(path) + strlen(dp->d_name) + 1);
                sprintf(new_path2, "%s\\",path);
                tosend= strcat(new_path2,dp->d_name);
                //printf("%s",tosend);
                for (int i = howmanyfiles*10; i < howmanyfiles*10+10; ++i) {
                    fileundo[i].name = strdup(tosend);
                }
                //printf("%s   ",fileundo[howmanyfiles*10].name);
                undotosave(tosend,howmanyfiles*10);
                howmanyeachfile[howmanyfiles]=0;
                howmanyeachwas[howmanyfiles]=0;
                howmanyfiles++;
            }
        }
        if(strstr(dp->d_name,".txt")==NULL && strcmp(dp->d_name,".")!=0 && strcmp(dp->d_name,"..")!=0 && indent<indent1){
            char *new_path = (char *)malloc(strlen(path) + strlen(dp->d_name) + 1);
            sprintf(new_path, "%s\%s\\", path, dp->d_name);
//            whole=strcat(dirr[indent-1],dp->d_name);
//            dirr[indent]= strdup(whole);
//            printf("%s",whole);
            tree(new_path,indent+1,indent1,sign);

        }

    }
    closedir(dir);
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
    //printf("%s  ",df);
    df[strlen(df)+1]='\0';
    df = strcat(df,ourfile);
    //printf("%s",df);
    FILE *ptr=fopen(df,"w");
    if(ptr==NULL) {
        printf("File could not be created \n");

    }else {
        for (int i = howmanyfiles * 10; i < howmanyfiles * 10 + 10; ++i) {
            fileundo[i].name = strdup(df);
        }
        //printf("%s   ",fileundo[howmanyfiles*10].name);
       // printf("%s",df);
        fclose(ptr);
        undotosave(df, howmanyfiles * 10);
        printf("File created\n");
    }
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
    if(ptr==NULL) {
        printf("File could not be created\n");
    }else {
        for (int i = howmanyfiles * 10; i < howmanyfiles * 10 + 10; ++i) {
            fileundo[i].name = strdup(df);
        }
        //printf("%s   ",fileundo[howmanyfiles*10].name);
        fclose(ptr);
        undotosave(df, howmanyfiles * 10);
        printf("File created\n");
    }
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
            else{
                string[counter]=c;
                string[++counter]=d;
            }

        }
        else
            string[counter]=c;
        counter++;
    }
}

void inputtext(char string[]){
    char c,d,e;
    int counter=1;
    while((c=getcharx())!=' '){
        if(c=='\\'){
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
    //printf("%s %s",ourroot,root);
    FILE *ptr = fopen(ourroot, "r+");
    char com[8];
    char text[500],saver[200],saver2[200];
    long int line=0,pos=0,entercounter=1,entercounter2=0,entercounter3=1,size=0;
    char *whole;
    if (ptr == NULL) {
        printf("File could not be created or be opened try again\n");
    }
    else {
        inputcommand(com);
        if (strcmp(com, "--str") == 0) {
            getcharx();
            if ((c = getcharx()) == '"')
                getcot(text);
            else  {
                text[0]=c;
                inputtext(text);
            }
            inputcommand(com);
            if (strcmp(com, "--pos") == 0) {
                scanf("%ld%c%ld", &line, &c, &pos);
//                 for (c = getc(ptr); c != EOF; c = getc(ptr)) {
//                     if(c=='\n' && entercounter<line)
//                         enterbefore++;
//                     if (c == '\n' || ((c!='\0' || c!=EOF)&& e=='\n'))
//                         entercounter++;
//                     if(entercounter<line)
//                         entercounter2++;
//                     e=c;
//                 }
                while (fgets(saver, 200, ptr) != NULL) {
                    if(entercounter<line) {
                        entercounter2 += strlen(saver)+1;
                    }
                    entercounter++;
                }
                //printf("%ld %d",entercounter2,entercounter);
                fseek(ptr,-1,SEEK_END);
                if(line<entercounter || line==1 ||(line==entercounter && fgetc(ptr)=='\n')){
                    rewind(ptr);
                    // printf("%ld %s %ld %ld ", ftell(ptr),text,line,pos);
                    while (fgets(saver, 200, ptr) != NULL) {
                        if (entercounter3 == line) {
                            size = strlen(saver);
                            break;
                        } else
                            entercounter3++;
                    }
                    //printf("%d", size);
                    long int y=0;char a;
                    if(line==entercounter-1){
                        fseek(ptr,-1,SEEK_END);
                        if((a= fgetc(ptr))!='\n')
                            y++;
                        // printf("%c",a);
                    }
                    if (size+y >= pos) {
                        if (fseek(ptr, entercounter2 + pos, SEEK_SET) != 0)
                            printf("Not successful to move pointer\n");
                        else {
                            long int j = 0;
                            for (long int i = entercounter2 + pos; (c = fgetc(ptr)) != EOF; ++i) {
                                saver2[j++] = c;
                            }
                            saver2[j] = '\0';
                            whole = strcat(text, saver2);
                            //printf("%s", whole);
                            //printf("%d %d", ftell(ptr), pos);
                            if (fseek(ptr, entercounter2 + pos, SEEK_SET) != 0)
                                printf("Not successful to move pointer\n");
                            else {
                                if (!fputs(text, ptr)) {
                                    printf("Successful\n");
                                    fclose(ptr);
                                    undotosave(ourroot, -2);
                                }
                                else
                                    printf("Unsuccessful\n");
                            }
                            fclose(ptr);
                        }
                    }
                    else {
                        printf("You cant write in that position\n");
                        fclose(ptr);
                    }
                    fclose(ptr);

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
    //printf("%s",ourroot);
    FILE *ptr=fopen(ourroot,"r+");
     char com[8],c;
     char text[500],saver[200],saver2[200];
     long int line=0,pos=0,entercounter=1,entercounter2=0,entercounter3=1,size=0;
     char *whole;
     if (ptr == NULL) {
         printf("File could not be created or be opened try again\n");
     }
     else {
         inputcommand(com);
         if (strcmp(com, "--str") == 0) {
             getcharx();
             if ((c = getcharx()) == '"')
                 getcot(text);
             else  {
                 text[0]=c;
                 inputtext(text);
             }
             inputcommand(com);
             if (strcmp(com, "--pos") == 0) {
                 scanf("%ld%c%ld", &line, &c, &pos);
//                 for (c = getc(ptr); c != EOF; c = getc(ptr)) {
//                     if(c=='\n' && entercounter<line)
//                         enterbefore++;
//                     if (c == '\n' || ((c!='\0' || c!=EOF)&& e=='\n'))
//                         entercounter++;
//                     if(entercounter<line)
//                         entercounter2++;
//                     e=c;
//                 }
                 while (fgets(saver, 200, ptr) != NULL) {
                     if(entercounter<line) {
                         entercounter2 += strlen(saver)+1;
                     }
                     entercounter++;
                 }
                 //printf("%ld %d",entercounter2,entercounter);
                 fseek(ptr,-1,SEEK_END);
                 if(line<entercounter || line==1 ||(line==entercounter && fgetc(ptr)=='\n')){
                     rewind(ptr);
                    // printf("%ld %s %ld %ld ", ftell(ptr),text,line,pos);
                     while (fgets(saver, 200, ptr) != NULL) {
                         if (entercounter3 == line) {
                             size = strlen(saver);
                             break;
                         } else
                             entercounter3++;
                     }
                             //printf("%d", size);
                     long int y=0;char a;
                     if(line==entercounter-1){
                         fseek(ptr,-1,SEEK_END);
                         if((a= fgetc(ptr))!='\n')
                             y++;
                         // printf("%c",a);
                     }
                             if (size +y >= pos) {
                                 if (fseek(ptr, entercounter2 + pos, SEEK_SET) != 0)
                                     printf("Not successful to move pointer\n");
                                 else {
                                     long int j = 0;

                                     for (long int i = entercounter2 + pos; (c = fgetc(ptr)) != EOF; ++i) {
                                         saver2[j++] = c;
                                     }
                                     saver2[j] = '\0';
                                     whole = strcat(text, saver2);
                                     //printf("%s", whole);
                                     //printf("%d %d", ftell(ptr), pos);
                                     if (fseek(ptr, entercounter2 + pos, SEEK_SET) != 0)
                                         printf("Not successful to move pointer\n");
                                     else {
                                         if (!fputs(text, ptr)) {
                                             printf("Successful\n");
                                             fclose(ptr);
                                             undotosave(ourroot, -2);
                                         }
                                         else
                                             printf("Unsuccessful\n");
                                     }
                                     fclose(ptr);
                                 }
                             }
                             else {
                                 printf("You cant write in that position\n");
                                 fclose(ptr);
                             }
                             fclose(ptr);

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

void cat(){
    char c,s;
    char root[70]={0};
    char dir1[30]="C:\\Users\\Amirhosein\\";
    char dir[30] = "C:\\Users\\Amirhosein";
    char * ourroot,*saver;
    c=getcharx();
    if(c=='\\') {
        inputcommand(root);
        ourroot= strcat(dir1,root);
        //printf("%s",ourroot);
        FILE *ptr=fopen(ourroot,"r");
        if (ptr == NULL) {
            printf("File could not be created or be opened try again\n");
        }
        else {
            while((s=fgetc(ptr))!=EOF) {
                printf("%c",s);
            }
//            while (!feof(ptr)) {
//                saver=fgets(saver, 200, ptr);
//                printf("%s\n", saver);
//            }
        }
        fclose(ptr);
    }
    else  if(c=='"') {
        getcot(root);
        ourroot = strcat(dir, root);
        //printf("%s %s",ourroot,root);
        FILE *ptr = fopen(ourroot, "r");
        if (ptr == NULL) {
            printf("File could not be created or be opened try again\n");
        }
        else {
            while((s=fgetc(ptr))!=EOF) {
                printf("%c",s);
            }
        }
        fclose(ptr);
    }
}

int removex(){
    char c,s,e,way;
    char root[70]={0},com[15],*whole,saver[200],saver2[1000],saver3[1000];
    char dir1[30]="C:\\Users\\Amirhosein\\";
    char dir[30] = "C:\\Users\\Amirhosein";
    char * ourroot;
    long int line,pos,entercounter=1,entercounter2=0,entercounter3=0,size=0,sizego,entercounter4=1;
    c=getcharx();
    //printf("%c",c);
    if(c=='\\') {
        inputcommand(root);
        ourroot = strcat(dir1, root);
       // printf("%s",ourroot);
        FILE *ptr = fopen(ourroot, "r");
        if (ptr == NULL) {
            return 1;
        }
        inputcommand(com);
       // printf("%s",com);
        if(strcmp(com,"--pos")!=0){
            return 2;
        }
        scanf("%ld%c%ld", &line, &s, &pos);
        inputcommand(com);
       // printf("%s",com);
        if(strcmp(com,"-size")!=0){
            return 2;
        }
        scanf("%d",&sizego);
        getcharx();
        e=getcharx();
        way=getcharx();
        while (fgets(saver, 200, ptr) != NULL) {
            if(entercounter<line) {
                entercounter2 += strlen(saver)+1;
            }
            entercounter++;
        }
        //printf("%ld %ld %ld %ld %ld %c %c", ftell(ptr),line,pos,entercounter2,entercounter,e,way);
        entercounter3= ftell(ptr);
        fseek(ptr,-1,SEEK_END);
        if((entercounter<line || (entercounter==line && fgetc(ptr)!='\n' && line != 1)))
            return 3;
        rewind(ptr);
        while (fgets(saver, 200, ptr) != NULL) {
            if (entercounter4 == line) {
                size = ftell(ptr)-entercounter4 - size;
                //printf("%d", size);
                break;
            } else {
                size = ftell(ptr)-entercounter4;
                // printf("%d  ",size);
                entercounter4++;
            }
        }
        long int y=0;char a;
        if(line==entercounter-1){
            fseek(ptr,-1,SEEK_END);
            if((a= fgetc(ptr))!='\n')
                y++;
            // printf("%c",a);
        }
        if(pos>size+y)
            return 4;
        long int j = 0;
        rewind(ptr);
        int x=0;
       // printf("%d %d %d",pos,sizego,size,entercounter4);
        long int entercounter5=0;
        if(way=='f') {
            if(entercounter2 + pos + sizego>entercounter3){
                return 5;}

            for (long int i = 0; i < entercounter2 + pos+1-entercounter4 && (c = fgetc(ptr)) != EOF; ++i) {
                saver2[j++] = c;
            }
            saver2[j] = '\0';
            long int where= ftell(ptr);
            if(fseek(ptr, entercounter2 + pos+sizego, SEEK_SET)!=0)
                return 5;
            if (fseek(ptr, entercounter2 + pos , SEEK_SET) != 0)
                return 5;
            j=0;
            for (long int i = 0; i < sizego && (c = fgetc(ptr)) != EOF; ++i) {
                ;
            }
            j = 0;
            long int where2= ftell(ptr);
            fseek(ptr,where,SEEK_SET);
            while (fgets(saver, 200, ptr) != NULL) {
                if (ftell(ptr)>=where2) {
                    x=entercounter5;
                    break;
                } else {
                    entercounter5++;
                }
            }
            if (fseek(ptr, entercounter2 + pos + sizego+x, SEEK_SET) != 0)
                return 5;
            for (;  (c = fgetc(ptr)) != EOF; ) {
                saver3[j++] = c;
            }
            saver3[j] = '\0';
            whole = strcat(saver2, saver3);
            fclose(ptr);
            ptr=fopen(ourroot,"w");
            //printf("%s",whole);
            if (!fputs(whole, ptr)) {
                undotosave(ourroot,-2);
                fclose(ptr);
                return 7;
            }
            else {
                fclose(ptr);
                return 8;
            }
        }
        else if(way=='b') {
            if(entercounter2-sizego+pos<0)
                return 5;
            for (long int i =0; i < entercounter2-sizego+pos-entercounter4+1 && (c = fgetc(ptr)) != EOF; ++i) {
                saver2[j++] = c;
            }
            saver2[j]='\0';
            long int j = 0;
            if(fseek(ptr, entercounter2 + pos, SEEK_SET)!=0)
                return 5;
            for (;  (c = fgetc(ptr)) != EOF; ) {
                saver3[j++] = c;
            }
            saver3[j] = '\0';
            whole = strcat(saver2, saver3);
            fclose(ptr);
            ptr=fopen(ourroot,"w");
            //printf("%s",whole);
            if (!fputs(whole, ptr)) {
                undotosave(ourroot,-2);
                fclose(ptr);
                return 7;
            }
            else {
                fclose(ptr);
                return 8;
            }
        }
        else {
            fclose(ptr);
            return 2;
        }
    }
    else  if(c=='"') {
        getcot(root);
        ourroot = strcat(dir, root);
        //printf("%s %s",ourroot,root);
        FILE *ptr = fopen(ourroot, "r");
        if (ptr == NULL) {
           return 1;
        }
        inputcommand(com);
        // printf("%s",com);
        if(strcmp(com,"--pos")!=0){
            return 2;
        }
        scanf("%ld%c%ld", &line, &s, &pos);
        inputcommand(com);
        // printf("%s",com);
        if(strcmp(com,"-size")!=0){
            return 2;
        }
        scanf("%d",&sizego);
        getcharx();
        e=getcharx();
        way=getcharx();
        while (fgets(saver, 200, ptr) != NULL) {
            if(entercounter<line) {
                entercounter2 += strlen(saver)+1;
            }
            entercounter++;
        }
        //printf("%ld %ld %ld %ld %ld %c %c", ftell(ptr),line,pos,entercounter2,entercounter,e,way);
        entercounter3= ftell(ptr);
        fseek(ptr,-1,SEEK_END);
        if((entercounter<line || (entercounter==line && fgetc(ptr)!='\n' && line != 1)))
            return 3;
        rewind(ptr);
        while (fgets(saver, 200, ptr) != NULL) {
            if (entercounter4 == line) {
                size = ftell(ptr)-entercounter4 - size;
                //printf("%d", size);
                break;
            } else {
                size = ftell(ptr)-entercounter4;
                // printf("%d  ",size);
                entercounter4++;
            }
        }
        long int y=0;char a;
        if(line==entercounter-1){
            fseek(ptr,-1,SEEK_END);
            if((a= fgetc(ptr))!='\n')
                y++;
            // printf("%c",a);
        }
        if(pos>size+y)
            return 4;
        long int j = 0;
        rewind(ptr);
        long int x=0;
        long int entercounter5=0;
        if(way=='f') {
            if(entercounter2 + pos + sizego>entercounter3){
                return 5;}

            for (long int i = 0; i < entercounter2 + pos+1-entercounter4 && (c = fgetc(ptr)) != EOF; ++i) {
                saver2[j++] = c;
            }
            saver2[j] = '\0';
            long int where= ftell(ptr);
            if(fseek(ptr, entercounter2 + pos+sizego, SEEK_SET)!=0)
                return 5;
            if (fseek(ptr, entercounter2 + pos , SEEK_SET) != 0)
                return 5;
            j=0;
            for (long int i = 0; i < sizego && (c = fgetc(ptr)) != EOF; ++i) {
                ;
            }
            j = 0;
            long int where2= ftell(ptr);
            fseek(ptr,where,SEEK_SET);
            while (fgets(saver, 200, ptr) != NULL) {
                if (ftell(ptr)>=where2) {
                    x=entercounter5;
                    break;
                } else {
                    entercounter5++;
                }
            }
            if (fseek(ptr, entercounter2 + pos + sizego+x, SEEK_SET) != 0)
                return 5;
            for (;  (c = fgetc(ptr)) != EOF; ) {
                saver3[j++] = c;
            }
            saver3[j] = '\0';
            whole = strcat(saver2, saver3);
            fclose(ptr);
            ptr=fopen(ourroot,"w");
            //printf("%s",whole);
            if (!fputs(whole, ptr)) {
                undotosave(ourroot,-2);
                fclose(ptr);
                return 7;
            }
            else {
                fclose(ptr);
                return 8;
            }
        }
        else if(way=='b') {
            if(entercounter2-sizego+pos<0)
                return 5;
            for (long int i =0; i < entercounter2-sizego+pos-entercounter4+1 && (c = fgetc(ptr)) != EOF; ++i) {
                saver2[j++] = c;
            }
            saver2[j]='\0';
            long int j = 0;
            if(fseek(ptr, entercounter2 + pos, SEEK_SET)!=0)
                return 5;
            for (;  (c = fgetc(ptr)) != EOF; ) {
                saver3[j++] = c;
            }
            saver3[j] = '\0';
            whole = strcat(saver2, saver3);
            fclose(ptr);
            ptr=fopen(ourroot,"w");
            //printf("%s",whole);
            if (!fputs(whole, ptr)) {
                undotosave(ourroot,-2);
                fclose(ptr);
                return 7;
            }
            else {
                fclose(ptr);
                return 8;
            }

        }
        else {
            fclose(ptr);
            return 2;
        }


    }
}

int copy() {
    char c, s, e, way;
    char root[70] = {0}, com[15], saver[200];
    char dir1[30] = "C:\\Users\\Amirhosein\\";
    char dir[30] = "C:\\Users\\Amirhosein";
    char *ourroot;
    FILE *ptr;
    long int line, pos, entercounter = 1, entercounter2 = 0, entercounter3 = 0, size = 0, sizego,entercounter4=1;
    c = getcharx();
    //printf("%c",c);
    if (c == '\\') {
        inputcommand(root);
        ourroot = strcat(dir1, root);
        // printf("%s",ourroot);
        ptr = fopen(ourroot, "r");
        if (ptr == NULL) {
            return 1;
        }
    } else if (c == '"') {
        getcot(root);
        ourroot = strcat(dir, root);
        // printf("%s %s",ourroot,root);
        ptr = fopen(ourroot, "r");
        if (ptr == NULL) {
            return 1;
        }
    }
    inputcommand(com);
    // printf(" %s",com);
    if (strcmp(com, "--pos") != 0) {
        return 2;
    }
    scanf("%ld%c%ld", &line, &s, &pos);
    inputcommand(com);
    //printf(" %s",com);
    if (strcmp(com, "-size") != 0) {
        return 2;
    }
    scanf("%d", &sizego);
    getcharx();
    e = getcharx();
    way = getcharx();
    while (fgets(saver, 200, ptr) != NULL) {
        if (entercounter < line) {
            entercounter2 += strlen(saver) + 1;
        }

        entercounter++;
    }

    long int j = 0;
    // printf(" %ld %ld %ld %ld %ld %c %c", ftell(ptr),line,pos,entercounter2,entercounter,e,way);
    entercounter3= ftell(ptr);
    fseek(ptr,-1,SEEK_END);
    if((entercounter<line || (entercounter==line && fgetc(ptr)!='\n' && line != 1)))
        return 3;
    rewind(ptr);
    while (fgets(saver, 200, ptr) != NULL) {
        if (entercounter4 == line) {
            size = ftell(ptr)-entercounter4 - size;
             //printf("%d", size);
            break;
        } else {
            size = ftell(ptr)-entercounter4;
            // printf("%d  ",size);
            entercounter4++;
        }
    }
    if(pos>size)
        return 4;
        if (way == 'f') {
            if (entercounter2 + pos + sizego > entercounter3)
                return 5;
            if (fseek(ptr, entercounter2 + pos + sizego, SEEK_SET) != 0)
                return 5;
            if (fseek(ptr, entercounter2 + pos, SEEK_SET) != 0)
                return 5;
            for (long int i = 0; i < sizego && (c = fgetc(ptr)) != EOF; ++i) {
                cutstr[j++] = c;
            }
            cutstr[j] = '\0';
            j = 0;

        } else if (way == 'b') {
            if (entercounter2 - sizego + pos < 0)
                return 5;
            if (fseek(ptr, entercounter2 + pos - sizego - 1, SEEK_SET) != 0)
                return 5;
            for (long int i = 0; i < sizego && (c = fgetc(ptr)) != EOF; ++i) {
                cutstr[j++] = c;
            }
            cutstr[j] = '\0';
            j = 0;
        }
        fclose(ptr);
        //printf("%s",copystr);
        return 7;
}

int cut(){
    char c,s,e,way;
    char root[70]={0},com[15],*whole,saver[200],saver2[1000],saver3[1000];
    char dir1[30]="C:\\Users\\Amirhosein\\";
    char dir[30] = "C:\\Users\\Amirhosein";
    char * ourroot;
    FILE * ptr;
    long int line,pos,entercounter=1,entercounter2=0,entercounter3=0,size=0,sizego,entercounter4=1;
    c=getcharx();
    //printf("%c",c);
    if(c=='\\') {
        inputcommand(root);
        ourroot = strcat(dir1, root);
        // printf("%s",ourroot);
        ptr = fopen(ourroot, "r");
        if (ptr == NULL) {
            return 1;
        }
    }
    else  if(c=='"') {
        getcot(root);
        ourroot = strcat(dir, root);
        // printf("%s %s",ourroot,root);
        ptr = fopen(ourroot, "r");
        if (ptr == NULL) {
            return 1;
        }
    }
    inputcommand(com);
    // printf(" %s",com);
    if (strcmp(com, "--pos") != 0) {
        return 2;
    }
    scanf("%ld%c%ld", &line, &s, &pos);
    inputcommand(com);
    //printf(" %s",com);
    if (strcmp(com, "-size") != 0) {
        return 2;
    }
    scanf("%d", &sizego);
    getcharx();
    e = getcharx();
    way = getcharx();
    while (fgets(saver, 200, ptr) != NULL) {
        if (entercounter < line) {
            entercounter2 += strlen(saver) + 1;
        }
        entercounter++;
    }
     //printf(" %ld %ld %ld %ld %ld %c %c %ld %ld", ftell(ptr),line,pos,entercounter2,entercounter,e,way,entercounter3,sizego);
    entercounter3= ftell(ptr);
    fseek(ptr,-1,SEEK_END);
    if((entercounter<line || (entercounter==line && fgetc(ptr)!='\n' && line != 1)))
        return 3;
    rewind(ptr);
    while (fgets(saver, 200, ptr) != NULL) {
        if (entercounter4 == line) {
            size = ftell(ptr)-entercounter4 - size;
           // printf("%d", size);
            break;
        } else {
            size = ftell(ptr)-entercounter4;
           // printf("%d  ",size);
            entercounter4++;
        }
    }
    long int y=0;char a;

    if(line==entercounter-1){
        fseek(ptr,-1,SEEK_END);
        if((a= fgetc(ptr))!='\n')
            y++;
       // printf("%c",a);
    }
    if(pos>size+y)
        return 4;
    long int j = 0;
    rewind(ptr);
    int x=0;
    long int entercounter5=0;
    if(way=='f') {
        if(entercounter2 + pos + sizego>entercounter3){
            return 5;}

        for (long int i = 0; i < entercounter2 + pos+1-entercounter4 && (c = fgetc(ptr)) != EOF; ++i) {
            saver2[j++] = c;
        }
        saver2[j] = '\0';
        long int where= ftell(ptr);
        if(fseek(ptr, entercounter2 + pos+sizego, SEEK_SET)!=0)
            return 5;
        if (fseek(ptr, entercounter2 + pos , SEEK_SET) != 0)
            return 5;
        j=0;
        for (long int i = 0; i < sizego && (c = fgetc(ptr)) != EOF; ++i) {
            cutstr[j++] = c;
        }
        cutstr[j] = '\0';
        j = 0;
        long int where2= ftell(ptr);
        fseek(ptr,where,SEEK_SET);
        while (fgets(saver, 200, ptr) != NULL) {
            if (ftell(ptr)>=where2) {
                x=entercounter5;
                break;
            } else {
                entercounter5++;
            }
        }
        if (fseek(ptr, entercounter2 + pos + sizego+x, SEEK_SET) != 0)
            return 5;
        for (; (c = fgetc(ptr)) != EOF;) {
            saver3[j++] = c;
        }
        saver3[j] = '\0';
        //printf("%s",saver3);
        whole = strcat(saver2, saver3);

        fclose(ptr);
        ptr = fopen(ourroot, "w");
        //printf("%s",cutstr);
        if (!fputs(whole, ptr)) {
            undotosave(ourroot,-2);
            fclose(ptr);
            return 7;
        } else {
            fclose(ptr);
            return 8;
        }
    }
    else if(way=='b') {
        if(entercounter2-sizego+pos<0)
            return 5;
        for (long int i =0; i < entercounter2-sizego+pos-entercounter4+1 && (c = fgetc(ptr)) != EOF; ++i) {
            saver2[j++] = c;
        }
        saver2[j]='\0';
        long int j = 0;
        if(fseek(ptr, entercounter2 + pos, SEEK_SET)!=0)
            return 5;
        for (;  (c = fgetc(ptr)) != EOF; ) {
            saver3[j++] = c;
        }
        saver3[j] = '\0';
        whole = strcat(saver2, saver3);
        if (entercounter2 - sizego + pos < 0)
            return 5;
        //printf("%s byyyyy %s",saver2,saver3);
        if (fseek(ptr, entercounter2 + pos -sizego-1 , SEEK_SET) != 0)
            return 5;
        j=0;
        for (long int i = 0; i <  sizego  && (c = fgetc(ptr)) != EOF; ++i) {
            cutstr[j++] = c;
        }
        cutstr[j] = '\0';
        j = 0;
        fclose(ptr);
        ptr=fopen(ourroot,"w");
       // printf("%s",cutstr);
        if (!fputs(whole, ptr)) {
            undotosave(ourroot,-2);
            fclose(ptr);
            return 7;
        }
        else {
            fclose(ptr);
            return 8;
        }
    }

}

int paste(){
    char c, s, e, way;
    char root[70] = {0}, com[15], saver[200],saver2[1000],saver3[1000];
    char dir1[30] = "C:\\Users\\Amirhosein\\";
    char dir[30] = "C:\\Users\\Amirhosein";
    char *ourroot,*whole1,*whole;
    FILE *ptr;
    long int line, pos, entercounter = 1, entercounter2 = 0, entercounter3 = 0, size = 0, sizego,entercounter4=1;
    c = getcharx();
    //printf("%c",c);
    if (c == '\\') {
        inputcommand(root);
        ourroot = strcat(dir1, root);
        // printf("%s",ourroot);
        ptr = fopen(ourroot, "r");
        if (ptr == NULL) {
            return 1;
        }
    } else if (c == '"') {
        getcot(root);
        ourroot = strcat(dir, root);
        // printf("%s %s",ourroot,root);
        ptr = fopen(ourroot, "r");
        if (ptr == NULL) {
            return 1;
        }
    }
    inputcommand(com);
    // printf(" %s",com);
    if (strcmp(com, "--pos") != 0) {
        return 2;
    }
    scanf("%ld%c%ld", &line, &s, &pos);

    //printf(" %s",com);
    while (fgets(saver, 200, ptr) != NULL) {
        if (entercounter < line) {
            entercounter2 += strlen(saver) + 1;
        }

        entercounter++;
    }

    long int j = 0;
    // printf(" %ld %ld %ld %ld %ld %c %c", ftell(ptr),line,pos,entercounter2,entercounter,e,way);
    entercounter3= ftell(ptr);
    fseek(ptr,-1,SEEK_END);
    if((entercounter<line || (entercounter==line && fgetc(ptr)!='\n' && line != 1)))
        return 3;
    rewind(ptr);
    while (fgets(saver, 200, ptr) != NULL) {
        if (entercounter4 == line) {
            size = strlen(saver);
            //printf(" %d",size);
            break;
        } else
            entercounter4++;
    }
    long int y=0;char a;
    if(line==entercounter-1){
        fseek(ptr,-1,SEEK_END);
        if((a= fgetc(ptr))!='\n')
            y++;
        // printf("%c",a);
    }
    if(pos>size+y)
        return 4;
    rewind(ptr);
    for (long int i = 0; i < entercounter2 + pos+1-entercounter4 && (c = fgetc(ptr)) != EOF; ++i) {
        saver2[j++] = c;
    }
    saver2[j] = '\0';
    j = 0;
    for (; (c = fgetc(ptr)) != EOF;) {
        saver3[j++] = c;
    }
    saver3[j] = '\0';
    //printf("%syyyyy %s",saver2,saver3);
    whole1= strcat(cutstr,saver3);
    fclose(ptr);
    fopen(ourroot,"w");
    if (!fputs(saver2, ptr)) {
        fclose(ptr);
        fopen(ourroot,"a+");
        if (!fputs(whole1, ptr)) {
            undotosave(ourroot,-2);
            fclose(ptr);
            return 7;
        }
        else {
            fclose(ptr);
            return 8;
        }
    }
    else {
        fclose(ptr);
        return 8;
    }

}

void switchx(int answer){
    switch (answer) {
        case 1:
            printf("File could not be created or be opened try again\n");
            break;
        case 2:
            printf("Invalid input try again\n");
            break;
        case 3:
            printf("You cant do this action in that line\n");
            break;
        case 4:
            printf("You cant do this action in that position\n");
            break;
        case 5:
            printf("You cannot move that much\n");
            break;
        case 6:
            printf("Not successful to move pointer\n");
            break;
        case 7:
            printf("Successful\n");
            break;
        case 8:
            printf("Unsuccessful\n");
            break;
    }
}

void getfind(char string[]){
    int counter=0;
    char c,d;
    while(1){
        c=getcharx();
        if(c=='"' && string[counter-1]!='\\') {
            string[counter] = '\0';
            break;
        }
        else if(c=='\\') {
            if((d = getcharx())=='"')
                string[counter]=d;
        }
        else
            string[counter]=c;
        counter++;
    }
}

void inputfind(char string[]){
    int counter=1;
    char c,d;
    while(1){
        c=getcharx();
        if(c==' ') {
            string[counter]='\0';
            break;
        }
        else
            string[counter]=c;
        counter++;
    }

}
int findstr() {
    char c, e, *ourroot, text[300], text2[300], com[15], root[70], saver[400], *wherefind = "";
    char dir1[30] = "C:\\Users\\Amirhosein\\";
    char dir[30] = "C:\\Users\\Amirhosein";
    char wholefile[8000], *whole,*token,*token2[30];
    int x = 0;
    FILE *ptr,*ptrr;
    //getcharx();
    if ((c = getcharx()) == '"')
        getfind(text);
    else {
        text[0] = c;
        inputfind(text);
    }
    //printf("%s",text);
    inputcommand(com);
    if (strcmp(com, "--file") != 0) {
        return -2;
    }
    getcharx();
    if ((c = getcharx()) == '\\') {
        inputcommand(root);

        ourroot = strcat(dir1, root);
        //printf("%s",ourroot);
        ptr = fopen(ourroot, "r");
        ptrr= fopen(ourroot,"r");
        if (ptr == NULL) {
            return -3;
        }
    } else if (c == '"') {
        getcot(root);
        ourroot = strcat(dir, root);
        // printf("%s %s",ourroot,root);
        ptr = fopen(ourroot, "r");
        ptrr= fopen(ourroot,"r");
        if (ptr == NULL) {
            return -3;
        }
    }
    //printf("%s",text);
    int flag=1,entercounter=0;
    if(text[strlen(text) - 1] == '*' && text[strlen(text) - 2] !='\\')
        flag=0;
    if (text[0] != '*'  && flag==1 ) {
//            char *e;
//            e = strrchr(file, '\\');
//            (int)(e-file)
        for (int i = 0,j=0; text[i] != '\0'; ++i,++j) {
            if (text[i] == '\\' && text[i + 1] == '*')
                text2[j] = text[++i];
            else
                text2[j] = text[i];
        }
    } else if (text[0] == '*') {
        for (int i = 1, j = 0; text[i] != '\0'; ++i, ++j) {
            if (text[i] == '\\' && text[i + 1] == '*')
                text2[j] = text[++i];
            else
                text2[j] = text[i];
        }
    }
    else if(flag==0) {
        for (int i = 0, j = 0;; ++i, ++j) {
            if (text[i] == '*' && text[i - 1] != '\\')
                break;
            if (text[i] == '\\' && text[i + 1] == '*')
                text2[j] = text[++i];
            else
                text2[j] = text[i];
        }
    }
    text2[strlen(text2)+1]='\0';
    int counter=0;
//        for (int i = 0; i < strlen(text2); ++i) {
//            if(text2[i]==' ')
//                counter++;
//        }
    int i=1,l=1,times=0;
    //printf("%s",text2);
    if ((e = getcharx()) == '\n' ) {
        if (text[0] != '*' && flag==1) {
            while (fgets(saver, 300, ptr) != NULL) {
                if ((wherefind = strstr(saver, text2)) != NULL) {
                    int y = (int) (wherefind - saver);
                    printf("at position :%d ", x + y-entercounter);
                    fclose(ptr);
                    return 1;
                }
                x = ftell(ptr);
                entercounter++;
            }
            if (wherefind == NULL) {
                fclose(ptr);
                return -1;
            }
        }
//        char *star;
//            star = strrchr(text, '~');
//            s=(int)(star-text);
        else {
            if (text[0] == '*' &&flag==1) {
                while (fgets(saver, 300, ptr) != NULL) {
                    if ((wherefind = strstr(saver, text2)) != NULL) {
                        int y = (int) (wherefind - saver);
                        fseek(ptr,x+y-1,SEEK_SET);
                        //printf("%d", ftell(ptr));
                        char star;
                        for (i=1; (star=fgetc(ptr))!=' ' && star!='\n'&& x+y-i!=-1;++i) {
                           // printf(" %c %d",star, ftell(ptr));
                            y--;
                            fseek(ptr,-2,SEEK_CUR);
                        }
                        if(i!=1) {
                            //printf("%d",y);
                            printf("at position :%d ", x + y-entercounter);
                            times++;
                            fclose(ptr);
                            return 1;
                        }
                    }
                    //printf("%d %d", strlen(saver), ftell(ptr));
                    x = ftell(ptr);
                    entercounter++;
                }
                if (times==0) {
                    fclose(ptr);
                    return -1;
                }
            }
            else {
                while (fgets(saver, 300, ptr) != NULL) {
                    int size= strlen(text2);
                    if ((wherefind = strstr(saver, text2)) != NULL) {
                        int y = (int) (wherefind - saver);
                        fseek(ptr,x+y+size,SEEK_SET);
                        //printf("%d", ftell(ptr));
                        char star;
                        for (l=1; (star=fgetc(ptr))!=' ' && star!='\n';++l) {
                             //printf(" %c %d",star, ftell(ptr));
                        }
                        if(l!=1) {
                            //printf("%d",y);
                            printf("at position :%d ", x + y-entercounter);
                            times++;
                            fclose(ptr);
                            return 1;
                        }
                    }
                    //printf("%d %d", strlen(saver), ftell(ptr));
                    x = ftell(ptr);
                    entercounter++;
                }
                if (times==0) {
                    fclose(ptr);
                    return -1;
                }
            }
        }
    }
        else if (e == ' ') {
        char *dup, *dup2;
        int ii, j,at, found, whereshould, z;
        int strLen, wordLen, timecounter = 0;
        char delim[] = " ,.!:;\n";
        int places[30], placesbyword[30], bywordcounter = 0, bywordcounter2 = 0, bywordcounter3 = 0, bywordplace = 0;
        inputcommand(com);
        if (strcmp(com, "-count") == 0 || strcmp(com, "-at") == 0 || strcmp(com, "-all") == 0 || strcmp(com, "-byword") == 0) {
            if(strcmp(com,"-at")==0){
                scanf("%d", &at);
            }
            while (fgets(saver, 300, ptrr) != NULL) {
                dup = strdup(saver);
                //printf("%s",dup2);
                // printf(" %dttt", ftell(ptrr));
                strLen = strlen(saver);
                wordLen = strlen(text2);
                for (ii = 0; ii <= strLen - wordLen; ii++) {
                    found = 1;
                    for (j = 0; j < wordLen; j++) {
                        if (saver[ii + j] != text2[j]) {
                            found = 0;
                            break;
                        }
                    }
                    if (found == 1) {
                        bywordplace = 0;
                        bywordcounter2 = 0;
                        if (text[0] == '*' && flag == 1) {
                            dup2 = strdup(saver);
                            int y = ii;
                            fseek(ptr, x + y - 1, SEEK_SET);
                            //  printf("%d %d",ii, ftell(ptr));
                            char star;
                            for (i = 1; (star = fgetc(ptr)) != ' ' && star != '\n' && x + y - i != -1; i++) {
                                //printf(" %c %d",star, ftell(ptr));
                                y--;
                                fseek(ptr, -2, SEEK_CUR);
                            }
                            printf( "%dtt",y,saver);
                            if (i != 1) {
                                token2[timecounter] = strtok(dup2, delim);
                                bywordplace += strlen(token2[timecounter]);
                                while (bywordplace <= y) {
                                     //printf(" %d %d %s",bywordcounter2,bywordplace,token2[timecounter]);
                                    bywordcounter2++;
                                    token2[timecounter] = strtok(NULL, delim);
                                    bywordplace += strlen(token2[timecounter])+1;
                                }
                                placesbyword[timecounter] = bywordcounter + bywordcounter2;
                                //  printf(" tt%d %d %d ",bywordcounter,bywordcounter2,placesbyword[timecounter]);
                                places[timecounter++] = x + y-entercounter;

                                //printf("%d", ftell(ptr));
                                // printf("at position :%d ", x + y);
                            }
                        } else if (text[strlen(text) - 1] == '*' && text[strlen(text) - 2] != '\\') {
                            dup2 = strdup(saver);
                            int size = strlen(text2);
                            int y = ii;
                            fseek(ptr, x + y + size, SEEK_SET);
                            //printf("%d", ftell(ptr));
                            char star;

                            for (l = 1; (star = fgetc(ptr)) != ' ' && star != '\n'; ++l) {
                                // printf(" %c %d",star, ftell(ptr));
                            }
                            if (l != 1) {
                                dup2 = strdup(saver);
                                token2[timecounter] = strtok(dup2, delim);
                                bywordplace += strlen(token2[timecounter]);
                                while (bywordplace <= y) {
                                    // printf("%d %d %s",bywordcounter2,bywordplace,token2[timecounter]);
                                    bywordcounter2++;
                                    token2[timecounter] = strtok(NULL, delim);
                                    bywordplace += strlen(token2[timecounter])+1;
                                }
                                //printf("yyyyyy");
                                //printf("at position :%d ", x + y);
                                placesbyword[timecounter]=bywordcounter+bywordcounter2;
                                places[timecounter++] = x + y-entercounter;

                            }
                        } else if (text[0] != '*' && flag == 1) {
                            dup2 = strdup(saver);
                            token2[timecounter] = strtok(dup2, delim);
                            bywordplace += strlen(token2[timecounter]);
                           // printf("%dii",ii);
                            while (bywordplace <= ii) {
                               //  printf("%d ",bywordplace,token2[timecounter]);
                                bywordcounter2++;
                                token2[timecounter] = strtok(NULL, delim);
                                bywordplace += strlen(token2[timecounter])+1;
                            }
                            placesbyword[timecounter]=bywordcounter+bywordcounter2;
                            places[timecounter++] = x + ii-entercounter;
                        }
                    }

                }
                x = ftell(ptrr);
                token = strtok(dup, delim);
                while (token != NULL) {
                    //printf("%s  ",token);
                    bywordcounter++;
                    token = strtok(NULL, delim);
                }
                entercounter++;

//                    printf("ftell %d %d ", ftell(ptrr), ftell(ptr));
                 printf("%d  ",bywordcounter);
            }
            if (getcharx() == '\n') {
                if (timecounter == 0) {
                    fclose(ptr);
                    fclose(ptrr);
                    return -1;
                } else {
                    if (strcmp(com, "-count") == 0) {
                        printf("%d ", timecounter);
                        fclose(ptr);
                        fclose(ptrr);
                        return 2;
                    } else if (strcmp(com, "-at") == 0) {
                        if (at > timecounter) {
                            fclose(ptr);
                            fclose(ptrr);
                            return -4;
                        }
                        printf("%dth times is in %d ", at, places[at - 1]);
                        fclose(ptr);
                        fclose(ptrr);
                        return 3;
                    } else if (strcmp(com, "-all") == 0) {
                        for (int k = 0; k < timecounter; ++k) {
                            printf("%d,", places[k]);
                        }
                        fclose(ptr);
                        fclose(ptrr);
                        return 4;
                    } else if (strcmp(com, "-byword") == 0) {
                        printf("at position: %d ", placesbyword[0]+1-counter);
                        fclose(ptrr);
                        fclose(ptr);
                        return 1;
                    }
                }
            }
            else{
                char com2[15];
                if (timecounter == 0) {
                    fclose(ptr);
                    fclose(ptrr);
                    return -1;
                }
                if(strcmp(com,"-at")==0){
                    inputcommand(com2);
                    if(strcmp(com2,"-byword")!=0)
                        return -2;
                    if (at > timecounter) {
                        fclose(ptr);
                        fclose(ptrr);
                        return -4;
                    }
                    printf("%dth times is in %d ", at, placesbyword[at - 1]+1-counter);
                    fclose(ptr);
                    fclose(ptrr);
                    return 3;
                }
                else if(strcmp(com,"-all")==0){
                    inputcommand(com2);
                    for (int k = 0; k < timecounter; ++k) {
                        printf("%d,", placesbyword[k] + 1-counter);
                    }fclose(ptrr);
                        fclose(ptr);
                        return 4;
                }
            }
        }
        else
            return -2;
    }
    }

int cutpaste(int pos,int sizego,char string[],char ourroot[]){
    char saver2[4000],saver3[4000],c,saver[500],*whole1;
    FILE *ptr;
    ptr= fopen(ourroot,"r");
    int j=0,x=0,entercounter5=0;
    //printf("ttt%d",pos);
    for (int i = 0; i < pos&& (c = fgetc(ptr)) != EOF ; ++i) {
        //printf("%diiiiii",i);
        //printf("%c",c);
        saver2[j++] = c;
    }
    saver2[j] = '\0';
    // printf("%s\n\n\n",saver2);
    long int where= ftell(ptr);
    //printf("%d",sizego);
    //fseek(ptr,  pos+sizego , SEEK_SET);
    j=0;
    for (long int i = 0; i < sizego && (c = fgetc(ptr)) != EOF; ++i) {
        ;
    }

    j = 0;
//    long int where2= ftell(ptr);
//    fseek(ptr,where,SEEK_SET);
//    while (fgets(saver, 200, ptr) != NULL) {
//        if (ftell(ptr)>=where2) {
//            x=entercounter5;
//            break;
//        } else {
//            entercounter5++;
//        }
//    }
//    printf("%d %d %d ",pos,sizego,x);
//    if (fseek(ptr, pos + sizego+x , SEEK_SET) != 0)
//        return 5;
//    printf("%d", ftell(ptr));
    //printf("%d", sizego);
    for (; (c = fgetc(ptr)) != EOF;) {
        saver3[j++] = c;
    }
    saver3[j] = '\0';
    whole1= strcat(saver2,string);
    fclose(ptr);
    //printf("%s\n\n\n\n",saver3);
    ptr= fopen(ourroot,"w");
    if (!fputs(whole1, ptr)) {
        fclose(ptr);
        fopen(ourroot,"a+");
        if (!fputs(saver3, ptr)) {
            fclose(ptr);
            return 5;
        }
        else {
            fclose(ptr);
            return -5;
        }
    } else {
        fclose(ptr);
        return -5;
    }

}

int replace() {
    char c, e, *ourroot, text[300], text2[300],texttowrite[200], com[15], root[70], saver[400], *wherefind = "";
    char dir1[30] = "C:\\Users\\Amirhosein\\";
    char dir[30] = "C:\\Users\\Amirhosein";
    char wholefile[8000], *whole, *token, *token2[30];
    int x = 0;
    FILE *ptr, *ptrr,*fileptr;
    getcharx();
    if ((c = getcharx()) == '"')
        getfind(text);
    else {
        text[0] = c;
        inputfind(text);
    }
//printf("%s",text);
    inputcommand(com);
    if (strcmp(com, "--str2") != 0) {
        return -2;
    }
    getcharx();
    if ((c = getcharx()) == '"')
        getcot(texttowrite);
    else  {
        texttowrite[0]=c;
        inputtext(texttowrite);
    }
    inputcommand(com);
    if(strcmp(com,"--file")!=0)
        return -2;
    int flag = 1, entercounter = 0,howmuch=0;
    getcharx();
    if ((c = getcharx()) == '\\') {
        inputcommand(root);

        ourroot = strcat(dir1, root);
//printf(" %s",ourroot);
        ptr = fopen(ourroot, "r");
        ptrr = fopen(ourroot, "r");
        if (ptr == NULL) {
            return -3;
        }
    }
    else if (c == '"') {
        getcot(root);
        ourroot = strcat(dir, root);
// printf("%s %s",ourroot,root);
        ptr = fopen(ourroot, "r");
        ptrr = fopen(ourroot, "r");
        if (ptr == NULL) {
            return -3;
        }
    }
//printf("%s",text);
    if (text[strlen(text) - 1] == '*' && text[strlen(text) - 2] != '\\')
        flag = 0;
    if (text[0] != '*' && flag == 1) {
//            char *e;
//            e = strrchr(file, '\\');
//            (int)(e-file)
        for (int i = 0, j = 0; text[i] != '\0'; ++i, ++j) {
            if (text[i] == '\\' && text[i + 1] == '*')
                text2[j] = text[++i];
            else
                text2[j] = text[i];
        }
    } else if (text[0] == '*') {
        for (int i = 1, j = 0; text[i] != '\0'; ++i, ++j) {
            if (text[i] == '\\' && text[i + 1] == '*')
                text2[j] = text[++i];
            else
                text2[j] = text[i];
        }
    } else if (flag == 0) {
        for (int i = 0, j = 0;; ++i, ++j) {
            if (text[i] == '*' && text[i - 1] != '\\')
                break;
            if (text[i] == '\\' && text[i + 1] == '*')
                text2[j] = text[++i];
            else
                text2[j] = text[i];
        }
    }
    text2[strlen(text2) + 1] = '\0';
    int counter = 0,at;
    if((e=getcharx())=='\n')
        howmuch=1;
    else if(e==' '){
        inputcommand(com);
        if(strcmp(com,"-at")==0)
            scanf("%d",&at);
    }
    //printf("%s",com);
    int ii, j, found;
    int i,l;
    int strLen, wordLen, timecounter = 0;
    int places[30];
    int sizetogive[30],wherefinish[30];
    while (fgets(saver, 300, ptrr) != NULL) {
        //printf("%s",dup2);
        // printf(" %dttt", ftell(ptrr));
        strLen = strlen(saver);
        wordLen = strlen(text2);
        for (ii = 0; ii <= strLen - wordLen; ii++) {
            found = 1;
            for (j = 0; j < wordLen; j++) {
                if (saver[ii + j] != text2[j]) {
                    found = 0;
                    break;
                }
            }
            if (found == 1) {
                if (text[0] == '*' && flag == 1) {
                    int y = ii;
                    fseek(ptr, x + y - 1, SEEK_SET);
                    //  printf("%d %d",ii, ftell(ptr));
                    char star;
                    for (i = 0; (star = fgetc(ptr)) != ' ' && star != '\n' && x + y - i != -1; i++) {
                        //printf(" %c %d",star, ftell(ptr));
                        y--;
                        fseek(ptr, -2, SEEK_CUR);
                    }
                    // printf( "%dtt",y,saver);
                    if (i != 0) {
                        //  printf(" tt%d %d %d ",bywordcounter,bywordcounter2,placesbyword[timecounter]);
                        places[timecounter] = x + y-entercounter;
                        sizetogive[timecounter++]=i+wordLen;
                        if(howmuch==1 &&timecounter==1)
                            return cutpaste(places[0],sizetogive[0],texttowrite,ourroot);
                        //printf("%d", ftell(ptr));
                        // printf("at position :%d ", x + y);
                    }
                } else if (text[strlen(text) - 1] == '*' && text[strlen(text) - 2] != '\\') {
                    int size = strlen(text2);
                    int y = ii;
                    fseek(ptr, x + y + size, SEEK_SET);
                    //printf("%d", ftell(ptr));
                    char star;

                    for (l = 0; (star = fgetc(ptr)) != ' ' && star != '\n'; ++l) {
                        // printf(" %c %d",star, ftell(ptr));
                    }
                    if (l != 0) {
                        //printf("at position :%d ", x + y);
                        places[timecounter] = x + y-entercounter;
                        sizetogive[timecounter++]=l+wordLen;
                        if(howmuch==1 && timecounter==1)
                            return cutpaste(places[0],sizetogive[0],texttowrite,ourroot);

                    }
                } else if (text[0] != '*' && flag == 1) {
                    places[timecounter] = x + ii-entercounter;
                    sizetogive[timecounter++]= wordLen;
                    //printf(" %lld %lld", strlen(text2),i);
                    if(howmuch==1 && timecounter==1)
                        return cutpaste(places[0],sizetogive[0],texttowrite,ourroot);
                }
            }

        }
        x = ftell(ptrr);
        entercounter++;

//                    printf("ftell %d %d ", ftell(ptrr), ftell(ptr));
    }
    if (timecounter == 0) {
        fclose(ptr);
        fclose(ptrr);
        return -1;
    }
    else {
        if (strcmp(com, "-at") == 0) {
            if (at > timecounter) {
                fclose(ptr);
                fclose(ptrr);
                return -4;
            }
            //printf("%dth times is in %d ", at, places[at - 1]);
            fclose(ptr);
            fclose(ptrr);
            undotosave(ourroot,-2);
            return cutpaste(places[at-1],sizetogive[at-1],texttowrite,ourroot);
        }
        else if (strcmp(com, "-all") == 0) {
            fclose(ptr);
            fclose(ptrr);
            int a,sizeforward=0,w;
            for (int k = 0; k < timecounter; ++k) {
               // printf("%d,", places[k]);
                w=places[k]+sizeforward;
                a=cutpaste(w,sizetogive[k],texttowrite,ourroot);
                sizeforward+=strlen(texttowrite)-sizetogive[k];
                if(a==5)
                    continue;
                else break;
            }
            undotosave(ourroot,-2);
            return a;
        }
    }

}


void switchfind(int answer){
    switch (answer) {
        case -2:
            printf("Invalid input try again\n");
            break;
        case -3:
            printf("File couldnt be opened or be created\n");
            break;
        case -4:
            printf("We dont have that much of you have searched in ourfile\n");
            break;
        case -5:
            printf("Unssuccessful\n");
            break;
        case -1:
            printf("returned -1 string not found\n");
            break;
        case 1:
            printf("String found\n");
            break;
        case 2:
            printf("Strings found\n");
            break;
        case 3:
            printf("position\n");
            break;
        case 4:
            printf("\n");
            break;
        case 5:
            printf("Successful\n");

    }
}

int grep(int sign){
    char c, e, *ourroot, text[300], com[15], root[70], saver[400],*wherefind,*whichfiles[50];
    char dir1[30] = "C:\\Users\\Amirhosein\\";
    char dir[30] = "C:\\Users\\Amirhosein";
    int times=0,eachfile[50]={0},counter=0;
    FILE *ptr;
    if(sign==1 || sign ==2) {
        inputcommand(com);
        getcharx();
        if (strcmp(com, "--str") != 0) {
            // printf("%s", com);
            return -1;
        }
    }
    if ((c = getcharx()) == '"')
        getfind(text);
    else {
        text[0] = c;
        inputfind(text);
    }
    inputcommand(com);
    if(strcmp(com,"--files")!=0) {
        printf("%s", com);
        return -1;
    }
    //printf("%s %s",com,text);
    while(getcharx()!='\n') {
        int sign2=0;
        if ((c = getcharx()) == '\\') {
            inputcommand(root);
            ourroot = strcat(dir1, root);
            //printf("%s",ourroot);
            ptr = fopen(ourroot, "r");
            if (ptr == NULL) {
                return -2;
            }
        } else if (c == '"') {
            getcot(root);
            ourroot = strcat(dir, root);
            // printf("%s %s",ourroot,root);
            ptr = fopen(ourroot, "r");
            if (ptr == NULL) {
                return -2;
            }
        }
        while (fgets(saver, 300, ptr) != NULL) {
            if ((wherefind = strstr(saver, text)) != NULL) {
                if(sign==3)
                    printf("In file %s :%s",root,saver);
                times++;
                sign2=1;
                if(eachfile[counter]!=1){
                    whichfiles[counter]= strdup(root);
                    //printf("%s",whichfiles[counter]);
                }
            }
        }
        fclose(ptr);
        if(sign2==1)
            counter++;

    }
    //printf("%d",counter);
    if(times==0)
        return -4;
    else if(sign==1){
        printf("%d\n",times);
        return 6;
    }
    else if(sign==2){
        for (int i = 0; i<counter; ++i) {
            printf("%s\n",whichfiles[i]);
        }
        return 6;
    }
}
void switchgrep(int answer) {
    switch (answer) {
        case -1:
            printf("Invalid input try again\n");
            break;
        case -2:
            printf("File couldnt be opened or be created\n");
            break;
        case -3:
            printf("returned -1 string not found\n");
            break;
        case -4:
            printf("Not found in any file\n");
            break;
        case 6:
            printf("");
            break;
    }
}


int main() {
    char com[15],com2[8],c;
    int answer=-1;
    char root[100],*ourroot;
    char dir1[30] = "C:\\Users\\Amirhosein\\";
    char dir[30] = "C:\\Users\\Amirhosein";
    char dir3[50]="C:\\Users\\Amirhosein\\root\\";
   // tree(dir3,1,-1,1);
    printf("User Guide:\n A:for creating file or folder:\n   1-createfile --file <file name and address>\n   2-createfile --file <\"file name and address\">"
           "(if your folder or your filenames have space\n   *Note:if you are willing to create folders only type '\\' at the end\n   Example:\\root\\1\\abc.txt\n"
           " B:insertfile:\n    1-insertstr --file <file name and address> –str <str> --pos <line no>:<start position>\n    2-You can enter string or filename with cotation same as createfile"
           "command\n C:Showing the content of a file:\n   1-cat --file <file name and address>\n D:For removing:\n   1-removestr --file <file name> --pos <line no>:<start position> -size\n"
           "<number of characters to remove> -f -b <forward or backward>\n D:For copy:\n   1-copystr --file <file name> --pos <line no>:<start position> -size <number of characters to copy> -f -b <forward or backward>\n E:for cut:\n"
           "   1-cutstr --file <file name> --pos <line no>:<start position> -size <number of characters to cut> -f -b <forward or backward>\n F:For paste:\n   1-pastestr --file <file name> --pos "
           "<line no>:<start position>\n G:For find:\n   1-find --str <str> --file <file name>\n   2-You can add -at,-count-all,-byword to the end(you can use -at of -all with byword)\n"
           "H:For replacing:\n   1-replace --str1 <str> --str2 <str> --file <file name> [-at <num> | -all]\n I:For grep:\n   1-grep [options] --str <pattern> --files [<file1> <file2> <file3> ...]\n"
           "   2-You can use optiong -c(to show number of pattern) or -l(to show filenames) or nothing(to show all)\n J:for undo:\n   1-undo --file <file>\n   2-you can undo 10 times and files"
           "that existed before runnig will have their first contents too\n ");

    inputcommand(com);
    while(strcmp(com,"exit")!=0){
        if(strcmp(com,"createfile")==0){
            inputcommand(com2);
            getcharx();
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
            getcharx();
            if (strcmp(com2, "--file") == 0) {
                c=getcharx();
                if(c=='\\') {
                    fileinserternonspace();
                }
                else  if(c=='"') {
                    fileinserterspace();
                }
                else
                    printf("Invalid Input\n");
            }
        }
        else if(strcmp(com,"cat")==0) {
            inputcommand(com2);
            getcharx();
            if(strcmp(com2,"--file")==0){
                cat();
            }
            else
                printf("Invalid Input\n");
        }
        else if(strcmp(com,"removestr")==0){
            inputcommand(com2);
            getcharx();
            if(strcmp(com2,"--file")==0){
                answer=removex();
                switchx(answer);
            }
            else
                printf("Invalid input\n");
        }
        else if(strcmp(com,"copystr")==0) {
            inputcommand(com2);
            getcharx();
            if (strcmp(com2, "--file") == 0) {
                answer = copy();
                switchx(answer);
            }
            else
                printf("Invalid input\n");
        }
        else if(strcmp(com,"cutstr")==0) {
            inputcommand(com2);
            getcharx();
            if (strcmp(com2, "--file") == 0) {
                answer = cut();
                switchx(answer);
            } else
                printf("Invalid input\n");
        }
        else if(strcmp(com,"pastestr")==0) {
            inputcommand(com2);
            getcharx();
            if (strcmp(com2, "--file") == 0) {
                answer = paste();
                switchx(answer);
            } else
                printf("Invalid input\n");
        }
        else if(strcmp(com,"find")==0) {
            inputcommand(com2);
            getcharx();
            if (strcmp(com2, "--str") == 0) {
                answer = findstr();
                switchfind(answer);
            } else
                printf("Invalid input\n");
        }
        else if(strcmp(com,"replace")==0){
            inputcommand(com2);
            getcharx();
            if (strcmp(com2, "--str1") == 0) {
                answer = replace();
                switchfind(answer);
            } else
                printf("Invalid input\n");
        }
        else if (strcmp(com, "grep")==0) {
            inputcommand(com2);
            getcharx();
            if (strcmp(com2, "-c") == 0) {
                answer = grep(1);
                switchgrep(answer);
            } else if (strcmp(com2, "-l") == 0) {
                answer=grep(2);
                switchgrep(answer);
            } else if (strcmp(com2, "--str") == 0) {
                answer=grep(3);
                switchgrep(answer);
            } else
                printf("Invalid input\n");
        }
        else if(strcmp(com,"undo")==0) {
            inputcommand(com2);
            getcharx();
            if (strcmp(com2, "--file") == 0) {

                if ((c = getcharx()) == '\\') {
                    inputcommand(root);
                    ourroot = strcat(dir1, root);
                    //printf(" %s",ourroot);
                }
                else if (c == '"') {
                    getcot(root);
                    ourroot = strcat(dir, root);
                    // printf("%s %s",ourroot,root);
                }
              //  printf("%s",ourroot);
                answer=undo(ourroot);
                //answer=undo(ourroot);
            } else
                printf("Invalid input\n");
        }
        else if(strcmp(com,"tree")==0) {
            inputcommand(com2);
            getcharx();
            if (strcmp(com2, "--file") == 0) {
                if ((c = getcharx()) == '\\') {
                    inputcommand(root);
                    ourroot = strcat(dir1, root);
                    //printf(" %s",ourroot);
                } else if (c == '"') {
                    getcot(root);
                    ourroot = strcat(dir, root);
                    // printf("%s %s",ourroot,root);
                }
                int depth;
                scanf("%d",&depth);
                if(depth<-1)
                    printf("Invalid input for depth\n");
                else {
                    printf("Directory tree is:\n");
                    tree(ourroot, 1, depth, 0);
                }
            } else
                printf("Invalid input\n");
        }
        else {
            if(getcharx()=='\n')
                printf("Invalid Input\n");
        }
        inputcommand(com);
    }
    return 0;
}

