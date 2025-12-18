#include <stdio.h>
#include <locale.h>
#include <string.h>

#define MAX 100

typedef struct {
    char title[100];
    int year;
    char style[50];
    int tracks;
    double duration;
} Album;

void menu();

void input_album(Album* a);
void print_album(const Album* a);
void print_all(Album arr[], int n);

void edit_album(Album arr[], int n);
void search_album(Album arr[], int n);
void sort_albums(Album arr[], int n);

int load_from_file(const char* filename, Album arr[], int* n);
int save_to_file(const char* filename, Album arr[], int n);

int main() {
    setlocale(LC_CTYPE, "RUS");

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
        printf("Выберите действие: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Имя файла для загрузки: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';

                if (load_from_file(filename, arr, &n) == 0)
                    printf("Данные загружены. Записей: %d\n", n);
                else
                    printf("Ошибка загрузки файла\n");
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
                printf("Сортировка выполнена\n");
                break;
            case 6:
                printf("Имя файла для сохранения: ");
                fgets(filename, sizeof(filename), stdin);
                filename[strcspn(filename, "\n")] = '\0';

                if (save_to_file(filename, arr, n) == 0)
                    printf("Данные сохранены\n");
                else
                    printf("Ошибка сохранения файла\n");
                break;
            case 0:
                printf("Выход из программы\n");
                break;
            default:
                printf("Неверный пункт меню\n");
        }

    } while (choice != 0);

    return 0;
}

void menu() {
    printf("1. Загрузить данные из файла\n");
    printf("2. Показать все записи\n");
    printf("3. Изменить запись\n");
    printf("4. Поиск записи по стилю\n");
    printf("5. Сортировка по году выпуска\n");
    printf("6. Сохранить данные в файл\n");
    printf("0. Выход\n");
}

void input_album(Album* a) {
    printf("Название: ");
    fgets(a->title, sizeof(a->title), stdin);
    a->title[strcspn(a->title, "\n")] = '\0';

    printf("Год выпуска: ");
    scanf("%d", &a->year);
    getchar();

    printf("Стиль: ");
    fgets(a->style, sizeof(a->style), stdin);
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
    if (n == 0) return;

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
    fgets(style, sizeof(style), stdin);
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

int load_from_file(const char* filename, Album arr[], int* n) {
    FILE* f = fopen(filename, "r");
    if (!f) return -1;

    for (int i = 0; i < *n; i++) {
        fgets(arr[i].title, 100, f);
        arr[i].title[strcspn(arr[i].title, "\n")] = '\0';

        fscanf(f, "%d\n", &arr[i].year);

        fgets(arr[i].style, 50, f);
        arr[i].style[strcspn(arr[i].style, "\n")] = '\0';

        fscanf(f, "%d\n", &arr[i].tracks);
        fscanf(f, "%lf\n", &arr[i].duration);
    }

    fclose(f);
    return 0;
}


int save_to_file(const char* filename, Album arr[], int n) {
    FILE* f = fopen(filename, "w");
    if (!f) return -1;

    for (int i = 0; i < n; i++) {
        fprintf(f, "\n%s\n", arr[i].title);
        fprintf(f, "%d\n", arr[i].year);
        fprintf(f, "%s\n", arr[i].style);
        fprintf(f, "%d\n", arr[i].tracks);
        fprintf(f, "%.2f\n", arr[i].duration);
    }

    fclose(f);
    return 0;
}

