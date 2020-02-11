/*									tab:8
 *
 * main.c - skeleton source file for ECE220 picture drawing program
 *
 * "Copyright (c) 2018 by Charles H. Zega, and Saransh Sinha."
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose, without fee, and without written agreement is
 * hereby granted, provided that the above copyright notice and the following
 * two paragraphs appear in all copies of this software.
 *
 * IN NO EVENT SHALL THE AUTHOR OR THE UNIVERSITY OF ILLINOIS BE LIABLE TO
 * ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
 * DAMAGES ARISING OUT  OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION,
 * EVEN IF THE AUTHOR AND/OR THE UNIVERSITY OF ILLINOIS HAS BEEN ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * THE AUTHOR AND THE UNIVERSITY OF ILLINOIS SPECIFICALLY DISCLAIM ANY
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE
 * PROVIDED HEREUNDER IS ON AN "AS IS" BASIS, AND NEITHER THE AUTHOR NOR
 * THE UNIVERSITY OF ILLINOIS HAS ANY OBLIGATION TO PROVIDE MAINTENANCE,
 * SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS."
 *
 * Author:	    Charles Zega, Saransh Sinha
 * Version:	    1
 * Creation Date:   12 February 2018
 * Filename:	    mp4.c
 * History:
 *	CZ	1	12 February 2018
 *		First written.
 */
#include "mp4.h"
#include <math.h>
/*
	You must write all your code only in this file, for all the functions!
*/


/*
 *  near_horizontal
 *
 *
 *
 *
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
near_horizontal(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
	int32_t x, y;
	if (x_start <= x_end){
	for (x = x_start; x <= x_end; x++){
		y = (2 * (y_end - y_start) * (x - x_end) + 1) / (2 * (x_end - x_start)) + y_end;
		draw_dot(x, y);
		if (!draw_dot(x, y))
		return 0;
	}
}
	else{
		for (x = x_end; x <= x_start; x++){
			y = (2 * (y_end - y_start) * (x - x_end) + 1) / (2 * (x_end - x_start)) + y_end;
			draw_dot(x, y);
			if (!draw_dot(x, y))
			return 0;
		}

	}
	return 1;
}

/*
 *  near_vertical
 *
 *
 *
 *
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
near_vertical(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
  int32_t x, y;
	if (y_start <= y_end){
	for (y = y_start; y <= y_end; y++){
		x = (2 * (x_end - x_start) * (y - y_end) + 1) / (2 * (y_end - y_start)) + x_end;
		draw_dot(x, y);
		if (!draw_dot(x, y)) return 0;
	}
}
	else {
	for (y = y_end; y <= y_start; y++){
		x = (2 * (x_end - x_start) * (y - y_end) + 1) / (2 * (y_end - y_start)) + x_end;
		draw_dot(x, y);
		if (!draw_dot(x, y)) return 0;
	}
}
	return 1;
}

/*
 *  draw_line
 *
 *
 *
 *
 * INPUTS: x_start,y_start -- the coordinates of the pixel at one end of the line
 * 	   x_end, y_end    -- the coordinates of the pixel at the other end
 * OUTPUTS: draws a pixel to all points in between the two given pixels including
 *          the end points
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_line(int32_t x_start, int32_t y_start, int32_t x_end, int32_t y_end){
	/* Your code goes here! */
	int32_t dump;
	if (x_end != x_start){
  int slope = (y_end - y_start) / (x_end - x_start);

	if (slope >= -1 && slope <= 1)
	dump = near_horizontal(x_start, y_start, x_end, y_end);
	else
	dump = near_vertical(x_start, y_start, x_end, y_end);
}
  else
	dump = near_vertical(x_start, y_start, x_end, y_end);
	return dump;
}


/*
 *  draw_rect
 *
 *
 *
 *
 * INPUTS: x,y -- the coordinates of the of the top-left pixel of the rectangle
 *         w,h -- the width and height, respectively, of the rectangle
 * OUTPUTS: draws a pixel to every point of the edges of the rectangle
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_rect(int32_t x, int32_t y, int32_t w, int32_t h){
	/* Your code goes here! */
  if (w < 0 || h < 0)
	return 0;
	//left vertical
	if (draw_line(x, y, x, y+h) == 0) return 0;
	//right vertical
	if (draw_line(x+w, y, x+w, y+h) == 0) return 0;
	//Top horizontal
	if (draw_line (x, y, x+w, y) == 0) return 0;
	//Bottom horizontal
	if (draw_line (x, y+h, x+w, y+h) == 0) return 0;
  //All done! Yay!
	return 1;
}


