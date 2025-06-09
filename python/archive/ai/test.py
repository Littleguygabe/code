import numpy as np 
from PIL import Image

image = Image.open('test.png')
greyImage = image.convert("L")

greyImageScaled = greyImage.resize((64,64))

brightnessMatrix = np.matrix(greyImageScaled)
print(brightnessMatrix)