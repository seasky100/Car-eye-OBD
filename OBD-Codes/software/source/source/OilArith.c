
/* car-eye车辆管理平台 
 * car-eye车辆管理公共平台   www.car-eye.cn
 * car-eye开源网址:  https://github.com/Car-eye-admin
 * Copyright car-eye 车辆管理平台  2017 
 */
#include "includes.h"


float  DivedFlt(float a,float b)
{ return(a/b);}

float  MultiplyFlt(float x,u8 y)
{ return(x*y*y*y);}

float  MultiplyFlt2(float x,u8 y)
{ return(x*y*y);}

/**************************************************************************************************
** 函数名: EndDataProcess
** 输　入: float ProcVal
** 输　出: float  
** 功能描述: 在十分位上做四舍五入
**************************************************************************************************/

float  EndDataProcess(float ProcVal)
{  
  unsigned long  TempData;
  
  TempData = 10*ProcVal;
  if((10*ProcVal-(float)TempData) >=0.5)
     return ((float)ProcVal+0.1);
  else
     return ProcVal;
}
/**************************************************************************************************
** 函数名: Gas050fMoleDeno
** 输　入: u8 ans05,u8 ans0f
** 输　出: float
** 功能描述:  Gas支持0B不支持10的算法（PID05 < 0x69）
**************************************************************************************************/
float  Gas050fMoleDeno(u8 ans05,u8 ans0f)
{
   float RetVal,Deno,Mole;
   u16 temp,val_val;
   temp = ans0f * ans0f;
   val_val = ans05 * ans05;
   Mole = 153.41216 + 0.059116 * ans05 - 0.00136159 * val_val + MultiplyFlt(0.0000066 , ans05) +
            0.011321762 * ans0f - 0.0000220469 * temp;
   Deno = 1 + 0.0062988487*ans05 - 0.0000122777135 * val_val + MultiplyFlt(0.000000057258 , ans05) + 
            0.005807 * ans0f;
   RetVal = DivedFlt(Mole,Deno);
   return RetVal;
}
/***********************Gas支持0B不支持10的算法*********************/

/**************************************************************************************************
** 函数名: Gas0fNo05
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  Gas支持0B不支持10的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Gas0fNo05(u8 ans0f)
{
   float  RetVal,val_val;
   val_val = ans0f * ans0f;
   RetVal = 41.925705 - 0.14364455*ans0f + 0.00038105445 * val_val - MultiplyFlt(0.000000494596 ,ans0f);
   return RetVal;
}
/*************************************************************************************************/

