from cs50 import get_int

height = 0

while not (height > 0 and height < 9):
    height = get_int("Heigth: ")


for i in range(height):
    print(f" " * (height - i - 1) + "#" * (i + 1) + "  " + "#" * (i + 1))
