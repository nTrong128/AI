#include <stdio.h>

#define tank_CapacityX 9
#define tank_CapacityY 4
#define empty 0
#define goal 6
#define maxLength 100

const char *action[] = {"First State", "pour Water Full X", "pour Water Full Y", "pour Water Empty X", "pour Water empty Y", "pour Water X to Y", "pour Water Y to X"};

typedef struct {
    int X, Y;
} State;

void makeNULLState(State* S) {
    S->X = 0;
    S->Y = 0;
}

void printState(State S) {
    printf("\n X: %d\t---\tY: %d\n", S.X, S.Y);
}

int goalCheck(State S) {
    return (S.X == goal || S.Y == goal);
}

int max(int a, int b) {
    return a > b ? a : b;
}
int min(int a, int b) {
    return a < b ? a : b;
}

int pourWaterFullX(State cur_S, State* result) {
    if(cur_S.X < tank_CapacityX) {
        result->X = tank_CapacityX;
        result->Y = cur_S.Y;
        return 1;
    }
    return 0;
}
int pourWaterFullY(State cur_S, State* result) {
    if(cur_S.Y < tank_CapacityY) {
        result->Y = tank_CapacityY;
        result->X = cur_S.X;
        return 1;
    }
    return 0;
}

int pourWaterEmptyX(State cur_S, State* result) {
    if(cur_S.X == empty)
        return 0;
    result->X = empty;
    result->Y = cur_S.Y;
    return 1;
}
int pourWaterEmptyY(State cur_S, State* result) {
    if(cur_S.Y == empty)
        return 0;
    result->Y = empty;
    result->X = cur_S.X;
    return 1;
}

int pourWaterXY(State cur_S, State *result)
{
    if (cur_S.X <= 0 || cur_S.Y >= tank_CapacityY)
        return 0;
    result->X = max(cur_S.X - (tank_CapacityY - cur_S.Y), empty);
    result->Y = min(cur_S.Y + cur_S.X, tank_CapacityY);
    return 1;
}
int pourWaterYX(State cur_S, State *result)
{
    if (cur_S.Y <= 0 || cur_S.X >= tank_CapacityX)
        return 0;
    result->Y = max(cur_S.Y - (tank_CapacityX - cur_S.X), empty);
    result->X = min(cur_S.Y + cur_S.X, tank_CapacityX);
    return 1;
}

int call_operator(State cur_S, State* result, int option) {
    switch (option) {
        case 1: return pourWaterFullX(cur_S, result);
        case 2: return pourWaterFullY(cur_S, result);
        case 3: return pourWaterEmptyX(cur_S, result);
        case 4: return pourWaterEmptyY(cur_S, result);
        case 5: return pourWaterXY(cur_S, result);
        case 6: return pourWaterYX(cur_S, result);
        default:
            printf("Error calls operators\n");
            return 0;
    }
}


int main() {
    State cur_S = {5, 4}, result;
    printf("Trang thai bat dau: ");
    printState(cur_S);
    int opt;
    for (opt = 1; opt <= 6;opt++) {
            int thuchien = call_operator(cur_S, &result, opt);
            if(thuchien == 1) {
                printf("\nHanh dong %s thanh cong", action[opt]);
                printState(result);
            } else {
                printf("\nHanh dong %s KHONG thanh cong", action[opt]);
            }

    }
    return 0;
}