/**************************************************************************************************
** 函数名: Diesel_Apid11MoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  diesel_a支持PID 11 不支持PID04  PID0B的算法（PID05 < 0x69）
**************************************************************************************************/
float  Diesel_Apid11MoleDeno(u8 ans05,u8 ans0f)
{
   float  RetVal,Deno,Mole;
   u16 val_val;
   val_val = ans05 * ans05;
   Mole = 38.594 - 0.033539*ans05 + 0.001 * val_val - MultiplyFlt(0.0000070566 ,ans05) -
            0.00015168*ans0f;
   Deno = RetVal = 1 + 0.00009592*ans05 + 0.0000299418 * val_val - MultiplyFlt(0.000000211126,ans05) + 
            0.001097*ans0f;
   RetVal = DivedFlt(Mole,Deno);
   return RetVal;
}
/**************************************************************************************************
** 函数名: Diesel_Apid0fNo05
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  diesel_a支持11的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Diesel_Apid0fNo05(u8 ans0f)
{

   float  RetVal;
   RetVal = 34.594488 - 0.0333595*ans0f + MultiplyFlt2(0.000023772 , ans0f);
   return RetVal;

}

/**************************************************************************************************
** 函数名: Diesel_Apid110bMoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  diesel_a支持PID 11，0B，不支持PID 04的算法（PID05 < 0x69）
**************************************************************************************************/
float  Diesel_Apid110bMoleDeno(u8 ans05,u8 ans0f)
{
   u16 val_val;
   float  RetVal,Mole,Deno;
   val_val = ans0f * ans0f;
   Mole = 30.858379 + 0.0020323334*ans05 - 0.020752317 * ans0f + 0.000146 * val_val -
            MultiplyFlt(0.0000003131,ans0f);
   Deno = 1 + 0.0011576*ans05 + 0.00036244 * ans0f + 0.00000508959*val_val - 
            MultiplyFlt(0.000000011,ans0f);
   RetVal = DivedFlt(Mole,Deno);
   return RetVal;
}
/**************************************************************************************************
** 函数名: Diesel_Apid110fNo05
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  diesel_a支持PID 11，0B，不支持PID 04的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Diesel_Apid110fNo05(u8 ans0f)
{

   float  RetVal;
   RetVal = 27.671978 - 0.026784*ans0f + MultiplyFlt2(0.00001950549 , ans0f);
   return RetVal;

}
/**************************************************************************************************
** 函数名: Diesel_Apid04No110bMoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  diesel_a支持PID 04，不支持PID 11,0b的算法（PID05 < 0x69）
**************************************************************************************************/
float  Diesel_Apid04No110bMoleDeno(u8 ans05,u8 ans0f)
{
   u16  val_val;
   float  RetVal,Mole,Deno;
   val_val = ans05 * ans05;
   Mole = 58.152754 - 0.0049*ans05 + 0.00024833 * val_val - MultiplyFlt(0.0000023999,ans05) +  
            0.00176481* ans0f;
   Deno = 1 + 0.001*ans05 + 0.000005274186 * val_val - MultiplyFlt(0.00000005135,ans05) + 
            0.00114157*ans0f;
   RetVal = DivedFlt(Mole,Deno);
   return RetVal;
}
/**************************************************************************************************
** 函数名: Diesel_Apid04No110b
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  diesel_a支持PID 04，不支持PID 11,0b的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Diesel_Apid04No110b(u8 ans0f)
{

   float  RetVal;
   RetVal = 52.072955 - 0.05021*ans0f + MultiplyFlt2(0.00003635531 , ans0f);
   return RetVal;
}
/**************************************************************************************************
** 函数名: Diesel_Apid040bNo11MoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  diesel_a支持PID 04，0b,不支持PID 11的算法（PID05 < 0x69）
**************************************************************************************************/
float  Diesel_Apid040bNo11MoleDeno(u8 ans05,u8 ans0f)
{
   u16 val_val;
   float  RetVal,Mole,Deno;
   val_val = ans0f * ans0f;
   Mole = 55.785999 + 0.004132*ans05 - 0.02709* ans0f + 0.00012342*val_val - MultiplyFlt(0.0000001466,ans0f);  
   Deno = 1 + 0.0011720288*ans05 + 0.00058 * ans0f + 0.00000210258*val_val - 
            MultiplyFlt(0.0000000020452288,ans0f);
   RetVal = DivedFlt(Mole,Deno);
   return RetVal;
}

