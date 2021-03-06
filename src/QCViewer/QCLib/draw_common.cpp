/*--------------------------------------------------------------------
QCViewer
Copyright (C) 2011  Alex Parent and The University of Waterloo,
Institute for Quantum Computing, Quantum Circuits Group

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

See also 'ADDITIONAL TERMS' at the end of the included LICENSE file.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.

QCViewer is a trademark of the of the The University of Waterloo,
Institute for Quantum Computing, Quantum Circuits Group

Authors: Alex Parent, Jacob Parker
---------------------------------------------------------------------*/


#include "draw_common.h"
#include "draw_constants.h"
#include <cmath>
#ifndef M_PI
#define M_PI 3.141592
#endif

using namespace std;

PangoLayout* create_text_layout(cairo_t *cr, string label, double &width, double &height)
{
    PangoLayout *layout = pango_cairo_create_layout (cr);
    PangoFontDescription *desc = pango_font_description_from_string ("LM Roman 12, Roman, Serif bold 18");
    pango_layout_set_font_description (layout, desc);
    pango_font_description_free (desc);
    pango_layout_set_markup (layout, label.c_str(), label.length());
    int w,h;
    pango_layout_get_size (layout, &w, &h);

    width = ((double)w/PANGO_SCALE);
    height = ((double)h/PANGO_SCALE);
    return layout;
}


void drawDot (cairo_t *cr, double xc, double yc, double radius, bool negative)
{
    if (negative) {
        cairo_set_source_rgb (cr, 1, 1, 1);
        cairo_arc (cr, xc, yc, radius, 0, 2*M_PI);
        cairo_fill (cr);
        cairo_set_source_rgb (cr, 0, 0, 0);
        cairo_set_line_width(cr, thickness);
        cairo_arc (cr, xc, yc, radius, 0, 2*M_PI);
        cairo_stroke (cr);
    } else {
        cairo_set_source_rgb (cr, 0, 0, 0);
        cairo_arc (cr, xc, yc, radius, 0, 2*M_PI);
        cairo_fill (cr);
    }
}

double wireToY (uint32_t x)
{
    return yoffset+(x+1)*wireDist;
}

gateRect combine_gateRect (const gateRect &a, const gateRect &b)
{
    gateRect c;
    c.x0 = min(a.x0, b.x0);
    c.y0 = min(a.y0, b.y0);
    c.width =  max (a.x0-c.x0 + a.width,  b.x0 - c.x0 + b.width);
    c.height = max (a.y0-c.y0 + a.height, b.y0 - c.y0 + b.height);
    return c;
}

void drawWire (cairo_t *cr, double x1, double y1, double x2, double y2)
{
    cairo_set_line_width (cr, thickness);
    cairo_set_source_rgb (cr, 0, 0, 0);
    cairo_move_to (cr, x1, y1);
    cairo_line_to (cr, x2, y2);
    cairo_stroke (cr);
}

void drawRect (cairo_t *cr, gateRect r, Colour outline, Colour fill)
{
    cairo_set_source_rgba (cr, fill.r, fill.g, fill.b, fill.a);
    cairo_rectangle (cr, r.x0, r.y0, r.width, r.height);
    cairo_fill (cr);
    cairo_set_source_rgba (cr, outline.r, outline.g, outline.b, outline.a);
    cairo_rectangle (cr, r.x0, r.y0, r.width, r.height);
    cairo_stroke (cr);
}
