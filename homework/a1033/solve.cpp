/**
 * 【元素入栈操作】
 * @param  x   [压入栈中的元素的值]
 * @return     []
 */
void Stack::push(int x)
{
    // TODO
    data[size++] = x;
    
}

/**
 * 【查询栈顶元素操作】
 * @param      []
 * @return     [栈顶元素的值]
 */
int Stack::top()
{
    // TODO
    return data[size - 1];
}

/**
 * 【弹出栈顶元素操作】
 * @param      []
 * @return     []
 */
void Stack::pop()
{
    // TODO
    size--;
}

/**
 * 【大整数相加操作】
 * @param  s1,s2 [以栈的形式表示的非负大整数]
 * @return       [两个大整数的和的链表表头指针]
 */
node *add(Stack &s1, Stack &s2)
{
    // TODO
    node *result = new node(-1);
    
    int cr = 0;
    while (!s1.empty() || !s2.empty())
	{
		if (!s1.empty()){
			cr += s1.top();
			s1.pop();
		}
					
		if (!s2.empty()) {
			cr += s2.top();
			s2.pop();
		}
			
		node *temp = new node(cr % 10);
		temp->next = result->next;
		result->next = temp;
		
		cr /= 10;
	}    
	
	if (cr > 0)
	{
		node *temp = new node(1);
		temp->next = result->next;
		result->next = temp;
	}
	node *temp = result->next;
	delete result;
	
	return temp;
}