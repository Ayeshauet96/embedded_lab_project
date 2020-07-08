# embedded_lab_project

This project builds a QT application to  implement paratroopers game logic which is simply a rescue boat capable of moving left and right and is able to catch paratroopers falling at random frequencies. An LED matrix emulator which is itself a QT application is used as a game display. The emulator is accessed in the kernel space through a device driver layer.The misc char driver has a read function which expects the led state in a char array and a write function which allows the game logic to write the led-state to the emulator. 
The GUI hosts two buttons, a left and a right button to move the rescue boat appropriately. Also a field is added to show current score and game over messages.
