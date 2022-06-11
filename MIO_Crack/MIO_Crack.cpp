// MIO_Crack.cpp : 
// 0x18-0x19 数据是FF D8，那么就删除0x00-0x17的数据，将0x18-0x1f 替换为 89 50 4E 47 0D 0A 1A 0A 
// 0x18-0x19 数据是89 50，那么就删除0x00-0x1d的数据，将0x1e-0x1f 替换为 FF D8
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	FILE* fp;
	FILE* fpout;
	const char TYPEA = (char)0xD8;
	const char TYPEB = (char)0x50;
	char temp = 0;
	printf("【羊油拆包专用】\n");
	printf("请确认待拆文件在同一目录下，数量为7013个，\n且文件名为“a (x)”，否则会报错。\n");
	printf("按回车开始！\n");
	temp = getchar();
	for (int i = 0;i < 7013;i++)
	{
		printf("【当前进度：%d of 7013】", i + 1);
		char in[20];
		char out[20];
		sprintf(in, "a (%d)", i + 1);
		sprintf(out, "%d.png", i + 1);
		fp = fopen(in, "rb");
		fseek(fp, 0x19, SEEK_SET);
		temp = fgetc(fp);
		fclose(fp);  //先判断加密头类型
		if (temp == TYPEA)
		{
			fp = fopen(in, "rb");
			fpout = fopen(out, "wb+");
			fseek(fp, 0x18, SEEK_SET);
			while (1)
			{
				temp = fgetc(fp);
				if (feof(fp))break;
				fputc(temp, fpout);
			}
			fclose(fp);
			fclose(fpout);
			fpout = fopen(out, "rb+");
			fputc((char)0x89, fpout);
			fputc((char)0x50, fpout);
			fputc((char)0x4E, fpout);
			fputc((char)0x47, fpout);
			fputc((char)0x0D, fpout);
			fputc((char)0x0A, fpout);
			fputc((char)0x1A, fpout);
			fputc((char)0x0A, fpout);
			fclose(fpout);
			printf("成功！\n");
		}
		else if (temp == TYPEB)
		{
			fp = fopen(in, "rb");
			fpout = fopen(out, "wb+");
			fseek(fp, 0x1E, SEEK_SET);
			while (1)
			{
				temp = fgetc(fp);
				if (feof(fp))break;
				fputc(temp, fpout);
			}
			fclose(fp);
			fclose(fpout);
			fpout = fopen(out, "rb+");
			fputc((char)0xFF, fpout);
			fputc((char)0xD8, fpout);
			fclose(fpout);
			printf("成功！\n");
		}
		else printf("失败！这个文件头的加密方式未知！\n");
	}
}
