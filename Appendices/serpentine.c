#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SZ 256

int main() {
    /* Initalize variables */
    int top = 2;
    int bottom = 8;
    int left = 4;
    int right = 9;
    int coord[4];
    coord[0]= top;
	coord[1]= left;
	coord[2]= bottom;
	coord[3]= right;
	printf("top space: %d. ", top);
	printf("left space: %d. ", left);
	printf("bottom space: %d. ", bottom);
	printf("right space: %d. \n", right);
    
    /* here, when x= something and y= something, that is the number of rotations needed for that axis (i.e. the number that would be sent to the stepper motors)*/
    
    int x = left;	/*moves eraser to beginning x position*/
    printf("starting x position=%d\n", x);
    int y = top;	/*moves eraser to beginning y position*/
    printf("starting y position=%d\n", y);
    
    int rotateX = right - left; // should be positive
    printf("rotateX=%d\n", rotateX);
    int countY	= bottom - top;	// should be positive
    int temp = rotateX;
    x = rotateX;
    printf("x =%d\n", x);
    while(countY != 0){
    	    	y = 1;
    	printf("y =%d\n", y);
    	/*delay(time_to_move);*/
    	y = 0;
    	printf("y =%d\n", y);
    	countY = countY - 1;
    	
		x = temp;
		x = -x;
    	printf("x =%d\n", x);
    	/*delay(time_to_move*abs(rotateX));*/
    	temp = x;
    	x = 0;
    	printf("x =%d\n", x);
    
	}
	if(x < 0){
		x = -left;
		printf("x =%d\n", x);
		/*delay(time_to_move*left)*/
		x = 0;
		printf("x =%d\n", x);
		y = -bottom;
		printf("y =%d\n", y);
		/*delay(time_to_move*bottom)*/
		y = 0;
		printf("y =%d\n", y);
	}
	else{  //x > 0
		x = -right;
		printf("x =%d\n", x);
		/*delay(time_to_move*right)*/
		x = 0;
		printf("x =%d\n", x);
		y = -bottom;
		printf("y =%d\n", y);
		/*delay(time_to_move*bottom)*/
		y = 0;
		printf("y=%d\n", y);
	}
    
    

    /* Pause the Console */
    system("pause");

    /* Free memory and exit. */
    return 0;
}
