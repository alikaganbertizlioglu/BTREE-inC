#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct BTREE_NODE_s *BTREE_NODE;
typedef struct BTREE_NODE_s {
    int n; // number of keys in this node
    unsigned int *key; // keys
    BTREE_NODE *child; // children pointers
} BTREE_NODE_t[1];

typedef struct BTREE_s *BTREE;
typedef struct BTREE_s {
    BTREE_NODE root;
} BTREE_t[1];

#define MAXDEG 6

BTREE btree_init() {
    BTREE bt = (BTREE) malloc(sizeof(BTREE_t));
    bt->root = NULL;
    return bt;
}

BTREE_NODE btree_node_init() {
    BTREE_NODE node = (BTREE_NODE) malloc(sizeof(BTREE_NODE_t));
    node->key = (unsigned int *) malloc(sizeof(unsigned int) * (MAXDEG - 1));
    node->child = (BTREE_NODE *) malloc(sizeof(BTREE_NODE) * MAXDEG);
    node->n = 0;
    return node;
}

void swap(void *a, void *b) {
    int temp = *(int *)a;
    *(int *)a = *(int *)b;
    *(int *)b = temp;
}

void sort(BTREE_NODE node) {
    int i, j;
    for(i = 0; i < node->n - 1; i++) {
        for(j = 0; j < node-> n - i - 1; j++) {
            if(node->key[j] > node->key[j+1]) {
                swap(&node->key[j], &node->key[j+1]);
            }
        }
    }
}

void create_btree(BTREE_NODE root, unsigned int *key) {
    int i, j;
    for(i = MAXDEG - 1; i < 35; i++) {
        int added = 0;
        for(j = 0; j < MAXDEG; j++) {
            if(key[i] <= root->key[j] && added == 0) {
                int keys = root->child[j]->n;
                if(keys <= MAXDEG - 1) {
                    root->child[j]->key[keys] = key[i];
                    root->child[j]->n++;
                    sort(root->child[j]);
                    added = 1;
                }else{
                    printf("Error in the input!\n");
                }
            }
            if(key[i] > root->key[4] && added == 0) {
                int keys = root->child[5]->n;
                if(keys <= MAXDEG - 1) {
                    root->child[5]->key[keys] = key[i];
                    root->child[5]->n++;
                    sort(root->child[5]);
                    added = 1;
                }else{
                    printf("Error in the input!\n");
                }
            }
        }
    }
}

void print_btree(BTREE_NODE root) {
    int i, j;
    for(i = 0; i < MAXDEG; i++){
        for(j = 0; j < MAXDEG - 1; j++){
            printf("%d ",root->child[i]->key[j]);
        }
        if(i < MAXDEG - 1){
            printf("  %d   ",root->key[i]);
        }
    }
}

void reverse(int arr[], int n)
{
    int aux[n];

    for (int i = 0; i < n; i++) {
        aux[n - 1 - i] = arr[i];
    }

    for (int i = 0; i < n; i++) {
        arr[i] = aux[i];
    }
}

void delete(int arr[],int size){

}
int main(void) {
    BTREE btree = btree_init();
    BTREE_NODE root = btree->root;

    unsigned int key[35] = { 25, 45, 70, 90, 100, 17, 34, 19, 26, 59, 41, 99, 38, 105, 75, 91, 110, 9, 50, 55, 80, 81, 95, 112, 40, 5, 60, 118, 120, 85, 99, 88, 68, 93, 24 };

    root = btree_node_init();

    for(int i = 0; i < MAXDEG - 1; i++) {
        root->key[i] = key[i];
    }

    for(int i = 0; i < MAXDEG; i++) {
        root->child[i] = btree_node_init();
    }

    create_btree(root, key);

    print_btree(root);

    int minkey = ceil(MAXDEG/2) - 1;

    unsigned int delete[21] = {9, 17, 19, 5, 110, 112, 105, 120, 100, 85, 81, 75, 80, 88, 68, 70, 34, 40, 25, 118, 90};

    // delete array's elements from the b-tree

    for (int x = 0; x < 4; ++x) {// bu for silincek 21 eleman oldugu ciin 21 kez calısıor
        for (int i = 0; i < MAXDEG ; ++i){//cocuklarda donuo
            for (int j = 0; j < root->child[i]->n ; ++j) {//keylerde donuo
                if(root->child[i]->key[j] == delete[x]){// aradıgı keyi buldu mu kontrol eden if
                    if(minkey < root->child[i]->n){
                        // key arrayında kac key oldugu (n-1) ini  n-1 ile uulastıgın keye
                        for (j = 1; j < (root->child[i]->n) - 1; ++j) {
                            root->child[i]->key[j] = root->child[i]->key[j+1];
                        }
                        root->child[i]->key[j] = -1;
                        root->child[i]->n = root->child[i]->n-1;
                    }
                    else
                    {
                        root->child[i]->key[j] = root->key[i];
                        int temp = root->key[i];

                        root->key[i] = root->child[i+1]->key[i];

                        root->child[i+1]->key[i]=temp;


                    }
                }
            }
        }
    }

    printf("\n******************************************************\n");
    print_btree(root);



    return EXIT_SUCCESS;
}

