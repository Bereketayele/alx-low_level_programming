#include "hash_tables.h"
/**
* hash_table_print - function
* @ht: hash table to print
*
* Description: function to print a hash table
* Return: Nothing
*/
void hash_table_print(const hash_table_t *ht)
{
	hash_node_t *moveNode;
	unsigned long int index;
	int i = 0;

	if (ht == NULL)
		return;

	printf("{");
	for (index = 0; index < (ht->size); index++)
	{
		moveNode = ht->array[index];
		while (moveNode != NULL)
		{
			if (i > 0)
				printf(", ");

			printf("\'%s\': \'%s\'", (moveNode->key), (moveNode->value));
			moveNode = moveNode->next;
			i++;
		}
	}
	printf("}\n");
}
