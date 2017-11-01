#include <iostream>

int main(void)
{
  using std::cout;
  using std::cin;

  int score1, score2;

  cout << "Enter score 1:";
  cin >> score1;

  cout << "\nEnter score 2: ";
  cin >> score2;

  cout << "\n";

  if (score1 > score2)
    cout << "Player 1 wins!";
  else if (score1 < score2)
    cout << "Player 2 wins";
  else
    cout << "Draw";
  cout << "\n";

}


/* Day 4 quiz section

1. Expression is something that can be evaluated (ie, not a comment)
2. Yes. 12.
3. 50
4. 1
5. unknown; 40; 40;
6. 14
7. first sets x to 3, second checks if it is equal to 3. First will always succeed.
8. F; T; T; F; T;

Ex
if (a!=b) && (a<b)) b=a; else a=b; /* pedantic != */

 */




