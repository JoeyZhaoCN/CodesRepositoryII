# encoding=UTF-8

class ShortInputEception(Exception):
    """一个由用户定义的异常类"""
    def __init__(self, length, atleast):
        Exception.__init__(self)
        self.length = length
        self.atleast = atleast


try:
    text = input('Enter something -->')
    if len(text) < 3:
        raise ShortInputEception(len(text), 3)
except EOFError:
    print('Why did you do an EOF on me?')
except ShortInputEception as ex:
    print(('ShortInputException: The input was ' +
        '{} long, excepted at least {}')
        .format(ex.length, ex.atleast))
else:
    print('No exception was raised.')
