def half_pyramid():
    h = int(input("Enter a number between 1 and 22: "))
    while h > 23 or h <= 0:
        h = int(input("Enter a number between 1 and 22: "))
    i = 0
    while i < h:
        spc = 0
        hsh = 0
        while spc < (h - (i + 1)):
            print(" ", end="")
            spc += 1
        while hsh < (i + 2):
            print("#", end="")
            hsh += 1
        print ('\n', end="")
        i += 1

if __name__ == "__main__":
    half_pyramid()