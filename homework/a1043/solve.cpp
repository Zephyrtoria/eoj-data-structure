#include <bits/stdc++.h>
#define MAXN 107                  // 最大节点个数
#define INFINITY_WEIGHT 0x3F3F3F  // 权重无穷大
typedef struct node {
    int index;
    char data;
    struct node* leftChild;
    struct node* rightChild;
    double weight;
    int sonNum;
} NODE;

NODE* createHuffmanTree(char data[], double weight[], int number);
void traversal(NODE* cur, int depth, std::vector<char>& path, std::string result[], int deps[]);

int main(void) {
    char ch[]{'C', 'B', 'E', 'D', 'F', 'G', 'H', 'A'};
    double we[]{0.15, 0.15, 0.10, 0.10, 0.05, 0.04, 0.01, 0.4};

    createHuffmanTree(ch, we, 8);
}

void swap(NODE* a, NODE* b) {
    NODE* temp = a;
    a = b;
    b = temp;
}

/**
 * [构建一课Huffman树]
 * @param  data[] [每个结点的值]
 * @param  weight[] [每个结点出现的频率]
 * @param  number [] [结点的个数]
 * @return   [Huffman树根]
 */
NODE* createHuffmanTree(char data[], double weight[], int number) {
    // weight:id
    // [] -> pq
    NODE* nodes[500];
    std::priority_queue<std::pair<double, std::pair<char, int>>, std::vector<std::pair<double, std::pair<char, int>>>, std::greater<std::pair<double, std::pair<char, int>>>> pq;

    for (int i = 0; i < number; i++) {
        pq.push({weight[i], {data[i], i}});
        nodes[i] = new NODE;
        nodes[i]->index = i;
        nodes[i]->data = data[i];
        nodes[i]->weight = weight[i];
        nodes[i]->leftChild = nodes[i]->rightChild = nullptr;
        nodes[i]->sonNum = 0;
    }

    int count = 1;
    int len = number;
    while (pq.size() > 1) {
        auto a = pq.top();
        pq.pop();
        auto b = pq.top();
        pq.pop();
        NODE* na = nodes[a.second.second];
        NODE* nb = nodes[b.second.second];
        NODE* ab = new NODE;
        pq.push({a.first + b.first, {INFINITY_WEIGHT, len}});
        if (na->weight == nb->weight) {
            if (na->sonNum > nb->sonNum) {
                swap(na, nb);
            } else if (na->sonNum == nb->sonNum) {
                if (na->data > nb->data) {
                    swap(na, nb);
                }
            }
        }

        ab->index = len;
        ab->data = -1;
        ab->leftChild = na;
        ab->rightChild = nb;
        ab->weight = a.first + b.first;
        nodes[len] = ab;
        len++;
    }

    std::vector<char> path;
    std::string result[number];
    int deps[number];
    traversal(nodes[len - 1], 0, path, result, deps);
    for (int i = 0; i < number; i++) {
        std::cout << nodes[i]->data << ' ' << result[i] << ' ';
        std::printf("%d %.3f\n", deps[i], deps[i] * nodes[i]->weight);
    }
    return nodes[len - 1];
}

void traversal(NODE* cur, int depth, std::vector<char>& path, std::string result[], int deps[]) {
    if (cur == nullptr) {
        return;
    }
    if (cur->data != -1) {
        std::string s = "";
        for (int i = 0; i < path.size(); i++) {
            s += path[i];
        }
        result[cur->index] = s;
        deps[cur->index] = depth;
    }

    if (cur->leftChild) {
        path.push_back('0');
        traversal(cur->leftChild, depth + 1, path, result, deps);
        path.pop_back();
    }
    if (cur->rightChild) {
        path.push_back('1');
        traversal(cur->rightChild, depth + 1, path, result, deps);
        path.pop_back();
    }
}