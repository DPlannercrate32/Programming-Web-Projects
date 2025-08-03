from PIL import Image
import random
from bisect import bisect

greyscale = [
            " ",
            "`",
            "-",
            "_",
            ":",
            "&",
            "%",
            "#"
            ]


zonebounds=[36,72,108,144,180,216,252]

select = raw_input("Type the path of the picture file that you want to CONVERT! If the image file is in the same folder as this program then just type its name!\n")
im=Image.open(select)
im=im.resize((150, 100),Image.BILINEAR)
im=im.convert("L") # convert to mono


str=""
for y in range(0,im.size[1]):
    for x in range(0,im.size[0]):
        lum=255-im.getpixel((x,y))
        row=bisect(zonebounds,lum)
        possibles=greyscale[row]
        str=str+possibles[random.randint(0,len(possibles)-1)]
    str=str+"\n"

print str
input()

