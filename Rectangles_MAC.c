#include <stdio.h>
#include <stdlib.h>
#include <wchar.h> 
#include <locale.h>

struct coordinates{
    int x1;
    int y1;
    int x2;
    int y2;
};

struct directions{
    int up; 
    int down;
    int left;
    int right;
};

int Reading(int *x1, int *y1, int *x2, int *y2, int n){
    printf("Enter the coordinates of the rectangle number %d (upper left corner, lower right corner): ", n);
    if(scanf("%d,%d,%d,%d", x1, y1, x2, y2) != 4 || getchar()!='\n' || !(*x1>=0 && *x1<=79) || !(*y1>=0 && *y1<=79) || !(*x2>=0 && *x2<=79) || !(*y2>=0 && *y2<=79) || (*x1 >= *x2) || (*y1 <= *y2)){
        return -1;
    }
    return 0;
}

void Create_symbol(struct directions *symbol, struct coordinates *rectangles, int t, int x, int y){
    for(int i = 0;i < t;i++){
        if(rectangles[i].x1 <= x && rectangles[i].x2 > x && (y == rectangles[i].y1 || y == rectangles[i].y2)){
            symbol->right = 1;
        }
        if(rectangles[i].x1 < x && rectangles[i].x2 >= x && (y == rectangles[i].y1 || y == rectangles[i].y2)){
            symbol->left = 1;
        }
        if(rectangles[i].y1 >= y && rectangles[i].y2 < y && (x == rectangles[i].x1 || x == rectangles[i].x2)){
            symbol->down = 1;
        }
        if(rectangles[i].y1 > y && rectangles[i].y2 <= y && (x == rectangles[i].x1 || x == rectangles[i].x2)){
            symbol->up = 1;
        }
    }
}

void Print_symbol(struct directions symbol){
    if(symbol.left == 1 && symbol.up == 1 && symbol.right == 1 && symbol.down == 1){
        wprintf(L"┼");
        return;
    }
    if(symbol.left == 1 && symbol.up == 1 && symbol.right == 1 && symbol.down == 0){
        wprintf(L"┴");
        return;
    }
    if(symbol.left == 1 && symbol.up == 1 && symbol.right == 0 && symbol.down == 1){
        wprintf(L"┤");
        return;
    }
    if(symbol.left == 1 && symbol.up == 0 && symbol.right == 1 && symbol.down == 1){
        wprintf(L"┬");
        return;
    }
    if(symbol.left == 0 && symbol.up == 1 && symbol.right == 1 && symbol.down == 1){
        wprintf(L"├");
        return;
    }
    if(symbol.left == 1 && symbol.up == 1 && symbol.right == 0 && symbol.down == 0){
        wprintf(L"┘");
        return;
    }
    if(symbol.left == 1 && symbol.up == 0 && symbol.right == 1 && symbol.down == 0){
        wprintf(L"─");
        return;
    }
    if(symbol.left == 1 && symbol.up == 0 && symbol.right == 0 && symbol.down == 1){
        wprintf(L"┐");
        return;
    }
    if(symbol.left == 0 && symbol.up == 1 && symbol.right == 1 && symbol.down == 0){
        wprintf(L"└");
        return;
    }
    if(symbol.left == 0 && symbol.up == 1 && symbol.right == 0 && symbol.down == 1){
        wprintf(L"│");
        return;
    }
    if(symbol.left == 0 && symbol.up == 0 && symbol.right == 1 && symbol.down == 1){
        wprintf(L"┌");
        return;
    }
    wprintf(L" ");
    
}

int main(){
    setlocale(LC_ALL, "ru_RU.utf-8");

    int t;
    printf("Enter the number of rectangles: ");
    if(scanf("%d", &t) != 1 || getchar() != '\n' || t<2){
        printf("Bad input!\n");
        return -1;
    }

    int max_x = 0, max_y = 0;
    struct coordinates rectangles[t];

    for(int i = 0;i < t;i++){
        if(Reading(&rectangles[i].x1, &rectangles[i].y1, &rectangles[i].x2, &rectangles[i].y2, i+1) == -1){
            printf("Bad input!\n");
            return -1;
        }
    }

    for(int i = 0;i < t;i++){
        if(rectangles[i].y1 > max_y)
            max_y = rectangles[i].y1;
        if(rectangles[i].x2 > max_x)
            max_x = rectangles[i].x2;
    }

    for(int i = max_y; i >= 0;i--){
        for(int j = 0; j <= max_x;j++){
            struct directions symbol = {.down = 0, .left = 0, .right = 0, .up = 0};
            Create_symbol(&symbol, rectangles, t, j, i);
            Print_symbol(symbol);
        }
        printf("\n");
    }

    return 0;
}

