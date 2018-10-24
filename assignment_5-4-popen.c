#include <stdio.h>
int main() {
	FILE *fpr, *fpw;
	char buf[256];
	char *test = "hello\nworld\n1\n2";
	buf[255] = '\0';
	int i;

	fpr = popen("ls","r");
	fpw = popen("wc -l","w");
	
	while(i=fread(buf,sizeof(char),255,fpr)){
		fwrite(buf,i,sizeof(char),fpw);
	}

	pclose(fpr);
	pclose(fpw);
	
}
