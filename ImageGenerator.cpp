#include "ImageGenerator.h"

QImage getSomeImage() {
    const int w = 500;
    const int h = 500;

    QImage image(w, h, QImage::Format_ARGB32);

    cairo_surface_t *surface = cairo_image_surface_create_for_data(image.bits(), CAIRO_FORMAT_ARGB32, w, h, image.bytesPerLine());

    cairo_t *cr = cairo_create(surface);

    cairo_set_source_rgb(cr, 1, 1, 1);
    cairo_paint(cr);
    cairo_set_source_rgb(cr, 0, 0, 0);

    cairo_move_to(cr, 0, 0);
    for (int i = 0; i <= w; i++) {
        double x = i;
        double y = 0.5 * h * (0.5 + 0.5 * sin(x / (M_PI * (w / 100))));
        if (i == 0) {
            cairo_move_to(cr, 0, y);
        } else {
            cairo_line_to(cr, x, y);

        }
    }

    cairo_stroke(cr);

    cairo_image_surface_get_data(surface);

    cairo_surface_write_to_png(surface, "example.png");

    cairo_destroy(cr);

    cairo_surface_destroy(surface);

    return image;
}