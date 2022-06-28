#ifndef YDGLOBAL_H
#define YDGLOBAL_H

#include <QString>

class YDModule;

namespace Character {
enum Power {
  //权限管理
  Authority_Show = 0x00,
  Character_Show = 0x01,
  Charater_Op = 0x02,
  User_Show = 0x04,
  USer_Op = 0x08,

  //设备管理
  Device_Show = 0x10,
  Device_Op = 0x20,

  //变量管理
  Variable_Show = 0x40,
  Variable_Op = 0x80,

  //任务
  Task_Show = 0x100,
  Task_Op = 0x200,

  //插件
  Plug_Show = 0x400,
  Plug_Op = 0x800,

  //访问者
  Visitor = Authority_Show | Character_Show | User_Show | Device_Show |
            Variable_Show | Task_Show | Plug_Show,

  //操作员
  Operator = Visitor | Device_Op | Variable_Op | Task_Op | Plug_Op,

  //管理员
  Admin = Operator | Charater_Op | USer_Op
};
Q_DECLARE_FLAGS(Powers, Power)

}  // namespace Character
Q_DECLARE_OPERATORS_FOR_FLAGS(Character::Powers)

namespace Window {
enum Style {
  // MainWindow Style
  MainWListBtnDefault = 0,
  MainWListBtnSelect,
  MainWListBtnBackground,
  MainWindow,
};
}  // namespace Window

namespace Language {
enum Country {
  Chinese = 0,
  English,
  French,
  Japanese,
  korean,
  Hindi,
  Russian,
  Arabic
};

}

namespace Module {
enum Type {
  //运动
  Motion = 0,
  Abs_Motion,    //绝对运动
  Rel_Motion,    //相对运动
  Jog_Motion,    // Jog运动
  Mul_Motion,    //多轴运动
  BackZ_Motion,  //回零运动
  Stop_Motion,   //停止运动
  Wait_Motion,   //运动到位等待

  // I/O
  IO = 40,
  Control_DO,  //控制DO输出
  Control_AO,  //控制AO输出
  Cylinder,    //气油缸

  //控制
  Control = 80,
  Condition,  //条件
  If_Condition,
  IfElse_Condition,  // IF-ELSE判定条件
  Times_Loop,        //次数循环
  Condition_Loop,    //条件循环
  Jump_Loop,         //跳出循环
  Delay_Wait,        //延时等待

  //其他
  Other = 240,
  SubTask_Call,   //子例程调用
  Programable,    //可编程模块
  Wait_Complete,  //等待任务完成
  Alarm_Confirm,  //报警确认
  Jump_To_Task    //跳转任务
};
}

//日志打印信息等级
enum LogLevel { Trace = 0, Debug, Info, Warning, Error, Fatal };

union YDModuleCast {
  YDModule *ptr;
  qintptr i;
};

#endif  // YDGLOBAL_H
