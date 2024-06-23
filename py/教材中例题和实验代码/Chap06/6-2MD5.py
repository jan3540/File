import hashlib
def get_md5(obj):
    # 实例化加密对象
    md5=hashlib.md5()
    # 进行加密操作
    md5.update(obj.encode('utf-8'))
    # 返回加密后的结果
    return md5.hexdigest()
phone=input("请输入一个手机号：")
print("加密结果是：",get_md5(phone))
