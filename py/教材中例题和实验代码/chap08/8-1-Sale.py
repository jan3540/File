# 例8-1
import numpy as np
prices = np.array([50, 60, 70, 80, 90])
total_price = np.sum(prices)
threshold_price = np.linalg.solve(np.array([[0.2]]), np.array([[100]]))
threshold_price = threshold_price[0,0]
print("当该类商品价格大于",np.array(41.0),"元且小于",threshold_price-total_price,"时，适合参加第一个活动。")
print("当该类商品价格大于",threshold_price-total_price,"元且小于",np.array(249.0),"元时，适合参加第二个活动。")