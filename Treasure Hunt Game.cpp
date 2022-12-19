#include<iostream>
#include<fstream>
#include<string>
#include<conio.h>
using namespace std;

template<class T>
class Stack
{
private:

    class Node
    {
    public:
        T data[2];
        Node* next;
        Node()
        {
            next = nullptr;
            data[0] = 0;
            data[1] = 0;
        }
    };
    Node* peek;

public:

    Stack()
    {
        peek = nullptr;
    }

    void Push(T x, T y)
    {
        Node* temp = new Node();
        temp->data[0] = x;
        temp->data[1] = y;
        temp->next = peek;
        peek = temp;
    }

    void Print_Stack()
    {
        Node* temp = peek;
        if (peek != nullptr)
        {
            while (temp != nullptr)
            {
                cout << "(" << temp->data[0] << ", " << temp->data[1] << ")";
                temp = temp->next;
                if (temp != nullptr)
                {
                    cout << ", ";
                }
            }
        }
    }
};

void LoadTitle();
void LoadMenu();
void LoadMap(char Map_1[][8], int rows_1, char Map_2[][11], int rows_2, char Map_3[][26], int rows_3, Stack<int>& T);
bool StartGame(char Map_1[][8], int rows_1, char Map_2[][11], int rows_2, char Map_3[][26], int rows_3, Stack<int>& M1, Stack<int>& M2, Stack<int>& M3);
bool Devil_Room(char Map_2[][11], int rows_2, char Map_3[][26], int rows_3, Stack<int>& M2, Stack<int>& M3);
bool Treasure_Room(char Map_3[][26], int rows_3, Stack<int>& M3);
void Show_Result(bool Result);
void Show_Paths(Stack<int>& M1, Stack<int>& M2, Stack<int>& M3, Stack<int>& T);
void LoadRules();
void Options();

int main()
{
    LoadTitle();
    char Map_1[11][8];
    char Map_2[10][11];
    char Map_3[20][26];
    int option = 0;
    Stack<int> M1, M2, M3, T;
    while (option != 4)
    {
        LoadMap(Map_1, 11, Map_2, 10, Map_3, 20, T);
        LoadMenu();
        cin >> option;
        system("cls");
        switch (option)
        {

        default:
        {
            cout << "Select right option\n"; break;
        }

        case 1:
        {
            Show_Result(StartGame(Map_1, 11, Map_2, 10, Map_3, 20, M1, M2, M3));
            Show_Paths(M1, M2, M3, T);
            break;
        }

        case 2:
        {
            LoadRules();
            break;
        }

        case 3:
        {
            Options();
            break;
        }

        case 4:
        {
            system("cls");
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\tQuiting......\n\n\n\n\n\n\n\n\n\n\n\n";
            return 0;
        }
        }
    }
}

