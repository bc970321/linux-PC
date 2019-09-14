#include <stdio.h> //主要包括常用的输入/输出函数
#include <string.h> //主要包括常用的字符串操作函数
#include <stdlib.h> //字符串转换函数、内存分配函数、过程控制函数

//以下两个库函数可使用之一，完成库函数的调用
#include <windows.h>//作用是将键盘输入的在屏幕上 打印 出来等
//#include <conio.h>//字符的输入、输出函数，字符操作函数、颜色设置函数

/*****Huffman结构定义**********/
typedef struct node 
{ 
    long    w;//w为权值
    short   p,l,r; //p为parent，l为左孩子，r为右孩子
}htnode,*htnp;//动态分配数组存储哈夫曼树

/*****Huffman编码表结构定义*****/
typedef struct huffman_code 
{ 
    unsigned char len;//长度
    unsigned char  *codestr; 
}hufcode;

typedef char **huffmancode;//动态分配数组存储哈夫曼编码表


/*********函数声明*********/
int initial_files(char *source_filename,FILE **inp,char *obj_filename,FILE **outp);
//1.初始化文件名
char *create_filename(char *source_filename,char* obj_filename);
//2.创建文件名
int compress(char *source_filename,char *obj_filename);
//3.压缩文件
long frequency_data(FILE *in,long fre[]);
//4.频率数据
int search_set(htnp ht,int n,int *s1, int *s2);
//5.选取结点权值最小的树
int create_hftree(long w[],int n,htnode ht[]);
//6.创建哈夫曼树
int encode_hftree(htnp htp,int n,hufcode hc[]);
//7.编码哈夫曼树
unsigned char chars_to_bits(const unsigned char chars[8]);
//8.把字符串用二进制数字表示：运用位运算的知识
int write_compress_file(FILE *in,FILE *out,htnp ht,hufcode hc[],char* source_filename,long source_filesize);
//9.写入压缩文件
int decompress(char *source_filename,char *obj_filename);
//10.解压缩
void get_mini_huffmantree(FILE* in,short mini_ht[][2]);
//11.解压构造微哈夫曼树
int write_decompress_file(FILE *in,FILE* out,short mini_ht[][2],long bits_pos,long obj_filesize);
//12.写入解压缩
int d_initial_files(char *source_filename,FILE **inp,char *obj_filename,FILE **outp);
//13.重新变成原始文件
/*菜单函数*/
void main()
{
	int s;
	char filename[10];
	//system("color 3F");//设置背景颜色 1.深蓝色 2.墨绿色 3.天蓝色4.棕红色 5.紫色6.褐色7.灰色
	    printf("        ****************************************************\n");
		printf("                    *           菜单：            *\n");
		printf("                    *   1.------压缩--------      *\n");
		printf("                    *   2.------解压缩------      *\n");
		printf("                    *   0.------退出--------      *\n");
		printf("        ****************************************************\n");
	scanf("%d",&s);
	while(s!=0)
	{
		getchar();
		switch(s)
		{
			case 1:
				puts("请输入待压缩文件路径：");
				gets(filename);
				compress(filename,NULL);
				break;
			case 2:
				puts("请输入待解压文件路径：");
				gets(filename);
				decompress(filename,NULL);
				break;
			default : 
				printf("指令错误！请重新输入指令：\n");
		}
		puts(" ");
		printf("        ****************************************************\n");
		printf("                    *           菜单：              *\n");
		printf("                    *   1.------压缩--------         *\n");
		printf("                    *   2.------解压缩------        *\n");
		printf("                    *   0.------退出--------          *\n");
		printf("        ****************************************************\n");
		scanf("%d",&s);
	}
}

                                       //FILE*定义指向文件的指针变量 inp,  outp
int initial_files(char *source_filename,FILE **inp,char *obj_filename,FILE **outp) //1.初始化文件
{                                     
    if(fopen(source_filename,"rb")==NULL) //用fopen函数，打开待压缩文件
    { 
        return -1;//用-1标记
    } 

    if(obj_filename==NULL) //压缩文件为空
    { 
        if((obj_filename=(char*)malloc(256*sizeof(char)))==NULL) //分配空间
        { 
            return -1;
        }                     
        create_filename(source_filename,obj_filename);    // 调用函数create_filename(source_filename,obj_filename);
    } 
    if(strcmp(source_filename,obj_filename)==0) //字符串比较函数：如果待压缩文件和压缩文件比较后相同
    { 
        return -1;
    } 
    printf("待压缩文件:%s,压缩文件:%s\n",source_filename,obj_filename);      //待压缩文件source_filename,压缩文件obj_filename
    if((*outp=fopen(obj_filename,"wb"))==NULL) //wb:含义：为了读和写，建立一个新的二进制文件，如果指定的文件不存在，建立新文件
    { 
        return -1;
    } 
    if((*inp=fopen(source_filename,"rb"))==NULL) //rb：为了读和写,打开一个二进制文件，如果指定的文件不存在，出错
    { 
        return -1;
    }
    free(obj_filename); //释放压缩文件（关闭目标文件）
    return 0; 
} 
 

