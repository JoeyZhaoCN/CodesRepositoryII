# coding=UTF-8

class SchoolMember:
    """代表任何学校里的成员"""
    def __init__(self, name, age):
        self.name = name
        self.age = age
        print('Initialized schoolMembers: {}'.format(self.name))

    def tell(self):
        """告诉我有关我的细节"""
        print('Name: {}  age: {} \\'.format(self.name, self.age), end=' ')


class Teacher(SchoolMember):
    """代表一位老师"""
    def __init__(self, name, age, salary):
        SchoolMember.__init__(self, name, age)
        self.salary = salary
        print('Initialized teacher: {}'.format(self.name))

    def tell(self):
        SchoolMember.tell(self)
        print('Salary: {}'.format(self.salary))


class Student(SchoolMember):
    """代表一位学生"""
    def __init__(self, name, age, marks):
        SchoolMember.__init__(self, name, age)
        self.marks = marks
        print('Initialized students: {}'.format(self.name))

    def tell(self):
        SchoolMember.tell(self)
        print('Marks: {}'.format(self.marks))


t = Teacher('Mrs. Shrividya', 40, 30000)
s = Student('Joezeo', 22, 95)

# 打印一行空白行
print()

members = [t, s]
for member in members:
    member.tell()
# help(str)
