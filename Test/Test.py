
import TicTacToe
game = TicTacToe.TicTacToe()
#print(game.next())
game.next(0,0)
game.next(1,playnum=1)
game.next(2,0)
game.next(3,1)
game.next(4,1)
game.next(5,0)
game.next(6,0)
game.next(7,0)
game.next(8,1)
print(game.state)
print(game.final)
#game.clear()
game.next(0,0)
game.next(1,0)
game.next(2,0)
print(game.state)
print(game.final)