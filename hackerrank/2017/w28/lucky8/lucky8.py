import sys

mod = [0 for i in range(8)]

n = int(raw_input().strip())
number = raw_input().strip()

modulo = 10**9 + 7

for ch in number:
    m = int(ch) % 8
    new_mod = mod[:]
    # handling single digit
    new_mod[m] += 1

    # for the current digit considered, to asses if its multiple of 8, we take the modulo value
    # of the sequence and form a new 2 digit number, if this 2 digit number is divisible by 8 then
    # its certain that the sequence that had the tens digit formed (by sequence mod 8) is divisible
    # by 8, we use this principle and maintain the possible modulo value and update them while
    # exploring new digits

    for r in range(8):
        new_r = ((r*10)+m)%8
        new_mod[new_r] = (new_mod[new_r] + mod[r]) % modulo
    mod = new_mod[:]

print(mod[0])
