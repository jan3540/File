import random
import threading
import time
 
N = 3
maxFrameNum = N - 2
maxWheelNum = N - 1
frame = 0
wheel = 0
empty = N
mutex = 1
 
 
def refresh(name):
    if name == 'maxFrameNum':
        return maxFrameNum
    elif name == 'maxWheelNum':
        return maxWheelNum
    elif name == 'frame':
        return frame
    elif name == 'wheel':
        return wheel
    elif name == 'empty':
        return empty
    elif name == 'mutex':
        return mutex
 
 
def p(id, item, name):
    print('【woker%s】need a  %s(%d)' % (id, name, item))
    while item <= 0:
        print('【woker%s】is waiting for %s' % (id, name))
        time.sleep(random.random())
        item = refresh(name)
    global maxWheelNum
    global maxFrameNum
    global wheel
    global empty
    global mutex
    global frame
    if name == 'maxFrameNum':
        maxFrameNum -= 1
    elif name == 'maxWheelNum':
        maxWheelNum -= 1
    elif name == 'frame':
        frame -= 1
    elif name == 'wheel':
        wheel -= 1
    elif name == 'empty':
        empty -= 1
    elif name == 'mutex':
        mutex -= 1
 
 
def v(id, item, name):
    global maxWheelNum
    global maxFrameNum
    global wheel
    global empty
    global mutex
    global frame
    if name == 'maxFrameNum':
        maxFrameNum += 1
    elif name == 'maxWheelNum':
        maxWheelNum += 1
    elif name == 'frame':
        frame += 1
    elif name == 'wheel':
        wheel += 1
    elif name == 'empty':
        empty += 1
    elif name == 'mutex':
        mutex += 1
    print('【woker%s】release  %s' % (id, name))
 
 
def printMsg():
    print('maxFrameNum:%s,maxWheelNum:%s,frame:%s,wheel:%s,empty:%s' % (maxFrameNum, maxWheelNum, frame, wheel, empty))
 
 
def woker1():
    while True:
        time.sleep(random.random() * 4)
        p(1, maxFrameNum, 'maxFrameNum')
        print('【woker1】is making a frame')
        p(1, empty, 'empty')
 
        p(1, mutex, 'mutex')
        print('【woker1】is putting a frame into the box')
        v(1, mutex, 'mutex')
 
        v(1, frame, 'frame')
        printMsg()
 
 
def woker2():
    while True:
        time.sleep(random.random() * 2)
        p(2, maxWheelNum, 'maxWheelNum')
        print('【woker2】is making a wheel')
        p(2, empty, 'empty')
 
        p(2, mutex, 'mutex')
        print('【woker2】is putting a wheel into the box')
        v(2, mutex, 'mutex')
 
        v(2, wheel, 'wheel')
 
        printMsg()
 
 
def woker3():
    while True:
        time.sleep(random.random() * 4)
        p(3, frame, 'frame')
        p(3, mutex, 'mutex')
        print('【woker3】is getting a frame from the box')
        v(3, mutex, 'mutex')
        v(3, maxFrameNum, 'maxFrameNum')
        v(3, empty, 'empty')
        printMsg()
        p(3, wheel, 'wheel')
        p(3, mutex, 'mutex')
        print('【woker3】is getting a wheel from the box')
        v(3, mutex, 'mutex')
        v(3, maxWheelNum, 'maxWheelNum')
        v(3, empty, 'empty')
        printMsg()
        p(3, wheel, 'wheel')
        p(3, mutex, 'mutex')
        print('【woker3】is getting a wheel from the box')
        v(3, mutex, 'mutex')
        v(3, maxWheelNum, 'maxWheelNum')
        v(3, empty, 'empty')
        printMsg()
        print('【woker3】is making a car')
 
 
if __name__ == '__main__':
    w1 = threading.Thread(target=woker1)
    w2 = threading.Thread(target=woker2)
    w3 = threading.Thread(target=woker3)
    w1.start()
    w2.start()
    w3.start()