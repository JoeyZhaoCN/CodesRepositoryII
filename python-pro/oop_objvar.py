# coding=UTF-8
class Robot:
    population = 0  # 计数实例的数量

    def __init__(self, name):
        """初始化数据

        初始化name，update population"""
        self.name = name
        print('Initializing {}'.format(self.name))
        Robot.population += 1

    def die(self):
        """消除机器人

        update population"""
        print('{} is being destroyed!'.format(self.name))
        Robot.population -= 1

        if Robot.population == 0:
            print('{} was the last one'.format(self.name))
        else:
            print('There are still {:d} robots working.'.format(
                Robot.population))

    def say_hi(self):
        """来自机器人的问候"""
        print('Greeting, my master call me {}'.format(self.name))

    # 装饰器，@classmethod 等价于调用 how_many = classmethod(how_many)
    @classmethod
    def how_many(cls):
        """打印出当前的人口数量"""
        print('We have {:d} robots.'.format(Robot.population))


droid1 = Robot('R2-D2')
droid1.say_hi()
Robot.how_many()

droid2 = Robot('C-3p0')
droid2.say_hi()
Robot.how_many()

print('\nRobots can do some work here\n')

print('Robots have finished their work. so let\'s destroy them.')

droid1.die()
droid2.die()

Robot.how_many()
