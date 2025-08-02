#include "image.h"
#include "model.h"
#include <string.h> 
#include <stdio.h>

int main()
{
    Vertex original_vertices[MAX_VERTICES];
    Vertex buffer_for_vertices[MAX_VERTICES];
    Face faces[MAX_FACES];
    int vcount, fcount;

    if (!load_obj("wolf.obj", original_vertices, &vcount, faces, &fcount))
    {
        return 1;
    }

    Vertex P1 = {5, 2, 5};
    Vertex P2 = {-5, 2, 5};
    Vertex T1 = {-10, 0, 0};  
    Vertex T2 = {-10, 0, 0}; 


    int num_frames = 30;
    float t = 0.0;

    float increment = 1.0 / (num_frames - 1);
    for (int frame = 0; frame < num_frames; ++frame)
    {

       // memcpy( destino, origem, tamanho );
        memcpy(buffer_for_vertices, original_vertices, sizeof(Vertex) * vcount);
        clr();

        // for (float t = 0.0; t < 1.0; t += 0.001)
    
        Camera cam = {
            .position = hermite(P1, P2, T1, T2, t),
            .target = {0, 0, 0},
            .up = {0, 1, 0},
        };

        apply_camera(buffer_for_vertices, vcount, cam);
        render_faces(buffer_for_vertices, faces, vcount, fcount);

        t += increment;


        char filename[100];
        sprintf(filename, "frames/frame%04d.ppm", frame);
        save_to_file(filename);
    }

    return 0;
}