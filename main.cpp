#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#define SIZE 100
using namespace std;

struct Point
{
    int x;
    int y;
};

//GENERATE 1 & 2 ()

int** Create_board(int n, int m)
{
    int** board = new int* [n];
    for (int i = 0; i < n; i++)
        board[i] = new int[m];

    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &board[i][j]);

    return board;
}

int Null_counts(int** board, int n, int m)
{
    int s = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            if (board[i][j] == 0) s++;

    return s;
}

int GetOponent(int n)
{
    if (n == 1) return 2;
    if (n == 2) return 1;
    return 0;
}

void Display_board(int** board, int n, int m)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%d ", board[i][j]);
        printf("\n");
    }
}

void Display_all_moves(int** board, int n, int m, int p, int moves)
{
    printf("%d \n", moves);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] == 0)
            {
                board[i][j] = p;                  //DISPLAY ALL MOVES
                Display_board(board, n, m);
                board[i][j] = 0;
            }
        }
    }
}

bool line(int** board, int n, int m, int k, int s, int l, int s1, int s2)
{
    if (l == k || n == s1 - 1)
    {
        if (s == k) return true;
        else return false;
    }
    l++;
    if (board[n][m] == board[n + 1][m])
        s++;
    bool score = line(board, n + 1, m, k, s, l, s1, s2);
    return score;
}



bool line2(int** board, int n, int m, int k, int s, int l, int s1, int s2)
{
    if (l == k || m == s2 - 1)
    {
        if (s == k) return true;
        else return false;
    }
    l++;
    if (board[n][m] == board[n][m + 1])
        s++;
    bool score = line2(board, n, m + 1, k, s, l, s1, s2);
    return score;
}

bool slant(int** board, int n, int m, int k, int s, int l, int s1, int s2)
{
    if (l == k || n == s1 - 1 || m == s2 - 1)
    {
        if (s == k) return true;
        else return false;
    }
    l++;
    if (board[n][m] == board[n + 1][m + 1])
        s++;
    bool score = slant(board, n + 1, m + 1, k, s, l, s1, s2);
    return score;
}

bool slant2(int** board, int n, int m, int k, int s, int l, int s1, int s2)
{
    if (l == k || n == 0 || m == s2 - 1)
    {
        if (s == k) return true;
        else return false;
    }
    l++;
    if (board[n][m] == board[n - 1][m + 1])
        s++;
    bool score = slant2(board, n - 1, m + 1, k, s, l, s1, s2);
    return score;
}



void Clearboard(int** board, int n)
{
    for (int i = 0; i < n; i++)
        delete[] board[i];
    delete[] board;
}

int GameOver(int** board,int n, int m, int k)
{
    bool row = false, col = false, sl = false, sl2 = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] != 0)
            {
                row = line2(board, i, j, k, 1, 1, n, m);
                col = line(board, i, j, k, 1, 1, n, m);
                sl = slant(board, i, j, k, 1, 1, n, m);
                sl2 = slant2(board, i, j, k, 1, 1, n, m);
            }
            if (row == true || col == true || sl == true || sl2 == true)
            {
                if (board[i][j] == 1) return 1;
                if (board[i][j] == 2) return -1;
            }
        }
    }
    return 0;
}


void Generate()
{
    int n, m, k, p;
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &k);
    scanf("%d", &p);
    int** board = Create_board(n, m);
    int sum = Null_counts(board, n, m);
    int score = GameOver(board, n, m, k);
    if (score != 0)
    {
        printf("%d \n", 0);
        Clearboard(board, n);
        return;
    }
    Display_all_moves(board, n, m, p, sum);
    Clearboard(board, n);
}



