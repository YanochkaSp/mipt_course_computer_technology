// #include <stdio.h>

// int main() {
//     int n ;
//     char mas[n];
//     int k = 0;

//     //считывание массива
//     printf("Введите массив\n");
//     for (int i = 0; i < n; i++) {
//         scanf("%c", &mas[i]);
//         while (mas[i]) != "\0") {
//             k++;
//         }
//     }  

//     while (mas[i]) != "\0") {
//         k++;
//     }
//     printf("%d", k);

// }


// #include <stdio.h>
// int length(char* str);
// char* str = 0;

// int main() {
//     int n ;
//     char mas[n];
//     printf("Введите массив\n");
//     for (int i = 0; i < n; i++) {
//         scanf("%c", &mas[i]);
//     }
//     length(str);
// }

// int length(char* str) {
//         int len = 0;
//         while (*str != '\0') {
//             ++ str;
//             len ++;
//         }
//         return len;
//     }

#include <stdio.h>
int length(char* str);


int main() {
    char* str = "Hello";
    int n;
    length(str);
}

int length(char* str) {
        int counter = 0;
        while (str[counter] != '\0') {
            counter ++;
        }
        return counter;
    }