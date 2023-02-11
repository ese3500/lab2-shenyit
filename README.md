# lab2_morse_skeleton

The link below is a demo video of the Morse code translations. The red LED blinking represents a dot and the green LED blinking represents a dash. 

I am printing “EMILY” into the serial port:
E	.
M	_ _
I	. .
L	. _ . .
Y	_ . _ _

Other than the UART file in order to print to the serial port, no other files were used. The times for dashes, dots, and spaces were also not extended or changed from Part C. 

I used a time prescaler value of 256. Though the times for dashes, dots, and spaces were not changed, the number of ticks calculated for 30ms, 200ms and 400ms were different due to the prescaler. For 30ms, the number of ticks was now 480000/256 = 1875. For 200ms, the number of ticks was now 12500. For 400ms, the number of ticks was now 25000. 

The code is composed of three main sections. There is a “printLetter” function that checks what ASCII character the String array contains. After the function has checked what the ASCII character is, the String array is then reset to take in the next Morse code.

The interrupt checks to see if the switch has been pressed or released. When the switch has been pressed, TCNT1 is reset to 0 and an unsigned int i is also set to 0. This is done in order to prevent potential overflow. Once the switch has been released, an unsigned int j takes the current value of TCNT1. 

Then the difference of j - i is calculated. If it is between 30ms to 200ms, the red LED is lit up and a dot is stored in the String array. If it is between 200ms to 400ms, the green LED is lit up and a dash is stored in the String array. If it is longer than 400ms or less than 30ms, then nothing will happen. Also, checkSpace, a variable that keeps track of whether the last value in the String array is a dot or dash, is set to 0. Note: The video recording could not capture all the LED flashes as the video was compressed so it lost a bit of quality, even though they were lighting up in real-life.

The main function keeps track of the unsigned int light variable, and once this light variable increments to 5000, it turns off the red or green LED. This is to prevent the use of delays in the code whilst also being able to turn off the LED after a small amount of time.

We also check that if after a certain amount of time no button is pressed, we print out one space. This is done in the main function. First, we must account for overflow. If j + 40000 is greater than 62500, the maximum value that the timer goes up to, as we have prescaled the timer by the value of 256, then we reset TCNT1 to 0 and take away 62500 from j to prevent overflow. Then we check if j + 40000 is less than TCNT1. If it is, we set checkSpace to 1 to indicate that we have gone to a space, and we go to the “printLetter” function.

https://drive.google.com/file/d/1P3QgMHXoYqEVa79Ag3l1B47OC1zRVJUw/view?usp=share_link 