void LoadTitle()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\t\t$$$$$$$$\\ " << '\n';
    cout << "\t\t\\__$$  __| " << '\n';
    cout << "\t\t   $$ | $$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$$\\ $$\\   $$\\  $$$$$$\\   $$$$$$\\        $$ |  $$ |$$\\   $$\\ $$$$$$$\\ $$$$$$\\    $$$$$$\\   $$$$$$\\  " << '\n';
    cout << "\t\t   $$ |$$  __$$\\ $$  __$$\\  \\____$$\\ $$  _____|$$ |  $$ |$$  __$$\\ $$  __$$\\       $$$$$$$$ |$$ |  $$ |$$  __$$\\\\_$$  _|  $$  __$$\\ $$  __$$\\ " << '\n';
    cout << "\t\t   $$ |$$ |  \\__|$$$$$$$$ | $$$$$$$ |\\$$$$$$\\  $$ |  $$ |$$ |  \\__|$$$$$$$$ |      $$  __$$ |$$ |  $$ |$$ |  $$ | $$ |    $$$$$$$$ |$$ |  \\__|" << '\n';
    cout << "\t\t   $$ |$$ |      $$   ____|$$  __$$ | \\____$$\\ $$ |  $$ |$$ |      $$   ____|      $$ |  $$ |$$ |  $$ |$$ |  $$ | $$ |$$\\ $$   ____|$$ |      " << '\n';
    cout << "\t\t   $$ |$$ |      \\$$$$$$$\\ \\$$$$$$$ |$$$$$$$  |\\$$$$$$  |$$ |      \\$$$$$$$\\       $$ |  $$ |\\$$$$$$  |$$ |  $$ | \\$$$$  |\\$$$$$$$\\ $$ |      " << '\n';
    cout << "\t\t   \\__|\\__|       \\_______| \\_______|\\_______/  \\______/ \\__|       \\_______|      \\__|  \\__| \\______/ \\__|  \\__|  \\____/  \\_____/ \\__/" << '\n';
    cout << "\n\t\t\t\t\t\t\t\t\t\t\t\t\tI n      A      H a u n t e d      H o u s e";
    cout << "\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\tPress any key to start the game\n";
    while (!_kbhit())
    {
        system("Color 6");
    }
    system("cls");
}

void LoadMenu()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t[M  E  N  U]\n\t\t\t\t\t\t\t\t1. Start Game \n\t\t\t\t\t\t\t\t2. Rules\n\t\t\t\t\t\t\t\t3. Options\n\t\t\t\t\t\t\t\t4. Quit\n\t\t\t\t\t\t\t\t";
}

void LoadMap(char Map_1[][8], int rows_1, char Map_2[][11], int rows_2, char Map_3[][26], int rows_3, Stack<int>& T)
{
    string CopyPaste1;
    //---------------------------------
    // MAP - 1
    //---------------------------------
    ifstream Map1;
    Map1.open("Map1.txt");
    if (Map1)
    {
        for (int i = 0; !Map1.eof(); i++)
        {
            getline(Map1, CopyPaste1);
            for (int j = 0; j < 8; j++)
            {
                if (CopyPaste1[j] == '|')
                {
                    Map_1[i][j] = (char)219;
                }
                else
                {
                    if (CopyPaste1[j] == 'X')
                    {
                        Map_1[i][j] = (char)219;
                    }
                    else if (CopyPaste1[j] == '0')
                    {
                        Map_1[i][j] = ' ';
                    }
                    else
                    {
                        Map_1[i][j] = CopyPaste1[j];
                    }
                }
            }
        }
        Map1.close();
    }
    else
    {
        cout << "Unable to load map1 :(\n";
    }
    //---------------------------------
    // MAP - 2
    //---------------------------------
    string CopyPaste2;
    ifstream Map2;
    Map2.open("Map2.txt");
    if (Map2)
    {
        for (int i = 0; !Map2.eof(); i++)
        {
            getline(Map2, CopyPaste2);
            for (int j = 0; j < 11; j++)
            {
                if (CopyPaste2[j] == '|')
                {
                    Map_2[i][j] = (char)219;
                }
                else
                {
                    if (CopyPaste2[j] == 'X')
                    {
                        Map_2[i][j] = (char)219;
                    }
                    else if (CopyPaste2[j] == '0')
                    {
                        Map_2[i][j] = ' ';
                    }
                    else
                    {
                        Map_2[i][j] = CopyPaste2[j];
                    }
                }
            }
        }
        Map2.close();
    }
    else
    {
        cout << "Unable to load map2 :(\n";
    }
    //---------------------------------
    // MAP - 3
    //---------------------------------
    string CopyPaste3;
    ifstream Map3;
    int Tx = 0, Ty = 0;
    Map3.open("Map3.txt");
    if (Map3)
    {
        for (int i = 0; !Map3.eof(); i++)
        {
            getline(Map3, CopyPaste3);
            for (int j = 0; j < 26; j++)
            {
                if (CopyPaste3[j] == '|' || CopyPaste3[j] == '+' || CopyPaste3[j] == '-')
                {
                    Map_3[i][j] = (char)219;
                }
                else
                {
                    Map_3[i][j] = CopyPaste3[j];
                }
                if (CopyPaste3[j] == 'T')
                {
                    Tx = i, Ty = j;
                    T.Push(Tx, Ty);
                }
            }
        }
        Map3.close();
    }
    else
    {
        cout << "Unable to load map2 :(\n";
    }
}

