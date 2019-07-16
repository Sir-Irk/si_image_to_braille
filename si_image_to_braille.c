#include <stdio.h>
#include <assert.h>
#include <fcntl.h>
#include "types.h"
#include <uchar.h>
#include <locale.h>
#include <io.h>
#include <windows.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_RESIZE_IMPLEMENTATION
#include "stb_image_resize.h"

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

inline u32 rgb_sum(u32 c, u32 rw, u32 gw, u32 bw)
{
	return (((c/rw) >> 0) & 0xFF) + (((c/gw) >> 8) & 0xFF) + (((c/bw) >> 16) & 0xFF);
}

void flatten_alpha(u32 *pixels, i32 count, u32 threshold)
{
	for(i32 i = 0; i < count; ++i) {
		if((pixels[i] >> 24) < threshold) {
			pixels[i] = 0xFFFFFF00;
		}
	}
}

int main(int argc, char **argv)
{
	if(argc < 2)
	{
		printf("Error: need a file name\n"); 
		printf("Usage: [filename] [color threshold] [alpha threshold] [red weight] [blue weight] [green weight] [weight]\n"); 
		return 1;
	}

	i32 inWidth, inHeight, comp;
	u8 *pixels = stbi_load(argv[1], &inWidth, &inHeight, &comp, 4);
	assert(pixels);

	u32 intensityThreshold = (argc > 2) ? atoi(argv[2]) : 128;
	u32 alphaThreshold = (argc > 3) ? atoi(argv[3]) : 64;
	r32 aspectRatio = inHeight/(r32)inWidth;

	printf("wtf\n");
	u32 width = 60;
	u32 height = (u32)(width*aspectRatio);
	printf("w:%d, h: %d\n", width, height);
	u8 *resizedPixels = calloc(width*height, sizeof(u32));
	if(!stbir_resize_uint8(pixels, inWidth, inHeight, 0, resizedPixels, width, height, 0, 4))
	{
		printf("failed to resize image\n");
		goto exit;
	}
	printf("wtf\n");
	flatten_alpha((u32 *)resizedPixels, width*height, alphaThreshold);

	//NOTE: 1 extra column for newline char
	i32 outputCount = (ceil(height/4)*ceil(width/2))+ceil(height/4)+1;
	printf("output count: %d\n", outputCount);
	wchar_t *output = calloc(outputCount, sizeof(wchar_t));
	assert(output);

	u32 rw = (argc > 4) ? atoi(argv[4]) : 1;
	u32 gw = (argc > 5) ? atoi(argv[5]) : 1;
	u32 bw = (argc > 6) ? atoi(argv[6]) : 1;
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
					u32 avg = rgb_sum(p32[idx], rw, gw, bw)/weight;
					if(avg > intensityThreshold) blockVal |= (1 << blockIdx);
					++blockIdx;
				}
			}
			output[outputIndex++] = to_braille(blockVal);
			assert(outputIndex < outputCount);
		}
		output[outputIndex++] = '\r\0\n\0';
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
