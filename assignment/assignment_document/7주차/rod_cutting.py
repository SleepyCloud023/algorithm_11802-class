def rod_cutting(length_rod, price_i):
    optimal_price = price_i[:]
    for i in range(1, length_rod + 1):
        best = price_i[i - 1]
        for j in range(1, i//2 + 1):
            price = price_i[j - 1] + price_i[i - j - 1]
            if best < price:
                best = price
        optimal_price[i - 1] = best
    print(optimal_price)
    return optimal_price[length_rod - 1]

rod_cutting(10, [1, 5, 8, 9, 10, 17, 17, 20, 24, 30])
rod_cutting(4, [1,5,8,9])
