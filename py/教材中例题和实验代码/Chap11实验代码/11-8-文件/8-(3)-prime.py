def is_prime(n):
    if n < 2:
        return False
    for i in range(2, n):
        if n % i == 0:
            return False
    return True

# 找出2到100之间的所有素数
prime_numbers = [str(num) for num in range(2, 101) if is_prime(num)]

# 将素数写入文本文件，以逗号间隔
with open('sy8-3.txt', 'w') as file:
    file.write(', '.join(prime_numbers))

print("2~100中所有的素数已写入sy8-3.txt文件。")