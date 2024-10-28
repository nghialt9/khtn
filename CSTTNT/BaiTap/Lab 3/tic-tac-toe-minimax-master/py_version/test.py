#!/usr/bin/env python3
from math import inf as infinity
from random import choice
import platform
import time
from os import system

HUMAN = -1
COMP = +1

def create_board(size):
    return [[0 for _ in range(size)] for _ in range(size)]

def evaluate(state):
    """
    Function to heuristic evaluation of state.
    :param state: the state of the current board
    :return: +1 if the computer wins; -1 if the human wins; 0 draw
    """
    if wins(state, COMP):
        return +1
    elif wins(state, HUMAN):
        return -1
    else:
        return 0

def wins(state, player):
    """
    This function tests if a specific player wins. The win condition is 5 in a row.
    :param state: the state of the current board
    :param player: a human or a computer
    :return: True if the player wins
    """
    size = len(state)
    win_condition = 5  # Win condition for 5 in a row

    # Check rows
    for row in range(size):
        for col in range(size - win_condition + 1):
            if all(state[row][col + i] == player for i in range(win_condition)):
                return True

    # Check columns
    for col in range(size):
        for row in range(size - win_condition + 1):
            if all(state[row + i][col] == player for i in range(win_condition)):
                return True

    # Check diagonals
    for row in range(size - win_condition + 1):
        for col in range(size - win_condition + 1):
            if all(state[row + i][col + i] == player for i in range(win_condition)):
                return True
            if all(state[row + i][col + win_condition - i - 1] == player for i in range(win_condition)):
                return True

    return False

def game_over(state):
    return wins(state, HUMAN) or wins(state, COMP)

def empty_cells(state):
    """
    Each empty cell will be added into cells' list
    :param state: the state of the current board
    :return: a list of empty cells
    """
    cells = []
    for x, row in enumerate(state):
        for y, cell in enumerate(row):
            if cell == 0:
                cells.append([x, y])
    return cells

def valid_move(x, y):
    if [x, y] in empty_cells(board):
        return True
    else:
        return False

def set_move(x, y, player):
    if valid_move(x, y):
        board[x][y] = player
        return True
    else:
        return False

def minimax(state, depth, player):
    if player == COMP:
        best = [-1, -1, -infinity]
    else:
        best = [-1, -1, +infinity]

    if depth == 0 or game_over(state):
        score = evaluate(state)
        return [-1, -1, score]

    for cell in empty_cells(state):
        x, y = cell[0], cell[1]
        state[x][y] = player
        score = minimax(state, depth - 1, -player)
        state[x][y] = 0
        score[0], score[1] = x, y

        if player == COMP:
            if score[2] > best[2]:
                best = score  # max value
        else:
            if score[2] < best[2]:
                best = score  # min value

    return best

def clean():
    os_name = platform.system().lower()
    if 'windows' in os_name:
        system('cls')
    else:
        system('clear')

def render(state, c_choice, h_choice):
    """
    Print the board on console
    :param state: current state of the board
    """
    chars = {
        -1: h_choice,
        +1: c_choice,
        0: ' '
    }
    str_line = '-' * (len(state) * 4 + 1)
    print('\n' + str_line)
    for row in state:
        for cell in row:
            symbol = chars[cell]
            print(f'| {symbol} |', end='')
        print('\n' + str_line)

def ai_turn(c_choice, h_choice):
    depth = len(empty_cells(board))
    if depth == 0 or game_over(board):
        return

    clean()
    print(f'Computer turn [{c_choice}]')
    render(board, c_choice, h_choice)

    if depth == len(board) * len(board):
        x = choice([i for i in range(len(board))])
        y = choice([i for i in range(len(board))])
    else:
        move = minimax(board, depth, COMP)
        x, y = move[0], move[1]

    set_move(x, y, COMP)
    time.sleep(1)

def human_turn(c_choice, h_choice):
    depth = len(empty_cells(board))
    if depth == 0 or game_over(board):
        return

    move = -1
    moves = {i + 1: [i // len(board), i % len(board)] for i in range(len(board) * len(board))}

    clean()
    print(f'Human turn [{h_choice}]')
    render(board, c_choice, h_choice)

    while move < 1 or move > len(board) * len(board):
        try:
            move = int(input(f'Use numpad (1..{len(board) * len(board)}): '))
            coord = moves[move]
            can_move = set_move(coord[0], coord[1], HUMAN)

            if not can_move:
                print('Bad move')
                move = -1
        except (EOFError, KeyboardInterrupt):
            print('Bye')
            exit()
        except (KeyError, ValueError):
            print('Bad choice')

def main():
    global board, board_size, win_condition
    clean()
    board_size = int(input("Enter board size (5 for 5x5, 10 for 10x10): "))
    win_condition = 5
    board = create_board(board_size)

    h_choice = ''  # X or O
    c_choice = ''  # X or O
    first = ''  # if human is the first

    while h_choice != 'O' and h_choice != 'X':
        try:
            print('')
            h_choice = input('Choose X or O\nChosen: ').upper()
        except (EOFError, KeyboardInterrupt):
            print('Bye')
            exit()
        except (KeyError, ValueError):
            print('Bad choice')

    if h_choice == 'X':
        c_choice = 'O'
    else:
        c_choice = 'X'

    clean()
    while first != 'Y' and first != 'N':
        try:
            first = input('First to start?[y/n]: ').upper()
        except (EOFError, KeyboardInterrupt):
            print('Bye')
            exit()
        except (KeyError, ValueError):
            print('Bad choice')

    while len(empty_cells(board)) > 0 and not game_over(board):
        if first == 'N':
            ai_turn(c_choice, h_choice)
            first = ''

        human_turn(c_choice, h_choice)
        ai_turn(c_choice, h_choice)

    if wins(board, HUMAN):
        clean()
        print(f'Human turn [{h_choice}]')
        render(board, c_choice, h_choice)
        print('YOU WIN!')
    elif wins(board, COMP):
        clean()
        print(f'Computer turn [{c_choice}]')
        render(board, c_choice, h_choice)
        print('YOU LOSE!')
    else:
        clean()
        render(board, c_choice, h_choice)
        print('DRAW!')

    exit()

if __name__ == '__main__':
    main()
