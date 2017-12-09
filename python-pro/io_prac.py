forbideen = ('!', ',', '.', ';', '/', '?', ' ')


def remove_forbideen(text):
    text = text.lower()
    for ch in text:
        if ch in forbideen:
            text = text.replace(ch, '')
    return text


def reverse(text):
    return text[::-1]# 反转字符串


def is_palindrome(text):
    return text == reverse(text)


instr = input('Please input a string:')
instr = remove_forbideen(instr)
if is_palindrome(instr):
    print('Yes, it is a palindrome')
else:
    print('No, it is not a palindrome')
