#include<stdio.h>
#include<stdlib.h>

struct pgmIMAGESTRUCT
{
    int maxVal;
    int width;
    int height;
    int data[800][800];
};

int sum(int arr[], int n)
{
    int sum = 0; // initialize sum
 
    // Iterate through all elements
    // and add them to sum
    for (int i = 0; i < n; i++)
    sum += arr[i];
 
    return sum;
}


int main()
{
    
    FILE *imagein,*imageout;

    int row, col;

    int i,j;
    int ch_int = 10;
    
    //Create a 2D array to store the pixels
    struct pgmIMAGESTRUCT *imginfo = malloc(sizeof(struct pgmIMAGESTRUCT));
    
    
    char infpath[500],outfpath[500];

    printf("Enter PGM file path:");
    scanf("%s",infpath);
    imagein = fopen(infpath,"r+");

    if(imagein == NULL)
    {
        printf("Error opening file");
        exit(8);
    }

    while(getc(imagein) != '\n');           // Ignore the first line in the input file

    if (getc(imagein) == '#' )              // If it is the case, ignore the second line in the input file
        {
        while(getc(imagein) != '\n');
        }
    else
        {
        fseek(imagein, -1, SEEK_CUR);
        }

    fscanf(imagein,"%d", &imginfo->width);
    fscanf(imagein,"%d", &imginfo->height);
    fscanf(imagein,"%d", &imginfo->maxVal);
    printf("\n width  = %d\n",imginfo->width);
    printf("\n height = %d\n",imginfo->height);
    printf("\n maxVal = %d\n",imginfo->maxVal);
    
    
    //DEMOSAICING - bilinear interpolation method

    //for each pixel, check if it is R, G or B using its row/col number (if its even/odd)
    //Once you know which color filter, we can use appropriate neighbouring pixels to average the RGB values
    
    for (row=0; row<imginfo->height; row++){

        for (col=0; col < imginfo->width; col++)
        {
            fscanf(imagein,"%d", &ch_int);
            imginfo->data[row][col] = ch_int;
            
            //Check if on RED filter, calculate RGB respectively
            if (row % 2 == 0 && col % 2 ==0) {
                //get blue average value
                float blue[4] = {imginfo->data[row-1][col+1], imginfo->data[row+1][col+1], imginfo->data[row-1][col-1], imginfo->data[row+1][col-1]};
                float B = sum(blue, 4) / sizeof(blue);
                
                //get green average value
                float green[4] = {imginfo->data[row][col+1], imginfo->data[row][col-1], imginfo->data[row-1][col], imginfo->data[row+1][col]};
                float G = sum(green, 4) / sizeof(green);
                
                //get red value
                float R = imginfo->data[row][col];
                
                //print rgb value of this pixel
                printf("row:", "%d", row);
                printf("col:", "%d", col);
                printf("R", "%.6f", R);
                printf("G", "%.6f", G);
                printf("B", "%.6f", B);
            }
            //check if on BLUE filter, calculate RGB respectively
            else if (row % 2 != 0 && col % 2 != 0) {
                //get red average value
                float red[4] = {imginfo->data[row-1][col+1], imginfo->data[row+1][col+1], imginfo->data[row-1][col-1], imginfo->data[row+1][col-1]};
                float R = sum(red, 4) / sizeof(red);
                
                //get green average value
                float green[4] = {imginfo->data[row][col+1], imginfo->data[row][col-1], imginfo->data[row-1][col], imginfo->data[row+1][col]};
                float G = sum(green, 4) / sizeof(green);
                
                //get blue value
                float B = imginfo->data[row][col];
                
                //print rgb value of this pixel
                printf("row:", "%d", row);
                printf("col:", "%d", col);
                printf("R", "%.6f", R);
                printf("G", "%.6f", G);
                printf("B", "%.6f", B);
                
            }
            //check if on green filter, calculate RGB respectively
            else {
                //get green average value
                float green[5] = {imginfo->data[row-1][col+1], imginfo->data[row-1][col+1], imginfo->data[row+1][col+1], imginfo->data[row-1][col-1], imginfo->data[row+1][col-1]};
                float G = sum(green, 5) / sizeof(green);
                
                //get red average value
                float red[2] = {imginfo->data[row-1][col], imginfo->data[row+1][col]};
                float R = sum(red, 2) / sizeof(red);
                
                //get blue value
                float blue[2] = {imginfo->data[row][col+1], imginfo->data[row][col-1]};
                float B = sum(blue, 2) / sizeof(blue);
                
                //print rgb value of this pixel
                printf("row:", "%d", row);
                printf("col:", "%d", col);
                printf("R", "%.6f", R);
                printf("G", "%.6f", G);
                printf("B", "%.6f", B);
                
            }
        }
    }

//close image file
    fclose(imagein);


    printf("Enter path of output file:");

    scanf("%s",outfpath);
    imageout = fopen(outfpath,"w+");

    
//print output file
    for ( i = 0 ; i < imginfo->height ; i++ )
    {
        for ( j = 0 ; j < imginfo->width ; j++ )
        {
            if (imginfo->data[i][j] == 0)
            fprintf( imageout,"%d  " , imginfo->data[i][j] );
            
        }
            fprintf( imageout,"\n" );
    }

    fclose(imageout);
    free(imginfo);

    return 0;
}
