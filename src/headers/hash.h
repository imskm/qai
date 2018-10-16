#define HASH_TABLE_SIZE 101


// Hash Table structures.
// 1.
typedef struct HashTableNode {

	char* key;
	void* data;
	struct HashTableNode* next;

}HashTableNode;

// 2.
typedef struct HashTable {
	HashTableNode* HTHead; // Hash Table head pointer
}HashTable;

// 3. this is for users
typedef struct HashMap {

	unsigned size_data;
	HashTable* htp;
	long unsigned int count;

}HashMap;



static HashTable* hashtable_init()
{
	HashTable* htp = (HashTable *) malloc(sizeof(HashTable) * HASH_TABLE_SIZE);
	if(htp) memset(htp, 0, HASH_TABLE_SIZE);

	return htp;
}

/**
 * Creates new HashMap in memory and returns
 * base address of newly created HashMap on
 * successful creation else NULL.
 *
 * @param unsigned size_data  size of user data to be put in HashTable
 * @return HashMap* | NULL
 */
HashMap* hash_create(unsigned size_data)
{
	HashMap* new_hm = (HashMap *) malloc(sizeof(HashMap));
	if(new_hm)
	{
		new_hm->size_data = size_data;
		new_hm->htp = hashtable_init();
		new_hm->count = 0;
	}

	return new_hm;
}

unsigned hash_hash(char* key)
{
	unsigned hashVal = 0;

	for(int i = 0; i < strlen(key); i++)
	{
		hashVal = hashVal + (key[i] * i);
	}

	return hashVal % HASH_TABLE_SIZE;
}

void* hash_get(HashMap* hm, char* key)
{
	unsigned hashIndex = hash_hash(key);

	for(HashTableNode* htnp = hm->htp[hashIndex].HTHead; htnp != NULL; htnp = htnp->next)
	{
		if(strcmp(htnp->key, key) == 0)
			return htnp->data;
	}

	return NULL;
}


bool hash_put(HashMap* hm, char* key, void* data)
{
	unsigned hashIndex = hash_hash(key);
	void* htnp;

	if((htnp = (void *) hash_get(hm, key)) == NULL)
	{
		HashTableNode* new_htn = (HashTableNode*) malloc(sizeof(HashTableNode));
		// on failure
		if(!new_htn) return false;

		// Updated (before these lines are not present
		new_htn->key = strdup(key);

		new_htn->data = (void *) malloc(hm->size_data);
		memcpy(new_htn->data, data, hm->size_data);

		new_htn->next = hm->htp[hashIndex].HTHead;
		hm->htp[hashIndex].HTHead = new_htn;
	}
	else
	{
		memcpy(htnp, data, hm->size_data);
	}

	return true;
}


// TODO
bool hash_delete(HashMap* hm, char* key)
{
	return true;
}

// TODO
bool hash_destroy(HashMap* hm)
{
	return true;
}

/**
 * USAGE
 *

truct MyData {
	int roll;
	char name[10];
};

HashMap* hm = hash_create(sizeof(struct MyData));
struct MyData mydata;

// Putting new data with key 111
mydata.roll = 111;
strcpy(mydata.name, "Zidan");
hash_put(hm, "111", &mydata);

// Putting new data with key 112
mydata.roll = 112;
strcpy(mydata.name, "Mukhtar");
hash_put(hm, "112", &mydata);

// Overriding the previously sotred data with key 111
mydata.roll = 113;
strcpy(mydata.name, "Farhan");
hash_put(hm, "111", &mydata);

// Getting the data from the hash table
struct MyData* md = (struct MyData *) hash_get(hm, "111");
printf("Roll = %d\n", md->roll);
printf("Name = %s\n", md->name);

// Getting the data from the hash table again
md = (struct MyData *) hash_get(hm, "112");
printf("Roll = %d\n", md->roll);
printf("Name = %s\n", md->name);
*/