/**************************************************************************************************
** 函数名: Diesel_Apid040bNo11
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  diesel_a支持PID 04，0b,不支持PID 11的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Diesel_Apid040bNo11(u8 ans0f)
{

   float  RetVal;
   RetVal = 49.990554 - 0.048198*ans0f + MultiplyFlt2(0.0000351 , ans0f);
   return RetVal;
}
/**************************************************************************************************
** 函数名: Diesel_Apid0411No0bMoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  diesel_a支持PID 04，11,不支持PID 0b的算法（PID05 < 0x69）
**************************************************************************************************/
float  Diesel_Apid0411No0bMoleDeno(u8 ans05,u8 ans0f)
{
   u16 val_val;
   float  RetVal,Mole,Deno;
   val_val = ans0f * ans0f;
   Mole = 58.147449 + 0.0042625*ans05 + 0.0015859* ans0f - 0.0000505285*val_val + 
          MultiplyFlt(0.00000003656028,ans0f);  
   Deno = 1 + 0.0011847526*ans05 + 0.0011392162 * ans0f - 0.00000092619278*val_val;
   RetVal = DivedFlt(Mole,Deno);
   return RetVal;
}
/**************************************************************************************************
** 函数名: Diesel_Apid0411No0b
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  diesel_a支持PID 04，11,不支持PID 0b的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Diesel_Apid0411No0b(u8 ans0f)
{

   float  RetVal;
   RetVal = 52.064713 - 0.049797314*ans0f + MultiplyFlt2(0.000034676435 , ans0f);
   return RetVal;

}
/**************************************************************************************************
** 函数名: Diesel_Apid04110bMoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  diesel_a支持PID 04,11,0b的算法（PID05 < 0x69）
**************************************************************************************************/
float  Diesel_Apid04110bMoleDeno(u8 ans05,u8 ans0f)
{
   u16 val_val;
   float  RetVal,Mole,Deno;
   val_val = ans0f * ans0f;
   Mole = 74.396011 + 0.0010723933*ans05 - 0.0071256761* ans0f - 0.000032767687*val_val +
            MultiplyFlt(0.00000023357,ans0f);  
   Deno = 1 + 0.0011102853*ans05 + 0.001008815 * ans0f - 0.00000077565094*val_val + 
            MultiplyFlt(0.00000000440857,ans0f);
   RetVal = DivedFlt(Mole,Deno);
   return RetVal;
}
/**************************************************************************************************
** 函数名: Diesel_Apid04110b
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  diesel_a支持PID 04,11,0b的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Diesel_Apid04110b(u8 ans0f)
{

   float  RetVal;
   RetVal = 66.673993 - 0.0642327*ans0f + MultiplyFlt2(0.000046031746 , ans0f);
   return RetVal;
}
/*************************************************************************************************/

