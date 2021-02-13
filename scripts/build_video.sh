# Build MP4 from PNG images with frame rate 0.5
ffmpeg -framerate 0.5 -i ../assets/screenshots/%d.png ../assets/output.mp4
