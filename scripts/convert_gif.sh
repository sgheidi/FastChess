ffmpeg \
  -i ../assets/output.mp4 \
  -r 15 \
  -vf scale=512:-1 \
  ../assets/out.gif
