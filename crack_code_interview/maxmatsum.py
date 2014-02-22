from random import randint;
maxSum = [0];
bestMatrix = [0];
def DFS(a):
    print a;
    if sum(a) > maxSum[0]:
        maxSum[0] = sum(a);
        bestMatrix[0] = a;
    for splitter in range(1, len(a)):
        leftSum = sum(a[:splitter]);
        rightSum = sum(a[splitter:]);
        if leftSum > 0 and rightSum < 0:
            DFS(a[:splitter]);
        elif leftSum < 0 and rightSum > 0:
            DFS(a[splitter:])
a = [randint(0, 20) - 10 for item in range(10)];
print a;
print "===";
DFS(a);
print maxSum[0];
print bestMatrix[0];