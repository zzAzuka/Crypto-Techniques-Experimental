#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Function to compute modular inverse
int findModInverse(int a, int m)
{
    a = a % m;
    for (int x = 1; x < m; x++)
    {
        if ((a * x) % m == 1)
        {
            return x;
        }
    }
    return -1;
}

// Convert character to index (0-25)
int toIndex(char c)
{
    return toupper(c) - 'A';
}

// Convert index to character, maintaining case
char toChar(int idx, int upper)
{
    return upper ? ('A' + idx) : ('a' + idx);
}

// Atbash Cipher
void applyAtbash()
{
    char input[1000];
    printf("Input text: ");
    fgets(input, sizeof(input), stdin);

    for (int i = 0; input[i]; i++)
    {
        if (isalpha(input[i]))
        {
            int isUpper = isupper(input[i]);
            input[i] = isUpper ? ('Z' - (input[i] - 'A')) : ('z' - (input[i] - 'a'));
        }
    }
    printf("Atbash Result: %s", input);
}

// Caesar Cipher
void applyCaesar()
{
    char input[1000];
    int shift = 3;
    printf("Input text: ");
    fgets(input, sizeof(input), stdin);

    for (int i = 0; input[i]; i++)
    {
        if (isalpha(input[i]))
        {
            char base = isupper(input[i]) ? 'A' : 'a';
            input[i] = base + ((input[i] - base + shift) % 26);
        }
    }
    printf("Caesar Result: %s", input);
}

// August Cipher
void applyAugust()
{
    char input[1000];
    printf("Input text: ");
    fgets(input, sizeof(input), stdin);

    for (int i = 0; input[i]; i++)
    {
        if (isalpha(input[i]))
        {
            char base = isupper(input[i]) ? 'A' : 'a';
            input[i] = base + ((input[i] - base + 1) % 26);
        }
    }
    printf("August Result: %s", input);
}

// Affine Cipher
void applyAffine()
{
    char input[1000];
    int a, b;
    printf("Input text: ");
    fgets(input, sizeof(input), stdin);
    printf("Enter a and b (keys): ");
    scanf("%d %d", &a, &b);
    getchar();

    if (findModInverse(a, 26) == -1)
    {
        printf("Error: 'a' must be coprime with 26!\n");
        return;
    }

    for (int i = 0; input[i]; i++)
    {
        if (isalpha(input[i]))
        {
            char base = isupper(input[i]) ? 'A' : 'a';
            input[i] = base + ((a * (input[i] - base) + b) % 26);
        }
    }
    printf("Affine Result: %s", input);
}

// Vigenere Cipher
void applyVigenere()
{
    char input[1000], key[100];
    printf("Enter text: ");
    fgets(input, sizeof(input), stdin);
    printf("Enter key (letters only): ");
    fgets(key, sizeof(key), stdin);

    int keyLength = strlen(key) - 1;
    int keyIdx = 0;

    for (int i = 0; input[i]; i++)
    {
        if (isalpha(input[i]))
        {
            int shift = toIndex(key[keyIdx % keyLength]);
            char base = isupper(input[i]) ? 'A' : 'a';
            input[i] = base + ((input[i] - base + shift) % 26);
            keyIdx++;
        }
    }
    printf("Vigenere Result: %s", input);
}

// Gronsfeld Cipher
void applyGronsfeld()
{
    char input[1000], key[100];
    printf("Enter text: ");
    fgets(input, sizeof(input), stdin);
    printf("Enter key (digits only): ");
    fgets(key, sizeof(key), stdin);

    int keyLength = strlen(key) - 1;
    int keyIdx = 0;

    for (int i = 0; input[i]; i++)
    {
        if (isalpha(input[i]) && isdigit(key[keyIdx % keyLength]))
        {
            int shift = key[keyIdx % keyLength] - '0';
            char base = isupper(input[i]) ? 'A' : 'a';
            input[i] = base + ((input[i] - base + shift) % 26);
            keyIdx++;
        }
    }
    printf("Gronsfeld Result: %s", input);
}

// Beaufort Cipher
void applyBeaufort()
{
    char input[1000], key[100];
    printf("Enter text: ");
    fgets(input, sizeof(input), stdin);
    printf("Enter key (letters): ");
    fgets(key, sizeof(key), stdin);

    int keyLength = strlen(key) - 1;
    int keyIdx = 0;

    for (int i = 0; input[i]; i++)
    {
        if (isalpha(input[i]))
        {
            int p = toIndex(input[i]);
            int k = toIndex(key[keyIdx % keyLength]);
            int cipher = (26 + k - p) % 26;
            input[i] = isupper(input[i]) ? ('A' + cipher) : ('a' + cipher);
            keyIdx++;
        }
    }
    printf("Beaufort Result: %s", input);
}

