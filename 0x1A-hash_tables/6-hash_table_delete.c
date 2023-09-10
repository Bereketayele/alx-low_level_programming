#include "hash_tables.h"
/**
* hash_table_delete - function
* @ht: hash table to delete
*
* Description: Function to delete a hash table.
* Return: 0 (Success)
*/
void hash_table_delete(hash_table_t *ht)
{
	hash_node_t *moveNode, *temp;
	unsigned long int index;

	if (ht == NULL)
		return;

	for (index = 0; index < (ht->size); index++)
	{
		moveNode = ht->array[index];
		while (moveNode != NULL)
		{
			temp = moveNode->next;
			if (moveNode->key != NULL)
				free(moveNode->key);
			if (moveNode->value != NULL)
				free(moveNode->value);
			if (moveNode != NULL)
				free(moveNode);
			moveNode = temp;
		}
	}
	free(ht->array);
	free(ht);
}
