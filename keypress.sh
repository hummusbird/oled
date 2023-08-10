tail -f /dev/ttyUSB0 &
xinput test-xi2 --root 3 | gawk '/RawKeyRelease/ {getline; getline; getline; print $2; fflush()}' | while read -r key;
do 
  echo "$key" >> /dev/ttyUSB0;
done
