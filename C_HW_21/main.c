#include <stdio.h>
#include <locale.h>
#include <string.h>

#include "album.h"
#include "fileio.h"
#include "utils.h"

#define MAX 100

void menu() {
    printf("\n===== МЕНЮ =====\n");
    printf("1. Загрузить данные из файла\n");
    printf("2. Показать все записи\n");
    printf("3. Изменить запись\n");
    printf("4. Поиск по стилю\n");
    printf("5. Сортировка по году\n");
    printf("6. Сохранить в файл\n");
    printf("0. Выход\n");
}

int main() {
    setlocale(LC_ALL, "");

    Album arr[MAX] = {
        {"The Dark Side of the Moon", 1973, "Progressive Rock", 10, 42.59},
        {"Back in Black", 1980, "Hard Rock", 10, 41.59},
        {"Nevermind", 1991, "Grunge", 13, 49.23},
        {"Hybrid Theory", 2000, "Nu Metal", 12, 37.45},
        {"Random Access Memories", 2013, "Electronic", 13, 74.24}
    };

    int n = 5;
    int choice;
    char filename[100];

    do {
        menu();
        printf("Выбор: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
        case 1:
            printf("Имя файла: ");
            fgets(filename, 100, stdin);
            filename[strcspn(filename, "\n")] = '\0';
            load_from_file(filename, arr, &n);
            break;

        case 2:
            print_all(arr, n);
            break;

        case 3:
            edit_album(arr, n);
            break;

        case 4:
            search_album(arr, n);
            break;

        case 5:
            sort_albums(arr, n);
            break;

        case 6:
            printf("Имя файла: ");
            fgets(filename, 100, stdin);
            filename[strcspn(filename, "\n")] = '\0';
            save_to_file(filename, arr, n);
            break;
        }
    } while (choice != 0);

    return 0;
}