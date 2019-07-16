#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include <windows.h>
#include "types.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

//TODO: test performance of bit flags vs array
#define bit_is_set(val, bit) (((val) & (1 << (bit))) >> (bit))
u32 to_braille(u8 v)
{
    u32 result = 4;

    if(v != 0)
    {
         result = (bit_is_set(v, 0) << 0)
                + (bit_is_set(v, 1) << 1)
                + (bit_is_set(v, 2) << 2)
                + (bit_is_set(v, 4) << 3)
                + (bit_is_set(v, 5) << 4)
                + (bit_is_set(v, 6) << 5)
                + (bit_is_set(v, 3) << 6)
                + (bit_is_set(v, 7) << 7);
    }

    return 0x2800+result;
}

inline u32 rgb_sum(u32 c)
{
    return ((c >> 0) & 0xFF) + ((c >> 8) & 0xFF) + ((c >> 16) & 0xFF);
}

void flatten_alpha(u32 *pixels, i32 count, u32 threshold)
{
    for(i32 i = 0; i < count; ++i) {
        if((pixels[i] >> 24) < threshold) {
            pixels[i] = 0xFFFFFFFF;
        }
    }
}

void invert_colors(u32 *pixels, i32 count) {
    for (i32 i = 0; i < count; ++i) {
        pixels[i] = (0xFFFFFFu - pixels[i]) | (pixels[i] & 0xFF000000u);
    }
}

int main(int argc, char **argv)
{
    //TODO: better handling of command line args such as order independence
    if(argc < 2)
    {
        printf("Error: need a file name\n"); 
        printf("Usage: [filename] [columns] [invert] [spaces] [color threshold] [alpha threshold] [weight]\n"); 
        return 1;
    }

    i32 inWidth, inHeight, comp;
    u8 *pixels = stbi_load(argv[1], &inWidth, &inHeight, &comp, 4);
    assert(pixels);

    u32 width = (argc > 2) ? atoi(argv[2])*2 : 60;
    //NOTE: Clamping to an arbitrary range for now
    width = min(4096, max(2, width));

    r32 aspectRatio = inHeight/(r32)inWidth;

    u32 height = (u32)(width*aspectRatio);
    u8 *resizedPixels = calloc(width*height, sizeof(u32));
    if(!stbir_resize_uint8(pixels, inWidth, inHeight, 0, resizedPixels, width, height, 0, 4))
    {
        //TODO: perhaps better error handling
        printf("failed to resize image\n");
        goto exit;
    }

    if(argc > 3 && atoi(argv[3])) invert_colors((u32 *)resizedPixels, width*height);

    b32 useSpaces = (argc > 4) ? atoi(argv[4]) : 0;
    u32 intensityThreshold = (argc > 5) ? atoi(argv[5]) : 128;
    u32 alphaThreshold = (argc > 6) ? atoi(argv[6]) : 64;
    flatten_alpha((u32 *)resizedPixels, width*height, alphaThreshold);

    //NOTE: 1 extra column for newline char
    i32 outputCount = (ceil(height/4)*ceil(width/2))+ceil(height/4)+1;
    printf("output character count: %d\n", outputCount);
    wchar_t *output = calloc(outputCount, sizeof(wchar_t));
    assert(output);

    u32 weight = (argc > 7) ? atoi(argv[7]) : 3;

    u32 *p32 = (u32 *)resizedPixels;
    i32 outputIndex = 0;
    for(i32 outerY = 0; outerY < height; outerY += 4) { 
        for(i32 outerX = 0; outerX < width; outerX += 2) { 
            u8 blockVal  = 0;
            i32 blockIdx = 0;
            for(i32 x = 0; x < 2; ++x) {
                for(i32 y = 0; y < 4; ++y) {
                    i32 idx = ((outerY+y)*width) + outerX+x;
                    u32 avg = rgb_sum(p32[idx])/weight;
                    if(avg < intensityThreshold) blockVal |= (1 << blockIdx);
                    ++blockIdx;
                }
            }
            output[outputIndex++] = to_braille(blockVal);
            assert(outputIndex < outputCount);
        }
        output[outputIndex++] = (useSpaces) ? ' \0' : '\r\0\n\0';
    }
    output[outputIndex] = '\0';

    //TODO: cross-platform file write
    FILE *f = fopen("braille_output.txt", "wb");
    if(f) {
        _setmode(_fileno(f), _O_U8TEXT);
        fwprintf(f, L"%lls", output);
        fclose(f);
    }

exit:
    if(pixels) free(pixels);
    if(resizedPixels) free(resizedPixels);
    if(output) free(output);
    return 0;
}
