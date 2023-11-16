# Slot-Machine

A simple slot machine game.

-Slot wheels are randomized & pulled from an array in spinWheels();
-Horizontal and diagonal wins are accounted for, vertical wins are not. *note: in the current wheel array, a vertical win is not possible.
-Up to 3 pairs can be made at once, adding bonuses to awards.
-The standard icons of the wheels are: 7, 8, O, @, and SPACE.

All parameters, including:
-bonus multipliers
-award amounts
-starting coins
-starting money 
-coin cost 
Can be changed through the values of the constants in lines 9-20

Running out coins will prompt the coin purchasing menu.
If coins and money are both equal to zero, an exit message will be output, and the program will exit.
By typing in "0" as your desired amount of coins to purchase, the game will enter a confimation screen, asking if you'd like to walk away.

*note: Typing in anything other than a number when prompted for a coin value will cause the program to crash.
