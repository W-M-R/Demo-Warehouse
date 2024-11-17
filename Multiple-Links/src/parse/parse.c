
#include <stdio.h>
#include <symbol.h>

extern struct symbol_table symbol_tabel[];
extern unsigned long symbol_num;

void parse_print(void)
{
	struct symbol_table *table = symbol_tabel;
	int i;
	for (i = 0; i < symbol_num; i++)
		{
			if ('b' == table[i].mask)
				{
					printf("parse %s addr: 0x%016x size: %d\n", table[i].name, table[i].addr, table[i].size);
				}
		}
}