/**************************************************************************************************
** 函数名: Diesel_Bpid11NO040bMoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  diesel_b支持PID 11,不支持PID 04,0b的算法（PID05 < 0x69）
**************************************************************************************************/
float  Diesel_Bpid11NO040bMoleDeno(u8 ans05,u8 ans0f)
{
   u16 val_val;
   float  RetVal,Mole,Deno;
   val_val = ans05 * ans05;
   Mole = 21.181917 - 0.0011100972*ans05 + 0.000033538432* val_val - MultiplyFlt(0.00000028047,ans05)- 
            0.00117847*ans0f;  
   Deno = 1 + 0.00107399*ans05 + 0.0010260795 * ans0f; 
   RetVal = DivedFlt(Mole,Deno);
   return RetVal;
}
/**************************************************************************************************
** 函数名: Diesel_Bpid11No040b
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  diesel_b支持PID 11,不支持PID 04,0b的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Diesel_Bpid11No040b(u8 ans0f)
{

   float  RetVal;
   RetVal = 18.994 - 0.018503419*ans0f + MultiplyFlt2(0.000014102564 , ans0f);
   return RetVal;

}
/**************************************************************************************************
** 函数名: Diesel_Bpid0b11NO04MoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  diesel_b支持PID 0b,11,不支持PID 04的算法（PID05 < 0x69）
**************************************************************************************************/
float  Diesel_Bpid0b11NO04MoleDeno(u8 ans05,u8 ans0f)
{
   u16  val_val;
   float  RetVal,Deno,Mole;
   val_val = ans0f * ans0f;
   Mole = 26.07 + 0.0027473415*ans05 - 0.0046941416* ans0f - 0.0000245465*val_val +
            MultiplyFlt(0.0000001236951,ans0f);  
   Deno = 1 + 0.00120532*ans05 + 0.00093805756 * ans0f - 0.0000017324418*val_val + 
            MultiplyFlt(0.000000007155579,ans0f); 
   RetVal = DivedFlt(Mole,Deno);
   return RetVal;
}
/**************************************************************************************************
** 函数名: Diesel_Bpid0b11No04
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  diesel_b支持PID 0b,11,不支持PID 04的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Diesel_Bpid0b11No04(u8 ans0f)
{

   float  RetVal;
   RetVal = 12.69475 - 0.012708*ans0f + MultiplyFlt2(0.00001092796 , ans0f);
   return RetVal;

}
/**************************************************************************************************
** 函数名: Diesel_Bpid04no110bMoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  diesel_b支持PID 04,不支持PID 11,0b的算法（PID05 < 0x69）
**************************************************************************************************/
float  Diesel_Bpid04no110bMoleDeno(u8 ans05,u8 ans0f)
{
   u16 val_val;
   float  RetVal,Mole,Deno;
   val_val = ans05 * ans05;
   Mole = 19.94121 + 0.0074937*ans05 - 0.00006553466* val_val - MultiplyFlt(0.000000276,ans05) - 
            0.0012801*ans0f;  
   Deno = 1 + 0.0015908*ans05 - 0.0000061641 * val_val + 0.001021893*ans0f; 
   RetVal = DivedFlt(Mole,Deno);
   return RetVal;
}
/**************************************************************************************************
** 函数名: Diesel_Bpid04no110b
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  diesel_b支持PID 04,不支持PID 11,0b的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Diesel_Bpid04no110b(u8 ans0f)
{

   float  RetVal;
   RetVal = 17.881929 - 0.017434298*ans0f + MultiplyFlt2(0.0000135177 , ans0f);
   return RetVal;

}
/**************************************************************************************************
** 函数名: Diesel_Bpid04110bMoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  diesel_b支持PID 04,11,0b的算法（PID05 < 0x69）
**************************************************************************************************/
float  Diesel_Bpid04110bMoleDeno(u8 ans05,u8 ans0f)
{
   u16 val_val;
   float  RetVal,Mole,Deno;
   val_val = ans0f * ans0f;
   Mole = 25.5201 - 0.0071535275*ans05 - 0.0037562287* ans0f + 0.000036602*val_val;  
   Deno = 1 + 0.00078248997*ans05 + 0.00089986 * ans0f + 0.0000018606594*val_val;
   RetVal = DivedFlt(Mole,Deno);
   return RetVal;
}
/**************************************************************************************************
** 函数名: Diesel_Bpid04110b
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  diesel_b支持PID 04,11,0b的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Diesel_Bpid04110b(u8 ans0f)
{

   float  RetVal;
   RetVal = 22.885478 - 0.022563566*ans0f + MultiplyFlt2(0.00001816 , ans0f);
   return RetVal;

}
/**************************************************************************************************
** 函数名: Diesel_Bpid040bno11MoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  diesel_b支持PID 04,0b,不支持PID 11的算法（PID05 < 0x69）
**************************************************************************************************/
float  Diesel_Bpid040bno11MoleDeno(u8 ans05,u8 ans0f)
{
   u16  val_val;
   float  RetVal,Mole,Deno;
   val_val = ans0f * ans0f;
   Mole = 47.938475 + 0.007206053*ans05 - 0.0015279574* ans0f - 0.000031507784*val_val + 
            MultiplyFlt(0.000000040676858,ans0f);  
   Deno = 1 + 0.0012803888*ans05 + 0.0010731508 * ans0f - 0.0000006079741*val_val;
   RetVal = DivedFlt(Mole,Deno); 
   return RetVal;
}
/**************************************************************************************************
** 函数名: Diesel_Bpid040bno11
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  diesel_b支持PID 04,0b,不支持PID 11的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Diesel_Bpid040bno11(u8 ans0f)
{

   float  RetVal;
   RetVal = 42.899307 - 0.0410544*ans0f + MultiplyFlt2(0.000028583 , ans0f);
   return RetVal;

}
/**************************************************************************************************
** 函数名: Diesel_Bpid0411no0bMoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  diesel_b支持PID 04,11,不支持PID 0b的算法（PID05 < 0x69）
**************************************************************************************************/
float  Diesel_Bpid0411no0bMoleDeno(u8 ans05,u8 ans0f)
{
   u16  val_val;
   float  RetVal,Mole,Deno;
   val_val = ans05 * ans05;
   Mole = 21.192099 - 0.00065385636*ans05 - 0.00005387275* val_val + MultiplyFlt(0.00000037418334,ans05) - 
            0.00046397611*ans0f;  
   Deno = 1 + 0.00111644*ans05 - 0.000004410657*val_val + MultiplyFlt(0.000000029766667, ans05) + 
            0.0010687*ans0f; 
   RetVal = DivedFlt(Mole,Deno); 
   return RetVal;
}
/**************************************************************************************************
** 函数名: Diesel_Bpid0411no0b
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  diesel_b支持PID 04,11,不支持PID 0b的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Diesel_Bpid0411no0b(u8 ans0f)
{

   float  RetVal;
   RetVal = 18.83142 - 0.017718*ans0f + MultiplyFlt2(0.0000110848 , ans0f);
   return RetVal;

}
/*************************************************************************************************/
/**************************************************************************************************
** 函数名: Hybrid_pid0bno10MoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  Hybrid支持PID 0b,不支持PID 10的算法（PID05 < 0x69）
**************************************************************************************************/
float  Hybrid_pid0bno10MoleDeno(u8 ans05,u8 ans0f)
{
   u16  val_val;
   float  RetVal,Mole,Deno;
   val_val = ans0f * ans0f;
   Mole = 151.2866 - 0.029747*ans05 + 0.058845836* ans0f - 0.0001052998*val_val; 
   val_val = ans05 * ans05;
   Deno = 1 + 0.00550676*ans05 + 0.00000158721*val_val - 0.000000023402122* val_val * ans05 + 0.0062577*ans0f; 
   RetVal = DivedFlt(Mole,Deno);
   return RetVal;
}
/***************************hybrid*********************************/