// Autokey Cipher
void applyAutokey()
{
    char input[1000], key[100];
    printf("Enter text: ");
    fgets(input, sizeof(input), stdin);
    printf("Enter key (letters): ");
    fgets(key, sizeof(key), stdin);

    int keyLength = strlen(key) - 1;
    char extendedKey[1000];
    strncpy(extendedKey, key, keyLength);
    extendedKey[keyLength] = '\0';

    int extIdx = keyLength;
    for (int i = 0; input[i] && extIdx < sizeof(extendedKey) - 1; i++)
    {
        if (isalpha(input[i]))
        {
            extendedKey[extIdx++] = input[i];
        }
    }
    extendedKey[extIdx] = '\0';

    int keyIdx = 0;
    for (int i = 0; input[i]; i++)
    {
        if (isalpha(input[i]))
        {
            int shift = toIndex(extendedKey[keyIdx]);
            char base = isupper(input[i]) ? 'A' : 'a';
            input[i] = base + ((input[i] - base + shift) % 26);
            keyIdx++;
        }
    }
    printf("Autokey Result: %s", input);
}

// Running Key Cipher
void applyRunningKey()
{
    char input[1000], key[1000];
    printf("Enter text: ");
    fgets(input, sizeof(input), stdin);
    printf("Enter running key (same or longer): ");
    fgets(key, sizeof(key), stdin);

    int keyIdx = 0;
    for (int i = 0; input[i] && key[keyIdx]; i++)
    {
        if (isalpha(input[i]))
        {
            while (key[keyIdx] && !isalpha(key[keyIdx]))
                keyIdx++;
            if (!key[keyIdx])
                break;
            int shift = toIndex(key[keyIdx]);
            char base = isupper(input[i]) ? 'A' : 'a';
            input[i] = base + ((input[i] - base + shift) % 26);
            keyIdx++;
        }
    }
    printf("Running Key Result: %s", input);
}

// Hill Cipher
int calcDeterminant(int a, int b, int c, int d)
{
    return (a * d - b * c) % 26;
}

void applyHill()
{
    char input[1000];
    int key[2][2];
    printf("Enter text (letters only, even length): ");
    fgets(input, sizeof(input), stdin);
    printf("Enter 2x2 key matrix (4 numbers, e.g., 3 5 2 7): ");
    scanf("%d %d %d %d", &key[0][0], &key[0][1], &key[1][0], &key[1][1]);
    getchar();

    int det = calcDeterminant(key[0][0], key[0][1], key[1][0], key[1][1]);
    if (det < 0)
        det += 26;
    if (findModInverse(det, 26) == -1)
    {
        printf("Error: Determinant must be coprime with 26!\n");
        return;
    }

    int len = strlen(input) - 1;
    for (int i = 0; i < len - 1; i += 2)
    {
        if (isalpha(input[i]) && isalpha(input[i + 1]))
        {
            int p1 = toIndex(input[i]);
            int p2 = toIndex(input[i + 1]);
            int c1 = (key[0][0] * p1 + key[0][1] * p2) % 26;
            int c2 = (key[1][0] * p1 + key[1][1] * p2) % 26;
            input[i] = isupper(input[i]) ? ('A' + c1) : ('a' + c1);
            input[i + 1] = isupper(input[i + 1]) ? ('A' + c2) : ('a' + c2);
        }
    }
    printf("Hill Result: %s", input);
}

// Rail Fence Cipher
void applyRailFence()
{
    char input[1000], result[1000];
    int rails;
    printf("Enter text: ");
    fgets(input, sizeof(input), stdin);
    printf("Enter rail count: ");
    scanf("%d", &rails);
    getchar();

    if (rails <= 1)
    {
        printf("Rail Fence Result: %s", input);
        return;
    }

    int len = strlen(input) - 1;
    char rail[50][1000];
    for (int i = 0; i < rails; i++)
    {
        for (int j = 0; j < len; j++)
        {
            rail[i][j] = '.';
        }
    }

    int row = 0, dir = 1;
    for (int i = 0; i < len; i++)
    {
        rail[row][i] = input[i];
        row += dir;
        if (row == rails - 1 || row == 0)
            dir = -dir;
    }

    int k = 0;
    for (int i = 0; i < rails; i++)
    {
        for (int j = 0; j < len; j++)
        {
            if (rail[i][j] != '.')
            {
                result[k++] = rail[i][j];
            }
        }
    }
    result[k] = '\0';
    printf("Rail Fence Result: %s\n", result);
}

