../02/sin 10000 3528 88200 > a.raw
../02/read_data2 a.raw > a.dat
./downsample 10 < a.raw > b.raw
../02/read_data2 b.raw > b.dat
