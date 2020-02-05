#define E 206000//弹性模量
#define pi 3.141593
#include <stdio.h>
#include<math.h>
int main()
{
	double n,fc,fd,L,fa,Fw2;//求静挠度所需变量
	double J0,k,s,c,sigma,W0_min,sigma_w,hp,n1,n0,h,b,num;//求断面尺寸，片数所需变量
    double Length[5]={0},x,y;int i;//求各片长度所需变量
	double H[5]={0},f_delta,R[5]={0},stress_pre[5]={0};//计算自由状态弧高和曲率半径所需变量
    double R0_check,H_check;//钢板弹簧总成弧高校核所需变量	
	double sigma_max,m2,l1,l2,fai,W0,c_distance,Fx,sigma_D,D_max,Fs,sigma_z,d_xiao,kd,sigma_uneven;//校核强度所需变量
	double ms,psi,omega,alpha,a,delta,vx,F0,delta_s,D_cylinder,p,lambda,Dc;//减振器的选择
	
	//计算悬架静挠度

	printf("计算悬架静挠度\n");
	n=1.4;printf("n=%lf\n",n);//后悬架偏频
    fc=(4.985/n)*(4.985/n)*10;printf("fc=%lf\n",fc);//后悬架挠度
    Fw2=4743.14;//后悬架单侧弹簧受到的悬上重量
	c=Fw2/fc;printf("c=%lf\n",c);//后悬架刚度
    fd=70;//动挠度
	fa=15;//满载弧高
	L=1200;//板簧长度
	printf("\n");


    ////断面尺寸，片数确定////

    printf("断面尺寸，片数确定\n");
	s=104;//U型螺栓中心距
    k=0.5;//刚性夹紧
    n1=0;n0=5;//没有重叠片，预计为5片
	sigma=1.5/(1.04*(1+0.5*n1/n0));printf("sigma=%lf\n",sigma);//挠度增大系数
    J0=((L-k*s)*(L-k*s)*(L-k*s)*c*sigma)/48/E;printf("J0=%lf\n",J0);//求总惯性力矩
    printf("\n");

	sigma_w=550;//许用弯曲应力
	W0_min=Fw2*(L-k*s)/4/sigma_w;printf("W0=%lf\n",W0_min);//总截面系数

	hp=2*J0/W0_min;printf("hp=%lf\n",hp);//平均厚度

	num=5;//片数
	b=60;//片宽
	h=pow(12*J0/num/b,0.333333); printf("h=%lf\n",h);//片厚
	h=7; printf("the chosen h is %lf\n",h);//设计中选择的厚度
	J0=num*b*h*h*h/12;printf("实际总惯性矩J0=%lf\n",J0);
	printf("\n");


	////各板簧长度确定////
   
	printf("各板簧长度确定\n");
	y=num*h*h*h;
	for(i=0;i<num;i++)
	{		
		x=(L-s)/2/num/h/h/h*y+s/2;
		Length[i]=2*x;printf("Length[%d]=%lf\n",i+1,Length[i]);//求出各片片厚
		y=y-h*h*h;
    }
	printf("圆整后各板簧长度\n");
	Length[0]=1200;printf("Length[%d]=%lf\n",1,Length[0]);
	Length[1]=980;printf("Length[%d]=%lf\n",2,Length[1]);
	Length[2]=760;printf("Length[%d]=%lf\n",3,Length[2]);
	Length[3]=540;printf("Length[%d]=%lf\n",4,Length[3]);
    Length[4]=320;printf("Length[%d]=%lf\n",5,Length[4]);
    printf("\n");

    
	////计算自由状态弧高和曲率半径////

    printf("计算自由状态弧高和曲率半径所需\n");
    f_delta=s*(3*L-s)*(fa+fc)/2/L/L;printf("△f=%lf\n",f_delta);//U形螺栓夹紧后形成的高度变化
	H[0]=f_delta+fc+fa;printf("H[0]=%lf\n",H[0]);//板簧自由状态下的弧高
    R[0]=L*L/8/H[0];printf("R[0]=%lf\n",R[0]);//主片在自由状态下的曲率半径
    stress_pre[0]=0-60;//输入各片预应力
	stress_pre[1]=0-30;
	stress_pre[2]=0;
	stress_pre[3]=30;
	stress_pre[4]=60;
	for(i=1;i<num;i++)
	{
		R[i]=R[0]/(1+(2*R[0]*stress_pre[i])/E/h);
		printf("R[%d]=%lf\n",i+1,R[i]);
		H[i]=Length[i]*Length[i]/8/R[i];
	    printf("H[%d]=%lf\n",i+1,H[i]);
	}
	printf("\n");

	
	////钢板弹簧总成弧高的校核////

    printf("钢板弹簧总成弧高的校核\n");
	x=0;y=0;
	for(i=0;i<num;i++)
	{
		x=x+Length[i];
		y=y+Length[i]/R[i];
	}
	R0_check=x/y;
	H_check=L*L/8/R0_check;
	printf("H_check=%lf\n",H_check);
	printf("\n");
	
	
	////强度验算////

    printf("强度验算\n");
	m2=1.25;//后轴负荷转移系数
	l1=0.5*Length[0];l2=0.5*Length[0];//板簧前后段长度
	fai=0.7;//道路附着系数
	W0=num*b*h*h/6;printf("W0=%lf\n",W0);//总截面系数
	c_distance=300;//弹簧固定点到路面的距离
	sigma_max=Fw2*m2*l1*(l2+fai*c_distance)/(l1+l2)/W0+Fw2*m2*fai/b/h;//校核驱动时后板簧最大应力
	printf("sigma_max=%lf\n",sigma_max);
	
	kd=(fc+fd)/fc;printf("kd=%lf\n",kd);
	sigma_uneven=kd*Fw2*l1*l2/(l1+l2)/W0;
	printf("经过不平路面时受到最大应力sigma_uneven=%lf\n",sigma_uneven);//校核经过不平路面时受到最大应力


	Fx=Fw2*fai*m2;//单侧板簧受到的纵向力
	sigma_D=350;//计算卷耳时所用的许用应力
	D_max=h*h*b*sigma_D/3/Fx-h/3;	printf("吊耳最大内径D_max=%lf\n",D_max);//卷耳内径
    Fs=0.5*Fw2*m2;
	sigma_z=7;
	d_xiao=Fs/b/sigma_z;printf("弹簧销最小内径D_xiao=%lf\n",d_xiao);//弹簧销内径
	printf("\n");


	////减振器参数的确定////

	printf("减振器参数的确定\n");
	ms=483.5;//后悬架单侧所受到的簧载质量
    psi=0.24;//相对阻尼系数，ψs=0.32,ψY=0.16
	alpha=pi*40/180;
	omega=sqrt(1000*c/ms);	printf("omega=%lf\n",omega);
    //delta=2*psi*ms*omega; printf("delta=%lf\n",delta);//求出阻尼系数
	vx=0.04*omega*cos(alpha);//卸荷速度
	printf("vx=%lf\n",vx);
	delta=psi*2*ms*omega/cos(alpha)/cos(alpha);printf("delta=%lf\n",delta);//求出阻尼系数
    F0=delta*vx;	printf("F0=%lf\n",F0); //减振器最大阻力
	p=3;//工作缸最大允许压力
	lambda=0.4;//连杆直径与缸筒直径之比
	D_cylinder=sqrt(4*F0/3.141593/p/(1-lambda*lambda));printf("D_cylinder=%lf\n",D_cylinder); //工作缸直径
	Dc=1.40*D_cylinder;printf("Dc=%lf\n",Dc); //储油桶直径
	printf("\n");
   
	return 0;
}
