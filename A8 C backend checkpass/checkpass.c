#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main() {
    //print esential tag and text
    printf("Content-Type:text/html\n\n");
    printf("<html><body>");
    
    char array[200];
    char copy[200];
    char username[200];
    char password[200];
    char *p;
    char *s;
    int n = atoi(getenv("CONTENT_LENGTH"));
    if(fgets(array,n+1,stdin)==NULL){
            printf("<h1>No input</h1>");
            printf("</body></html>");
            return 0;
            }

    //printf("<h1>%s</h1>", array);
    //copy array to another array called copy
    strcpy(copy,array);
    //split array with & symbol,p is the first half
    p = strtok(array, "&");
    if(p)
    {
        //split first half of array with "="
        s=strtok(p, "=");
        //get username which locates after "="
        s=strtok(NULL, "=");
        //save username into variable
        strcpy(username,s);
        //printf("<h1>%s</h1>", s);
    }
    //now use the copy to get the password
    p = strtok(copy, "&");
    p = strtok(NULL, "&");
    if(p){
        s=strtok(p, "=");
        s=strtok(NULL, "=");
        strcpy(password,s);
      //  printf("<h1>%s</h1>", s);
    }else{
        //if didn't get any password, error
        printf("<h1>error with your password</h1>");
        printf("</body></html>");
        return 0;
    }
    //read csv file
    FILE *the_file=fopen("users.csv","r");
    if (the_file==NULL) {
        //if cannot get to csv, show error
        printf("database disconnected</body></html>");
        return 0;
    }
    char line[200];
    //read csv line by line
    while (fgets(line,sizeof(line),the_file)) {
        char *s;
        char *p;
        s=strtok(line,",");
        //printf("<h1>%s</h1>", s);
        //printf("<h1>%s</h1>", username);
        if (s!=NULL) {
            if (strcmp(s,username)==0){ //printf("<h1>usernamematched</h1></body></html>");
                s=strtok(NULL,",");
                //printf("<h1>%s</h1>", s);
                strcpy(copy,s);
                //since every line has an new-line-symbol in the end, remove it.
                p=strtok(copy,"\n");
                //printf("<h1>%s</h1>", p);
                //printf("<h1>%s</h1>", password);
                if(strcmp(password,p)==0){
                    printf("<h1>Your Password Matches</h1></body></html>");
                    return 0;
                }
            }
        }
    }
    //loop to the end and didn't find the matched pair=>wrong password
    printf("<h1>Wrong username or password</h1></body></html>");
    return 0;
}