/**************************************************************************************************
** 函数名: Hybrid_pid0bno10
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  Hybrid支持PID 0b,不支持PID 10的算法（PID05 >= 0x69）
**************************************************************************************************/
float  Hybrid_pid0bno10(u8 ans0f)
{

   float  RetVal,val;
   val = ans0f * ans0f;
   RetVal = 94.34832 - 0.322886*ans0f + 0.0008574 * val - MultiplyFlt(0.000001120978,ans0f);
   return RetVal;

}
/*************************************************************************************************/
/**************************************************************************************************
** 函数名: Hybrid_pid0bno10MoleDeno
** 输　入: u8 ans05, u8 ans0f
** 输　出: float
** 功能描述:  LPG支持PID 0b,不支持PID 10的算法（PID05 < 0x69）
**************************************************************************************************/
float  LPG_pid0bno10MoleDeno(u8 ans05,u8 ans0f)
{
   u16  val_val;
   float  RetVal,Mole,Deno;
   val_val = ans0f * ans0f;
   Mole = 99.210368 + 0.0022374773*ans05 - 0.0092605809* ans0f + 0.000088635755*val_val - 
            MultiplyFlt(0.00000023205,ans0f);  
   Deno = 1 + 0.0058038967*ans05 + 0.0056114576*ans0f + 0.0000015446* val_val - 
            MultiplyFlt(0.000000004309,ans0f); 
   RetVal = DivedFlt(Mole,Deno); 
   return RetVal;
}
/**************************************************************************************************
** 函数名: LPG_pid0bno10
** 输　入: u8 ans0f
** 输　出: float
** 功能描述:  LPG支持PID 0b,不支持PID 10的算法（PID05 >= 0x69）
**************************************************************************************************/
float  LPG_pid0bno10(u8 ans0f)
{

   float  RetVal,val;
   val = ans0f * ans0f;
   RetVal = 61.669837 - 0.2109949*ans0f + 0.000559399 * val - MultiplyFlt(0.00000072852463,ans0f);
   return RetVal;

}

