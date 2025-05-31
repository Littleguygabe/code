def minOperations(boxes):
    a = []
    for i in range(len(boxes)):
        count = 0
        for j in range(len(boxes)):
            if boxes[j] == '1':
                count+=(abs(j-i))

        a.append(count)

    return a



print(minOperations('001011'))