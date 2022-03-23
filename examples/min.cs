class Program
    {
        static void Main(string[] args)
        {
            int[,] array = new int[5, 5];
            InitializeArray(array);
            Console.WriteLine();
            Console.WriteLine("Min Element in array: {0}", MinElement(array));
            Console.ReadLine();
        }
 
        static void InitializeArray(int[,] array)
        {
            Random random = new Random();
            for (int i = 0; i < array.GetLength(0); i++)
            {
                for (int j = 0; j < array.GetLength(1); j++)
                {
                    array[i, j] = random.Next(1000);
                    Console.Write("[{0},{1}] = {2} ", i, j, array[i, j]);
                }
                Console.WriteLine();
            }
        }
 
        static int MinElement(int[,] array)
        {
            int minElement = array[0, 0];
            for (int i = 0; i < array.GetLength(0); i++)
            {
                for (int j = 0; j < array.GetLength(1); j++)
                {
                    if (minElement > array[i, j])
                    {
                        minElement = array[i, j];
                    }
                }
            }
            return minElement;
        }
    }