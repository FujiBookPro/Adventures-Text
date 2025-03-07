#include "raylib.h"
#include "raymath.h"
#include <stdlib.h>

#define WIDTH 1920
#define HEIGHT 1080

struct BezierCurveSegment {
    Vector2 anchor_a;
    Vector2 control;
    Vector2 anchor_b;
};

struct PointList {
    int n_points;
    Vector2* points;
};

Vector2 linear_interpolate(Vector2 a, Vector2 b, float t) {
    Vector2 output = Vector2Scale(a, 1 - t);
    output = Vector2Add(output, Vector2Scale(b, t));
    return output;
}

Vector2 interpolate_curve(struct BezierCurveSegment segment, float t) {
    Vector2 between_a = linear_interpolate(segment.anchor_a, segment.control, t);
    Vector2 between_b = linear_interpolate(segment.control, segment.anchor_b, t);

    return linear_interpolate(between_a, between_b, t);
}

struct PointList build_point_list(struct BezierCurveSegment segment, int n_points) {
    struct PointList list = {n_points, malloc(sizeof(Vector2) * n_points)};

    for (int i = 0; i < n_points; i++) {
        float t = (float)(i + 1) / n_points;
        list.points[i] = interpolate_curve(segment, t);
    }

    return list;
}

int main(void) {
    InitWindow(WIDTH, HEIGHT, "text");

    struct BezierCurveSegment segment = {{200, 200}, {200, 800}, {800, 600}};
    struct PointList line = build_point_list(segment, 20);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // DrawLineStrip(line.points, line.n_points, BLUE);
        DrawTriangleFan(line.points, line.n_points, BLUE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
