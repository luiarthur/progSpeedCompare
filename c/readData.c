// This Program reads in pairs of data.
// The data file must start with a line specifying 
// The number of lines of data in the file.
// If it does not already have it, using linux to add 
// the number of lines to the beginning of the file is 
// not difficult.

#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int x, y;
} Point;

int main() {
  int numOf;
  Point *myPoints = NULL;
  FILE *myfile = fopen ("data","r");
  if (myfile == NULL)
      perror ("Error opening file"); //or return 1;
  else
  {
      fscanf(myfile, "%d", &numOf);
      myPoints = (Point*)malloc(sizeof(Point) * numOf);
      while ( !feof (myfile) && numOf-- )
      {
          fscanf(myfile, "%d %d", &(myPoints[numOf].x), &(myPoints[numOf].y));
      }
  }
  fclose(myfile);
  //Do stuff with array
  int temp = myPoints[3].x;

  printf("%d\n",temp);
  free ((void*)myPoints);
  //getchar();//Press enter to close debugger etc.
  return 0;
}

/*
#include <stdio.h>
void main()
{
FILE *fopen(), *fp;
char c;
int i=0,j=0;
char file[50][50];
fp = fopen("data","r");
c = getc(fp) ;
while (c!= EOF)
{
file[i][j]=c;

    j++;
    c = getc(fp);

    if(j==50){
    i++;
    j=0;
    }
}
fclose(fp);
printf("%c\n",file[0][0]);
}
*/
