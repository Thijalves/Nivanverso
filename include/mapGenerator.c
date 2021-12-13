#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t  BYTE;
typedef uint32_t DWORD;
typedef int32_t  LONG;
typedef uint16_t WORD;

#pragma pack(1)
typedef struct{
    WORD   bfType;
    DWORD  bfSize;
    WORD   bfReserved1;
    WORD   bfReserved2;
    DWORD  bfOffBits;
}BITMAPFILEHEADER;

#pragma pack(1)
typedef struct{
    DWORD  biSize;
    LONG   biWidth;
    LONG   biHeight;
    WORD   biPlanes;
    WORD   biBitCount;
    DWORD  biCompression;
    DWORD  biSizeImage;
    LONG   biXPelsPerMeter;
    LONG   biYPelsPerMeter;
    DWORD  biClrUsed;
    DWORD  biClrImportant;
}BITMAPINFOHEADER;

#pragma pack(1)
typedef struct{
    BYTE  rgbBlue;
    BYTE  rgbGreen;
    BYTE  rgbRed;
}RGBTRIPLE;


void generateMap(){
    //utilização: ./main fase.bmp fase.txt


    FILE *inputFile = fopen("./maps/fase1.bmp", "r");

    if(inputFile == NULL){
        printf("Erro ao abrir o arquivo\n");
        exit(1);
    }

    FILE *outputFile = fopen("./data/faseTeste.txt", "w");

    if(outputFile == NULL){
        printf("Erro ao criar o arquivo de saida\n");
        exit(1);
    }

    //faz a leitura do cabeçalho de tipo "BITMAPFILEHEADER"
    BITMAPFILEHEADER fileHeader;
    fread(&fileHeader, sizeof(BITMAPFILEHEADER), 1, inputFile);
    
    //faz a leitura do cabeçalho de tipo "BITMAPINFOHEADER"
    BITMAPINFOHEADER infoHeader;
    fread(&infoHeader, sizeof(BITMAPINFOHEADER), 1, inputFile);

    int width = abs(infoHeader.biWidth);
    int height = infoHeader.biHeight;

    RGBTRIPLE **image;

    image = (RGBTRIPLE **)malloc(height * sizeof(*image));

    for(int i = 0; i < height; i++){
        image[i] = (RGBTRIPLE *)malloc(width * sizeof(image));
    }

    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    for(int i = 0; i < height; i++){
        fread(image[i], sizeof(RGBTRIPLE), width, inputFile);
        fseek(inputFile, padding, SEEK_CUR);
    }

    for(int i = 0; i < height/2; i++){
        for(int j = 0; j < width; j++){
            RGBTRIPLE tmp;
            tmp = image[i][j];
            image[i][j] = image[height - 1 - i][j];
            image[height - 1 - i][j] = tmp;
        }
    }

    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int color = image[i][j].rgbBlue + (image[i][j].rgbGreen << 8) + (image[i][j].rgbRed << 16);
            switch(color){
                case 0x8F563B: //marrom
                    fprintf(outputFile, "x");
                    break;
                case 0x000000: //preto
                    fprintf(outputFile, "#");
                    break;
                case 0x5FCDE4: //azul
                    fprintf(outputFile, "0");
                    break;
                case 0xE80000: //vermelho
                    fprintf(outputFile, "@");
                    break;
                case 0x6abe30: //verde
                    fprintf(outputFile, "^");
                    break;
                default:
                    // printf("RGB da cor [%d][%d]: %d %d %d\n", i, j, image[i][j].rgbRed, image[i][j].rgbGreen, image[i][j].rgbBlue);
                    fprintf(outputFile, ",");
                    printf("Cor nao registrada!\n");
                    break;
            }
        }
    }

    fprintf(outputFile, "\nwidth: %d\n", infoHeader.biWidth);

    for(int i = 0; i < height; i++){
        free(image[i]);
    }
    free(image);

}