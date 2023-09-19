#include <stdio.h>
#include <malloc.h>

#define tank_CapacityX 10
#define tank_CapacityY 5
#define tank_CapacityZ 6

#define empty 0
#define goal 8
#define maxLength 100

const char *action[] = {
    "First State",
    "pour Water X to Y",
    "pour Water X to Z",
    "pour Water Y to X",
    "pour Water Y to Z",
    "pour Water Z to X",
    "pour Water Z to Y",
};

typedef struct State
{
    int X, Y, Z;
} State;

void makeNULLState(State *S)
{
    S->X = 0;
    S->Y = 0;
    S->Z = 0;
}

void printState(State S)
{
    printf("\n X: %d\t---\tY: %d\t---Z: %d\n", S.X, S.Y, S.Z);
}

int goalCheck(State S)
{
    return (S.X == goal || S.Y == goal || S.Y == goal);
}

int max(int a, int b)
{
    return a > b ? a : b;
}
int min(int a, int b)
{
    return a < b ? a : b;
}

int pourWaterXY(State cur_S, State *result)
{
    if (cur_S.X <= 0 || cur_S.Y >= tank_CapacityY)
        return 0;
    result->X = max(cur_S.X - (tank_CapacityY - cur_S.Y), empty);
    result->Y = min(cur_S.Y + cur_S.X, tank_CapacityY);
    result->Z = cur_S.Z;
    return 1;
}

int pourWaterXZ(State cur_S, State *result)
{
    if (cur_S.X <= 0 || cur_S.Z >= tank_CapacityZ)
        return 0;
    result->X = max(cur_S.X - (tank_CapacityZ - cur_S.Z), empty);
    result->Z = min(cur_S.Z + cur_S.X, tank_CapacityZ);
    result->Y = cur_S.Y;
    return 1;
}

int pourWaterYX(State cur_S, State *result)
{
    if (cur_S.Y <= 0 || cur_S.X >= tank_CapacityX)
        return 0;
    result->Y = max(cur_S.Y - (tank_CapacityX - cur_S.X), empty);
    result->X = min(cur_S.Y + cur_S.X, tank_CapacityX);
    result->Z = cur_S.Z;
    return 1;
}

int pourWaterYZ(State cur_S, State *result)
{
    if (cur_S.Y <= 0 || cur_S.Z >= tank_CapacityZ)
        return 0;
    result->Y = max(cur_S.Y - (tank_CapacityZ - cur_S.Z), empty);
    result->Z = min(cur_S.Y + cur_S.Z, tank_CapacityZ);
    result->X = cur_S.X;
    return 1;
}

int pourWaterZX(State cur_S, State *result)
{
    if (cur_S.Z <= 0 || cur_S.X >= tank_CapacityX)
        return 0;
    result->Z = max(cur_S.Z - (tank_CapacityX - cur_S.X), empty);
    result->X = min(cur_S.Z + cur_S.X, tank_CapacityX);
    result->Y = cur_S.Y;
    return 1;
}

int pourWaterZY(State cur_S, State *result)
{
    if (cur_S.Z <= 0 || cur_S.Y >= tank_CapacityY)
        return 0;
    result->Z = max(cur_S.Z - (tank_CapacityY - cur_S.Y), empty);
    result->Y = min(cur_S.Z + cur_S.Y, tank_CapacityY);
    result->X = cur_S.X;
    return 1;
}

int call_operator(State cur_S, State *result, int option)
{
    switch (option)
    {
    case 1:
        return pourWaterXY(cur_S, result);
    case 2:
        return pourWaterXZ(cur_S, result);
    case 3:
        return pourWaterYX(cur_S, result);
    case 4:
        return pourWaterYZ(cur_S, result);
    case 5:
        return pourWaterZX(cur_S, result);
    case 6:
        return pourWaterZY(cur_S, result);
    default:
        printf("Error calls operators\n");
        return 0;
    }
}
typedef struct Node
{
    State state;
    struct Node *parent;
    int no_Function;
} Node;

typedef struct Stack
{
    Node *Elements[maxLength];
    int top_Idx;
} Stack;

