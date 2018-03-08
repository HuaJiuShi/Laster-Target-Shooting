#include "image.h"
#include "ov7725.h"

#define START_LINE 0

s16 left[IMG_H]={0};		
s16 right[IMG_H]={0};		
float middle_x=0,middle_y=0;
s16 L_M_X=CAMERA_W,L_M_Y=0,R_M_X=0,R_M_Y=0;

void findborder(void)   //Ѱ�ұ���
{
    s16 i;
    s16 row=CAMERA_H;            //120��
    u8  Y_flag0=CAMERA_W,Y_flag1=0;          //Y�����Ч������Χ
    s16 n1,n2;
    
    for(i=0;i<IMG_H;i++)   //ÿ������Ҫ����
    {
      left[i]=0;
      right[i]=0;
      L_M_X=CAMERA_W;
      L_M_Y=0;
      R_M_X=0;
      R_M_Y=0;
    }
    
    
    //�Ƚ�����ͼ��ı��߲ɼ�����
    for(row=10;row<IMG_H-10;row++)
    {
      for(i=6;i<IMG_W-6;i++)    //X�ᣨ160�У����еĵ㶼����
      {
         if(img_ready[row][i]==0&&img_ready[row][i+1])       //����5����Ϊ�׵��ж�Ϊ����
            break;
      }
      left[row]=i;
      for(i=IMG_W-6;i>5;i--)    //X�ᣨ160�У����еĵ㶼����
      {
         if(img_ready[row][i-1]&&img_ready[row][i]==0)       //����������Ϊ�׵��ж�Ϊ����
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
      

    //��ʼ��Բ��
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