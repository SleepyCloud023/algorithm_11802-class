def rod_cutting(length_rod, price_i):
    price_i = [0] + price_i
    optimal_price = price_i[:]
    optimal_divide = [0] * (length_rod + 1)
    for i in range(1, length_rod + 1):
        best = price_i[i]
        optimal_divide[i] = i
        for j in range(1, i//2 + 1):
            price = price_i[j] + price_i[i - j]
            if best < price:
                best = price
                optimal_divide[i] = j

        optimal_price[i] = best
    print(optimal_price[length_rod])
    while(length_rod > 0):
        divided_amount = optimal_divide[length_rod]
        print(divided_amount, end=' ')
        length_rod -= divided_amount
    print()
    return optimal_price[length_rod]

rod_cutting(10, [1, 5, 8, 9, 10, 17, 17, 20, 24, 30])
rod_cutting(4, [1,5,8,9])
