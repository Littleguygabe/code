import random, time, os
from random import sample
base  = 3
side  = base*base
numberEmpty = 40
difficulty = numberEmpty/(side*side)
large_labels = []
empty_nums = []
empty_pos = []

# pattern for a baseline valid solution
def pattern(r,c): return (base*(r%base)+r//base+c)%side

# randomize rows, columns and numbers
def shuffle(s): 
    return sample(s,len(s))

rBase = range(base) 
rows  = [g*base + r for g in shuffle(rBase) for r in shuffle(rBase)]
cols  = [g*base + c for g in shuffle(rBase) for c in shuffle(rBase)]
nums  = shuffle(range(1,base*base+1))

def check_board():
    entry_list = []   
    answers = []
    check = []
    count = 0

    print('checking board')

    #check against give
    for y in range(0,len(large_labels)):
        for x in range(0,len(large_labels[y])):
            label = str(large_labels[y][x])
            if label[2] == 'e':
                entry_list.append(large_labels[y][x])
                answers.append(str(solution[y][x]))

    for i in entry_list:
        check.append(i.get())

    for i in range(0,len(answers)):
        if check[i] == answers[i]:
            entry_list[i].config(bg = 'green')

        elif check[i] == 'gabe':
            print(answers)

        else:
            entry_list[i].config(bg = 'red')
            count+=1
        
    if count == 0:
        print('you completed it!')
                    
def remove_nums(board):
    global empty_nums, empty_pos 
    empty_squares = int(len(board)*len(board[0])*difficulty)
    for i in range(0,empty_squares):
        x = random.randint(0,side-1)
        y = random.randint(0,side-1)
        while board[y][x] == '':
            x = random.randint(0,side-1)
            y = random.randint(0,side-1)
        board[y][x] = ''
        empty_pos.append(y)
        empty_pos.append(x)

def check_valid(board):
    breakCount = 15
    emptyCount = 0
    count = 0
    possibilities = 1
    numCoordsToCheck = []
    print('validating board')
    for i in range(0,len(empty_pos),2):
        possibleNumbers = []
        tempCoords = []
        for num in range(1,side+1):
            possibleNumbers.append(num)
        y = empty_pos[i]
        x = empty_pos[i+1]
        #check horizontal
        for checkx in range(0,side):
            if board[y][checkx] != '':
                possibleNumbers.remove(board[y][checkx])

        #check vertical
        for checky in range(0,side):
            for i in range(0,len(possibleNumbers)):
                if len(possibleNumbers) == 1:
                    break
                else:
                    if board[checky][x] == possibleNumbers[i-1]:
                        possibleNumbers.remove(board[checky][x])

        #check 3x3
        for boxy in range(0-(y%base),(0-(y%base))+3):
            for boxx in range(0-(x%base),(0-(x%base))+3):

                if board[y+boxy][x+boxx] != '':
                    for i in range(0,len(possibleNumbers)):
                        if possibleNumbers[i-1] == board[y+boxy][x+boxx]:
                            possibleNumbers.remove(board[y+boxy][x+boxx])
                            
        if len(possibleNumbers) > 1:
            #print(len(possibleNumbers))
            print('greater than length of 2')
            numCoordsToCheck.append(possibleNumbers)
            tempCoords.append(y)
            tempCoords.append(x)
            numCoordsToCheck.append(tempCoords)

        elif len(possibleNumbers) == 1:
            print('len --> 1')
            print(board[y][x])
            board[y][x] = possibleNumbers[0]
            for i in range(0,len(board)):
                print(board[i])

        if emptyCount==20:
            break

        for y in range(0,len(board)):
            for x in range(0,len(board)):
                if board[y][x] == '':
                    emptyCount+=1
                    breakCount+=1

        else:
            print('valid solution')
            finish = True

        if emptyCount>=1:
            if breakCount<=20:
                finish = True
    
        possibilities = possibilities*len(possibleNumbers)
        print('possible numbers are -> ',possibleNumbers, 'for -->',y,x)
        print(possibilities, 'current solution(s)')
        print(numCoordsToCheck)
        print('--->')
        count+=1

        if finish == True:
            break

def generate_Board():
    global board, solution, empty_squares,large_labels
    solution = [ [nums[pattern(r,c)] for c in cols] for r in rows ]
    board = [ [nums[pattern(r,c)] for c in cols] for r in rows ]

    remove_nums(board)
    check_valid(board)

os.system('cls')
generate_Board()
for i in range(0,len(board)):
    print(board[i])