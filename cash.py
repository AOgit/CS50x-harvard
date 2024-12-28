from cs50 import get_float

change = 0

while not change > 0:
    change = get_float("Change: ")

coins = [25, 10, 5, 1]

amount_coins = 0
change = change * 100

for coin in coins:
    if change >= coin:
        div = int(change / coin)
        amount_coins += div
        change -= coin * div

print(amount_coins)




