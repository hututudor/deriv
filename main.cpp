#include "global.h"
#include "read.h"

node_t* ast_t;
int n ;

int main()
{
        ReadTree(ast_t, n);
        Deriva(ast_t);

        return 0;
}