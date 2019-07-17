# si_image_to_braille
### Converts an image to braille characters

NOTE: I still need to do more testing and tweaking to get better results. This is just the initial version I'm saving.
Currently is only usable from the command line.

Usage: [filename] [columns] [invert] [spaces] [color thresh] [alpha thresh] [weight]

<pre>
[filename]     : path to file
[columns]      : (2-4096) number of columns to output in braille characters(note the image will be resized if needed)
[invert]       : (0-1)invert the colors of the input image
[spaces]       : (0-1)uses spaces instead of newline characters at the end of each line(for Twitch chat which ignores newlines)
[color Thresh] : (0-255)The threshold for derterming if a color's intensity counts as a "raised" bump in braille
[alpha Thresh] : (0-255)Used when flattening the alpha channel for images that have transparency to determine filled pixels
[weight]       : used when dividing the sum of rgb values. By default this is 3 which simply gives the average intensity
</pre>

Uses the awesome single-header libraries stb_image.h and stb_image_resize.h by Sean Barrett and co https://github.com/nothings/stb

Blank spaces currently do not use the blank braille character due to it messing up the formatting. This may only be font specific but it messes up the spacing of the other characters due to the blank character being a different width than the other braille characters. I may find a work-around for this later. Note that Twtich chat does not use newline/carraige return characters so in order to get proper formatting you need to output with the [spaces] arg set(1 to enable). Also Twitch chat by default is 30 columns wide

More information about braille patterns https://en.wikipedia.org/wiki/Braille_Patterns

TODO: 
  - [ ] Better command line arg handling  
  - [ ] Cross platform file writing in utf-8(currently uses windows only code)
  - [ ] Get rid of the awfulness that is windows.h
  - [ ] Desaturation options other than just weighted average 
  - [ ] GUI frontend for easier control of parameters and instant viewing of results
  - [ ] Dithering option
  - [ ] Possibly more downsampling/upsampling options for input image
  
  - and other things as I think of them
  
  Example with a random public domain image
  
  Input: "si_image_to_braille.exe pug.jpg 64 0 0 116" on command line
  
  ![](https://imgur.com/dG7Skc3.png) 
  
  Output:
  
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣀⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣴⡆⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠙⣷⣄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢀⣼⡟⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⣀⣀⣀⠄⠄⠄⠄⠸⣿⣦⡀⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢀⣤⣿⣿⡟⠄⠄⠄⢀⣀⣤⣴⣶⣶⡀⠄⠄⡀⠄⠄⠄⠄⠄⠄⠄⢀⣤⠄⠄⣤⣿⣿⣿⣷⡤⠄⠄⠄⢹⣿⣷⣦⣤⣀⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⢀⣤⣾⣿⣿⣟⣿⣿⠁⠄⢀⣠⣾⣿⣿⣿⣿⣿⣿⡀⢀⣿⣀⣀⣤⣴⣶⣶⣦⣿⣿⣷⣴⣿⣿⣿⡿⣿⣿⣿⣶⣤⡀⢻⣿⣿⣿⣿⣷⣦⡀⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⢀⣴⣿⣿⣿⣿⣿⢸⣿⡇⢀⣼⣿⣿⣶⠾⠭⢉⠛⣿⣿⣿⣿⣿⣿⠿⠿⠿⠿⣿⣿⣿⣿⣿⣿⣿⣟⡴⠛⠛⠿⣿⣿⣿⣷⣼⣿⣿⣿⣿⣿⣿⣿⣦⡀⠄⠄⠄⠄
⠄⠄⠄⠄⣴⣿⣿⣿⣿⣿⣿⣿⢸⣿⡇⣾⣿⣿⣟⣁⣀⠄⠄⣀⣌⣿⣿⣿⣿⣧⡤⠄⠐⠒⢺⣿⣿⣿⣿⣿⣿⡟⡄⠄⢠⣤⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣄⠄⠄⠄
⠄⠄⢀⣼⣿⣿⣿⣿⣿⣿⣿⡇⢸⣿⡿⣿⣿⣿⣿⣿⣿⡇⣰⠏⣹⣿⣿⣿⣿⣿⣾⢇⢀⠁⣸⣿⣿⣿⣿⣿⣿⣿⣿⣷⣬⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄
⠄⠄⣿⣿⣿⣿⣿⣿⣿⣿⣿⡇⣿⡿⠄⠹⣿⣿⣿⡿⠟⠉⢡⣾⣿⣿⣿⣿⣿⣿⣅⣼⠿⡂⢿⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠄⠄⠄
⠄⠄⠈⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⡧⠄⠄⠘⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⡟⣏⣛⠄⠇⡞⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠄⠄⣿⣿⣿⣿⣿⣿⣿⣿⠏⠄⠄⠄⠄
⠄⠄⠄⠄⠙⢿⣿⣿⣿⣿⣿⣿⣿⡇⠄⠄⠄⠄⠙⢿⣿⣿⣿⣿⣿⡿⡙⠉⠉⠄⢘⣿⣧⡄⠻⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⢿⡏⠄⠄⠄⢹⣿⣿⣿⣿⡿⠟⠁⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠉⠻⣿⣿⣿⣿⣿⣷⠄⠄⠄⠄⢠⣶⣿⣿⣿⡟⡟⠁⠄⠄⠄⠄⠄⣸⣿⣯⠄⠈⠛⠟⠿⢿⣿⣿⣿⣿⣿⣿⣿⡄⠄⠄⠄⠸⢿⣿⠟⠉⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠈⠛⠿⢿⣿⣿⣆⠄⢀⣴⣿⣿⣿⣿⣿⣿⣇⡆⠄⠄⢀⣾⣿⠿⠛⠛⠛⣿⣾⣦⣔⣽⣿⣿⣿⣿⣿⣿⣿⣷⡄⠄⠄⠄⠄⠙⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠘⠛⠉⠉⠄⠘⢿⣿⣿⣿⣿⣿⣿⡟⠃⣄⣴⣾⣿⣿⣷⣀⣤⣤⣿⣿⣿⣿⣆⣿⣿⣿⣿⣿⣿⣿⣿⠇⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢹⣿⣿⣿⣿⣿⣿⣷⣿⣿⣿⣿⣿⣿⣷⢩⣬⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡟⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠎⢿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⢻⣿⣿⣿⣿⣿⣿⣿⣥⣤⣿⣿⣏⣻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠟⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠉⠛⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠿⠋⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠉⢻⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠟⠁⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠉⠉⠛⠋⠈⠙⠛⠉⠁⠄⠄⠄⠄⠄⠄⢀⣄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠈⠛⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄⠄
