# TemplateMatching
  Matches the given template in the given image and returns the position where the most probable position occurs.
  Given image is pre processed (ex: sharpening, contrast adjustment etc...) and binarised.
  The binarised result is correlated with the given template to find the best probable match position
  
### Assumptions 
  - Images are inputed as raw (headerless) 24 bit RGB bit map array.
  - Template images are already preprocessed and cropped.
    
