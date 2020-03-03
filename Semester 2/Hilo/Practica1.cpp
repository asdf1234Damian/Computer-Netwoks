#include <iostream>
#include <stdio.h>

void invertirCad(char *cad){
    char *end = cad;
    char c;
    while(*(end+1) != '\0') {
        end++;
    }
    while (end>cad){
        c = *cad;
        *cad = *end;
        *end = c;
        cad++;end--;
    }
}

int main(int argc, char const *argv[]){
    char *s = (char *)malloc(256);
    fgets(s,255 ,stdin);
    printf("cadena : %s\n",s);
    invertirCad(s);
    printf("cadena invertida : %s\n",s);
}
