/**
 * \file wireframe.c
 *
 * \brief Implementação do arquivo principal de renderização do modelo 3D.
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

#include "image.h"
#include "model.h"

int main()
{
    Vertex vertices[MAX_VERTICES];
    Face faces[MAX_FACES];
    int vcount, fcount;

    clr();

    // Lê o arquivo OBJ enviado
    if (!load_obj("wolf.obj", vertices, &vcount, faces, &fcount))
    {
        return 1;
    }

    Camera cam = {
        .position = {2, 0, 4},
        .target = {0, 0, 0},
        .up = {0, 1, 0},
    };

    Vertex P1 = {100, 100, 0};
    Vertex P2 = {400, 400, 0};
    Vertex T1 = {200, 0, 0};
    Vertex T2 = {0, -200, 0};

    apply_camera(vertices, vcount, cam);

    // Renderiza as faces no framebuffer
    // render_faces(vertices, faces, vcount, fcount);

    for (float t = 0.0; t < 1.0; t += 0.001)
    {
        Vertex point3d = hermite(P1, P2, T1, T2, t);
        draw_point(point3d.x, point3d.y);
    }
    save();

    return 0;
}
