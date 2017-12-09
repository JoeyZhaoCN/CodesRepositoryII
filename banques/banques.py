# coding=UTF-8
import banques_db


class BanquesMain:
    def __init__(self):
        self.database = banques_db.DataBase()

    def start(self):
        while True:
            print('1.修改数据：')
            print('2.查询数据')
            print('3.关闭连接')
            flag = int(input('请选择操作 -->'))
            if flag == 1:
                self.database.change_data()
            if flag == 2:
                self.database.query_data()
            if flag == 3:
                self.database.close_connect()
                break


if __name__ == '__main__':
    banques = BanquesMain()
    banques.start()
