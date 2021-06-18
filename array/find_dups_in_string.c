#include <stdio.h>
#include <stdlib.h>

int count_dups_in_string(char *str)
{
    int i = 0;
    int freq[52] = {0};
    int count = 0;

    for (i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z')
            freq[str[i] - 'A']++;
        else if (str[i] >= 'a' && str[i] <= 'z')
            freq[str[i] - 'a' + 26]++;
    }

    for (i = 0; i < 52; i++) {
        if (freq[i] > 1)
            count += freq[i] - 1; 
    }

    return count;
}

int is_anagram(char *str1, char *str2) {

    int freq[52] = {0};
    int i;

    for (i = 0; str1[i] != '\0'; i++) {
        if (str1[i] >= 'A' && str1[i] <= 'Z')
            freq[str1[i] - 'A']++;
        else if (str1[i] >= 'a' && str1[i] <= 'z')
            freq[str1[i] - 'a' + 26]++;
    }

    for (i = 0; str2[i] != '\0'; i++) {
        if (str2[i] >= 'A' && str2[i] <= 'Z')
            freq[str2[i] - 'A']--;
        else if (str2[i] >= 'a' && str2[i] <= 'z')
            freq[str2[i] - 'a' + 26]--;
    }

    for (i = 0; i < 52; i++)
        if (freq[i] < 0)
            return -1;

    return 0;
}

int main (int argc, char *argv[])
{

    char A[] = "verbose";
    char B[] = "observe";
    char C[] = "hooray";

    printf("dups = %d\r\n", count_dups_in_string(A));

    printf("is_anagram = %d\r\n", is_anagram(A, B));

    printf("is_anagram = %d\r\n", is_anagram(A, C));

    return 0;
}
