int[] array = new int[] {4,5,1,2,6};
int size = 5;
int min_el = 100;
for(int i = 0; i < 5; i++)
{
    if(array[i] < min_el)
    {
        min_el = array[i];
    }
}

System.Console.WriteLine("Min Element in array: {0}", min_el);