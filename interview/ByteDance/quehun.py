#a = input().split()
#alist = [int(x) for x in a]
 
alist = [1, 1, 1, 2, 2, 2, 6, 6, 6, 7, 7, 7, 9]
 
He_kinds = []
 
# 判断是否和牌
def isHe(cardlist):
    l = len(cardlist)
    if l == 0:
        return True
    count0 = cardlist.count(cardlist[0])
    
    # 没出现过雀头，且第一个数字出现的次数 >= 2，且去掉雀头剩下的能组成和牌
    if l % 3 != 0 and count0 >= 2 and isHe(cardlist[2:]) == True:
        return True
    # 如果第一个数字出现次数 >= 3，且去掉这个刻子后剩下的能和牌
    if count0 >= 3 and isHe(cardlist[3:]) == True:                         
        return True
    # 如果存在顺子，且移除顺子后剩下的能和牌
    if cardlist[0]+1 in cardlist and cardlist[0]+2 in cardlist:
        c_cardlist = cardlist[1:]
        c_cardlist.remove(cardlist[0]+1)
        c_cardlist.remove(cardlist[0]+2)
        if isHe(c_cardlist) == True:
            return True
    # 以上条件都不满足，则不能和牌
    return False
    
# 最多有9种抽牌方法可以和牌，计算每一种能不能和牌
for i in range(1,10):
    if (alist.count(i) == 4):
        continue
    if isHe(sorted(alist + [i])) == True:       # 如果这种抽牌方式可以和牌
        He_kinds.append(i)                      # 加入和牌类型列表

for x in He_kinds:
    print(x, end=" ")