bool StartGame(char Map_1[][8], int rows_1, char Map_2[][11], int rows_2, char Map_3[][26], int rows_3, Stack<int>& M1, Stack<int>& M2, Stack<int>& M3)
{
    char axis;
    int Px, Py; Px = 7; Py = 6;
    int Gx, Gy; Gx = 9; Gy = 4;
    int Dx, Dy; Dx = 2; Dy = 3;
    bool Devil = false;
    M1.Push(Px, Py);
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    for (int i = 0; i < rows_1; i++)
    {
        cout << "\t\t\t\t\t\t\t\t";
        for (int j = 0; j < 8; j++)
        {
            cout << Map_1[i][j];
        }
        cout << endl;
    }
    while ((Px != Dx) || (Py != Dy))
    {
        if (_kbhit())
        {
            axis = _getch();
            if (axis == 'a')
            {
                if (Map_1[Px][Py - 1] != 'G')
                {
                    if (Map_1[Px][Py - 1] != 'X' && Map_1[Px][Py - 1] != (char)219)
                    {
                        Map_1[Px][Py - 1] = Map_1[Px][Py];
                        Map_1[Px][Py] = ' ';
                        Py -= 1;
                    }
                    M1.Push(Px, Py);
                }
                else
                {
                    if (Devil_Room(Map_2, rows_2, Map_3, rows_3, M2, M3))
                    {
                        Devil = true;
                    }
                    else
                    {
                        Devil = false;
                    }
                    break;
                }
            }
            else if (axis == 'd')
            {
                if (Map_1[Px][Py + 1] != 'G')
                {
                    if (Map_1[Px][Py + 1] != 'X' && Map_1[Px][Py + 1] != (char)219)
                    {
                        Map_1[Px][Py + 1] = Map_1[Px][Py];
                        Map_1[Px][Py] = ' ';
                        Py += 1;
                    }
                    M1.Push(Px, Py);
                }
                else
                {
                    if (Devil_Room(Map_2, rows_2, Map_3, rows_3, M2, M3))
                    {
                        Devil = true;
                    }
                    else
                    {
                        Devil = false;
                    }
                    break;
                }
            }
            else if (axis == 'w')
            {
                if (Map_1[Px - 1][Py] != 'G')
                {
                    if (Map_1[Px - 1][Py] != 'X' && Map_1[Px - 1][Py] != (char)219)
                    {
                        Map_1[Px - 1][Py] = Map_1[Px][Py];
                        Map_1[Px][Py] = ' ';
                        Px -= 1;
                    }
                    M1.Push(Px, Py);
                }
                else
                {
                    if (Devil_Room(Map_2, rows_2, Map_3, rows_3, M2, M3))
                    {
                        Devil = true;
                    }
                    else
                    {
                        Devil = false;
                    }
                    break;
                }
            }
            else if (axis == 's')
            {
                if (Map_1[Px + 1][Py] != 'G')
                {
                    if (Map_1[Px + 1][Py] != 'X' && Map_1[Px + 1][Py] != (char)219)
                    {
                        Map_1[Px + 1][Py] = Map_1[Px][Py];
                        Map_1[Px][Py] = ' ';
                        Px += 1;
                    }
                    M1.Push(Px, Py);
                }
                else
                {
                    if (Devil_Room(Map_2, rows_2, Map_3, rows_3, M2, M3))
                    {
                        Devil = true;
                    }
                    else
                    {
                        Devil = false;
                    }
                    break;
                }
            }
            system("cls");
            cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
            for (int i = 0; i < rows_1; i++)
            {
                cout << "\t\t\t\t\t\t\t\t";
                for (int j = 0; j < 8; j++)
                {
                    cout << Map_1[i][j];
                }
                cout << endl;
            }
        }
    }
    system("cls");
    return Devil;
}

