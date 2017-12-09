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
        self.cursor = self.connect.cursor

    def change_data(self):
        """数据库操作：
        修改数据
        """
        sql = input('请输入sql修改操作语句 -->')
        self.cursor.execute(sql)
        self.connect.commit()
        print('成功修改', cursor.rowcount, '条数据')

    def query_data(self):
        """数据库操作：
        查询数据
        """
        sql = input('请输入sql查询操作语句 -->')
        self.cursor.execute(sql)
        for row in cursor.fetchall():
            print(row)
        print('共查出', cursor.rowcount, '条数据')

    def close_connect(self):
        """数据库操作：
        关闭连接
        """
        self.cursor.close()
        self.connect.close()
        print('已关闭数据库连接')
