#include <fudge.h>
#include <gfx/gfx.h>

struct pcx_header
{

    char identifier;
    char version;
    char encoding;
    char bpp;
    short xstart;
    short ystart;
    short xend;
    short yend;
    short xdpi;
    short ydpi;
    char palette[48];
    char reserved1[1];
    char nplanes;
    short bpl;
    short palettetype;
    short xscreen;
    short yscreen;
    char reserved2[54];

};

static struct gfx_backend backend;
static struct gfx_surface rootSurface;
static struct pcx_header header;

static char read_byte(unsigned int *offset)
{

    char byte;

    call_read(FUDGE_IN, *offset, 1, &byte);

    *offset = *offset + 1;

    return byte;

}

static void print_data()
{

    char buffer[0x200];
    unsigned int buffersize = 0x200;
    unsigned int offset = 0;
    unsigned int index = 0;
    char byte;
    unsigned int runcount;
    unsigned int total;
    char runvalue;

/*
    unsigned int width = header.xend - header.xstart + 1;
    unsigned int height = header.yend - header.ystart + 1;
    unsigned int scanline = header.nplanes * header.bpl;
    unsigned int padding = ((header.bpl * header.nplanes) * (8 / header.bpp)) - ((header.xend - header.xstart) + 1);
*/

    call_open(3, FUDGE_ROOT, 27, "system/video/vga/resolution");
    call_write(3, 0, 9, "320x200x8");
    call_close(3);

    do
    {

        byte = read_byte(&offset);

        if ((byte & 0xC0) == 0xC0)
        {

            runcount = byte & 0x3F;
            runvalue = read_byte(&offset);

        }

        else
        {

            runcount = 1;
            runvalue = byte;

        }

        for (total += runcount; runcount && index < buffersize; runcount--, index++)
            buffer[index] = runvalue;

    } while (index < buffersize);

    call_write(FUDGE_OUT, 0, 0x200, &buffer);

}

void main()
{

    call_read(FUDGE_IN, 0, sizeof (struct pcx_header), &header);
    call_open(FUDGE_OUT, FUDGE_ROOT, 21, "system/video/vga/data");
    gfx_init_backend(&backend, FUDGE_OUT);
    gfx_init_surface(&rootSurface, 320, 200, GFX_RGB8, &backend);
    print_data();

}