char *create_filename(char *source_filename,char* obj_filename) //2.创建文件
{ 
    char *temp; 
    if((temp=strrchr(source_filename,'.'))==NULL) //把原始文件 赋给 临时文件夹 为空
    { 
        strcpy(obj_filename,source_filename);//字符串 复制 函数:将原始文件复制到目标文件
        strcat(obj_filename,".zip");         //字符串 连接 函数：将.zip连接到目标文件后
    } 
    else 
    { 
        strncpy(obj_filename,source_filename,temp-source_filename); 
        obj_filename[temp-source_filename]='\0';
        strcat(obj_filename,".zip");//strcat：字符串连接函数
    } 
	return obj_filename;
}

                   /*待压缩文件                压缩文件 */
int compress(char *source_filename,char *obj_filename)       //3.压缩文件
{ 
    FILE *in,*out;//定义两个指向文件的指针变量 in，out
	char ch;
    int error_code,i,j; 
    float compress_rate; //压缩比率
    hufcode hc[256]; 
    htnode  ht[256*2-1]; 
    long frequency[256],source_filesize,obj_filesize=0; 
    error_code=initial_files(source_filename,&in,obj_filename,&out);//调用初始化文件的函数
    if(error_code!=0) 
    { 
		puts("文件打开失败！请重新输入文件路径：");
        return error_code; 
    } 
    source_filesize=frequency_data(in,frequency);   //调用频率数据赋给源文件大小
    printf("文件大小 %ld 字节\n",source_filesize); 
    error_code=create_hftree(frequency,256,ht); 
    if(error_code!=0) 
    { 
		puts("建立哈夫曼树失败！");
        return error_code; 
    } 

    error_code=encode_hftree(ht,256,hc); //调用哈夫曼编码函数
    if(error_code!=0) 
    { 
		puts("建立哈夫曼编码失败！");
        return error_code; 
    } 
    for(i=0;i<256;i++) 
        obj_filesize+=frequency[i]*hc[i].len;
    obj_filesize=obj_filesize%8==0?obj_filesize/8:obj_filesize/8+1;
    for(i=0;i<256-1;i++) 
        obj_filesize+=2*sizeof(short);
    obj_filesize+=strlen(source_filename)+1;
    obj_filesize+=sizeof(long);
    obj_filesize+=sizeof(unsigned int);
    compress_rate=(float)obj_filesize/source_filesize; 
    printf("压缩文件大小:%ld字节,压缩比例:%.2lf%%\n",obj_filesize,compress_rate*100); 
    error_code=write_compress_file(in,out,ht,hc,source_filename,source_filesize); 
	if(error_code!=0) 
    { 
		puts("写入文件失败！");
        return error_code; 
    } 
    puts("压缩完成!"); 
	puts(" ");
	puts("是否打印该文件中字符对应的huffman树及编码？");
	puts("          Please input Y OR N");
	do{
		scanf("%s",&ch);
		switch(ch)
		{
			case 'Y': 
				puts("以下是哈夫曼树：");
				for(i=256;i<256*2-2;i++)
				{
					if(ht[i].w>0)
						printf("%-10d%-10d%-10d%-10d%-10d\n",i,ht[i].w,ht[i].p,ht[i].l,ht[i].r);
				}
				puts("以下是哈夫曼编码：");	
				for(i=0;i<256;i++)
				{
					if(frequency[i]==0)
						i++;
					else
					{
						printf("%d\t",frequency[i]);
						for(j=0;j<hc[i].len;j++)
							printf(" %d",hc[i].codestr[j]);
						printf("\n");
					}
				}
				break;
			case  'N':	break;
			default : 
				printf("指令错误！请重新输入指令：\n");
		}
	}while(ch!='Y'&&ch!='N');
    fclose(in); 
    fclose(out);
    for(i=0;i<256;i++) 
    { 
        free(hc[i].codestr); 
    } 
    return 0; 
} 




long frequency_data(FILE *in,long frequency[]) //4.频率数据
{ 
    int     i,read_len; 
    unsigned char   buf[256];
    long    filesize;//文件大小
     
    for(i=0;i<256;i++) 
    { 
        frequency[i]=0; 
    } 
    fseek(in,0L,SEEK_SET); 
    read_len=256;     

    while(read_len==256) 
    { 
        read_len=fread(buf,1,256,in); 
        for(i=0;i<read_len;i++) 
        { 
            frequency[*(buf+i)]++;
        } 
    } 
    for(i=0,filesize=0;i<256;i++) 
    { 
        filesize+=frequency[i];
    } 

    return filesize; 
} 



