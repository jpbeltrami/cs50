import sys

def main():
    # Gets input from command line and exits if not just one number
    if len(sys.argv) != 2:
        print("Please enter ONE number.")
        exit(0)
    else:
        k = int(sys.argv[1])
        p = input("Enter your plain text: ")
        
        # rotate the letters
        for word in p:
            string = word.split()
            for letter in string:
                # TODO:
                # split string into letters
                # letters_list = string.split('')
                # convert to lowercase
                # for letter in letters_list:
                #   letter = letter.lower()
                # if not letter ignore
                # convert to unicode
                #   letter = ord(letter)
                # else rotate by key
                # join the encrypted letters and append word to new_list
                # join the encrypted words into one sentence
        
        
if __name__ == "__main__":
    main()