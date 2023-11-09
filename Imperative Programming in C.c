#include <stdio.h>
#include <stdlib.h>

// Structure to hold grayscale pixel data
typedef struct {
    unsigned char value;
} PixelGray;

// Function to read a PGM image into a 2D array
PixelGray** readPGM(const char* filename, int* width, int* height){
    /** Opening file and handling errors in case it doesn't open properly */
    FILE* lennaPGM = fopen(filename, "rb");
    if(lennaPGM == NULL){
        perror("Error: File failed to open.");
        return NULL;
    }

    /** Reading first 3 lines of the file and storing the values */
    char lineOne[4];
    int dim1, dim2, maxPixelValue;
    fscanf(lennaPGM, "%s", lineOne);
    fscanf(lennaPGM, "%d %d\n %d\n", &dim1, &dim2,&maxPixelValue);
    *width = dim1;
    *height = dim2;
//    printf("%s\n", lineOne);
//    printf("%d\n%d\n%d", dim1, dim2, maxPixelValue);

    /** Allocating memory for 2D array of PixelGray */
    PixelGray** pixels = malloc(dim2 * sizeof(PixelGray*));
    if (pixels == NULL) {
        perror("Error: Unable to allocate memory for rows");
        return NULL;
    }
    for (int i = 0; i < dim2; i++) {
        pixels[i] = malloc(dim1 * sizeof(PixelGray));
        if (pixels[i] == NULL) {
            printf("Error: Unable to allocate memory for columns in row %d", i);
            return NULL;
        }
    }


    /** Reading the rest of the file and storing the pixel values in the 2D array */
    for (int i = 0; i < dim2; i++) {
        for (int j = 0; j < dim1; j++) {
            fread(&pixels[i][j], 1, 1, lennaPGM);
//            printf("%u ", (unsigned int)pixels[i][j].value);
        }
//        printf("\n");
    }

    /** Closing the file and returning */
    fclose(lennaPGM);
    return pixels;
}

// Function to write a 2D matrix as a PGM image
void writePGM(const char* filename, PixelGray** matrix, int* width, int* height){
    /** Open the file to write */
    FILE* output = fopen(filename, "wb");
    if (output == NULL) {
        perror("Error: File failed to open.");
        return;
    }

    /** Writing PGM header */
    fprintf(output, "P5\n%d %d\n255\n", *width, *height);

    /** Writing each column to file individually */
    for (int i = 0; i < *height; i++) {
        for (int j = 0; j < *width; j++) {
            fwrite(&matrix[i][j], sizeof(PixelGray), 1, output);
//            printf("%u ", (unsigned int)matrix[i][j].value);
        }
//        printf("\n"); // Print a new line after each row of pixels
    }

    /** Closing the file */
    fclose(output);
//    printf("File saved: %s\n", filename);
}


// Function to threshold the image matrix
PixelGray** threshold(PixelGray** matrix, int* width, int* height){
    /** Allocating memory for 2D array of PixelGray */
    PixelGray** matrix_threshold = malloc(*height * sizeof(PixelGray*));
    if (matrix_threshold == NULL) {
        perror("Error: Unable to allocate memory for rows");
        return NULL;
    }
    for (int i = 0; i < *height; i++) {
        matrix_threshold[i] = malloc(*width * sizeof(PixelGray));
        if (matrix_threshold[i] == NULL) {
            printf("Error: Unable to allocate memory for columns in row %d", i);
            return NULL;
        }
    }

    /** Changing values in array based on threshold */
    for (int i = 0; i < *width; i++) {
        for (int j = 0; j < *height; j++) {
            if(matrix[i][j].value > 80){
                matrix_threshold[i][j].value = 255;
            }
            else{
                matrix_threshold[i][j].value = 0;
            }
        }
    }
    return matrix_threshold;
}

// Function to rotate the image matrix
PixelGray** rotate(PixelGray** matrix, int* width, int* height){
    /** Allocating memory for 2D array of PixelGray */
    PixelGray** matrix_rotate = malloc(*height * sizeof(PixelGray*));
    if (matrix_rotate == NULL) {
        perror("Error: Unable to allocate memory for rows");
        return NULL;
    }
    for (int i = 0; i < *height; i++) {
        matrix_rotate[i] = malloc(*width * sizeof(PixelGray));
        if (matrix_rotate[i] == NULL) {
            printf("Error: Unable to allocate memory for columns in row %d", i);
            return NULL;
        }
    }

    /** Rotating 2D array by transposing it -- and then storing inside new 2D array */
    for (int i = 0; i < *width; i++) {
        for (int j = 0; j < *height; j++) {
            matrix_rotate[i][j].value = matrix[j][i].value;
        }
    }
    return matrix_rotate;
}


//main function - DO NOT MODIFY
int main() {
    int width, height;  // variable to hold width and height. Use reference in other functions

    PixelGray** image_original = readPGM("lenna.pgm", &width, &height);
    // Now you have the grayscale image data in the 'image_original' 2D array

    // Access pixel data using image[row][col].value
    // For example, to access the pixel at row=2, col=3:
    // unsigned char pixel_value = image[2][3].value;

    // Create a new 2D array 'image_thresh' to store the threshold image
    PixelGray** image_thresh = threshold(image_original, &width, &height);
    //write the image data as "threshold.pgm"
    writePGM("threshold.pgm", image_thresh, &width, &height);

    // Create a new 2D array 'image_rotate' to store the rotated image
    PixelGray** image_rotate = rotate(image_original, &width, &height);
    //write the image data as "rotate.pgm"
    writePGM("rotate.pgm", image_rotate, &width, &height);

    image_rotate = rotate(image_rotate, &width, &height);
    //write the image data as "rotate_again.pgm"
    writePGM("rotate_again.pgm", image_rotate, &width, &height);

    // Free the allocated memory when you're done
    for (int i = 0; i < height; ++i) {
        free(image_original[i]);
        free(image_thresh[i]);
        free(image_rotate[i]);
    }
    free(image_original);
    free(image_thresh);
    free(image_rotate);
    return 0;
}