/**************************************************************************************************
** 函数名: Oil_Arith_Proc
** 输　入: PID$05,PID$05,PID$05,PID$05,PID$05,PID$05,PID$05,PID$05,
** 输　出: float 及时油耗
** 功能描述: 
**************************************************************************************************/
//time 为ms//
/*
空挡滑行的时候确实是按照怠速供油，但是你看到的是怠速供油脉宽除以
您的速度以后的读数（也就是您说的比较高的数字），这个时候数字后面
的单位是L/KM ，而您所说的0.7也好0.5也好是您的车停下来的数字，这个时候
的速度为0，所以您看到的那个数值的单位是L/H，也就是“升/小时”。因为
您的车停下来的时候瞬时油耗是无限大的，您不管喷几箱油车都是没行驶
的，所以瞬时油耗的车在时速5公里以下的时候都是按时间，也就是小时计
算的。所以您看到的两种情况下怠速的油耗不同也是理所应当的
*/
/*
一、平均油耗
　　平均油耗就是一般所说的油耗，定义为车辆行驶单位路程时所用燃油的量，常用的单位为升/百公里。
计算公式：
　　平均油耗＝燃油量÷用这些燃油行驶的路程　或　＝燃油量/用这些燃油行驶的路程
二、瞬时油耗
　　这是汽车开始出现行车电脑后出现的一个技术名词，严格的物理定义是，在无限小（瞬时）的时间内，
汽车油耗的燃油量和用这些燃油行驶过的路程之比。因为是无限小时间，所以在无限小的时间内车辆消耗
的燃油量和行驶的路程都是无限小，所以这里的瞬时油耗是无限小与无限小之比，这是一个极限问题，在
极限问题中，无限小除以无限小是可以有一个固定值（当然也可以有其它结果，如无限大，无限小，但对
于汽车油耗，是一个固定值）。
　　公式：
　　瞬时油耗＝在瞬时时间内的燃油消耗量/在此瞬时时间内车辆用这些燃油行驶过的路程
　　无限小的时间间隔无法实现，实际上的瞬时油耗测试，大多用二秒左右作为测试时间间隔，所以现代
汽车行车电脑给出的瞬时油耗值实际上是以二秒为时间单位的平均油耗值。
　　以上定义和公式可以帮助我们理解和解释一些问题，下面给出常见疑问的解答。
1、　问：为什么行车电脑显示起步时瞬时油耗很大？
　　　答：油耗是用油量和用这些油行驶路程的比，通俗的看，油耗是一个分数的值，分子是用油量（行
车电脑实际是用二秒平均油耗作为瞬时油耗的，有一实际值），分母是用这些油行驶的距离。汽车起步时
行驶路程很短，相当于分母很小，所以分数的值，就是油耗很大。起步后，随着行驶距离的增加，瞬时油
耗会很快下降。
2、问：怠速时怎样计算怠速油耗？
　　答：行车电脑实际是用二秒平均油耗作为瞬时油耗的，所以在怠速情况下，用油量一定，相当于分子
有一定的值，而汽车行驶距离为零，相当于分母为零，这样分数的值将为无穷大，公式已经失去意义，行
车电脑显示的瞬时油耗也为无穷大，这显然与事实不符，因为无穷大就意味着油箱里的油在极短时间内就
用完了！所以在怠速情况下，应该用单位时间内的用油量标准来衡量油耗的高低，常用的单位为升/每小时
，事实上，有的汽车的行车电脑在怠速时会自动转换成升/每小时为单位。对于远景这样不能转换的车辆，
可以参考我的帖子进行计算。
http://club.autohome.com.cn/bbs/thread-c-474-1522662-1.html
3、问：为什么一般情况下低挡油耗高，高挡位油耗低？
　　答：首选要知道一个基本原理，也是基本前提，就是在汽车挡位一定的情况下，发动机转速与行驶速
度成正比，因为各挡位变速比不同，所以在发动机转速一定的情况下，汽车有不同的行驶速度，这就是我
们知道的低挡走得慢，高挡位走得快。而发动机油耗与转速及输出功率有关，简单粗略地可以看作是与转
速成正比。假设我们用发动机2000转速行进，用一挡的速度必然低于二挡，二挡低于三挡等等，在一定时间
内，既然发动机转速不变，从上面油耗计算公式，相当于油耗这个分数的分子即燃油消耗量一样，而用一
挡行驶的距离最短，即分母最小，所以油耗，即这个分数的值最大。从另一方面，我们还可以这样理解，
假如一、二两挡的速度相差一倍，那么要跑完相同的路程，用一挡就要比二挡多用一倍时间，也就是说发
动机要多工作一掊的时间，那油耗高就是必然的了。
4、问：为什么跑长途油耗低，城区街道行进油耗高？
　　答：从问题3我们可以看到挡位与油耗的关系，在城区用速度慢，用低挡位多，油耗高是必然，另一方
面，在城区不要不断起步，加速，刹车，这些都要多耗油，当然会使油耗进一步升高，如果道路非常拥挤
，只能用很慢的速度行进且频繁停起步，那么油耗将达到非常惊人的程度。
5、问：瞬时油耗与平均油耗两个数值计算时，是两个系统分别计算？还是平均油耗来自于瞬时油耗的累加
？
　　答：行车电脑瞬时油耗计算实际是二秒平均油耗，因此我认为将此油耗叠加并用时间加权即可，没有
必要用两个系统。
6、问：平均油耗显示的数值是每次启动后的计算？还是上次复位后累计计算？
　　答：不是，远景车是复位后才重新计算，显示值为上次复位至本次读取时间段内（或这段行驶里程内
）的平均油耗
*/