// Route Cipher
void applyRoute()
{
    char input[1000];
    int rows, cols;
    printf("Enter text: ");
    fgets(input, sizeof(input), stdin);
    printf("Enter grid rows and columns: ");
    scanf("%d %d", &rows, &cols);
    getchar();

    int len = strlen(input) - 1;
    char grid[50][50];
    int k = 0;

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            grid[i][j] = (k < len && isalpha(input[k])) ? input[k++] : 'X';
        }
    }

    char result[1000];
    k = 0;
    int top = 0, bottom = rows - 1, left = 0, right = cols - 1;
    while (top <= bottom && left <= right)
    {
        for (int j = left; j <= right; j++)
            result[k++] = grid[top][j];
        top++;
        for (int i = top; i <= bottom; i++)
            result[k++] = grid[i][right];
        right--;
        if (top <= bottom)
        {
            for (int j = right; j >= left; j--)
                result[k++] = grid[bottom][j];
            bottom--;
        }
        if (left <= right)
        {
            for (int i = bottom; i >= top; i--)
                result[k++] = grid[i][left];
            left++;
        }
    }
    result[k] = '\0';
    printf("Route Result: %s\n", result);
}

// Myszkowski Cipher
void applyMyszkowski()
{
    char input[1000], key[100];
    int cols;
    printf("Enter text: ");
    fgets(input, sizeof(input), stdin);
    printf("Enter key (letters): ");
    fgets(key, sizeof(key), stdin);
    cols = strlen(key) - 1;

    int len = strlen(input) - 1;
    int rows = (len + cols - 1) / cols;
    char grid[50][50];

    int k = 0;
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            grid[i][j] = (k < len && isalpha(input[k])) ? input[k++] : 'X';
        }
    }

    int order[100];
    for (int i = 0; i < cols; i++)
        order[i] = i;
    for (int i = 0; i < cols - 1; i++)
    {
        for (int j = 0; j < cols - i - 1; j++)
        {
            if (key[order[j]] > key[order[j + 1]])
            {
                int temp = order[j];
                order[j] = order[j + 1];
                order[j + 1] = temp;
            }
        }
    }

    char result[1000];
    k = 0;
    for (int keyVal = 'A'; keyVal <= 'Z'; keyVal++)
    {
        for (int j = 0; j < cols; j++)
        {
            if (toupper(key[order[j]]) == keyVal)
            {
                for (int i = 0; i < rows; i++)
                {
                    if (grid[i][order[j]] != '\0')
                    {
                        result[k++] = grid[i][order[j]];
                    }
                }
            }
        }
    }
    result[k] = '\0';
    printf("Myszkowski Result: %s\n", result);
}

// Menu
void showMenu()
{
    int choice;
    while (1)
    {
        printf("\n=== Cryptography Menu ===\n");
        printf("1. Atbash\n2. Caesar\n3. August\n4. Affine\n5. Vigenere\n");
        printf("6. Gronsfeld\n7. Beaufort\n8. Autokey\n9. Running Key\n");
        printf("10. Hill\n11. Rail Space\n12. Route\n13. Myszkowski\n0. Exit\n");
        printf("Select option: ");
        scanf("%d", &choice);
        getchar();

        switch (choice)
        {
        case 1:
            applyAtbash();
            break;
        case 2:
            applyCaesar();
            break;
        case 3:
            applyAugust();
            break;
        case 4:
            applyAffine();
            break;
        case 5:
            applyVigenere();
            break;
        case 6:
            applyGronsfeld();
            break;
        case 7:
            applyBeaufort();
            break;
        case 8:
            applyAutokey();
            break;
        case 9:
            applyRunningKey();
            break;
        case 10:
            applyHill();
            break;
        case 11:
            applyRailFence();
            break;
        case 12:
            applyRoute();
            break;
        case 13:
            applyMyszkowski();
            break;
        case 0:
            exit(0);
        default:
            printf("Invalid option!\n");
        }
    }
}

int main()
{
    showMenu();
    return 0;
}