int search_set(htnp ht,int n,int *s1, int *s2) //5.选取结点权值最小的树
{ 
    int i,x; 
	long minValue = 1000000,min = 0;
    for(x=0;x<n;x++) 
    { 
        if(ht[x].p==-1)  break; 

    } 
    for(i=0;i<n;i++) 
    { 
        if(ht[i].p==-1 && ht[i].w < minValue) 
        { 
			minValue = ht[i].w;
            min=i;
        } 
    } 
    *s1 = min;

    minValue = 1000000,min = 0;
    for(i=0;i<n;i++) 
    { 
        if(ht[i].p==-1 && ht[i].w < minValue && i != *s1) 
        { 
           	minValue = ht[i].w;
            min=i;
        } 
    } 

    *s2 = min;
    return 1; 
} 



int create_hftree(long w[],int n,htnode ht[]) //6.创建哈夫曼树
{ 
    int m,i,s1,s2; 

    if (n<1)    return -1; 
    m=2*n-1;
    if (ht==NULL)   return -1; 
    for(i=0;i<n;i++) 
    { 
        ht[i].w=w[i];
		ht[i].p=ht[i].l=ht[i].r=-1; 
    }  
    for(;i<m;i++) 
    { 
        ht[i].w=ht[i].p=ht[i].l=ht[i].r=-1;
    } 

    for(i=n;i<m;i++)
    { 
        search_set(ht,i,&s1,&s2); 

        ht[s1].p = ht[s2].p = i;
        ht[i].l  = s1;
		ht[i].r = s2; 
        ht[i].w  = ht[s1].w + ht[s2].w; 
    } 
    return 0; 
} 



int encode_hftree(htnp htp,int n,hufcode hc[]) //7.o-1编码哈夫曼树
{ 
    int i,j,p,codelen;
    unsigned char *code=(unsigned char*)malloc(n*sizeof(unsigned char)); 
     
    if (code==NULL) return -1; 
    for(i=0;i<n;i++)
    { 
        for(p=i,codelen=0;p!=2*n-2;p=htp[p].p,codelen++) 
        { 
            code[codelen]=(htp[htp[p].p].l==p?0:1);
        }        
        if((hc[i].codestr=(unsigned char *)malloc((codelen)*sizeof(unsigned char)))==NULL) 
        { 
            return -1;
        } 
        hc[i].len=codelen; 
        for(j=0;j<codelen;j++) 
        { 
            hc[i].codestr[j]=code[codelen-j-1];
        } 
    }
    free(code);
    return 0; 
} 



unsigned char chars_to_bits(const unsigned char chars[8]) //8.把字符串用二进制数字表示
{ 
    int i; 
    unsigned char bits=0; 
    bits|=chars[0]; 
    for(i=1;i<8;++i)
    { 
        bits<<=1; 
        bits|=chars[i];      
    } 
    return bits; 
} 


int write_compress_file(FILE *in,FILE *out,htnp ht,hufcode hc[],char* source_filename,long source_filesize) //9.写入压缩文件
{ 
    unsigned int    i,read_counter,write_counter,zip_head=0xFFFFFFFF;
    unsigned char   write_char_counter,code_char_counter,copy_char_counter,
            read_buf[256],write_buf[256],write_chars[8],filename_size=strlen(source_filename);
    hufcode *cur_hufcode; 

    fseek(in,0L,SEEK_SET); 
    fseek(out,0L,SEEK_SET); 
    fwrite(&zip_head,sizeof(unsigned int),1,out);
    fwrite(&filename_size,sizeof(unsigned char),1,out); 
    fwrite(source_filename,sizeof(char),filename_size,out); 
    fwrite(&source_filesize,sizeof(long),1,out); 
    for(i=256;i<256*2-1;i++) 
    { 
        fwrite(&(ht[i].l),sizeof(ht[i].l),1,out);
        fwrite(&(ht[i].r),sizeof(ht[i].r),1,out);
    } 
    write_counter=write_char_counter=0;
    read_counter=256;
    while(read_counter==256) 
    { 
        read_counter=fread(read_buf,1,256,in);
        for(i=0;i<read_counter;i++) 
        { 
            cur_hufcode=&hc[read_buf[i]];
            code_char_counter=0;
            while(code_char_counter!=cur_hufcode->len) 
            {
                copy_char_counter=  (8-write_char_counter > cur_hufcode->len-code_char_counter ?  
                                    cur_hufcode->len-code_char_counter : 8-write_char_counter); 
                memcpy(write_chars+write_char_counter,cur_hufcode->codestr+code_char_counter,copy_char_counter); 
                write_char_counter+=copy_char_counter;
                code_char_counter+=copy_char_counter;
                if(write_char_counter==8) 
                { 
                    write_char_counter=0;
                    write_buf[write_counter++]=chars_to_bits(write_chars); 
                    if(write_counter==256) 
                    { 
                        fwrite(write_buf,1,256,out);
                        write_counter=0;
                    } 
                } 
            } 
        } 
         
    } 
    fwrite(write_buf,1,write_counter,out);


    if(write_char_counter!=0) 
    { 
       
		
		write_char_counter=chars_to_bits(write_chars);//位函数的调用，实现压缩功能



        fwrite(&write_char_counter,1,1,out);
    } 
    return 0; 
} 



