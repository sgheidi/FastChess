ffmpeg \
  -i output.mp4 \
  -r 15 \
  -vf scale=512:-1 \
  out.gif
