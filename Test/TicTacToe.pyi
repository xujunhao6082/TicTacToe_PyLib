"""这个模块用于创建TicTacToe的游戏对象"""
__all__ = ['TicTacToe']
class TicTacToe:
    """TicTacToe game object"""
    state:tuple[tuple[int,int,int],tuple[int,int,int],tuple[int,int,int]]
    """游戏的状态,记录了各个位置的玩家号,-1为无占用,先行号后列号,该属性只读"""
    count:int
    """已用位置计数"""
    final:int
    """最终结果,3为平局,-1为进行中,0/1则为赢得游戏的玩家号"""
    def next(posision,playnum) -> None: 
        """放棋子,前参数为位置(posision)(0~8),后参为玩家号(playnum)为0或1,当终局后再进行操作会触发异常,位置号同小键盘数字减一"""
        ...
    def clear() -> None:
        """清理,重新开始一局游戏"""
        ...
    def __init__() -> None: ...