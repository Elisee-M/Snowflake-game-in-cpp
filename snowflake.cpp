#include <iostream>
#include <conio.h>    // for _kbhit() and _getch()
#include <windows.h>  // for Sleep()
#include <cstdlib>    // for rand()

using namespace std;

int main() {
    int width, height, basketSize, speed;
    cout << "Enter play area width (10-40): ";
    cin >> width;
    cout << "Enter play area height (5-20): ";
    cin >> height;
    cout << "Enter basket size (2-5): ";
    cin >> basketSize;
    cout << "Enter speed in ms (50-500): ";
    cin >> speed;

    // Clamp speed to a reasonable minimum
    if (speed < 100) speed = 100;

    int snowX = rand() % width;
    int snowY = 0;
    int basketX = width / 2;
    int score = 0;
    int misses = 0;
    const int maxMisses = 3;

    while (true) {
        // Process basket movement BEFORE drawing, for more responsive controls
        for (int i = 0; i < 5; ++i) { // Check input several times per frame
            if (_kbhit()) {
                char key = _getch();
                if (key == 'a' && basketX > 0) basketX--;
                if (key == 'd' && basketX < width - basketSize) basketX++;
            }
            Sleep(speed / 5); // Spread out input checks for smoother control
        }

        system("cls");

        // Draw play area
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                if (x == snowX && y == snowY)
                    cout << "❄";
                else if (y == height - 1 && x >= basketX && x < basketX + basketSize)
                    cout << "=";
                else
                    cout << " ";
            }
            cout << endl;
        }

        cout << "Score: " << score << "  Misses: " << misses << "/" << maxMisses << endl;

        // Move snowflake
        snowY++;
        if (snowY > height - 1) {
            if (snowX >= basketX && snowX < basketX + basketSize)
                score++;
            else
                misses++;
            // Reset snowflake
            snowX = rand() % width;
            snowY = 0;
        }

        if (misses >= maxMisses) {
            cout << "Game Over! Final Score: " << score << endl;
            break;
        }
    }
}
