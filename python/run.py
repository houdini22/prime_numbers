import matplotlib.pyplot as plt
import numpy as np
import math

with open("./data.txt") as f:
    content = f.readlines()

content = [x.strip() for x in content]

def isPrime(x):
    if x < 2: return False
    if x == 2: return True
    if x % 2 == 0: return False
    for i in range(3, int(x / 2)):
        if x % i == 0: return False
    
    return True

#fig = plt.figure(figsize=(3840 * 4 / 96, 2160 * 4 / 96), dpi=96)
x = []
my_x_ticks = []
for i in range(0, 40):
    x.append(i)
    my_x_ticks.append(str(i) + " " + str(int(isPrime(i))))

#plt.xticks(x, my_x_ticks)
plt.axis('equal')
plt.grid()

fig = plt.figure(figsize=(1080 * 16 / 96, 1080 * 16 / 96), dpi=96)


ax = fig.add_subplot(111)
ax.axhline(y=0, linewidth=2, color='blue')
ax.axvline(x=0, linewidth=2, color='blue')
ax.set_xticks(x)
ax.set_xticklabels(my_x_ticks)

histogram = {}

for c in content:
    c = c.split(" ")
    x = int(c[0])
    histogram[x] = {}
    
    key = 0;
    for num in c:
        y = False
        
        if key == 0:
            key += 1
            continue
        
        if num in histogram[x]:
            histogram[x][num] += 1 
        else:
            histogram[x][num] = 1
        
        key += 1
    
for c in content:
    c = c.split(" ")
    x = int(c[0])
    
    if (x < 0 or x > 40):
        continue
    
    print("curr: ", x)
    
    key = 0;
    for num in c:
        y = False
        if key == 0:
            key += 1
            continue
        
        length = len(num)
        direction = num[length - 1]
        
        if direction == 'F':
            direction = -1;
        else:
            direction = 1;
        
        y = int(num[:-1])
        
        if key == 1:
            y = y - 1
            
        if y == 0:
            continue
            
        y = y * direction
        
        plt.plot([x], [y], marker='o', color="green", markersize=8)
        
        radius = histogram[int(x)][num]
        circle1 = plt.Circle((x, y), radius, linewidth=1, fill=False, edgecolor='red')
        ax.add_artist(circle1)
            
        key += 1
        
        
        
for c in content:
    c = c.split(" ")
    x = int(c[0])
    
    if (x < -40 or x > 0):
        continue
    
    #print("curr: ", x)
    
    x = abs(x)
    
    key = 0;
    for num in c:
        y = False
        if key == 0:
            key += 1
            continue
        
        length = len(num)
        direction = num[length - 1]
        
        if direction == 'F':
            direction = -1;
        else:
            direction = 1;
        
        y = int(num[:-1])
        
        #if key == 1:
            #y = y - 1
            
        if y == 0:
            continue
            
        y = y * direction
        
        #plt.plot([x], [y], marker='o', color="red", markersize=4)
        
        key += 1

fig.savefig("result_new.png", pad_inches=0)
