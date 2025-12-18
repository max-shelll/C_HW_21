#ifndef ALBUM_H
#define ALBUM_H

typedef struct {
    char title[100];
    int year;
    char style[50];
    int tracks;
    double duration;
} Album;

void input_album(Album* a);
void print_album(const Album* a);
void print_all(Album arr[], int n);

void edit_album(Album arr[], int n);
void search_album(Album arr[], int n);
void sort_albums(Album arr[], int n);

#endif