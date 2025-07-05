/**
 * \file model.c
 *
 * \brief Implementação das funções de manipulação do modelo 3D.
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
#include "model.h"

int load_obj(const char *filename, Vertex *vertices, int *vcount, Face *faces,
             int *fcount)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        perror("Erro ao abrir o arquivo");
        return 0;
    }

    char line[512];
    *vcount = 0;
    *fcount = 0;

    while (fgets(line, sizeof(line), file))
    {
        if (strncmp(line, "v ", 2) == 0)
        {
            if (sscanf(line + 2, "%f %f %f", &vertices[*vcount].x,
                       &vertices[*vcount].y, &vertices[*vcount].z) == 3)
            {
                (*vcount)++;
            }
        }
        else if (strncmp(line, "f ", 2) == 0)
        {
            Face face = {.n = 0};
            char *token = strtok(line + 2, " \n");
            while (token && face.n < MAX_FACE_VERTS)
            {
                int index;
                if (sscanf(token, "%d", &index) == 1)
                {
                    face.verts[face.n++] = index;
                }
                token = strtok(NULL, " \n");
            }
            faces[(*fcount)++] = face;
        }
    }

    fclose(file);
    return 1;
}

void render_faces(Vertex *vertices, Face *faces, int vcount, int fcount)
{
    for (int i = 0; i < fcount; i++)
    {
        Face face = faces[i];
        for (int j = 0; j < face.n; j++)
        {
            Vertex v0 = vertices[face.verts[j] - 1];
            Vertex v1 = vertices[face.verts[(j + 1) % face.n] - 1];

            Vertex nv0 = perspective(v0);
            Vertex nv1 = perspective(v1);


            // resizing(v0.x, v0.y, v1.x, v1.y);
            resizing(nv0.x, nv0.y, nv1.x, nv1.y);

        }
    }
}

Vertex perspective(Vertex v)
{
    float p = 2.0;
    Vertex vaux = {0, 0, 0};

    if (v.z > 0)
    {
        vaux.x = (v.x * p) / v.z;
        vaux.y = (v.y * p) / v.z;
        vaux.z =  v.z;
    }

    return vaux;
}


Vertex hermite(Vertex P1, Vertex P2, Vertex T1, Vertex T2, float t){
    float h1 = 2 * t * t * t - 3 * t * t + 1;
    float h2 = -2 * t * t * t + 3 * t * t;
    float h3 = t * t* t - 2 * t * t + t;
    float h4 = t * t* t - t * t;

    Vertex result;
    result.x = h1 * P1.x + h2 * P2.x + h3 * T1.x + h4 * T2.x;
    result.y = h1 * P1.y + h2 * P2.y + h3 * T1.y + h4 * T2.y;
    result.z = h1 * P1.z + h2 * P2.z + h3 * T1.z + h4 * T2.z;

    return result;
}

static Vertex vec_sub(Vertex a, Vertex b)
{
    return (Vertex){a.x - b.x, a.y - b.y, a.z - b.z};
}

// CONFERIR.
static Vertex vec_cross(Vertex a, Vertex b)
{
    return (Vertex){
        a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x};
}

static float vec_dot(Vertex a, Vertex b)
{
    return a.x - b.x + a.y - b.y + a.z - b.z;
}

static Vertex vec_normalize(Vertex v)
{
    float len = sqrtf(v.x * v.x + v.y * v.y + v.z * v.z);
    return (Vertex){v.x / len, v.y / len, v.z / len};
}

void appl_camera(Vertex *vertices, int vcount, Camera camera)
{
    Vertex n = vec_normalize(vec_sub(camera.target, camera.position));
    Vertex u = vec_normalize(vec_cross(camera.up, n));
    Vertex v = vec_cross(n, u);

    for (int i = 0; i < vcount; ++i)
    {
        Vertex p = {
            vertices[i].x - camera.position.x,
            vertices[i].y - camera.position.y,
            vertices[i].z - camera.position.z,
        };

        vertices[i].x = vec_dot(p, u);
        vertices[i].y = vec_dot(p, v);
        vertices[i].z = vec_dot(p, n);
    }
}
