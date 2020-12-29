#include <conio.h>
#include <vector>
struct Gamer {
    bool Test = false;
    std::vector<char> Button;
    int count = 0;
    bool Exit() {
        if (Test) {
            count++;
            return (Button[count - 1] == 'q');
        }
        if (count == 0) {
            count++;
            return false;
        }
        int c = getch();
        if (c == 'q')
            return true;
        return false;
    }
};