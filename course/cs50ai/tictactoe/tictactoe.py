"""
Tic Tac Toe Player
"""

import math
import copy

X = "X"
O = "O"
EMPTY = None

def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    if terminal(board): return None
    cnt_x = 0
    cnt_o = 0
    for i in range(3):
        for j in range(3):
            if board[i][j] == X:
                cnt_x += 1
            if board[i][j] == O:
                cnt_o += 1
    return X if cnt_x == cnt_o else O 


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    if terminal(board):
        return None
    act = player(board)
    res = set()
    for i in range(3):
        for j in range(3):
            if board[i][j] == EMPTY:
                res.add((i, j))
    return res

    


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """
    p = player(board)
    new_board = copy.deepcopy(board)
    i, j =  action
    scope = [0, 1, 2]
    if i not in scope or j not in scope or board[i][j] != EMPTY:
        raise RuntimeError("action undefind")
    new_board[i][j] = p
    return new_board


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    for i in range(3):
        if (board[i][0] == board[i][1] == board[i][2]) and board[i][0] != EMPTY:
            return board[i][0]
        if (board[0][i] == board[1][i] == board[2][i]) and board[0][i] != EMPTY:
            return board[0][i]
    
    if (board[0][0] == board[1][1] == board[2][2]) and board[0][0] != EMPTY:
        return board[0][0]

    if (board[0][2] == board[1][1] == board[2][0]) and board[0][2] != EMPTY:
        return board[0][2] 

    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """
    if winner(board) != None:
        return True
    for i in range(3):
        for j in range(3):
            if board[i][j] == EMPTY:
                return False
    return True


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """
    winner_player = winner(board)
    if winner_player == X:
        return 1
    elif winner_player == O:
        return -1
    else:
        return 0


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """
    if terminal(board):
        return None
    current_player = player(board)
    best_action = None

    if current_player == X:
        score = float('-inf')
        current_action = actions(board)
        for action in current_action:
            action_result = result(board, action)
            if terminal(action_result):
                current_score = utility(action_result)
                if current_score < score:
                    return None
            else:
                next_action = minimax(action_result)
                new_board = result(action_result, next_action)
                while not terminal(new_board):
                    i, j = minimax(new_board)
                    new_board[i][j] = player(new_board)
                current_score = utility(new_board) 
            if current_score > score:
                score = current_score
                best_action = action

    elif current_player == O:
        score = float('inf')
        current_action = actions(board)
        for action in current_action:
            action_result = result(board, action)
            if terminal(action_result):
                current_score = utility(action_result)
                if current_score > score:
                    return None
            else:
                next_action = minimax(action_result)
                new_board = result(action_result, next_action)
                while not terminal(new_board):
                    i, j = minimax(new_board)
                    new_board[i][j] = player(new_board)
                current_score = utility(new_board) 
            if current_score < score:
                score = current_score
                best_action = action

    return best_action