void makeNULLStack(Stack *stack)
{
    stack->top_Idx = maxLength;
}

int emptyStack(Stack stack)
{
    return stack.top_Idx == maxLength;
}

int fullStack(Stack stack)
{
    return stack.top_Idx == 0;
}

Node *top(Stack stack)
{
    if (!emptyStack(stack))
        return stack.Elements[stack.top_Idx];
    return NULL;
}

void pop(Stack *stack)
{
    if (!emptyStack(*stack))
        stack->top_Idx += 1;
    else
        printf("Error! Stack is empty");
}

void push(Node *X, Stack *stack)
{
    if (fullStack(*stack))
        printf("Error! Stack is full");
    else
    {
        stack->top_Idx -= 1;
        stack->Elements[stack->top_Idx] = X;
    }
}

typedef struct Queue
{
    Node *Element[maxLength];
    int front, rear;
} Queue;

void makeNULLQueue(Queue *q)
{
    q->front = -1;
    q->rear = -1;
}

int emptyQueue(Queue q)
{
    return q.front == -1;
}

int fullQueue(Queue q)
{
    return ((q.rear - q.front + 1) % maxLength) == 0;
}

Node *getFront(Queue q)
{
    if (emptyQueue(q))
        printf("Queue is empty");
    else
        return q.Element[q.front];
}

void delQueue(Queue *q)
{
    if (!emptyQueue(*q))
    {
        if (q->front == q->rear)
            makeNULLQueue(q);
        else
            q->front = (q->front + 1) % maxLength;
    }
    else
        printf("Eror, Delete");
}

void pushQueue(Node *x, Queue *q)
{
    if (!fullQueue(*q))
    {
        if (emptyQueue(*q))
            q->front = 0;
        q->rear = (q->rear + 1) % maxLength;
        q->Element[q->rear] = x;
    }
    else
        printf("Error, Push");
}

int compareStates(State S1, State S2)
{
    return (S1.X == S2.X && S1.Y == S2.Y);
}

int findState(State state, Queue openQueue)
{
    while (!emptyQueue(openQueue))
    {
        if (compareStates(getFront(openQueue)->state, state))
            return 1;
        delQueue(&openQueue);
    }
    return 0;
}

Node *BFS_Algorithm(State state)
{
    Queue OpenBFS, CloseBFS;
    makeNULLQueue(&OpenBFS);
    makeNULLQueue(&CloseBFS);

    Node *root = (Node *)malloc(sizeof(Node));
    root->state = state;
    root->parent = NULL;
    root->no_Function = 0;
    pushQueue(root, &OpenBFS);

    while (!emptyQueue(OpenBFS))
    {
        Node *node = getFront(OpenBFS);
        delQueue(&OpenBFS);
        pushQueue(node, &CloseBFS);

        if (goalCheck(node->state))
            return node;
        int opt;
        for (opt = 1; opt <= 6; opt++)
        {
            State newState;
            makeNULLState(&newState);
            if (call_operator(node->state, &newState, opt))
            {
                if (findState(newState, CloseBFS) || findState(newState, OpenBFS))
                    continue;
                Node *newNode = (Node *)malloc(sizeof(Node));
                newNode->state = newState;
                newNode->parent = node;
                newNode->no_Function = opt;
                pushQueue(newNode, &OpenBFS);
            }
        }
    }
    return NULL;
}

void printWaysToGetGoal(Node *node)
{
    Stack stackPrint;
    makeNULLStack(&stackPrint);
    while (node->parent != NULL)
    {
        push(node, &stackPrint);
        node = node->parent;
    }
    push(node, &stackPrint);

    int noAction = 0;
    while (!emptyStack(stackPrint))
    {
        printf("\nAction: %d: %s", noAction, action[top(stackPrint)->no_Function]);
        printState(top(stackPrint)->state);
        pop(&stackPrint);
        noAction++;
    }
}

int main()
{
    State cur_S = {10, 0, 0};
    Node *p = BFS_Algorithm(cur_S);
    printWaysToGetGoal(p);

    return 0;
}