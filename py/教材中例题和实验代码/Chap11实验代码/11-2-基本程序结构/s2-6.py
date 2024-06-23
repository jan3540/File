annualRate=eval(input("年利率(格式示例7.25):"))
monthRate=annualRate/1200
loan=eval(input("贷款金额(单位元,格式示例500000):"))
year=eval(input("贷款年限(格式示例10):"))
monthpay=loan*monthRate/(1-1/(1+monthRate)**(year*12))
totalpay=monthpay*year*12
print("月供是:",round(monthpay,2))
print("总还款金额是:",round(totalpay,2))
