/**
 * \file model.h
 *
 * \brief Header com protótipos de funções para manipulação de modelo 3D.
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

#ifndef MODEL_H
#define MODEL_H

#define MAX_VERTICES 50000
#define MAX_FACES 50000
#define MAX_FACE_VERTS 32

typedef struct {
  float x, y, z;
} Vertex;

typedef struct {
  int verts[MAX_FACE_VERTS];
  int n;
} Face;

typedef struct model
{
  Vertex position;
  Vertex target;
  Vertex up;
  /* data */
}Camera;

// static Vertex vec_sub(Vertex a, Vertex b);

int load_obj(const char *filename, Vertex *vertices, int *vcount, Face *faces, int *fcount);

void render_faces(Vertex *vertices, Face *faces, int vcount, int fcount);

void apply_camera(Vertex *vertices, int vcount, Camera camera);

Vertex perspective(Vertex v);

Vertex hermite(Vertex P1, Vertex P2, Vertex T1, Vertex T2, float t);
#endif
