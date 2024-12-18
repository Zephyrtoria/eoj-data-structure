
int listRangeDelete(int list[], int n, int m, int M) {
    // TODO
    int i = 0;
    for (int j = 0; j < n; j++)
	{
		if (m <= list[j] && list[j] <= M)
		{
			list[i++] = list[j];
		}
	}
	return i;
}