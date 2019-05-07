#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_SZ 256

int main() {
    /* Initalize variables */
    int	picture[10][10]= {
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //row 1
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, //row 2
		{0, 0, 0, 0, 1, 1, 1, 1, 0, 0}, //row 3
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0}, //row 4
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0}, //row 5
		{0, 0, 0, 0, 0, 1, 1, 0, 0, 0}, //row 6
		{0, 0, 0, 0, 1, 1, 1, 0, 0, 0}, //row 7
		{0, 0, 0, 0, 1, 1, 1, 1, 0, 0}, //row 8
		{0, 0, 0, 0, 0, 1, 1, 1, 0, 0}, //row 9
		{0, 0, 0, 0, 0, 0, 0, 0, 0, 0}  //row 10
		};
	int	coord[4];	//will contain the final coordinates (coord[top, left, bottom, right])
	int top = 11;			//top-most row (11 is because it will never be 11; used as a comparison value to see if initial 1 has been found yet)
	int left = 11;		//left-most column
	int bottom = 11;		//bottom-most row
	int right = 11;		//right-most column
	int i, j;

	for(i = 0; i < 10; i++){	//row loop (matters for top and bottom)
		for(j = 0; j < 10; j++){	//column loop (matters for left and right)
			if(picture[i][j] == 1){
				if(top == 11 && left == 11 && bottom == 11 && right == 11){ //if the coord don't have values yet (start as NULL), give them the first coord to base the rest of the comparisons off of
					top = i;
					left = j;
					bottom = i;
					right = j;
				}
				else{	//if the coord do have values in them, begin comparing to find the outermost values
					if(i < top) top = i;
					else if (i > bottom) bottom = i;
					else if (j < left) left = j;
					else if (j > right) right = j;
				}
			}
			
		}
		
	}
/*	top++;		//indexes values to where they would be on scale of 1 - 10
	left++;
	bottom++;
	right++; */
	coord[0]= top;
	coord[1]= left;
	coord[2]= bottom;
	coord[3]= right; 
    /* Prints matrix. */
    printf("Here is your matrix:\n");
	for (i=0; i<10; i++)
	{
	    for(j=0; j<10; j++)
	        {
	         printf("%d  ", picture[i][j]);
	        }
	    printf("<< row %d", i);
		printf("\n");
	 }
	 
	 printf("\nThese are the values that were found: \ntop-most = %d \nleft-most = %d \nbottom-most = %d \nright-most = %d\n\n", top, left, bottom, right);

    printf("Therefore, the coordinates to be sent to the Arduino are:\nCoord = [");
	for (i=0; i<4; i++)
	{
	    printf("%d  ", coord[i]);
	 }
	 printf("].");
	 
    /* Print Message. */
    printf("\n\nI hope your values are what they were supposed to be!\n\n");

    /* Pause the Console */
    system("pause");

    /* Free memory and exit. */
    return 0;
}