bool Devil_Room(char Map_2[][11], int rows_2, char Map_3[][26], int rows_3, Stack<int>& M2, Stack<int>& M3)
{
    char axis;
    int Px, Py; Px = 1; Py = 1;
    int D1x, D1y; D1x = 4; D1y = 3;
    int D2x, D2y; D2x = 8; D2y = 5;
    int D3x, D3y; D3x = 1; D3y = 7;
    int Gx, Gy; Gx = 5; Gy = 9;
    bool D1_left = true, D1_right = false;
    bool D2_left = true, D2_right = false;
    bool D3_left = true, D3_right = false;
    bool G_left = true, G_right = false;
    bool Treasure = false;
    M2.Push(Px, Py);
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    for (int i = 0; i < rows_2; i++)
    {
        cout << "\t\t\t\t\t\t\t\t";
        for (int j = 0; j < 11; j++)
        {
            cout << Map_2[i][j];
        }
        cout << endl;
    }
    Map_2[Px][Py] = 'P';
    while (((Px != D1x) || (Py != D1y)) && ((Px != D2x) || (Py != D2y)) && ((Px != D3x) || (Py != D3y)))
    {
        if (_kbhit())
        {
            axis = _getch();
            if (axis == 'a')
            {
                if (Map_2[Px][Py - 1] != 'G')
                {
                    if (Map_2[Px][Py - 1] != 'X' && Map_2[Px][Py - 1] != (char)219)
                    {
                        Map_2[Px][Py - 1] = Map_2[Px][Py];
                        Map_2[Px][Py] = ' ';
                        Py -= 1;
                        M2.Push(Px, Py);
                    }
                }
                else
                {
                    if (Treasure_Room(Map_3, rows_3, M3))
                    {
                        Treasure = true;
                    }
                    else
                    {
                        Treasure = false;
                    }
                    break;
                }
            }
            else if (axis == 'd')
            {
                if (Map_2[Px][Py + 1] != 'G')
                {
                    if (Map_2[Px][Py + 1] != 'X' && Map_2[Px][Py + 1] != (char)219)
                    {
                        Map_2[Px][Py + 1] = Map_2[Px][Py];
                        Map_2[Px][Py] = ' ';
                        Py += 1;
                        M2.Push(Px, Py);
                    }
                }
                else
                {
                    if (Treasure_Room(Map_3, rows_3, M3))
                    {
                        Treasure = true;
                    }
                    else
                    {
                        Treasure = false;
                    }
                    break;
                }
            }
            else if (axis == 'w')
            {
                if (Map_2[Px - 1][Py] != 'G')
                {
                    if (Map_2[Px - 1][Py] != 'X' && Map_2[Px - 1][Py] != (char)219)
                    {
                        Map_2[Px - 1][Py] = Map_2[Px][Py];
                        Map_2[Px][Py] = ' ';
                        Px -= 1;
                        M2.Push(Px, Py);
                    }
                }
                else
                {
                    if (Treasure_Room(Map_3, rows_3, M3))
                    {
                        Treasure = true;
                    }
                    else
                    {
                        Treasure = false;
                    }
                    break;
                }
            }
            else if (axis == 's')
            {
                if (Map_2[Px + 1][Py] != 'G')
                {
                    if (Map_2[Px + 1][Py] != 'X' && Map_2[Px + 1][Py] != (char)219)
                    {
                        Map_2[Px + 1][Py] = Map_2[Px][Py];
                        Map_2[Px][Py] = ' ';
                        Px += 1;
                        M2.Push(Px, Py);
                    }
                }
                else
                {
                    if (Treasure_Room(Map_3, rows_3, M3))
                    {
                        Treasure = true;
                    }
                    else
                    {
                        Treasure = false;
                    }
                    break;
                }
            }

        }
        // Devil 1 Movement Started
        if ((Map_2[D1x - 1][D1y] != 'P'))
        {
            if ((Map_2[D1x - 1][D1y] != (char)19 && Map_2[D1x - 1][D1y] == ' ') && D1_left == false)
            {
                Map_2[D1x - 1][D1y] = Map_2[D1x][D1y];
                Map_2[D1x][D1y] = ' ';
                D1x -= 1;
            }
            else
            {
                D1_left = true;
                D1_right = false;
            }
        }
        else
        {
            return false;
        }
        if ((Map_2[D1x + 1][D1y] != 'P'))
        {
            if ((Map_2[D1x + 1][D1y] != (char)19 && Map_2[D1x + 1][D1y] == ' ') && D1_right == false)
            {
                Map_2[D1x + 1][D1y] = Map_2[D1x][D1y];
                Map_2[D1x][D1y] = ' ';
                D1x += 1;
            }
            else
            {
                D1_right = true;
                D1_left = false;
            }
        }
        else
        {
            return false;
        }
        // Devil 1 Movement Ended
        // ------------------------
        // Devil 2 Movement Started
        if ((Map_2[D2x - 1][D2y] != 'P'))
        {
            if ((Map_2[D2x - 1][D2y] != (char)19 && Map_2[D2x - 1][D2y] == ' ') && D2_left == false)
            {
                Map_2[D2x - 1][D2y] = Map_2[D2x][D2y];
                Map_2[D2x][D2y] = ' ';
                D2x -= 1;
            }
            else
            {
                D2_left = true;
                D2_right = false;
            }
        }
        else
        {
            return false;
        }
        if ((Map_2[D2x + 1][D2y] != 'P'))
        {
            if ((Map_2[D2x + 1][D2y] != (char)19 && Map_2[D2x + 1][D2y] == ' ') && D2_right == false)
            {
                Map_2[D2x + 1][D2y] = Map_2[D2x][D2y];
                Map_2[D2x][D2y] = ' ';
                D2x += 1;
            }
            else
            {
                D2_right = true;
                D2_left = false;
            }
        }
        else
        {
            return false;
        }
        // Devil 2 Movement Ended
        // ------------------------
        // Devil 3 Movement Started
        if ((Map_2[D3x - 1][D3y] != 'P'))
        {
            if ((Map_2[D3x - 1][D3y] != (char)19 && Map_2[D3x - 1][D3y] == ' ') && D3_left == false)
            {
                Map_2[D3x - 1][D3y] = Map_2[D3x][D3y];
                Map_2[D3x][D3y] = ' ';
                D3x -= 1;
            }
            else
            {
                D3_left = true;
                D3_right = false;
            }
        }
        else
        {
            return false;
        }
        if ((Map_2[D3x + 1][D3y] != 'P'))
        {
            if ((Map_2[D3x + 1][D3y] != (char)19 && Map_2[D3x + 1][D3y] == ' ') && D3_right == false)
            {
                Map_2[D3x + 1][D3y] = Map_2[D3x][D3y];
                Map_2[D3x][D3y] = ' ';
                D3x += 1;
            }
            else
            {
                D3_right = true;
                D3_left = false;
            }
        }
        else
        {
            return false;
        }
        // Devil 3 Movement Ended
        // ------------------------
        // Gasper Movement Started
        if ((Map_2[Gx - 1][Gy] != 'P'))
        {
            if ((Map_2[Gx - 1][Gy] != (char)19 && Map_2[Gx - 1][Gy] == ' ') && G_left == false)
            {
                Map_2[Gx - 1][Gy] = Map_2[Gx][Gy];
                Map_2[Gx][Gy] = ' ';
                Gx -= 1;
            }
            else
            {
                G_left = true;
                G_right = false;
            }
        }
        else
        {
            if (Treasure_Room(Map_3, rows_3, M3))
            {
                Treasure = true;
            }
            else
            {
                Treasure = false;
            }
            break;
        }
        if ((Map_2[Gx + 1][Gy] != 'P'))
        {
            if ((Map_2[Gx + 1][Gy] != (char)19 && Map_2[Gx + 1][Gy] == ' ') && G_right == false)
            {
                Map_2[Gx + 1][Gy] = Map_2[Gx][Gy];
                Map_2[Gx][Gy] = ' ';
                Gx += 1;
            }
            else
            {
                G_right = true;
                G_left = false;
            }
        }
        else
        {
            if (Treasure_Room(Map_3, rows_3, M3))
            {
                Treasure = true;
            }
            else
            {
                Treasure = false;
            }
            break;
        }
        // Gasper Movement Ended
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
        for (int i = 0; i < rows_2; i++)
        {
            cout << "\t\t\t\t\t\t\t\t";
            for (int j = 0; j < 11; j++)
            {
                cout << Map_2[i][j];
            }
            cout << endl;
        }
    }
    system("cls");
    return Treasure;
}

