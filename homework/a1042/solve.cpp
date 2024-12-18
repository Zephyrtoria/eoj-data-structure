#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 1000
#define inf 0x7fffffff

/* 其他声明与定义，细节隐藏不表 */
typedef struct huffnode {
    char data;                    // 值
    struct huffnode* leftChild;   // 左子树
    struct huffnode* rightChild;  // 右子树
    /* 其他成员变量，细节隐藏不表 */
} HUFFNODE;

/* 你的代码将会被嵌入在这个部分 */
void decipherHuffmanCoding(HUFFNODE* head, char cipher[]) {
    HUFFNODE* cur = head;
    for (int idx = 0, size = strlen(cipher); idx < size; idx++) {
        if (cur->leftChild == nullptr && cur->rightChild == nullptr) {
            printf("%c", cur->data);
            cur = head;
        }
        if (cipher[idx] == '0') {
            cur = cur->leftChild;
        } else {
            cur = cur->rightChild;
        }
    }
    printf("%c", cur->data);
}