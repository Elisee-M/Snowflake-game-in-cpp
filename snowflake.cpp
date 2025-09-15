#include <iostream>
#include <conio.h>   // for _kbhit() and _getch()
#include <windows.h> // for Sleep()
#include <cstdlib>   // for rand()

using namespace std;

int main() {
    const int width = 20;
    int snowX = rand() % width;  // Snowflake position
    int snowY = 0;
    int basketX = width / 2;     // Basket starts in middle
    int score = 0;

    while (true) {
        system("cls"); // clear screen

        // Draw play area
        for (int y = 0; y < 10; y++) {
            for (int x = 0; x < width; x++) {
                if (x == snowX && y == snowY)
                    cout << "❄"; // snowflake
                else if (y == 9 && x >= basketX && x < basketX + 3)
                    cout << "="; // basket
                else
                    cout << " ";
            }
            cout << endl;
        }

        cout << "Score: " << score << endl;

        // Move snowflake
        snowY++;
        if (snowY > 9) {
            // Check if caught
            if (snowX >= basketX && snowX < basketX + 3)
                score++;
            // Reset snowflake
            snowX = rand() % width;
            snowY = 0;
        }

        // Move basket
        if (_kbhit()) {
            char key = _getch();
            if (key == 'a' && basketX > 0) basketX--;
            if (key == 'd' && basketX < width - 3) basketX++;
        }

        Sleep(150); // control speed
    }
}
