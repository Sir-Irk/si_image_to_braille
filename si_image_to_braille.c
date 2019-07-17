/* LICENSE AT END OF FILE */
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

    if(v) {
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
    return ((c >> 0) & 0xFFu) + ((c >> 8) & 0xFFu) + ((c >> 16) & 0xFFu);
}

void flatten_alpha(u32 *pixels, i32 count, u32 threshold)
{
    for(i32 i = 0; i < count; ++i) {
        if((pixels[i] >> 24) < threshold) {
            pixels[i] = 0xFFFFFFFFu;
        }
    }
}

void invert_colors(u32 *pixels, i32 count) 
{
    for (i32 i = 0; i < count; ++i) {
        pixels[i] = (0xFFFFFFu - pixels[i]) | (pixels[i] & 0xFF000000u);
    }
}

i32 clamp(i32 val, i32 min, i32 max)
{
    return max(min(val, max), min);
}

i32 nearest_multiple(i32 val, i32 m)
{
    if(m == 0) return val;
    i32 remainder = val%m;
    if(remainder == 0) return val;
    return val + m - remainder;
}

int main(int argc, char **argv)
{
    //TODO: better handling of command line args such as order independence
    //      and input validation
    
    if(argc < 2) {
        printf("Error: need a file name\n"); 
        printf("Usage: [filename] [columns] [invert] [spaces] [color threshold] [alpha threshold] [weight]\n"); 
        return EXIT_FAILURE;
    }

    i32 inWidth, inHeight, comp;
    u8 *pixels = stbi_load(argv[1], &inWidth, &inHeight, &comp, 4);
    if(!pixels) {
        printf("failed to load image: %s\n", argv[1]);
        return EXIT_FAILURE;
    }

    r32 aspectRatio = inHeight/(r32)inWidth;

    //NOTE: Clamping width to an arbitrary range for now
    u32 width = (argc > 2) ? atoi(argv[2])*2 : 60;
    width = nearest_multiple(clamp(width, 2, 4096), 2);
    i32 height = nearest_multiple((i32)(width*aspectRatio), 4);

    u8 *resizedPixels = calloc(width*height, sizeof(u32));
    assert(resizedPixels);

    if(!stbir_resize_uint8(pixels, inWidth, inHeight, 0, resizedPixels, width, height, 0, 4)) {
        //TODO: perhaps better error handling
        printf("failed to resize image\n");
        free(pixels);
        free(resizedPixels);
        return EXIT_FAILURE;
    }

    b32 useSpaces          = (argc > 4) ? atoi(argv[4]) : 0;
    u32 intensityThreshold = (argc > 5) ? clamp(atoi(argv[5]), 0, 255) : 128;
    u32 alphaThreshold     = (argc > 6) ? clamp(atoi(argv[6]), 0, 255) : 64;
    u32 weight             = (argc > 7) ? clamp(atoi(argv[7]), 0, 255) : 3;

    flatten_alpha((u32 *)resizedPixels, width*height, alphaThreshold);

    if(argc > 3 && atoi(argv[3])) {
        invert_colors((u32 *)resizedPixels, width*height);
    }

    //NOTE: 1 extra column for newline char
    i32 outputCount = (height/4)*(width/2)+(height/4)+1;
    wchar_t *output = calloc(outputCount, sizeof(wchar_t));
    assert(output);

    printf("output character count: %d\n", outputCount);

    u32 *p32 = (u32 *)resizedPixels;
    i32 outputIndex = 0;

    for(i32 outerY = 0; outerY < height; outerY += 4) { 
        for(i32 outerX = 0; outerX < width; outerX += 2) { 
            u8 blockVal  = 0;
            i32 blockIdx = 0;
            //TODO: see if this can be done row-major without much hassle
            for(i32 x = 0; x < 2; ++x) {
                for(i32 y = 0; y < 4; ++y) {
                    i32 idx = ((outerY+y)*width) + outerX+x;
                    u32 avg = rgb_sum(p32[idx])/weight;
                    if(avg < intensityThreshold) {
                        blockVal |= (1 << blockIdx);
                    }
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
/*
------------------------------------------------------------------------------
This software is available under 2 licenses -- choose whichever you prefer.
------------------------------------------------------------------------------
ALTERNATIVE A - MIT License
Copyright (c) 2017 Sean Barrett
Permission is hereby granted, free of charge, to any person obtaining a copy of 
this software and associated documentation files (the "Software"), to deal in 
the Software without restriction, including without limitation the rights to 
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies 
of the Software, and to permit persons to whom the Software is furnished to do 
so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all 
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, 
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
SOFTWARE.
