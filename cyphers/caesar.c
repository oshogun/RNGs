// Caesar's cypher
// An ancient and very simple encryption algorythm that was used in
// ancient Rome, adapted to a modern version that uses the entire
// ascii table instead of just the 26 letters

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

unsigned int measureString(char * string);
void encrypt (char * text, unsigned int size);
void decrypt (char * text, unsigned int size);

int main(int argc, char** argv)
{
    if (argc != 2) {
        printf("Usage: %s {text}, where {text} is the text to be ", argv[0]);
        printf("encrypted\n");
        return 1;
    }
    char * text = argv[1];
    int size = measureString(text);
    printf("Encrypting text %s\n", text);
    encrypt(text, size);
    printf("Encrypted text: %s\n", text);
    decrypt(text, size);
    printf("Decrypted text: %s\n", text);
}

unsigned int measureString(char * string) {
    unsigned int i = 0;
    while (string[i] != '\0') i++;
    return i;
} 

void encrypt (char * text, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++) {
        text[i] += 3;
    }
}

void decrypt (char * text, unsigned int size)
{
    for (unsigned int i = 0; i < size; i++) {
        text[i] -=3;
    }
}