bool Treasure_Room(char Map_3[][26], int rows_3, Stack<int>& M3)
{
    char axis;
    int Px, Py; Px = Py = 1;
    int Tx, Ty; Tx = 18; Ty = 4;
    int Dx, Dy; Dx = 9; Dy = 12;
    int D1x, D1y; D1x = 7; D1y = 14;
    int D2x, D2y; D2x = 11; D2y = 13;
    int D3x, D3y; D3x = 16; D3y = 5;
    bool D_left = true, D_right = false;
    bool D1_left = false, D1_right = true;
    bool D2_left = true, D2_right = false;
    bool D3_left = false, D3_right = true;
    M3.Push(Px, Py);
    while (((Px != Dx) || (Py != Dy)) && ((Px != Tx) || (Py != Ty)) && ((Px != D1x) || (Py != D1y)) && ((Px != D2x) || (Py != D2y)) && ((Px != D3x) || (Py != D3y)))
    {
        system("cls");
        cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
        for (int i = 0; i < rows_3; i++)
        {
            cout << "\t\t\t\t\t\t\t\t";
            for (int j = 0; j < 26; j++)
            {
                cout << Map_3[i][j];
            }
            cout << endl;
        }
        if (_kbhit())
        {
            axis = _getch();
            // Player Movement Started
            if (axis == 'a')
            {
                if (Map_3[Px][Py - 1] != (char)19 && Map_3[Px][Py - 1] == ' ')
                {
                    Map_3[Px][Py - 1] = Map_3[Px][Py];
                    Map_3[Px][Py] = ' ';
                    Py -= 1;
                    M3.Push(Px, Py);
                }
            }
            else if (axis == 'd')
            {
                if (Map_3[Px][Py + 1] != (char)19 && Map_3[Px][Py + 1] == ' ')
                {
                    Map_3[Px][Py + 1] = Map_3[Px][Py];
                    Map_3[Px][Py] = ' ';
                    Py += 1;
                    M3.Push(Px, Py);
                }
            }
            else if (axis == 'w')
            {
                if (Map_3[Px - 1][Py] != (char)19 && Map_3[Px - 1][Py] == ' ')
                {
                    Map_3[Px - 1][Py] = Map_3[Px][Py];
                    Map_3[Px][Py] = ' ';
                    Px -= 1;
                    M3.Push(Px, Py);
                }
            }
            else if (axis == 's')
            {
                if (Map_3[Px + 1][Py] != (char)19 && Map_3[Px + 1][Py] == ' ')
                {
                    Map_3[Px + 1][Py] = Map_3[Px][Py];
                    Map_3[Px][Py] = ' ';
                    Px += 1;
                    M3.Push(Px, Py);
                }
            }
            // Player Movement Ended
        }
        // Devil Movement Started
        if ((Map_3[Dx][Dy - 1] != (char)19 && Map_3[Dx][Dy - 1] == ' ') && D_left == false)
        {
            Map_3[Dx][Dy - 1] = Map_3[Dx][Dy];
            Map_3[Dx][Dy] = ' ';
            Dy -= 1;
        }
        else
        {
            D_left = true;
            D_right = false;
        }
        if ((Map_3[Dx][Dy + 1] != (char)19 && Map_3[Dx][Dy + 1] == ' ') && D_right == false)
        {
            Map_3[Dx][Dy + 1] = Map_3[Dx][Dy];
            Map_3[Dx][Dy] = ' ';
            Dy += 1;
        }
        else
        {
            D_right = true;
            D_left = false;
        }
        // Devil Movement Ended
        // ------------------------
        // Devil 1 Movement Started
        if ((Map_3[D1x][D1y - 1] != 'P'))
        {
            if ((Map_3[D1x][D1y - 1] != (char)19 && Map_3[D1x][D1y - 1] == ' ') && D1_left == false)
            {
                Map_3[D1x][D1y - 1] = Map_3[D1x][D1y];
                Map_3[D1x][D1y] = ' ';
                D1y -= 1;
            }
            else
            {
                D1_left = true;
                D1_right = false;
            }
        }
        else
        {
            return false;
        }
        if ((Map_3[D1x][D1y + 1] != 'P'))
        {
            if ((Map_3[D1x][D1y + 1] != (char)19 && Map_3[D1x][D1y + 1] == ' ') && D1_right == false)
            {
                Map_3[D1x][D1y + 1] = Map_3[D1x][D1y];
                Map_3[D1x][D1y] = ' ';
                D1y += 1;
            }
            else
            {
                D1_right = true;
                D1_left = false;
            }
        }
        else
        {
            return false;
        }
        // Devil 1 Movement Ended
        // ------------------------
        // Devil 2 Movement Started
        if ((Map_3[D2x][D2y - 1] != 'P'))
        {
            if ((Map_3[D2x][D2y - 1] != (char)19 && Map_3[D2x][D2y - 1] == ' ') && D2_left == false)
            {
                Map_3[D2x][D2y - 1] = Map_3[D2x][D2y];
                Map_3[D2x][D2y] = ' ';
                D2y -= 1;
            }
            else
            {
                D2_left = true;
                D2_right = false;
            }
        }
        else
        {
            return false;
        }
        if ((Map_3[D2x][D2y + 1] != 'P'))
        {
            if ((Map_3[D2x][D2y + 1] != (char)19 && Map_3[D2x][D2y + 1] == ' ') && D2_right == false)
            {
                Map_3[D2x][D2y + 1] = Map_3[D2x][D2y];
                Map_3[D2x][D2y] = ' ';
                D2y += 1;
            }
            else
            {
                D2_right = true;
                D2_left = false;
            }
        }
        else
        {
            return false;
        }
        // Devil 2 Movement Ended
        // ------------------------
        // Devil 3 Movement Started
        if ((Map_3[D3x][D3y - 1] != 'P'))
        {
            if ((Map_3[D3x][D3y - 1] != (char)19 && Map_3[D3x][D3y - 1] == ' ') && D3_left == false)
            {
                Map_3[D3x][D3y - 1] = Map_3[D3x][D3y];
                Map_3[D3x][D3y] = ' ';
                D3y -= 1;
            }
            else
            {
                D3_left = true;
                D3_right = false;
            }
        }
        else
        {
            return false;
        }
        if ((Map_3[D3x][D3y + 1] != 'P'))
        {
            if ((Map_3[D3x][D3y + 1] != (char)19 && Map_3[D3x][D3y + 1] == ' ') && D3_right == false)
            {
                Map_3[D3x][D3y + 1] = Map_3[D3x][D3y];
                Map_3[D3x][D3y] = ' ';
                D3y += 1;
            }
            else
            {
                D3_right = true;
                D3_left = false;
            }
        }
        else
        {
            return false;
        }
        // Devil 3 Movement Ended
        if ((Map_3[Tx][Ty + 1] == 'P'))
        {
            return true;
        }
    }
    if (((Px == Dx) || (Py == Dy)) || ((Px == D1x) || (Py == D1y)) || ((Px == D2x) || (Py == D2y)) || ((Px == D3x) || (Py == D3y)))
    {
        return false;
    }
    else if ((Px == Tx) || (Py == Ty))
    {
        return true;
    }
    //return true;
}