int Cut_if_end(int** board, int n, int m, int k,int p,int version)
{
    bool row = false, col = false, sl = false, sl2 = false;
    for (int x = 0; x < n; x++)
    {
        for (int y = 0; y < m; y++)
        {

            if (board[x][y] == 0)
            {
                board[x][y] = p;
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        if (board[i][j] == p)
                        {
                            row = line2(board, i, j, k, 1, 1, n, m);
                            col = line(board, i, j, k, 1, 1, n, m);
                            sl = slant(board, i, j, k, 1, 1, n, m);
                            sl2 = slant2(board, i, j, k, 1, 1, n, m);
                        }
                        if (row == true || col == true || sl == true || sl2 == true)
                        {
                            if (version==1) board[x][y] = 0;
                            if (p==1) return 1;
                            if (p==2) return -1;
                        }
                    }
                }
                board[x][y] = 0;
            }
        }
    }
    return 0;
}

void Generate2()
{
    int n, m, k, p;
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &k);
    scanf("%d", &p);
    int** board = Create_board(n, m);
    int sum = Null_counts(board, n, m);
    int score = GameOver(board, n, m, k);
    if (score != 0)
    {
        printf("%d \n", 0);
        Clearboard(board, n);
        return;
    }
    score=Cut_if_end(board, n, m, k, p,0);
    if (score != 0)
    {
        printf("%d \n", 1);
        Display_board(board, n, m);
        Clearboard(board, n);                 //CUT THEN
        return;
    }
    Display_all_moves(board, n, m, p, sum);
    Clearboard(board, n);
}


//SOLVE()


Point* Get_Moves_Array(int** board, int n, int m)
{
    int sum = Null_counts(board, n, m);
    Point* table = new Point[sum];

    int s = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            if (board[i][j] == 0)
            {
                table[s].x = i;
                table[s].y = j;
                s++;
            }
        }
    }
    return table;
}

int min(int a, int b)
{
    if (a <= b) return a;
    else return b;
}

int max(int a, int b)
{
    if (a >= b) return a;
    else return b;
}

int Minmax(int** board, int p, int n, int m, int k,int p_s)
{
    int best;
    Point* tab = Get_Moves_Array(board, n, m);
    int score = GameOver(board, n, m, k);
    if (score == 1)
    {
        delete[] tab;
        return 1;
    }
    if (score == -1)
    {
        delete[] tab;
        return -1;
    }
    score = Cut_if_end(board, n, m, k, p,1);
    if (score == 1)
    {
        delete[] tab;
        return 1;
    }
    if (score == -1)
    {
        delete[] tab;
        return -1;
    }
    int sum = Null_counts(board, n, m);
    if (sum == 0)
    {
        delete[] tab;
        return 0;
    }
    if (p == 1)
    {
        best = -10;
        for (int i = 0; i < sum; i++)
        {
            board[tab[i].x][tab[i].y] = p;
            best = max(best, Minmax(board, GetOponent(p), n, m, k,p_s));
            board[tab[i].x][tab[i].y] = 0;
            if (best == 1) break;
        }
        delete[] tab;
        return best;
    }
    else
    {
        best = 10;
        for (int i = 0; i < sum; i++)
        {
            board[tab[i].x][tab[i].y] = p;
            best = min(best, Minmax(board, GetOponent(p), n, m, k,p_s));
            board[tab[i].x][tab[i].y] = 0;
            if (best == -1) break;
        }  
        delete[] tab;
        return best;
    }
}

void Solve()
{
    int n, m, k, p;
    scanf("%d", &n);
    scanf("%d", &m);
    scanf("%d", &k);
    scanf("%d", &p);
    int** board = Create_board(n, m);
    int score = Minmax(board, p, n, m, k, p);
    if (score == 1) printf("FIRST_PLAYER_WINS\n");
    else if (score == -1) printf("SECOND_PLAYER_WINS\n");
    else if (score == 0) printf("BOTH_PLAYERS_TIE\n");
    Clearboard(board, n);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(NULL);
    char command[SIZE];
    while (true)
    {
        scanf("%s", command);
        if (feof(stdin) != 0)
        {
            break;
        }
        if (strcmp(command, "GEN_ALL_POS_MOV") == 0) Generate();
        if (strcmp(command, "GEN_ALL_POS_MOV_CUT_IF_GAME_OVER") == 0) Generate2();
        if (strcmp(command, "SOLVE_GAME_STATE") == 0) Solve();
    } 
}
