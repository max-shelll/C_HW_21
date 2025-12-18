#include <stdio.h>
#include <string.h>
#include "album.h"

void input_album(Album* a) {
    printf("Название: ");
    fgets(a->title, 100, stdin);
    a->title[strcspn(a->title, "\n")] = '\0';

    printf("Год выпуска: ");
    scanf("%d", &a->year);
    getchar();

    printf("Стиль: ");
    fgets(a->style, 50, stdin);
    a->style[strcspn(a->style, "\n")] = '\0';

    printf("Количество треков: ");
    scanf("%d", &a->tracks);

    printf("Длительность (мин): ");
    scanf("%lf", &a->duration);
    getchar();
}

void print_album(const Album* a) {
    printf("\nНазвание: %s\n", a->title);
    printf("Год: %d\n", a->year);
    printf("Стиль: %s\n", a->style);
    printf("Треков: %d\n", a->tracks);
    printf("Длительность: %.2f мин\n", a->duration);
}

void print_all(Album arr[], int n) {
    if (n == 0) {
        printf("Массив пуст\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("\n=== Альбом %d ===", i + 1);
        print_album(&arr[i]);
    }
}

void edit_album(Album arr[], int n) {
    int index;
    printf("Номер записи (1-%d): ", n);
    scanf("%d", &index);
    getchar();

    if (index < 1 || index > n) {
        printf("Неверный номер\n");
        return;
    }

    input_album(&arr[index - 1]);
}

void search_album(Album arr[], int n) {
    char style[50];
    int found = 0;

    printf("Введите стиль: ");
    fgets(style, 50, stdin);
    style[strcspn(style, "\n")] = '\0';

    for (int i = 0; i < n; i++) {
        if (strcmp(arr[i].style, style) == 0) {
            print_album(&arr[i]);
            found = 1;
        }
    }

    if (!found)
        printf("Ничего не найдено\n");
}

void sort_albums(Album arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].year > arr[j + 1].year) {
                Album tmp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = tmp;
            }
        }
    }
}