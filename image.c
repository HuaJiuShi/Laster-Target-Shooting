#include "image.h"
#include "ov7725.h"

#define START_LINE 0

s16 left[IMG_H]={0};		
s16 right[IMG_H]={0};		
float middle_x=0,middle_y=0;
s16 L_M_X=CAMERA_W,L_M_Y=0,R_M_X=0,R_M_Y=0;

void findborder(void)   //寻找边线
{
    s16 i;
    s16 row=CAMERA_H;            //120行
    u8  Y_flag0=CAMERA_W,Y_flag1=0;          //Y轴的有效点数范围
    s16 n1,n2;
    
    for(i=0;i<IMG_H;i++)   //每次来都要清零
    {
      left[i]=0;
      right[i]=0;
      L_M_X=CAMERA_W;
      L_M_Y=0;
      R_M_X=0;
      R_M_Y=0;
    }
    
    
    //先将整幅图像的边线采集出来
    for(row=10;row<IMG_H-10;row++)
    {
      for(i=6;i<IMG_W-6;i++)    //X轴（160列）所有的点都处理
      {
         if(img_ready[row][i]==0&&img_ready[row][i+1])       //连续5个点为白点判断为白盘
            break;
      }
      left[row]=i;
      for(i=IMG_W-6;i>5;i--)    //X轴（160列）所有的点都处理
      {
         if(img_ready[row][i-1]&&img_ready[row][i]==0)       //连续三个点为白点判断为白盘
            break;
      }
      right[row]=i;
      
      n1=right[row];
      n2=left[row];
      
      if(n2<=CAMERA_W/2 && n1==5)
      {
          right[row] = left[row];
          left[row] = 2;
      }
      if(n2>=CAMERA_W/2 && n1==CAMERA_W-5)
      {
          left[row] = right[row];
          right[row] = CAMERA_W-2;
      }
      
      if(row<=Y_flag0)
          Y_flag0 = row;
      if(row>=Y_flag1)
          Y_flag1 = row;
    }
      

    //开始算圆心
    for(i=Y_flag0;i<Y_flag1;i++)
    {
        if(left[i]<=L_M_X)
        {
            L_M_X = left[i];
            L_M_Y = i;
        }
        if(right[i]>=R_M_X)
        {
            R_M_X = right[i];
            R_M_Y = i;
        }
    }
    
    middle_x = (L_M_X+R_M_X)/2.0;
    middle_y = (L_M_Y+R_M_Y)/2.0;
}