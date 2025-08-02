/**
 * \file image.c
 *
 * \brief Implementação das funções de manipulação da imagem.
 *
 * \author
 * Petrucio Ricardo Tavares de Medeiros \n
 * Universidade Federal Rural do Semi-Árido \n
 * Departamento de Engenharias e Tecnologia \n
 * petrucio at ufersa (dot) edu (dot) br
 *
 * \version 1.0
 * \date May 2025
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "image.h"

unsigned char image[HEIGHT][WIDTH][3];

void set_pixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) {
  if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT) {
    image[y][x][0] = r;
    image[y][x][1] = g;
    image[y][x][2] = b;
  }
}

void draw_point( int x0, int y0 ){
  //
  // Descomente essa linha quando implementar a função rotate
  //
  //rotate( &x0, &y0, -10.0 );
  set_pixel(x0, y0, 255, 255, 255 );
}

void clr(){
  for(int i = 0; i < WIDTH; i++)
    for(int j = 0; j < HEIGHT; j++)
      for(int c = 0; c < 3; c++)
	image[i][j][c] = 0;
}

void draw_line(int x0, int y0, int x1, int y1)
{
    for (float t = 0.0; t < 1.0; t = t + 0.0001)
        set_pixel((int)x0 + (x1 - x0) * t, (int)y0 + (y1 - y0) * t, 55, 255, 100);
}


void resizing( float v0x, float v0y, float v1x, float v1y ){
  int x0 = (int)((v0x + 1.0f) * WIDTH / 2.0f);
  int y0 = (int)((1.0f - v0y) * HEIGHT / 2.0f);
  int x1 = (int)((v1x + 1.0f) * WIDTH / 2.0f);
  int y1 = (int)((1.0f - v1y) * HEIGHT / 2.0f);
  
  draw_point( x0, y0 );
  draw_point( x1, y1 );

  //
  // Descomente essa linha quando implementar a funcao draw_line
  //
  draw_line(x0, y0, x1, y1);                                                                                                                                    
}

void save(){
  printf("P3\n %d \t %d\n 255\n", WIDTH, HEIGHT);
  for(int i = 0; i < WIDTH; i++){
    for(int j = 0; j < HEIGHT; j++){
      for(int c = 0; c < 3; c++){
	printf("%d \t", image[i][j][c]);
      }
      printf("\n");
    }
  }
}



// Nova função para salvar a imagem em um arquivo específico
void save_to_file(const char* filename) {
    FILE* fp = fopen(filename, "w");
    if (!fp) {
        printf("Nao foi possivel abrir o arquivo para escrita");
        exit(1);
    }

    fprintf(fp, "P3\n%d %d\n255\n", WIDTH, HEIGHT);

   
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            fprintf(fp, "%d %d %d ", image[i][j][0], image[i][j][1], image[i][j][2]);
        }
        fprintf(fp, "\n");
    }

    fclose(fp);
}