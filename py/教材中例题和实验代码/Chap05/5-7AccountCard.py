class AccountCard():
    '''创建卡片类'''
    def __init__(self,card_ID,expiry_date,card_type='储蓄卡'):
        self.card_ID=card_ID
        self.card_type=card_type
        self.expiry_date=expiry_date
    # 格式化卡片信息
    def __repr__(self):
        return f'卡号:{self.card_ID}有效日期:{self.expiry_date}类型:{self.card_type}'
 
class ATM():
    '''创建一个ATM机类，定义属性，传入一个账户信息数据库'''
    def __init__(self):
        self.accounts={
            '1122334455667788':{'password':'123321','balance':12000.0,'valid':'True'},
            '1122334455667789':{'password':'123456','balance':54321.0,'valid':'True'},
            '1122334455667790':{'password':'147258','balance':0.0,'valid':'True'}
            }
        # 声明一个卡片容器属性、一个卡片信息容器属性
        self.current_card=None
        self.current_account=None
 
    def read_card(self,card):
        '''定义一个读取卡片信息的方法'''
        # 判断传入的卡片信息是否在数据库中
        if card.card_ID in self.accounts:
            # 将数据库中对应的卡片信息赋值给信息容器
            self.current_account=self.accounts[card.card_ID]
            # 密码输入次数限制
            for i in range(3):
                password = input('请输入密码：')
                if password==self.current_account['password']:
                    # 密码正确，则卡片读取成功，返回卡插入成功
                    self.current_card=card
                    return True
                else:
                    print('密码错误！')
            else:
                print('密码输入次数已经超过三次，已锁卡')
        else:
            print('账户不存在！')
            return False
 
    def show_balance(self):
        '''定义一个账户余额展示方法'''
        # 判断信息容器是否有信息
        if self.current_account:
            print(f"余额：{self.current_account['balance']}")
 
    def save_money(self,money):
        '''定义存钱的方法'''
        # 加入存钱限制条件
        if self.current_account and money >=100:
            self.current_account['balance'] += money
            print('存钱成功！')
            return True
        return False
 
    def get_money(self,money):
        '''定义一个取钱的方法'''
        # 添加限定条件
        if 100 <= money < self.current_account['balance'] and self.current_account:
            self.current_account['balance']-=money
            print('取钱成功！')
            return True
        return False
 
    def transfer(self,other_card_ID,money):
        '''定义一个转账功能,传入转账卡号，金额'''
        # 添加限制条件
        if self.current_account and other_card_ID in self.accounts:
            other_account=self.accounts[other_card_ID]
            if money < self.current_account['balance']:
                self.current_account['balance'] -= money
                other_account['balance'] += money
                print('转账成功！')
                return True
            else:
                print('转账金额超限！')
            return False
        else:
            print('无效账户名')
        return False
 
    def move_card(self):
        '''拔卡'''
        self.accounts=None
        self.current_account=None
 
if __name__ == '__main__':
    # 准备两张卡片的信息
    card1=AccountCard('1122334455667788','2050-05-11','信用卡')
    card2=AccountCard('1122334455667789','2070-08-29')
 
    a=ATM()
    # 读取卡片信息
    a.read_card(card1)
    a.show_balance()
    # 存钱并查看
    a.save_money(5000)
    a.show_balance()
    #取钱并查看
    a.get_money(8000)
    a.show_balance()
    a.transfer('1122334455667789',6666)
    
    # 展示转账后卡2的信息
    a.read_card(card2)
    a.show_balance()
    a.move_card()