void Show_Result(bool Result)
{
    system("cls");
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    if (Result)
    {
        cout << "\t\t\t\t\t\\     / +-------+  |       |      |      |  +-------+  |\\     |\n";
        cout << "\t\t\t\t\t \\   /  |       |  |       |      |      |  |       |  | \\    |\n";
        cout << "\t\t\t\t\t  \\ /   |       |  |       |      |      |  |       |  |  \\   |\n";
        cout << "\t\t\t\t\t   |    |       |  |       |      |  /\\  |  |       |  |   \\  |\n";
        cout << "\t\t\t\t\t   |    |       |  |       |      | /  \\ |  |       |  |    \\ |\n";
        cout << "\t\t\t\t\t   |    +-------+  +-------+      |/    \\|  +-------+  |     \\|\n";
    }
    else
    {
        cout << "\t\t\t\t\t\\     / +-------+  |       |      |        +-------+  +-------+  +-------+\n";
        cout << "\t\t\t\t\t \\   /  |       |  |       |      |        |       |  |          |        \n";
        cout << "\t\t\t\t\t  \\ /   |       |  |       |      |        |       |  |          |        \n";
        cout << "\t\t\t\t\t   |    |       |  |       |      |        |       |  +-------+  +-------+\n";
        cout << "\t\t\t\t\t   |    |       |  |       |      |        |       |          |  |        \n";
        cout << "\t\t\t\t\t   |    |       |  |       |      |        |       |          |  |        \n";
        cout << "\t\t\t\t\t   |    +-------+  +-------+      +------  +-------+  +-------+  +-------+\n";
    }
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    system("pause"); system("cls");
}

