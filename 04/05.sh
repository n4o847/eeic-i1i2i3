sox doremi.wav -t raw -c 1 - | ./bandpass 8192 300 3400 | play -t raw -b 16 -c 1 -e s -r 44100 -