/*
 *  draw_triangle
 *
 *
 *
 *
 * INPUTS: x_A,y_A -- the coordinates of one of the vertices of the triangle
 *         x_B,y_B -- the coordinates of another of the vertices of the triangle
 *         x_C,y_C -- the coordinates of the final of the vertices of the triangle
 * OUTPUTS: draws a pixel to every point of the edges of the triangle
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_triangle(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
	/* Your code goes here! */
	//Left
	if (draw_line(x_A, y_A, x_B, y_B) == 0) return 0;
	//Bottom
	if (draw_line(x_A, y_A, x_C, y_C) == 0) return 0;
	//right
	if (draw_line(x_C, y_C, x_B, y_B) == 0) return 0;
	//All done, yay!
	return 1;
}

/*
 *  draw_parallelogram
 *
 *
 *
 *
 * INPUTS: x_A,y_A -- the coordinates of one of the vertices of the parallelogram
 *         x_B,y_B -- the coordinates of another of the vertices of the parallelogram
 *         x_C,y_C -- the coordinates of another of the vertices of the parallelogram
 * OUTPUTS: draws a pixel to every point of the edges of the parallelogram
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_parallelogram(int32_t x_A, int32_t y_A, int32_t x_B, int32_t y_B, int32_t x_C, int32_t y_C){
	/* Your code goes here! */
	//Top
	if (draw_line(x_A, y_A, x_B, y_B) == 0) return 0;
	//right
  if (draw_line(x_B, y_B, x_C, y_C) == 0) return 0;
	//solve for x_D and y_D
	int32_t x_D = x_C + (x_A - x_B);
	int32_t y_D = y_C + (y_A - y_B);
	//Bottom
	if (draw_line(x_C, y_C, x_D, y_D) == 0) return 0;
	//left
	if (draw_line(x_D, y_D, x_A, y_A) == 0) return 0;
  //All done!! Yay!
	return 1;
}


/*
 *  draw_circle
 *
 *
 *
 *
 * INPUTS: x,y -- the center of the circle
 *         inner_r,outer_r -- the inner and outer radius of the circle
 * OUTPUTS: draws a pixel to every point whose distance from the center is
 * 	    greater than or equal to inner_r and less than or equal to outer_r
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
draw_circle(int32_t x, int32_t y, int32_t inner_r, int32_t outer_r){
	/* Your code goes here!*/

	if (inner_r < 0 || outer_r < inner_r) return 0;
	//Looping thru radii.
	int x_end, y_end;
   	for (x_end = x - outer_r; x_end <= x + outer_r; x_end++){
			for (y_end = y - outer_r; y_end <= y + outer_r; y_end++)
			if (outer_r * outer_r >= (y_end - y)*(y_end - y) + (x_end - x)*(x_end - x) && inner_r * inner_r <= (y_end - y)*(y_end - y) + (x_end - x)*(x_end - x)){
			if (!draw_dot(x_end, y_end)) return 0;
		}
			}
			//All done! Yay!
			return 1;
		}



/*
 *  rect_gradient
 *
 *
 *
 *
 * INPUTS: x,y -- the coordinates of the of the top-left pixel of the rectangle
 *         w,h -- the width and height, respectively, of the rectangle
 *         start_color -- the color of the far left side of the rectangle
 *         end_color -- the color of the far right side of the rectangle
 * OUTPUTS: fills every pixel within the bounds of the rectangle with a color
 *	    based on its position within the rectangle and the difference in
 *          color between start_color and end_color
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */

int32_t
rect_gradient(int32_t x, int32_t y, int32_t w, int32_t h, int32_t start_color, int32_t end_color){
	/* Your code goes here! */
  if (w < 0 || h < 0) return 0;
  //loops thru columns

	int32_t cur_x, cur_y, level_r, level_g, level_b, level;
	for (cur_x = x; cur_x <= x + w; cur_x++){
			level_r = ((2 * (cur_x - x) * (((end_color & 0x00FF0000) >> 16) - ((start_color & 0x00FF0000) >> 16)) + 1) / (2*w)) + ((start_color & 0x00FF0000) >> 16);
			level_r = level_r << 16;
			level_g = ((2 * (cur_x - x) * (((end_color & 0x0000FF00) >> 8) - ((start_color & 0x0000FF00) >> 8)) + 1) / (2*w)) + ((start_color & 0x0000FF00) >> 8);
			level_g = level_g << 8;
			level_b = ((2 * (cur_x - x) * ((end_color & 0x000000FF) - (start_color & 0x000000FF)) + 1) / (2*w)) + (start_color & 0x000000FF);
			level = level_r + level_g + level_b;
		for (cur_y = y; cur_y <= y + h; cur_y++){
			set_color(level);
			if (!draw_dot(cur_x, cur_y)) return 0;
		}
	}

	return 1;
}


/*
 *  draw_picture
 *
 *
 *
 *
 * INPUTS: none
 * OUTPUTS: alters the image by calling any of the other functions in the file
 * RETURN VALUE: 0 if any of the pixels drawn are out of bounds, otherwise 1
 * SIDE EFFECTS: none
 */


int32_t
draw_picture(){
	/* Your code goes here! */

return 1;
}
