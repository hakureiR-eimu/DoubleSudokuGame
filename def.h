#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define OK 1
#define ERROR 0
#define FOUND 1
#define NOTFOUND 0
#define NOANSWER 0
#define YES 1
#define NO 0
#define TRUE 1
#define FALSE -1;
typedef int status;

typedef struct LiteralNode
{
    int data = 0;
    struct LiteralNode* right = NULL;
} LiteralNode;

typedef struct ClauseNode
{
    int num = 0;
    struct LiteralNode* right = NULL;
    struct ClauseNode* down = NULL;
} ClauseNode;