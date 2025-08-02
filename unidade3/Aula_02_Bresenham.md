# Bresenham

Jack Bresenham propôs em 1965, no artigo *Algorithm for Computer Control of a Digital Plotter*, um algoritmo de rasterização de linhas com tipo inteiro. No texto *Algoritmo de Bresenham* contém uma breve explicação sobre o algoritmo.

![Figura 7 - Linhas geradas pelo algoritmo de Bresenham](imagens/img4.png)

## Código

A implementação do algoritmo de Bresenham está disponível no arquivo `bresenhamLines.c`.

```c
/** 
 * \file bresenhamLines.c 
 * 
 * \brief Implementação do algoritmo bresenham para linhas. 
 * 
 * \author 
 * Petrucio Ricardo Tavares de Medeiros \n 
 * Universidade Federal Rural do Semi-Árido \n 
 * Departamento de Engenharias e Tecnologia \n 
 * petrucio at ufersa (ponto) edu (ponto) br 
 * 
 * \versão 1.0 
 * \data abril de 2025 
 */

#include <stdio.h> 
#include <stdlib.h>  // abs

#define largura 200 
#define altura 200

unsigned char imagem[altura][largura][3];

// Função para preencher um pixel na imagem
void putPixel(int x, int y, unsigned char r, unsigned char g, unsigned char b) { 
  if ((x >= 0) && (x <= largura) && (y >= 0) && (y <= altura)) { 
    imagem[x][y][0] = r; 
    imagem[x][y][1] = g; 
    imagem[x][y][2] = b; 
  } 
}

// Função para limpar a imagem
void clearImage() { 
  for (int y = 0; y < altura; y++) 
    for (int x = 0; x < largura; x++) 
      putPixel(x, y, 255, 255, 255); 
}

// Função para salvar imagem no formato PPM
void saveImage() { 
  // Configurando o cabeçalho do formato PPM 
  printf("P3\n%d\t%d\n255\n", largura, altura);

  for (int y = 0; y < altura; y++) { 
    for (int x = 0; x < largura; x++) { 
      for (int c = 0; c < 3; c++) { 
        printf("%d\t", imagem[x][y][c]); 
      } 
      printf("\n"); 
    } 
  } 
}

// Algoritmo Bresenham (1º quadrante)
void drawBresenhamLinesIncomplete(int x0, int y0, int x1, int y1) {
  int dx = x1 - x0; 
  int dy = y1 - y0;
  int D = (2 * dy) - dx;
  int x = x0; 
  int y = y0;

  putPixel(x, y, 255, 0, 0);

  while (x < x1) { 
    x = x + 1; 
    if (D < 0) { 
      D = D + (2 * dy); 
    } else { 
      y = y + 1; 
      D = D + (2 * (dy - dx)); 
    } 
    putPixel(x, y, 255, 0, 0); 
  }
}

// Algoritmo Bresenham (todos os quadrantes)
void drawBresenhamLines(int x0, int y0, int x1, int y1) { 
  int dx = abs(x1 - x0); 
  int dy = abs(y1 - y0);
  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;
  int erro = dx - dy;

  while (1) { 
    putPixel(x0, y0, 250, 0, 0);
    if (x0 == x1 && y0 == y1) break;

    int erro2 = 2 * erro;

    if (erro2 > -dy) {
      erro -= dy; 
      x0 += sx; 
    }

    if (erro2 < dx) {
      erro += dx; 
      y0 += sy; 
    } 
  } 
}

int main() {
  clearImage();
  //drawBresenhamLinesIncomplete(0, 0, 200, 200);

  drawBresenhamLines(20, 20, 80, 20); 
  drawBresenhamLines(20, 20, 20, 80); 
  drawBresenhamLines(20, 80, 80, 80); 
  drawBresenhamLines(80, 20, 80, 80);

  saveImage();

  return 0; 
}
```

## Descrição do programa

Neste momento, estaríamos repetindo todo o processo descrito anteriormente. Para evitar redundância, descreveremos apenas o conteúdo que adicionamos ao arquivo. Sendo assim, falaremos sobre a função `drawBresenhamLinesIncomplete`. Esta função está descrita no texto *Algoritmo de Bresenham*.

```c
void drawBresenhamLinesIncomplete(int x0, int y0, int x1, int y1) {
  int dx = x1 - x0; 
  int dy = y1 - y0;
  int D = (2 * dy) - dx;
  int x = x0; 
  int y = y0;

  putPixel(x, y, 255, 0, 0);

  while (x < x1) { 
    x = x + 1; 
    if (D < 0) { 
      D = D + (2 * dy); 
    } else { 
      y = y + 1; 
      D = D + (2 * (dy - dx)); 
    } 
    putPixel(x, y, 255, 0, 0); 
  }
}
```

Na função `drawBresenhamLines`, incluímos todos os quadrantes como sugerido no artigo supracitado.

```c
void drawBresenhamLines(int x0, int y0, int x1, int y1) { 
  int dx = abs(x1 - x0); 
  int dy = abs(y1 - y0);
  int sx = (x0 < x1) ? 1 : -1;
  int sy = (y0 < y1) ? 1 : -1;
  int erro = dx - dy;

  while (1) { 
    putPixel(x0, y0, 250, 0, 0);
    if (x0 == x1 && y0 == y1) break;

    int erro2 = 2 * erro;

    if (erro2 > -dy) {
      erro -= dy; 
      x0 += sx; 
    }

    if (erro2 < dx) {
      erro += dx; 
      y0 += sy; 
    } 
  } 
}
```