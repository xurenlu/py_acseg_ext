
#include "mem_collector.h"
#include "acseg_util.h"

int main(int argc, char **argv){
	mc_collector_t *mc;	
	mc = NULL;

	void *data;
	data = (void *) mc_calloc(&mc, 15);

	acseg_list_t *list;	
	list = acseg_list_init(&mc);
	acseg_queue_push(list, data, &mc);	
	acseg_queue_pop(list);
	mc_free(data);
	mc_destory(mc);
}
