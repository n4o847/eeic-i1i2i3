sox doremi.wav -t raw -b 16 -c 1 -e s -r 44100 - | ./downsample 5 | play -t raw -b 16 -c 1 -e s -r 8820 -