void get_mini_huffmantree(FILE* in,short mini_ht[][2]) //
{ 
    int i; 
    for(i=0;i<256;i++) 
    { 
        mini_ht[i][0]=mini_ht[i][1]=-1;
    } 
    fread(mini_ht[i],sizeof(short),2*(256-1),in);
} 



int write_decompress_file(FILE *in,FILE* out,short mini_ht[][2],long bits_pos,long obj_filesize) //写入解压缩
{ 
    long    cur_size; 
    unsigned char   read_buf[256],write_buf[256],convert_bit; 
    unsigned int    read_counter,write_counter,cur_pos; 
    fseek(in,bits_pos,SEEK_SET);
    fseek(out,0L,SEEK_SET);
    read_counter=256-1;
    cur_size=write_counter=0;
    cur_pos=256*2-2;
    while(cur_size!=obj_filesize) 
    {   
        if(++read_counter==256) 
        { 
            fread(read_buf,1,256,in);
            read_counter=0;
        } 
        for(convert_bit=128;convert_bit!=0;convert_bit>>=1) 
        { 
            cur_pos=((read_buf[read_counter]&convert_bit)==0?mini_ht[cur_pos][0]:mini_ht[cur_pos][1]);
            if(cur_pos<256)
            { 
                write_buf[write_counter]=(unsigned char)cur_pos; 
                if(++write_counter==256)
                { 
                    fwrite(write_buf,1,256,out);
                    write_counter=0;
                } 
                cur_pos=256*2-2;
                if(++cur_size==obj_filesize) 
                { 
                    break;
                } 
            } 
        } 

    } 
    fwrite(write_buf,1,write_counter,out);
    return 0; 
} 





int decompress(char *source_filename,char *obj_filename) //解压缩文件
{ 
    int     error_code; 
    FILE    *in,*out; 
    short   mini_ht[256*2-1][2]; 
    long    obj_filesize; 

    error_code=d_initial_files(source_filename,&in,obj_filename,&out); //调用重新变为原始文件的函数
    if(error_code!=0) 
    { 
		puts("打开文件失败！请重新输入文件路径：");
        return error_code; 
    } 
    fread(&obj_filesize,sizeof(long),1,in); 
    printf("解压文件大小:%ld字节\n",obj_filesize); 
    get_mini_huffmantree(in,mini_ht); //调用函数
    error_code=write_decompress_file(in,out,mini_ht,ftell(in),obj_filesize); //调用函数
    if(error_code!=0) 
    { 
		puts("解压缩失败！");
        return error_code; 
    } 
    puts("解压缩完成!"); 
    fclose(in); 
    fclose(out); 
    return 0; 
} 


int d_initial_files(char *source_filename,FILE **inp,char *obj_filename,FILE **outp) //重新变成原始文件
{ 
    unsigned int    zip_head; //压缩文件的头文件
    unsigned char   filename_size;    //文件大小 
    if ((*inp=fopen(source_filename,"rb"))==NULL) //rb读写，打开输出文件并使*inp指向此文件
    { 
        return -1;
    } 
	printf("待解压缩文件:%s,",source_filename); 
    fread(&zip_head,sizeof(unsigned int),1,*inp); 
    if(zip_head!=0xFFFFFFFF) 
    { 
        return -1;
    } 
    if(obj_filename==NULL) 
    { 
        if((obj_filename=(char*)malloc(256*sizeof(char)))==NULL) //分配
        { 
            return -1;
        } 
        fread(&filename_size,sizeof(unsigned char),1,*inp);
        fread(obj_filename,sizeof(char),filename_size,*inp);
        obj_filename[filename_size]='\0';
    } 
    else 
    { 
        fread(&filename_size,sizeof(unsigned char),1,*inp); 
        fseek(*inp,filename_size,SEEK_CUR);
    } 
    printf("解压缩文件:%s\n",obj_filename); 
    if((*outp=fopen(obj_filename,"wb"))==NULL) 
    { 
        return -1;
    } 
    free(obj_filename);//释放压缩文件
    return 0; 
}
