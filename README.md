# si_image_to_braille
### Converts an image to braille characters(mainly for spamming in Twitch chat)

NOTE: I still need to do more testing and tweaking to get better results. This is just the initial version I'm saving.
Currently is only usable from the command line.

Usage: [filename] [columns] [spaces] [color threshold] [alpha threshold] [red weight] [blue weight] [green weight] [average weight]

Blank spaces currently do not use the blank braille character due to it messing up the formatting. This may only be font specific but it messes up the spacing of the other characters due to the blank character being a different width than the other braille characters. I may find a work-around for this later. Note that Twtich chat does not use newline/carraige return characters so in order to get proper formatting you need to output with the [spaces] arg set(1 to enable). Also Twitch chat by default is 30 columns wide

TODO: 
  - [ ] Better command line arg handling  
  - [ ] Desaturation options other than just weighted average 
  - [ ] GUI frontend for easier control of parameters and instant viewing of results
  - [ ] Dithering option
  - [ ] Possibly more downsampling/upsampling options for input image
  
  - and other things as I think of them
  
  Example with a random public domain image
  
  Input:
  
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
