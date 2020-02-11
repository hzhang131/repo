#include <stdio.h>
#include <stdint.h>

void defaultArray(int32_t r1, int32_t r2, int32_t r3, int32_t r4, int32_t* standard, int32_t width);
void generateArray(int32_t r1, int32_t r2, int32_t r3, int32_t r4, int32_t diff, int32_t loc, int32_t num, int32_t width, int32_t* checker);
void perfectArray(int32_t width, int32_t* checked);
void printArray(int32_t width, int32_t* checked);

void printArray(int32_t width, int32_t* checked){
  int y;
  for (y = 0; y < width; y++)
  {
    if (checked[y] == 0)
    printf(".");
    else
    printf("X");
  }
}
void perfectArray(int32_t width, int32_t* checked){
  int z;
  for (z = 0; z < width; z++){
    checked[z] = 1;
  }
}

void defaultArray(int32_t r1, int32_t r2, int32_t r3, int32_t r4, int32_t* standard, int32_t width){
  int a, b, c, d, e;
  for (a = 0; a < r1; a++){
    standard[a] = 1;
  }
  standard[r1] = 0;
  for (b = r1+1; b < r1+1+r2; b++){
    standard[b] = 1;
  }
  standard[r1+1+r2] = 0;
 for (c = r1+2+r2; c < r1+2+r2+r3; c++){
   standard[c] = 1;
 }
 standard[r1+2+r2+r3] = 0;
 for (d = r1+3+r2+r3; d< r1+r2+r3+r4+3; d++){
   standard[d] = 1;
 }
 for (e = r1+r2+r3+r4+3; e < width; e++ ){
   standard[e] = 0;
 }
}

void generateArray(int32_t r1, int32_t r2, int32_t r3, int32_t r4, int32_t diff, int32_t loc, int32_t num, int32_t width, int32_t* checker)
{
  int f, g, h, i, j, k, l, m, n, temp1, temp2, temp3, temp4, addr;
  temp1 = r1;
  temp2 = r2;
  temp3 = r3;
  temp4 = r4;
  addr = 0;

  if (loc == 0){
    for (f = 0; f < num; f++){
      checker[f] = 0;
    }
    addr += num;
  }
  for (g = addr; g < addr + temp1; g++){
    checker[g] = 1;
  }
  addr = addr + temp1;
  checker[addr] = 0;
  addr ++;

  if (loc == 1){
    for (h = addr; h < addr+num; h++){
      checker[h] = 0;
    }
    addr += num;
  }

  for (i = addr; i < addr+temp2; i++){
    checker[i] = 1;
  }
  addr = addr + temp2;
  checker[addr] = 0;
  addr ++;

  if (loc == 2){
    for (j = addr; j < addr+num; j++){
      checker[j] = 0;

    }
    addr += num;
  }

  for (k = addr; k < addr + temp3; k++ )
  {
    checker[k] = 1;
  }
  addr = addr + temp3;
  checker [addr] = 0;
  addr ++;

  if (loc == 3){
    for (l = addr; l < addr + num; l++){
      checker[l] = 0;
    }
      addr += num;
  }

  for (m = addr; m < addr + temp4; m++ )
  {
    checker[m] = 1;
  }
  addr = addr + temp4;
  checker[temp1 + temp2 + temp3 + temp4 + 3] = 0;
  addr ++;

  for (n = addr; n < width - addr; n++ ){
    checker[n] = 0;
  }


}

int32_t print_row (int32_t r1, int32_t r2, int32_t r3, int32_t r4, int32_t width){
  // Min number of pixels required.
  int32_t total_pixel = r1 + r2 + r3 + r4 + 1 + 1 + 1;
  int32_t i;
  int32_t j;
  int32_t k;
  int32_t l;
  int32_t diff = width - total_pixel;
  int32_t standard[width];
  int32_t checker[width];
  int32_t checked[width];

  if (total_pixel <= width && r1 > 0){

   defaultArray(r1, r2, r3, r4, standard, width);
   perfectArray(width, checked);


   for (i = 0; i < 4; i++)
   {

      for (j = 0; j <= diff; j++)
      {

        for (k = 0; k <= j; k++)
        {

          generateArray(r1, r2, r3, r4, j, i, k, width, checker);
          for (l = 0; l < width; l++)
          {

            if (checker[l] != standard[l])
            checked[l] = 0;
            else if(checker[l] == standard[l] && checker[l] == 0)
            checked[l] = 0;
          }
        }
      }
   }
   printArray(width, checked);
   printf("\n");
   return 1;
  }
  else
  return 0;
}
