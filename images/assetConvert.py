from PIL import Image
import os

f = open("src\\assets.h","w+")

f.write("#ifndef ASSET_H\r#define ASSET_H\r\r")

f.write("//Begin tileset dump...\r")
tileSize = 8

for filename in os.listdir("images\\tilesets"): #each image in the tileset folder

  f.write("//  "+filename+"\r")                             #filename comment
  f.write("PROGMEM const uint8_t "+filename[:-4]+"[] = {")  #variable declaration
  #(variable name is filename minus the extension)
  f.write("\r  "+str(tileSize)+","+str(tileSize)+",\r")

  image = Image.open("images\\tilesets\\"+filename, "r") #open the bmp image file
  pix_val = list(image.getdata())                   #list of pixels (zero or 255)

  # for v in pix_val:
  #   print v


  x = 0
  startX = 0
  # read each column of tiles
  while (startX < image.width):
    startY = 0
    while (startY < image.height):
      f.write("  ")
      #########################################################
      x = startX
      # this does a single tile
      while (x < (startX+tileSize)) :
        # read a column of pixels
        y = startY+tileSize
        currchar = 0
        while (y > (startY)) :
          y = y-1
          currchar = currchar << 1
          if ( pix_val[(y*image.width)+x][0] != 0 ):
            currchar = currchar|1
        f.write(str(hex(currchar))+",")
        x = x+1
      #######################################################
      startY = startY+tileSize
      f.write("\r")
    startX = x

  f.write("};")

f.write("\r\r#endif")
f.close()