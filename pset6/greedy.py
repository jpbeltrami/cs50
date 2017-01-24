import math

def main():
    coins = 0
    change = math.floor(float(input("Oh hai! How much change is owed?")) * 100)
    
    while change <= 0:
        change = math.floor(float(input("Oh hai! How much change is owed?")) * 100)
        
    while change != 0:
        if change >= 25:
            coins += 1
            change -= 25
            
        elif change >= 10:
            coins  += 1
            change -= 10
            
        elif change >= 5:
            coins += 1
            change -= 5
            
        elif change >= 1:
            coins += 1
            change -= 1
            
    print(coins)
    

if __name__ == '__main__':
    main()