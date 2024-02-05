from PIL import Image
import os

image_path = r"C:\Users\Administrator\Documents\GitHub\NANS_Projekat_2023_-_RayTracing_renderer\NANS_Projekat_2023_-_RayTracing_renderer\slike\image.ppm"

fsize = os.path.getsize(image_path)

if fsize > 0 :       
    img = Image.open(image_path)
    img.save(r"slike\image.jpg")
