/**************************

**********************************************************************************/
#include"include.h"

//extern volatile u8 LPT_INT_count;
extern u16 piancha,flag_pid=0,END_MID,speed_max;
extern s16 OutData[4],MMA_Y,MMA_X,MMA_Z,qulvs;  
s16 SPEED=0,KPM=4,KDM=14,errm1=300,errm2=300,errm3=0,oldpwm=0;//�ٶȱ��������P I D,���P D ,�����������
double errs1=1,errs2=0,KPS=0.1000,KDS=0.06,KIS=0.000,olddir=0,KIM=0.5,accM=1.0,accS=0.0;
//���PD���� ��������ֵ
u16 plus=0,qipao=0;;
extern u8 END_MARK;
void ste_PD(s16 dir)//
{

    errs1=dir;
    accS += KIS*(float)(errs1-errs2);
    dir=DJ_center-(u16)(KPS*(errs1)+accS+KDS*(errs1-errs2));
    olddir=dir;
    spwm(dir);
    if(accS>400)accS=400;     
    if(-accS>400)accS=-400;
    if(boma_1)
    {
        LCD_P8X16NUM(0,7,(s16)dir,BLUE,YELLOW);
        LCD_P8X16NUM(14,7,(s16)qulvs,BLUE,YELLOW); 
    }
    errs2=errs1;
}

//���PID���� ��������ֵ
void mot_PID(s16 mspd)
{
    s16 KPM1=KPM;
    if(mspd<180&&END_MARK<2)mspd=180;
    //if(mspd<0)mspd=0;
    errm1 = mspd - SPEED; //������ 
    if(errm1<0)
        KPM1=KPM+2;
    else
        KPM1=KPM;
    KIM *= errm1;
    accM += KIM;
    mspd=KPM1*errm1+(s16)accM+KDM*(errm1-errm2)+oldpwm;
    if(mspd>=6999)//���ռ�ձȴ���10000 �����10000
        mspd=6999;
    else
    if(mspd<=-6999)
        mspd=-6999;
    
    mpwm(mspd);
    oldpwm=mspd;
    errm3=errm2;
    errm2=errm1;

    if(KIM>2000u)
    KIM=2000u;
}

//�ɵ���������ܳ�����
void cotrl(u16 dir,s16 mspd)
{   
    mot_PID(mspd);  
    ste_PD(dir);
}

//�ٶȼ�⣬����Ĵ���
void spd_check()
{
    u8 FRONT=1; //�����������������ת��ʱ����Ϊ��0�Ϳ��ԣ������ٸ�
    FRONT=PTA12_IN;
    if(FRONT==0)
        SPEED=0;
    else
    SPEED=LPTMR0_CNR;                                   //�����������������ֵ,  
    lptmr_counter_clean();                                  //����������������ֵ��������գ��������ܱ�֤����ֵ׼ȷ��
    plus+=SPEED;
    qipao+=SPEED;
    //MMA8451();

}

//���pwm�������ƣ���ֹ���
void mpwm(s16 pwm)
{

    if(pwm>=0) 
    {
        FTM_PWM_Duty(FTM0,CH4,pwm);
        FTM_PWM_Duty(FTM0,CH5,0);
    }
    else
    {
        FTM_PWM_Duty(FTM0,CH4,0);
        FTM_PWM_Duty(FTM0,CH5,-pwm);    
    }
    
}
void spwm(u16 pwm)
{
    if(pwm>DJ_scope+DJ_center)//���ƺ���
        pwm=DJ_scope+DJ_center;
    else 
    if(pwm<DJ_center-DJ_scope)
        pwm=DJ_center-DJ_scope;               
    FTM_PWM_Duty(FTM1,CH1,pwm);
}

void contrlss(void)
{
        
}