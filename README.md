# PES-Assignment-4

Files created: 
button.h
button.c
led_on.h
led_on.c
log.h
pwm.h
pwm.c
state_machine.h
state_machine.c
systick.h
systick.c
touch.h
touch.c

SysTick interrupt is generated every 50 milliseconds.

For Extra Credit #2, 
Port D Pin 3 is used as a switch. 

main() function is in the file Buffahiti.c

All header files to be included and all source code files are in "source" folder. 

For DEBUG mode, LOG calls are included in every state transition. 

Touch Sensor and GPIO Switch interrupt are being polled every 100 milliseconds.

UART and LOG messages are displayed using TERA TERM. 
In Tera Term, after selecting the COM port, 
Go to Setup->Serial Port-> Baud rate = 115200.
Then, go to Setup->Terminal->Newline->Receive->LF

Extra Credit #1
Peer Review: 
Partner: Amey Dashaputre

Peer Review Date: 12 October 2021
Peer Review Time: 4.30 AM

Comments by reviewer:
1. Remove all the commented code lines.
2. Add comment in SYSTICK-> VAL
3. Add comments in pwm init functions.
4. Add comments in switch init

Edits: 
Added comments to the sections suggested by reviewer.


-------------
Final Code is tagged with tag "final-code-for-review"