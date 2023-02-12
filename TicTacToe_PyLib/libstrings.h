#pragma once
#define MODULE_NAME "TicTacToe"
#define MODULE_DOC "这个模块用于创建TicTacToe的游戏对象"
#define CLASS_NAME "TicTacToe.TicTacToe"
#define CLASS_DOC "TicTacToe game object"
#define CLASS_STATE_NAME "state"
#define CLASS_STATE_DOC "游戏的状态,先行号后列号,该属性只读"
#define CLASS_NEXT_NAME "next"
#define CLASS_NEXT_FIRSTARG "first"
#define CLASS_NEXT_SECONDARG "second"
#define CLASS_NEXT_DOC "放棋子,前参数(first)为先手位置,后参数(second)反之,若位置已使用或相等则会抛出异常,默认-1表弃权,输入数字同小键盘数字减一,返回一个数值,若为-1则进行中,0为平局,1为先手赢,2为后手赢,当仅检查状态时无需入参"
#define EXP_INDEX_USED "The Index is used"
#define EXP_INDEX_OVER "The Index out of range"
#define EXP_ARGS "Parameter format is not correct"
#define EXP_SETSTATE "Attribute 'state' is read-only"