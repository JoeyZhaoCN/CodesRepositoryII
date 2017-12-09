# coding=UTF-8
import pymysql.cursors


class DataBase():
    def __init__(self):
        """初始化
        连接至数据库
        """
        self.connect = pymysql.Connect(
            host='localhost',
            port=3306,
            user='root',
            passwd='***********',
            db='banques',
        )
        self.cursor = self.connect.cursor()

    def change_data(self):
        """数据库操作：
        修改数据
        """
        try:
            sql = input('请输入sql修改操作语句 -->')
            # cursor = self.connect.cursor
            self.cursor.execute(sql)
            self.connect.commit()
            print('成功修改', self.cursor.rowcount, '条数据')
            print('---------------------------------------')
            print('\n')
        except Exception:
            print('语句输入错误，请检查后重新输入')
            print('---------------------------------------')
            print('\n')

    def query_data(self):
        """数据库操作：
        查询数据
        """
        try:
            sql = str(input('请输入sql查询操作语句 -->'))
            # cursor = self.connect.cursor
            self.cursor.execute(sql)
            for row in self.cursor.fetchall():
                print(row)
            print('共查出', self.cursor.rowcount, '条数据')
            print('---------------------------------------')
            print('\n')
        except Exception:
            print('语句输入错误，请检查后重新输入')
            print('---------------------------------------')
            print('\n')


    def close_connect(self):
        """数据库操作：
        关闭连接
        """
        self.cursor.close()
        self.connect.close()
        print('已关闭数据库连接')
