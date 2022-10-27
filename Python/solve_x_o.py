from ast import main
from typing import List


class Solution:
    def solve(self, board: List[List[str]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        leetcode 130. 被围绕的区域
        给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' ，找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。
        """
        rows = len(board)
        cols = len(board[0])

        def dfs(row, col):
            if 0 <= row < rows and 0 <= col < cols and board[row][col] == "O":
                board[row][col] = "N"
                for [a, b] in [[-1, 0], [1, 0], [0, -1], [0, 1]]:
                    dfs(row + a, col + b)
            else:
                return

        for i in range(rows):
            dfs(i, 0)
            dfs(i, cols - 1)
        for j in range(cols):
            dfs(0, j)
            dfs(rows - 1, j)

        for i in range(rows):
            for j in range(cols):
                if board[i][j] == "N":
                    board[i][j] = "O"
                elif board[i][j] == "O":
                    board[i][j] = "X"


if __name__ == "__main__":
    solution1 = Solution()
    board = [
        ["X", "X", "X", "X"],
        ["X", "O", "O", "X"],
        ["X", "X", "O", "X"],
        ["X", "O", "X", "X"],
    ]
    solution1.solve(board)
    print(board)
