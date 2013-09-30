/*
 *
 */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>

#include "mem_collector.h"
#include "acseg_tree.h"

void print_time(const char *name){
	time_t now;
	now = time(NULL);

	struct tm *now_tm;
	now_tm = localtime(&now);

	char buf[64];
	strftime(buf, 64, "%Y-%m-%d %H:%M:%S\n", now_tm);
	printf("%s\t%s", name, buf);
}

int main(int argc, char **argv)
{
	char dict_path[]  = "word.txt";
	//char dict_path[]  = "dict3.txt";
	char text_path[]  = "mogu.txt";
	//char text_path[]  = "info.txt";

	char new_word[] =  "new_word";

	int hash_size = 50;
	unsigned char buf[8192];

	int text_fd;
	ssize_t read_size;
	int j;

	acseg_index_t *acseg_index;
	acseg_index = acseg_index_init();

	print_time("load dict start");
	if ( !acseg_index_load(acseg_index, dict_path) ) {
		printf("load dict failed\n");
		return 0;
	}
	print_time("load dict end");
	acseg_index_fix(acseg_index);
	print_time("fix index end \n");
	
	acseg_result_t * seg_result;

	acseg_str_t text;

	text_fd = open(text_path, O_RDONLY);
	read_size = read(text_fd, buf, sizeof(buf));
	//printf("%s", buf);

	text.len  = read_size;
	text.data = buf;

	print_time("start seg\n");
	seg_result = acseg_full_seg(acseg_index, &text);
	print_time("end seg\n");

	acseg_str_t *phrase;
	acseg_list_item_t *result_item;
	result_item = seg_result->list->first;
	while (result_item) {
		phrase = (acseg_str_t *) result_item->data;	
		printf("%s ", phrase->data); 
		result_item = result_item->next;
	}

	// free res
	close(text_fd);
	acseg_destory_result(&seg_result);
	acseg_destory_index(&acseg_index);


}
