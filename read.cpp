#include "read.h"

ifstream fin("input.txt");

void ReadTree(node_t* &ast_t, int &n)
{
    node_t* nodes[Nmax];
    fin >> n;

    for (int i = 1; i <= n; i++)
    {
        int tokenType;
        fin >> tokenType;

        nodes[i] = new node_t();
        nodes[i]->left = NULL;
        nodes[i]->right = NULL;
        nodes[i]->token.type = GetTokenType(tokenType);

        if (tokenType == 1)
        {
            int y;
            fin >> y;
            nodes[i]->token.val = y;
        }
    }

    for (int i = 1; i <= n; i++)
    {
        int tata;
        fin >> tata;

        if (tata == 0)
        {
            ast_t = nodes[i];
        }
        else
        {
            if (nodes[tata]->left == NULL)
            {
                nodes[tata]->left = nodes[i];
            }
            else
            {
                nodes[tata]->right = nodes[i];
            }
        }
    }
}