void Show_Paths(Stack<int>& M1, Stack<int>& M2, Stack<int>& M3, Stack<int>& T)
{
    system("cls");
    cout << "Treasure Location is in Coordinates ";
    T.Print_Stack();
    cout << " of map 3\n";
    cout << "Paths :-\n";
    cout << "-> Coordinates of path in map 1 : ";
    M1.Print_Stack(); cout << endl;
    cout << "-> Coordinates of path in map 2 : ";
    M2.Print_Stack(); cout << endl;
    cout << "-> Coordinates of path in map 3 : ";
    M3.Print_Stack(); cout << endl;
    system("pause"); system("cls");
}

void LoadRules()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t[G  A  M  E    R  U  L  E  S]\n";
    cout << "\t\t\t\t\t\t\t\t[1] Go to gasper to find treasure room\n";
    cout << "\t\t\t\t\t\t\t\t[2] Contact with devil will kill you\n";
    cout << "\t\t\t\t\t\t\t\t[3] Find treasure to win\n";
    system("pause"); system("cls");
}

void Options()
{
    cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
    cout << "\t\t\t\t\t\t\t\t[MOVEMENT KEYS]\n";
    cout << "\t\t\t\t\t\t\t\t[1] Press A for left movement\n";
    cout << "\t\t\t\t\t\t\t\t[2] Press D for right movement\n";
    cout << "\t\t\t\t\t\t\t\t[3] Press W for up movement\n";
    cout << "\t\t\t\t\t\t\t\t[4] Press S for down movement\n";
    system("pause"); system("cls");
}