float Oil_Arith_PID10(float maf,u32 time)
{
	float temp_oil;

	temp_oil = maf*0.3352349; //*99.9/298//
	while(temp_oil > 219.5)
	{
		temp_oil -= 219.5; //结果大于219.6，则减去219.6
	}
	
	temp_oil *= (((float)time/1000)/3600);

	return temp_oil;
}

						   //0x0c//0x05//0x0f//   0x0b//  
float Oil_Arith_PID0b(float rpm,float etc,float iat,float map,u32 time)
{
	float temp_oil,tempfloat;

	tempfloat = (float)(rpm/16384.0)*(ObdData.EngineL/3.0);

	temp_oil = map/255;
	temp_oil *= DivedFlt(tempfloat,3.3); 

	if(etc<65.000000)	//<65°C//
	{
		temp_oil *= Gas050fMoleDeno(etc + 40.0,iat + 40.0);
		temp_oil *= 12.94615;
	}
	else
	{
		temp_oil *= Gas0fNo05(iat + 40.0);
		temp_oil *= 29.6;
	}

	while(temp_oil > 219.5)
	{
		temp_oil -= 219.5; //结果大于219.6，则减去219.6
	}

	temp_oil *= (float)(((float)time/1000.0)/3600.0);

	return temp_oil;
}


float Oil_Arith_PID43(float rpm,float EngineL,float load_lbs)
{
	float val;
	//MyPrintf("EngineL:%f\r\n",EngineL);
	//MyPrintf("load_lbs:%f\r\n",load_lbs);
	//MyPrintf("rpm:%f\r\n",rpm);
	
	val = EngineL * load_lbs * rpm*0.009867;

	//MyPrintf("43:%fg/s\r\n",val);
	return val;
}



