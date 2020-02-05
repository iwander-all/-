#define E 206000//����ģ��
#define pi 3.141593
#include <stdio.h>
#include<math.h>
int main()
{
	double n,fc,fd,L,fa,Fw2;//���Ӷ��������
	double J0,k,s,c,sigma,W0_min,sigma_w,hp,n1,n0,h,b,num;//�����ߴ磬Ƭ���������
    double Length[5]={0},x,y;int i;//���Ƭ�����������
	double H[5]={0},f_delta,R[5]={0},stress_pre[5]={0};//��������״̬���ߺ����ʰ뾶�������
    double R0_check,H_check;//�ְ嵯���ܳɻ���У���������	
	double sigma_max,m2,l1,l2,fai,W0,c_distance,Fx,sigma_D,D_max,Fs,sigma_z,d_xiao,kd,sigma_uneven;//У��ǿ���������
	double ms,psi,omega,alpha,a,delta,vx,F0,delta_s,D_cylinder,p,lambda,Dc;//��������ѡ��
	
	//�������ܾ��Ӷ�

	printf("�������ܾ��Ӷ�\n");
	n=1.4;printf("n=%lf\n",n);//������ƫƵ
    fc=(4.985/n)*(4.985/n)*10;printf("fc=%lf\n",fc);//�������Ӷ�
    Fw2=4743.14;//�����ܵ��൯���ܵ�����������
	c=Fw2/fc;printf("c=%lf\n",c);//�����ܸն�
    fd=70;//���Ӷ�
	fa=15;//���ػ���
	L=1200;//��ɳ���
	printf("\n");


    ////����ߴ磬Ƭ��ȷ��////

    printf("����ߴ磬Ƭ��ȷ��\n");
	s=104;//U����˨���ľ�
    k=0.5;//���Լн�
    n1=0;n0=5;//û���ص�Ƭ��Ԥ��Ϊ5Ƭ
	sigma=1.5/(1.04*(1+0.5*n1/n0));printf("sigma=%lf\n",sigma);//�Ӷ�����ϵ��
    J0=((L-k*s)*(L-k*s)*(L-k*s)*c*sigma)/48/E;printf("J0=%lf\n",J0);//���ܹ�������
    printf("\n");

	sigma_w=550;//��������Ӧ��
	W0_min=Fw2*(L-k*s)/4/sigma_w;printf("W0=%lf\n",W0_min);//�ܽ���ϵ��

	hp=2*J0/W0_min;printf("hp=%lf\n",hp);//ƽ�����

	num=5;//Ƭ��
	b=60;//Ƭ��
	h=pow(12*J0/num/b,0.333333); printf("h=%lf\n",h);//Ƭ��
	h=7; printf("the chosen h is %lf\n",h);//�����ѡ��ĺ��
	J0=num*b*h*h*h/12;printf("ʵ���ܹ��Ծ�J0=%lf\n",J0);
	printf("\n");


	////����ɳ���ȷ��////
   
	printf("����ɳ���ȷ��\n");
	y=num*h*h*h;
	for(i=0;i<num;i++)
	{		
		x=(L-s)/2/num/h/h/h*y+s/2;
		Length[i]=2*x;printf("Length[%d]=%lf\n",i+1,Length[i]);//�����ƬƬ��
		y=y-h*h*h;
    }
	printf("Բ�������ɳ���\n");
	Length[0]=1200;printf("Length[%d]=%lf\n",1,Length[0]);
	Length[1]=980;printf("Length[%d]=%lf\n",2,Length[1]);
	Length[2]=760;printf("Length[%d]=%lf\n",3,Length[2]);
	Length[3]=540;printf("Length[%d]=%lf\n",4,Length[3]);
    Length[4]=320;printf("Length[%d]=%lf\n",5,Length[4]);
    printf("\n");

    
	////��������״̬���ߺ����ʰ뾶////

    printf("��������״̬���ߺ����ʰ뾶����\n");
    f_delta=s*(3*L-s)*(fa+fc)/2/L/L;printf("��f=%lf\n",f_delta);//U����˨�н����γɵĸ߶ȱ仯
	H[0]=f_delta+fc+fa;printf("H[0]=%lf\n",H[0]);//�������״̬�µĻ���
    R[0]=L*L/8/H[0];printf("R[0]=%lf\n",R[0]);//��Ƭ������״̬�µ����ʰ뾶
    stress_pre[0]=0-60;//�����ƬԤӦ��
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

	
	////�ְ嵯���ܳɻ��ߵ�У��////

    printf("�ְ嵯���ܳɻ��ߵ�У��\n");
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
	
	
	////ǿ������////

    printf("ǿ������\n");
	m2=1.25;//���Ḻ��ת��ϵ��
	l1=0.5*Length[0];l2=0.5*Length[0];//���ǰ��γ���
	fai=0.7;//��·����ϵ��
	W0=num*b*h*h/6;printf("W0=%lf\n",W0);//�ܽ���ϵ��
	c_distance=300;//���ɹ̶��㵽·��ľ���
	sigma_max=Fw2*m2*l1*(l2+fai*c_distance)/(l1+l2)/W0+Fw2*m2*fai/b/h;//У������ʱ�������Ӧ��
	printf("sigma_max=%lf\n",sigma_max);
	
	kd=(fc+fd)/fc;printf("kd=%lf\n",kd);
	sigma_uneven=kd*Fw2*l1*l2/(l1+l2)/W0;
	printf("������ƽ·��ʱ�ܵ����Ӧ��sigma_uneven=%lf\n",sigma_uneven);//У�˾�����ƽ·��ʱ�ܵ����Ӧ��


	Fx=Fw2*fai*m2;//�������ܵ���������
	sigma_D=350;//������ʱ���õ�����Ӧ��
	D_max=h*h*b*sigma_D/3/Fx-h/3;	printf("��������ھ�D_max=%lf\n",D_max);//����ھ�
    Fs=0.5*Fw2*m2;
	sigma_z=7;
	d_xiao=Fs/b/sigma_z;printf("��������С�ھ�D_xiao=%lf\n",d_xiao);//�������ھ�
	printf("\n");


	////������������ȷ��////

	printf("������������ȷ��\n");
	ms=483.5;//�����ܵ������ܵ��Ļ�������
    psi=0.24;//�������ϵ������s=0.32,��Y=0.16
	alpha=pi*40/180;
	omega=sqrt(1000*c/ms);	printf("omega=%lf\n",omega);
    //delta=2*psi*ms*omega; printf("delta=%lf\n",delta);//�������ϵ��
	vx=0.04*omega*cos(alpha);//ж���ٶ�
	printf("vx=%lf\n",vx);
	delta=psi*2*ms*omega/cos(alpha)/cos(alpha);printf("delta=%lf\n",delta);//�������ϵ��
    F0=delta*vx;	printf("F0=%lf\n",F0); //�������������
	p=3;//�������������ѹ��
	lambda=0.4;//����ֱ�����Ͳֱ��֮��
	D_cylinder=sqrt(4*F0/3.141593/p/(1-lambda*lambda));printf("D_cylinder=%lf\n",D_cylinder); //������ֱ��
	Dc=1.40*D_cylinder;printf("Dc=%lf\n",Dc); //����Ͱֱ��
	printf("\n");
   
	return 0;
}
